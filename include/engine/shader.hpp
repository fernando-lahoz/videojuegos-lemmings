#pragma once

#include <SDL2/SDL.h>

#include "lib/spectrum.hpp"
#include "lib/texture.hpp"

class Engine;

class Shader
{
public:
    enum Resolution : int { AUTO = -1 };

private:
    SDL_Renderer *renderer = nullptr;
    SDL_Texture *buffer = nullptr;

    enum class Type { NONE, INVISIBLE, FILLED_BOX, COLOR_MASK, CHANGE_RESOLUTION };
    Type type = Type::NONE;

    int buffer_width = AUTO, buffer_height = AUTO;

    SDL_BlendMode blendmode;
    RGBA mask_color;

    void generate_buffer(int w, int h, Uint32 format = SDL_PIXELFORMAT_RGBA32);

public:
    Shader(Engine& engine);
    Shader(const Shader& other);
    Shader(Shader&& other);
    ~Shader();

    Shader& change_resolution(int w, int h);
    Shader& color_mask(RGBA color, int w = AUTO, int h = AUTO);
    Shader& filled_box(RGBA color, int w = AUTO, int h = AUTO);
    Shader& invisible();

private:
    void render_copy(const Texture& texture, SDL_Rect& rect);
    Shader() = default;

    friend class Camera2D;
    friend class Render_2D;
};
