#pragma once

#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "types.hpp"

class Texture
{
    private:

    std::shared_ptr<SDL_Texture> texture;
    int width;
    int height;


    // Load a texture from a file
    SDL_Texture* load_image(const std::string file, SDL_Renderer* renderer)
    {
        SDL_Texture* sdl_texture = nullptr;

        try {
            SDL_Surface* surface = IMG_Load(file.c_str());
            if (surface == nullptr)
            {
                throw "Failed to load image";
            }

            sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);

            if (sdl_texture == nullptr)
            {
                throw "Failed to create texture";
            }

            SDL_FreeSurface(surface);
        }
        catch (const char* error)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error: %s", error);
            throw;
        }

        return sdl_texture;
    }


    public:

    Texture()
    {
        texture = nullptr;
        width = 0;
        height = 0;
    }

    Texture(SDL_Texture* sdl_texture)
    {
        texture = std::shared_ptr<SDL_Texture>(sdl_texture, SDL_DestroyTexture);
        SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
    }

    Texture(const Texture& other)
    {
        this->texture = other.texture;
        this->width = other.width;
        this->height = other.height;
    }

    void load(std::string file, SDL_Renderer* renderer)
    {
        auto sdl_texture = load_image(file, renderer);
        texture = std::shared_ptr<SDL_Texture>(sdl_texture, SDL_DestroyTexture);

        SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
    }

    Texture& operator=(const Texture& other)
    {
        this->texture = other.texture;
        this->width = other.width;
        this->height = other.height;
        return *this;
    }

    // Returns the raw SDL_Texture pointer
    SDL_Texture* get() const
    {
        return texture.get();
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }
};