/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#ifndef gameplay
#define gameplay 

#include <raylib.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string.h>

using namespace std;

// struct
struct Pokemon
{
    bool deleted = false;
    bool selected = false;
    int key = 0;
};
/*
    this struct using to store the point for the line drawing job
*/
struct Point
{
    int x;
    int y;
    Point *next;
};

void specialModeColasp(Pokemon **pokeArr, int row, int col);
void UnloadTextureArray(Texture2D* textureArray, int arraySize);
void free2DArray(Pokemon** &arr, int rows);
void clearList(Point *&head);
void drawLine(Point* pHead, int scaledWidth, int scaledHeight);
void addTail(Point* &pHead, int x, int y);
Point* uMatching (Pokemon **pokeArr, int row, int col, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY);
Point *zMatching(Pokemon **pokeArr, int x_1, int y_1, int x_2, int y_2);
Point *lMatching(Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY);
Point* iMatching (Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY);
Texture2D* readImage(const int nPicture);

void swapPokemon(Pokemon& p1, Pokemon& p2);
void shufflePokemonArray(Pokemon* pokemonArray, int size);
void createTable(Pokemon** &resArr, int row, int col, int nPicture);
void drawTable(Pokemon **a, int row, int col, const int scaledWidth, const int scaledHeight, int playerPosX, int playerPosY, Texture2D *texture);
void deleteCell(Pokemon **a, int deletePosX, int deletePosY);
int calScore(int x_1, int y_1, int x_2, int y_2, char key);
void updateTable(Pokemon **pokeArr, int &playerPosX, int &playerPosY, int row, int col, bool &firstSelectionDone, int &selectedX, int &selectedY, Point* &pointList, float &matchingTime, int &scoree, bool &isMatching, int &framesCounter);
bool suggestion(Pokemon **pokeArr, int row, int col, Point *&pointList);
bool suggestionButItJustForDeveloper(Pokemon **pokeArr, int row, int col, Point *&pointList, float &matchingTime);
bool checkEmpty(Pokemon **pokeArr, int row, int col);
void shuffle_array_2d(Pokemon **arr, int row, int col);
#endif
