#include "engine/render_2D.hpp"
#include "engine/IO.hpp"
#include "engine/engine.hpp"

Camera2D::Camera2D()
    : src{Point2f(0, 0), Point2f(1, 1)}, dst{}
{

}

Camera2D::Camera2D(Bound2f world_frame, Bound2f window_frame)
    : src{world_frame}, dst{window_frame}
{

}

Point2f Camera2D::world_to_screen(Point2f world_point)
{
    Float x = ((world_point.x - src.pMin.x) / src.width()) * dst.width() + dst.pMin.x;
    Float y = ((world_point.y - src.pMin.y) / src.height()) * dst.height() + dst.pMin.y;

    return Point2f(x, y);
}

Vector2f Camera2D::world_to_screen(Vector2f world_vector)
{
    Float x = ((world_vector.x) / src.width()) * dst.width();
    Float y = ((world_vector.y) / src.height()) * dst.height();

    return Vector2f(x, y);
}

Point2f Camera2D::screen_to_world(Point2f screen_point)
{
    Float x = ((screen_point.x - dst.pMin.x) / dst.width()) * src.width() + src.pMin.x;
    Float y = ((screen_point.y - dst.pMin.y) / dst.height()) * src.height() + src.pMin.y;

    return Point2f(x, y);
}

Vector2f Camera2D::screen_to_world(Vector2f screen_vector)
{
    Float x = ((screen_vector.x) / dst.width()) * src.width();
    Float y = ((screen_vector.y) / dst.height()) * src.height();

    return Vector2f(x, y);
}

Bound2f Camera2D::get_window_frame() const
{
    return dst;
}

Bound2f Camera2D::get_world_frame() const
{
    return src;
}

void Camera2D::update_position(Engine&)
{
    // Do nothing by default
}

bool Camera2D::is_visible(const Entity& entity)
{
    return is_visible(entity.bound2f());
}

bool Camera2D::is_visible(const Bound2f& bound)
{
    return src.overlaps(bound);
}

void Camera2D::on_event_down(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

void Camera2D::on_event_up(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

//------------------------------------------------------------------------------

void Render_2D::clear_window(Spectrum color)
{
    SDL_SetRenderDrawColor(renderer, color.get_r(), color.get_g(), color.get_b(), color.get_a());
    SDL_RenderClear(renderer);
}

SDL_Rect Render_2D::entity_to_rect(Entity& e, Camera2D& camera)
{
    SDL_Rect rect;

    auto w_position = world_to_raster(e.get_position2D(), camera);
    rect.x = (int) (w_position.x);
    rect.y = (int) (w_position.y);


    auto w_diag = world_to_raster(e.bound2f().diagonal(), camera);
    rect.w = (int) (w_diag.x);
    rect.h = (int) (w_diag.y);


    return rect;
}

void Render_2D::render_entity(Entity& entity, Camera2D& camera)
{
    if (camera.is_visible(entity))
    {
        auto rect = entity_to_rect(entity, camera);

        auto texture = entity.get_active_texture();
        SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);          
    }
}

void Render_2D::render_fixed_text(FixedText& text, Camera2D& camera)
{
    auto bound = text.bound2f();
    auto [w_map, h_map] = text.texture_letter_size;
    auto [w_pre, h_pre] = bound.diagonal();
    auto [w, h] = world_to_raster(bound.diagonal(), camera);

    for (auto letter : text.entity_name)
    {
        if (camera.is_visible(bound))
        {
            
            auto [x_map, y_map] = text.map(letter);
            SDL_Rect letter_in_texture = {.x = x_map * w_map, .y = y_map * h_map, .w = w_map, .h = h_map};
            Texture font_texture = text.get_active_texture();

            auto [x, y] = world_to_raster(bound.pMin, camera);
            SDL_Rect rect = {.x = (int)x, .y = (int)y, .w = (int)w, .h = (int)h};
            SDL_RenderCopy(renderer, font_texture.get(), &letter_in_texture, &rect);
        }
        bound.pMin.x += w_pre;
        bound.pMax.x += w_pre;
    }
}

Render_2D::Render_2D(std::string window_name, int width, int height)
{
    resolution = Vector2i(width, height);

    // Window with vsync
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

   
    // Config alpha layers
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Texture Render_2D::load_texture(const std::string& file)
{
    if (textures.find(file) != textures.end())
    {
        return textures[file];
    }
    else
    {
        Texture texture;
        texture.load(file, renderer);
        textures[file] = texture;

        return texture;
    }
}


Point2f Render_2D::world_to_raster(Point2f world_point, Camera2D& camera)
{
    //std::cout << "World: (" << world_point.x << ", " << world_point.y << ")\n";
    auto screen_p = camera.world_to_screen(world_point);
    auto w_frame = camera.get_window_frame();
    auto p = Point2f(((screen_p.x - w_frame.pMin.x) / w_frame.width()) * resolution.x,
                   ((screen_p.y - w_frame.pMin.y) / w_frame.height()) * resolution.y);
    //std::cout << "Raster: (" << p.x << ", " << p.y << ")\n";
    return p;
}

Vector2f Render_2D::world_to_raster(Vector2f world_vector, Camera2D& camera)
{
    auto screen_v = camera.world_to_screen(world_vector);
    auto w_frame = camera.get_window_frame();
    return Vector2f(((screen_v.x) / w_frame.width()) * resolution.x,
                    ((screen_v.y) / w_frame.height()) * resolution.y);
}

Point2f Render_2D::raster_to_world(Point2f raster_point, Camera2D& camera)
{
    auto w_frame = camera.get_window_frame();
    auto screen_p = Point2f((raster_point.x * w_frame.width() / resolution.x) + w_frame.pMin.x,
                            (raster_point.y * w_frame.height() / resolution.y) + w_frame.pMin.y);
    return camera.screen_to_world(screen_p);
}

Vector2f Render_2D::raster_to_world(Vector2f raster_vector, Camera2D& camera)
{
    auto w_frame = camera.get_window_frame();
    auto screen_v = Vector2f((raster_vector.x * w_frame.width() / resolution.x),
                             (raster_vector.y * w_frame.height() / resolution.y));
    return camera.screen_to_world(screen_v);
}



void Render_2D::draw(std::vector<EntityPtr> &entities,
        std::vector<std::shared_ptr<Camera2D>>& cameras)
{
    clear_window(Spectrum(0.529*255, 0.808*255, 0.922*255));

    for (auto& camera : cameras)
    {
        // Render drawables
        for (auto &d : entities)
        {
            FixedText *text_ptr = dynamic_cast<FixedText*>(d.get());
            if (text_ptr != nullptr) {
                render_fixed_text(*text_ptr, *camera);
            }
            else {
                render_entity(*d, *camera);
            }
        }
    }

    SDL_RenderPresent(renderer);
}