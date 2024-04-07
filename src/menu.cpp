#include "menu.h"


// Định nghĩa các hàm
void menuChoice(int &choice)
{
    // Nếu người dùng nhấn nút lên
    if (IsKeyPressed(KEY_W)) 
    {
        choice--;
        if (choice < 1) choice = 4; // Wrap-around
    }
    // Nếu người dùng nhấn nút xuống
    else if (IsKeyPressed(KEY_S)) 
    {
        choice++;
        if (choice > 4) choice = 1; // Wrap-around
    }
}

void menuDraw(int choice)
{
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    const char *title = "Pikachu The Matching Game :D";
    const char *option1 ="Normal";
    const char *option2 ="Special";
    const char *option3 ="Leader Board";
    const char *option4 ="Go Back";

    Vector2 textSize = MeasureTextEx(GetFontDefault(), title, 40, 4);
    DrawText(title, screenWidth / 2 - textSize.x/2, 100, 40, GRAY);

    if (choice == 1)
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 40, 4);
        DrawText(option1, screenWidth / 2 - textSize.x/2, 200, 40, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 40, 4);
        DrawText(option1, screenWidth / 2 - textSize.x/2, 200, 40, GRAY);
    }
    if (choice == 2)
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 40, 4);
        DrawText(option2, screenWidth / 2 - textSize.x/2, 300, 40, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 40, 4);
        DrawText(option2, screenWidth / 2 - textSize.x/2, 300, 40, GRAY);
    }
    if (choice == 4)
    {
        textSize = MeasureTextEx(GetFontDefault(), option4, 40, 4);
        DrawText(option4, screenWidth / 2 - textSize.x/2, 500, 40, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option4, 40, 4);
        DrawText(option4, screenWidth / 2 - textSize.x/2, 500, 40, GRAY);
    }
    if (choice == 3)
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 40, 4);
        DrawText(option3, screenWidth / 2 - textSize.x/2, 400, 40, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 40, 4);
        DrawText(option3, screenWidth / 2 - textSize.x/2, 400, 40, GRAY);
    }
}

void levelMenu(int &currentLevel, int maxNormalLevel)
{
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    if (IsKeyPressed(KEY_D) && currentLevel < maxNormalLevel) currentLevel++;
    else if (IsKeyPressed(KEY_A) && currentLevel > 1) currentLevel--;

    const int maxLevel = 6;

    for (int i = 0; i < maxLevel; i++)
    {
        if (i < currentLevel) DrawRectangle(1024/2 - 105*maxLevel/2 + 105*i, 300, 100, 100, RED);
        DrawRectangleLines(1024/2 - 105*maxLevel/2 + 105*i, 300, 100, 100, MAROON);
    }

    const char* difficulty = "";
    switch (currentLevel)
    {
        case 1:
            difficulty = "Very Easy";
            break;
        case 2:
            difficulty = "Easy";
            break;
        case 3:
            difficulty = "Medium";
            break;
        case 4:
            difficulty = "Hard";
            break;
        case 5:
            difficulty = "strict";
            break;
        case 6:
            difficulty = "You are Insane :D";
            break;
    }

    Vector2 textSize = MeasureTextEx(GetFontDefault(), difficulty, 40, 4);
    DrawText(difficulty, screenWidth / 2 - textSize.x/2, 450, 40, GRAY);

}
void exitMenu(int &exitOption, bool isPlayerInMatch)
{
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    DrawRectangle(0, screenHeight / 2 - 250, screenWidth, 500, BLACK);
    string text1 = "Are you sure you want to exit the game ?";
    string text2 = "Game paused";
    Vector2 textSize;

    const char *option1 =  "Continue :D";
    const char *option2 = "Go To Menu";
    const char *option3 = "Exit Game";

    if (IsKeyPressed(KEY_S))
    {
        if (exitOption == 2)
        exitOption = 0;
        else // wrap around
        exitOption++;
    }
    if (IsKeyPressed(KEY_W))
    {
        if (exitOption == 0)
        exitOption = 2;
        else // wrap around
        exitOption--;
    }

    if (isPlayerInMatch)
    {
        textSize = MeasureTextEx(GetFontDefault(), text2.c_str(), 30, 3);
        DrawText(text2.c_str(), screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 70 , 30, WHITE);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), text1.c_str(), 30, 3);
        DrawText(text1.c_str(), screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 70 , 30, WHITE);
    }

    if (exitOption == 0)
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);
        DrawText(option1, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 150, 30, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);
        DrawText(option1, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 150, 30, GRAY);
    }
    if (exitOption == 1)
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 30, 3);
        DrawText(option2, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 250, 30, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 30, 3);
        DrawText(option2, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 250, 30, GRAY);
    }
    if (exitOption == 2)
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 30, 3);
        DrawText(option3, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 350, 30, RED);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 30, 3);
        DrawText(option3, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 350, 30, GRAY);
    }

}