#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "lib/spectrum.hpp"
#include "lib/texture.hpp"
#include "engine/entity.hpp"
#include "engine/IO.hpp"
#include "engine/fixed_text.hpp"
#include "engine/shader.hpp"

class Engine;

class Camera2D
{
public:
    using ID = int64_t;

protected:
    Bound2f world_frame, window_frame;
    int64_t id;
    int layer = 0;
    bool deleted = false;

    std::unordered_map<std::string, Shader> shaders;
    Shader global_shader;
    bool is_global_shader_set = false;

    static ID next_id;

public:
    Camera2D();

    Camera2D(Bound2f world_frame, Bound2f window_frame, int layer = 0);

    virtual ~Camera2D() = default;

    Point2f world_to_screen(Point2f world_point);
    Vector2f world_to_screen(Vector2f world_vector);

    Point2f screen_to_world(Point2f screen_point);
    Vector2f screen_to_world(Vector2f screen_vector);

    Bound2f& get_window_frame();
    Bound2f& get_world_frame();

    virtual void update_position(Engine&);

    bool is_visible(const Entity& entity);
    bool is_visible(const Bound2f& bound);

    virtual void on_event_down(Engine&, EngineIO::InputEvent);
    virtual void on_event_up(Engine&, EngineIO::InputEvent);

    bool is_deleted() const;
    void destroy();

    void change_layer(int new_layer);
    int get_layer();

    uint64_t get_id();

    // Applies this shader to all entities of the especified class
    void set_shader(std::string entity_class, const Shader& shader);

    Shader* find_shader_for(const std::string& entity_class);
};

class Render_2D
{
protected:

    std::mutex texture_mtx;

    std::unordered_map<std::string, Texture> textures;

    void clear_window(Spectrum color = Spectrum(0, 0, 0));

    SDL_Rect bound_to_rect(Bound2f bound, Camera2D& camera, Camera2D& main_camera);

    bool render_entity(Entity& entity, Camera2D& camera, Camera2D& main_camera, bool always_visible = false);
    void render_fixed_text(FixedText& text, Camera2D& camera, Camera2D& main_camera);

public:
    SDL_Rect rect1, rect2;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Vector2i resolution;
    Bound2f frame;

    Render_2D() = default;
    Render_2D(const std::string& window_name, int width, int height);

    Texture load_texture(const std::string& file, bool cache);
    void flush_texture_cache();
    void set_window_icon(const std::string& window_icon);

    //Updates resolution and printable frame
    void update_resolution(Engine& engine);

    SDL_Renderer *get_sdl_renderer();

    Point2f world_to_raster(Point2f world_point, Camera2D& camera, Camera2D& main_camera);
    Vector2f world_to_raster(Vector2f world_vector, Camera2D& camera, Camera2D& main_camera);

    Point2f raster_to_world(Point2f raster_point, Camera2D& camera, Camera2D& main_camera);
    Vector2f raster_to_world(Vector2f raster_vector, Camera2D& camera, Camera2D& main_camera);

    std::unordered_map<Entity*, Camera2D::ID> draw_and_return_hovered(std::vector<EntityPtr> &entities,
            std::vector<std::shared_ptr<Camera2D>>& cameras, Point2f mouse_position);


    inline void set_fullscreen()
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }

    inline void set_windowmode()
    {
        SDL_SetWindowFullscreen(window, 0);
    }

    inline void set_window_size(Vector2i size)
    {
        SDL_SetWindowSize(window, size.x, size.y);
    }

    inline Vector2i get_window_size()
    {
        Vector2i size;
        SDL_GetWindowSize(window, &size.x, &size.y);
        return size;
    }

    inline void set_window_title(const std::string &title)
    {
        SDL_SetWindowTitle(window, title.c_str());
    }

};