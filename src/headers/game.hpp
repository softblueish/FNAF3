#ifndef GAME_HPP
#define GAME_HPP
#include <filesystem>
#include <vector>
#include "main.hpp"
#include "graphics.hpp"
#include "objects.hpp"
#include "audio.hpp"

void tick(float delta, SDL_Window *window, SDL_Renderer *renderer, SDL_Event *event);
void initializeAssets(SDL_Window *window, SDL_Renderer *renderer, std::string path);

#endif