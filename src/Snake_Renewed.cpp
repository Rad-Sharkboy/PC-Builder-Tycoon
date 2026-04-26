#include <stdio.h>
#include <windows.h> //To set console font style consistant
#include <stdlib.h>
#include <time.h> //For random Function
#include <conio.h> //To read w,a,s,d
#include <ctype.h> //for tolower()
#include <string.h> //for string compare

int targetScore = 0;

#define WIDTH 70
#define HEIGHT 25
#define MAX_LENGTH 500 //change later on

#define FOOD '*' //$$(BUG: cant set any other ascii symbol because of border)$$
#define HEAD '@'
#define BODY 'o'

int SnakeX[MAX_LENGTH];
int SnakeY[MAX_LENGTH];

int snakeLength = 3;
int direction; // 0=N,1=E,2=S,3=W

int FoodX;
int FoodY;

int score = 0;
char player_Name[50] = {0};
int highScore = 0;
int Speed = 320;

void generateFood(void){
    int collide;
    do 
    {
        FoodX = rand() % (WIDTH - 4) + 2; //Have to avoid food spawn on border (x=axis)
        FoodY = rand() % (HEIGHT - 4) + 2; //Have to avoid food spawn on border (y-axix)
        collide = 0;
        for (int i = 0;i < snakeLength;i++) {
            if (FoodX == SnakeX[i] && FoodY == SnakeY[i]) {
                collide = 1;
                break;
            }
        }
    } while (collide == 1);
}
//Used STack Overflow for this function(to hide cursor)
void GoToXY(int x,int y) {
    COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void draw(void){
    GoToXY(0, 0); //Flicker free game
    for (int row=0;row < HEIGHT;row++) {
        for (int col=0;col < WIDTH;col++) {
            if (row == 0 && col == 0) printf("╔");
            else if (row == 0 && col == WIDTH - 1) printf("╗");
            else if (row == HEIGHT - 1 && col == 0) printf("╚");
            else if (row == HEIGHT - 1 && col == WIDTH - 1) printf("╝");
            else if (row == 0 || row == HEIGHT - 1) printf("═");
            else if (col == 0 || col == WIDTH - 1) printf("║");
            else if (row == FoodY && col == FoodX) printf("%c", FOOD);
            else 
            {
                int printed = 0;
                for (int i = 0;i < snakeLength;i++){
                    if (row == SnakeY[i] && col == SnakeX[i]){
                        if (i == 0) printf("%c",HEAD);
                        else printf("%c",BODY);
                        printed = 1;
                        break;
                    }
                }
                if (!printed) printf(" ");
            }
        }
        printf("\n");
    }
    // printf("Player: %s\t Score: %d\t Previous High Score: %d\n",player_Name,score,highScore);
    printf("Player: %s\t Previous High Score: %d\n", player_Name, highScore);
    printf("TARGET OVERCLOCK: %d pts\t CURRENT OC: %d pts\n", targetScore, score * 2);
}

void MoveSnake(void){ 
    if (_kbhit()){
        char key = _getch(); //Reads pressed key
        if ((key == 'w' || key == 'W') && direction != 2) direction = 0; // UP also checks if snake going down and press W so cant directly go up
        else if ((key == 'a' || key == 'A') && direction != 1) direction = 3; // LEFT
        else if ((key == 's' || key == 'S') && direction != 0) direction = 2; // DOWN
        else if ((key == 'd' || key == 'D') && direction != 3) direction = 1; // RIGHT
    }
    for (int i = snakeLength - 1; i > 0; i--) 
    {
        SnakeX[i] = SnakeX[i - 1];
        SnakeY[i] = SnakeY[i - 1];
    }
    if (direction == 0)       // UP update
        SnakeY[0]--;
    else if (direction == 1)  // RIGHT update
        SnakeX[0]++;
    else if (direction == 2)  // DOWN update
        SnakeY[0]++;
    else if (direction == 3)  // LEFT update
        SnakeX[0]--;
}

int CheckCollision(void)  //RETURNS 0/1 for "IF" in MAIN
{
    if (SnakeX[0] <= 0 || SnakeX[0] >= WIDTH - 1 ||
        SnakeY[0] <= 0 || SnakeY[0] >= HEIGHT - 1)
        return 1;
    for (int i = 1; i < snakeLength; i++)
        if (SnakeX[0] == SnakeX[i] && SnakeY[0] == SnakeY[i])
            return 1;
    return 0;
}

void CheckFood(void){
    if (SnakeX[0] == FoodX && SnakeY[0] == FoodY){
        score = score + 10;
        if (snakeLength < MAX_LENGTH - 1) snakeLength++; //Prevent buffer overflow
        generateFood();
        
    }
    if (score >= 50 && score < 100) Speed = 300;
    else if (score >= 100 && score < 150) Speed = 270;
    else if (score >= 150 && score < 200) Speed = 240;
    else if (score >= 200 && score < 250) Speed = 210;
    else if (score >= 250 && score < 300) Speed = 180;
    else if (score >= 300) Speed = 150;
}
int main(void)
{ //For Rig-Builder
    targetScore = 0;
    FILE *targetFile = fopen("snake_target.txt", "r");
    if (targetFile != NULL) {
        fscanf(targetFile, "%d", &targetScore);
        fclose(targetFile);
    }

    SetConsoleOutputCP(65001); //for font/visualization
    //Code taken from Stack Overflow to hide blinking cursor:
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    //
    srand((unsigned)time(NULL)); //random func initilized

    printf("\n");
    printf("╔════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                ║\n");
    printf("║     ███████╗███╗   ██╗ █████╗  ██╗  ██╗███████╗                ║\n");
    printf("║     ██╔════╝████╗  ██║██╔══██╗ ██║ ██╔╝██╔════╝                ║\n");
    printf("║     ███████╗██╔██╗ ██║███████║ █████╔╝ █████╗                  ║\n");
    printf("║     ╚════██║██║╚██╗██║██╔══██║ ██╔═██╗ ██╔══╝                  ║\n");
    printf("║     ███████║██║ ╚████║██║  ██║ ██║  ██╗███████╗                ║\n");
    printf("║     ╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝ ╚═╝  ╚═╝╚══════╝                ║\n");
    printf("║                                                                ║\n");
    printf("║                  🐍 SNAKE GAME RENEWED 🐍                      ║\n");
    printf("╚════════════════════════════════════════════════════════════════╝\n\n");
    Sleep(500);

    //DONT NEED IN RIG-BUILDER
    //
    // printf("Enter your UserName: ");
    // if (fgets(player_Name,sizeof(player_Name),stdin) != NULL){
    //     size_t len = strlen(player_Name);
    //     if (len > 0 && player_Name[len - 1] == '\n')
    //         player_Name[len - 1] = '\0';
        
    //     // Convert to lowercase
    //     for (int i = 0; player_Name[i]; i++) player_Name[i] = tolower(player_Name[i]);
    // }

    // //Check if username is not empty, if so default to player
    // if (strlen(player_Name) == 0){
    //     strcpy(player_Name, "player");
    // }
    strcpy(player_Name, "TycoonBoss"); //INSTEAD REPLACED WITH THIS
    
    FILE *fp = fopen("scores.txt", "r");
    highScore = 0;
    if (fp != NULL){
        char Name[50];
        int Score;
        while (fscanf(fp,"%49s %d",Name,&Score) == 2){
            if (strcmp(Name,player_Name) == 0){
                highScore = Score;
                break;
            }
        }
        fclose(fp);
    }
    while (1){ //For now infinite loop
        score = 0;
        snakeLength = 3;
        direction = 1; //Default snakes moves right at start

        generateFood();
        int headX = WIDTH / 2, headY = HEIGHT / 2;
        for (int i = 0; i < snakeLength; i++) {
            SnakeX[i] = headX - i;
            SnakeY[i] = headY;
        }
        Speed = 320;
        while (1){
            MoveSnake(); // update snake position
            CheckFood(); //Checks for Food

            if (CheckCollision()){
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); //Resets buffer/direction variable
                system("cls");
                printf("\n\n\t💀 GAME OVER 💀\n\n");
                printf("Your snake crashed into the wall or itself!\n");
                printf("You Ate %d Apples!\n", score / 10);
                printf("Final Score: %d!\n", score);
                Beep(550, 150);
                Beep(420, 120);
                Beep(260, 180);

                // --- EXPORT BONUS FOR TYCOON GAME ---
                FILE *bonusFile = fopen("snake_bonus.txt", "w");
                if (bonusFile != NULL) {
                    fprintf(bonusFile, "%d\n", score / 10); // Exports total apples eaten
                    fclose(bonusFile);
                }
                
                if (score > highScore){
                    printf("\n✨ NEW HIGH SCORE: %d! ✨\n", score);
                    FILE *fp = fopen("scores.txt", "r");
                    FILE *temp = fopen("temp.txt", "w");
                    
                    if (temp == NULL) {
                        printf("Error: Could not save high score.\n");
                        break;
                    }
                    char Name[50];
                    int Score;
                    int found = 0;
                    if (fp != NULL){
                        while (fscanf(fp, "%49s %d", Name, &Score) == 2){
                            if (strcmp(Name, player_Name) == 0){
                                fprintf(temp, "%s %d\n", player_Name, score);
                                found = 1;
                            } else {
                                fprintf(temp, "%s %d\n", Name, Score);
                            }
                        }
                        fclose(fp);
                    }
                    if (!found) fprintf(temp, "%s %d\n", player_Name, score);
                    fclose(temp);
                    remove("scores.txt");
                    rename("temp.txt", "scores.txt");
                    highScore = score;
                }
                break;
            }
            draw(); //redraw everything
            if (direction == 0 || direction == 2) Sleep(Speed); //little slower
            else Sleep(Speed - 80); // left/right slightly faster to normalize speed
        }
        //DONT NEED IN RIG-BUILDER

        // //Replay
        // printf("\nEnter R to Re-Play OR any other key to Exit...");
        // char replay = _getch();
        // if (replay != 'r' && replay != 'R') break;
        
        //system("cls");
        //INSTEAD REPLACED WITH THIS
        printf("\nPress ANY KEY to return to the Tycoon Shop...");
        _getch();
        break;
    }
    return 0;
}