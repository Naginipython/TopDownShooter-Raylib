#include "game.h"

#include "main.h"

// 0.5s cooldown
Game::Game()
    : shootTimer(0.0f),
      shootCooldown(0.5f),
      healthTimer(0.0f),
      healthCooldown(5.0f) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Shooter");
  // MaximizeWindow();
  SetTargetFPS(60);
  camera = {0};
  camera.target = {0, 0};
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera.zoom = 1.0f;
}
Game::~Game() { CloseWindow(); }

void Game::run() {
  while (!WindowShouldClose()) {
    update();
    draw();
  }
}

void Game::update() {
  // temp
  if (IsKeyPressed(KEY_R)) {
    println("hurt");
    player.health = 1;
    healthTimer = 0.0f;
  }
  // Player
  player.update();
  camera.target = player.getPosition();
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

  // Player health
  healthTimer += GetFrameTime();
  if (healthTimer >= healthCooldown && player.health < 3.0f) {
    player.health += 0.1f;
    if (player.health >= 3.0f) {
      player.health = 3.0f;
      healthTimer = 0.0f;
    }
  }

  playerShoot();

  // Bullets
  for (auto it = bullets.begin(); it != bullets.end();) {
    it->update();
    // Delete uneeded bullets
    Vector2 screenBulletPos = GetWorldToScreen2D(it->getPosition(), camera);
    if (screenBulletPos.x < 0 || screenBulletPos.x > GetScreenWidth() ||
        screenBulletPos.y < 0 || screenBulletPos.y > GetScreenHeight()) {
      it = bullets.erase(it);
    } else {
      ++it;
    }
  }

  // Create enemy
  createEnemies();
}

void Game::draw() {
  BeginDrawing();
  ClearBackground(DARKGRAY);

  BeginMode2D(camera);
  DrawRectangle(100, 0, 200, 200, RED);

  for (Bullet& bullet : bullets) {
    bullet.draw(player.getPosition());
  }

  Vector2 playerPos = player.getPosition();
  float startX = playerPos.x - 30;
  // Health timer
  float healthLeft = player.health / 3.0f;
  if (player.health < 3)
    DrawLineEx({startX, playerPos.y - 45},
               {startX + (60 * healthLeft), playerPos.y - 45}, 5, RED);

  // Bullet timer
  float timeLeft = shootTimer / shootCooldown;
  if (timeLeft < 1)
    DrawLineEx({startX, playerPos.y - 35},
               {startX + (60 * timeLeft), playerPos.y - 35}, 5, DARKBLUE);

  player.draw();
  EndMode2D();

  // Menu

  EndDrawing();
}

void Game::playerShoot() {
  shootTimer += GetFrameTime();
  if (shootTimer >= shootCooldown && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 screenPos = {(float)GetMouseX(), (float)GetMouseY()};
    Vector2 worldPos = GetScreenToWorld2D(screenPos, camera);
    bullets.push_back(Bullet(worldPos, player.getPosition()));
    shootTimer = 0.0f;
  }
}

void Game::createEnemies() {
  int side = GetRandomValue(0, 3);
  switch (side) {
    case 0: {  // North
      Vector2 pos = {(float)GetRandomValue(0, GetScreenWidth()),
                     (float)GetRandomValue(-10, -5)};
      enemies.emplace_back(pos);
      break;
    }
    case 1: {  // South
      Vector2 pos = {
          (float)GetRandomValue(0, GetScreenWidth()),
          (float)GetRandomValue(GetScreenHeight() + 5, GetScreenHeight() + 10)};
      enemies.emplace_back(pos);
      break;
    }
    case 2: {  // West
      Vector2 pos = {(float)GetRandomValue(-10, -5),
                     (float)GetRandomValue(0, GetScreenHeight())};
      enemies.emplace_back(pos);
      break;
    }
    case 3: {  // East
      Vector2 pos = {
          (float)GetRandomValue(GetScreenWidth() + 5, GetScreenWidth() + 10),
          (float)GetRandomValue(0, GetScreenHeight())};
      enemies.emplace_back(pos);
      break;
    }
  }
}