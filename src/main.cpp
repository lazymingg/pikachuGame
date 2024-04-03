#include "raylib.h"
#include "menu.h"
#include <sstream>
#include "login.h"
#include "gameplay.h"
#include <iomanip>
#include <iostream>
using namespace std;

typedef enum GameScreen { LOGO = 0, LOGIN, MENU, LEVEL, GAMEPLAY, SCORE, EXIST } GameScreen;

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

int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "pikachugame");

    const int numberOfPicture = 12;
    Texture2D *resTexture = readImage(numberOfPicture);

    GameScreen currentScreen = LOGO;

    bool tableCreated = false;
    bool selected = true;
    bool isTheLineBeDraw = false;
    Pokemon **resArr = NULL;

    float previousMatchingTime = 0;
    int framesCounter = 0;
    Point* pointList = NULL;
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
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
                // if (IsKeyPressed(KEY_ENTER))
                // {
                //     currentScreen = SCORE;
                // }
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
                drawLogin(keyPressed, choice);
            } break;
            case MENU:
            {
                menuChoice(choice, keyPressed);
                menuDraw(choice);
            } break;
            case LEVEL:
            {
                levelMenu(currentLevel);
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
                        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);
                        updateTable(resArr, playerPosX, playerPosY, row, col, selected, playerSelectionX, playerSelectionY, pointList, previousMatchingTime);
                    break;

                    case 2:
                        row = 7;
                        col = 9;
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
            case SCORE:
            {
                levelMenu(currentLevel);
            } break;
            case EXIST:
            {
                levelMenu(currentLevel);
            } break;
            default: break;
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}