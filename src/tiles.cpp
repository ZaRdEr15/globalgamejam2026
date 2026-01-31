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

struct Floor : DrawableObject {

    Floor(Rectangle r, Vector2 p) {
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

void createFloor() {
    const int gridY = 10;
    for (int gridX = 0; gridX < kGridsX; gridX++) {
        const Rectangle floor_tile = {
            .x = 0,
            .y = 0,
            .width = kGridSize,
            .height = kGridSize,
        };
        Vector2 pos = {
            .x = static_cast<float>(gridX * kGridSize),
            .y = static_cast<float>(gridY * kGridSize),
        };
        auto floor = std::make_unique<Floor>(floor_tile, pos);

        setGridAtXY(gridX, gridY, std::move(floor));
    }
}

const std::array<std::unique_ptr<DrawableObject>, kTotalGrids>* getGrid() {
    return &gGrids;
}
