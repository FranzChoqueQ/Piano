#pragma once

#include <SDL2/SDL.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();
    
    void clear();
    void present();
    SDL_Renderer* getRenderer() const;
    SDL_Window* getSDLWindow() const;
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
};