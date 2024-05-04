#include "lib/texture.hpp"

// Load a texture from a file
void Texture::load_image(const std::string &file, SDL_Renderer *renderer)
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

Texture::Texture(SDL_Texture *sdl_texture)
    : texture{sdl_texture, SDL_DestroyTexture}
{
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
}

Texture::Texture(const Texture &other)
    : texture{other.texture}, surface{other.surface},
      width{other.width}, height{other.height}
{
}

Texture &Texture::operator=(const Texture &other)
{
    this->texture = other.texture;
    this->surface = other.surface;
    this->width = other.width;
    this->height = other.height;

    return *this;
}

void Texture::load(const std::string &file, SDL_Renderer *renderer)
{
    load_image(file, renderer);
    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
}

bool Texture::change_pixel(Point2i pixel, Uint8 rgba[4], SDL_Renderer *renderer)
{
    if (!surface)
        throw std::runtime_error("No surface loaded");

    if (pixel.x < 0 || pixel.y < 0 || pixel.x >= surface->w || pixel.y >= surface->h)
        throw std::out_of_range("Pixel coordinates out of range on pixel change, pixel: " + std::to_string(pixel.x) + ", " + std::to_string(pixel.y));

    if (!modified)
    {
        // Copy the surface to a new one
        surface = std::shared_ptr<SDL_Surface>(SDL_ConvertSurfaceFormat(surface.get(), SDL_PIXELFORMAT_ARGB8888, 0), SDL_FreeSurface);

        // Allocate new texture
        texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture);
    }

    Uint32* pixels = (Uint32*)surface->pixels;
    
    Uint8 r, g, b, a;
    Uint32 pixel_value = pixels[(pixel.y * surface->w) + pixel.x];
    SDL_GetRGBA(pixel_value, surface->format, &r, &g, &b, &a);

    if (a >= 16)
        return false;

    Uint32 new_pixel_value = SDL_MapRGBA(surface->format, rgba[0], rgba[1], rgba[2], rgba[3]);
    pixels[(pixel.y * surface->w) + pixel.x] = new_pixel_value;

    // Update texture
    SDL_UpdateTexture(texture.get(), nullptr, surface->pixels, surface->pitch);
	

    modified = true;
    return true;
}

bool Texture::set_alpha_pixel(Point2i ipixel, uint8_t alpha, SDL_Renderer *renderer)
{
    if (ipixel.x < 0 || ipixel.y < 0 || ipixel.x >= surface->w || ipixel.y >= surface->h)
        throw std::out_of_range("Pixel coordinates out of range on alpha change, pixel: " + std::to_string(ipixel.x) + ", " + std::to_string(ipixel.y));

    if (!modified)
    {
        // Copy the surface to a new one
        surface = std::shared_ptr<SDL_Surface>(SDL_ConvertSurfaceFormat(surface.get(), SDL_PIXELFORMAT_ARGB8888, 0), SDL_FreeSurface);

        // Allocate new texture
        texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, surface.get()), SDL_DestroyTexture);
    }

    Uint32* pixels = (Uint32*)surface->pixels;
    
    Uint8 r, g, b, a;
    Uint32 pixel_value = pixels[(ipixel.y * surface->w) + ipixel.x];
    SDL_GetRGBA(pixel_value, surface->format, &r, &g, &b, &a);

    if (a < 16)
        return false;

    Uint32 new_pixel_value = SDL_MapRGBA(surface->format, 0, 0, 0, alpha);
    pixels[(ipixel.y * surface->w) + ipixel.x] = new_pixel_value;

    // Update texture
    SDL_UpdateTexture(texture.get(), nullptr, surface->pixels, surface->pitch);

    modified = true;
    return true;
}

bool Texture::set_alpha_box(Bound2f box, uint8_t alpha, SDL_Renderer *renderer)
{
    box.pMin = clamp(box.pMin, Point2f(0, 0), Point2f(1, 1));
    box.pMax = clamp(box.pMax, Point2f(0, 0), Point2f(1, 1));

    if (box.area() < 0.000001)
        return false;

    bool destroyed_anything = false;

    for (int x = box.pMin.x * get_width(); x < box.pMax.x * get_width(); x++)
    {
        for (int y = box.pMin.y * get_height(); y < box.pMax.y * get_height(); y++)
        {
            // Call to set alpha pixel
            if (set_alpha_pixel(Point2i(x, y), alpha, renderer))
            {
                destroyed_anything = true;
            }
        }
    }

    modified = true;
    return destroyed_anything;
}

bool Texture::fill_box_with_color(Bound2f box, RGBA color, SDL_Renderer *renderer)
{
    box.pMin = clamp(box.pMin, Point2f(0, 0), Point2f(1, 1));
    box.pMax = clamp(box.pMax, Point2f(0, 0), Point2f(1, 1));

    if (box.area() < 0.000001)
        return false;

    bool filled_anything = false;

    for (int x = box.pMin.x * get_width(); x < box.pMax.x * get_width(); x++)
    {
        for (int y = box.pMin.y * get_height(); y < box.pMax.y * get_height(); y++)
        {
            uint8_t rgba[4] = {color.r, color.g, color.b, color.a};
            if (change_pixel(Point2i(std::round(x), std::round(y)), rgba, renderer))
            {
                filled_anything = true;
            }
        }
    }

    modified = true;
    return filled_anything;
}

bool Texture::is_alpha_pixel(Point2f lpixel) const
{
    Point2i pixel;
    lpixel = clamp(lpixel, Point2f(0.00000001, 0.00000001), Point2f(0.999999, 0.999999));

    pixel.x = lpixel.x * get_width();
    pixel.y = lpixel.y * get_height();

    if (!surface)
        throw std::runtime_error("No surface loaded");

    if (pixel.x < 0 || pixel.y < 0 || pixel.x >= surface->w || pixel.y >= surface->h)
        throw std::out_of_range("Pixel coordinates out of range on alpha check, lpixel: " + std::to_string(lpixel.x) + ", " + std::to_string(lpixel.y));

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + pixel.y * surface->pitch + pixel.x * bpp;

    Uint32 pixel_value;
    switch (bpp)
    {
    case 1:
        pixel_value = *p;
        break;
    case 2:
        pixel_value = *(Uint16 *)p;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            pixel_value = p[0] << 16 | p[1] << 8 | p[2];
        else
            pixel_value = p[0] | p[1] << 8 | p[2] << 16;
        break;
    case 4:
        pixel_value = *(Uint32 *)p;
        break;
    default:
        throw std::runtime_error("Unknown pixel format");
    }

    Uint8 r, g, b, a;
    SDL_GetRGBA(pixel_value, surface->format, &r, &g, &b, &a);

    return a < 16;
}

// Returns the raw SDL_Texture pointer
SDL_Texture *Texture::get() const
{
    return texture.get();
}

SDL_Surface *Texture::get_surface() const
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