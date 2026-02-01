#include "common.h"
#include <memory>

namespace grid {
enum TYPE : unsigned char {
    NONE = 0,
    PLATFORM_STANDARD,
    PLATFORM_RED,
    PLATFORM_BLUE,
};
}

struct DrawableObject {
    virtual void Draw() = 0;
    virtual bool hasCollision() = 0;
    virtual Rectangle getRectangle() = 0;
    virtual grid::TYPE getType() = 0;
};

void setGridAtXY(int x, int y, std::unique_ptr<DrawableObject> obj);
void initializeGrid();
void drawGrid();
void createFloor();

const std::array<std::unique_ptr<DrawableObject>, kTotalGrids>& getGrid();
