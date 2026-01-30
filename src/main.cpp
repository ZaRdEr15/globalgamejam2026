#include <string>

#include "raylib.h"
#include "player.h"
#include "common.h"

int main(void) {
    const std::string kGameTitle = "TITLE_PLACHOLDER";

    InitWindow(screenWidth, screenHeight, kGameTitle.c_str());
    SetTargetFPS(60);
    while (!WindowShouldClose()) { // Detect window close button or ESC key
        float delta = GetFrameTime();
        movePlayer(delta);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(gPlayer, RED);
            DrawRectangleRec(gFloor, BLACK);
            DrawText("Hello, world!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
