#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "collisionDetection.h"
#include "class.h"
#include "renderScreen.h"
#include "text.h"

using namespace std;

SDL_Texture *background2;
SDL_Texture *help1, *help2, *help3;
SDL_Texture *level;
SDL_Texture *background, *cloud, *santa, *player, *object, *heart;
SDL_Texture *gameOver, *playAgain, *yes, *no;

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

void unload_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(cloud);
    SDL_DestroyTexture(santa);
    SDL_DestroyTexture(object);
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(heart);
    SDL_DestroyTexture(gameOver);
    SDL_DestroyTexture(playAgain);
    SDL_DestroyTexture(yes);
    SDL_DestroyTexture(no);
    SDL_DestroyTexture(background2);
    SDL_DestroyTexture(help1);
    SDL_DestroyTexture(help2);
    SDL_DestroyTexture(help3);
    SDL_DestroyTexture(level);
    IMG_Quit();
}

void load_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer)
{
    background = loadTexture("images/background.jpg", renderer);
    cloud = loadTexture("images/cloud.png", renderer);
    santa = loadTexture("images/santa.png", renderer);
    object = loadTexture("images/droppedObject.png", renderer);
    player = loadTexture("images/player.png", renderer);
    heart = loadTexture("images/heart.png", renderer);
    gameOver = loadTexture("images/gameOver.png", renderer);
    background2 = loadTexture("images/background2.png", renderer);
    help1 = loadTexture("images/help1.png", renderer);
    help2 = loadTexture("images/help2.png", renderer);
    help3 = loadTexture("images/help3.png", renderer);
    level = loadTexture("images/level.png", renderer);
    if (background == nullptr  || cloud == nullptr || santa == nullptr ||
        object ==nullptr || player == nullptr || heart == nullptr || gameOver == nullptr ){
        unload_SDL_And_Images(window, renderer);
        exit(1);
    }
}


void renderTexture(SDL_Texture *tex,  int x, int y, SDL_Renderer *ren)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void renderBackground(SDL_Renderer* renderer, int screenWidth, int screenHeight, SDL_Texture *bg) {
    SDL_Rect destRect = {0, 0, screenWidth, screenHeight};
    SDL_RenderCopy(renderer, bg, NULL, &destRect);
}

void showLevel1(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY,  int PLAY_TIMES, int SCREEN_HEIGHT) {
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, background);
    if (PLAY_TIMES!=0)
    {
        renderTexture(santa, 450, 15, renderer);
        if (checkAll(objX, objY, playerX, playerY, SCREEN_HEIGHT)==false)
        {
            renderTexture(object, objX, objY, renderer);
        }
        renderTexture(cloud, 0, 10, renderer);
        renderTexture(player, playerX, playerY, renderer);
        int sum = PLAY_TIMES*30 + 40;
        for (int i = 50; i<sum ; i+=30) {
            renderTexture(heart, i ,  40, renderer);
        }
    }
}

void showLevel2(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY,  int PLAY_TIMES, int SCREEN_HEIGHT) {
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, background);
    if (PLAY_TIMES!=0)
    {
        renderTexture(santa, 450, 15, renderer);
        if (checkAll(objX, objY, playerX, playerY, SCREEN_HEIGHT)==false  && objY<=200)
        {
            renderTexture(object, objX, objY, renderer);
        }
        renderTexture(cloud, 0, 10, renderer);
        renderTexture(player, playerX, playerY, renderer);
        int sum = PLAY_TIMES*30 + 40;
        for (int i = 50; i<sum ; i+=30) {
            renderTexture(heart, i ,  40, renderer);
        }
    }
}

void showLevel3(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY,  int PLAY_TIMES, int SCREEN_HEIGHT) {
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, background);
    if (PLAY_TIMES!=0)
    {
        renderTexture(santa, 450, 15, renderer);
        if (checkAll(objX, objY, playerX, playerY, SCREEN_HEIGHT)==false)
        {
            renderTexture(object, objX, objY, renderer);
        }
        renderTexture(cloud, 0, 10, renderer);
        if (objY<=200) renderTexture(player, playerX, playerY, renderer);
        int sum = PLAY_TIMES*30 + 40;
        for (int i = 50; i<sum ; i+=30) {
            renderTexture(heart, i ,  40, renderer);
        }
    }
}

void showLevel4(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY,  int PLAY_TIMES, int SCREEN_HEIGHT) {
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, background);
    if (PLAY_TIMES!=0)
    {
        renderTexture(santa, 450, 15, renderer);
        if (checkAll(objX, objY, playerX, playerY, SCREEN_HEIGHT)==false  && objY<=200)
        {
            renderTexture(object, objX, objY, renderer);
        }
        renderTexture(cloud, 0, 10, renderer);
        if (objY<=200) renderTexture(player, playerX, playerY, renderer);
        int sum = PLAY_TIMES*30 + 40;
        for (int i = 50; i<sum ; i+=30) {
            renderTexture(heart, i ,  40, renderer);
        }
    }
}

void showEndGame(SDL_Window* window, SDL_Renderer* renderer)
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, gameOver);
}

void showStartGame(SDL_Window* window, SDL_Renderer* renderer)
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, background2);
}

void showHelp1(SDL_Window* window, SDL_Renderer* renderer)
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, help1);
}

void showHelp2(SDL_Window* window, SDL_Renderer* renderer)
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, help2);
}

void showHelp3(SDL_Window* window, SDL_Renderer* renderer)
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, help3);
}

void showLevel(SDL_Window* window, SDL_Renderer* renderer)
{
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    renderBackground(renderer, screenWidth, screenHeight, level);
}

void clean(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
}

