#include "headers/main.hpp"

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event event;

const int SCREEN_WIDTH = 1024; // 1024
const int SCREEN_HEIGHT = 768; // 768
const bool START_AS_FULLSCREEN = false;
std::string GAME_PATH;

int getScreenSize(int pos){
    int width, height;
    SDL_GetWindowSize(window, &width, &height);
    if(pos == 0) return width;
    else return height;
}

void initialize(){
    window = SDL_CreateWindow("Five Nights at Freddy's 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(START_AS_FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 1024);
}

std::string GetExecutableDirectory() {
    char buffer[PATH_MAX];

    #ifdef _WIN32
    GetModuleFileName(NULL, buffer, sizeof(buffer));
    #else
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len == -1) {
        throw std::runtime_error("readlink failed");
    }
    buffer[len] = '\0';
    #endif
    std::string path(buffer);
    return path.substr(0, path.find_last_of("/\\"));
}

std::string GetParentDirectory(const std::string& directory) {
    #ifdef _WIN32
    size_t last_slash_pos = directory.find_last_of("\\");
    #else
    size_t last_slash_pos = directory.find_last_of("/");
    #endif
    if (last_slash_pos != std::string::npos) {
        return directory.substr(0, last_slash_pos);
    }
    return "";
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
#else
int main(){
#endif
    GAME_PATH = GetParentDirectory(GetExecutableDirectory());
    initialize();
    std::cout << "1/4: Window and renderer initialized\n";
    Graphics graphics = Graphics(window, renderer);
    std::cout << "2/4: Graphics initialized\n";

    // Render loading screen
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Render bottom right loading symbol on the bottom right, with a texture
    #ifdef _WIN32
    Asset loading = Asset(GAME_PATH + "\\assets\\80.png", renderer);
    #else
    Asset loading = Asset(GAME_PATH + "/assets/80.png", renderer);
    #endif
    SDL_Rect loadingRect = {(1024-64) * SCREEN_WIDTH/1024, (768-64) * SCREEN_HEIGHT/768, loading.width * SCREEN_WIDTH/1024, loading.height * SCREEN_HEIGHT/768};
    SDL_RenderCopy(renderer, loading.texture, NULL, &loadingRect);
    SDL_RenderPresent(renderer);
    
    initializeAssets(window, renderer, GAME_PATH);

    Uint64 timeNow = SDL_GetPerformanceCounter();
    Uint64 timeLast = 0;
    double deltaTime = 0;

    /*std::vector<double> avgFPS; // FPS MEASURING CODE
    double avgFPSMax;*/
    while(true){
        /*avgFPS.push_back(1000/deltaTime); // FPS MEAUSRING CODE
        if(SDL_PollEvent(&event) && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_u){
            avgFPSMax = 0;
            for(int i = 0; i < avgFPS.size(); i++){
                avgFPSMax += avgFPS[i];
            }
            avgFPSMax /= avgFPS.size();
            std::cout << "Average FPS: " << avgFPSMax << std::endl;
            avgFPS.clear();
        }*/

        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();
        deltaTime = (double)((timeNow - timeLast)*1000 / (double)SDL_GetPerformanceFrequency());
        if(SDL_PollEvent(&event) && event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
            if(SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(window, 0);
            else SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        }
        tick(deltaTime, window, renderer, &event);
        graphics.render();
        if(event.type == SDL_QUIT) break;
    }
    graphics.quit();
    return 0;
}