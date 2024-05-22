#ifndef FRAME_PER_SECOND_H_
#define FRAME_PER_SECOND_H_

#include "initScreen.h"

bool checkCollision( int objX, int objY, int playerX, int playerY);
bool checkEnd(int playerY, int SCREEN_HEIGHT);
bool checkAll(int objX, int objY, int playerX, int playerY, int SCREEN_HEIGHT);

#endif // FRAME_PER_SECOND_H_
