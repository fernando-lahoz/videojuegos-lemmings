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

    SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);


    generate_alpha_mask();
}

void Texture::generate_alpha_mask()
{
    if (!surface)
        throw std::runtime_error("No surface loaded");

    if (!alpha_mask)
        alpha_mask = std::make_shared<std::vector<BLOCK_TYPE>>(get_alpha_mask_width() * get_alpha_mask_height(), 0);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //std::cout << x << ", " << y << ": " << !is_alpha_pixel(Point2i(x, y)) << std::endl; 
            if (!is_alpha_pixel(Point2i(x, y)))
            {
                size_t block_x = x / BLOCK_SIZE;
                size_t block_y = y;

                size_t block_index = block_y * get_alpha_mask_width() + block_x;
                size_t block_offset = BLOCK_SIZE - 1 - (x % BLOCK_SIZE);

                (*alpha_mask)[block_index] |= 1 << block_offset;
            }
        }
    }
}

std::shared_ptr<std::vector<Texture::BLOCK_TYPE>> Texture::get_alpha_mask() const
{
    return alpha_mask;
}

Point2i Texture::local_to_texture(Point2f local) const
{
    local = clamp(local, Point2f(0, 0), Point2f(1, 1));
    return Point2i(local.x * width, local.y * height);
}

Point2f Texture::texture_to_local(Point2i texture) const
{
    return Point2f(texture.x / (float)width, texture.y / (float)height);
}

Vector2f Texture::texture_to_local(Vector2f texture) const
{
    return Vector2f(texture.x / (float)width, texture.y / (float)height);
}

std::vector<bool> Texture::get_uncompressed_alpha_mask() const
{
    std::vector<bool> uncompressed_alpha_mask(width * height, false);

    for (int i = 0; i < alpha_mask->size(); i++)
    {
        for (int j = BLOCK_SIZE-1; j >= 0; j--)
        {
            if ((*alpha_mask)[i] & (1 << j))
            {
                uncompressed_alpha_mask[i * BLOCK_SIZE + j] = true;
            }
        }
    }

    return uncompressed_alpha_mask;
}



size_t Texture::get_alpha_mask_width() const
{
    size_t w = width / BLOCK_SIZE;
    if (width % BLOCK_SIZE)
        w++;

    return w;
}

size_t Texture::get_alpha_mask_height() const
{
    return height;
}

Texture::Texture(SDL_Texture *sdl_texture)
    : texture{sdl_texture, SDL_DestroyTexture}
{
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
    generate_alpha_mask();
}

Texture::Texture(const Texture &other)
    : texture{other.texture}, surface{other.surface},
      width{other.width}, height{other.height},
        modified{false}, alpha_mask{other.alpha_mask}
{
}

Texture &Texture::operator=(const Texture &other)
{
    this->texture = other.texture;
    this->surface = other.surface;
    this->width = other.width;
    this->height = other.height;
    this->modified = false;
    this->alpha_mask = other.alpha_mask;

    return *this;
}

void Texture::load(const std::string &file, SDL_Renderer *renderer)
{
    load_image(file, renderer);
}

void Texture::change_pixel(Point2i pixel, Uint8 rgba[4])
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
        texture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(nullptr, surface.get()), SDL_DestroyTexture);
    }

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + pixel.y * surface->pitch + pixel.x * bpp;

    Uint32 new_pixel_value = SDL_MapRGBA(surface->format, rgba[0], rgba[1], rgba[2], rgba[3]);

    switch (bpp)
    {
    case 1:
        *p = new_pixel_value;
        break;
    case 2:
        *(Uint16 *)p = new_pixel_value;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (new_pixel_value >> 16) & 0xff;
            p[1] = (new_pixel_value >> 8) & 0xff;
            p[2] = new_pixel_value & 0xff;
        }
        else
        {
            p[0] = new_pixel_value & 0xff;
            p[1] = (new_pixel_value >> 8) & 0xff;
            p[2] = (new_pixel_value >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = new_pixel_value;
        break;
    default:
        throw std::runtime_error("Unknown pixel format");
    }

    modified = true;
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

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + ipixel.y * surface->pitch + ipixel.x * bpp;

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

    if (a < 16)
        return false;

    Uint32 new_pixel_value = SDL_MapRGBA(surface->format, r, g, b, alpha);

    switch (bpp)
    {
    case 1:
        *p = new_pixel_value;
        break;
    case 2:
        *(Uint16 *)p = new_pixel_value;
        break;
    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (new_pixel_value >> 16) & 0xff;
            p[1] = (new_pixel_value >> 8) & 0xff;
            p[2] = new_pixel_value & 0xff;
        }
        else
        {
            p[0] = new_pixel_value & 0xff;
            p[1] = (new_pixel_value >> 8) & 0xff;
            p[2] = (new_pixel_value >> 16) & 0xff;
        }
        break;
    case 4:
        *(Uint32 *)p = new_pixel_value;
        break;
    default:
        throw std::runtime_error("Unknown pixel format");
    }

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

bool Texture::is_alpha_pixel(Point2f lpixel) const
{
    Point2i pixel;
    lpixel = clamp(lpixel, Point2f(0.00000001, 0.00000001), Point2f(0.999999, 0.999999));

    pixel.x = lpixel.x * get_width();
    pixel.y = lpixel.y * get_height();

    return is_alpha_pixel(pixel);
}


bool Texture::is_alpha_pixel(Point2i pixel) const
{
    if (!surface)
        throw std::runtime_error("No surface loaded");

    if (pixel.x < 0 || pixel.y < 0 || pixel.x >= surface->w || pixel.y >= surface->h)
        throw std::out_of_range("Pixel coordinates out of range on alpha check, pixel: " + std::to_string(pixel.x) + ", " + std::to_string(pixel.y));

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