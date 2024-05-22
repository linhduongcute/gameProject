#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

bool initSDLTTF() {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf. Error: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void renderScore(SDL_Window* window, SDL_Renderer* renderer, int score, int x, int y) {
    if (initSDLTTF()== false) {
        SDL_Quit();
    }
    TTF_Font* font = TTF_OpenFont("font/minecraft/Minecraft.ttf", 18);
    if (font == nullptr) {
        std::cerr << "Failed to load font. Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {0, 0, 0};

    std::string scoreText;
    // Tạo surface từ điểm số
    if (x == 1000) {
    scoreText = "SCORE: " + std::to_string(score);
    }
    else if (x == 800) {
    scoreText = "HIGH SCORE: " + std::to_string(score);
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Unable to render text surface. Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    // Tạo texture từ surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Unable to create texture from rendered text. Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Lấy kích thước của texture để vẽ lên màn hình
    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    // Vị trí để vẽ text lên màn hình
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    // Vẽ texture lên renderer
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
}

void renderScoreEndGame(SDL_Window* window, SDL_Renderer* renderer, int score, int x, int y) {
    if (initSDLTTF()== false) {
        SDL_Quit();
    }
    TTF_Font* font = TTF_OpenFont("font/minecraft/Minecraft.ttf", 45);
    if (font == nullptr) {
        std::cerr << "Failed to load font. Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Color textColor = {0, 0, 0};

    std::string scoreText;
    // Tạo surface từ điểm số
    scoreText = "SCORE: " + std::to_string(score);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, scoreText.c_str(), textColor);
    if (textSurface == nullptr) {
        std::cerr << "Unable to render text surface. Error: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    // Tạo texture từ surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Unable to create texture from rendered text. Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Lấy kích thước của texture để vẽ lên màn hình
    int textWidth = 0;
    int textHeight = 0;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textWidth, &textHeight);

    // Vị trí để vẽ text lên màn hình
    SDL_Rect renderQuad = {x, y, textWidth, textHeight};

    // Vẽ texture lên renderer
    SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
}

