#include "raylib.h"
#include "player.h"
#include "common.h"
#include "assets.h"
#include "tiles.h"

void drawHelp() {
    constexpr int kHelpXOffset = 50;
    constexpr int kFontSize = 20;
    DrawText("W (ARROW UP) - JUMP", kHelpXOffset, 0, kFontSize, WHITE);
    DrawText("A/D (ARROW LEFT/ARROW RIGHT) - LEFT-RIGHT", kHelpXOffset, 30, kFontSize, WHITE);
    // ADD EXPLANATION ON Z, X KEYS!
}

int main(void) {
    SetTraceLogLevel(LOG_DEBUG);
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

    Player player{};
    Vector2 player_pos = player.getPoition();
    Camera2D camera{
        .offset =  {screenWidth / 2.0f, screenHeight / 2.0f},// {screenWidth / 2.0f, screenHeight / 2.0f},
        .target = {player_pos.x + 20.0f, player_pos.y + 20.0f},
        .rotation = 0.0,
        .zoom = 1.0,
    };

    player.loadSounds();

    createFloor();

    while (!WindowShouldClose()) { // Detect window close button or ESC key
        UpdateMusicStream(mainTheme);
        float deltaTime = GetFrameTime();
        player.updatePosition(deltaTime);
        camera.target = player.getPoition();
        camera.target.x += 20.0f;
        camera.target.y += 20.0f;
        BeginDrawing();
        {
            BeginMode2D(camera);
            ClearBackground(BLACK);
            // loadTileMap();
            DrawTexture(getTile(tiles::BLOCK), 20, 20, WHITE);
            drawGrid();
            player.draw();
            EndMode2D();
            drawHelp();
        }
        EndDrawing();
    }
    UnloadMusicStream(mainTheme);
    CloseAudioDevice();
    CloseWindow(); // Close OpenGL context also
    return 0;
}
