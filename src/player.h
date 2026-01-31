#pragma once

#include "raylib.h"
#include "common.h"

struct Player {
    static constexpr float kMaxSpeed = 320.0;
    static constexpr float kAcceleration = 320.0;
    static constexpr float kFriction = 8.0;
    static constexpr float kGravity = 1000;
    static constexpr float kFallGravity = 2000;
    static constexpr float kJumpVelocity = 500.0;

    Vector2 pos;
    Vector2 velocity;
    bool canJump;
    Rectangle collision;

    Player(Vector2 pos);
    void updatePosition(float delta, Rectangle floorCollisionRect);
    void syncCollisionRect();
    float getGravity();
    void applyGravity(float delta);
    void applyVelocityToPos(float delta);
};