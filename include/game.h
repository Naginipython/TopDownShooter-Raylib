#pragma once
#include <raylib.h>
#include <vector>
#include "bullet.h"
#include "player.h"
#include "enemy.h"

class Game {
  // Objects
  Camera2D camera;
  Player player;
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;

  // Timers
  float shootTimer;
  float shootCooldown;
  float healthTimer;
  float healthCooldown;

  void draw();
  void update();
  void playerShoot();
  void createEnemies();
public:
  Game();
  ~Game();
  void run();
};