#ifndef SOUND_H_
#define SOUND_H_

#include <SDL.h>
#include <SDL_mixer.h>

void loadAudio();
void playClick();
void playMoney();
void playDrop();
void cleanup();

#endif // SOUND_H_
