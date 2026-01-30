#pragma once

#include "raylib.h"
#include "common.h"

inline Rectangle gPlayer = {
    .x = 100,
    .y = 5,
    .width = 50,
    .height = 100
};

inline const Rectangle gFloor = {
    .x = screenWidth / 2,
    .y = 250,
    .width = 1000,
    .height = 10,
};

void movePlayer(float delta);