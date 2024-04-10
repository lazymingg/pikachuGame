/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/

#include "timer.h"

/*
    this funtion will draw an rectangle timer
*/
void displayTimer(float Maxtime, float &timeLeft)
{
    //set the width and height of the timer display
    float timerWidth = 500;
    float timerHeight = 35;

    // make sure that timeLeft does not exceed maxtime
    if (timeLeft > Maxtime) 
        timeLeft = Maxtime;

    //calculate the percentage of time left
    int percent = timeLeft / Maxtime * 100;

    //define the rectangle representing the timer bar outline
    Rectangle timerBlock = {400, 600, timerWidth, timerHeight};

    //draw the outline of the timer bar
    DrawRectangleLinesEx(timerBlock, 3, RED);

    //define the rectangle representing the filled portion of the timer bar based on the percentage of time left
    timerBlock = {400, 600, timerWidth * percent / 100, timerHeight};

    //draw the filled portion of the timer bar
    DrawRectangleRec(timerBlock, RED);
}