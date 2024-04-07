#ifndef menu
#define menu

#include <iostream>
#include <raylib.h>
#include <string>
// Khai báo biến global
using namespace std;

// Khai báo các hàm
void menuDraw(int choice);
void menuChoice(int &choice);
void levelMenu(int &currentLevel, int maxNormalLevel);
void exitMenu(int &exitOption, bool isPlayerInMatch);
#endif
