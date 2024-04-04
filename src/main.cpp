// #include "raylib.h"
#include "menu.h"
#include <sstream>
#include "login.h"
#include "gameplay.h"
using namespace std;

typedef enum GameScreen { LOGO = 0, LOGIN, MENU, LEVEL, LEVELSPECIAL, GAMEPLAY, SCORE, EXIST } GameScreen;

const string filePath = "src/data/user.txt";

int choice = 1;
bool keyPressed = false;
int currentLevel = 1;

int row = 0;
int col = 0;

int playerPosX = 1;
int playerPosY = 1;

int playerSelectionX = 1;
int playerSelectionY = 1;

const int screenHeight = 686, screenWidth = 1024;
Color backGround = {176, 212, 184, 255};

int maxNormalLevel = 0;
int *playerNormalSore = NULL;
int maxSpecialLevel = 0;
int *playerSpecialScore = NULL;

int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "pikachu");

    SetExitKey(KEY_NULL);

    const int numberOfPicture = 12;
    Texture2D *resTexture = readImage(numberOfPicture);

    GameScreen currentScreen = LOGO;

    bool tableCreated = false;
    bool selected = false;
    
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit

    Pokemon **resArr = NULL;

    float previousMatchingTime = 0;
    int framesCounter = 0;

    Point* pointList = NULL;

    string userName = "";

    SetTargetFPS(60);

    while (!exitWindow)
    {
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation
            
            // if (IsKeyPressed(KEY_Y)) exitWindow = true;
            // else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
            if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindow = true;
        }
        switch (currentScreen)
        {
            case LOGO:
            {
                framesCounter++;

                if (framesCounter > 120)
                {
                    currentScreen = LOGIN;
                }
            } break;
            case LOGIN:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    checkAndCreateUser(filePath, userName);
                    playerNormalSore = readNormalData(filePath, userName, maxNormalLevel);
                    playerSpecialScore = readSpecialData(filePath, userName, maxSpecialLevel);
                    currentScreen = MENU;
                }
            } break;
            case MENU:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = LEVEL;
                }
            } break;
            case LEVEL:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = SCORE;
                }
            } break;
            case SCORE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = EXIST;
                }
            } break;
            case EXIST:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    currentScreen = LOGIN;
                }
            } break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(backGround);

        switch (currentScreen)
        {
            case LOGO:
            {
                Vector2 textSize = MeasureTextEx(GetFontDefault(), "hiiiii welcome to my game project :D", 40, 4);
                DrawText("hiiiii welcome to my game project :D", screenWidth / 2 - textSize.x/2, 300, 40, GRAY);
            } break;
            case LOGIN:
            {
                drawLogin(keyPressed, choice, userName);

            } break;
            case MENU:
            {
                menuChoice(choice, keyPressed);
                menuDraw(choice);
            } break;
            case LEVEL:
            {
                levelMenu(currentLevel, maxNormalLevel);
            } break;
            case GAMEPLAY:
            {
                switch(currentLevel)
                {
                    case 1:
                        row = 6;
                        col = 9;
                        if (tableCreated == false)
                        {
                        resArr = createTable(row, col, resTexture, numberOfPicture);
                        tableCreated = true;
                        cout << "mot";
                        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);
                        }

                        if (GetTime() - previousMatchingTime < 1)
                        {
                            drawLine(pointList, 60, 60);
                        }
                        //khi win hãy xóa bộ nhớ của list điểm cuối cùng và delete resArr nữa 
                        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);
                        updateTable(resArr, playerPosX, playerPosY, row, col, selected, playerSelectionX, playerSelectionY, pointList, previousMatchingTime);
                    break;

                    case 2:
                        row = 7;
                        col = 10;
                        if (tableCreated == false)
                        {
                        resArr = createTable(row, col, resTexture, numberOfPicture);
                        tableCreated = true;
                        cout << "hai";
                        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);
                        }

                        if (GetTime() - previousMatchingTime < 1)
                        {
                            drawLine(pointList, 60, 60);
                        }
                        //khi win hãy xóa bộ nhớ của list điểm cuối cùng và delete resArr nữa 
                        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);
                        updateTable(resArr, playerPosX, playerPosY, row, col, selected, playerSelectionX, playerSelectionY, pointList, previousMatchingTime);
                    break;

                    case 3:
                        row = 7;
                        col = 9;
                    break;
                    
                    case 4:
                        row = 7;
                        col = 9;
                    break;

                    case 5:
                        row = 7;
                        col = 9;
                    break;

                    case 6:
                        row = 7;
                        col = 9;
                    break;
                }
            } break;
            case LEVELSPECIAL:
            {
                levelMenu(currentLevel, maxSpecialLevel);
            } break;
            case SCORE:
            {
                // levelMenu(currentLevel);
            } break;
            case EXIST:
            {
                // levelMenu(currentLevel);
            } break;
            default: break;
        }

        EndDrawing();
    }

    CloseWindow();

     delete[] resTexture;

    return 0;
}