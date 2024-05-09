#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <chrono>

#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "engine/render_2D.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Dynamic_camera : public Camera2D
{
    Game_info &game_info;
    EngineIO::InputEvent left_button, right_button, up_button, down_button;

    unsigned int max_width = 3168, max_heigth = 320;
    Float current_zoom = 1.0f;
    Vector2f full_diagonal;

public:
    Dynamic_camera(Game_info &_game_info)
        : Camera2D(Bound2f(Point2f(0, 0), Point2f(1, 1)), Bound2f(Point2f(0, 0), Point2f(800, 800))), game_info(_game_info)
    {
        assign_keys();
        full_diagonal = world_frame.diagonal();
    }

    Dynamic_camera(Game_info &_game_info, Bound2f _world_frame, Bound2f _window_frame, int id) : game_info(_game_info)
    {
        this->world_frame = _world_frame;
        this->window_frame = _window_frame;
        this->layer = id;
        assign_keys();

        full_diagonal = world_frame.diagonal();
    }

    Dynamic_camera(Game_info &_game_info, Bound2f frame) : game_info(_game_info)
    {
        this->world_frame = frame;
        assign_keys();
    }

    void set_position(int x)
    {
        float half = std::abs(world_frame.pMin.x - world_frame.pMax.x) / 2;
        world_frame.pMin.x = x - half;
        world_frame.pMax.x = x + half;
    }

    Float get_position()
    {
        Float half = std::abs(world_frame.pMin.x - world_frame.pMax.x) / 2;
        return half;
    }

    void update_zoom(Engine &engine)
    {
        if (engine.is_key_down(EngineIO::InputEvent::CTRL))
        {
            current_zoom += 0.1f;
            if (current_zoom > 2.0f)
                current_zoom = 2.0f;
            
            world_frame.pMin = world_frame.centroid() - (full_diagonal/2) / current_zoom;
            world_frame.pMax = world_frame.centroid() + (full_diagonal/2) / current_zoom;
        }

        if (engine.is_key_down(EngineIO::InputEvent::ALT))
        {
            current_zoom -= 0.1f;
            if (current_zoom < 1.0f)
                current_zoom = 1.0f;
            
            world_frame.pMin = world_frame.centroid() - (full_diagonal/2) / current_zoom;
            world_frame.pMax = world_frame.centroid() + (full_diagonal/2) / current_zoom;
        }
    }

    void update_position(Engine &engine) override
    {
        Float delta_time = engine.get_delta_time() / engine.get_delta_time_factor();

        if (!game_info.get_is_camera_stopped())
        {
            update_zoom(engine);

            auto p = engine.get_mouse_position_in_camera(*this);
            bool move_left = world_frame.is_near_border(p, Bound2f::Border::RIGHT, 10) || world_frame.is_past_border(p, Bound2f::Border::RIGHT) || engine.is_key_down(left_button);
            bool move_right = world_frame.is_near_border(p, Bound2f::Border::LEFT, 10) || world_frame.is_past_border(p, Bound2f::Border::LEFT) || engine.is_key_down(right_button);
            //bool move_up = engine.is_key_down(up_button);
            //bool move_down = engine.is_key_down(down_button);
            bool move_up = false;
            bool move_down = false;

            if (p.y < world_frame.pMin.y + 10) 
                move_up = true;

            if (p.y > world_frame.pMax.y + 30)
                move_down = true;



            /************ Camera movement ***********/

            if (move_left && !move_right)
            {
                world_frame.pMin.x -= 200 * delta_time;
                world_frame.pMax.x -= 200 * delta_time;
                //game_info.set_pos_camera(game_info.get_pos_camera() - 200 * delta_time);
            }
            if (move_right && !move_left)
            {
                world_frame.pMin.x += 200 * delta_time;
                world_frame.pMax.x += 200 * delta_time;
                //game_info.set_pos_camera(game_info.get_pos_camera() + 200 * delta_time);
            }
            // std::cout << "Camera Position:" << game_info.get_pos_camera() << std::endl;
        
            if (move_down && !move_up)
            {
                world_frame.pMin.y += 200 * delta_time;
                world_frame.pMax.y += 200 * delta_time;
                //game_info.set_pos_camera_y(game_info.get_pos_camera_y() - 200 * delta_time);
            }

            if (move_up && !move_down)
            {
                world_frame.pMin.y -= 200 * delta_time;
                world_frame.pMax.y -= 200 * delta_time;
            }

            /************ Corrections *************/
            
            if (world_frame.pMin.x - 200 * delta_time < 0)
            {
                auto diagonal = world_frame.diagonal();
                world_frame.pMin.x = 0;
                world_frame.pMax = world_frame.pMin + diagonal;
            }

            if (world_frame.pMax.y + 200 * delta_time > max_heigth)
            {
                auto diagonal = world_frame.diagonal();
                world_frame.pMin.y = max_heigth - (world_frame.pMax.y - world_frame.pMin.y);
                world_frame.pMax = world_frame.pMin + diagonal;
            }

            if (world_frame.pMin.y - 200 * delta_time < 0)
            {
                auto diagonal = world_frame.diagonal();
                world_frame.pMin.y = 0;
                world_frame.pMax = world_frame.pMin + diagonal;
            }

            if (world_frame.pMax.x + 200 * delta_time > max_width)
            {
                auto diagonal = world_frame.diagonal();
                world_frame.pMin.x = max_width - (world_frame.pMax.x - world_frame.pMin.x);
                world_frame.pMax = world_frame.pMin + diagonal;
                //game_info.set_pos_camera(max_width - get_world_frame().diagonal().x / 2);
            }
        }

        if (game_info.get_do_restart_camera())
        {
            game_info.set_do_restart_camera(false);
            set_position(Utils::LEVEL_CAMERA_POS_INI[game_info.get_difficulty()][game_info.get_level()]);
            game_info.set_pos_camera(Utils::LEVEL_CAMERA_POS_INI[game_info.get_difficulty()][game_info.get_level()]);
        }
    }

    void assign_keys()
    {
        EngineIO::InputEvent aux[18];
        KeyBindings().readKeyBindingsFile(aux);
        left_button = aux[16];
        right_button = aux[17];
    }
};