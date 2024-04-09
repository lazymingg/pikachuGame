// #include "raylib.h"
#include "menu.h"
#include <sstream>
#include "login.h"
#include "gameplay.h"
#include "score.h"
#include "timer.h"
#include "leaderBoard.h"
#include "dealocateAndSaveGame.h"
#include "colors.h"

typedef enum GameScreen { LOGO = 0, LOGIN, MENU, LEADERBOARD, LEVEL, LEVELSPECIAL, GAMEPLAY, SCORE, EXIST } GameScreen;

using namespace std;

const int screenHeight = 700, screenWidth = 1024;


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

    Color backGround = tim;

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

    int pressFrame = 0;

    GameScreen previousGameScreen = LOGO;

    int animFrames = 0;
    Image imScarfyAnim = LoadImageAnim("src/data/background3.gif", &animFrames);

    Texture2D texScarfyAnim = LoadTextureFromImage(imScarfyAnim);
    unsigned int nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data
    int currentAnimFrame = 0;       // Current animation frame to load and draw
    int frameDelay = 8;             // Frame delay to switch between animation frames
    int frameCounter = 0;           // General frames counter



    SetTargetFPS(60);

    while (!exitWindow)
    {
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            // Move to next frame
            // NOTE: If final frame is reached we return to first frame
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

            // Get memory offset position for next frame data in image.data
            nextFrameDataOffset = imScarfyAnim.width*imScarfyAnim.height*4*currentAnimFrame;

            // Update GPU texture data with next frame image data
            // WARNING: Data size (frame size) and pixel format must match already created texture
            UpdateTexture(texScarfyAnim, ((unsigned char *)imScarfyAnim.data) + nextFrameDataOffset);

            frameCounter = 0;
        }

        
        // out game we need to dealocate so much thing here :DDDD
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            // save game

            tempTimeLeft = GetTime();
            if (currentScreen != EXIST)
            {
                previousGameScreen = currentScreen;
            }
            currentScreen = EXIST;
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
                if (IsKeyPressed(KEY_ENTER) && !userName.empty())
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
                            playerNormalScore = NULL;
                        }
                        if (playerSpecialScore != NULL)
                        {
                            delete[] playerSpecialScore;
                            cout << "delet special scoree" << endl;
                            playerSpecialScore = NULL;
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
                                deleteAllDataAndSaveSocore(playerNormalScore, playerSpecialScore, maxNormalLevel, maxSpecialLevel, filePath, userName, pointList, suggestionList, resTexture, numberOfPicture, resArr, row, dataBase, dataBaseSize);
                                exitWindow = true;
                            break;
                    }
                }
                else if (WindowShouldClose())
                {
                    deleteAllDataAndSaveSocore(playerNormalScore, playerSpecialScore, maxNormalLevel, maxSpecialLevel, filePath, userName, pointList, suggestionList, resTexture, numberOfPicture, resArr, row, dataBase, dataBaseSize);
                    exitWindow = true;
                    break;
                }
            } break;
            default: break;
        }

        BeginDrawing();
        ClearBackground(backGround);
        Rectangle sourceRec = { 0, 0, texScarfyAnim.width, texScarfyAnim.height };
        Rectangle destRec = { 0, 0, screenWidth, screenHeight};
        DrawTexturePro(texScarfyAnim, sourceRec, destRec, {0, 0}, 0, GRAY);

        switch (currentScreen)
        {
            case LOGO:
            {
                Vector2 textSize = MeasureTextEx(GetFontDefault(), "hiiiii welcome to my game project :D", 40, 4);
                DrawText("hiiiii welcome to my game project :D", screenWidth / 2 - textSize.x/2, 300, 40, hong_cam);
            } break;

            case LOGIN:
            {
                if (userName == "")
                {
                    Vector2 warning = MeasureTextEx(GetFontDefault(), "You need to enter a username first in order to play", 30, 3);
                    // Vẽ hình chữ nhật với màu mờ
                    Color fadedColor = Fade(BLACK, 0.5f); // Thiết lập độ trong suốt của màu sắc
                    DrawRectangleRec((Rectangle){screenWidth / 2 - warning.x / 2 - 20, 600 - 20, warning.x + 40, warning.y + 40}, fadedColor);
                    // Vẽ văn bản
                    DrawText("You need to enter a username first in order to play", screenWidth / 2 - warning.x / 2, 600, 30, WHITE);
                }
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
                updateTable(resArr, playerPosX, playerPosY, row, col, selected, playerSelectionX, playerSelectionY, pointList, previousMatchingTime, scoree, isMatching, pressFrame);
                displayScore(scoree);
                displayTimer(timeLevel, timeLeft);
                displayRemainingHelp(remainHelp);

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