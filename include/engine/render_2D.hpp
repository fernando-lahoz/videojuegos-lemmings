#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <algorithm>
#include <unordered_map>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "lib/spectrum.hpp"
#include "lib/texture.hpp"
#include "engine/entity.hpp"
#include "engine/IO.hpp"
#include "engine/fixed_text.hpp"

class Engine;

class Camera2D
{
protected:
    Bound2f src, dst;

public:
    Camera2D();

    Camera2D(Bound2f world_frame, Bound2f window_frame);

    Point2f world_to_screen(Point2f world_point);
    Vector2f world_to_screen(Vector2f world_vector);

    Point2f screen_to_world(Point2f screen_point);
    Vector2f screen_to_world(Vector2f screen_vector);

    Bound2f get_window_frame() const;
    Bound2f get_world_frame() const;

    virtual void update_position(Engine&);

    bool is_visible(const Entity& entity);
    bool is_visible(const Bound2f& bound);

    virtual void on_event_down(Engine&, EngineIO::InputEvent);
    virtual void on_event_up(Engine&, EngineIO::InputEvent);
};

class Render_2D
{
protected:

    std::unordered_map<std::string, Texture> textures;

    void clear_window(Spectrum color = Spectrum(0, 0, 0));

    SDL_Rect entity_to_rect(Entity& e, Camera2D& camera);

    void render_entity(Entity& entity, Camera2D& camera);

    void render_fixed_text(FixedText& text, Camera2D& camera);

public:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Vector2i resolution;

    Render_2D() = default;
    Render_2D(std::string window_name, int width, int height);

    Texture load_texture(const std::string& file);

    Point2f world_to_raster(Point2f world_point, Camera2D& camera);
    Vector2f world_to_raster(Vector2f world_vector, Camera2D& camera);

    Point2f raster_to_world(Point2f raster_point, Camera2D& camera);
    Vector2f raster_to_world(Vector2f raster_vector, Camera2D& camera);

    void draw(std::vector<EntityPtr> &entities, Camera2D& camera);
};