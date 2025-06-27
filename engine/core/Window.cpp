#include "Window.hpp"

#include <stdexcept>

Window::Window(const std::string& title, int width, int height)
    : width(width), height(height) {

    window = SDL_CreateWindow(
    title.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_SHOWN
    );

    if (!window) {
        throw std::runtime_error("Failed to create window: " + std::string(SDL_GetError()));
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        throw std::runtime_error("Failed to create renderer: " + std::string(SDL_GetError()));
    }
}

Window::~Window(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::clear(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Color negro
    SDL_RenderClear(renderer);
}

void Window::present(){
    SDL_RenderPresent(renderer);
}

SDL_Renderer* Window::getRenderer() const {
    return renderer;
}

SDL_Window* Window::getSDLWindow() const {
    return window;
}
