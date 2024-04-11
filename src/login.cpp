/*
    "Most of the functions below were coded by me and my partner. 
    If any function is referenced or copied from another source, 
    the source will be noted in a comment above the function."
*/
#include "login.h"

const int screenHeight = 686, screenWidth = 1024;
/*
    this funtion draw the login menu handle player slection 
    through the parameter
*/
void drawLogin(bool &keyPressed, int &playerSelection, string &userName)
{
    // defIne text for draw
    const char *title = "Pikachu The Matching Game :D";
    const char *title2 = "Press Enter to login :D";
    const char *option1 ="User Name : ";
    const char *warning ="User Name lenght must at least 15 character !";

    // delete the player username when user press the backspace key
    if (IsKeyPressed(KEY_BACKSPACE))
    {
        if (userName.length() > 0)
            userName.pop_back();
    }
    // else if player enter them username
    else
    {
        for (int key = KEY_A; key <= KEY_Z; key++)
        {
            if (IsKeyPressed(key) && userName.length() < 15)
            {
                char letter = static_cast<char>(key);
                // i want the username must be lower case so i convert them to lower case
                letter = tolower(letter);
                userName += letter;
            }
            // handle case when username to long i just let them to enter username less than 15 character
            if (userName.length() == 15)
            {
                Vector2 warningSize = MeasureTextEx(GetFontDefault(), warning, 20, 2);
                DrawText(warning, screenWidth / 2 - warningSize.x/2, 400, 20, RED);
            }
        }
    }
    //draw instruction and text in login menu
    Vector2 textSize = MeasureTextEx(GetFontDefault(), title, 50, 5);
    // set color for text background
    Color fadedColor = Fade(BLACK, 0.5f);
    // text background size
    DrawRectangleRec((Rectangle){screenWidth / 2 - textSize.x / 2 - 20, 150 - 20, textSize.x + 40, textSize.y + 40}, fadedColor);
    // draw text
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
/*
    player data is in this format
    userName
    maxNormalMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    maxSpecialMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    this funtion aim to read the normalMode data
*/
int* readNormalData(string filePath, string userName, int& size)
{
    ifstream fin(filePath.c_str());
    if (!fin.is_open()) 
    {
        cout << "cannot open the file." << std::endl;
        return NULL;
    }

    string temp;
    int* normalData = NULL;
    while (getline(fin, temp))
    {
        if (temp == userName)
        {
            //read size of normal mode data
            fin >> size;
            fin.ignore(); //ignore 

            normalData = new int[size];

            for (int i = 0; i < size; i++)
            {
                fin >> normalData[i];
            }
            fin.close();
            return normalData;
        }
    }

    cout << "cannot find normal data for user." << std::endl;
    return NULL;
}
/*
    player data is in this format
    userName
    maxNormalMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    maxSpecialMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    this funtion aim to read the specialMode data
*/
int* readSpecialData(string filePath, string userName, int& size)
{
    ifstream fin(filePath);
    if (!fin.is_open()) 
    {
        cout << "cannot open the file" << endl;
        return NULL;
    }

    string temp;
    int* specialData = NULL;
    while (getline(fin, temp))
    {
        if (temp == userName)
        {
            // Read and discard the line containing maxNormalMode data
            getline(fin, temp);

            // Read size of special mode data
            fin >> size;
            fin.ignore(); // Ignore the newline character

            // Allocate memory for specialData array
            specialData = new int[size];

            // Read special mode data
            for (int i = 0; i < size; i++)
            {
                fin >> specialData[i];
            }
            fin.close();
            return specialData;
        }
    }

    cout << "cannot find special data for user" << endl;
    return NULL;
}
/*
    player data is in this format
    userName
    maxNormalMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    maxSpecialMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    this funtion will save all the data of the user i will use this when player exit the game 
*/
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
    // move the cursor to the beginning
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
    //re write
    ofstream fOut(filePath, ios::out);
    for (int i = 0; i < count; i++)
    {
        fOut << line[i] << endl;
    }

    delete[] line;
    fOut.close();
    return;
}
/*
    player data is in this format
    userName
    maxNormalMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    maxSpecialMode scorelevel1 scorelevel2 scorelevel3 scorelevel4 scorelevel5 scorelevel6
    if in the file dont have the username this funtion will add a new user with a base data like this
    userName
    1 0 0 0 0 0 0
    1 0 0 0 0 0 0
*/
void checkAndCreateUser(string filePath, string userName)
{
    ifstream fIn(filePath.c_str());

    if (!fIn.is_open()) 
    {
        cout << "canot openfile" << endl;
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
/*
    if the player socre more higher than the hi score we will update hi score
*/
void saveScore(int *playerModeScore, int currentLevel, int newScore)
{
    if (playerModeScore[currentLevel - 1] < newScore)
    {
        playerModeScore[currentLevel - 1] = newScore;
    }
}
/*
    if player win we will increse player maxlevel so that they can play the next level
*/
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