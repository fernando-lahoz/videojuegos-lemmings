#pragma once

#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/types.hpp"

class Texture
{
private:
    std::shared_ptr<SDL_Texture> texture {nullptr, SDL_DestroyTexture};
    int width {};
    int height {};

public:

    constexpr Texture() = default;

    Texture(SDL_Texture* sdl_texture);

    Texture(const Texture& other);

    void load(const std::string& file, SDL_Renderer* renderer);

    Texture& operator=(const Texture& other);

    // Returns the raw SDL_Texture pointer
    SDL_Texture* get() const;

    int get_width() const;

    int get_height() const;
};