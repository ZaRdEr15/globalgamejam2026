#include "common.h"
#include <memory>

void setGridAtXY(int x, int y, std::unique_ptr<DrawableObject> obj);
void initializeGrid();
void drawGrid();
void createFloor();
