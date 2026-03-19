#include "raylib.h"
#include <iostream>
using namespace std;

int main(){
    // Initialize the window with a custom width, height, and an emoji title
    InitWindow(1280,720,"🖥️ RigBuilder Tycoon 🛠️");
    
    // Load the Icon Image File and set it as the window icon,then unload the image from memory
    Image icon = LoadImage("icon.png"); 
    SetWindowIcon(icon); 
    UnloadImage(icon); 

    // Lock the game to run at a smooth 60 FPS
    SetTargetFPS(60);


    // Keep running the game loop until the user presses the X button or hits ESC
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // Draw some text in the middle of the screen to prove it works
        DrawText("RigBuilder Tycoon Environment is Setup!",350,340,30,DARKGRAY);
        
        EndDrawing();
    }

    // Safely close the window and clean up any leftover background resources
    CloseWindow();
    return 0;
}