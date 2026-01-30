#include "raylib.h"


constexpr float PLAYER_SPEED = 5;

void moveRectPlayer(Rectangle &rect) {
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        rect.x -= PLAYER_SPEED;
    } else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        rect.x += PLAYER_SPEED;
    }
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    Rectangle rect = {
        .x = screenWidth / 2,
        .y = screenHeight / 2,
        .width = screenWidth / 10,
        .height = screenHeight / 10
    };

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);

    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        moveRectPlayer(rect);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(rect, RED);
            DrawText("Hello, world!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }
    CloseWindow(); // Close window and OpenGL context
    return 0;
}
