// #include "raylib.h"

// // Định nghĩa các trạng thái của màn hình
// typedef enum {
//     MAIN_MENU,
//     GAMEPLAY,
//     OPTIONS,
//     PAUSE
// } Screen;

// int main(void) {
//     const int screenWidth = 800;
//     const int screenHeight = 450;

//     InitWindow(screenWidth, screenHeight, "Screen Management Example");

//     // Khởi tạo trạng thái màn hình ban đầu
//     Screen currentScreen = MAIN_MENU;

//     SetTargetFPS(60);

//     while (!WindowShouldClose()) {
//         // Update logic tùy thuộc vào trạng thái màn hình hiện tại
//         switch (currentScreen) {
//             case MAIN_MENU:
//                 // Xử lý logic cho màn hình menu
//                 if (IsKeyPressed(KEY_ENTER)) {
//                     // Chuyển sang màn hình gameplay nếu nhấn phím Enter
//                     currentScreen = GAMEPLAY;
//                 }
//                 break;
//             case GAMEPLAY:
//                 // Xử lý logic cho màn hình gameplay
//                 if (IsKeyPressed(KEY_P)) {
//                     // Chuyển sang màn hình pause nếu nhấn phím P
//                     currentScreen = PAUSE;
//                 }
//                 // Thêm logic gameplay ở đây
//                 break;
//             case OPTIONS:
//                 // Xử lý logic cho màn hình options
//                 // Thêm logic options ở đây
//                 break;
//             case PAUSE:
//                 // Xử lý logic cho màn hình pause
//                 if (IsKeyPressed(KEY_P)) {
//                     // Quay lại màn hình gameplay nếu nhấn phím P
//                     currentScreen = GAMEPLAY;
//                 }
//                 // Thêm logic pause ở đây
//                 break;
//         }

//         // Vẽ các đối tượng tương ứng với trạng thái màn hình hiện tại
//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         switch (currentScreen) {
//             case MAIN_MENU:
//                 DrawText("Main Menu", screenWidth / 2 - MeasureText("Main Menu", 40) / 2, screenHeight / 2 - 20, 40, BLACK);
//                 break;
//             case GAMEPLAY:
//                 DrawText("Gameplay", screenWidth / 2 - MeasureText("Gameplay", 40) / 2, screenHeight / 2 - 20, 40, BLACK);
//                 break;
//             case OPTIONS:
//                 DrawText("Options", screenWidth / 2 - MeasureText("Options", 40) / 2, screenHeight / 2 - 20, 40, BLACK);
//                 break;
//             case PAUSE:
//                 DrawText("Pause", screenWidth / 2 - MeasureText("Pause", 40) / 2, screenHeight / 2 - 20, 40, BLACK);
//                 break;
//         }

//         EndDrawing();
//     }

//     CloseWindow();

//     return 0;
// }
