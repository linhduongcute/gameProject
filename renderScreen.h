#ifndef RENDER_SCREEN_H_
#define RENDER_SCREEN_H_

#include "class.h"

void load_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer);
void unload_SDL_And_Images(SDL_Window* window, SDL_Renderer* renderer);
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer);
void renderBackground(SDL_Renderer* renderer, int screenWidth, int screenHeight);
void showLevel1(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY, int PLAY_TIMES, int SCREEN_HEIGHT);
void showLevel2(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY, int PLAY_TIMES, int SCREEN_HEIGHT);
void showLevel3(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY, int PLAY_TIMES, int SCREEN_HEIGHT);
void showLevel4(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY, int PLAY_TIMES, int SCREEN_HEIGHT);
void clean(SDL_Renderer* renderer);
void showEndGame(SDL_Window* window, SDL_Renderer* renderer);
void showStartGame(SDL_Window* window, SDL_Renderer* renderer);
void showHelp1(SDL_Window* window, SDL_Renderer* renderer);
void showHelp2(SDL_Window* window, SDL_Renderer* renderer);
void showHelp3(SDL_Window* window, SDL_Renderer* renderer);
void showLevel(SDL_Window* window, SDL_Renderer* renderer);

#endif // RENDER_SCREEN_H_
