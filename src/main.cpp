#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    // Detect window close button or ESC key 
    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Hello, world!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}