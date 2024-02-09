#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <algorithm>
#include <unordered_map>

#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/bounding_box.hpp"
#include "lib/spectrum.hpp"
#include "../lib/texture.cpp"
#include "entity.cpp"



class Camera2D
{
    protected:
    
    Bound2f frame;

    public:

    Camera2D()
    {
        frame = Bound2f(Point2f(0, 0), Point2f(1, 1));
    }

    Camera2D(Bound2f frame)
    {
        this->frame = frame;
    }

    Point2f world_to_screen(Point3f world_point)
    {
        float x = (world_point.x - frame.pMin.x) / (frame.width());
        float y = (world_point.y - frame.pMin.y) / (frame.height());

        return Point2f(x, y);
    }

    Vector2f world_to_screen(Vector2f world_vector)
    {
        float x = world_vector.x / frame.width();
        float y = world_vector.y / frame.height();

        return Vector2f(x, y);
    }

    void moveRight(Float delta)
    {
        frame.pMin.x += delta;
        frame.pMax.x += delta;
    }

    void moveLeft(Float delta)
    {
        frame.pMin.x -= delta;
        frame.pMax.x -= delta;
    }

    void moveUp(Float delta)
    {
        frame.pMin.y += delta;
        frame.pMax.y += delta;
    }

    void moveDown(Float delta)
    {
        frame.pMin.y -= delta;
        frame.pMax.y -= delta;
    }

    bool isVisible(EntityPtr &entity)
    {
        return frame.overlaps(entity->bound2f());
    }

    virtual void on_key_down(Engine_ptr engine, SDL_KeyboardEvent key) {}
    virtual void on_key_up(Engine_ptr engine, SDL_KeyboardEvent key) {}
};

typedef std::shared_ptr<Camera2D> Camera_ptr;

class Render_2D
{
    protected:

    std::unordered_map<std::string, Texture> textures;


    /******************** Methods ************************/


    void clear_window(Spectrum color=Spectrum(0, 0, 0))
    {
        SDL_SetRenderDrawColor(renderer, color.getR(), color.getG(), color.getB(), color.getA());
        SDL_RenderClear(renderer);
    }

    SDL_Rect entity_to_rect(EntityPtr e, Camera_ptr camera)
    {
        SDL_Rect rect;

        auto l_position = camera->world_to_screen(e->get_position3D());
        rect.x = (uint) (l_position.x * resolution.x);
        rect.y = (uint) (l_position.y * resolution.y);


        auto l_diag = camera->world_to_screen(e->bound2f().diagonal());
        rect.w = (uint) (l_diag.x * resolution.x);
        rect.h = (uint) (l_diag.y * resolution.y);


        return rect;
    }

    void render_entity(EntityPtr entity, Camera_ptr camera)
    {
        if (camera->isVisible(entity))
        {
            auto rect = entity_to_rect(entity, camera);

            auto texture = entity->get_active_texture();
            SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);          
        }
    }

    public:

    SDL_Window* window;
    SDL_Renderer* renderer;
    uint2 resolution;

    Render_2D() {}

    Render_2D(int width, int height)
    {
        resolution = uint2(width, height);

        // Window with vsync
        window = SDL_CreateWindow("Render_2D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        // Config alpha layers
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    }

    Texture loadTexture(std::string file)
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

    void draw(std::vector<EntityPtr> &entities, Camera_ptr camera)
    {
        clear_window(Spectrum(0.529*255, 0.808*255, 0.922*255));

        // Render drawables
        for (auto &d : entities)
        {
            render_entity(d, camera);
        }

        SDL_RenderPresent(renderer);
    }
};