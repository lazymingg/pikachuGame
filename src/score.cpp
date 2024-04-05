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
    DrawText(TextFormat("SCORE: %i", scoree), 1024/2 - 50, 130, 40, MAROON);
    DrawText(TextFormat("HI-SCORE: %i", hiScore), 1084/2 - 50, 200, 50, BLACK);
    DrawText("Press ENTER to SAVE values", 250, 310, 20, LIGHTGRAY);
    DrawText("Press SPACE to LOAD values", 252, 350, 20, LIGHTGRAY);
}