#include "game.h"

#include "main.h"

Game::Game() : shootTimer(0.0f) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Shooter");
  MaximizeWindow();
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
  // Player
  player.update();
  camera.target = player.getPosition();
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

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
}

void Game::draw() {
  BeginDrawing();
  ClearBackground(DARKGRAY);

  BeginMode2D(camera);
  DrawRectangle(0, 0, 200, 200, RED);

  for (Bullet& bullet : bullets) {
    bullet.draw(player.getPosition());
  }

  player.draw();
  EndMode2D();

  // Menu

  EndDrawing();
}

void Game::playerShoot() {
  shootTimer += GetFrameTime();
  if (shootTimer >= 0.5f) {  // 0.5s cooldown
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      Vector2 screenPos = {(float)GetMouseX(), (float)GetMouseY()};
      Vector2 worldPos = GetScreenToWorld2D(screenPos, camera);
      bullets.push_back(Bullet(worldPos, player.getPosition()));
      shootTimer = 0.0f;
    }
  }
}