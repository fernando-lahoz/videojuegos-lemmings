#include "engine/render_2D.hpp"
#include "engine/IO.hpp"
#include "engine/engine.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <algorithm>
#include <ranges>

Camera2D::ID Camera2D::next_id = 0;

Camera2D::Camera2D()
    : world_frame{Point2f(0, 0), Point2f(1, 1)}, window_frame{}, id{next_id++}
{

}

Camera2D::Camera2D(Bound2f world_frame, Bound2f window_frame, int layer)
    : world_frame{world_frame}, window_frame{window_frame}, id{next_id++}, layer{layer}
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

Bound2f& Camera2D::get_window_frame()
{
    return window_frame;
}

Bound2f& Camera2D::get_world_frame()
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

uint64_t Camera2D::get_id()
{
    return id;
}

void Camera2D::set_shader(std::string entity_class, const Shader& shader)
{
    if (entity_class == "ALL") {
        is_global_shader_set = true;
    }
    shaders.emplace(std::move(entity_class), shader);
}

Shader* Camera2D::find_shader_for(const std::string& entity_class)
{
    auto it = shaders.find(entity_class);

    if (it != shaders.end())
    {
        return &it->second;
    }
    else if (is_global_shader_set)
    {
        return &global_shader;
    }
    else
    {
        return nullptr;
    }
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
    rect.x = (int)std::round(w_position.x);
    rect.y = (int)std::round(w_position.y);


    auto w_diag = world_to_raster(bound.diagonal(), camera, main_camera);
    rect.w = (int)std::round(w_diag.x);
    rect.h = (int)std::round(w_diag.y);


    return rect;
}

bool Render_2D::render_entity(Entity& entity, Camera2D& camera, Camera2D& main_camera, bool always_visible)
{
    if (entity.get_active_texture().get() != nullptr &&
        (always_visible || camera.is_visible(entity)))
    {
        auto e_bound = entity.bound2f();
        auto rect = bound_to_rect(e_bound, camera, main_camera);
        
        auto texture = entity.get_active_texture();

        Shader *shader = camera.find_shader_for(entity.get_class());
        if (shader != nullptr)
        {
            shader->render_copy(texture, rect);
        }
        else
        {
            SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);
        }

        return true;  
    }
    return false;
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

SDL_Renderer *Render_2D::get_sdl_renderer()
{
    return renderer;
}

Render_2D::Render_2D(const std::string& window_name, int width, int height)
{
    resolution = Vector2i(width, height);

    // Window with vsync
    window = SDL_CreateWindow(window_name.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
        throw error::sdl_exception(ERROR_CONTEXT);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
        throw error::sdl_exception(ERROR_CONTEXT);
    
    // Config alpha layers
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

void Render_2D::set_window_icon(const std::string& window_icon)
{
    auto icon = IMG_Load(window_icon.c_str());
    if (icon == nullptr)
        throw error::sdl_exception(ERROR_CONTEXT);
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

Texture Render_2D::load_texture(const std::string& file, bool cache)
{
    std::unique_lock lock(texture_mtx);

    if (textures.find(file) != textures.end())
    {
        return textures[file];
    }
    else
    {
        lock.unlock();

        Texture texture;
        texture.load(file, renderer);
        
        if (cache) {
            lock.lock();
            textures[file] = texture;
        }

        return texture;
    }
}

void Render_2D::flush_texture_cache()
{
    textures.clear();
}

Point2f bound_to_bound(Point2f p, Bound2f src, Bound2f dst)
{
    return Point2f(((p.x - src.pMin.x) / src.width()) * dst.width() + dst.pMin.x,
                   ((p.y - src.pMin.y) / src.height()) * dst.height() + dst.pMin.y);
}

Vector2f bound_to_bound(Vector2f p, Bound2f src, Bound2f dst)
{
    return Vector2f((((p.x) / src.width()) * dst.width()),
                   (((p.y) / src.height()) * dst.height()));
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

        // top
        rect1 = {.x = 0, .y = 0, .w = resolution.x, .h = (int)frame.pMin.y};
        // bottom
        rect2 = {.x = 0, .y = (int)frame.pMax.y, .w = resolution.x, .h = (int)std::ceil(frame.pMin.y)};
    }
    else// if (aspect_ratio < window_ar) // height limits
    {
        auto blank_width = resolution.x - (resolution.y * aspect_ratio);
        frame.pMin.x = blank_width / 2;
        frame.pMin.y = 0;
        frame.pMax.x = resolution.x - (blank_width / 2);
        frame.pMax.y = resolution.y;

        // left
        rect1 = {.x = 0, .y = 0, .w = (int)frame.pMin.x, .h = resolution.y};
        // right
        rect2 = {.x = (int)frame.pMax.x, .y = 0, .w = (int)std::ceil(frame.pMin.x), .h = resolution.y};
    }
    //SDL_Rect rect = {.x = (int)frame.pMin.x, .y = (int)frame.pMin.y,
    //                 .w = (int)frame.width(), .h = (int)frame.height()};
    //SDL_RenderSetClipRect(renderer, &rect);
}

// Draws and returns mouse-hovered entities
std::unordered_map<Entity*, Camera2D::ID> Render_2D::draw_and_return_hovered(std::vector<EntityPtr> &entities,
        std::vector<std::shared_ptr<Camera2D>>& cameras, Point2f mouse_position)
{
    clear_window();
    std::unordered_map<Entity*, Camera2D::ID> hovered_entities;
    Engine::EntityCollection::iterator over_bands_begin = entities.end();
    for (auto& camera : cameras | std::views::reverse)
    {
        auto world_mouse = raster_to_world(mouse_position, *camera, *cameras[0]);
        // Render drawables
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            auto& d = *it;

            auto z = d->get_position3D().z;
            if (std::isinf(z) && z < 0) {
                over_bands_begin = it;
                break;
            }

            FixedText *text_ptr = dynamic_cast<FixedText*>(d.get());
            if (text_ptr != nullptr) {
                render_fixed_text(*text_ptr, *camera, *cameras[0]);
            }
            else {
                bool visible = render_entity(*d, *camera, *cameras[0]);
                if (visible && d->contains(world_mouse, true))
                {
                    hovered_entities.insert({d.get(), camera->get_id()});
                }
            }
        }
    }
    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);
    auto& camera = cameras[0];
    {
        auto world_mouse = raster_to_world(mouse_position, *camera, *cameras[0]);
        // Render drawables
        for (auto it = over_bands_begin; it != entities.end(); ++it)
        {
            auto& d = *it;
            bool visible = render_entity(*d, *camera, *cameras[0], true);
            if (visible && d->contains(world_mouse, false))
            {
                hovered_entities.insert({d.get(), camera->get_id()});
            } 
        }
    }

    SDL_RenderPresent(renderer);
    return hovered_entities;
}