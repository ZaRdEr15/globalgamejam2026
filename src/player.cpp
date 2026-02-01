#include "player.h"
#include "assets.h"
#include "common.h"
#include "raymath.h"
#include <memory>
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
    collision(Rectangle{ 0, 0, kGridSize, kGridSize }),
    mask(NONE) {}

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
    // TraceLog(LOG_DEBUG, "steps: %d", currentAnimationSteps);

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

    if (IsKeyPressed(KEY_Z)) {
        PlaySound(maskSound);
        mask = BLUE_MASK;
    }
    else if (IsKeyPressed(KEY_X)) {
        PlaySound(maskSound);
        mask = RED_MASK;
    }

    Rectangle source{};
    source.width = facingLeft ? -1.0 * playerSprite.width : 1.0 * playerSprite.width;
    source.height = static_cast<float>(playerSprite.height);

    // We need an actual mask here!
    auto color = WHITE;
    if (mask == BLUE_MASK) {
        color = BLUE;
    } else if (mask == RED_MASK) {
        color = RED;
    }
    DrawTextureRec(playerSprite, source, pos, color);
}

void Player::updatePosition(float delta) {
    if (IsKeyPressed(KEY_R)) {
        respawn();
    }

    applyGravity(delta);

    if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && canJump) {
        if (velocity.y > 0) {
            velocity.y = 0;
        }
        velocity.y -= kJumpVelocity;
        canJump = false;
        PlaySound(jumpSound);
    }
    if ((IsKeyReleased(KEY_W) || IsKeyReleased(KEY_UP)) && (velocity.y < 0)) {
        velocity.y *= 0.5;
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

    const std::array<std::unique_ptr<DrawableObject>, kTotalGrids> &grid = getGrid();
    for (const auto &tile : grid) {
        Rectangle tileRect = tile->getRectangle();
        if (CheckCollisionRecs(collision, tileRect) && (velocity.y >= 0)) {
            auto type = tile->getType();
            if (type == grid::PLATFORM_BLUE || type == grid::PLATFORM_RED) {
                velocity.y = 0;
                velocity.y -= kJumpVelocity;
                PlaySound(jumpSound);

                if (type == grid::PLATFORM_BLUE && mask == BLUE_MASK) {
                    canJump = true;
                }

                if (type == grid::PLATFORM_RED && mask == RED_MASK) {
                    velocity.y -= kJumpVelocity * 0.55;
                }
            } else {
                velocity.y = 0;
                canJump = true;
            }
            pos.y = tileRect.y - collision.height; // no clipping, snap
        }
    }

    if (pos.y > kGridsY * kGridSize) {
        pos = kRespawnPoint;
    }
}

Vector2 Player::getPoition() {
    return pos;
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
