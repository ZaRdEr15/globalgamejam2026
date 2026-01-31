#include <array>
#include <memory>
#include <raylib.h>
#include "common.h"
#include "assets.h"

std::array<std::unique_ptr<DrawableObject>, kTotalGrids> gGrids = {};
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

    Platform(Rectangle r, Vector2 p) {
        rect = r;
        pos = p;
    };

    virtual void Draw() {
        // printf("Drawing floor at (%f, %f)\n", pos.x, pos.y);
        DrawTextureRec(getTile(tiles::BLOCK), rect, pos, WHITE);
    }
    virtual bool hasCollision() {
        // printf("Drawing floor at (%f, %f)\n", pos.x, pos.y);
        return true;
    }
    virtual Rectangle getRectangle() {
        auto rect_copy = rect;
        rect_copy.x = pos.x;
        rect_copy.y = pos.y;
        return rect_copy;
    }

    Vector2 pos;
    Rectangle rect;
    tiles::TILE_TYPES type;
};

void createPlatform(int x, int y, int width) {
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
        auto floor = std::make_unique<Platform>(floor_tile, pos);

        setGridAtXY(x, gridY, std::move(floor));
        x++;
    }
}

void generateLevel() {
    SetRandomSeed((int)time(NULL));

    const int min_gap_x = 2;
    const int max_gap_x = 4;
    const int min_gap_start = 6;
    const int max_up = -14;
    const int min_down = 14;

    int current_x = min_gap_start;
    int current_y = kGridsY / 2 + GetRandomValue(max_up, min_down);

    while (current_x < kGridsX - 6) {
        while (current_y >= kGridsY - 4) {
            current_y += max_up;
        }

        while (current_y <= 0) {
            current_y += min_down;
        }

        createPlatform(current_x, current_y, 3);

        current_y += GetRandomValue(max_up, min_down);
        current_x += GetRandomValue(min_gap_x, max_gap_x);
    }
}

void createEnd() {
    const int width = 3;
    const int y = kGridsY / 2;
    const int x = kGridsX - width;

    createPlatform(x, y, 3);
};

void createFloor() {
    const int gridY = kGridsY - 1;

    createPlatform(0, gridY / 2, 3);
    createEnd();
    generateLevel();
}

const std::array<std::unique_ptr<DrawableObject>, kTotalGrids>& getGrid() {
    return gGrids;
}
