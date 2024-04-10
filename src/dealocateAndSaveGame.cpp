/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#include "dealocateAndSaveGame.h"

/*
    main funtion to dealocate all the data of the game before exit game :D
*/
void deleteAllDataAndSaveSocore(int *&playerNormalScore, int *&playerSpecialScore, int maxNormalLevel, int maxSpecialLevel, string filePath, string userName, Point* &pointList, Point* &suggestionList, Texture2D *&restexture, int numberOfPicture, Pokemon **&resArr, int row, PlayerData *&dataBase, int dataBaseSize)
{
    saveGame(userName, playerNormalScore, maxNormalLevel, playerSpecialScore, maxSpecialLevel, filePath);
    //dealocate
    cout << "clear point list and suggestion list " << endl;
    clearList(suggestionList);
    clearList(pointList);
    cout << "free table " << endl;
    free2DArray(resArr, row);
    cout << "free texture array" << endl;
    UnloadTextureArray(restexture, numberOfPicture);
    if (playerNormalScore != NULL)
    {
        delete[] playerNormalScore;
        playerNormalScore = NULL;
        cout << "free player Normal score" << endl;
    }
    if (playerSpecialScore != NULL)
    {
        delete[] playerSpecialScore;
        playerSpecialScore = NULL;
        cout << "free player Special Scoree" << endl;
    }
    cout << "dealocate data base" << endl;
    deallocatePlayerArray(dataBase, dataBaseSize);
}