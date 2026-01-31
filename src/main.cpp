#include "raylib.h"
#include "player.h"
#include "common.h"

int main(void) {
    InitWindow(screenWidth, screenHeight, kGameTitle.c_str());
    SetTargetFPS(60);

    Player player(Vector2{ 100, 100 });

    const Rectangle floor = {
        .x = 0,
        .y = 250,
        .width = 1000,
        .height = 10,
    };

    while (!WindowShouldClose()) { // Detect window close button or ESC key
        float deltaTime = GetFrameTime();
        player.updatePosition(deltaTime, floor);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(player.collision, RED); // debug
            DrawRectangleRec(floor, BLACK);
        EndDrawing();
    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
