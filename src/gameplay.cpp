/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/

#include "gameplay.h"

/*
    thís funtion aim to delete dynamic texture array and unload texture using
    Unloaded Texture frome raylib
*/
void UnloadTextureArray(Texture2D* textureArray, int arraySize)
{
    for (int i = 0; i < arraySize; ++i)
    {
        UnloadTexture(textureArray[i]);
    }

    delete[] textureArray;
}
// free 2d dynamic array
void free2DArray(Pokemon** &arr, int rows)
{
    // is empty arr
    if (arr == NULL) return;
    
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    // dealocate
    delete[] arr;
    arr = NULL;
}

// create point Nodes
Point* createNodes(int x, int y)
{
    //tao nodes
    Point *newNodes = new Point;
    // gan gia tri
    newNodes -> x = x;
    newNodes -> y = y;
    newNodes -> next = NULL;
    return newNodes;
}
// clear Point list
void clearList(Point *&head)
{
    // if list empty pause
    if (head == NULL)
    return;

    while (head != nullptr)
    {
        Point *temp = head; 
        head = head->next; 
        delete temp;
    }
    // head = NULL to orther recoznize that list is empty
    head = NULL;
}

// add nodes to the end of list
void addTail(Point* &pHead, int x, int y)
{
    Point *add = new Point;
    add->x = x;
    add->y = y;
    add->next = NULL;
    if (!pHead) pHead = add;
    else {
        Point *pCur = pHead;
        while (pCur->next) pCur = pCur->next;
        pCur->next = add;
    }
}
/*
    this funtion aim to do the special mode which if there is a empty row or an empty col
    every element will be move up or to left 
*/
void specialModeColasp(Pokemon **pokeArr, int row, int col)
{
    //move every element to the left 
    for (int i = 1; i < col - 1; i++)
    {
        bool isColEmpty = true;

        for (int j = 1; j < row - 1; j++)
        {
            if (pokeArr[j][i].deleted == false)
            {
                isColEmpty = false;
                break;
            }
        }
        // if col empty move every element to left
        if (isColEmpty)
        {
            for (int s = i; s < col - 2; s++)
            {
                for (int k = 0; k < row - 1 ; k++)
                {
                    swap(pokeArr[k][s], pokeArr[k][s + 1]);
                }
            }
            col--; // reduce col if not have this there will be and infinire loop
            i--;
        }
    }

    //move element up
    for (int i = 1; i < row - 1; i++)
    {
        bool isRowEmpty = true;

        for (int j = 1; j < col - 1; j++)
        {
            if (pokeArr[i][j].deleted == false)
            {
                isRowEmpty = false;
                break;
            }
        }
        // if have row empty move every element up
        if (isRowEmpty)
        {
            for (int s = i; s < row - 2; s++)
            {
                for (int k = 1; k < col - 1 ; k++)
                {
                    swap(pokeArr[s][k], pokeArr[s + 1][k]);
                }
            }
            row--; // reduce row if not have this there will be and infinire loop
            i--;
        }
    }
}


/**********************************U I Z L maching*************************************/
Point* uMatching (Pokemon **pokeArr, int row, int col, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key)
        return NULL;
    if (playerPosX == playerPosXX && playerPosY == playerPosYY)
        return NULL;
    if (pokeArr[playerPosY][playerPosX].deleted == true || pokeArr[playerPosYY][playerPosXX].deleted == true)
        return NULL;
    // Chuẩn bị các tham số cần thiết
    Point* pHead = NULL;
    int minx, maxx, miny, maxy;
    if (playerPosX < playerPosXX){
        minx = playerPosX;
        maxx = playerPosXX;
    } else {
        minx = playerPosXX;
        maxx = playerPosX;
    }
    if (playerPosY < playerPosYY){
        miny = playerPosY;
        maxy = playerPosYY;
    } else {
        miny = playerPosYY;
        maxy = playerPosY;
    }
    // Check U trái
    for (int i = minx - 1; i >= 0 && pokeArr[playerPosY][i].deleted == true && pokeArr[playerPosYY][i].deleted == true; i--){
        bool valid = true;
        for (int j = i; j < playerPosX; j++){
            if (pokeArr[playerPosY][j].deleted == false){
                valid = false;
                break;
            }
        }
        if (valid){
            for (int j = i; j < playerPosXX; j++){
                if (pokeArr[playerPosYY][j].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            for (int j = miny; j < maxy + 1; j++){
                if (pokeArr[j][i].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            addTail(pHead, playerPosX, playerPosY);
            addTail(pHead, i, playerPosY);
            addTail(pHead, i, playerPosY);
            addTail(pHead, i, playerPosYY);
            addTail(pHead, i, playerPosYY);
            addTail(pHead, playerPosXX, playerPosYY);
            return pHead;
        }
    }
    // Check U phải
    for (int i = maxx + 1; i < col && pokeArr[playerPosY][i].deleted == true && pokeArr[playerPosYY][i].deleted == true; i++){
        bool valid = true;
        for (int j = i; j > playerPosX; j--){
            if (pokeArr[playerPosY][j].deleted == false){
                valid = false;
                break;
            }
        }
        if (valid){
            for (int j = i; j > playerPosXX; j--){
                if (pokeArr[playerPosYY][j].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            for (int j = miny; j < maxy + 1; j++){
                if (pokeArr[j][i].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            addTail(pHead, playerPosX, playerPosY);
            addTail(pHead, i, playerPosY);
            addTail(pHead, i, playerPosY);
            addTail(pHead, i, playerPosYY);
            addTail(pHead, i, playerPosYY);
            addTail(pHead, playerPosXX, playerPosYY);
            return pHead;
        }
    }
    // Check U trên
    for (int i = miny - 1; i >= 0 && pokeArr[i][playerPosX].deleted == true && pokeArr[i][playerPosXX].deleted == true; i--){
        bool valid = true;
        for (int j = i; j < playerPosY; j++){
            if (pokeArr[j][playerPosX].deleted == false){
                valid = false;
                break;
            }
        }
        if (valid){
            for (int j = i; j < playerPosYY; j++){
                if (pokeArr[j][playerPosXX].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            for (int j = minx; j < maxx + 1; j++){
                if (pokeArr[i][j].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            addTail(pHead, playerPosX, playerPosY);
            addTail(pHead, playerPosX, i);
            addTail(pHead, playerPosX, i);
            addTail(pHead, playerPosXX, i);
            addTail(pHead, playerPosXX, i);
            addTail(pHead, playerPosXX, playerPosYY);
            return pHead;
        }
    }
    // Check U dưới
    for (int i = maxy + 1; i < row && pokeArr[i][playerPosX].deleted == true && pokeArr[i][playerPosXX].deleted == true; i++){
        bool valid = true;
        for (int j = i; j > playerPosY; j--){
            if (pokeArr[j][playerPosX].deleted == false){
                valid = false;
                break;
            }
        }
        if (valid){
            for (int j = i; j > playerPosYY; j--){
                if (pokeArr[j][playerPosXX].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            for (int j = minx; j < maxx + 1; j++){
                if (pokeArr[i][j].deleted == false){
                    valid = false;
                    break;
                }
            }
        }
        if (valid){
            addTail(pHead, playerPosX, playerPosY);
            addTail(pHead, playerPosX, i);
            addTail(pHead, playerPosX, i);
            addTail(pHead, playerPosXX, i);
            addTail(pHead, playerPosXX, i);
            addTail(pHead, playerPosXX, playerPosYY);
            return pHead;
        }
    }
    return NULL;
}
Point *zMatching(Pokemon **pokeArr, int x_1, int y_1, int x_2, int y_2){
    if (pokeArr[y_1][x_1].key != pokeArr[y_2][x_2].key)
        return NULL;
    if (x_1 == x_2 || y_1 == y_2)
        return NULL;
    if (pokeArr[y_1][x_1].deleted == true || pokeArr[y_2][x_2].deleted == true)
        return NULL;
    Point *pHead = NULL;
    // Tráo thành 1 trái, 2 phải
    if (x_1 > x_2){
        swap(x_1, x_2);
        swap(y_1, y_2);
    }
    // Chọn mode: 1 là 1 dưới 2, 2 là 1 trên 2
    int mode;
    if (y_1 > y_2) mode = 1;
    else mode = 2; 
    if (mode == 1){
        // Mode 1 : 2 dọc 1 ngang
        for (int i = y_1 - 1; i > y_2; i--){
            bool valid = true;
            for (int j = i; j < y_1; j++){
                if (pokeArr[j][x_1].deleted == false){
                    valid = false;
                    break;
                }
            }
            if (valid){
                for (int j = i; j > y_2; j--){
                    if (pokeArr[j][x_2].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                for (int j = x_1; j < x_2 + 1; j++){
                    if (pokeArr[i][j].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                addTail(pHead, x_1, y_1);
                addTail(pHead, x_1, i);
                addTail(pHead, x_1, i);
                addTail(pHead, x_2, i);
                addTail(pHead, x_2, i);
                addTail(pHead, x_2, y_2);
                return pHead;
            }
        }
        // Mode 1 : 2 ngang 1 dọc
        for (int i = x_1 + 1; i < x_2; i++){
            bool valid = true;
            for (int j = i; j > x_1; j--){
                if (pokeArr[y_1][j].deleted == false){
                    valid = false;
                    break;
                }
            }
            if (valid){
                for (int j = i; j < x_2; j++){
                    if (pokeArr[y_2][j].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                for (int j = y_1; j > y_2 - 1; j--){
                    if (pokeArr[j][i].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                addTail(pHead, x_1, y_1);
                addTail(pHead, i, y_1);
                addTail(pHead, i, y_1);
                addTail(pHead, i, y_2);
                addTail(pHead, i, y_2);
                addTail(pHead, x_2, y_2);
                return pHead;
            }
        }
    } else if (mode == 2){
        // Mode 2 : 2 dọc 1 ngang
        for (int i = y_1 + 1; i < y_2; i++){
            bool valid = true;
            for (int j = i; j > y_1; j--){
                if (pokeArr[j][x_1].deleted == false){
                    valid = false;
                    break;
                }
            }
            if (valid){
                for (int j = i; j < y_2; j++){
                    if (pokeArr[j][x_2].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                for (int j = x_1; j < x_2 + 1; j++){
                    if (pokeArr[i][j].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                addTail(pHead, x_1, y_1);
                addTail(pHead, x_1, i);
                addTail(pHead, x_1, i);
                addTail(pHead, x_2, i);
                addTail(pHead, x_2, i);
                addTail(pHead, x_2, y_2);
                return pHead;
            }
        }
        // Mode 2 : 2 ngang 1 dọc
        for (int i = x_1 + 1; i < x_2; i++){
            bool valid = true;
            for (int j = i; j > x_1; j--){
                if (pokeArr[y_1][j].deleted == false){
                    valid = false;
                    break;
                }
            }
            if (valid){
                for (int j = i; j < x_2; j++){
                    if (pokeArr[y_2][j].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                for (int j = y_1; j < y_2 + 1; j++){
                    if (pokeArr[j][i].deleted == false){
                        valid = false;
                        break;
                    }
                }
            }
            if (valid){
                addTail(pHead, x_1, y_1);
                addTail(pHead, i, y_1);
                addTail(pHead, i, y_1);
                addTail(pHead, i, y_2);
                addTail(pHead, i, y_2);
                addTail(pHead, x_2, y_2);
                return pHead;
            }
        }
    }
    return NULL;
}
/*
    L matching checking funtion if they are matching return a point list reference to the L case for drawing job
*/
Point *lMatching(Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    // ignore if they are not same or if they are one
    // base conditon
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key || playerPosXX == playerPosX && playerPosY == playerPosYY)
    return NULL;
    if (pokeArr[playerPosY][playerPosX].deleted == true || pokeArr[playerPosYY][playerPosXX].deleted == true) return NULL;

    // gennrate head for point list
    Point* pHead = NULL;

    // make sure that playerPosX, playerPosY is the location of the left in one of two pokemon
    if (playerPosX > playerPosXX)
    {
        swap(playerPosX, playerPosXX);
        swap(playerPosY, playerPosYY);
    }
    
    // if the last one pokemon in right have taller location
    if (playerPosYY < playerPosY)
    {
        // case go ringht and go up
        // travese from fist point to right
        for (int i = 1; i <= playerPosXX - playerPosX; i++)
        {
            // access through the right if blocked then switch to another case
            if (pokeArr[playerPosY][playerPosX + i].deleted == false)
            break; 

            //stop travese
            if (i == playerPosXX - playerPosX)
            {
                // travese up
                for (int j = 0; j < playerPosY - playerPosYY; j++)
                {
                    //access through the right if blocked then switch to another case
                    if (pokeArr[playerPosY - j][playerPosX + i].deleted == false)
                    {
                        break;
                    }
                    // if not being blocked return point list
                    if (j == playerPosY - playerPosYY - 1)
                    {
                        // create point list
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }

        // go up and go right case
        // travese up
        for (int i = 1; i <= playerPosY - playerPosYY; i++)
        {
            // if being blocked switch to another case
            if (pokeArr[playerPosY - i][playerPosX].deleted == false)
            break;

            // if have the same Y location continue to travese right
            if (i == playerPosY - playerPosYY)
            {
                // travese to right till meet the last pokemon
                for (int j = 0; j < playerPosXX - playerPosX; j++)
                {
                    // if being blocked switch to another case
                    if (pokeArr[playerPosY - i][playerPosX + j].deleted == false)
                    {
                        break;
                    }
                    // if not being blocked create point list and return point list
                    if (j == playerPosXX - playerPosX - 1)
                    {
                        // gán điểm 
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX, playerPosY - i);
                        addTail(pHead, playerPosX, playerPosY - i);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }

    }
    //  if the last one in right have location lower then the first in left
    if (playerPosYY > playerPosY)
    {
        // travese to right till have same x value
        for (int i = 1; i <= playerPosXX - playerPosX; i++)
        {

            // if being blocked switch to another case
            if (pokeArr[playerPosY][playerPosX + i].deleted == false)
            break;
            // when have same x location continue travese down 
            if (i == playerPosXX - playerPosX)
            {
                // travese down till meet the last pokemon
                for (int j = 0; j < playerPosYY - playerPosY; j++)
                {
                    // if being blocked switch to another case
                    if (pokeArr[playerPosY + j][playerPosX + i].deleted == false)
                    {
                        break;
                    }
                    // if not being blocked input point to list and return list
                    if (j == playerPosYY - playerPosY - 1)
                    {
                        // gán điểm 
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY );
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }
        // case go down then go right
        // travese down till have same y location
        for (int i = 1; i <= playerPosYY - playerPosY; i++)
        {
            //if being blocked switch to another case
            if (pokeArr[playerPosY + i][playerPosX].deleted == false)
            break;
            // if have same y location continue travese to right
            if (i == playerPosYY - playerPosY)
            {
                // travese to right till meet the last pokemon
                for (int j = 0; j < playerPosXX - playerPosX; j++)
                {
                    // if being blocked switch to another case
                    if (pokeArr[playerPosY + i][playerPosX + j].deleted == false)
                    {
                        break;
                    }
                    // if not being blocked input point to list and return list
                    if (j == playerPosXX - playerPosX - 1)
                    {
                        // gán điểm 
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX, playerPosY + i);
                        addTail(pHead, playerPosX, playerPosY + i);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }
    }
    return NULL;
}
/*
    I matching cheking funtion if they matching this funtion will return a point list using linked list
    to reference to the line for drawing job
*/
Point* iMatching (Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    // ignore if they are not same or if they are one
    // base conditon
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key || playerPosX == playerPosXX && playerPosY == playerPosYY) return NULL;
    if (pokeArr[playerPosY][playerPosX].deleted == true || pokeArr[playerPosYY][playerPosXX].deleted == true) return NULL;

    // create point list 
    Point *pHead = NULL;
    // if they have same y location
    if (playerPosY == playerPosYY)
    {    
        if (playerPosX > playerPosXX) swap(playerPosX, playerPosXX);
        //travese to right
        for (int i = playerPosX + 1; i < playerPosXX; i++)
        {
            if (pokeArr[playerPosY][i].deleted == false) return NULL;
        }
        // input point for list and return  
        pHead = createNodes(playerPosX, playerPosY);
        pHead -> next = createNodes(playerPosXX,playerPosYY);
        return pHead;
    }
    // if they have same y location
    if (playerPosXX == playerPosX)
    {
        if (playerPosY > playerPosYY) swap(playerPosY, playerPosYY);
        // travese down
        for (int i = playerPosY + 1; i < playerPosYY; i++)
        {
            if (pokeArr[i][playerPosX].deleted == false) return NULL;
        }
        // input point for list then return
        pHead = createNodes(playerPosX, playerPosY);
        pHead -> next = createNodes(playerPosXX,playerPosYY);
        return pHead;
    }
    // if not i matching return NULL
    return NULL;
}

/**********************************************************************************************************************************/


/*
    after matching or suggest list it provided this funtion aim to draw all the line conneted by two point in linklist (point list)
*/
void drawLine(Point* pHead, int scaledWidth, int scaledHeight)
{
    // base case if empty return
    if (pHead == NULL) return;

    Point *pCur = pHead->next;
    Point *pPrev = pHead;

    // travese and draw all point 
    while (pCur != NULL)
    {
        // get two point to to draw a line
        Vector2 point1 = {(pPrev->x * (scaledWidth + 5) + scaledWidth / 2), (pPrev->y * (scaledHeight + 5) + scaledHeight / 2)};
        Vector2 point2 = {(pCur->x * (scaledWidth + 5) + scaledWidth / 2), (pCur->y * (scaledHeight + 5) + scaledHeight / 2)};
        // draw a circle in point of intersection of two line
        DrawCircle((pPrev->x * (scaledWidth + 5) + scaledWidth / 2), (pPrev->y * (scaledHeight + 5) + scaledHeight / 2), 5, BLUE);
        // draw line
        DrawLineEx(point1, point2, 3, BLUE);// Ve duong thang
        // draw a circle in point of intersection of two line
        DrawCircle((pCur->x * (scaledWidth + 5) + scaledWidth / 2), (pCur->y * (scaledHeight + 5) + scaledHeight / 2), 5, BLUE);

        // check if is there have another line or not
        if (pCur -> next)
        {
            pPrev = pPrev -> next -> next;
            pCur = pCur -> next -> next;
        }
        // if there is not remaining line loop again to draw line
        else 
        {
            pCur = pHead->next;
            pPrev = pHead;
            break;
        }
    }
}

/*
    read (n)image name "image.(i)" and return a dymanic texture array
    texture is a funtion provided by raylib graphics libary
*/
Texture2D* readImage(const int nPicture)
{
    //location to your picture
    const string path = "src/croppic/";
    const string picNameBase = "image";//pic name base
    Texture2D *resTexture = new Texture2D[nPicture];

    // Load image
    for (int i = 0; i < nPicture; i++)
    {
        string tempName = picNameBase + to_string(i) + ".png"; //picname
        string picName = path + tempName; //  name with location

        Image image = LoadImage(picName.c_str());//load image
        resTexture[i] = LoadTextureFromImage(image);//load texture from image
        UnloadImage(image);// delete image after load
    }
    //return ressult dynamic result texture array
    return resTexture;
}
/*
becasue swap(pokemon[i], pokemon[j]) may erors becasue 
they are struct and my teacher say that we should not do that 
*/
void swapPokemon(Pokemon& p1, Pokemon& p2)
{
    using std::swap; // Import swap

    swap(p1.deleted, p2.deleted);
    swap(p1.selected, p2.selected);
    swap(p1.key, p2.key);
}
/*
    this funtion using Fisher-Yates shuffle algorithm
    i take this from chat GPT, openAI
*/
void shufflePokemonArray(Pokemon* pokemonArray, int size) {
    // Random seed
    srand(time(NULL));

    // Start from the last element and move backwards
    for (int i = size - 1; i > 0; --i) {
        // Choose a random element in the range from 0 to i
        int j = rand() % (i + 1);

        // Swap the values of element i and j
        swapPokemon(pokemonArray[i], pokemonArray[j]);
    }
}


/*
    this funtion create a dynamic 2d Array to store pokemon
    and random it
*/
void createTable(Pokemon** &resArr, int row, int col, int nPicture)
{   
    //seed random
    srand(time(0));
    int randomNumber = 0;

    //gennerate arr 1 dimarr
    int size = (row - 2)*(col - 2);
    Pokemon *temp = new Pokemon[size];

    //random Image via key and input two neighboring element
    for (int i = 0; i < size;)
    {
        randomNumber = rand() % nPicture;
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        i++;
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        i++; 
    }
    // shufle the one dim array
    // i like to shuffle two times =))
    shufflePokemonArray(temp, size);
    shufflePokemonArray(temp, size);
    
    // create 2D array 
    resArr = new Pokemon*[row];

    for (int i = 0; i < row; i++)
    {
        resArr[i] = new Pokemon[col];
    }

    //input all element fromt one dim arr have been shuffle 
    // to 2D array but here we dont input on the grid of the 2d array 
    // to get more easy when building all matching algolrithm
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // input delete = true on the grid of the array
            if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
            {
                resArr[i][j].deleted = true;
                resArr[i][j].key = 0;
            }
            else
            {
                resArr[i][j].deleted = temp[count].deleted;
                resArr[i][j].key = temp[count].key;
                count++;
            }
        }
    }
    //free the one dim arr
    delete[] temp;
}
/*
    this funtion aim to draw the table where the player will see all
    the pokemon to play and draw player pos via the rectangle line
*/
void drawTable(Pokemon **a, int row, int col, const int scaledWidth, const int scaledHeight, int playerPosX, int playerPosY, Texture2D *texture)
{

    //travese 2d Array
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            // draw all the poke are not being delete
            if(a[i][j].deleted == false)
            {

                //sourceRec is a size of source image destRec, is size of the out put image
                Rectangle sourceRec = { 0, 0, (texture[a[i][j].key]).width, (texture[a[i][j].key]).height };
                Rectangle destRec = { j * (scaledWidth + 5), i * (scaledHeight + 5), scaledWidth, scaledHeight};
                //dest line rec is the size of the rectangle line display the playerPos
                Rectangle destLineRec = { j * (scaledWidth + 5) - 5, i * (scaledHeight + 5) - 5, scaledWidth + 10, scaledHeight + 10};

                // draw poke
                DrawTexturePro(texture[a[i][j].key], sourceRec, destRec, {0, 0}, 0, WHITE);
                // if they are being selected draw a grid rectangle
                if (a[i][j].selected == true)
                {
                    DrawRectangleLinesEx(destLineRec, 9, ORANGE);
                }

            }
            // or if player pos are there draw a rectangle grid to player know
            if ((j == playerPosX && i == playerPosY))
            {
                Rectangle destLineRec = { j * (scaledWidth + 5) - 5, i * (scaledHeight + 5) - 5, scaledWidth + 10, scaledHeight + 10};
                DrawRectangleLinesEx(destLineRec, 9, ORANGE);
            }

        }
    }
}
//delete pokemon element
void deleteCell(Pokemon **a, int deletePosX, int deletePosY)
{
    a[deletePosY][deletePosX].deleted = true;
}
/*
    this funtion aim to cal score of the player depend on the distance of the 
    two matching point and the matching type
*/
int calScore(int x_1, int y_1, int x_2, int y_2, char key)
{
    // the distance of two point
    int x = x_2 - x_1, y = y_2 - y_1;
    // if they a negative turning they to positive
    if (x < 0) x = 0 - x;
    if (y < 0) y = 0 - y;
    //score depend on matching type
    switch(key)
    {
        case 'i' : return (x + y)*5 + 10;
        case 'l' : return (x + y)*5 + 30;
        case 'u' : return (x + y)*5 + 30;
        case 'z' : return (x + y)*5 + 30;
    }
    return 0;
}
/*
    this is the soul of the game this funtion handling all case of matching, calc score, and out put
    time where the line should be draw, update player moving and player selection, update point list and delete it prev list before
    create new one

    there also have feature which when player hold moving keys they will go more faster
    because this funtion is very important and hard to understand so i give you a brief
    decription about all the parameter of this funtion 

    pokeArr       2D array containing information about the Pokemon on the table.
    playerPosX    Reference to the current x-coordinate of the player on the table.
    playerPosY    Reference to the current y-coordinate of the player on the table.
    row           Number of rows in the game table.
    col           Number of columns in the game table.
    firstSelectionDone    Flag indicating whether the player has selected the first Pokemon.
    selectedX     Reference to the x-coordinate of the selected Pokemon.
    selectedY     Reference to the y-coordinate of the selected Pokemon.
    pointList     Pointer to the list of connecting points between selected Pokemon we will return this list for
    a draw line out side this funtion to draw that line
    matchingTime  Reference to the time when the matching occurs.
    scoree        Reference to the player's score.
    isMatching    Flag indicating whether the selected Pokemon are forming a valid pair.
    framesCounter Reference to the counter for frames elapsed since last key press.
*/
void updateTable(Pokemon **pokeArr, int &playerPosX, int &playerPosY, int row, int col, bool &firstSelectionDone, int &selectedX, int &selectedY, Point* &pointList, float &matchingTime, int &scoree, bool &isMatching, int &framesCounter)
{
    //create temp point list
    Point* temp = NULL;
    // check is player press any key 
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_A) || IsKeyDown(KEY_W) || IsKeyDown(KEY_S) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_ENTER) || IsKeyDown(KEY_SPACE))
    {
        //increment the frames counter
        framesCounter += 1;
        //if frames counter is less than 20 mean that player just pressed it but not hold it
        if (framesCounter < 20)
        {
            //if any movement or selection key is pressed
            if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_A) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S) || IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_SPACE))
            {
                //if the player does't selected the first Pokemon yet
                if (!firstSelectionDone)
                {
                    //handdle player movement and initial selection
                    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (playerPosX < col - 2))
                    {
                        
                        playerPosX++;
                    }
                    else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (playerPosX > 1))
                    {
                        playerPosX--;
                    }
                    else if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (playerPosY > 1))
                    {
                        playerPosY--;
                    }
                    else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (playerPosY < row - 2))
                    {
                        playerPosY++;
                    }
                    //if the player presses enter or space to select a Pokemon
                    else if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) && pokeArr[playerPosY][playerPosX].deleted == false)
                    {
                        firstSelectionDone = true;
                        selectedX = playerPosX;
                        selectedY = playerPosY;
                        pokeArr[selectedY][selectedX].selected = true;
                    }
                }
                else
                {
                    // handle player move after selection
                    if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && (playerPosX < col - 2))
                    {
                        playerPosX++;
                    }
                    else if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && (playerPosX > 1))
                    {
                        playerPosX--;
                    }
                    else if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && (playerPosY > 1))
                    {
                        playerPosY--;
                    }
                    else if ((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && (playerPosY < row - 2))
                    {
                        playerPosY++;
                    }
                    else if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
                    {
                        firstSelectionDone = false; //reset for next selection
                        //chek i matching
                        if (temp = iMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                        {
                            // dealocate before input new list
                            clearList(pointList);
                            pointList = temp;
                            // delete pokemon if they imatching
                            deleteCell(pokeArr, selectedX, selectedY);
                            deleteCell(pokeArr, playerPosX, playerPosY);
                            //reference ismatching to main funtion so main funtion will know that have couple of pokemon
                            // have been matching
                            isMatching = true;
                            //reference time to main funtion
                            matchingTime = GetTime();
                            //calculate scoree
                            scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'i');
                        }
                        // 3 case down is same as the first one
                        else if(temp = zMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                        {
                            clearList(pointList);
                            pointList = temp;
                            deleteCell(pokeArr, selectedX, selectedY);
                            deleteCell(pokeArr, playerPosX, playerPosY);
                            isMatching = true;
                            matchingTime = GetTime();
                            scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'z');
                        }
                        else if(temp = lMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                        {
                            clearList(pointList);
                            pointList = temp;
                            deleteCell(pokeArr, selectedX, selectedY);
                            deleteCell(pokeArr, playerPosX, playerPosY);
                            isMatching = true;
                            matchingTime = GetTime();
                            scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'l');
                        }
                        else if(temp = uMatching(pokeArr, row, col, selectedX, selectedY, playerPosX, playerPosY))
                        {
                            clearList(pointList);
                            pointList = temp;
                            deleteCell(pokeArr, selectedX, selectedY);
                            deleteCell(pokeArr, playerPosX, playerPosY);
                            matchingTime = GetTime();
                            isMatching = true;
                            scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'u');
                        }
                        // penalty if player chose wrong couple of pokemon
                        else if (selectedX != playerPosX && selectedY != playerPosY && pokeArr[playerPosY][playerPosX].deleted == false && pokeArr[selectedY][selectedX].deleted == false)
                        {
                            if (scoree - 30 > 0)
                            scoree -= 30;
                        }
                        pokeArr[selectedY][selectedX].selected = false;
                        firstSelectionDone = true;
                        selectedX = playerPosX;
                        selectedY = playerPosY;
                        pokeArr[selectedY][selectedX].selected = true;
                    }
                }
            }
        }
        else
        {
            if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && (playerPosX < col - 2))
            {
                if (framesCounter % 4 == 0)
                playerPosX++; 
            }
            else if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && (playerPosX > 1))
            {
                if (framesCounter % 4 == 0)
                playerPosX--;
            }
            else if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && (playerPosY > 1))
            {
                if (framesCounter % 4 == 0)
                playerPosY--;
            }
            else if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && (playerPosY < row - 2))
            {
                if (framesCounter % 4 == 0)
                playerPosY++;
            }
        }
    }
    else framesCounter = 0;
}
/*
    This function traverses through the 2d pokemon matrix and finds all pairs of pokemon
    to check if they are matching or not it will returns the point list for suggestion.
*/
bool suggestion(Pokemon **pokeArr, int row, int col, Point *&pointList)
{
    //traverse through the matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //if the pokemon is not deleted
            if (pokeArr[i][j].deleted == false)
            {
                //check each pair of pokemon
                for (int k = 0; k < row; k++)
                {
                    for (int l = 0; l < col; l++)
                    {
                        //avoid checking the same pokemon
                        if (!(i == k && j == l))
                        {
                            //try different matching patterns to find a match
                            Point* p1 = uMatching(pokeArr, row, col, j, i, l, k);
                            if (p1 != NULL)
                            {
                                //if a match is found assign the point list and return true
                                pointList = p1;
                                return true;
                            }
                            Point* p2 = zMatching(pokeArr, j, i, l, k);
                            if (p2 != NULL)
                            {
                                pointList = p2;
                                return true;
                            }
                            Point* p3 = lMatching(pokeArr, j, i, l, k);
                            if (p3 != NULL)
                            {
                                pointList = p3;
                                return true;
                            }
                            Point* p4 = iMatching(pokeArr, j, i, l, k);
                            if (p4 != NULL)
                            {
                                pointList = p4;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    //if no matching pair is found set pointList to NULL and return false
    pointList = NULL;
    return false;
}

/*
    this function checks if the Pokemon array is empty or not
    it traverses through the 2D array and checks if any pokemon is not deleted
    if it finds any pokemon that is not deleted returns false
    indicating that the array is not empty otherwise it return true
    indicating that the array is empty.
*/
bool checkEmpty(Pokemon **pokeArr, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (pokeArr[i][j].deleted == false)
                return false;
        }
    }
    return true;
}
/*
    i take this funtion from https://chat.openai.com/ is using Fisher-Yates shuffle algorthm
    to shuffle array in case player can win the game becasue threre are no couple of pokemon can matching
*/
void shuffle_array_2d(Pokemon **arr, int row, int col)
{
  // Start from position (1, 1) and end at (row - 2, col - 2) to leave the outer border
  for (int i = 1; i < row - 1; i++) {
    for (int j = 1; j < col - 1; j++) {
      // Generate a random position within the range of inner elements
      int rand_i = rand() % (row - 2 - 1) + 1;
      int rand_j = rand() % (col - 2 - 1) + 1;

      //swap the element at the current position with the random position
      swapPokemon(arr[i][j], arr[rand_i][rand_j]);
    }
  }
}
