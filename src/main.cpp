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

/**********************************U I Z L maching*************************************/

bool uMatching (Pokemon **pokeArr, int row, int col, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key)
        return false;
    //check U ngang trái
    int posx = 0;
    for (int i = playerPosX - 1; i > 0; i--){
        if (pokeArr[playerPosY][i].deleted == false){
            posx = i + 1;
            break;
        }
    }
    int posxx = 0;
    for (int i = playerPosXX - 1; i > 0; i--){
        if (pokeArr[playerPosYY][i].deleted == false){
            posxx = i + 1;
            break;
        }
    }
    if (posx == posxx) return true;
    //check U ngang phải
    posx = col - 1;
    for (int i = playerPosX + 1; i < col - 1; i++){
        if (pokeArr[playerPosY][i].deleted == false){
            posx = i - 1;
            break;
        }
    }
    posxx = col - 1;
    for (int i = playerPosXX + 1; i < col - 1; i++){
        if (pokeArr[playerPosYY][i].deleted == false){
            posxx = i - 1;
            break;
        }
    }
    if (posx == posxx) return true;
    //Check U trên
    int posy = 0;
    for (int i = playerPosY - 1; i > 0; i--){
        if (pokeArr[i][playerPosX].deleted == false){
            posy = i + 1;
            break;
        }
    }
    int posyy = 0;
    for (int i = playerPosYY - 1; i > 0; i--){
        if (pokeArr[i][playerPosX].deleted == false){
            posyy = i + 1;
            break;
        }
    }
    if (posy == posyy) return true;
    //Check U dưới
    posy = row - 1;
    for (int i = playerPosY + 1; i < row - 1; i++){
        if (pokeArr[i][playerPosX].deleted == false){
            posy = i - 1;
            break;
        }
    }
    posyy = row - 1;
    for (int i = playerPosYY + 1; i < row - 1; i++){
        if (pokeArr[i][playerPosX].deleted == false){
            posyy = i - 1;
            break;
        }
    }
    if (posy == posyy) return true;
    // Cả 4 không thỏa, trả về false
    return false;
}
bool iMatching (Pokemon **pokeArr, int x_1, int y_1, int x_2, int y_2)
{
    //ignore if they are not same or if they are one
    if (pokeArr[y_1][x_1].key != pokeArr[y_2][x_2].key || x_1 == x_2 && y_1 == y_2) return false;


    if (y_1 == y_2)
    {
        if (x_1 > x_2) swap(x_1, x_2);

        for (int i = x_1 + 1; i < x_2; i++)
        {
            if (pokeArr[y_1][i].deleted == false) return false;
        }

        return true;
    }

    if (x_2 == x_1)
    {
        if (y_1 > y_2) swap(y_1, y_2);

        for (int i = y_1 + 1; i < y_2; i++)
        {
            if (pokeArr[i][x_1].deleted == false) return false;
        }

        return true;
    }
    return false;
}


/*****************************************************************************************/
struct Line
{
    bool vertical = false;
    bool display = false;
};
// void updateLine(Line **lineArr, int row, int col)
// {
    
// }
void drawLine(Line **lineArr, int row, int col, int scaledWidth, int scaledHeight)
{

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (lineArr[i][j].display == true)
            {
                if (lineArr[i][j].vertical == true)
                {
                    // toa do x y cua duong thang
                    Vector2 point1 = {(j * scaledWidth + scaledWidth / 2), i * scaledHeight};
                    Vector2 point2 = {(j * scaledWidth + scaledWidth / 2), (i + 1) * scaledHeight};
                    double startTime = GetTime(); // Lưu thời gian bắt đầu
                    while ((GetTime() - startTime) < 1.5) { // Kiểm tra thời gian đã trôi qua
                        BeginDrawing();
                        ClearBackground(RAYWHITE);
                        DrawLineEx(point1, point2, 2, GRAY);
                        EndDrawing();
                    }
                }
                else
                {
                    // toa do x y cua duong thang
                    Vector2 point1 = {j * scaledWidth, (i * scaledHeight + scaledHeight / 2)};
                    Vector2 point2 = {(j + 1) * scaledWidth, (i * scaledHeight + scaledHeight / 2)};
                    double startTime = GetTime(); // Lưu thời gian bắt đầu
                    while ((GetTime() - startTime) < 1.5) { // Kiểm tra thời gian đã trôi qua
                        BeginDrawing();
                        ClearBackground(RAYWHITE);
                        DrawLineEx(point1, point2, 2, GRAY);
                        EndDrawing();
                    }
                }
            }
        }
    }
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
                if (iMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY) || uMatching(pokeArr, row, col, playerPosX, playerPosY, selectedX, selectedY))
                {
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
        updateTable(resArr, playerPosX, playerPosY, row, col, selected, selectedPosX, selectedPosY);
        drawTable(resArr, row, col, 60, 60, playerPosX, playerPosY);// draw pokemon
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