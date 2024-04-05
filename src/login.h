#ifndef login
#define login

#include <iostream>
#include <raylib.h>
#include <string>
#include <string>
#include <fstream>
// Khai báo biến global
using namespace std;
// Khai báo các hàm
void drawLogin(bool &keyPressed, int &playerSelection, string &userName);
int *readNormalData(string filePath, string userName, int &size);
int *readSpecialData(string filePath, string userName, int &size);
void saveGame(string userName, int *playerNormalData, int maxNormalLevel, int *playerSpecialData, int maxSpecialLevel, string filePath);
void checkAndCreateUser(string filePath, string userName);
void levelUp(int *&playerModeScore, int &maxModeLevel);
void saveScore(int *playerModeScore, int currentLevel, int newScore);
#endif
