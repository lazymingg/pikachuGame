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

//***********************************************************************
//U I Z L maching
bool uMatching (Pokemon **pokeArr, int row, int col, int playerPosX, int playerPosY)
{
    
}






//**************************************************************************
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
        Pokemon temp = pokemonArray[i];
        pokemonArray[i] = pokemonArray[j];
        pokemonArray[j] = temp;
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
        cout << i;
        i++;
        temp[i].pokeImage = texture[randomNumber];
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        cout << i;
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
                Rectangle sourceRec = { 0, 0, (a[i][j].pokeImage).width, (a[i][j].pokeImage).height };
                Rectangle destRec = { j * scaledWidth, i * scaledHeight, scaledWidth - 2, scaledHeight - 2};
            if ((j == playerPosX && i == playerPosY))
                DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, GRAY);
            else
            {
                //sourceRec is a size of source image destRec, is size of the out put image
                // Rectangle sourceRec = { 0, 0, (a[i][j].pokeImage).width, (a[i][j].pokeImage).height };
                // Rectangle destRec = { j * scaledWidth, i * scaledHeight, scaledWidth - 2, scaledHeight - 2};
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
    a[deletePosX][deletePosY].deleted = true;
}

bool keyPressedLastFrame = false;
void updatePlayerPosition(Pokemon **pokeArr, int &playerPosX, int &playerPosY, int row, int col) {
    bool keyPressed = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_UP) || IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_ENTER);

    if (keyPressed && !keyPressedLastFrame) {
        if (IsKeyDown(KEY_RIGHT) && playerPosX < col - 1) {
            playerPosX++;
        } else if (IsKeyDown(KEY_LEFT) && playerPosX > 0) {
            playerPosX--;
        } else if (IsKeyDown(KEY_UP) && playerPosY > 0) {
            playerPosY--;
        } else if (IsKeyDown(KEY_DOWN) && playerPosY < row - 1) {
            playerPosY++;
        } else if (IsKeyDown(KEY_ENTER)) {
            pokeArr[playerPosY][playerPosX].selected = true;
        }
    }
    // if (IsKeyPressed(KEY_ENTER) && !enterKeyPressed)
        // {
        //     // selectPosX = playerPosX;
        //     // selectPosY = playerPosY;
        //     deleteCell(resArr, playerPosX, playerPosY);
        //     enterKeyPressed = true;
        // }

    keyPressedLastFrame = keyPressed;
}

int main()
{
    const int HEIGHT = 686, WIDTH = 1024;

    // initial player Position
    int playerPosX = 0;
    int playerPosY = 0;

    int selectPosX = -1;// comming soon
    int selectPosY = -1;

    // size of the table row = row -2 col = col - 2
    int row = 9;
    int col = 14;

    InitWindow(WIDTH, HEIGHT, "Ming:DDD");
    SetTargetFPS(60);

    //read nPicture
    const int numberOfPicture = 12;
    Texture2D *resTexture = readImage(numberOfPicture);//read image

    //generate table
    // Pokemon **resArr = createTable(row, col, resTexture, numberOfPicture);
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
        updatePlayerPosition(resArr, playerPosX, playerPosY, row, col);
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
