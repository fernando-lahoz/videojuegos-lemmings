#include "engine/render_2D.hpp"
#include "engine/IO.hpp"
#include "engine/engine.hpp"

#include <ranges>

Camera2D::Camera2D()
    : world_frame{Point2f(0, 0), Point2f(1, 1)}, window_frame{}
{

}

Camera2D::Camera2D(Bound2f world_frame, Bound2f window_frame, int layer)
    : world_frame{world_frame}, window_frame{window_frame}, layer{layer}
{

}

Point2f Camera2D::world_to_screen(Point2f world_point)
{
    Float x = ((world_point.x - world_frame.pMin.x) / world_frame.width()) * window_frame.width() + window_frame.pMin.x;
    Float y = ((world_point.y - world_frame.pMin.y) / world_frame.height()) * window_frame.height() + window_frame.pMin.y;

    return Point2f(x, y);
}

Vector2f Camera2D::world_to_screen(Vector2f world_vector)
{
    Float x = ((world_vector.x) / world_frame.width()) * window_frame.width();
    Float y = ((world_vector.y) / world_frame.height()) * window_frame.height();

    return Vector2f(x, y);
}

Point2f Camera2D::screen_to_world(Point2f screen_point)
{
    Float x = ((screen_point.x - window_frame.pMin.x) / window_frame.width()) * world_frame.width() + world_frame.pMin.x;
    Float y = ((screen_point.y - window_frame.pMin.y) / window_frame.height()) * world_frame.height() + world_frame.pMin.y;

    return Point2f(x, y);
}

Vector2f Camera2D::screen_to_world(Vector2f screen_vector)
{
    Float x = ((screen_vector.x) / window_frame.width()) * world_frame.width();
    Float y = ((screen_vector.y) / window_frame.height()) * world_frame.height();

    return Vector2f(x, y);
}

Bound2f Camera2D::get_window_frame() const
{
    return window_frame;
}

Bound2f Camera2D::get_world_frame() const
{
    return world_frame;
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
    return world_frame.overlaps(bound);
}

void Camera2D::on_event_down(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

void Camera2D::on_event_up(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

bool Camera2D::is_deleted() const
{
    return deleted;
}

void Camera2D::destroy()
{
    deleted = true;
}

void Camera2D::change_layer(int new_layer)
{
    layer = new_layer;
}

int Camera2D::get_layer()
{
    return layer;
}

//------------------------------------------------------------------------------

void Render_2D::clear_window(Spectrum color)
{
    SDL_SetRenderDrawColor(renderer, color.get_r(), color.get_g(), color.get_b(), color.get_a());
    SDL_RenderClear(renderer);
}

SDL_Rect Render_2D::bound_to_rect(Bound2f bound, Camera2D& camera, Camera2D& main_camera)
{
    SDL_Rect rect;

    auto w_position = world_to_raster(bound.pMin, camera, main_camera);
    rect.x = (int) (w_position.x);
    rect.y = (int) (w_position.y);


    auto w_diag = world_to_raster(bound.diagonal(), camera, main_camera);
    rect.w = (int) (w_diag.x);
    rect.h = (int) (w_diag.y);


    return rect;
}

void Render_2D::render_entity(Entity& entity, Camera2D& camera, Camera2D& main_camera)
{
    if (camera.is_visible(entity))
    {
        auto e_bound = entity.bound2f();
        auto rect = bound_to_rect(e_bound, camera, main_camera);
        
        auto texture = entity.get_active_texture();

        // auto cam_bound = camera.get_world_frame();
        // auto cam_rect = bound_to_rect(cam_bound, camera, main_camera);

        // rect.x = std::max(cam_rect.x, rect.x);
        // rect.y = std::max(cam_rect.y, rect.y);
        // rect.w = std::min(rect.w, cam_rect.w - std::abs(cam_rect.x - rect.x));
        // rect.h = std::min(rect.h, cam_rect.h - std::abs(cam_rect.y - rect.y));

        // SDL_Rect clip;
        // clip.x = (int) (((cam_bound.pMin.x - e_bound.pMin.x) * texture.get_width()) / e_bound.width());
        // clip.y = (int) (((cam_bound.pMin.y - e_bound.pMin.y) * texture.get_height()) / e_bound.height());
        // clip.w = (int) ((cam_bound.width() * texture.get_width()) / e_bound.width());
        // clip.h = (int) ((cam_bound.height() * texture.get_height()) / e_bound.height());

        SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);          
    }
}

void Render_2D::render_fixed_text(FixedText& text, Camera2D& camera, Camera2D& main_camera)
{
    auto bound = text.bound2f();
    auto [w_map, h_map] = text.texture_letter_size;
    auto [w_pre, h_pre] = bound.diagonal();
    auto [w, h] = world_to_raster(bound.diagonal(), camera, main_camera);

    for (auto letter : text.entity_name)
    {
        if (camera.is_visible(bound))
        {
            
            auto [x_map, y_map] = text.map(letter);
            SDL_Rect letter_in_texture = {.x = x_map * w_map, .y = y_map * h_map, .w = w_map, .h = h_map};
            Texture font_texture = text.get_active_texture();

            auto [x, y] = world_to_raster(bound.pMin, camera, main_camera);
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
    window = SDL_CreateWindow(window_name.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_RESIZABLE);
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

Point2f bound_to_bound(Point2f p, Bound2f src, Bound2f dst)
{
    return Point2f(((p.x - src.pMin.x) / src.width()) * dst.width() + dst.pMin.x,
                   ((p.y - src.pMin.y) / src.height()) * dst.height() + dst.pMin.y);
}

Vector2f bound_to_bound(Vector2f p, Bound2f src, Bound2f dst)
{
    return Vector2f(((p.x) / src.width()) * dst.width(),
                   ((p.y) / src.height()) * dst.height());
}


Point2f Render_2D::world_to_raster(Point2f world_point, Camera2D& camera, Camera2D& main_camera)
{
    auto cam_p = camera.world_to_screen(world_point);
    auto w_frame = main_camera.get_window_frame();

    return bound_to_bound(cam_p, w_frame, frame);
}

Vector2f Render_2D::world_to_raster(Vector2f world_vector, Camera2D& camera, Camera2D& main_camera)
{
    auto cam_p = camera.world_to_screen(world_vector);
    auto w_frame = main_camera.get_window_frame();

    return bound_to_bound(cam_p, w_frame, frame);
}

Point2f Render_2D::raster_to_world(Point2f raster_point, Camera2D& camera, Camera2D& main_camera)
{
    auto w_frame = main_camera.get_window_frame();
    return camera.screen_to_world(bound_to_bound(raster_point, frame, w_frame));
}

Vector2f Render_2D::raster_to_world(Vector2f raster_vector, Camera2D& camera, Camera2D& main_camera)
{
    auto w_frame = main_camera.get_window_frame();
    return camera.screen_to_world(bound_to_bound(raster_vector, frame, w_frame));
}

void Render_2D::update_resolution(Engine& engine)
{
    SDL_GetWindowSizeInPixels(window, &resolution.x, &resolution.y);

    auto f = engine.get_main_camera().get_window_frame();
    auto aspect_ratio = f.width() / f.height();
    auto window_ar = (Float)resolution.x / resolution.y;

    if (aspect_ratio > window_ar) // width limits
    {
        auto blank_height = resolution.y - (resolution.x / aspect_ratio);
        frame.pMin.x = 0;
        frame.pMin.y = blank_height / 2;
        frame.pMax.x = resolution.x;
        frame.pMax.y = resolution.y - (blank_height / 2);
    }
    else// if (aspect_ratio < window_ar) // height limits
    {
        auto blank_width = resolution.x - (resolution.y * aspect_ratio);
        frame.pMin.x = blank_width / 2;
        frame.pMin.y = 0;
        frame.pMax.x = resolution.x - (blank_width / 2);
        frame.pMax.y = resolution.y;
    }
    SDL_Rect rect = {.x = (int)frame.pMin.x, .y = (int)frame.pMin.y,
                     .w = (int)frame.width(), .h = (int)frame.height()};
    SDL_RenderSetClipRect(renderer, &rect);
}

void Render_2D::draw(std::vector<EntityPtr> &entities,
        std::vector<std::shared_ptr<Camera2D>>& cameras)
{
    clear_window();

    for (auto& camera : cameras | std::views::reverse)
    {
        // Render drawables
        for (auto &d : entities)
        {
            FixedText *text_ptr = dynamic_cast<FixedText*>(d.get());
            if (text_ptr != nullptr) {
                render_fixed_text(*text_ptr, *camera, *cameras[0]);
            }
            else {
                render_entity(*d, *camera, *cameras[0]);
            }
        }
    }

    SDL_RenderPresent(renderer);
}