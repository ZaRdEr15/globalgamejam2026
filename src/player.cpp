#include "player.h"
#include "assets.h"
#include "raymath.h"
#include <raylib.h>
#include "common.h"
#include "raylib.h"
#include "raymath.h"
#include "tiles.h"

static int getInputDir() {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        return -1;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        return 1;
    } else {
        return 0;
    }
}

Player::Player(Vector2 pos) :
    pos(pos), velocity(Vector2One()), canJump(true), collision(Rectangle{ 0, 0, 30, 30 }) {}

Player::~Player() {
    UnloadSound(jumpSound);
    UnloadSound(maskSound);
    UnloadSound(deathSound);
    UnloadSound(winSound);
}

void Player::loadSounds() {
    jumpSound = LoadSound("sfx/jump.wav");
    maskSound = LoadSound("sfx/mask.wav");
    deathSound = LoadSound("sfx/death.wav");
    winSound = LoadSound("sfx/win.wav");
}

void Player::draw() {
    DrawTexture(sprite, roundf(pos.x), roundf(pos.y), WHITE);
}

void Player::updatePosition(float delta) {
    applyGravity(delta);

    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && canJump) {
        velocity.y -= kJumpVelocity;
        PlaySound(jumpSound);
    }
    if ((IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP)) && (velocity.y < 0)) {
        velocity.y *= 0.5;
    }

    int inputDir = getInputDir();
    if (inputDir) {
        sprite = getTile(tiles::CHAR_MOVE);
        velocity.x += inputDir * kAcceleration * delta;
        velocity.x = Clamp(velocity.x, -kMaxSpeed, kMaxSpeed);
    } else {
        sprite = getTile(tiles::CHAR_IDLE);
        velocity.x = Lerp(velocity.x, 0, kFriction * delta);
    }

    applyVelocityToPos(delta);
    syncCollisionRect();

    auto grid = getGrid();
    for (const auto &tile : *grid) {
        auto tileRect = tile->getRectangle();
        printf("checking tilerect: (%f, %f)\n", tileRect.x, tileRect.y);
        if (CheckCollisionRecs(collision, tileRect) && (velocity.y >= 0)) {
            velocity.y = 0;
            canJump = true;
            pos.y = tileRect.y - collision.height; // no clipping, snap
        } else {
            canJump = false;

        }
    }
}

void Player::syncCollisionRect() {
    collision.x = pos.x;
    collision.y = pos.y;
}

float Player::getGravity() {
    return velocity.y < 0 ? kGravity : kFallGravity;
}

void Player::applyGravity(float delta) {
    velocity.y += getGravity() * delta;
}

void Player::applyVelocityToPos(float delta) {
    pos = Vector2Add(pos, Vector2Scale(velocity, delta));
}
