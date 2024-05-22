#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include "sound.h"

Mix_Chunk* click;
Mix_Chunk* money, *drop;

Mix_Chunk* loadSound(const std::string& filePath) {
    Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
    if (sound == nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    return sound;
}

void loadAudio() {
    click = loadSound("sound/click.WAV");
    money = loadSound("sound/money.WAV");
    drop = loadSound("sound/drop.WAV");
    if (click == nullptr) {
        std::cerr << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}

void playClick() {
    Mix_PlayChannel(-1, click, 0);
}

void playMoney() {
    Mix_PlayChannel(-1, money, 0);
}

void playDrop() {
    Mix_PlayChannel(-1, drop, 0);
}

void cleanup() {
    Mix_FreeChunk(click);
    Mix_CloseAudio();
}
