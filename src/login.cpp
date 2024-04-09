#include "login.h"
using namespace std;


const int screenHeight = 686, screenWidth = 1024;
const char *title = "Pikachu The Matching Game :D";
const char *title2 = "Press Enter to login :D";
const char *option1 ="User Name : ";
const char *warning ="User Name lenght must at least 15 character !";

void drawLogin(bool &keyPressed, int &playerSelection, string &userName)
{

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            // Xóa ký tự cuối cùng của tên người dùng
            if (userName.length() > 0)
                userName.pop_back();
        }
        else
        {
            // Thêm ký tự được nhập vào tên người dùng
            for (int key = KEY_A; key <= KEY_Z; key++)
            {
                if (IsKeyPressed(key) && userName.length() < 15)
                {
                    char letter = static_cast<char>(key);
                    letter = tolower(letter);
                    userName += letter;
                }
                if (userName.length() == 15)
                {
                    Vector2 warningSize = MeasureTextEx(GetFontDefault(), warning, 20, 2);
                    DrawText(warning, screenWidth / 2 - warningSize.x/2, 400, 20, RED);
                }
            }
        }

    Vector2 textSize = MeasureTextEx(GetFontDefault(), title, 50, 5);
    Color fadedColor = Fade(BLACK, 0.5f); // Thiết lập độ trong suốt của màu sắc
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 150 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
    DrawText(title, screenWidth / 2 - textSize.x/2, 150, 50, PINK);

    Vector2 userNameSize = MeasureTextEx(GetFontDefault(), userName.c_str(), 30, 3);
    textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x/2 - userNameSize.x/2 - 20 , 350 - 20, textSize.x + userNameSize.x + 40, textSize.y + 40}, fadedColor);
    DrawText(option1, screenWidth / 2 - textSize.x/2 - userNameSize.x/2, 350, 30, PINK);
    DrawText(userName.c_str(), screenWidth / 2 + textSize.x/2 - userNameSize.x/2, 350, 30, PINK);


    textSize = MeasureTextEx(GetFontDefault(), title2, 30, 3);
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x/2 - 20 , 500 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
    DrawText(title2, screenWidth / 2 - textSize.x/2, 500, 30, PINK);
}
int *readNormalData(string filePath, string userName, int &size)
{
    ifstream fIn(filePath.c_str());

    if (!fIn.is_open()) 
    {
        cout << "Không thể mở tệp tin!" << endl;
        return NULL;
    }
    string temp = "";
    size = 0;
    int *normalData = NULL;
    while (!fIn.eof())
    {
        getline(fIn, temp);
        if (temp == userName)
        {
            fIn >> size;
            fIn.ignore();
            normalData = new int[size];
            for (int i = 0; i < size; i++)
            {
                fIn >> normalData[i];
                fIn.ignore();
            }
            fIn.close();
            return normalData;
        }
    }
    cout << "cant find normal data";
    return NULL;
}
int *readSpecialData(string filePath, string userName, int &size)
{
    ifstream fIn(filePath.c_str());

    if (!fIn.is_open()) 
    {
        cout << "Không thể mở tệp tin!" << endl;
        return NULL;
    }
    string temp = "";
    size = 0;
    int *specialData = NULL;
    while (!fIn.eof())
    {
        getline(fIn, temp);
        if (temp == userName)
        {
            // skip một dòng 
            string skip;
            getline(fIn, skip);
            //
            fIn >> size;
            fIn.ignore();
            specialData = new int[size];
            for (int i = 0; i < size; i++)
            {
                fIn >> specialData[i];
                fIn.ignore();
            }
            fIn.close();
            return specialData;
        }
    }
    cout << "cant find normal data";
    return NULL;
}
void saveGame(string userName, int *playerNormalData, int maxNormalLevel, int *playerSpecialData, int maxSpecialLevel, string filePath)
{
    if (playerNormalData == NULL || playerSpecialData == NULL) return;
    ifstream fIn(filePath.c_str());
    
    string temp = "";
    int count = 0;

    while (getline(fIn, temp))
    {
        count++;
    }
    fIn.clear();
    fIn.seekg(0, ios::beg);
    string *line = new string[count];
    for (int i = 0; i < count; i++)
    {
        getline(fIn, line[i]);
    }
    fIn.close();
    for (int i = 0; i < count; i++)
    {
        if (line[i] == userName)
        {
            line[i + 1] = to_string(maxNormalLevel) + " ";
            for (int j = 0; j < 6; j++)
            {
                if (j < maxNormalLevel)
                {
                    line[i + 1] = line[i + 1] + to_string(playerNormalData[j]);  
                }
                else
                {
                    line[i + 1] = line[i + 1] + to_string(0);
                }
                if (j < 5) line[i + 1] = line[i + 1] + " ";
            }
            line[i + 2] = to_string(maxSpecialLevel) + " ";
            for (int j = 0; j < 6; j++)
            {
                if (j < maxSpecialLevel)
                {
                    line[i + 2] = line[i + 2] + to_string(playerSpecialData[j]);  
                }
                else
                {
                    line[i + 2] = line[i + 2] + to_string(0);
                }
                if (j < 5) line[i + 2] = line[i + 2] + " ";
            }
        }
    }
    //ghi lại lên file
    ofstream fOut(filePath, ios::out);
    for (int i = 0; i < count; i++)
    {
        fOut << line[i] << endl;
    }

    delete[] line;
    fOut.close();
    return;
}
void checkAndCreateUser(string filePath, string userName)
{
    ifstream fIn(filePath.c_str());

    if (!fIn.is_open()) 
    {
        cout << "Không thể mở tệp tin!" << endl;
        return;
    }

    string temp = "";

    while (!fIn.eof())
    {
        getline(fIn, temp);
        if (userName == temp)
        {
            fIn.close();
            return;
        }
    }
    fIn.close();

    ofstream fOut(filePath, ios::out | ios::app);
    fOut << userName << endl;
    fOut << 1 << " ";
    for (int i = 0; i < 6; i++)
    {
        if (i == 5)
        {
            fOut << 0 << endl;
        }
        else
        fOut << 0 << " ";
    }
    fOut << 1 << " ";
    for (int i = 0; i < 6; i++)
    {
        if (i == 5 )
        {
            fOut << 0 << endl;
        }
        else
        fOut << 0 << " ";
    }
    fOut.close();
}

// sau khi hoàn thành xong màn chơi nếu người chơi chưa mở màn tiếp theo thì hãy mở cho họ và cập nhật điểm

void saveScore(int *playerModeScore, int currentLevel, int newScore)
{
    if (playerModeScore[currentLevel - 1] < newScore)
    {
        playerModeScore[currentLevel - 1] = newScore;
    }
}

void levelUp(int *&playerModeScore, int &maxModeLevel)
{
    int *temp = new int[maxModeLevel + 1];

    for (int i = 0; i < maxModeLevel; i++)
    {
        temp[i] = playerModeScore[i];
    
    }
    
    temp[maxModeLevel] = 0;
    maxModeLevel++;

    delete[] playerModeScore;
    playerModeScore = temp;
}