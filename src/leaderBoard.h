/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#ifndef leaderBoard
#define leaderBoard

#include <iostream>
#include <fstream>
#include <raylib.h>
#include <string>
using namespace std;


struct PlayerData
{
    string userName;
    int *playerNormalScore = NULL;
    int maxNormalLevel = 1;
    int *playerSpecialScore = NULL;
    int maxSpecialLevel = 1;
};

PlayerData* readUserData(int &size);
void bubbleSort(PlayerData *arr, int n, int level, bool mode);
void drawLeaderBoard(PlayerData *arr, int size, int level, bool mode);
void displayLeaderBoard(PlayerData *arr, int size, bool &mode, int &level);
void drawLeaderBoard(PlayerData *arr, int size, int level, bool mode);
void deallocatePlayerArray(PlayerData* &playerArray, int size);
#endif
