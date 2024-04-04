#include "score.h"

using namespace std;

int calScore(int x_1, int y_1, int x_2, int y_2, char key)
{
    int x = x_2 - x_1, y = y_2 - y_1;
    if (x < 0) x = 0 - x;
    if (y < 0) y = 0 - y;
    switch(key){
        case 'i' : return x + y + 1; break;
        case 'l' : return x + y + 2; break;
        case 'u' : return x + y + 3; break;
        case 'z' : return x + y + 4; break;
    }
    return 0;
}
void displayScore()
{
    
}