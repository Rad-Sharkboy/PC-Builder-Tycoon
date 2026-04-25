#include "raylib.h"
#include <iostream>
using namespace std;
/* --- RAYLIB SYNTAX FROM WEBSITE ---

WINDOW & SETUP:
WindowShouldClose()                                   // Returns true if player clicks the X or hits ESC
CloseWindow()                                         // Safely closes the window and frees memory

IMAGES & ICONS:
LoadImage(const char *fileName)                       // Loads an image file from your folder into RAM
SetWindowIcon(Image image)                            // Sets the icon in the top-left of the window
UnloadImage(Image image)                              // Deletes the image from RAM to save memory


SHAPES & TEXT:
DrawText(const char *text, int posX, int posY, int fontSize, Color color)

DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color)
  -> Rectangle rec = {x, y, width, height}
  -> roundness = 0.0f (sharp edges) up to 1.0f (full circle)
  -> segments = how smooth the curves are {10 is good for most cases}

DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, float lineThick, Color color)
  -> lineThick = how thick the border line is in pixels

DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint)
  -> position = {x, y}
  -> spacing = space between letters

CUSTOM COLORS:
Color myColor = {R, G, B, Alpha} 
  -> Red, Green, Blue, and Alpha (transparency). Values go 0-255.
*/

int main(){
    //Initialize the window
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT); //Make the window background transparent.
    InitWindow(1280,720,"Rig-Builder Tycoon 🛠️");
    
    Image icon = LoadImage("icon.ico"); 
    if (icon.data != NULL) SetWindowIcon(icon); 
    UnloadImage(icon);

    Font mainFont = LoadFontEx("mainfont.ttf",64,0,0);
    SetTextureFilter(mainFont.texture, TEXTURE_FILTER_POINT);

    SetTargetFPS(60);

    // CUSTOM COLOR PALETTE
    Color bgDark = {25,25,25,240}; //background
    Color panelColor = {45,45,45,255}; //lighter gray for the panels
    Color borderColor = {80,80,80,255}; //Clean border -offgrey
    Color textLight = {240,240,240,255}; //Off-white for main headers
    Color moneyGreen = {70,200,100,255}; //Bright green for MONEY!!!

    //Initilize Variables
    int shopFunds=0;
    int highScore=0;
    
    bool customerWaiting=false;
    int currentBudget=0;
    int targetScore=0;

    int currentMenu = 0; //0=Main Categories, 1=CPUs, 2=GPUs, 3=RAM

    //CURRENT BUILD VARIABLES
    const char* selectedCPU = "None";
    const char* selectedGPU = "None";
    const char* selectedRAM = "None";
    int currentCost=0;

    //BUTTON HITBOXES
    Rectangle btnCPU = {475,190,300,60};
    Rectangle btnGPU = {475,310,300,60};
    Rectangle btnRAM = {475,430,300,60};
    Rectangle btnBench = {870,550,340,60}; 
    Rectangle btnBack = {475,540,300,50};
    
    //ITEM HITBOXES
    Rectangle btnItem1 = {460,200,330,50};
    Rectangle btnItem2 = {460,290,330,50};

    while (!WindowShouldClose()){
        Vector2 mousePos=GetMousePosition();

        //Generate customer if queue is empty
        if (!customerWaiting){
            currentBudget = GetRandomValue(600,2500); 
            targetScore = GetRandomValue(50,150); 
            customerWaiting = true;
        }

        //Default Button Colors
        Color colorCPU = DARKBLUE;
        Color colorGPU = DARKGREEN;
        Color colorRAM = MAROON;
        Color colorBench = ORANGE;

        //Hover & Click Detection with Menu Logic
        if (currentMenu == 0){
            if (CheckCollisionPointRec(mousePos,btnCPU)){
                colorCPU = SKYBLUE; 
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentMenu=1; 
            }
            if (CheckCollisionPointRec(mousePos,btnGPU)){
                colorGPU = GREEN; 
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentMenu=2; 
            }
            if (CheckCollisionPointRec(mousePos,btnRAM)){
                colorRAM = RED; 
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentMenu=3; 
            }
        }
        else{
            if (CheckCollisionPointRec(mousePos,btnBack)){
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentMenu=0; 
            }
            //Item Clicks
            if (CheckCollisionPointRec(mousePos,btnItem1)){
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    if (currentMenu==1) { selectedCPU="Intel core i5"; currentCost+=180; }
                    if (currentMenu==2) { selectedGPU="Nvidia GTX 1650"; currentCost+=150; }
                    if (currentMenu==3) { selectedRAM="8GB DDR4"; currentCost+=40; }
                }
            }
            if (CheckCollisionPointRec(mousePos,btnItem2)){
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    if (currentMenu==1) { selectedCPU="AMD Ryzen 7"; currentCost+=300; }
                    if (currentMenu==2) { selectedGPU="Nvidia RTX 3060"; currentCost+=350; }
                    if (currentMenu==3) { selectedRAM="16GB DDR5"; currentCost+=90; }
                }
            }
        }
        
        if (CheckCollisionPointRec(mousePos,btnBench)){
            colorBench = GOLD;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) cout<<"BENCHMARK TRIGGERED!\n";
        }

        BeginDrawing();
        ClearBackground(bgDark);
        
        //PANEL 1: CUSTOMER REQUEST (Left Side)
        DrawRectangleRounded({50,60,350,600},0.05f,10,panelColor);
        DrawRectangleRoundedLines({50,60,350,600},0.05f,10,3,borderColor);
        
        DrawTextEx(mainFont,"Customer Queue",{56,80},24,1,textLight);
      
        if (customerWaiting){
            DrawTextEx(mainFont,"A customer wants a rig!",{55,160},16,1,LIGHTGRAY);

            DrawTextEx(mainFont,TextFormat("Budget: $%i",currentBudget),{60,240},24,1,moneyGreen);
            DrawTextEx(mainFont,TextFormat("Target Score: %i",targetScore),{60,320},24,1,ORANGE);
        }
        else{
            DrawTextEx(mainFont,"Waiting for customer...",{55,160},16,1,LIGHTGRAY);
        }

        //PANEL 2: SHOP INVENTORY (Middle)
        DrawRectangleRounded({450,60,350,600},0.05f,10,panelColor);
        DrawRectangleRoundedLines({450,60,350,600},0.05f,10,3,borderColor);
        
        if (currentMenu == 0){
            DrawTextEx(mainFont,"Shop Inventory",{461,80},24,1,textLight);
            
            DrawRectangleRounded(btnCPU,0.1f,10,colorCPU);
            DrawTextEx(mainFont,"1. CPU",{510,212},16,1,WHITE);
            
            DrawRectangleRounded(btnGPU,0.1f,10,colorGPU);
            DrawTextEx(mainFont,"2. GPU",{510,332},16,1,WHITE);
            
            DrawRectangleRounded(btnRAM,0.1f,10,colorRAM);
            DrawTextEx(mainFont,"3. RAM",{510,452},16,1,WHITE);
        }
        else{
            if (currentMenu == 1) DrawTextEx(mainFont,"~~ CPU LIST ~~",{463,80},24,1,SKYBLUE);
            if (currentMenu == 2) DrawTextEx(mainFont,"~~ GPU LIST ~~",{463,80},24,1,GREEN);
            if (currentMenu == 3) DrawTextEx(mainFont,"~~ RAM LIST ~~",{462,80},24,1,RED);
            
            DrawRectangleRounded(btnItem1,0.1f,10,DARKGRAY);
            DrawRectangleRounded(btnItem2,0.1f,10,DARKGRAY);
            
            if (currentMenu == 1){
                DrawTextEx(mainFont,"Intel i5 - $180",{490,218},16,1,WHITE);
                DrawTextEx(mainFont,"AMD Ryzen 7 - $300",{490,308},16,1,WHITE);
            }
            if (currentMenu == 2){
                DrawTextEx(mainFont,"GTX 1650 - $150",{490,218},16,1,WHITE);
                DrawTextEx(mainFont,"RTX 3060 - $350",{490,308},16,1,WHITE);
            }
            if (currentMenu == 3){
                DrawTextEx(mainFont,"8GB DDR4 - $40",{490,218},16,1,WHITE);
                DrawTextEx(mainFont,"16GB DDR5 - $90",{490,308},16,1,WHITE);
            }
            
            DrawRectangleRounded(btnBack,0.1f,10,DARKGRAY);
            DrawTextEx(mainFont,"< BACK",{510,558},16,1,WHITE);
        }

        //PANEL 3: CURRENT BUILD & BENCHMARK (Right Side)
        DrawRectangleRounded({850,60,380,600},0.05f,10,panelColor);
        DrawRectangleRoundedLines({850, 60, 380, 600},0.05f,10,3,borderColor);
        
        DrawTextEx(mainFont,"Current Build",{890,80},24,1,textLight);
        
        DrawTextEx(mainFont,"CPU:",{865,150},16,1,SKYBLUE);
        DrawTextEx(mainFont,selectedCPU,{865,175},20,1,WHITE);
        
        DrawTextEx(mainFont,"GPU:",{865,235},16,1,GREEN);
        DrawTextEx(mainFont,selectedGPU,{865,260},20,1,WHITE);
        
        DrawTextEx(mainFont,"RAM:",{865,320},16,1,RED);
        DrawTextEx(mainFont,selectedRAM,{865,345},20,1,WHITE);
        
        DrawTextEx(mainFont,TextFormat("Total: $%i",currentCost),{865,450},24,1,moneyGreen);
        
        DrawRectangleRounded(btnBench,0.1f,10,colorBench);
        DrawTextEx(mainFont,"RUN BENCHMARK",{915,570},20,1,WHITE); 

        DrawTextEx(mainFont,TextFormat("Shop Funds: $%i",shopFunds),{50,680},20,1,moneyGreen);
        DrawTextEx(mainFont,TextFormat("High Score: %i",highScore),{1000,680},20,1,ORANGE);

        EndDrawing();
    }
    UnloadFont(mainFont);
    CloseWindow();
    return 0;
}