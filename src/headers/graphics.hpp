#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "main.hpp"

class Graphics {
    public:
        SDL_Window *currentWindow;
        SDL_Renderer *currentRenderer;
        Graphics(SDL_Window *window, SDL_Renderer *renderer);
        void quit();
        void render();
};

class Asset {
    public:
        SDL_Texture *texture;
        int width;
        int height;
        Asset(std::string path, SDL_Renderer *renderer);
        Asset();
        void Free();
};

class Animation {
    public:
        std::vector<Asset*> frames;
        int currentFrame;
        float currentSubFrame;
        bool isPlaying;
        Animation();
        void addFrame(Asset *frame);
};
#endif