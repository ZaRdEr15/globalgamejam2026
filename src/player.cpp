#include "player.h"
#include "raylib.h"
#include "raymath.h"

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

void Player::updatePosition(float delta, Rectangle floor) {
    applyGravity(delta);

    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && canJump) {
        velocity.y -= kJumpVelocity;
    }
    if ((IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP)) && (velocity.y < 0)) {
        velocity.y *= 0.5;
    }

    int inputDir = getInputDir();
    if (inputDir) {
        velocity.x += inputDir * kAcceleration * delta;
        velocity.x = Clamp(velocity.x, -kMaxSpeed, kMaxSpeed);
    } else {
        velocity.x = Lerp(velocity.x, 0, kFriction * delta);
    }

    applyVelocityToPos(delta);
    syncCollisionRect();

    if (CheckCollisionRecs(collision, floor) && (velocity.y >= 0)) {
        velocity.y = 0;
        canJump = true;
        pos.y = floor.y - collision.height; // no clipping, snap
    } else {
        canJump = false;
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
