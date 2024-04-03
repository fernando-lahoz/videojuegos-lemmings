#include "engine/shader.hpp"

#include "engine/engine.hpp"

//TODO: change constructors

Shader::Shader(Engine& engine)
    : renderer{engine.get_renderer()}
{

}

Shader::Shader(const Shader& other)
    : renderer{other.renderer}, buffer{nullptr}, type{other.type},
      buffer_width{other.buffer_width}, buffer_height{other.buffer_height},
      blendmode{other.blendmode}, mask_color{other.mask_color}
{
    if (buffer_width != Resolution::AUTO && buffer_height != Resolution::AUTO)
    {
        generate_buffer(buffer_width, buffer_height);
    }
}

Shader::Shader(Shader&& other)
    : renderer{other.renderer}, buffer{other.buffer}, type{other.type},
      buffer_width{other.buffer_width}, buffer_height{other.buffer_height},
      blendmode{other.blendmode}, mask_color{other.mask_color}
{
    other.buffer = nullptr;
}

Shader::~Shader()
{
    SDL_DestroyTexture(buffer);
}



void Shader::generate_buffer(int w, int h, Uint32 format)
{
    SDL_DestroyTexture(buffer);
    buffer = SDL_CreateTexture(
            renderer, format, SDL_TEXTUREACCESS_TARGET, w, h);
    SDL_SetTextureBlendMode(buffer, SDL_BLENDMODE_BLEND);
}

Shader& Shader::change_resolution(int w, int h)
{
    type = Type::CHANGE_RESOLUTION;

    buffer_width = w;
    buffer_height = h;
    if (w != Resolution::AUTO && h != Resolution::AUTO)
    {
        generate_buffer(w, h);
    }
    return *this;
}

Shader& Shader::color_mask(RGBA color, int w, int h)
{
    type = Type::COLOR_MASK;

    buffer_width = w;
    buffer_height = h;
    if (w != Resolution::AUTO && h != Resolution::AUTO)
    {
        generate_buffer(w, h);
    }

    mask_color = color;

    blendmode = SDL_ComposeCustomBlendMode(
            SDL_BLENDFACTOR_ZERO,
            SDL_BLENDFACTOR_SRC_ALPHA,
            SDL_BLENDOPERATION_ADD,
            SDL_BLENDFACTOR_ONE,
            SDL_BLENDFACTOR_ZERO,
            SDL_BLENDOPERATION_ADD
    );
    return *this;
}

Shader& Shader::filled_box(RGBA color, int w, int h)
{
    type = Type::FILLED_BOX;

    buffer_width = w;
    buffer_height = h;

    mask_color = color;
    return *this;
}

Shader& Shader::invisible()
{
    type = Type::INVISIBLE;

    return *this;
}

void Shader::render_copy(const Texture& texture, SDL_Rect& rect)
{
    int w = texture.get_width(), h = texture.get_height();

    constexpr Float scale = 0.5f;
    int h_aux = 0, w_aux = 0;

    switch (type)
    {
    case Type::FILLED_BOX:

        w_aux = rect.w;
        h_aux = rect.h;
        rect.w = (Float)rect.w * scale;
        rect.h = (Float)rect.h * scale;
        rect.x += (w_aux - rect.w) / 2;
        rect.y += (h_aux - rect.h) / 2;

        SDL_SetRenderDrawColor(renderer, mask_color.r, mask_color.g,
                                         mask_color.b, mask_color.a);

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        break;
    
    case Type::COLOR_MASK:
        SDL_SetRenderDrawColor(renderer, mask_color.r, mask_color.g,
                                         mask_color.b, mask_color.a);

        SDL_SetTextureBlendMode(texture.get(), blendmode);

        [[fallthrough]];
    case Type::CHANGE_RESOLUTION:
        if (buffer_width == AUTO && buffer_height == AUTO) { generate_buffer(w, h); }
        else if (buffer_width == AUTO) { generate_buffer((buffer_height * w) / h, buffer_height); }
        else if (buffer_height == AUTO) { generate_buffer(buffer_width, ((buffer_width * h) / w)); }

        SDL_SetRenderTarget(renderer, buffer);
        
        // Apply changes to buffer
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture.get(), nullptr, nullptr);

        // Render buffer content
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderCopy(renderer, buffer, nullptr, &rect);

        // Reset default values
        SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
        break;
    case Type::NONE:
        SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);
        break;
    case Type::INVISIBLE:
        break;
    }
}