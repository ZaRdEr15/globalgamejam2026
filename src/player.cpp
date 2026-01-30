#include <cmath>

#include "player.h"
#include <raylib.h>

constexpr float kGravity = 9.8;
constexpr float kVelocity = 500.0;
constexpr float kJumpSpeed = 5.0;

int gDirection = 0;

void movePlayer(float delta) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        gDirection = -1;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        gDirection = 1;
    } else {
        gDirection = 0;
    }
    gPlayer.x += gDirection * kVelocity * delta;

    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        gPlayer.y -= kJumpSpeed * delta;
    }
    if (gPlayer.y && !CheckCollisionRecs(gPlayer, gFloor)) {
        gPlayer.y += std::pow(kGravity, 2) *  delta;
    }
}