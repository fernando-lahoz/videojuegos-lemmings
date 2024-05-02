#pragma once

#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/types.hpp"
#include "geometry/point.hpp"
#include "lib/error.hpp"
#include "geometry/bounding_box.hpp"
#include "lib/spectrum.hpp"

class Texture
{
private:
    std::shared_ptr<SDL_Texture> texture{nullptr, SDL_DestroyTexture};
    std::shared_ptr<SDL_Surface> surface{nullptr, SDL_FreeSurface};
    int width{};
    int height{};
    bool modified = false;

    void load_image(const std::string &file, SDL_Renderer *renderer);

public:
    constexpr Texture() = default;

    Texture(SDL_Texture *sdl_texture);

    Texture(const Texture &other);
    Texture &operator=(const Texture &other);
    void load(const std::string &file, SDL_Renderer *renderer);

    // Returns the raw SDL_Texture pointer
    SDL_Texture *get() const;
    SDL_Surface *get_surface() const;

    // Returns true if the pixel has an alpha value > 128
    bool is_alpha_pixel(Point2f pixel) const;

    bool change_pixel(Point2i ipixel, uint8_t rgb[3], SDL_Renderer* renderer);
    bool set_alpha_pixel(Point2i ipixel, uint8_t alpha, SDL_Renderer *renderer);
    bool set_alpha_box(Bound2f box, uint8_t alpha, SDL_Renderer *renderer);

    bool fill_box_with_color(Bound2f box, RGBA color, SDL_Renderer *renderer);

    int get_width() const;
    int get_height() const;
};