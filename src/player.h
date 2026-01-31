#pragma once

#include "raylib.h"

struct Player {
    // Player movement constants
    static constexpr float kMaxSpeed = 320.0;
    static constexpr float kAcceleration = 320.0;
    static constexpr float kFriction = 15.0;
    static constexpr float kGravity = 1000;
    static constexpr float kFallGravity = 2000;
    static constexpr float kJumpVelocity = 500.0;

    Vector2 pos;
    Vector2 velocity;
    bool canJump;
    Rectangle collision;
    Texture2D sprite;

    Sound jumpSound;
    Sound maskSound;
    Sound deathSound;
    Sound winSound;

    Player(Vector2 pos);
    ~Player();
    void loadSounds();
    void draw();
    void updatePosition(float delta, Rectangle floorCollisionRect);
    void syncCollisionRect();
    float getGravity();
    void applyGravity(float delta);
    void applyVelocityToPos(float delta);
};
