/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#include "menu.h"

void menuChoice(int &choice)
{
    // if press key up
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) 
    {
        choice--;
        if (choice < 1) choice = 4; //wrap around
    }
    //if player press keys down
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) 
    {
        choice++;
        if (choice > 4) choice = 1; //wrap around
    }
}
/*
    this funtion will draw a main menu of the game and all option
    a para choice will decide if that choice being colored or not
*/
void menuDraw(int choice)
{
    //get screen size
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    const char *title = "Pikachu The Matching Game :D";
    const char *option1 ="Normal";
    const char *option2 ="Special";
    const char *option3 ="Leader Board";
    const char *option4 ="Go Back";

    Vector2 textSize = MeasureTextEx(GetFontDefault(), title, 40, 4);
    //intialize fade of black color/
    Color fadedColor = Fade(BLACK, 0.5f);
    //draw black grid of the text
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 100 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
    DrawText(title, screenWidth / 2 - textSize.x/2, 100, 40, PINK);

    // handle player choice
    if (choice == 1)
    {
        // draw choice if they are being chose they will have pink color
        textSize = MeasureTextEx(GetFontDefault(), option1, 40, 4);
        DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 200 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
        DrawText(option1, screenWidth / 2 - textSize.x/2, 200, 40, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 40, 4);
        DrawText(option1, screenWidth / 2 - textSize.x/2, 200, 40, GRAY);
    }
    // draw choice if they are being chose they will have pink color
    if (choice == 2)
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 40, 4);
        DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 300 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
        DrawText(option2, screenWidth / 2 - textSize.x/2, 300, 40, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 40, 4);
        DrawText(option2, screenWidth / 2 - textSize.x/2, 300, 40, GRAY);
    }
    // draw choice if they are being chose they will have pink color
    if (choice == 4)
    {
        textSize = MeasureTextEx(GetFontDefault(), option4, 40, 4);
        DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 500 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
        DrawText(option4, screenWidth / 2 - textSize.x/2, 500, 40, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option4, 40, 4);
        DrawText(option4, screenWidth / 2 - textSize.x/2, 500, 40, GRAY);
    }
    // draw choice if they are being chose they will have pink color
    if (choice == 3)
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 40, 4);
        DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 400 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
        DrawText(option3, screenWidth / 2 - textSize.x/2, 400, 40, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 40, 4);
        DrawText(option3, screenWidth / 2 - textSize.x/2, 400, 40, GRAY);
    }
}
/*
    this funtion will draw instruction and all menulevel in a 6 block
*/
void levelMenu(int &currentLevel, int maxModeLevel)
{
    // get screen size
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    // handle player level moving
    if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && currentLevel < maxModeLevel) currentLevel++;
    else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && currentLevel > 1) currentLevel--;

    // draw instruction
    Vector2 textSize;
    textSize = MeasureTextEx(GetFontDefault(),"Use button A to decrease difficulty and button D to increase difficulty.", 20, 2);
    DrawText("Use button A to decrease difficulty and button D to increase difficulty.", screenWidth / 2 - textSize.x / 2, 100, 20, GRAY);
    textSize = MeasureTextEx(GetFontDefault()," You must win the previous level to unlock the next level.", 20, 2);
    DrawText("You must win the previous level to unlock the next level.", screenWidth / 2 - textSize.x / 2, 150, 20, GRAY);
    textSize = MeasureTextEx(GetFontDefault(),"Press Enter to play, Enjoyy :D", 20, 2);
    DrawText("Press Enter to play, Enjoyy :D", screenWidth / 2 - textSize.x / 2, 200, 20, GRAY);
    textSize = MeasureTextEx(GetFontDefault(),"During gameplay, use the WASD keys to move and press Enter to select.", 20, 2);
    DrawText("During gameplay, use the WASD keys to move and press Enter to select.", screenWidth / 2 - textSize.x / 2, 600, 20, GRAY);

    // max level of the game is 6
    const int maxLevel = 6;

    // draw 6 box reference to level
    for (int i = 0; i < maxLevel; i++)
    {
        if (i < currentLevel) DrawRectangle(1024/2 - 105*maxLevel/2 + 105*i, 300, 100, 100, RED);
        DrawRectangleLines(1024/2 - 105*maxLevel/2 + 105*i, 300, 100, 100, MAROON);
    }
    // handdle level case
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
    // draw level information
    textSize = MeasureTextEx(GetFontDefault(), difficulty, 40, 4);
    DrawText(difficulty, screenWidth / 2 - textSize.x/2, 450, 40, GRAY);

}
/*
    this funtion will draw the exit menu 
*/
void exitMenu(int &exitOption, bool isPlayerInMatch)
{
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    
    //set fade color to make background for text
    Color fadedColor = Fade(BLACK, 0.5f);
    
    //draw a semi transparent to make the text more readable
    DrawRectangleRec((Rectangle){0, screenHeight / 2 - 250, screenWidth, 500}, fadedColor);
    
    //define text for choice 
    string text1 = "Are you sure you want to exit the game ?";
    string text2 = "Game paused";
    Vector2 textSize;

    const char *option1 =  "Continue :D";
    const char *option2 = "Go To Menu";
    const char *option3 = "Exit Game";

    //handle player choice
    if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
    {
        if (exitOption == 2)
            exitOption = 0;
        else // Wrap around
            exitOption++;
    }
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        if (exitOption == 0)
            exitOption = 2;
        else // Wrap around
            exitOption--;
    }

    // if player inmatch draw game pause else draw do you want to exit the game
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

    //drawn the exit option
    //exit option will decide if they are player pos or not via color
    if (exitOption == 0)
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);
        DrawText(option1, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 150, 30, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);
        DrawText(option1, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 150, 30, GRAY);
    }
    if (exitOption == 1)
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 30, 3);
        DrawText(option2, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 250, 30, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option2, 30, 3);
        DrawText(option2, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 250, 30, GRAY);
    }
    if (exitOption == 2)
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 30, 3);
        DrawText(option3, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 350, 30, PINK);
    }
    else
    {
        textSize = MeasureTextEx(GetFontDefault(), option3, 30, 3);
        DrawText(option3, screenWidth / 2 - textSize.x/2, screenHeight / 2 - 250 + 350, 30, GRAY);
    }

}