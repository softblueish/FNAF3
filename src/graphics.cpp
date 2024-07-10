#include "headers/graphics.hpp"

Graphics::Graphics(SDL_Window *window, SDL_Renderer *renderer){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    currentRenderer = renderer;
    currentWindow = window;
}

void Graphics::quit(){
    SDL_DestroyRenderer(currentRenderer);
    SDL_DestroyWindow(currentWindow);
    SDL_Quit();
}

void Graphics::render(){
    SDL_RenderPresent(currentRenderer);
    SDL_SetRenderDrawColor(currentRenderer, 0, 0, 0, 255);
    SDL_RenderClear(currentRenderer);
}

Asset::Asset(std::string path, SDL_Renderer *renderer){
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "Failed to load image: " << SDL_GetError() << std::endl;
        texture = NULL;
        return;
    }
    std::cout << "Loaded " << path << "\n";
    width = surface->w;
    height = surface->h;
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    std::cout << "Created texture from " << path << "\n";
    SDL_FreeSurface(surface);
}

void Asset::Free(){
    SDL_DestroyTexture(texture);
    delete this;
}

Asset::Asset(){
    texture = NULL;
    width = 0;
    height = 0;
}

Animation::Animation(){
    currentFrame = 0;
    currentSubFrame = 0;
}

void Animation::addFrame(Asset *frame){
    frames.push_back(frame);
}