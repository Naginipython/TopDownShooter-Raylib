#pragma once
#include <raylib.h>

class Player {
  Vector2 position;
  Vector2 velocity;
  float speed;

  void move();
public:
  float health;
  Player();
  void draw();
  void update();
  inline Vector2 getPosition() { return position; }
};