#include <array>
#include <memory>
#include <raylib.h>
#include "common.h"
#include "assets.h"
#include "tiles.h"

static std::array<std::unique_ptr<DrawableObject>, kTotalGrids> gGrids = {};
void setGridAtXY(int x, int y, std::unique_ptr<DrawableObject> obj) {
    gGrids[(y * kGridsX) + x] = std::move(obj);
}

struct Empty : DrawableObject {
    Empty(Vector2 p) {
        rec = Rectangle{
            .x = 0,
            .y = 0,
            .width = kGridSize,
            .height = kGridSize,
        };
        pos = p;
    }
    Rectangle rec;
    Vector2 pos;
    virtual void Draw() {
        // printf("Drawing empty at (%f, %f)\n", pos.x, pos.y);
        DrawTextureRec(getTile(tiles::EMPTY), rec, pos, WHITE);
    }
    virtual bool hasCollision() {
        return false;
    }

    virtual grid::TYPE getType() {
        return grid::NONE;
    }

    virtual Rectangle getRectangle() {
        return {0, 0, 0, 0};
    }
};

void initializeGrid() {
    for (int gridY = 0; gridY < kGridsY; gridY++) {
        for (int gridX = 0; gridX < kGridsX; gridX++) {
            Vector2 pos = {
                .x = static_cast<float>(gridX * kGridSize),
                .y = static_cast<float>(gridY * kGridSize),
            };
            setGridAtXY(gridX, gridY, std::make_unique<Empty>(pos));
        }
    }
}

void drawGrid() {
    for (auto &grid : gGrids) {
        grid->Draw();
    }
}

struct Platform : DrawableObject {

    Platform(Rectangle r, Vector2 p, grid::TYPE t = grid::PLATFORM_STANDARD) {
        rect = r;
        pos = p;
        type = t;
    };

    virtual void Draw() {
        // printf("Drawing floor at (%f, %f)\n", pos.x, pos.y);
        auto color = WHITE;
        if (type == grid::PLATFORM_RED) {
            color = RED;
        } else if (type == grid::PLATFORM_BLUE) {
            color = BLUE;
        }
        DrawTextureRec(getTile(tiles::BLOCK), rect, pos, color);
    }
    virtual bool hasCollision() {
        // printf("Drawing floor at (%f, %f)\n", pos.x, pos.y);
        return true;
    }

    virtual grid::TYPE getType() {
        return type;
    }

    virtual Rectangle getRectangle() {
        auto rect_copy = rect;
        rect_copy.x = pos.x;
        rect_copy.y = pos.y;
        return rect_copy;
    }

    Vector2 pos;
    Rectangle rect;
    grid::TYPE type;
};

void createPlatform(int x, int y, int width, grid::TYPE type = grid::PLATFORM_STANDARD) {
    const int gridY = y;
    for (int i = 0; i < width; i++) {
        const Rectangle floor_tile = {
            .x = 0,
            .y = 0,
            .width = kGridSize,
            .height = kGridSize,
        };
        Vector2 pos = {
            .x = static_cast<float>(x * kGridSize),
            .y = static_cast<float>(gridY * kGridSize),
        };
        auto floor = std::make_unique<Platform>(floor_tile, pos, type);

        setGridAtXY(x, gridY, std::move(floor));
        x++;
    }
}

void createEnd(const int y) {
    const int width = 3;
    const int x = kGridsX - width;

    createPlatform(x, y, 3);
};

void generateLevel() {
    SetRandomSeed((int)time(NULL));

    const int min_gap_x = 8;
    const int max_gap_x = 12;
    const int min_gap_start = 6;
    const int max_up = -7;
    const int min_down = 7;

    int current_x = min_gap_start;
    int current_y = kGridsY / 2 + GetRandomValue(max_up, min_down);
    bool type_is_blue = true;

    while (current_x < kGridsX - 6) {
        while (current_y >= kGridsY - 4) {
            current_y += max_up;
        }

        while (current_y <= 0) {
            current_y += min_down;
        }

        auto type = grid::PLATFORM_BLUE;
        if (!type_is_blue) {
            type = grid::PLATFORM_RED;
        }
        createPlatform(current_x, current_y, 3, type);
        type_is_blue = !type_is_blue;

        current_y += GetRandomValue(max_up, min_down);
        current_x += GetRandomValue(min_gap_x, max_gap_x);
    }
    current_y += GetRandomValue(max_up, min_down);
    createEnd(current_y);
}

void createFloor() {
    const int gridY = kGridsY - 1;

    createPlatform(0, gridY / 2, 3);
    generateLevel();
}

const std::array<std::unique_ptr<DrawableObject>, kTotalGrids>& getGrid() {
    return gGrids;
}
