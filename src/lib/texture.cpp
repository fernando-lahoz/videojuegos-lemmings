#include "lib/texture.hpp"

// Load a texture from a file
void Texture::load_image(const std::string& file, SDL_Renderer* renderer)
{
    SDL_Surface *sdl_surface = nullptr;
    SDL_Texture *sdl_texture = nullptr;
    
    sdl_surface = IMG_Load(file.c_str());
    if (sdl_surface == nullptr)
        throw std::runtime_error("Failed to load image \"" + file + "\"");

    sdl_texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
    if (sdl_texture == nullptr)
        throw std::runtime_error("Failed to load texture \"" + file + "\"");

    surface = std::shared_ptr<SDL_Surface>(sdl_surface, SDL_FreeSurface);
    texture = std::shared_ptr<SDL_Texture>(sdl_texture, SDL_DestroyTexture);
}

Texture::Texture(SDL_Texture* sdl_texture)
    : texture{sdl_texture, SDL_DestroyTexture}
{
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
}


Texture::Texture(const Texture& other)
    : texture{other.texture}, surface{other.surface}, 
        width{other.width}, height{other.height}
{ }

Texture& Texture::operator=(const Texture& other)
{
    this->texture = other.texture;
    this->surface = other.surface;
    this->width = other.width;
    this->height = other.height;

    return *this;
}



void Texture::load(const std::string& file, SDL_Renderer* renderer)
{
    load_image(file, renderer);
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
}


bool Texture::is_alpha_pixel(Point2f lpixel) const
{
    Point2i pixel;
    pixel.x = lpixel.x * get_width();
    pixel.y = lpixel.y * get_height();

    if (!surface)
        throw std::runtime_error("No surface loaded");

    if (pixel.x < 0 || pixel.y < 0 || pixel.x >= surface->w || pixel.y >= surface->h)
        throw std::out_of_range("Pixel coordinates out of range");

    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + pixel.y * surface->pitch + pixel.x * bpp;

    Uint32 pixel_value;
    switch(bpp) {
    case 1:
        pixel_value = *p;
        break;
    case 2:
        pixel_value = *(Uint16*)p;
        break;
    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixel_value = p[0] << 16 | p[1] << 8 | p[2];
        else
            pixel_value = p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        pixel_value = *(Uint32*)p;
        break;
    default:
        throw std::runtime_error("Unknown pixel format");
    }

    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel_value, surface->format, &r, &g, &b, &a);

    return a == 0;
}

// Returns the raw SDL_Texture pointer
SDL_Texture* Texture::get() const
{
    return texture.get();
}

SDL_Surface* Texture::get_surface() const
{
    return surface.get();
}

int Texture::get_width() const
{
    return width;
}

int Texture::get_height() const
{
    return height;
}