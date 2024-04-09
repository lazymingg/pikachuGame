#ifndef dealocateAndSaveGame
#define dealocateAndSaveGame


#include "gameplay.h"
#include "leaderBoard.h"
#include "score.h"
#include "timer.h"
#include "login.h"
#include "menu.h"


void deleteAllDataAndSaveSocore(int *&playerNormalScore, int *&playerSpecialScore, int maxNormalLevel, int maxSpecialLevel, string filePath, string userName, Point* &pointList, Point* &suggestionList, Texture2D *&restexture, int numberOfPicture, Pokemon **&resArr, int row, PlayerData *&dataBase, int dataBaseSize);
#endif
