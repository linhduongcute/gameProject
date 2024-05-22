#ifndef INIT_SCREEN_H_
#define INIT_SCREEN_H_

#include <SDL.h>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 675;
const static char* WINDOW_TITLE = "money money I want it!";

void logErrorAndExit(const char* msg, const char* error);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();

#endif // INIT_SCREEN_H_


