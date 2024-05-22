#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "class.h"
#include "collisionDetection.h"
#include "renderScreen.h"
#include "sound.h"

int objW = 50;
int objH = 35;
int playerW = 100;
int playerH = 100;

bool checkCollision(int objX, int objY, int playerX, int playerY) {
    // Xác định các cạnh của hình chữ nhật A
    int leftA = objX;
    int rightA = objX + objW;
    int topA = objY;
    int bottomA = objY + objH;

    // Xác định các cạnh của hình chữ nhật B
    int leftB = playerX;
    int rightB = playerX + playerW;
    int topB = playerY;
    int bottomB = playerY + playerH;

    // Kiểm tra va chạm giữa hai hình chữ nhật
    if (bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) {
        // Không có va chạm
        return false;
    }
    playMoney();
    // Có va chạm
    return true;
}

bool checkEnd(int objY, int SCREEN_HEIGHT)
{
    int bottomA = objY + objH;
        if (bottomA <= SCREEN_HEIGHT ) {
        return false;
        }
    playDrop();
    return true;
}

bool checkAll(int objX, int objY, int playerX, int playerY, int SCREEN_HEIGHT)
{
    if (checkCollision(objX, objY, playerX, playerY)|| checkEnd(objY, SCREEN_HEIGHT))
    {
        return true;
    }
    return false;
}
