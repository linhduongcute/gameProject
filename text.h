#ifndef TEXT_H_
#define TEXT_H_

bool initSDLTTF();
void renderScore(SDL_Window* window, SDL_Renderer* renderer, int score, int x, int y);
void renderQuestion(SDL_Window* window, SDL_Renderer* renderer, int x, int y);
void renderScoreEndGame(SDL_Window* window, SDL_Renderer* renderer, int score, int x, int y);

#endif // TEXT_H_
