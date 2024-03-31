#include <raylib.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string.h>

using namespace std;

struct Pokemon
{
    Texture2D pokeImage;
    bool deleted = false;
    bool selected = false;
    int key = 0;
};
struct Point
{
    int x;
    int y;
    Point *next;
};
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
void clearList(Point *&head) {
    while (head != nullptr) {
        Point *temp = head; // Lưu địa chỉ của node hiện tại
        head = head->next; // Di chuyển head đến node tiếp theo
        delete temp; // Xóa node hiện tại
    }
}
void addTail(Point* &pHead, int x, int y){
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
/**********************************U I Z L maching*************************************/
Point* uMatching (Pokemon **pokeArr, int row, int col, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key)
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
    //check U ngang trái
    for (int i = minx - 1; i >= 0 && pokeArr[playerPosY][i].deleted == true && pokeArr[playerPosYY][i].deleted == true; i--){
        bool valid = true;
        for (int j = miny; j <= maxy; j++){
            if (pokeArr[j][i].deleted == false){
                valid = false;
                break;
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
    // Check U ngang phải
    for (int i = maxx + 1; i < col && pokeArr[playerPosY][i].deleted == true && pokeArr[playerPosYY][i].deleted == true; i++){
        bool valid = true;
        for (int j = miny; j <= maxy; j++){
            if (pokeArr[j][i].deleted == false){
                valid = false;
                break;
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
        for (int j = minx; j <= maxx; j++){
            if (pokeArr[i][j].deleted == false){
                valid = false;
                break;
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
        for (int j = minx; j <= maxx; j++){
            if (pokeArr[i][j].deleted == false){
                valid = false;
                break;
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
    return pHead;
}
Point *zMatching(Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key || playerPosX == playerPosXX && playerPosY == playerPosYY)
    {
        return NULL;
    }
    Point* pHead = NULL;

    // chắc chắn rằng playerPosX playerPosY luôn là điểm nằm bên trái
    if (playerPosX > playerPosXX)
    {
        swap(playerPosX, playerPosXX);
        swap(playerPosY, playerPosYY);
    }
    // kiểm tra xem điểm còn lại nằm ở trên hay dưới
    // z doc
    if (playerPosY > playerPosYY) // nếu nằm ở trên
    {
        for (int i = 1; i <  playerPosXX - playerPosX; i++)
        {
            if (pokeArr[playerPosY][playerPosX + i].deleted && pokeArr[playerPosYY][playerPosX + i].deleted)
            {
                for (int s = 0; s + i + playerPosX < playerPosXX; s++)
                {
                    if(pokeArr[playerPosYY][playerPosX + i + s].deleted == false) continue;
                }
                for (int j = 0; j <= playerPosY - playerPosYY; j++)
                {
                    if (pokeArr[playerPosY - j][playerPosX + i].deleted == false)
                    {
                        break;
                    }
                    if (j == playerPosY - playerPosYY)
                    {
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY - j);
                        addTail(pHead, playerPosX + i, playerPosY - j);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }
    //z ngang 
        for (int i = 1; i <  playerPosY - playerPosYY; i++)
        {
            if (pokeArr[playerPosY - i][playerPosX].deleted && pokeArr[playerPosY - i][playerPosXX].deleted)
            {
                for (int s = 0; playerPosY - i - s > playerPosYY; s++)
                {
                    if(pokeArr[playerPosY - i - s][playerPosXX].deleted == false) continue;
                }
                for (int j = 0; j <= playerPosXX - playerPosX; j++)
                {
                    if (pokeArr[playerPosY - i][playerPosX + j].deleted == false)
                    {
                        break;
                    }
                    if (j == playerPosXX - playerPosX)
                    {
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX, playerPosY - i);
                        addTail(pHead, playerPosX, playerPosY - i);
                        addTail(pHead, playerPosX + j, playerPosY - i);
                        addTail(pHead, playerPosX + j, playerPosY - i);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }
    }
    if (playerPosY < playerPosYY) // nếu nằm dưới 
    {
        //z doc
        for (int i = 1; i <  playerPosXX - playerPosX; i++)
        {
            if (pokeArr[playerPosY][playerPosX + i].deleted && pokeArr[playerPosYY][playerPosX + i].deleted)
            {
                for (int s = 0; s + i + playerPosX < playerPosXX; s++)
                {
                    if(pokeArr[playerPosYY][playerPosX + i + s].deleted == false) continue;
                }
                for (int j = 0; j <= playerPosYY - playerPosY; j++)
                {
                    if (pokeArr[playerPosY + j][playerPosX + i].deleted == false)
                    {
                        break;
                    }
                    if (j == playerPosYY - playerPosY)
                    {
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY + j);
                        addTail(pHead, playerPosX + i, playerPosY + j);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }      
                }
            }
        }
        // z ngang
        for (int i = 1; i <  playerPosYY - playerPosY; i++)
        {
            if (pokeArr[playerPosY + i][playerPosX].deleted && pokeArr[playerPosY + i][playerPosXX].deleted)
            {
                for (int s = 0; playerPosY + i + s < playerPosYY; s++)
                {
                    if(pokeArr[playerPosY + i + s][playerPosXX].deleted == false) continue;
                }
                for (int j = 0; j <= playerPosXX - playerPosX; j++)
                {
                    if (pokeArr[playerPosY + i][playerPosX + j].deleted == false)
                    {
                        break;
                    }
                    if (j == playerPosXX - playerPosX)
                    {
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX, playerPosY + i);
                        addTail(pHead, playerPosX, playerPosY + i);
                        addTail(pHead, playerPosX + j, playerPosY + i);
                        addTail(pHead, playerPosX + j, playerPosY + i);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }
    }
    return NULL;
}
Point *lMatching(Pokemon **pokeArr, int row, int col, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{

}
Point* iMatching (Pokemon **pokeArr, int x_1, int y_1, int x_2, int y_2)
{
    //ignore if they are not same or if they are one
    if (pokeArr[y_1][x_1].key != pokeArr[y_2][x_2].key || x_1 == x_2 && y_1 == y_2) return NULL;

    //create point list
    Point *pHead = NULL;

    if (y_1 == y_2)
    {
        if (x_1 > x_2) swap(x_1, x_2);

        for (int i = x_1 + 1; i < x_2; i++)
        {
            if (pokeArr[y_1][i].deleted == false) return NULL;
        }
        // input point for list
        pHead = createNodes(x_1, y_1);
        pHead -> next = createNodes(x_2,y_2);
        return pHead;
    }

    if (x_2 == x_1)
    {
        if (y_1 > y_2) swap(y_1, y_2);

        for (int i = y_1 + 1; i < y_2; i++)
        {
            if (pokeArr[i][x_1].deleted == false) return NULL;
        }
        // input point for list
        pHead = createNodes(x_1, y_1);
        pHead -> next = createNodes(x_2,y_2);
        return pHead;
    }
    return NULL;
}


/*****************************************************************************************/

void drawLine(Point* pHead, int scaledWidth, int scaledHeight)
{
    if (pHead == NULL) return;

    Point *pCur = pHead->next;
    Point *pPrev = pHead;

    double startTime = GetTime(); // Lưu thời gian bắt đầu
    

    while (GetTime() - startTime < 0.5) // Kiểm tra thời gian đã trôi qua
    {
        BeginDrawing(); // Bắt đầu quá trình vẽ
        // Vẽ tất cả các đoạn thẳng trong danh sách
        while (pCur != NULL)
        {
            // Gan diem dau va cuoi cua duong thang theo kich thuoc cua o
            Vector2 point1 = {(pPrev->x * scaledWidth + scaledWidth / 2), (pPrev->y * scaledHeight + scaledHeight / 2)};
            Vector2 point2 = {(pCur->x * scaledWidth + scaledWidth / 2), (pCur->y * scaledHeight + scaledHeight / 2)};
            
            DrawLineEx(point1, point2, 3, BLUE);// Ve duong thang

            // Kiểm tra xem còn đoạn thẳng tiếp theo không
            if (pCur -> next)
            {
                pPrev = pPrev -> next -> next;
                pCur = pCur -> next -> next;
            }
            else 
            {
                pCur = pHead->next;
                pPrev = pHead;
                break;
            }
        }
        EndDrawing(); // Kết thúc quá trình vẽ
    }
    clearList(pHead);
}

//read (n)image name "image.(i)"
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

        Image image = LoadImage(picName.c_str());// load image
        resTexture[i] = LoadTextureFromImage(image);// load texture from image
        UnloadImage(image);// delete image after load
    }
    return resTexture;
}

void swapPokemon(Pokemon& p1, Pokemon& p2) {
    using std::swap; // Import hàm swap từ thư viện chuẩn

    // Sử dụng hàm swap để hoán đổi từng phần tử của hai biến
    swap(p1.pokeImage, p2.pokeImage);
    swap(p1.deleted, p2.deleted);
    swap(p1.selected, p2.selected);
    swap(p1.key, p2.key);
}
void shufflePokemonArray(Pokemon* pokemonArray, int size) {
    // Sử dụng hạt giống ngẫu nhiên từ thời gian
    srand(time(NULL));

    // Bắt đầu từ phần tử cuối cùng và di chuyển ngược lên
    for (int i = size - 1; i > 0; --i) {
        // Chọn một phần tử ngẫu nhiên trong đoạn từ 0 đến i
        int j = rand() % (i + 1);

        // Hoán đổi giá trị của phần tử thứ i và j
        swapPokemon(pokemonArray[i], pokemonArray[j]);
    }
}

// hàm này sẽ tạo môtj bảng với viền bên ngoài sẽ là các pokemon được gán mặc định là đã bị xóa
// làm vậy để sau này đồng bộ với hàm vẽ đường đi vì đương đi có thể nằm ở ngoài viền
Pokemon **createTable(int row, int col, Texture2D *texture, int nPicture)
{   
    //seed random
    srand(time(0));
    int randomNumber = 0;

    //gennerate arr 1 dimarr
    int size = (row - 2)*(col - 2);
    Pokemon *temp = new Pokemon[size];

    //random Image via key
    for (int i = 0; i < size;)
    {
        randomNumber = rand() % nPicture;
        temp[i].pokeImage = texture[randomNumber];
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        i++;
        temp[i].pokeImage = texture[randomNumber];
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        i++; 
    }
    //free texture
    delete[] texture;
    shufflePokemonArray(temp, size);
    shufflePokemonArray(temp, size);

    Pokemon **resArr = new Pokemon *[row];
    for (int i = 0; i < row; i++)
    {
        resArr[i] = new Pokemon[col];
    }
    //randomcolor
    int count = 0;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
            {
                resArr[i][j].deleted = true;
                resArr[i][j].pokeImage = temp[0].pokeImage;
                resArr[i][j].key = temp[count].key;
            }
            else
            {
            resArr[i][j].deleted = temp[count].deleted;
            resArr[i][j].pokeImage = temp[count].pokeImage;
            resArr[i][j].key = temp[count].key;
            count++;
            }
        }
    }
    //free the one dim arr
    delete[] temp;
    return resArr;
}
void drawTable(Pokemon **a, int row, int col, const int scaledWidth, const int scaledHeight, int playerPosX, int playerPosY)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(a[i][j].deleted == false || (j == playerPosX && i == playerPosY))
            {
                //sourceRec is a size of source image destRec, is size of the out put image
                Rectangle sourceRec = { 0, 0, (a[i][j].pokeImage).width, (a[i][j].pokeImage).height };
                Rectangle destRec = { j * scaledWidth, i * scaledHeight, scaledWidth - 2, scaledHeight - 2};

            if (a[i][j].deleted == true)
            {
                DrawRectangle(j * scaledWidth, i * scaledHeight, scaledWidth - 2, scaledHeight - 2, Fade(LIGHTGRAY, 0.5f));
            }
            else if ((j == playerPosX && i == playerPosY))
                DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, GRAY);
            else
            {
                if (a[i][j].selected == true)
                DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, GRAY);
                else
                DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, WHITE);
            }
            }
        }
    }
}
//delete cell
void deleteCell(Pokemon **a, int deletePosX, int deletePosY)
{
    a[deletePosY][deletePosX].deleted = true;
}

bool keyPressedLastFrame = false;
void updateTable(Pokemon **pokeArr, int &playerPosX, int &playerPosY, int row, int col, bool &firstSelectionDone, int &selectedX, int &selectedY)
{
    bool keyPressed = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_ENTER);

    if (keyPressed && !keyPressedLastFrame) {
        if (!firstSelectionDone) {
            //if the first selection is not done update player position
            if (IsKeyDown(KEY_RIGHT) && playerPosX < col - 2) {
                playerPosX++;
            } else if (IsKeyDown(KEY_LEFT) && playerPosX > 1) {
                playerPosX--;
            } else if (IsKeyDown(KEY_UP) && playerPosY > 1) {
                playerPosY--;
            } else if (IsKeyDown(KEY_DOWN) && playerPosY < row - 2) {
                playerPosY++;
            } else if (IsKeyDown(KEY_ENTER)) {
                //if the user presses Enter mark the first selection
                firstSelectionDone = true;
                selectedX = playerPosX;
                selectedY = playerPosY;
                pokeArr[selectedY][selectedX].selected = true;
            }
        } else {
            //if the first selection is done update player position
            if (IsKeyDown(KEY_RIGHT) && playerPosX < col - 2) {
                playerPosX++;
            } else if (IsKeyDown(KEY_LEFT) && playerPosX > 1) {
                playerPosX--;
            } else if (IsKeyDown(KEY_UP) && playerPosY > 1) {
                playerPosY--;
            } else if (IsKeyDown(KEY_DOWN) && playerPosY < row - 2) {
                playerPosY++;
            } else if (IsKeyDown(KEY_ENTER)) {
                //if the user presses Enter again mark the second selection
                firstSelectionDone = false; // Reset for next selection
                //call a function to handle the selection
                if (iMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                {
                    Point* pointList = iMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY);
                    drawLine(pointList, 60 , 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                }
                else if(zMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                {
                    Point* pointList = zMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY);
                    drawLine(pointList, 60, 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                }
                else if(uMatching(pokeArr, row, col, selectedX, selectedY, playerPosX, playerPosY))
                {
                    Point* pointList = uMatching(pokeArr, row, col, selectedX, selectedY, playerPosX, playerPosY);
                    drawLine(pointList, 60 , 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                }
                pokeArr[selectedY][selectedX].selected = false;
            }
        }
    }

    keyPressedLastFrame = keyPressed;
}

int main()
{
    const int HEIGHT = 686, WIDTH = 1024;

    // initial player Position
    int playerPosX = 1;
    int playerPosY = 1;

    int selectedPosX = 1;// comming soon
    int selectedPosY = 1;
    bool selected = false;

    // size of the table row = row -2 col = col - 2
    int row = 9;
    int col = 14;

    InitWindow(WIDTH, HEIGHT, "Ming:DDD");
    SetTargetFPS(60);

    //read nPicture
    const int numberOfPicture = 12;
    Texture2D *resTexture = readImage(numberOfPicture);//read image

    // read background
    Image image = LoadImage("src/croppic/nen.png");
    Texture2D texture = LoadTextureFromImage(image);
    UnloadImage(image);
    Pokemon **resArr = createTable(row, col, resTexture, numberOfPicture);
    const int scaledWidth = WIDTH; // beacause size of background need to be the same with scren width and screen height
    const int scaledHeight = HEIGHT; 
    Rectangle sourceRec = { 0, 0, texture.width, texture.height }; // initial pic size
    Rectangle destRec = { 0, 0, scaledWidth, scaledHeight }; // out put pic size
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexturePro(texture, sourceRec, destRec, {0, 0}, 0, WHITE);// draw background
        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);// draw pokemon
        updateTable(resArr, playerPosX, playerPosY, row, col, selected, selectedPosX, selectedPosY);
        EndDrawing();
    }
    //free resarr
    for (int i = 0; i < row; i++)
    {
        delete[] resArr[i];
    }
    delete[] resArr;
    CloseWindow();
}