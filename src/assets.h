#include <raylib.h>

constexpr unsigned char tileSizeHeight = 16;
constexpr unsigned char tileSizeWidth = 16;
constexpr unsigned char tilesX = 20;
constexpr unsigned char tilesY = 20;
constexpr unsigned char tilePadX = 1;
constexpr unsigned char tilePadY = 1;

namespace tiles {

enum TILE_TYPES : unsigned short {
    EMPTY = 0,
    BLOCK = 10,
};

}

void loadTileMap();
Texture2D getTile(tiles::TILE_TYPES type);
