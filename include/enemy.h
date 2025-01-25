#pragma once
#include <raylib.h>

class Enemy {
  Vector2 position;
  Vector2 velocity;
  float angle;
public:
  Enemy(Vector2 pos);
};