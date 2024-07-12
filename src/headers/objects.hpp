#ifndef OBJECTS_HPP
#define OBJECTS_HPP
#include "main.hpp"
#include "graphics.hpp"

class Asset;
class Animation;

class Object{
    private:
    int *global_x;
    int *global_y;
    public:
    int x;
    int y;
    float parallax_coefficient;
    int width;
    int height;
    int opacity;
    int reverseExpansion;
    float animationSpeed;
    float animationSpeedSecondary;
    bool clickable;
    bool isInvisible;
    bool mouseReleased;
    bool floating;
    bool forceShow;
    Asset *currentAsset;
    Animation *currentAnimation;
    Animation *currentSecondaryAnimation;
    SDL_Window *currentWindow;
    SDL_Renderer *currentRenderer;
    SDL_Texture *currentTexture;
    Object();
    Object(Asset *asset, int x, int y, int *global_x, int *global_y, SDL_Window *window, SDL_Renderer *renderer);
    Object(int x, int y, int *global_x, int *global_y, int width, int height, SDL_Window *window, SDL_Renderer *renderer);
    void render();
    void setVisibility(bool visibility);
    int getPosition(bool axis);
    bool isMouseHovering();
    bool isMouseClicking();
};

#endif