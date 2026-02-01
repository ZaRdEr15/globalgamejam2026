#pragma once

#include "common.h"
#include "raylib.h"
#include <raymath.h>

struct Player {
    // Player movement constants
    static constexpr float kMaxSpeed = 320.0;
    static constexpr float kAcceleration = 320.0;
    static constexpr float kFriction = 15.0;
    static constexpr float kGravity = 1000;
    static constexpr float kFallGravity = 2000;
    static constexpr float kJumpVelocity = 500.0;

    static constexpr int kAnimationSteps = 10;

    enum MASK : unsigned short {
        NONE,
        RED_MASK,
        BLUE_MASK,
    };

    const Vector2 kRespawnPoint = { 1, kGridsY - 2 };

    Vector2 pos;
    Vector2 velocity;
    bool canJump;
    Rectangle collision;
    MASK mask;
    Texture2D playerSprite;
    Texture2D maskSprite;

    Sound jumpSound;
    Sound maskSound;
    Sound deathSound;
    Sound winSound;

    Player();
    ~Player();
    void loadSounds();
    void draw();
    void updatePosition(float delta);
    Vector2 getPoition();
    void respawn();
    void syncCollisionRect();
    float getGravity();
    void applyGravity(float delta);
    void applyVelocityToPos(float delta);
};
