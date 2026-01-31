#include "raylib.h"
#include "player.h"
#include "common.h"
#include "assets.h"
#include "tiles.h"

void drawHelp() {
    DrawText("W (ARROW UP) - JUMP, A/D (ARROW LEFT/ARROW RIGHT) - LEFT-RIGHT", 50, 0, 40, WHITE);
}

int main(void) {
    InitWindow(screenWidth, screenHeight, kGameTitle.c_str());
    InitAudioDevice();
    SetTargetFPS(60);
    loadTileMap();
    initializeGrid();
    printf("Grids X: %d, Grids Y: %d\n", kGridsX, kGridsY);

    Music mainTheme = LoadMusicStream("sfx/theme.mp3");
    mainTheme.looping = true;
    SetMusicVolume(mainTheme, 0.1);
    PlayMusicStream(mainTheme);

    Player player(Vector2{ 100, 0 });
    player.loadSounds();

    createFloor();

    while (!WindowShouldClose()) { // Detect window close button or ESC key
        UpdateMusicStream(mainTheme);
        float deltaTime = GetFrameTime();
        player.updatePosition(deltaTime);
        BeginDrawing();
        {
            ClearBackground(BLACK);
            // loadTileMap();
            DrawTexture(getTile(tiles::BLOCK), 20, 20, WHITE);
            drawGrid();
            player.draw();
            drawHelp();
        }
        EndDrawing();
    }
    UnloadMusicStream(mainTheme);
    CloseAudioDevice();
    CloseWindow(); // Close OpenGL context also
    return 0;
}
