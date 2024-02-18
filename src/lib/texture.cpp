#include "lib/texture.hpp"

// Load a texture from a file
SDL_Texture* load_image(const std::string& file, SDL_Renderer* renderer)
{
    SDL_Texture* sdl_texture = nullptr;
    
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (surface == nullptr)
        throw std::runtime_error("Failed to load image \"" + file + "\"");

    sdl_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (sdl_texture == nullptr)
        throw std::runtime_error("Failed to load texture \"" + file + "\"");

    SDL_FreeSurface(surface);
    return sdl_texture;
}

Texture::Texture(SDL_Texture* sdl_texture)
    : texture{sdl_texture, SDL_DestroyTexture}
{
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
}

Texture::Texture(const Texture& other)
    : texture{other.texture}, width{other.width}, height{other.height}
{ }

void Texture::load(const std::string& file, SDL_Renderer* renderer)
{
    auto sdl_texture = load_image(file, renderer);
    texture = std::shared_ptr<SDL_Texture>(sdl_texture, SDL_DestroyTexture);

    if (SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height) != 0)
        throw std::runtime_error("Can't load texture: " + file);
}

Texture& Texture::operator=(const Texture& other)
{
    this->texture = other.texture;
    this->width = other.width;
    this->height = other.height;
    return *this;
}

// Returns the raw SDL_Texture pointer
SDL_Texture* Texture::get() const
{
    return texture.get();
}

int Texture::get_width() const
{
    return width;
}

int Texture::get_height() const
{
    return height;
}