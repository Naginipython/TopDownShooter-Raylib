#include "player.h"
#include "main.h"

Player::Player() : position({0, 0}), velocity({0, 0}), speed(5.0f), health(3.0f) {}

void Player::draw() {
  DrawCircle(position.x, position.y, 25, BLUE);
}

void Player::update() {
  move();
}

void Player::move() {
  if (IsKeyDown(KEY_A)) velocity.x = -speed;
  else if (IsKeyDown(KEY_D)) velocity.x = speed;
  else velocity.x = 0;
  if (IsKeyDown(KEY_W)) velocity.y = -speed;
  else if (IsKeyDown(KEY_S)) velocity.y = speed;
  else velocity.y = 0;

  position.x += velocity.x;
  position.y += velocity.y;
}