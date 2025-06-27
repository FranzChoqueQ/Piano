#include "TextRenderer.hpp"
#include <stdexcept>

TextRenderer::TextRenderer() : font(nullptr), currentSize(0) {}

TextRenderer::~TextRenderer() {
    if (font) {
        TTF_CloseFont(font);
    }
}

bool TextRenderer::loadFont(const std::string& path, int fontSize) {
    fontPath = path;
    currentSize = fontSize;
    return reloadFont();
}

void TextRenderer::setFontSize(int size) {
    if (size != currentSize) {
        currentSize = size;
        reloadFont();
    }
}

bool TextRenderer::reloadFont() {
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    
    font = TTF_OpenFont(fontPath.c_str(), currentSize);
    return font != nullptr;
}

void TextRenderer::render(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color) {
    if (!font) return;
    
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) return;
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/*
void MainGame::renderText(const std::string& message, int x, int y) {
    TTF_Font* font = TTF_OpenFont("assets/fonts/arial.ttf", 25);        //assets/fonts/arial.ttf
    if (!font) {
        throw std::runtime_error("Failed to load font: " + std::string(TTF_GetError()));
    }
    
    SDL_Color color = {255, 255, 255, 255}; // Blanco
    SDL_Surface* surface = TTF_RenderText_Solid(font, message.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window.getRenderer(), surface);
    
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(window.getRenderer(), texture, nullptr, &rect);
    
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
*/

int TextRenderer::getTextWidth(const std::string& text) const {
    if (!font) return 0;
    int width;
    TTF_SizeText(font, text.c_str(), &width, nullptr);
    return width;
}

int TextRenderer::getTextHeight(const std::string& text) const {
    if (!font) return 0;
    int height;
    TTF_SizeText(font, text.c_str(), nullptr, &height);
    return height;
}
