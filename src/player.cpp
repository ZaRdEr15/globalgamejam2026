#include "player.h"
#include "assets.h"
#include "raymath.h"
#include <raylib.h>
#include "raymath.h"
#include "tiles.h"
#include <array>

static int getInputDir() {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        return -1;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        return 1;
    } else {
        return 0;
    }
}

Player::Player() :
    pos(kRespawnPoint),
    velocity(Vector2One()), 
    canJump(true), 
    collision(Rectangle{ 0, 0, kGridSize, kGridSize }) {}

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
    static bool facingLeft = false;
    static int currentAnimationSteps = 0;
    static bool animationMove = false;
    TraceLog(LOG_DEBUG, "steps: %d", currentAnimationSteps);

    if (velocity.x < -0.1) facingLeft = true;
    if (velocity.x > 0.1) facingLeft = false;

    if (std::abs(velocity.x) > 0.1) {
        ++currentAnimationSteps;
        if (currentAnimationSteps >= kAnimationSteps) {
            currentAnimationSteps = 0;
            animationMove = !animationMove;
        }
        playerSprite = animationMove ? getTile(tiles::CHAR_MOVE) : getTile(tiles::CHAR_IDLE);
    } else {
        currentAnimationSteps = 0;
        animationMove = false;
        playerSprite = getTile(tiles::CHAR_IDLE);
    }

    if ((std::abs(velocity.y) > 0.1) && canJump) {
        playerSprite = getTile(tiles::CHAR_JUMP);
    }

    if (IsKeyPressed(KEY_Z) || IsKeyPressed(KEY_X)) {
        PlaySound(maskSound);
    }

    Rectangle source{};
    source.width = facingLeft ? -1.0 * playerSprite.width : 1.0 * playerSprite.width;
    source.height = static_cast<float>(playerSprite.height);
    DrawTextureRec(playerSprite, source, pos, WHITE);
}

void Player::updatePosition(float delta) {
    if (IsKeyPressed(KEY_R)) {
        respawn();
    }

    applyGravity(delta);

    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && canJump) {
        velocity.y -= kJumpVelocity;
        PlaySound(jumpSound);
    }
    if ((IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP)) && (velocity.y < 0)) {
        velocity.y *= 0.5;
        canJump = false;
    }

    int inputDir = getInputDir();
    if (inputDir) {
        velocity.x += inputDir * kAcceleration * delta;
        velocity.x = Clamp(velocity.x, -kMaxSpeed, kMaxSpeed);
    } else {
        playerSprite = getTile(tiles::CHAR_IDLE);
        velocity.x = Lerp(velocity.x, 0, kFriction * delta);
    }

    applyVelocityToPos(delta);
    syncCollisionRect();

    auto &grid = getGrid();
    for (const auto &tile : grid) {
        Rectangle tileRect = tile->getRectangle();
        if (CheckCollisionRecs(collision, tileRect) && (velocity.y >= 0)) {
            velocity.y = 0;
            canJump = true;
            pos.y = tileRect.y - collision.height; // no clipping, snap
        }
    }
}

void Player::respawn() {
    pos = kRespawnPoint;
    velocity = Vector2Zero();
    syncCollisionRect();
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
