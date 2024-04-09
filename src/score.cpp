#include "score.h"

using namespace std;

std::string intToString(int number) {
    std::string result;
    bool isNegative = false;
    
    // Xử lý trường hợp số âm
    if (number < 0) {
        isNegative = true;
        number = -number;
    }

    // Xử lý trường hợp số 0
    if (number == 0) {
        return "0";
    }

    // Chuyển đổi từ số nguyên thành chuỗi
    while (number > 0) {
        result = char('0' + number % 10) + result;
        number /= 10;
    }

    // Nếu là số âm, thêm dấu âm vào trước
    if (isNegative) {
        result = "-" + result;
    }

    return result;
}
void displayScore(int scoree)
{
        string scoreDisplay = "";
        scoreDisplay = intToString(scoree);
        Vector2 Score = MeasureTextEx(GetFontDefault(), scoreDisplay.c_str(), 40, 4);
        Vector2 title = MeasureTextEx(GetFontDefault(), "SCORE : ", 40, 4);
        DrawText("SCORE : ", 200 - title.x/2 - Score.x/2, 600, 40, GRAY);
        DrawText(scoreDisplay.c_str(), 200 + title.x/2 - Score.x/2, 600, 40, GRAY);

}
void scoreMenu(int scoree, int hiScore)
{

    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    Vector2 textSize = MeasureTextEx(GetFontDefault(),TextFormat("SCORE: %i", scoree), 40, 4);
    DrawText(TextFormat("SCORE: %i", scoree), screenWidth / 2 - textSize.x / 2, 130, 40, MAROON);
    textSize = MeasureTextEx(GetFontDefault(),TextFormat("HI-SCORE: %i", hiScore), 50, 5);
    DrawText(TextFormat("HI-SCORE: %i", hiScore), screenWidth / 2 - textSize.x / 2, 200, 50, BLACK);
    textSize = MeasureTextEx(GetFontDefault(),"Press ENTER to SAVE values", 20, 2);
    DrawText("Press ENTER to SAVE values", screenWidth / 2 - textSize.x / 2, 400, 20, GRAY);
    textSize = MeasureTextEx(GetFontDefault(),"Press SPACE to LOAD values", 20, 2);
    DrawText("Press SPACE to LOAD values", screenWidth / 2 - textSize.x / 2, 500, 20, GRAY);
}
void displayRemainingHelp(int remainHelp)
{
    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();
    string text = "Remaining Help : ";

    Vector2 textSize = MeasureTextEx(GetFontDefault(),TextFormat("%s %i", text.c_str(), remainHelp), 20, 2);
    DrawText(TextFormat("%s %i", text.c_str(), remainHelp), 85, 20, 20, GRAY);
    textSize = MeasureTextEx(GetFontDefault(), "Press ESC to pause game or press x key to get some help from meee :D", 20, 2);
    DrawText("Press ESC to pause game or press x key to get some help from meee :D", screenWidth / 2 - textSize.x / 2, 660, 20, GRAY);


}