#ifndef menu
#define menu

#include <iostream>
#include <raylib.h>

// Khai báo biến global
extern int myGlobalVariable;

// Khai báo các hàm
void menuDraw(int choice);
void menuChoice(int &choice);
void levelMenu(int &currentLevel, int maxNormalLevel);
#endif
