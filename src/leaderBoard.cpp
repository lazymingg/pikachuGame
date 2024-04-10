/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#include "leaderBoard.h"
/*
     player data is in this format
    userName
    maxNormalMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    maxSpecialMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    this funtion aim to read that data and store in a array to make data base for the leader board
*/
PlayerData* readUserData(int &size)
{
    const string filePath = "src/data/user.txt";
    ifstream fIn(filePath.c_str());

    if (!fIn.is_open()) {
        cerr << "Failed to open file " << filePath << endl;
        return nullptr;
    }

    string temp = "";
    int count = 0;
    while (getline(fIn,temp))
    {
        count++;
    }
    size = count / 3;
    PlayerData *resArr = new PlayerData[size];

    // Reset file pointer to the beginning of the file
    fIn.clear();
    fIn.seekg(0, ios::beg);

    for (int i = 0; i < size; i++)
    {
        getline(fIn, resArr[i].userName);

        fIn >> resArr[i].maxNormalLevel;
        fIn.ignore();
        resArr[i].playerNormalScore = new int[6];
        for (int j = 0; j < 6; j++)
        {
            fIn >> resArr[i].playerNormalScore[j];
            fIn.ignore();
        }

        fIn >> resArr[i].maxSpecialLevel;
        fIn.ignore();
        resArr[i].playerSpecialScore = new int[6];
        for (int j = 0; j < 6; j++)
        {
            fIn >> resArr[i].playerSpecialScore[j];
            fIn.ignore();
        }
    }
    fIn.close();
    return resArr;
}
/*
    i using the buble sort taken from https://www.geeksforgeeks.org/bubble-sort/
    and modify it to make it sort the playerData for me
*/
void bubbleSort(PlayerData *arr, int n, int level, bool mode)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (j = 0; j < n - i - 1; j++)
        {
            if (mode == true)
            {
                if (arr[j].playerNormalScore[level - 1] < arr[j + 1].playerNormalScore[level - 1])
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            else
            {
                if (arr[j].playerSpecialScore[level - 1] < arr[j + 1].playerSpecialScore[level - 1])
                {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
        }
 
        // If no two elements were swapped
        // by inner loop, then break
        if (swapped == false)
            break;
    }
}

/*
    after have the data base of the player this funtion will be call when player press in the leader board to
    drawn all the leader board, level, and player score
*/
void drawLeaderBoard(PlayerData *arr, int size, int level, bool mode)
{
    // get screen size
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    Color fadedColor = Fade(BLACK, 0.5f); // Thiết lập độ trong suốt của màu sắc
    Vector2 textSize = MeasureTextEx(GetFontDefault(), "LEADER BOARD :D", 50, 5);
    // vẽ khung hình vuông bao quanh text
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 50 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
    DrawText("LEADER BOARD :D", screenWidth / 2 - textSize.x/2, 50, 50, PINK);
    string temp = "Level : " + to_string(level);
    textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 50, 5);
    // vẽ khung hình vuông bao quanh text
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 10, 130 - 10, textSize.x + 20, textSize.y + 20}, fadedColor);
    DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2, 130, 50, PINK);
    temp = "Only the top 5 outstanding players are mentioned here";
    textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 20, 2);
    DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2, 590, 20, GRAY);
    temp = " Use the WASD buttons to scroll further and press Enter to exit.";
    textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 20, 2);
    DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2, 630, 20, GRAY);

    if (mode)
    {
        temp = "Normal Mode";
        textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 40, 4);
        // vẽ khung hình vuông bao quanh text
        DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x/2 - 350 - 20, screenHeight / 2 - textSize.y/2 - 60 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
        DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2 - 350, screenHeight / 2 - textSize.y/2 - 60, 40, PINK);
        temp = "Special Mode";
        textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 40, 4);
        DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2 - 350, screenHeight / 2 - textSize.y/2 + 60 , 40, GRAY);
    }
    else
    {
        temp = "Normal Mode";
        textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 40, 4);
        DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2 - 350, screenHeight / 2 - textSize.y/2 - 60, 40, GRAY);
        temp = "Special Mode";
        textSize = MeasureTextEx(GetFontDefault(), temp.c_str(), 40, 4);
        DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x/2 - 350 - 20, screenHeight / 2 - textSize.y/2 + 60 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
        DrawText(temp.c_str(), screenWidth / 2 - textSize.x/2 - 350, screenHeight / 2 - textSize.y/2 + 60, 40, PINK);
    }
    // handle player pos selection if they are playerpos we will change color and draw the background box
    if (mode)
    {
        for (int i = 0; i < size && i < 5; i++)
        {
            Vector2 textSize = MeasureTextEx(GetFontDefault(), TextFormat("%s %i", arr[i].userName.c_str(), arr[i].playerNormalScore[level - 1]), 40, 4);
            DrawText(TextFormat("%s %i", arr[i].userName.c_str(), arr[i].playerNormalScore[level - 1]), screenWidth / 2 - textSize.x/2, i * 65 + 250, 40, GOLD);
        }
    }
    else
    {
        for (int i = 0; i < size && i < 5; i++)
        {
            Vector2 textSize = MeasureTextEx(GetFontDefault(), TextFormat("%s %i", arr[i].userName.c_str(), arr[i].playerSpecialScore[level - 1]), 40, 4);
            DrawText(TextFormat("%s %i", arr[i].userName.c_str(), arr[i].playerSpecialScore[level - 1]), screenWidth / 2 - textSize.x/2, i * 65 + 250, 40, GOLD);
        }
    }
}
/*
    this funtion will be using to handle the choice and using the drawLeaderBoard funtion to 
    draw the right leadboard like the user want to
*/
void displayLeaderBoard(PlayerData *arr, int size, bool &mode, int &level)
{
    // handle the player selection
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
    {
        if (mode == false)
        mode = true;
        else
        mode = false;
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        if (mode == true)
        mode = false;
        else
        mode = true;
    }
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
    {
        if (level == 6)
        level = 1;
        else
        level++;
    }
    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
    {   
        if (level == 1)
        level = 6;
        else
        level--;
    }
    //sort them befor draw them
    switch (level)
    {
        case 1:
            bubbleSort(arr, size, level, mode);
            drawLeaderBoard(arr, size, level, mode);
            break;
        case 2:
            bubbleSort(arr, size, level, mode);
            drawLeaderBoard(arr, size, level, mode);
            break;
        case 3:
            bubbleSort(arr, size, level, mode);
            drawLeaderBoard(arr, size, level, mode);
            break;
        case 4:
            bubbleSort(arr, size, level, mode);
            drawLeaderBoard(arr, size, level, mode);
            break;
        case 5:
            bubbleSort(arr, size, level, mode);
            drawLeaderBoard(arr, size, level, mode);
            break;
        case 6:
            bubbleSort(arr, size, level, mode);
            drawLeaderBoard(arr, size, level, mode);
            break;
    }
}
/*
    dealocate the database this funtion will be used after player exit the leaderBoard
*/
void deallocatePlayerArray(PlayerData* &playerArray, int size)
{
    // if they are alredy empty we dont need to dealocate anymore
    if (playerArray == NULL)
    {
        return;
    }

    //travese through the array to dealocate all the dynamic element in the playerData struct
    for (int i = 0; i < size; ++i)
    {
        //dealloate playerNormalScore array if it not NULL
        if (playerArray[i].playerNormalScore != NULL)
        {
            delete[] playerArray[i].playerNormalScore;
            playerArray[i].playerNormalScore = NULL; //set to NULL after deallocation
        }

        //dealloate playerSpecialScore array if it's not NULL
        if (playerArray[i].playerSpecialScore != NULL)
        {
            delete[] playerArray[i].playerSpecialScore;
            playerArray[i].playerSpecialScore = NULL; //set to null after deallocation
        }
    }
    delete[] playerArray;
    playerArray = NULL;
}
