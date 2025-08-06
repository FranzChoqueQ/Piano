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
