#include "headers/objects.hpp"

Object::Object(){
    this->x = 0;
    this->y = 0;
    this->global_x = 0;
    this->global_y = 0;
    this->width = 0;
    this->height = 0;
    this->opacity = 100;
    animationSpeed = 1;
    animationSpeedSecondary = 1;
    isInvisible = false;
    floating = false;
    forceShow = false;
    currentWindow = NULL;
    currentRenderer = NULL;
    currentTexture = NULL;
    currentAsset = NULL;
    currentAnimation = NULL;
    currentSecondaryAnimation = NULL;
}

Object::Object(Asset *asset, int x, int y, int *global_x, int *global_y, SDL_Window *window, SDL_Renderer *renderer){
    this->x = x;
    this->y = y;
    this->global_x = global_x;
    this->global_y = global_y;
    this->width = asset->width;
    this->height = asset->height;
    this->opacity = 100;
    animationSpeed = 1;
    animationSpeedSecondary = 1;
    isInvisible = false;
    floating = false;
    forceShow = false;
    currentWindow = window;
    currentRenderer = renderer;
    currentAsset = asset;
    currentTexture = currentAsset->texture;
    currentAnimation = NULL;
    currentSecondaryAnimation = NULL;
}

Object::Object(int x, int y, int *global_x, int *global_y, int width, int height, SDL_Window *window, SDL_Renderer *renderer){
    this->x = x;
    this->y = y;
    this->global_x = global_x;
    this->global_y = global_y;
    this->width = width;
    this->height = height;
    animationSpeed = 1;
    animationSpeedSecondary = 1;
    isInvisible = false;
    currentWindow = window;
    currentRenderer = renderer;
    currentAsset = NULL;
    currentTexture = NULL;
    currentAnimation = NULL;
    currentSecondaryAnimation = NULL;
}

void Object::render(){
    if(forceShow==true){
        SDL_Rect rect = {getPosition(0) * getScreenSize(0)/1024, getPosition(1) * getScreenSize(1)/768, width * getScreenSize(0)/1024, height * getScreenSize(1)/768};
        SDL_SetRenderDrawColor(currentRenderer, 255, 0, 255, 255);
        SDL_RenderFillRect(currentRenderer, &rect);
    } else {
        if(!isInvisible) return;
        SDL_SetTextureAlphaMod(currentTexture, (int)(opacity * 2.55));
        SDL_Rect rect = {getPosition(0) * getScreenSize(0)/1024, getPosition(1) * getScreenSize(1)/768, width * getScreenSize(0)/1024, height * getScreenSize(1)/768};
        SDL_RenderCopy(currentRenderer, currentTexture, NULL, &rect);
        SDL_SetTextureAlphaMod(currentTexture, 255);
    }
}

int Object::getPosition(bool axis){
    if(axis){
        if(floating == true) return x; else return x + *global_x;
    } else {
        if(floating == true) return y; else return y + *global_y;
    }
}

void Object::setVisibility(bool visibility){
    isInvisible = visibility;
}

bool Object::isMouseHovering(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    mouseX = mouseX * 1024 / getScreenSize(0);
    mouseY = mouseY * 768 / getScreenSize(1);
    if(mouseX > getPosition(0) && mouseX < getPosition(0) + width && mouseY > getPosition(1) && mouseY < getPosition(1) + height){
        return true;
    } else {
        return false;
    }
}

bool Object::isMouseClicking(){
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    mouseX = mouseX * 1024 / getScreenSize(0);
    mouseY = mouseY * 768 / getScreenSize(1);
    if(!clickable) return false;
    if(mouseX > getPosition(0) && mouseX < getPosition(0) + width && mouseY > getPosition(1) && mouseY < getPosition(1) + height && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
        if(!mouseReleased) return false;
        mouseReleased = false;
        return true;
    } else {
        mouseReleased = true;
        return false;
    }
}