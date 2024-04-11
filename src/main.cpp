/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#include "menu.h"
#include <sstream>
#include "login.h"
#include "gameplay.h"
#include "score.h"
#include "timer.h"
#include "leaderBoard.h"
#include "dealocateAndSaveGame.h"

typedef enum GameScreen { LOGO = 0, LOGIN, MENU, LEADERBOARD, LEVEL, LEVELSPECIAL, GAMEPLAY, SCORE, EXIST } GameScreen;

using namespace std;

const int screenHeight = 700, screenWidth = 1024;

/*
    in this main funtion using the basic screen maneger example on this web  https://www.raylib.com/examples.html
*/
int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "pikachuu");
    // reading audio from data
    InitAudioDevice();
    Sound correctSound = LoadSound("src/data/correctsound.wav");
    
    // this line will make the game can be close by anything
    SetExitKey(KEY_NULL);
    //file path for reading data
    const string filePath = "src/data/user.txt";
    // parameter 
    int choice = 1;
    bool keyPressed = false;
    int currentLevel = 1;
    // argument for the create table and update table 
    int row = 0;
    int col = 0;

    //intialize the player pos
    int playerPosX = 1;
    int playerPosY = 1;

    //intialize the player selection
    int playerSelectionX = 1;
    int playerSelectionY = 1;

    //set background color
    Color backGround = { 7, 5, 68, 255 };

    //intialize player score data
    int maxNormalLevel = 0;
    int *playerNormalScore = NULL;
    int maxSpecialLevel = 0;
    int *playerSpecialScore = NULL;

    //intialize socre
    int scoree = 0;

    //this bool variable using in update table it will turn to true if player matching any pokemon
    bool isMatching = false;

    // check if player are playing normalmode or special mode
    bool normalMode = true;
    
    // 12 is a number of all pokemon picture in src/data/cropic
    const int numberOfPicture = 12;
    // read all the pokemon pic and return it in a dynamic data texture array
    cout << "create restexture array" << endl;
    Texture2D *resTexture = readImage(numberOfPicture);

    //intialize current screen
    GameScreen currentScreen = LOGO;
    
    // check if player have selected one poke or not
    bool selected = false;
    
    // flag to set window to exit
    bool exitWindow = false;

    //main pokemon array
    Pokemon **resArr = NULL;

    // 2 variable using to calculate the time when the line of suggest or line of matching is being draw
    float previousMatchingTime = 0;
    float previousSuggestTime = 0;

    //control the game level
    float startGameTime = 0;
    int timeLevel = 0;
    float timeLeft = 0;
    float tempTimeLeft = 0;
    int remainHelp = 0;
    int timeUp = 0;
    
    // to count the LOGO screen display time
    int framesCounter = 0;

    //2 list of point using drawLine() funtion to draw them in time with previousMatchingTime, previousSuggestTime
    Point* pointList = NULL;
    Point* suggestionList = NULL;
    string userName = "";

    // data base for leader board
    int dataBaseSize = 0;
    PlayerData *dataBase = NULL;
    bool normalLeaderBoard = true;
    int levelLeaderBoard = 1;

    //exit menu handling variable
    int exitOption = 0;
    bool isPlayerInMatch = false;

    // to cal frame player hold the moving button to make them go more fast 
    int pressFrame = 0;

    //intialize previous game screen for the exit menu
    GameScreen previousGameScreen = LOGO;

    //this gif playing technique i reference from this web https://www.raylib.com/examples.html 
    int animFrames = 0;
    Image backGroundAnim = LoadImageAnim("src/data/background3.gif", &animFrames);
    Texture2D texBackgroundAnim = LoadTextureFromImage(backGroundAnim);
    unsigned int nextFrameDataOffset = 0;  // Current byte offset to next frame in image.data
    int currentAnimFrame = 0;       // Current animation frame to load and draw
    int frameDelay = 8;             // Frame delay to switch between animation frames
    int frameCounter = 0;           // General frames counter



    SetTargetFPS(60);

    while (!exitWindow)
    {
        //update the frame of the animation of the background
        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            // Move to next frame
            // NOTE: If final frame is reached we return to first frame
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames) currentAnimFrame = 0;

            // Get memory offset position for next frame data in image.data
            nextFrameDataOffset = backGroundAnim.width*backGroundAnim.height*4*currentAnimFrame;

            // Update GPU texture data with next frame image data
            // WARNING: Data size (frame size) and pixel format must match already created texture
            UpdateTexture(texBackgroundAnim, ((unsigned char *)backGroundAnim.data) + nextFrameDataOffset);

            frameCounter = 0;
        }

        
        // if user want to exit game if they click on the x they will out the game without exit menu
        // if they using ecs button the exit menu will display
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {

            tempTimeLeft = GetTime();
            // chane current screen to the exit menu
            if (currentScreen != EXIST)
            {
                // save the prevscreen if user want come back
                previousGameScreen = currentScreen;
            }
            currentScreen = EXIST;
        }


        /*
            there are two switch case here the first one without the begindrawing and enddrawing we wont draw here in this
            switch case we just handdle all the case if player want to move to another gamescreen
        */
        switch (currentScreen)
        {
            //display logo for two minutes
            case LOGO:
            {
                framesCounter++;

                if (framesCounter > 120)
                {
                    currentScreen = LOGIN;
                }
                
            }
            break;

            case LOGIN:
            {
                // if player press the enter we will create account if they havent have one yet
                // else using them prev data
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
                //handle menu choice
                if (IsKeyPressed(KEY_ENTER))
                {
                    switch (choice)
                    {
                        case 1:
                            // go to normal mode
                            normalMode = true;
                            currentScreen = LEVEL;
                            currentLevel = 1;
                            break;
                        case 2:
                            //special Mode
                            normalMode = false;
                            currentScreen = LEVEL;
                            currentLevel = 1;
                            break;
                        case 3:
                            // go go leader board
                            cout << "dealocate data base array" << endl;
                            deallocatePlayerArray(dataBase, dataBaseSize);
                            dataBase = NULL;
                            cout << "create data base" << endl;
                            dataBase = readUserData(dataBaseSize);
                            currentScreen = LEADERBOARD;
                            break;
                        case 4:
                        // login again dealocate all the previous login data
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
            }
            break;

            case LEADERBOARD :
            {
                //dealocate if player press enter
                if (IsKeyPressed(KEY_ENTER))
                {
                    cout << "dealocate data base" << endl;
                    deallocatePlayerArray(dataBase, dataBaseSize);
                    currentScreen = MENU;
                }
            }
            break;
            //handle level 
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
                                timeUp = 3;
                            break;
                            
                            case 4:
                                row = 7;
                                col = 14;
                                timeLevel = 9;
                                remainHelp = 3;
                                timeUp = 3;
                            break;

                            case 5:
                                row = 8;
                                col = 15;
                                timeLevel = 9;
                                remainHelp = 3;
                                timeUp = 2;
                            break;

                            case 6:
                                row = 9;
                                col = 16;
                                timeLevel = 7;
                                remainHelp = 3;
                                timeUp = 2;
                        break;
                        }
                        // when level are being intialize create a pokemon talbe to play
                        cout << "create table" << endl;
                        createTable(resArr, row, col, numberOfPicture);

                        // get the first suggestion here
                        suggestion(resArr, row, col, suggestionList);

                        //intialize player pos again 
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
            }
            break;

            case GAMEPLAY:
            {
                // calculate player time left
                timeLeft = timeLevel - (GetTime() - startGameTime);
                if (timeLeft > timeLevel)
                {
                    // bounus scoree if player playing toooo fasssttttt
                    scoree += 30;
                    startGameTime = GetTime();
                }

                //player Out of Time they wont be able to unlock new level just update them hiscore if they have new once
                if (timeLeft < 0)
                {
                    //save player score
                    if (normalMode)
                        saveScore(playerNormalScore, currentLevel, scoree);
                    else
                        saveScore(playerSpecialScore, currentLevel, scoree);

                    cout << "free tabe" << endl;
                    //free the playing table
                    free2DArray(resArr, row);
                    resArr = NULL;

                    // they are not in match anymore
                    // turning in to score menu
                    isPlayerInMatch = false;
                    currentScreen = SCORE;
                }
                if (isMatching == true)
                {
                    // if they matching get them bonus time 
                    startGameTime += timeUp;
                    //play matching sound
                    PlaySound(correctSound);

                    // clear the suggest list and create new once
                    clearList(suggestionList);
                    suggestion(resArr, row, col, suggestionList);
                    
                    // player win or the matrix need to be random again
                    if (suggestionList == NULL)
                    {
                        //if player win we need to update playerscore and update current level
                        if (checkEmpty(resArr, row, col))
                        {
                            // save score
                            if (normalMode)
                                saveScore(playerNormalScore, currentLevel, scoree);
                            else
                                saveScore(playerSpecialScore, currentLevel, scoree);
                                
                            //update player level if they win
                            if (currentLevel == maxNormalLevel && currentLevel < 6 && normalMode == true)
                            { 
                                levelUp(playerNormalScore, maxNormalLevel);
                            }
                            if (currentLevel == maxSpecialLevel && currentLevel < 6 && normalMode == false)
                            { 
                                levelUp(playerSpecialScore, maxSpecialLevel);
                            }
                            // dealocate playing table
                            cout << "free table" << endl;
                            free2DArray(resArr, row);
                            resArr = NULL;
                            // player not in match anymore turn to score menu
                            isPlayerInMatch = false;
                            currentScreen = SCORE;
                            // break;
                        }
                        else if (normalMode == true)
                        {
                            //if there no way to win shuffle the matrix until have a way to matching
                            while (suggestionList == NULL)
                            {
                                shuffle_array_2d(resArr, row, col);
                                clearList(suggestionList);
                                suggestion(resArr, row, col, suggestionList);
                            }
                        }
                        // if not normal mode and out of matching player will lose
                        // update special score data
                        if (normalMode == false)
                        {
                            saveScore(playerSpecialScore, currentLevel, scoree);
                            // dealocate playing table
                            cout << "free table" << endl;
                            free2DArray(resArr, row);
                            resArr = NULL;
                            // player not in match anymore turn to score menu
                            isPlayerInMatch = false;
                            currentScreen = SCORE;
                        }
                    }
                    //intialize ismatching again prepare for the next matching
                    isMatching = false;
                }
            }
            break;

            case SCORE:
            {
                // out score menu
                if (IsKeyPressed(KEY_ENTER))
                {
                    scoree = 0;
                    currentScreen = LEVEL;
                    currentLevel = 1;

                }
            }
            break;
            case EXIST:
            {
                //exit menu handling
                if (IsKeyPressed(KEY_ENTER))
                {

                    switch (exitOption)
                    {
                        case 0:
                            // if they are in match save current time if they want to get back this is the pause game feature
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
                            //if they want to go the menu
                            // if they are in match dealocate
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
                            // if they are loin and logo they must login fist before goin the menu
                            else if (previousGameScreen == LOGIN || previousGameScreen == LOGO) 
                            {
                                currentScreen = LOGIN;
                            }
                            //dealocate data base if they were in leader board
                            else
                            {
                                cout << "dealocate database" << endl;
                                deallocatePlayerArray(dataBase, dataBaseSize);
                                currentScreen = MENU;
                            }
                            break;
                        case 2:
                            // they want to exit the game save score and out
                                deleteAllDataAndSaveSocore(playerNormalScore, playerSpecialScore, maxNormalLevel, maxSpecialLevel, filePath, userName, pointList, suggestionList, resTexture, numberOfPicture, resArr, row, dataBase, dataBaseSize);
                                exitWindow = true;
                            break;
                    }
                }
                else if (WindowShouldClose())
                {
                    // if they click in the x button save score and out not need to exit menu
                    deleteAllDataAndSaveSocore(playerNormalScore, playerSpecialScore, maxNormalLevel, maxSpecialLevel, filePath, userName, pointList, suggestionList, resTexture, numberOfPicture, resArr, row, dataBase, dataBaseSize);
                    exitWindow = true;
                    break;
                }
            }
            break;
        }
        //this is the second switch case to drawing all the game screen 
        BeginDrawing();

        ClearBackground(backGround);
        // resize the back ground to draw it
        Rectangle sourceRec = { 0, 0, texBackgroundAnim.width, texBackgroundAnim.height };
        Rectangle destRec = { 0, 0, screenWidth, screenHeight};
        // draw background
        DrawTexturePro(texBackgroundAnim, sourceRec, destRec, {0, 0}, 0, GRAY);

        switch (currentScreen)
        {
            case LOGO:
            {
                // draw logo menu
                Vector2 textSize = MeasureTextEx(GetFontDefault(), "hiiiii welcome to my game project :D", 40, 4);
                DrawText("hiiiii welcome to my game project :D", screenWidth / 2 - textSize.x/2, 300, 40, {224, 68, 131, 255});
            } break;

            case LOGIN:
            {
                // instruction about login
                if (userName == "")
                {
                    Vector2 warning = MeasureTextEx(GetFontDefault(), "You need to enter a username first in order to play", 30, 3);
                    // setting color for the background of the instruction
                    Color fadedColor = Fade(BLACK, 0.5f); // Thiết lập độ trong suốt của màu sắc
                    DrawRectangleRec((Rectangle){screenWidth / 2 - warning.x / 2 - 20, 600 - 20, warning.x + 40, warning.y + 40}, fadedColor);
                    //draw text
                    DrawText("You need to enter a username first in order to play", screenWidth / 2 - warning.x / 2, 600, 30, WHITE);
                }
                drawLogin(keyPressed, choice, userName);

            }
            break;

            case MENU:
            {
                //draw menu
                menuChoice(choice);
                menuDraw(choice);
            }
            break;

            case LEADERBOARD :
            {
                //draw leader board
                displayLeaderBoard(dataBase, dataBaseSize, normalLeaderBoard, levelLeaderBoard);
            }
            break;

            case LEVEL:
            {   
                //draw level menu
                if (normalMode)
                levelMenu(currentLevel, maxNormalLevel);
                else
                levelMenu(currentLevel, maxSpecialLevel);
            }
            break;

            case GAMEPLAY:
            {
                // draw table for the game play

                //draw the matching line if they matching
                if (GetTime() - previousMatchingTime < 0.4)
                {
                    drawLine(pointList, 60, 60);
                }
                else if (normalMode == false)
                {
                    specialModeColasp(resArr, row, col);
                    //update suggest becase the location have been change
                    clearList(suggestionList);
                    suggestion(resArr, row, col, suggestionList);
                }

                //draw playing table and update them
                drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY, resTexture);
                updateTable(resArr, playerPosX, playerPosY, row, col, selected, playerSelectionX, playerSelectionY, pointList, previousMatchingTime, scoree, isMatching, pressFrame);
                displayScore(scoree);
                displayTimer(timeLevel, timeLeft);
                displayRemainingHelp(remainHelp);
                //if they want to suggest update time to display suggest
                if (IsKeyPressed(KEY_X) && remainHelp > 0)
                {
                    remainHelp--;
                    previousSuggestTime = GetTime();
                }
                // display suggest depend on time they press X
                if (GetTime() - previousSuggestTime < 0.5)
                {
                    drawLine(suggestionList, 60, 60);
                }

            }
            break;
            case SCORE:
            {
                // draw score menu
                if (normalMode == true)
                {
                    scoreMenu(scoree, playerNormalScore[currentLevel - 1]);
                }
                else
                    scoreMenu(scoree, playerSpecialScore[currentLevel - 1]);
            }
            break;
            case EXIST:
            {
                // draw exit menu
                exitMenu(exitOption, isPlayerInMatch);
            }
            break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}