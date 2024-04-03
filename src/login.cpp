#include "login.h"

using namespace std;


const int screenHeight = 686, screenWidth = 1024;
const char *title = "Pikachu The Matching Game :D";
const char *title2 = "Press Enter to login :D";
const char *option1 ="User Name : ";
const char *warning ="User Name lenght must at least 15 character !";

string userName = "";
string passWord = "";

// Định nghĩa các hàm
// bool checkUser(string userName)
// {
//     ifstream fIn("/src/data/user.txt");

//     if (!fIn.is_open())
//     {
//         cout <<"canot open file"; return 0;
//     }
//     string temp = "";
//     while(!fIn.eof())
//     {
//         getline(fIn, temp);

//         if (temp == userName)
//         {
//             // lay du lieu cua nguoi choi username va cho ho vao game
//         }

//     }
// }
void drawLogin(bool &keyPressed, int &playerSelection)
{
    // Nếu không có nút nào được nhấn, đặt keyPressed thành false
    // if (!IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) 
    // {
    //     keyPressed = false;
    // }

    // if (IsKeyDown(KEY_ENTER)) 
    // {
    //     playerSelection++;
    //     if (playerSelection > 2) playerSelection = 1;
    //     keyPressed = true;
    // }
    // // Tương tự, nếu người dùng nhấn nút xuống và keyPressed là false
    // else if (IsKeyDown(KEY_DOWN) && !keyPressed) 
    // {
    //     playerSelection--;
    //     if (playerSelection <  1) playerSelection = 2; // Wrap-around
    //     keyPressed = true; // Đặt keyPressed thành true để chỉ di chuyển một lần
    // }

    // if (playerSelection == 1)
    // {
    //     // Nếu ô tên người dùng đang được chọn
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
    // }

    // if (playerSelection == 2)
    // {
    //     // Nếu ô tên người dùng đang được chọn
    //     if (IsKeyPressed(KEY_BACKSPACE))
    //     {
    //         // Xóa ký tự cuối cùng của tên người dùng
    //         if (passWord.length() > 0)
    //             passWord.pop_back();
    //     }
    //     else
    //     {
    //         // Thêm ký tự được nhập vào tên người dùng
    //         for (int key = KEY_A; key <= KEY_Z; key++)
    //         {
    //             if (IsKeyPressed(key) && passWord.length() < 15)
    //             {
    //                 char letter = static_cast<char>(key);
    //                 passWord += letter;
    //             }
    //         }
    //     }
    // }

    Vector2 textSize = MeasureTextEx(GetFontDefault(), title, 50, 5);
    DrawText(title, screenWidth / 2 - textSize.x/2, 150, 50, {93, 123, 111, 255});

    Vector2 userNameSize = MeasureTextEx(GetFontDefault(), userName.c_str(), 30, 3);
    // Vector2 passWordSize = MeasureTextEx(GetFontDefault(), passWord.c_str(), 30, 3);

    // if (playerSelection == 1)
    // {
        // userNameSize = MeasureTextEx(GetFontDefault(), userName.c_str(), 30, 3);
        // textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);

        // DrawText(option1, screenWidth / 2 - textSize.x/2 - userNameSize.x/2 , 300, 30, RED);
        // DrawText(userName.c_str(), screenWidth / 2 + textSize.x/2 - userNameSize.x/2 , 300, 30, RED);
    // }
    // else
    // {
        userNameSize = MeasureTextEx(GetFontDefault(), userName.c_str(), 30, 4);
        textSize = MeasureTextEx(GetFontDefault(), option1, 30, 3);
        DrawText(option1, screenWidth / 2 - textSize.x/2 - userNameSize.x/2, 350, 30, GRAY);
        DrawText(userName.c_str(), screenWidth / 2 + textSize.x/2 - userNameSize.x/2, 350, 30, GRAY);

        
        textSize = MeasureTextEx(GetFontDefault(), title2, 30, 3);
        DrawText(title2, screenWidth / 2 - textSize.x/2, 500, 30, GRAY);
    // }
    // if (playerSelection == 2)
    // {
    //     passWordSize = MeasureTextEx(GetFontDefault(), passWord.c_str(), 30, 3);
    //     textSize = MeasureTextEx(GetFontDefault(), option2, 30, 3);
    //     DrawText(option2, screenWidth / 2 - textSize.x/2 - passWordSize.x/2, 400, 30, RED);
    //     DrawText(passWord.c_str(), screenWidth / 2 + textSize.x/2 - passWordSize.x/2, 400, 30, RED);
    // }
    // else
    // {
    //     passWordSize = MeasureTextEx(GetFontDefault(), passWord.c_str(), 30, 3);
    //     textSize = MeasureTextEx(GetFontDefault(), option2, 30, 3);
    //     DrawText(option2, screenWidth / 2 - textSize.x/2 - passWordSize.x/2, 400, 30, GRAY);
    //     DrawText(passWord.c_str(), screenWidth / 2 + textSize.x/2 - passWordSize.x/2, 400, 30, RED);
    // }

}