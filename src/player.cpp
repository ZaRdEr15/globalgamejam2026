#include "player.h"
#include <raylib.h>

constexpr float kSpeed = 5.0;
constexpr float kJumpSpeed = 5.0;

void movePlayer(Rectangle &rect, float delta) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        rect.x -= kSpeed;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        rect.x += kSpeed;
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        rect.y -= kJumpSpeed * delta;
    }
}