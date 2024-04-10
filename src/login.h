/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#ifndef login
#define login

#include <iostream>
#include <raylib.h>
#include <string>
#include <fstream>

using namespace std;


void drawLogin(bool &keyPressed, int &playerSelection, string &userName);
int *readNormalData(string filePath, string userName, int &size);
int *readSpecialData(string filePath, string userName, int &size);
void saveGame(string userName, int *playerNormalData, int maxNormalLevel, int *playerSpecialData, int maxSpecialLevel, string filePath);
void checkAndCreateUser(string filePath, string userName);
void levelUp(int *&playerModeScore, int &maxModeLevel);
void saveScore(int *playerModeScore, int currentLevel, int newScore);
#endif
