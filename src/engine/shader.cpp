#include "engine/shader.hpp"

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/render_2D.hpp"


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

    buffer_width = w;
    buffer_height = h;
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

//src_color , dst_color, color_op -> color * 0 + alpha * 
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

static Point2f bound_to_bound(Point2f p, Bound2f src, Bound2f dst)
{
    return Point2f(((p.x - src.pMin.x) / src.width()) * dst.width() + dst.pMin.x,
                   ((p.y - src.pMin.y) / src.height()) * dst.height() + dst.pMin.y);
}

static Vector2f bound_to_bound(Vector2f p, Bound2f src, Bound2f dst)
{
    return Vector2f((((p.x) / src.width()) * dst.width()),
                   (((p.y) / src.height()) * dst.height()));
}

void Shader::render_copy(Entity& entity, Camera2D& camera, Camera2D& main_camera, Render_2D& render2d)
{
    auto texture = entity.get_active_texture();
    int w = texture.get_width(), h = texture.get_height();

    int h_aux = 0, w_aux = 0;

    switch (type)
    {
    case Type::FILLED_BOX:
    {
        if (this->buffer_width <= 0 || this->buffer_height <= 0)
            break;

        auto e_bound = entity.bound2f();
        auto rect = render2d.bound_to_rect(e_bound, camera, main_camera);

        w_aux = rect.w;
        h_aux = rect.h;
        rect.w = (rect.w * this->buffer_width) / 100; // buffer_widht = scale percentage
        rect.h = (rect.h * this->buffer_height) / 100;
        rect.x += (w_aux - rect.w) / 2;
        rect.y += (h_aux - rect.h) / 2;

        SDL_SetRenderDrawColor(renderer, mask_color.r, mask_color.g,
                                         mask_color.b, mask_color.a);

        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        break;
    }
    case Type::COLOR_MASK:
        if (texture.get() == nullptr)
            break;

        SDL_SetRenderDrawColor(renderer, mask_color.r, mask_color.g,
                                         mask_color.b, 0);

        SDL_SetTextureBlendMode(texture.get(), blendmode);

        [[fallthrough]];
    case Type::CHANGE_RESOLUTION:
    {
        if (texture.get() == nullptr)
            break;

        auto cam_window_bound = camera.get_window_frame();
        w = cam_window_bound.diagonal().x;
        h = cam_window_bound.diagonal().y;

        if (buffer_width == AUTO && buffer_height == AUTO) { generate_buffer(w, h); }
        else if (buffer_width == AUTO) { generate_buffer((buffer_height * w) / h, buffer_height); }
        else if (buffer_height == AUTO) { generate_buffer(buffer_width, ((buffer_width * h) / w)); }

        SDL_SetRenderTarget(renderer, buffer);

        Bound2f buffer_bound = Bound2f({0, 0}, {Float(buffer_width), Float(buffer_height)});

        auto cam_rect = render2d.bound_to_rect(camera.get_world_frame(), camera, main_camera);

        SDL_Rect entity_rect;
        auto w_position = bound_to_bound(camera.world_to_screen(entity.get_position2D()), cam_window_bound, buffer_bound);
        entity_rect.x = (int)(w_position.x);
        entity_rect.y = (int)(w_position.y);

        auto w_diag = bound_to_bound(camera.world_to_screen(entity.get_diagonal()), cam_window_bound, buffer_bound);
        entity_rect.w = (int)std::round(w_diag.x);
        entity_rect.h = (int)std::round(w_diag.y);

        // std::cout << camera.world_to_screen(entity.get_position2D())<< '\n';
        // std::cout << camera.get_window_frame() << '\n';
        // std::cout << buffer_bound<< '\n';
        // std::cout << buffer_width <<' ' << buffer_height << '\n';

        // std::cout << "[ " << entity_rect.x << ", " << entity_rect.y << ", " << entity_rect.w << ", " << entity_rect.h << "]\n";
        
        // Apply changes to buffer
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture.get(), nullptr, &entity_rect);

        // Render buffer content
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderCopy(renderer, buffer, nullptr, &cam_rect);

        // Reset default values
        SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
        break;
    }
    case Type::NONE:
    {
        auto e_bound = entity.bound2f();
        auto rect = render2d.bound_to_rect(e_bound, camera, main_camera);
    
        if (texture.get() != nullptr)
        {
            SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);
        }
        break;
    }
    case Type::INVISIBLE:
        break;
    }
}