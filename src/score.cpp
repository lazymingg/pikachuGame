/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#include "score.h"

using namespace std;

/*
    this funtion will dis play score when player are playing on gameplay menu
*/
void displayScore(int scoree)
{
    //convert score to string
    string scoreDisplay = to_string(scoree);
    //measure text dimensions
    Vector2 Score = MeasureTextEx(GetFontDefault(), scoreDisplay.c_str(), 40, 4);
    Vector2 title = MeasureTextEx(GetFontDefault(), "SCORE : ", 40, 4);    
    //draw score text on screen
    DrawText("SCORE : ", 200 - title.x/2 - Score.x/2, 600, 40, GRAY);
    DrawText(scoreDisplay.c_str(), 200 + title.x/2 - Score.x/2, 600, 40, GRAY);
}

/*
    this funtion will display hi score and score player achive when they complete a match

*/
void scoreMenu(int scoree, int hiScore)
{
    //get screen dimensions
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    
    // using measuretextex from raylib to get size of the line to center them
    Vector2 textSize = MeasureTextEx(GetFontDefault(),TextFormat("SCORE: %i", scoree), 40, 4);
    Vector2 hiScoreTextSize = MeasureTextEx(GetFontDefault(),TextFormat("HI-SCORE: %i", hiScore), 50, 5);
    
    //draw them in the screen
    DrawText(TextFormat("SCORE: %i", scoree), screenWidth / 2 - textSize.x / 2, 130, 40, GRAY);
    DrawText(TextFormat("HI-SCORE: %i", hiScore), screenWidth / 2 - hiScoreTextSize.x / 2, 200, 50, MAROON);
    
    //draw instruction
    textSize = MeasureTextEx(GetFontDefault(),"Press ENTER to SAVE values", 20, 2);
    DrawText("Press ENTER to SAVE values", screenWidth / 2 - textSize.x / 2, 400, 20, GRAY);
}

/*
    this funtion will display remainning help when player are playing at game play
    menu
*/
void displayRemainingHelp(int remainHelp)
{
    //get screen dimensions
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    
    //display text
    string text = "Remaining Help : ";

    //get size of the text to center them
    Vector2 textSize = MeasureTextEx(GetFontDefault(),TextFormat("%s %i", text.c_str(), remainHelp), 20, 2);
    
    //draw remening help on the screen
    DrawText(TextFormat("%s %i", text.c_str(), remainHelp), 85, 20, 20, GRAY);
    
    //get size to center instructions
    textSize = MeasureTextEx(GetFontDefault(), "Press ESC to pause game or press x key to get some help from meee :D", 20, 2);
    
    //drawn instructions
    DrawText("Press ESC to pause game or press x key to get some help from meee :D", screenWidth / 2 - textSize.x / 2, 660, 20, GRAY);
}
