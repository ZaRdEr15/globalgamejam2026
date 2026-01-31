#include "raylib.h"
#include "player.h"
#include "common.h"
#include "assets.h"
#include "tiles.h"

int main(void) {
    InitWindow(screenWidth, screenHeight, kGameTitle.c_str());
    InitAudioDevice();
    SetTargetFPS(60);
    loadTileMap();
    initializeGrid();

    Music mainTheme = LoadMusicStream("sfx/theme.mp3");
    mainTheme.looping = true;
    SetMusicVolume(mainTheme, 0.1);
    PlayMusicStream(mainTheme);

    Player player(Vector2{ 100, 0 });
    player.loadSounds();

    const Rectangle floor = {
        .x = 0,
        .y = 250,
        .width = 1000,
        .height = 10,
    };

    createFloor();

    while (!WindowShouldClose()) { // Detect window close button or ESC key
        UpdateMusicStream(mainTheme);
        float deltaTime = GetFrameTime();
        player.updatePosition(deltaTime, floor);
        BeginDrawing();
        {
            ClearBackground(BLACK);
            // loadTileMap();
            DrawTexture(getTile(tiles::BLOCK), 20, 20, WHITE);
            // DrawRectangleRec(floor, WHITE);
            drawGrid();
            DrawRectangleRec(player.collision, RED); // debug
        }
        EndDrawing();
    }
    UnloadMusicStream(mainTheme);
    CloseAudioDevice();
    CloseWindow(); // Close OpenGL context also
    return 0;
}
