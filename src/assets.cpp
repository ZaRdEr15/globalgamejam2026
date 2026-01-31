#include <array>
#include <cstdio>
#include <raylib.h>
#include "assets.h"
#include "common.h"

static std::array<Texture2D, 400> gTiles{};

// Not my finest code, but it works
void loadTileMap() {
    Image data = LoadImage("assets/Tilemap/monochrome_tilemap.png");

    int imagePos = 0;
    int tileYPad = 0;
    int tileXPad = 0;

    for (int tileY = 0; tileY < tilesY; tileY++) {
        if (tileY == 0) {
            tileYPad = 0;
        } else {
            tileYPad = tilePadY;
        }
        for (int tileX = 0; tileX < tilesX; tileX++) {
            if (tileX == 0) {
                tileXPad = 0;
            } else {
                tileXPad = tilePadX;
            }
            Image tile = ImageCopy(data);
            Rectangle crop = {
                .x = static_cast<float>(tileX * (tileSizeWidth + tileXPad)),
                .y = static_cast<float>(tileY * (tileSizeHeight + tileYPad)),
                .width = tileSizeWidth,
                .height = tileSizeHeight,
            };
            ImageCrop(&tile, crop);
            printf("image size: %d, %d\n", tile.width, tile.height);
            ImageResize(&tile, kGridSize, kGridSize);
            printf("image new size: %d, %d\n", tile.width, tile.height);
            gTiles[imagePos] = LoadTextureFromImage(tile);
            // if (tileX == 1 && tileY == 0) {
            //     printf("x: %f, y: %f\n", crop.x, crop.y);
            //     // DrawTexture(getTile(static_cast<tiles::TILE_TYPES>(1)), 20, 20, WHITE);
            //     // DrawTexture(gTiles[1], 20, 20, WHITE);
            // }
            printf("x: %f, y: %f, imgagePos: %d\n", crop.x, crop.y, imagePos);
            imagePos++;
        }
    }
}

Texture2D getTile(tiles::TILE_TYPES type) {
    return gTiles[type];
}
