#pragma once

#include <string>

inline constexpr int screenWidth = 1000;
inline constexpr int screenHeight = 650;
inline constexpr int kGridSize = 30;
inline constexpr int kGridsX = screenWidth / kGridSize;
inline constexpr int kGridsY = screenHeight / kGridSize;
inline constexpr int kTotalGrids = kGridsX * kGridsY;
inline const std::string kGameTitle = "TITLE_PLACHOLDER";

struct DrawableObject {
    virtual void Draw() = 0;
};
