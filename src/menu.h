/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#ifndef menu
#define menu

#include <iostream>
#include <raylib.h>
#include <string>


using namespace std;



void menuDraw(int choice);
void menuChoice(int &choice);
void levelMenu(int &currentLevel, int maxModeLevel);
void exitMenu(int &exitOption, bool isPlayerInMatch);
#endif
