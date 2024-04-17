#pragma once

#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "lib/types.hpp"
#include "geometry/point.hpp"
#include "lib/error.hpp"
#include "geometry/bounding_box.hpp"

class Texture
{
public:

    const static size_t BLOCK_SIZE = 8;
    using BLOCK_TYPE = u_int8_t;


private:
    std::shared_ptr<SDL_Texture> texture{nullptr, SDL_DestroyTexture};
    std::shared_ptr<SDL_Surface> surface{nullptr, SDL_FreeSurface};
    int width{};
    int height{};
    bool modified = false;

    std::shared_ptr<std::vector<BLOCK_TYPE>> alpha_mask;

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

    // Returns true if the pixel is transparent
    bool is_alpha_pixel(Point2f pixel) const;
    bool is_alpha_pixel(Point2i pixel) const;


    void change_pixel(Point2i ipixel, uint8_t rgb[3]);
    bool set_alpha_pixel(Point2i ipixel, uint8_t alpha, SDL_Renderer *renderer);
    bool set_alpha_box(Bound2f box, uint8_t alpha, SDL_Renderer *renderer);

    void generate_alpha_mask();

    Point2i local_to_texture(Point2f local) const;
    Point2f texture_to_local(Point2i texture) const;

    size_t get_alpha_mask_width() const;
    size_t get_alpha_mask_height() const;
    std::shared_ptr<std::vector<BLOCK_TYPE>> get_alpha_mask() const;

    std::vector<bool> get_uncompressed_alpha_mask() const;

    int get_width() const;
    int get_height() const;
};