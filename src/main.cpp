#include "raylib.h"
#include <iostream>
#include <fstream>
#include <string>

#include "SaveSystemPlus.h" //Ali's Save System
#include "Array.h" //Ali's Custom Array
#include "CPU.h" //Zain's Hardware
#include "GPU.h" //Zain's Hardware
#include "RAM.h" //Zain's Hardware
#include "PC.h" //Zain's Assembly Logic
using namespace std;

/* ~~~ RAYLIB SYNTAX FROM WEBSITE ~~~

WINDOW & SETUP:
WindowShouldClose()                   // Returns true if player clicks the X or hits ESC
CloseWindow()                         // Safely closes the window and frees memory

IMAGES & ICONS:
LoadImage(const char *fileName)       // Loads an image file from your folder into RAM
SetWindowIcon(Image image)            // Sets the icon in the top-left of the window
UnloadImage(Image image)              // Deletes the image from RAM to save memory

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
    SetConfigFlags(FLAG_WINDOW_TRANSPARENT); 
    InitWindow(1280,720,"Rig-Builder Tycoon 🛠️");

    InitAudioDevice(); 
    Music bgm = LoadMusicStream("bgmusic.mp3");
    PlayMusicStream(bgm);
    
    Image icon = LoadImage("icon.ico"); 
    if (icon.data != NULL) SetWindowIcon(icon); 
    UnloadImage(icon);

    Font mainFont = LoadFontEx("mainfont.ttf",64,0,0);
    SetTextureFilter(mainFont.texture,TEXTURE_FILTER_POINT);

    SetTargetFPS(60);

    // CUSTOM COLOR PALETTE
    Color bgDark = {25,25,25,240}; 
    Color panelColor = {45,45,45,255}; 
    Color borderColor = {80,80,80,255}; 
    Color textLight = {240,240,240,255}; 
    Color moneyGreen = {70,200,100,255}; 
    Color bsodBlue = {0,120,215,255}; 

    //Initilize Variables
    int shopFunds=0;
    int highScore=0;

    SaveSystemPlus saveManager; 
    saveManager.loadGame(shopFunds,highScore); 
    
    //ZAIN'S HARDWARE SETUP USING ALIS TEMPLATE ARRAY
    Array<CPU*> shopCPUs;
    shopCPUs.add(new CPU("Intel Core i3 (Old)",80,20));
    shopCPUs.add(new CPU("Intel Core i5",180,40));
    shopCPUs.add(new CPU("Intel Core Ultra 9",500,120));

    Array<GPU*> shopGPUs;
    shopGPUs.add(new GPU("Intel HD Graphics",50,10));
    shopGPUs.add(new GPU("Nvidia RTX 3060",350,75));
    shopGPUs.add(new GPU("Nvidia RTX 5090",900,200));

    Array<RAM*> shopRAMs;
    shopRAMs.add(new RAM("4GB DDR3",20,10));
    shopRAMs.add(new RAM("16GB DDR4",70,30));
    shopRAMs.add(new RAM("32GB DDR5",150,60));

    bool customerWaiting=false;
    int currentBudget=0;
    int targetScore=0;

    int currentMenu = 0; 

    //CURRENT BUILD VARIABLES
    int selCPU_Idx = -1; //set to null
    int selGPU_Idx = -1;
    int selRAM_Idx = -1;
    int currentCost=0;
    int currentBaseScore=0;

    //Button Hitboxes x,y,w,h
    Rectangle btnCPU = {475,190,300,60};
    Rectangle btnGPU = {475,310,300,60};
    Rectangle btnRAM = {475,430,300,60};
    Rectangle btnBench = {870,550,340,60}; 
    Rectangle btnBack = {475,540,300,50};
    
    //ITEM HITBOXES
    Rectangle btnItem1 = {460,200,330,50};
    Rectangle btnItem2 = {460,290,330,50};
    Rectangle btnItem3 = {460,380,330,50};

    //ANIMATION & BSOD VARIABLES
    float popupTimer=0.0f;
    string popupText="";
    Color popupColor=WHITE;
    bool isBSOD = false;
    float bsodTimer = 0.0f;

    int lastAchievedScore = 0;
    int lastTargetScore = 0;
    int lastCostLost = 0;

    while (!WindowShouldClose()){
        float dt=GetFrameTime();
        if (dt>0.5f) dt=0.016f;//16ms = 60fps
        
        UpdateMusicStream(bgm);
        Vector2 mousePos=GetMousePosition();

        if (!customerWaiting){
            currentBudget = GetRandomValue(500,1600);
            targetScore = GetRandomValue(150,420);
            customerWaiting = true;
        }

        Color colorCPU = DARKBLUE;
        Color colorGPU = DARKGREEN;
        Color colorRAM = MAROON;
        Color colorBench = ORANGE;

        if (!isBSOD){
            if (currentMenu==0){
                if (CheckCollisionPointRec(mousePos,btnCPU)){
                    colorCPU = SKYBLUE; //Hover Effect
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) currentMenu=1;
                }
                if (CheckCollisionPointRec(mousePos,btnGPU)){
                    colorGPU=GREEN; 
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
                if (CheckCollisionPointRec(mousePos,btnItem1)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (currentMenu==1) selCPU_Idx=0;
                        if (currentMenu==2) selGPU_Idx=0;
                        if (currentMenu==3) selRAM_Idx=0;
                    }
                }
                if (CheckCollisionPointRec(mousePos,btnItem2)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (currentMenu==1) selCPU_Idx=1;
                        if (currentMenu==2) selGPU_Idx=1;
                        if (currentMenu==3) selRAM_Idx=1;
                    }
                }
                if (CheckCollisionPointRec(mousePos,btnItem3)){
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        if (currentMenu==1) selCPU_Idx=2;
                        if (currentMenu==2) selGPU_Idx=2;
                        if (currentMenu==3) selRAM_Idx=2;
                    }
                }
            }
            //NExt frame reset the price selected
            currentCost=0;
            currentBaseScore=0;
            //Uses Alis array to get the pointer and then that pointer for zains calc price
            if (selCPU_Idx != -1){
                currentCost += shopCPUs.get(selCPU_Idx)->getPrice();
                currentBaseScore += shopCPUs.get(selCPU_Idx)->calculatePerformance();
            }
            if (selGPU_Idx != -1){
                currentCost += shopGPUs.get(selGPU_Idx)->getPrice();
                currentBaseScore += shopGPUs.get(selGPU_Idx)->calculatePerformance();
            }
            if (selRAM_Idx != -1){
                currentCost += shopRAMs.get(selRAM_Idx)->getPrice();
                currentBaseScore += shopRAMs.get(selRAM_Idx)->calculatePerformance();
            }

            if (CheckCollisionPointRec(mousePos,btnBench)){
                colorBench = GOLD;
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    if (selCPU_Idx != -1 && selGPU_Idx != -1 && selRAM_Idx != -1){
                        
                        string cpuName = shopCPUs.get(selCPU_Idx)->getName();
                        string ramName = shopRAMs.get(selRAM_Idx)->getName();
                        string gpuName = shopGPUs.get(selGPU_Idx)->getName();
                        
                        //COMPATIBILITY CHECKS
                        bool isCompatible = true;
                        //no position (the word wasn't found).
                        if (cpuName.find("i3")!=string::npos && ramName.find("DDR5")!=string::npos){
                            popupText = "ERROR: Old i3 motherboard can't fit DDR5!";
                            isCompatible=false;
                        }
                        else if (cpuName.find("Ultra")!=string::npos && ramName.find("DDR3")!=string::npos){
                            popupText = "ERROR: Core Ultra requires DDR4 or DDR5!";
                            isCompatible=false;
                        }
                        
                        // If it fails the check, show red popup and cancel benchmark!
                        if (!isCompatible){
                            popupColor = RED;
                            popupTimer = 3.0f;
                        }
                        else{
                            CPU* rigCPU = new CPU(*shopCPUs.get(selCPU_Idx));
                            GPU* rigGPU = new GPU(*shopGPUs.get(selGPU_Idx));
                            RAM* rigRAM = new RAM(*shopRAMs.get(selRAM_Idx));
                            
                            PC currentRig;
                            currentRig.addPart(rigCPU);
                            currentRig.addPart(rigGPU);
                            currentRig.addPart(rigRAM);
                            
                            int basePerf = currentRig.calculateTotalPerformance();
                            
                            //BOTTLENECK PENALTY
                            if (gpuName.find("5090")!=string::npos && cpuName.find("i3")!=string::npos){
                                basePerf -= 50; //Huge penalty to base score
                            }
                            
                            int scoreNeeded = targetScore-basePerf;
                            if (scoreNeeded<0) scoreNeeded=0; 
                            
                            ofstream targetOut("snake_target.txt");
                            targetOut << scoreNeeded;
                            targetOut.close();
                            //Clear the file after save
                            ofstream clearBonus("snake_bonus.txt");
                            clearBonus << 0;
                            clearBonus.close();
                            
                            system("start /wait Snake_Renewed.exe"); //Runs Snake_Game
                            
                            int applesEaten=0;
                            ifstream snakeFile("snake_bonus.txt");
                            if (snakeFile.is_open()){
                                snakeFile>>applesEaten;
                                snakeFile.close();
                            }
                            
                            int totalPerf = basePerf+(applesEaten * 2);
                            
                            lastAchievedScore = totalPerf;
                            lastTargetScore = targetScore;
                            lastCostLost = currentCost;

                            //Win Condition Check
                            if (totalPerf >= targetScore && currentCost <= currentBudget){
                                int baseProfit = currentBudget - currentCost + 500;
                                
                                //BONUS MONEY
                                int extraPoints = totalPerf-targetScore;
                                int bonusMoney =0;
                                
                                if (extraPoints > 0){
                                    bonusMoney = extraPoints * 5; //$5 for every point over the target
                                }
                                
                                int totalProfit = baseProfit+bonusMoney;

                                shopFunds += totalProfit;
                                if (totalPerf > highScore) highScore=totalPerf;
                                
                                saveManager.addScore(totalPerf);
                                saveManager.saveGame(shopFunds, highScore);
                                
                                customerWaiting = false;
                                selCPU_Idx = -1; selGPU_Idx = -1; selRAM_Idx = -1;
                                
                                //SUCCESS ANIMATION
                                if (bonusMoney > 0){
                                    popupText = "+$" + to_string(totalProfit) + " ($" + to_string(bonusMoney) + " OC Bonus!)";
                                } else {
                                    popupText = "+$" + to_string(totalProfit) + " (Score: " + to_string(totalPerf) + ")";
                                }
                                popupColor = GREEN;
                                popupTimer = 4.0f;
                            }
                            else{
                                //BSOD!
                                shopFunds -= currentCost; //You lose money spent on parts
                                saveManager.saveGame(shopFunds,highScore); //Save the new money
                                
                                customerWaiting=false; //Angry customer leaves
                                selCPU_Idx = -1; selGPU_Idx = -1; selRAM_Idx = -1;
                                
                                isBSOD = true;
                                bsodTimer = 4.0f;
                            }
                        }
                        
                    }else{
                        popupText = "WARNING: Select all 3 parts!";
                        popupColor = RED;
                        popupTimer = 3.0f;
                    }
                }
            }
        }

        string displayCPU = (selCPU_Idx != -1) ? shopCPUs.get(selCPU_Idx)->getName() : "None";
        string displayGPU = (selGPU_Idx != -1) ? shopGPUs.get(selGPU_Idx)->getName() : "None";
        string displayRAM = (selRAM_Idx != -1) ? shopRAMs.get(selRAM_Idx)->getName() : "None";

        BeginDrawing();
        ClearBackground(bgDark);
        
        //PANEL 1: CUSTOMER REQUEST (Left Side)
        DrawRectangleRounded({50,60,350,600},0.05f,10,panelColor);
        DrawRectangleRoundedLines({50,60,350,600},0.05f,10,3,borderColor);
        
        DrawTextEx(mainFont,"Customer Queue",{57,80},24,1,textLight);
      
        if (customerWaiting){
            DrawTextEx(mainFont,"A customer wants a rig!",{55,160},16,1,LIGHTGRAY);
            DrawTextEx(mainFont,TextFormat("Budget: $%i",currentBudget),{58,240},21,1,moneyGreen);
            DrawTextEx(mainFont,TextFormat("Target Score: %i",targetScore),{58,320},21,1,ORANGE);
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
            DrawRectangleRounded(btnItem3,0.1f,10,DARKGRAY);
            
            if (currentMenu == 1){
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopCPUs.get(0)->getName().c_str(),shopCPUs.get(0)->getPrice()),{467,218},14,1,WHITE);
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopCPUs.get(1)->getName().c_str(),shopCPUs.get(1)->getPrice()),{485,308},14,1,WHITE);
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopCPUs.get(2)->getName().c_str(),shopCPUs.get(2)->getPrice()),{461,398},14,1,WHITE);
            }
            if (currentMenu == 2){
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopGPUs.get(0)->getName().c_str(),shopGPUs.get(0)->getPrice()),{475,218},14,1,WHITE);
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopGPUs.get(1)->getName().c_str(),shopGPUs.get(1)->getPrice()),{485,308},14,1,WHITE);
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopGPUs.get(2)->getName().c_str(),shopGPUs.get(2)->getPrice()),{485,398},14,1,WHITE);
            }
            if (currentMenu == 3){
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopRAMs.get(0)->getName().c_str(),shopRAMs.get(0)->getPrice()),{485,218},14,1,WHITE);
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopRAMs.get(1)->getName().c_str(),shopRAMs.get(1)->getPrice()),{485,308},14,1,WHITE);
                DrawTextEx(mainFont,TextFormat("%s - $%i",shopRAMs.get(2)->getName().c_str(),shopRAMs.get(2)->getPrice()),{485,398},14,1,WHITE);
            }
            
            DrawRectangleRounded(btnBack,0.1f,10,DARKGRAY);
            DrawTextEx(mainFont,"< BACK",{510,558},15,1,WHITE);
        }

        //PANEL 3: CURRENT BUILD & BENCHMARK (Right Side)
        DrawRectangleRounded({850,60,380,600},0.05f,10,panelColor);
        DrawRectangleRoundedLines({850, 60, 380, 600},0.05f,10,3,borderColor);
        
        DrawTextEx(mainFont,"Current Build",{890,80},24,1,textLight);
        
        DrawTextEx(mainFont,"CPU:",{865,150},16,1,SKYBLUE);
        DrawTextEx(mainFont,displayCPU.c_str(),{865,175},20,1,WHITE);
        
        DrawTextEx(mainFont,"GPU:",{865,235},16,1,GREEN);
        DrawTextEx(mainFont,displayGPU.c_str(),{865,260},20,1,WHITE);
        
        DrawTextEx(mainFont,"RAM:",{865,320},16,1,RED);
        DrawTextEx(mainFont,displayRAM.c_str(),{865,345},20,1,WHITE);
        
        DrawTextEx(mainFont,TextFormat("Total Cost: $%i",currentCost),{865,420},20,1,moneyGreen);
        DrawTextEx(mainFont,TextFormat("Base Score: %i",currentBaseScore),{865,455},20,1,SKYBLUE);
        
        if (customerWaiting && selCPU_Idx != -1 && selGPU_Idx != -1 && selRAM_Idx != -1){
            int needed = targetScore-currentBaseScore;
            if (needed < 0) needed = 0;
            DrawTextEx(mainFont,TextFormat("OC Needed: %i pts", needed),{865,490},20,1, (needed>0)?ORANGE:GREEN);
        }
        
        DrawRectangleRounded(btnBench,0.1f,10,colorBench);
        DrawTextEx(mainFont,"RUN BENCHMARK",{915,570},20,1,WHITE); 

        DrawTextEx(mainFont,TextFormat("Shop Funds: $%i",shopFunds),{50,680},20,1,moneyGreen);
        DrawTextEx(mainFont,TextFormat("High Score: %i",highScore),{1000,680},20,1,ORANGE);
        //Animation (.a =aplha 1.5s == 127(50% transparent))
        if (popupTimer > 0.0f){
            popupTimer -= dt;
            popupColor.a = (unsigned char)(255.0f * (popupTimer / 3.0f)); 
            DrawTextEx(mainFont, popupText.c_str(),{856,520},11,1,popupColor);
        }

        if (isBSOD){
            bsodTimer -= dt;
            DrawRectangle(0,0,1280,720,bsodBlue);
            DrawTextEx(mainFont,":(",{115,100},120,1,WHITE);
            DrawTextEx(mainFont,"Your Overclock was unstable and the PC crashed.",{115,280},26,1,WHITE);
            DrawTextEx(mainFont,"The customer stormed out angry.",{115,330},24,1,LIGHTGRAY);
            DrawTextEx(mainFont, TextFormat("Target Score Needed: %i", lastTargetScore), {115, 420}, 24, 1, WHITE);
            DrawTextEx(mainFont, TextFormat("Your Achieved Score: %i", lastAchievedScore), {115, 460}, 24, 1, RED);
            DrawTextEx(mainFont,TextFormat("PENALTY: You lost $%i on ruined parts!",lastCostLost),{115,540},28,1,RED);
            DrawTextEx(mainFont,"Rebooting shop...",{115,620},20,1,LIGHTGRAY);
            
            if (bsodTimer <= 0.0f) isBSOD = false; 
        }

        EndDrawing();
    }
    
    saveManager.saveGame(shopFunds, highScore);

    for (int i = 0; i < shopCPUs.size(); i++) delete shopCPUs.get(i);
    for (int i = 0; i < shopGPUs.size(); i++) delete shopGPUs.get(i);
    for (int i = 0; i < shopRAMs.size(); i++) delete shopRAMs.get(i);

    UnloadFont(mainFont);
    UnloadMusicStream(bgm);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}