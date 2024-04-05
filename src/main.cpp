// #include "raylib.h"
#include "menu.h"
#include <sstream>
#include "login.h"
#include "gameplay.h"
using namespace std;
#include "score.h"
typedef enum GameScreen { LOGO = 0, LOGIN, MENU, LEVEL, LEVELSPECIAL, GAMEPLAY, SCORE, EXIST } GameScreen;



const int screenHeight = 686, screenWidth = 1024;


int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "thanhhh binhhh de thuongg :D");

    SetExitKey(KEY_NULL);
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

    Color backGround = {176, 212, 184, 255};

    int maxNormalLevel = 0;
    int *playerNormalScore = NULL;

    int maxSpecialLevel = 0;
    int *playerSpecialScore = NULL;

    int scoree = 0;
    bool isMatching = false;

    bool normalMode = true;

    const int numberOfPicture = 12;
    Texture2D *resTexture = readImage(numberOfPicture);

    GameScreen currentScreen = LOGO;

    bool tableCreated = false;
    bool selected = false;
    
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit

    Pokemon **resArr = NULL;

    float previousMatchingTime = 0;
    float previousSuggestTime = 0;

    int framesCounter = 0;

    Point* pointList = NULL;
    Point* suggestionList = NULL;
    string userName = "";

    SetTargetFPS(60);

    while (!exitWindow)
    {

        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;
        if (exitWindowRequested)
        {
            // A request for close window has been issued, we can save data before closing
            // or just show a message asking for confirmation
            saveGame(userName, playerNormalScore, maxNormalLevel, playerSpecialScore, maxSpecialLevel, filePath);
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
                    playerNormalScore = readNormalData(filePath, userName, maxNormalLevel);
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
                    if (resArr == NULL)
                    {
                        switch(currentLevel)
                        {
                            case 1:
                                row = 3;
                                col = 4;
                            break;

                            case 2:
                                row = 3;
                                col = 4;
                            break;

                            case 3:
                                row = 8;
                                col = 11;
                            break;
                            
                            case 4:
                                row = 8;
                                col = 13;
                            break;

                            case 5:
                                row = 10;
                                col = 14;
                            break;

                            case 6:
                                // row = 10;
                                // col = 16;
                                row = 5;
                                col = 4;
                        break;
                        }
                        cout << "row : " << row << "col : " << col << endl;
                        createTable(resArr, row, col, numberOfPicture);
                    }
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                if (isMatching == true)
                {
                    cout << "aaaaa";
                    clearList(suggestionList);
                    suggestion(resArr, row, col, suggestionList);
                    if (suggestionList == NULL)
                    {
                        // player win or the matrix need to be random again

                        //if player win we need to update playerscore and update current level
                        if (checkEmpty(resArr, row, col))
                        {
                            // cập nhật điểm mở khóa màn chơi mới cho người chơi
                            saveScore(playerNormalScore, currentLevel, scoree);
                            levelUp(playerNormalScore, maxNormalLevel);
                            // chuyển sang menu score
                            free2DArray(resArr, row);
                            resArr = NULL;
                            currentScreen = SCORE;
                            break;
                            cout << "win";
                        }
                        else
                        {
                            hintshuffle(resArr, row, col);
                        }
                    }
                    isMatching = false;
                }
            } break;
            case SCORE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    if (currentLevel == maxNormalLevel && currentLevel < 6)
                    {
                        cout << "level up : " << endl;
                        cout << "max normal level : " << maxNormalLevel << endl;
                    }
                    currentScreen = LEVEL;

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
                if (GetTime() - previousMatchingTime < 0.5)
                {
                    drawLine(pointList, 60, 60);
                }
                //khi win hãy xóa bộ nhớ của list điểm cuối cùng và delete resArr nữa 
                drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY, resTexture);
                updateTable(resArr, playerPosX, playerPosY, row, col, selected, playerSelectionX, playerSelectionY, pointList, previousMatchingTime, scoree, isMatching);
                displayScore(scoree);

                if (IsKeyPressed(KEY_X))
                {
                    previousSuggestTime = GetTime();
                }
                if (GetTime() - previousSuggestTime < 0.5)
                {
                    drawLine(suggestionList, 60, 60);
                }
            } break;
            case LEVELSPECIAL:
            {
                levelMenu(currentLevel, maxSpecialLevel);
            } break;
            case SCORE:
            {
                if (normalMode == true)
                {
                    scoreMenu(scoree, playerNormalScore[currentLevel - 1]);
                }
                
            } break;
            case EXIST:
            {


            } break;
            default: break;
        }

        EndDrawing();


    }

    CloseWindow();

     delete[] resTexture;

    return 0;
}