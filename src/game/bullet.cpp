#include "bullet.h"
#include "cmath"

Bullet::Bullet(Vector2 WorldPos, Vector2 playerPos) : position(playerPos) {
  angle = atan2(WorldPos.y - playerPos.y, WorldPos.x - playerPos.x) * (180.0f / PI);
  velocity.x = cos(angle * (PI / 180.0f)) * 15;
  velocity.y = sin(angle * (PI / 180.0f)) * 15;
}

void Bullet::update() {
  position.x += velocity.x;
  position.y += velocity.y;
}

void Bullet::draw(Vector2 playerPos) {
  // DrawCircle(position.x, position.y, radius, RED);
  DrawRectanglePro({position.x, position.y, 10, 5}, {5,2.5f}, angle, RED);
}