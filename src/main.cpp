// #include "raylib.h"
#include "menu.h"
#include <sstream>
#include "login.h"
#include "gameplay.h"
#include "score.h"
#include "timer.h"
#include "leaderBoard.h"

typedef enum GameScreen { LOGO = 0, LOGIN, MENU, LEADERBOARD, LEVEL, LEVELSPECIAL, GAMEPLAY, SCORE, EXIST } GameScreen;

using namespace std;

const int screenHeight = 686, screenWidth = 1024;


int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "pikachuu");

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
    cout << "create restexture array" << endl;
    Texture2D *resTexture = readImage(numberOfPicture);

    GameScreen currentScreen = LOGO;

    bool selected = false;
    
    bool exitWindowRequested = false;   // Flag to request window to exit
    bool exitWindow = false;    // Flag to set window to exit

    Pokemon **resArr = NULL;

    float previousMatchingTime = 0;
    float previousSuggestTime = 0;

    float startGameTime = 0;
    int timeLevel = 0;
    float timeLeft = 0;
    float tempTimeLeft = 0;
    int remainHelp = 0;
    int timeUp = 0;

    int framesCounter = 0;

    Point* pointList = NULL;
    Point* suggestionList = NULL;
    string userName = "";

    int dataBaseSize = 0;
    PlayerData *dataBase = NULL;
    bool normalLeaderBoard = true;
    int levelLeaderBoard = 1;

    int exitOption = 0;
    bool isPlayerInMatch = false;

    GameScreen previousGameScreen = LOGO;

    SetTargetFPS(60);

    while (!exitWindow)
    {
        cout << currentScreen << " " << previousGameScreen;
        // out game we need to dealocate so much thing here :DDDD
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            // save game
            tempTimeLeft = GetTime();
            previousGameScreen = currentScreen;
            currentScreen = EXIST;
            // if (IsKeyPressed(KEY_Y)) exitWindow = true;
            // else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
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
                    cout << "read player normal and special scoree" << endl;
                    playerNormalScore = readNormalData(filePath, userName, maxNormalLevel);
                    playerSpecialScore = readSpecialData(filePath, userName, maxSpecialLevel);
                    currentScreen = MENU;
                }
            } break;
            case MENU:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    switch (choice)
                    {
                        case 1:
                            normalMode = true;
                            currentScreen = LEVEL;
                            break;
                        case 2:
                            //special Mode
                            normalMode = false;
                            currentScreen = LEVEL;
                            break;
                        case 3:
                        
                            cout << "dealocate data base array" << endl;
                            deallocatePlayerArray(dataBase, dataBaseSize);
                            dataBase = NULL;
                            cout << "create data base" << endl;
                            dataBase = readUserData(dataBaseSize);
                            currentScreen = LEADERBOARD;
                            break;
                        case 4:
                        // login again
                        if (playerNormalScore != NULL)
                        {
                            cout << "delete normal scoree" << endl;
                            delete[] playerNormalScore;
                        }
                        if (playerSpecialScore != NULL)
                        {
                            delete[] playerSpecialScore;
                            cout << "delet special scoree" << endl;
                        }
                            currentScreen = LOGIN;
                            break;
                    }
                }
            } break;
            case LEADERBOARD :
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    cout << "dealocate data base" << endl;
                    deallocatePlayerArray(dataBase, dataBaseSize);
                    currentScreen = MENU;
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
                                row = 7;
                                col = 10;
                                timeLevel = 12;
                                remainHelp = 4;
                                timeUp = 6;
                            break;

                            case 2:
                                row = 7;
                                col = 12;
                                timeLevel = 12;
                                remainHelp = 3;
                                timeUp = 4.5;
                            break;

                            case 3:
                                row = 7;
                                col = 14;
                                timeLevel = 10;
                                remainHelp = 3;
                                timeUp = 4;
                            break;
                            
                            case 4:
                                row = 7;
                                col = 14;
                                timeLevel = 10;
                                remainHelp = 3;
                                timeUp = 3;
                            break;

                            case 5:
                                row = 8;
                                col = 15;
                                timeLevel = 9;
                                remainHelp = 3;
                                timeUp = 3;
                            break;

                            case 6:
                                row = 9;
                                col = 16;
                                timeLevel = 7;
                                remainHelp = 3;
                                timeUp = 2;
                        break;
                        }
                        cout << "create table" << endl;
                        createTable(resArr, row, col, numberOfPicture);
                        suggestion(resArr, row, col, suggestionList);

                        playerPosX = 1;
                        playerPosY = 1;
                        playerSelectionX = 1;
                        playerSelectionY = 1;
                    }
                    //  lets playyy
                    isPlayerInMatch = true;
                    startGameTime = GetTime();
                    currentScreen = GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                timeLeft = timeLevel - (GetTime() - startGameTime);
                if (timeLeft > timeLevel)
                {
                    // bounus scoree if player playing toooo fasssttttt
                    scoree += 30;
                    startGameTime = GetTime();
                }
                //player Out of Time
                if (timeLeft < 0)
                {
                    saveScore(playerNormalScore, currentLevel, scoree);
                    cout << "free tabe" << endl;
                    free2DArray(resArr, row);
                    resArr = NULL;
                    isPlayerInMatch = false;
                    currentScreen = SCORE;
                }
                else if (isMatching == true)
                {
                    startGameTime += timeUp;

                    clearList(suggestionList);
                    suggestion(resArr, row, col, suggestionList);
                    
                    // player win or the matrix need to be random again
                    if (suggestionList == NULL)
                    {
                        //if player win we need to update playerscore and update current level
                        if (checkEmpty(resArr, row, col))
                        {
                            // cập nhật điểm mở khóa màn chơi mới cho người chơi
                            saveScore(playerNormalScore, currentLevel, scoree);
                            if (currentLevel == maxNormalLevel && currentLevel < 6)
                            { 
                                levelUp(playerNormalScore, maxNormalLevel);
                            }
                            // giải phóng mảng 2 chiều
                            cout << "free table" << endl;
                            free2DArray(resArr, row);
                            resArr = NULL;
                            isPlayerInMatch = false;
                            //chuyển sang màn hình score
                            currentScreen = SCORE;
                            break;
                        }
                        else
                        {
                            while (suggestionList == NULL)
                            {
                                shuffle_array_2d(resArr, row, col);
                                clearList(suggestionList);
                                suggestion(resArr, row, col, suggestionList);
                            }
                        }
                        // nếu chưa thắng và không có nước đi nào còn có thể đi được thì xáo mảng lại
                    }
                    
                    isMatching = false;
                }
            } break;
            case SCORE:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    scoree = 0;
                    currentScreen = LEVEL;
                }
            } break;
            case EXIST:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    switch (exitOption)
                    {
                        case 0:
                            if (isPlayerInMatch)
                            {
                                startGameTime += GetTime() - tempTimeLeft;
                                currentScreen = GAMEPLAY;
                            }
                            else 
                            {
                                currentScreen = previousGameScreen;
                                cout << previousGameScreen;
                            }
                            break;
                        case 1:
                            if (isPlayerInMatch)
                            {
                                if (resArr != NULL)
                                {
                                    clearList(suggestionList);
                                    clearList(pointList);
                                    free2DArray(resArr, row);
                                    resArr = NULL;
                                    isPlayerInMatch = false;
                                    playerPosX = 1;
                                    playerPosY = 1;
                                    playerSelectionX = 1;
                                    playerSelectionY = 1;
                                    currentScreen = MENU;
                                }
                            }
                            else if (previousGameScreen == LOGIN || previousGameScreen == LOGO) 
                            {
                                cout << "flaggggg" << endl;
                                currentScreen = LOGIN;
                            }
                            else
                            {
                                cout << "dealocate database" << endl;
                                deallocatePlayerArray(dataBase, dataBaseSize);
                                currentScreen = MENU;
                            }
                            break;
                        case 2:
                                cout << "saving current player Score" << endl;
                                saveGame(userName, playerNormalScore, maxNormalLevel, playerSpecialScore, maxSpecialLevel, filePath);
                                //dealocate
                                cout << "clear point list and suggestion list " << endl;
                                clearList(suggestionList);
                                clearList(pointList);
                                cout << "free table " << endl;
                                free2DArray(resArr, row);
                                cout << "free texture array" << endl;
                                UnloadTextureArray(resTexture, numberOfPicture);
                                if (playerNormalScore != NULL)
                                {
                                    delete[] playerNormalScore;
                                    playerNormalScore = NULL;
                                    cout << "free player Normal score" << endl;
                                }
                                if (playerSpecialScore != NULL)
                                {
                                    delete[] playerSpecialScore;
                                    playerSpecialScore = NULL;
                                    cout << "free player Special Scoree" << endl;
                                }
                                cout << "dealocate data base" << endl;
                                deallocatePlayerArray(dataBase, dataBaseSize);
                                exitWindow = true;
                            break;
                    }
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
                menuChoice(choice);
                menuDraw(choice);
            } break;

            case LEADERBOARD :
            {
                displayLeaderBoard(dataBase, dataBaseSize, normalLeaderBoard, levelLeaderBoard);
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
                displayTimer(timeLevel, timeLeft);

                if (IsKeyPressed(KEY_X) && remainHelp > 0)
                {
                    remainHelp--;
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
                exitMenu(exitOption, isPlayerInMatch);
            } break;
            default: break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}