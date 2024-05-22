#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "initScreen.h"
#include "renderScreen.h"
#include "class.h"
#include "collisionDetection.h"
#include "text.h"
#include "sound.h"

using namespace std;

int RENDER_TIME = SDL_GetTicks();
int DELAY_TIME = 500 - RENDER_TIME;
static int SCORE = 0;
int PLAY_TIMES = 3;
static int HIGH_SCORE_LEVEL_1;
static int HIGH_SCORE_LEVEL_2;
static int HIGH_SCORE_LEVEL_3;
static int HIGH_SCORE_LEVEL_4;
/*****************************************************/
bool canCatch = true;
bool checkPlay = false;
bool startGame(int x, int y);
bool checkLevel(int x, int y);
bool level1 = false;
bool level2 = false;
bool level3 = false;
bool level4 = false;
bool help(int x, int y);
bool next1(int x, int y);
bool next2(int x, int y);
bool back(int x, int y);
bool quit(int x, int y);
bool checkYes(int x, int y);
bool checkNo(int x, int y);
bool checkLevel(int x, int y);
void endGame();
void show(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY, int PLAY_TIMES, int SCREEN_HEIGHT);
void chooseLevel(SDL_Window* window, SDL_Renderer* renderer,SDL_Event e);
void highScore(int score);
void checkRenderHighScore(SDL_Window* window, SDL_Renderer* renderer);
/*****************************************************/
int main(int argc, char *argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    int mouseX = 0, mouseY = 0;

    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    load_SDL_And_Images(window, renderer);
    loadAudio();
    showStartGame(window, renderer);
    SDL_RenderPresent(renderer);
    SDL_Event e;
    while (true) {
        SDL_Delay(10);

        if (SDL_WaitEvent(&e) == 0) continue;
        if (e.type == SDL_QUIT) break;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) { break; }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            playClick();
            mouseX = e.button.x;
            mouseY = e.button.y;
            if (startGame(mouseX, mouseY))
            {
            chooseLevel(window, renderer, e);
            if(checkPlay) break;
            }
            if (help(mouseX, mouseY))
            {
                showHelp1(window, renderer);
                SDL_RenderPresent(renderer);
                while (true) {
                    SDL_Delay(10);
                    if (SDL_WaitEvent(&e) == 0) continue;
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        playClick();
                        mouseX = e.button.x;
                        mouseY = e.button.y;
                        if (next1(mouseX, mouseY)){
                            showHelp2(window, renderer);
                            SDL_RenderPresent(renderer);
                            while (true) {
                                SDL_Delay(10);
                                if (SDL_WaitEvent(&e) == 0) continue;
                                if (e.type == SDL_MOUSEBUTTONDOWN) {
                                    playClick();
                                    mouseX = e.button.x;
                                    mouseY = e.button.y;
                                    if (next2(mouseX, mouseY)){
                                        showHelp3(window, renderer);
                                        SDL_RenderPresent(renderer);
                                        while (true) {
                                            SDL_Delay(10);
                                            if (SDL_WaitEvent(&e) == 0) continue;
                                            if (e.type == SDL_MOUSEBUTTONDOWN) {
                                                playClick();
                                                mouseX = e.button.x;
                                                mouseY = e.button.y;
                                                if (back(mouseX,mouseY)) {
                                                    showHelp2(window, renderer);
                                                    SDL_RenderPresent(renderer);
                                                    break;
                                                }
                                                else continue;
                                            }
                                        }
                                    }
                                    else if (back(mouseX,mouseY)) {
                                        showHelp1(window, renderer);
                                        SDL_RenderPresent(renderer);
                                        break;
                                    }
                                    else continue;
                                }
                            }
                        }
                        else if (back(mouseX,mouseY)) {
                            showStartGame(window, renderer);
                            SDL_RenderPresent(renderer);
                            break;
                        }
                        else continue;
                    }
                }
            }
            if (quit(mouseX, mouseY))
            {
                break;
            }
        }
    }
    while (checkPlay) {
        Player player;
        while (canCatch) {
            Object object;
            SDL_Event e;
            while (true) {
                while (SDL_PollEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        canCatch = false;
                        quitSDL(window, renderer);
                        return 0;
                    }
                    if (e.type == SDL_KEYDOWN) {
                        if (e.key.keysym.sym == SDLK_LEFT) {
                                player.playerX -= player.velX;
                        }
                        if (e.key.keysym.sym == SDLK_RIGHT) {
                                player.playerX += player.velX;
                        }
                        if (e.key.keysym.sym == SDLK_ESCAPE) {
                            quitSDL(window, renderer);
                            return 0;
                        }
                    }
                }
                object.update();
                if (checkCollision(object.objX, object.objY, player.playerX, player.playerY) == false) {
                    clean(renderer);
                    show(window, renderer, object.objX, object.objY, player.playerX, player.playerY, PLAY_TIMES, SCREEN_HEIGHT);
                    renderScore(window, renderer, SCORE, 1000, 40);
                    checkRenderHighScore(window, renderer);
                    SDL_RenderPresent(renderer);
                }
                if (checkCollision(object.objX, object.objY, player.playerX, player.playerY)) {
                    clean(renderer);
                    show(window, renderer, object.objX, object.objY, player.playerX, player.playerY, PLAY_TIMES, SCREEN_HEIGHT);
                    SCORE += 100;
                    highScore(SCORE);
                    renderScore(window, renderer, SCORE, 1000, 40);
                    checkRenderHighScore(window, renderer);
                    SDL_RenderPresent(renderer);
                    break;
                }
                if (checkEnd(object.objY, SCREEN_HEIGHT)) {
                    PLAY_TIMES --;
                    break;
                }
            }
            if (PLAY_TIMES == 0)
            {
                clean(renderer);
                while (true) {
                    endGame();
                    showEndGame(window, renderer);
                    renderScoreEndGame(window, renderer, SCORE, 430, 330);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(10);
                    if ( SDL_WaitEvent(&e) == 0) continue;
                    if (e.type == SDL_QUIT) break;
                    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) break;
                    if (e.type == SDL_MOUSEBUTTONDOWN) {
                        playClick();
                        mouseX = e.button.x;
                        mouseY = e.button.y;
                        if (checkYes(mouseX, mouseY))
                        {
                            endGame();
                            PLAY_TIMES = 3;
                            SCORE = 0;
                            chooseLevel(window, renderer, e);
                            break;
                        }
                        if (checkNo(mouseX, mouseY))
                        {
                            endGame();
                            checkPlay = false;
                            break;
                            quitSDL(window, renderer);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    quitSDL(window, renderer);
    return 0;
}
/********************************************/
bool startGame(int x, int y)
{
    if (x >=227 && x <= 553 && y >=432 && y<=508) return true; //tọa độ của nút play
    return false;
}

bool help(int x, int y)
{
    if (x >=668 && x <= 991 && y >=438 && y<=508) return true; //tọa độ của nút help
    return false;
}

bool next1(int x, int y)
{
    if (x >=922 && x <= 967 && y >=599 && y<=617) return true; //tọa độ của nút đến với phần hướng dẫn chơi
    return false;
}

bool next2(int x, int y)
{
    if (x >=224 && x <= 274 && y >=570 && y<=600) return true; //tọa độ của nút đến với phần các cấp độ
    return false;
}

bool back(int x, int y)
{
    if (x >=60 && x <= 126 && y >=58 && y<=104) return true; //tọa độ của nút quay lại
    return false;
}

bool quit(int x, int y)
{
    if (x >=469 && x <= 816 && y >=548 && y<=609) return true; //tọa độ của nút quit
    return false;
}

bool checkYes(int x, int y)
{
    if (x >=282 && x <= 523 && y >=545 && y<=605) return true; //tọa độ của nút yes
    return false;
}

bool checkNo(int x, int y)
{
    if (x >=706 && x <= 943 && y >=545 && y<=605) return true; //tọa độ của nút no
    return false;
}

bool checkLevel(int x, int y)
{
    if (x >=430 && x <= 770 && y >=118 && y<=183) {
            level1 = true;
            return true;
    } //tọa độ của nút easy
    if (x >=458 && x <= 793 && y >=247 && y<=314) {
            level2 = true;
            return true;
    } //tọa độ của nút medium
    if (x >=426 && x <= 773 && y >=368 && y<=433) {
            level3 = true;
            return true;
    } //tọa độ của nút hard
    if (x >=462 && x <= 794 && y >=484 && y<=553) {
            level4 = true;
            return true;
    } //tọa độ của nút inforne
    return false;
}

void endGame()
{
    level1 = false;
    level2 = false;
    level3 = false;
    level4 = false;
}

void show(SDL_Window* window, SDL_Renderer* renderer, int objX, int objY, int playerX, int playerY, int PLAY_TIMES, int SCREEN_HEIGHT) {
    if (level1==true)
        showLevel1(window, renderer, objX, objY, playerX, playerY, PLAY_TIMES, SCREEN_HEIGHT);
    if (level2==true)
        showLevel2(window, renderer, objX, objY, playerX, playerY, PLAY_TIMES, SCREEN_HEIGHT);
    if (level3==true)
        showLevel3(window, renderer, objX, objY, playerX, playerY, PLAY_TIMES, SCREEN_HEIGHT);
    if (level4==true)
        showLevel4(window, renderer, objX, objY, playerX, playerY, PLAY_TIMES, SCREEN_HEIGHT);
}

void chooseLevel(SDL_Window* window, SDL_Renderer* renderer,SDL_Event e) {
            showLevel(window,renderer);
            SDL_RenderPresent(renderer);
            int mouseX = 0, mouseY = 0;
            while (true) {
                SDL_Delay(10);
                if (SDL_WaitEvent(&e) == 0) continue;
                if (e.type == SDL_MOUSEBUTTONDOWN) {
                playClick();
                mouseX = e.button.x;
                mouseY = e.button.y;
                if (back(mouseX,mouseY)) {
                    showStartGame(window, renderer);
                    SDL_RenderPresent(renderer);
                    break;
                }
                else if (checkLevel(mouseX,mouseY)) {
                    checkPlay = true;
                    break;
                }
                else continue;
                }
            }
}

void highScore(int score) {
    if (level1==true)
        if (HIGH_SCORE_LEVEL_1 < score) {
            HIGH_SCORE_LEVEL_1 = SCORE;
        }
    if (level2==true)
        if (HIGH_SCORE_LEVEL_2 < score) {
            HIGH_SCORE_LEVEL_2 = SCORE;
        }
    if (level3==true)
        if (HIGH_SCORE_LEVEL_3 < score) {
            HIGH_SCORE_LEVEL_3 = SCORE;
        }
    if (level4==true)
        if (HIGH_SCORE_LEVEL_4 < score) {
            HIGH_SCORE_LEVEL_4 = SCORE;
        }
}

void checkRenderHighScore(SDL_Window* window, SDL_Renderer* renderer) {
    if (level1==true)
        renderScore(window, renderer, HIGH_SCORE_LEVEL_1, 800, 40);
    if (level2==true)
        renderScore(window, renderer, HIGH_SCORE_LEVEL_2, 800, 40);
    if (level3==true)
        renderScore(window, renderer, HIGH_SCORE_LEVEL_3, 800, 40);
    if (level4==true)
        renderScore(window, renderer, HIGH_SCORE_LEVEL_4, 800, 40);
}
