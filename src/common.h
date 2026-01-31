#pragma once

#include <raylib.h>
#include <string>

inline constexpr int screenWidth = 800;
inline constexpr int screenHeight = 640;
inline constexpr int kGridSize = 16;
inline constexpr int kGridsX = screenWidth / kGridSize;
inline constexpr int kGridsY = screenHeight / kGridSize;
inline constexpr int kTotalGrids = kGridsX * kGridsY;
inline const std::string kGameTitle = "TITLE_PLACHOLDER";

struct DrawableObject {
    virtual void Draw() = 0;
    virtual bool hasCollision() = 0;
    virtual Rectangle getRectangle() = 0;
};
