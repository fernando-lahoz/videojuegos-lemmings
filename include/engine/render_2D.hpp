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

class Engine;

class Camera2D
{
protected:

    Bound2f frame;

public:

    Camera2D();

    Camera2D(Bound2f frame);

    Point2f world_to_screen(Point3f world_point);

    Vector2f world_to_screen(Vector2f world_vector);

    void moveRight(Float delta);

    void moveLeft(Float delta);

    void moveUp(Float delta);

    void moveDown(Float delta);

    bool isVisible(Entity& entity);

    virtual void on_key_down(Engine&, SDL_KeyboardEvent);
    virtual void on_key_up(Engine&, SDL_KeyboardEvent);
};

class Render_2D
{
protected:

    std::unordered_map<std::string, Texture> textures;

    void clear_window(Spectrum color = Spectrum(0, 0, 0));

    SDL_Rect entity_to_rect(Entity& e, Camera2D& camera);

    void render_entity(Entity& entity, Camera2D& camera);

public:

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    // TODO: This was a int2
    Vector2i resolution;

    Render_2D() = default;

    Render_2D(int width, int height);

    Texture load_texture(const std::string& file);

    void draw(std::vector<EntityPtr> &entities, Camera2D& camera);
};