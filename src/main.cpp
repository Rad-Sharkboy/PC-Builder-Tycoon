#include "raylib.h"

int main() {
    InitWindow(1280, 720, "RigBuilder Tycoon");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("RigBuilder Tycoon Environment is Setup!", 350, 340, 30, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}