#pragma once
#include <raylib.h>

class Bullet {
  Vector2 position;
  Vector2 velocity;
  float angle;
public:
  Bullet(Vector2 worldPos, Vector2 playerPos);
  void update();
  void draw(Vector2 playerPos);
  inline Vector2 getPosition() { return position; }
};