#include "timer.h"

void displayTimer(float Maxtime, float &timeLeft)
{
    float timerWidth = 500;
    float timerHeight = 50;
    if (timeLeft > Maxtime) timeLeft = Maxtime;
    int percent = timeLeft / Maxtime *100;
    Rectangle timerBlock = {400, 600, timerWidth, timerHeight};
    DrawRectangleLinesEx(timerBlock, 5, RED);
    timerBlock = {400, 600, timerWidth * percent / 100, timerHeight};
    DrawRectangleRec(timerBlock,RED);
}