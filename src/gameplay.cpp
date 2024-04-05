#include "gameplay.h"

using namespace std;
void free2DArray(Pokemon** arr, int rows)
{
    // Giải phóng từng hàng của mảng
    for (int i = 0; i < rows; ++i) {
        delete[] arr[i];
    }
    // Giải phóng con trỏ đến mảng chính
    delete[] arr;
}
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
// Point *zMatching(Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
// {
//     if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key || playerPosX == playerPosXX && playerPosY == playerPosYY)
//     {
//         return NULL;
//     }
//     if (pokeArr[playerPosY][playerPosX].deleted == true || pokeArr[playerPosYY][playerPosXX].deleted == true) return NULL;
//     Point* pHead = NULL;

//     // chắc chắn rằng playerPosX playerPosY luôn là điểm nằm bên trái
//     if (playerPosX > playerPosXX)
//     {
//         swap(playerPosX, playerPosXX);
//         swap(playerPosY, playerPosYY);
//     }
//     // kiểm tra xem điểm còn lại nằm ở trên hay dưới
//     // z doc
//     if (playerPosY > playerPosYY) // nếu nằm ở trên
//     {
//         for (int i = 1; i <  playerPosXX - playerPosX; i++)
//         {
//             bool breakOut = false;
//             if (pokeArr[playerPosY][playerPosX + i].deleted && pokeArr[playerPosYY][playerPosX + i].deleted)
//             {
//                 for (int s = 0; s + i + playerPosX < playerPosXX; s++)
//                 {
//                     if(pokeArr[playerPosYY][playerPosX + i + s].deleted == false) breakOut = true;
//                 }
//             if (breakOut == true) continue;
//                 for (int j = 0; j <= playerPosY - playerPosYY; j++)
//                 {
//                     if (pokeArr[playerPosY - j][playerPosX + i].deleted == false)
//                     {
//                         break;
//                     }
//                     if (j == playerPosY - playerPosYY)
//                     {
//                         addTail(pHead, playerPosX, playerPosY);
//                         addTail(pHead, playerPosX + i, playerPosY);
//                         addTail(pHead, playerPosX + i, playerPosY);
//                         addTail(pHead, playerPosX + i, playerPosY - j);
//                         addTail(pHead, playerPosX + i, playerPosY - j);
//                         addTail(pHead, playerPosXX, playerPosYY);
//                         return pHead;
//                     }
//                 }
//             }
//         }
//     //z ngang 
//         for (int i = 1; i <  playerPosY - playerPosYY; i++)
//         {
//             bool breakOut = false;
//             if (pokeArr[playerPosY - i][playerPosX].deleted && pokeArr[playerPosY - i][playerPosXX].deleted)
//             {
//                 for (int s = 0; playerPosY - i - s > playerPosYY; s++)
//                 {
//                     if(pokeArr[playerPosY - i - s][playerPosXX].deleted == false) breakOut = true;
//                 }
//                 if (breakOut == true) continue;
//                 for (int j = 0; j <= playerPosXX - playerPosX; j++)
//                 {
//                     if (pokeArr[playerPosY - i][playerPosX + j].deleted == false)
//                     {
//                         break;
//                     }
//                     if (j == playerPosXX - playerPosX)
//                     {
//                         addTail(pHead, playerPosX, playerPosY);
//                         addTail(pHead, playerPosX, playerPosY - i);
//                         addTail(pHead, playerPosX, playerPosY - i);
//                         addTail(pHead, playerPosX + j, playerPosY - i);
//                         addTail(pHead, playerPosX + j, playerPosY - i);
//                         addTail(pHead, playerPosXX, playerPosYY);
//                         return pHead;
//                     }
//                 }
//             }
//         }
//     }
//     if (playerPosY < playerPosYY) // nếu nằm dưới 
//     {
//         //z doc
//         for (int i = 1; i <  playerPosXX - playerPosX; i++)
//         {
//             bool breakOut = false;
//             if (pokeArr[playerPosY][playerPosX + i].deleted && pokeArr[playerPosYY][playerPosX + i].deleted)
//             {
//                 for (int s = 0; s + i + playerPosX < playerPosXX; s++)
//                 {
//                     if(pokeArr[playerPosYY][playerPosX + i + s].deleted == false) breakOut = true;
//                 }

//                 if (breakOut == true) continue;

//                 for (int j = 0; j <= playerPosYY - playerPosY; j++)
//                 {
//                     if (pokeArr[playerPosY + j][playerPosX + i].deleted == false)
//                     {
//                         break;
//                     }
//                     if (j == playerPosYY - playerPosY)
//                     {
//                         addTail(pHead, playerPosX, playerPosY);
//                         addTail(pHead, playerPosX + i, playerPosY);
//                         addTail(pHead, playerPosX + i, playerPosY);
//                         addTail(pHead, playerPosX + i, playerPosY + j);
//                         addTail(pHead, playerPosX + i, playerPosY + j);
//                         addTail(pHead, playerPosXX, playerPosYY);
//                         return pHead;
//                     }      
//                 }
//             }
//         }
//         // z ngang
//         for (int i = 1; i <  playerPosYY - playerPosY; i++)
//         {
//             bool breakOut = false;
//             if (pokeArr[playerPosY + i][playerPosX].deleted && pokeArr[playerPosY + i][playerPosXX].deleted)
//             {
//                 for (int s = 0; playerPosY + i + s < playerPosYY; s++)
//                 {
//                     if(pokeArr[playerPosY + i + s][playerPosXX].deleted == false) breakOut = true;
//                 }

//                 if (breakOut == true) continue;

//                 for (int j = 0; j <= playerPosXX - playerPosX; j++)
//                 {
//                     if (pokeArr[playerPosY + i][playerPosX + j].deleted == false)
//                     {
//                         break;
//                     }
//                     if (j == playerPosXX - playerPosX)
//                     {
//                         addTail(pHead, playerPosX, playerPosY);
//                         addTail(pHead, playerPosX, playerPosY + i);
//                         addTail(pHead, playerPosX, playerPosY + i);
//                         addTail(pHead, playerPosX + j, playerPosY + i);
//                         addTail(pHead, playerPosX + j, playerPosY + i);
//                         addTail(pHead, playerPosXX, playerPosYY);
//                         return pHead;
//                     }
//                 }
//             }
//         }
//     }
//     return NULL;
// }
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
Point *lMatching(Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    // base condition
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key || playerPosXX == playerPosX && playerPosY == playerPosYY)
    return NULL;
    if (pokeArr[playerPosY][playerPosX].deleted == true || pokeArr[playerPosYY][playerPosXX].deleted == true) return NULL;

    // tạo List các điểm 
    Point* pHead = NULL;

    // chắc chắn rằng điểm playerPosX , playerPosY luôn là điểm nằm bên trái
    if (playerPosX > playerPosXX)
    {
        swap(playerPosX, playerPosXX);
        swap(playerPosY, playerPosYY);
    }

    // nếu điểm còn lại ở trên
    if (playerPosYY < playerPosY)
    {
        // duyệt qua phải
        for (int i = 1; i <= playerPosXX - playerPosX; i++)
        {
            if (pokeArr[playerPosY][playerPosX + i].deleted == false)
            break; // nếu đường đi bị chặn thì hủy không chạy nữa chuyển sang trường hợp dưới

            if (i == playerPosXX - playerPosX)
            {
                // duyệt lên
                for (int j = 0; j < playerPosY - playerPosYY; j++)
                {
                    // nếu bị chặn đường thì chuyển sang trường hợp khác
                    if (pokeArr[playerPosY - j][playerPosX + i].deleted == false)
                    {
                        break;
                    }
                    // nếu thỏa điều kiện đã chạy tới ô cần xét
                    if (j == playerPosY - playerPosYY - 1)
                    {
                        // gán điểm 
                        addTail(pHead, playerPosX, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosX + i, playerPosY);
                        addTail(pHead, playerPosXX, playerPosYY);
                        return pHead;
                    }
                }
            }
        }
        // Duyệt lên rồi qua phải
        for (int i = 1; i <= playerPosY - playerPosYY; i++)
        {
            if (pokeArr[playerPosY - i][playerPosX].deleted == false)
            break; // nếu đường đi bị chặn thì hủy không chạy nữa chuyển sang trường hợp dưới

            if (i == playerPosY - playerPosYY)
            {
                // duyệt qua Phải
                for (int j = 0; j < playerPosXX - playerPosX; j++)
                {
                    // nếu bị chặn đường thì chuyển sang trường hợp khác
                    if (pokeArr[playerPosY - i][playerPosX + j].deleted == false)
                    {
                        break;
                    }
                    // nếu thỏa điều kiện đã chạy tới ô cần xét
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
    // nếu điểm còn lại ở dưới 
    if (playerPosYY > playerPosY)
    {
        // duyệt qua phải
        for (int i = 1; i <= playerPosXX - playerPosX; i++)
        {
            if (pokeArr[playerPosY][playerPosX + i].deleted == false)
            break; // nếu đường đi bị chặn thì hủy không chạy nữa chuyển sang trường hợp dưới

            if (i == playerPosXX - playerPosX)
            {
                // duyệt xuống
                for (int j = 0; j < playerPosYY - playerPosY; j++)
                {
                    // nếu bị chặn đường thì chuyển sang trường hợp khác
                    if (pokeArr[playerPosY + j][playerPosX + i].deleted == false)
                    {
                        break;
                    }
                    // nếu thỏa điều kiện đã chạy tới ô cần xét
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
        // duyệt xuống rồi qua phải 
        for (int i = 1; i <= playerPosYY - playerPosY; i++)
        {
            if (pokeArr[playerPosY + i][playerPosX].deleted == false)
            break; // nếu đường đi bị chặn thì hủy không chạy nữa chuyển sang trường hợp dưới

            if (i == playerPosYY - playerPosY)
            {
                // duyệt qua phải
                for (int j = 0; j < playerPosXX - playerPosX; j++)
                {
                    // nếu bị chặn đường thì chuyển sang trường hợp khác
                    if (pokeArr[playerPosY + i][playerPosX + j].deleted == false)
                    {
                        break;
                    }
                    // nếu thỏa điều kiện đã chạy tới ô cần xét
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
Point* iMatching (Pokemon **pokeArr, int playerPosX, int playerPosY, int playerPosXX, int playerPosYY)
{
    //ignore if they are not same or if they are one
    if (pokeArr[playerPosY][playerPosX].key != pokeArr[playerPosYY][playerPosXX].key || playerPosX == playerPosXX && playerPosY == playerPosYY) return NULL;
    if (pokeArr[playerPosY][playerPosX].deleted == true || pokeArr[playerPosYY][playerPosXX].deleted == true) return NULL;
    //create point list
    Point *pHead = NULL;

    if (playerPosY == playerPosYY)
    {
        if (playerPosX > playerPosXX) swap(playerPosX, playerPosXX);

        for (int i = playerPosX + 1; i < playerPosXX; i++)
        {
            if (pokeArr[playerPosY][i].deleted == false) return NULL;
        }
        // input point for list
        pHead = createNodes(playerPosX, playerPosY);
        pHead -> next = createNodes(playerPosXX,playerPosYY);
        return pHead;
    }

    if (playerPosXX == playerPosX)
    {
        if (playerPosY > playerPosYY) swap(playerPosY, playerPosYY);

        for (int i = playerPosY + 1; i < playerPosYY; i++)
        {
            if (pokeArr[i][playerPosX].deleted == false) return NULL;
        }
        // input point for list
        pHead = createNodes(playerPosX, playerPosY);
        pHead -> next = createNodes(playerPosXX,playerPosYY);
        return pHead;
    }
    return NULL;
}
void drawLine(Point* pHead, int scaledWidth, int scaledHeight)
{
    if (pHead == NULL) return;

    Point *pCur = pHead->next;
    Point *pPrev = pHead;


        while (pCur != NULL)
        {
            // Gan diem dau va cuoi cua duong thang theo kich thuoc cua o
            Vector2 point1 = {(pPrev->x * (scaledWidth + 5) + scaledWidth / 2), (pPrev->y * (scaledHeight + 5) + scaledHeight / 2)};
            Vector2 point2 = {(pCur->x * (scaledWidth + 5) + scaledWidth / 2), (pCur->y * (scaledHeight + 5) + scaledHeight / 2)};
            DrawCircle((pPrev->x * (scaledWidth + 5) + scaledWidth / 2), (pPrev->y * (scaledHeight + 5) + scaledHeight / 2), 5, BLUE);
            DrawLineEx(point1, point2, 3, BLUE);// Ve duong thang
            DrawCircle((pCur->x * (scaledWidth + 5) + scaledWidth / 2), (pCur->y * (scaledHeight + 5) + scaledHeight / 2), 5, BLUE);

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
void createTable(Pokemon** &resArr, int row, int col, int nPicture)
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
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        i++;
        temp[i].deleted = false;
        temp[i].key = randomNumber;
        i++; 
    }

    shufflePokemonArray(temp, size);
    shufflePokemonArray(temp, size);

    cout << "flag";
    resArr = new Pokemon*[row];
    cout << "flag";
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
                resArr[i][j].key = temp[count].key;
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
// Pokemon **createTable(int row, int col, Texture2D *texture, int nPicture)
// {   
//     srand(time(NULL)); // Seed random number generator
    
//     // Calculate total number of non-border cells
//     int innerSize = (row - 2) * (col - 2);
    
//     // Create a temporary array to hold shuffled Pokémon
//     Pokemon *temp = new Pokemon[innerSize * 2];
    
//     // Generate random Pokémon
//     for (int i = 0; i < innerSize * 2; i += 2)
//     {
//         int randomNumber = rand() % nPicture;
//         temp[i].pokeImage = texture[randomNumber];
//         temp[i].deleted = false;
//         temp[i].key = randomNumber;
//         temp[i + 1] = temp[i]; // Assign the same Pokémon to the next cell
//     }

//     // Shuffle Pokémon array
//     shufflePokemonArray(temp, innerSize * 2);
//     shufflePokemonArray(temp, innerSize * 2);

//     // Create the 2D array
//     Pokemon **resArr = new Pokemon *[row];
//     for (int i = 0; i < row; i++)
//     {
//         resArr[i] = new Pokemon[col];
//     }

//     // Assign Pokémon to cells
//     int count = 0;
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < col; j++)
//         {
//             if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
//             {
//                 resArr[i][j].deleted = true;
//                 resArr[i][j].pokeImage = temp[0].pokeImage; // Use the first Pokémon's image for border cells
//                 resArr[i][j].key = temp[count].key;
//             }
//             else
//             {
//                 resArr[i][j].deleted = temp[count].deleted;
//                 resArr[i][j].pokeImage = temp[count].pokeImage;
//                 resArr[i][j].key = temp[count].key;
//                 count++;
//             }
//         }
//     }

//     // Cleanup
//     delete[] temp;
    
//     return resArr;
// }

// void drawTable(Pokemon **a, int row, int col, const int scaledWidth, const int scaledHeight, int playerPosX, int playerPosY)
// {
//     for (int i = 0; i < row; i++)
//     {
//         for (int j = 0; j < col; j++)
//         {
//             if(a[i][j].deleted == false || (j == playerPosX && i == playerPosY))
//             {
//                 //sourceRec is a size of source image destRec, is size of the out put image
//                 Rectangle sourceRec = { 0, 0, (a[i][j].key).width, (a[i][j].pokeImage).height };
//                 Rectangle destRec = { j * (scaledWidth + 5), i * (scaledHeight + 5), scaledWidth, scaledHeight};
//                 Rectangle destLineRec = { j * (scaledWidth + 5) - 5, i * (scaledHeight + 5) - 5, scaledWidth + 10, scaledHeight + 10};

//             if (a[i][j].deleted == true)
//             {
//                 // DrawRectangle(j * (scaledWidth + 5), i * (scaledHeight + 5), scaledWidth, scaledHeight, Fade(LIGHTGRAY, 0.5f));
//                 DrawRectangleLinesEx(destLineRec, 2, DARKGREEN);
//             }
//             else if ((j == playerPosX && i == playerPosY))
//             {
//                 DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, WHITE);
//                 DrawRectangleLinesEx(destLineRec, 5, DARKGREEN);
//             }
//             else
//             {
//                 if (a[i][j].selected == true)
//                 {
//                 DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, WHITE);
//                 DrawRectangleLinesEx(destLineRec, 5, DARKGREEN);
//                 }
//                 else
//                 DrawTexturePro(a[i][j].pokeImage, sourceRec, destRec, {0, 0}, 0, WHITE);
//             }
//             }
//         }
//     }
// }
void drawTable(Pokemon **a, int row, int col, const int scaledWidth, const int scaledHeight, int playerPosX, int playerPosY, Texture2D *texture)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if(a[i][j].deleted == false || (j == playerPosX && i == playerPosY))
            {
                //sourceRec is a size of source image destRec, is size of the out put image
                Rectangle sourceRec = { 0, 0, (texture[a[i][j].key]).width, (texture[a[i][j].key]).height };
                Rectangle destRec = { j * (scaledWidth + 5), i * (scaledHeight + 5), scaledWidth, scaledHeight};
                Rectangle destLineRec = { j * (scaledWidth + 5) - 5, i * (scaledHeight + 5) - 5, scaledWidth + 10, scaledHeight + 10};

            if (a[i][j].deleted == true)
            {
                // DrawRectangle(j * (scaledWidth + 5), i * (scaledHeight + 5), scaledWidth, scaledHeight, Fade(LIGHTGRAY, 0.5f));
                DrawRectangleLinesEx(destLineRec, 2, DARKGREEN);
            }
            else if ((j == playerPosX && i == playerPosY))
            {
                DrawTexturePro(texture[a[i][j].key], sourceRec, destRec, {0, 0}, 0, WHITE);
                DrawRectangleLinesEx(destLineRec, 5, DARKGREEN);
            }
            else
            {
                if (a[i][j].selected == true)
                {
                DrawTexturePro(texture[a[i][j].key], sourceRec, destRec, {0, 0}, 0, WHITE);
                DrawRectangleLinesEx(destLineRec, 5, DARKGREEN);
                }
                else
                DrawTexturePro(texture[a[i][j].key], sourceRec, destRec, {0, 0}, 0, WHITE);
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
int calScore(int x_1, int y_1, int x_2, int y_2, char key)
{
    int x = x_2 - x_1, y = y_2 - y_1;
    if (x < 0) x = 0 - x;
    if (y < 0) y = 0 - y;
    switch(key){
        case 'i' : return (x + y)*5 + 10;
        case 'l' : return (x + y)*5 + 30;
        case 'u' : return (x + y)*5 + 30;
        case 'z' : return (x + y)*5 + 30;
    }
    return 0;
}
void updateTable(Pokemon **pokeArr, int &playerPosX, int &playerPosY, int row, int col, bool &firstSelectionDone, int &selectedX, int &selectedY, Point* &pointList, float &matchingTime, int &scoree, bool &isMatching)
{
    Point* temp = NULL;
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_SPACE)) {
        if (!firstSelectionDone) {
            if (IsKeyPressed(KEY_RIGHT) && playerPosX < col - 2) {
                playerPosX++;
            } else if (IsKeyPressed(KEY_LEFT) && playerPosX > 1) {
                playerPosX--;
            } else if (IsKeyPressed(KEY_UP) && playerPosY > 1) {
                playerPosY--;
            } else if (IsKeyPressed(KEY_DOWN) && playerPosY < row - 2) {
                playerPosY++;
            } else if (IsKeyPressed(KEY_SPACE)) {
                firstSelectionDone = true;
                selectedX = playerPosX;
                selectedY = playerPosY;
                pokeArr[selectedY][selectedX].selected = true;
            }
        } else {
            if (IsKeyPressed(KEY_RIGHT) && playerPosX < col - 2) {
                playerPosX++;
            } else if (IsKeyPressed(KEY_LEFT) && playerPosX > 1) {
                playerPosX--;
            } else if (IsKeyPressed(KEY_UP) && playerPosY > 1) {
                playerPosY--;
            } else if (IsKeyPressed(KEY_DOWN) && playerPosY < row - 2) {
                playerPosY++;
            } else if (IsKeyPressed(KEY_SPACE)) {
                firstSelectionDone = false; // Reset for next selection
                if (temp = iMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                {
                    cout << "imatching " << endl;
                    clearList(pointList);
                    pointList = temp;
                    // drawLine(pointList, 60 , 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                    isMatching = true;
                    matchingTime = GetTime();
                    scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'i');
                }
                else if(temp = zMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                {
                    cout << "zmatching" << endl;
                    clearList(pointList);
                    pointList = temp;
                    // drawLine(pointList, 60, 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                    isMatching = true;
                    matchingTime = GetTime();
                    scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'z');
                }
                else if(temp = lMatching(pokeArr, selectedX, selectedY, playerPosX, playerPosY))
                {
                    cout << "lmatching" << endl;
                    clearList(pointList);
                    pointList = temp;
                    // drawLine(pointList, 60 , 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                    isMatching = true;
                    matchingTime = GetTime();
                    scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'l');
                }
                else if(temp = uMatching(pokeArr, row, col, selectedX, selectedY, playerPosX, playerPosY))
                {
                    cout << "umatching"<< endl;
                    clearList(pointList);
                    pointList = temp;
                    // drawLine(pointList, 60 , 60);
                    deleteCell(pokeArr, selectedX, selectedY);
                    deleteCell(pokeArr, playerPosX, playerPosY);
                    matchingTime = GetTime();
                    isMatching = true;
                    scoree += calScore(selectedX, selectedY, playerPosX, playerPosY, 'u');
                }
                else if (scoree - 20 > 0)
                {
                    scoree -= 20;
                }
                
                pokeArr[selectedY][selectedX].selected = false;
            }
        }
    }
}

bool suggestion(Pokemon **pokeArr, int row, int col, Point *&pointList){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (pokeArr[i][j].deleted == false){
                for (int k = 0; k < row; k++){
                    for (int l = 0; l < col; l++){
                        if (!(i == k && j == l)){
                            Point* p1 = uMatching(pokeArr, row, col, j, i, l, k);
                            if (p1 != NULL){
                                pointList = p1;
                                // matchingTime = GetTime();
                                return true;
                            }
                            Point* p2 = zMatching(pokeArr, j, i, l, k);
                            if (p2 != NULL){
                                pointList = p2;
                                // matchingTime = GetTime();
                                return true;
                            }
                            Point* p3 = lMatching(pokeArr, j, i, l, k);
                            if (p3 != NULL){
                                pointList = p3;
                                // matchingTime = GetTime();
                                return true;
                            }
                            Point* p4 = iMatching(pokeArr, j, i, l, k);
                            if (p4 != NULL){
                                pointList = p4;
                                // matchingTime = GetTime();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    pointList = NULL;
    return false;
}
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
bool suggestionButItJustForDeveloper(Pokemon **pokeArr, int row, int col, Point *&pointList, float &matchingTime){
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            if (pokeArr[i][j].deleted == false){
                for (int k = 0; k < row; k++){
                    for (int l = 0; l < col; l++){
                        if (!(i == k && j == l)){
                            Point* p1 = uMatching(pokeArr, row, col, j, i, l, k);
                            if (p1 != NULL){
                                pointList = p1;
                                matchingTime = GetTime();
                                return true;
                            }
                            Point* p2 = zMatching(pokeArr, j, i, l, k);
                            if (p2 != NULL){
                                pointList = p2;
                                matchingTime = GetTime();
                                return true;
                            }
                            Point* p3 = lMatching(pokeArr, j, i, l, k);
                            if (p3 != NULL){
                                pointList = p3;
                                matchingTime = GetTime();
                                return true;
                            }
                            Point* p4 = iMatching(pokeArr, j, i, l, k);
                            if (p4 != NULL){
                                pointList = p4;
                                matchingTime = GetTime();
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void hintshuffle(Pokemon **pokeArr, int row, int col)
{
    int left = 0;
    bool del[row - 2][col - 2];
    for (int i = 1; i < row - 1; i++){
        for (int j = 1; j < col - 1; j++){
            if (pokeArr[i][j].deleted)
                del[i][j] = true;
            else {
                del[i][j] = false;
                left++;
            }
        }
    }
    srand(time(0));
    for (int i = 1; i < row - 1; i++){
        for (int j = 1; j < col - 1; j++){
            if (left == 0) return;
            if(del[i][j] == false){
                int k = i, l = j;
                while ((k == i && l == j) || del[k][l] == true){
                    k = (rand() % (row - 2)) + 1;
                    l = (rand() % (col - 2)) + 1;
                }
                swapPokemon(pokeArr[i][j], pokeArr[k][l]);
                del[i][j] = true;
                del[k][l] = true;
                left -= 2;
            }
        }
    }
}