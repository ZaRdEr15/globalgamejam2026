#pragma once

#include "raylib.h"
#include "common.h"

inline Rectangle gPlayer = {
    .x = screenWidth / 2,
    .y = screenHeight / 2,
    .width = screenWidth / 10,
    .height = screenHeight / 10
};

void movePlayer(Rectangle &rect, float delta);