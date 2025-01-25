#pragma once
#include <raylib.h>
#include <vector>
#include "player.h"

class Game {
  Camera2D camera;
  Player player;
  std::vector<Bullet> bullets;
  float shootTimer;

  void draw();
  void update();
  void playerShoot();
public:
  Game();
  ~Game();
  void run();
};