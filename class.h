#ifndef CLASS_H_
#define CLASS_H_

#include <random>
#include "initScreen.h"
#include "renderScreen.h"

class Object
{
public:
    int objX, objY;
    int velY;
    SDL_Renderer* renderer;
    SDL_Texture* pObject;

    int randomPosition() {
        return (rand() % 1000) + 50;
    }
    Object()
    {
        objX = randomPosition();
        objY = 115;
        velY = 1;
    }

    void update() {
        objY += velY;
    }
};

class Player
{
public:
    int playerX, playerY;
    int velX;
    SDL_Renderer* renderer;
    SDL_Texture *pPlayer = NULL;

    int randomPosition() {
        return (rand() % 1100) + 1;
    }

    Player()
    {
        playerX = randomPosition();
        playerY = 500;
        velX = 10;
    }
    void move() {
        playerX += velX;
    }
};

#endif //CLASS_H_

