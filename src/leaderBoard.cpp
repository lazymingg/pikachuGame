#include "leaderBoard.h"

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
void drawLeaderBoard(PlayerData *arr, int size, int level, bool mode)
{
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
void displayLeaderBoard(PlayerData *arr, int size, bool &mode, int &level)
{
    if (IsKeyPressed(KEY_S))
    {
        if (mode == false)
        mode = true;
        else
        mode = false;
    }
    if (IsKeyPressed(KEY_W))
    {
        if (mode == true)
        mode = false;
        else
        mode = true;
    }
    if (IsKeyPressed(KEY_D))
    {
        if (level == 6)
        level = 1;
        else
        level++;
    }
    if (IsKeyPressed(KEY_A))
    {   
        if (level == 1)
        level = 6;
        else
        level--;
    }
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
void deallocatePlayerArray(PlayerData* &playerArray, int size)
{
    // Kiểm tra nếu playerArray là NULL thì không cần giải phóng bộ nhớ
    if (playerArray == NULL)
    {
        return;
    }

    // Duyệt qua từng phần tử của mảng và giải phóng bộ nhớ
    for (int i = 0; i < size; ++i)
    {
        // Dealloate playerNormalScore array if it's not NULL
        if (playerArray[i].playerNormalScore != NULL)
        {
            delete[] playerArray[i].playerNormalScore;
            playerArray[i].playerNormalScore = NULL; // Set to NULL after deallocation
        }

        // Dealloate playerSpecialScore array if it's not NULL
        if (playerArray[i].playerSpecialScore != NULL)
        {
            delete[] playerArray[i].playerSpecialScore;
            playerArray[i].playerSpecialScore = NULL; // Set to NULL after deallocation
        }
    }
    // Giải phóng bộ nhớ của mảng con trỏ
    delete[] playerArray;
    playerArray = NULL;
}
