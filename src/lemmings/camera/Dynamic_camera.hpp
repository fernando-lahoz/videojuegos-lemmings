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

public:
    Dynamic_camera(Game_info &_game_info)
        : Camera2D(Bound2f(Point2f(0, 0), Point2f(1, 1)), Bound2f(Point2f(0, 0), Point2f(800, 800))), game_info(_game_info)
    {
    }

    Dynamic_camera(Game_info &_game_info, Bound2f _world_frame, Bound2f _window_frame, int id) : game_info(_game_info)
    {
        this->world_frame = _world_frame;
        this->window_frame = _window_frame;
        this->layer = id;
    }

    Dynamic_camera(Game_info &_game_info, Bound2f frame) : game_info(_game_info)
    {
        this->world_frame = frame;
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

    void update_position(Engine &engine) override
    {
        Float delta_time = engine.get_delta_time();

        if (!game_info.get_is_camera_stopped())
        {
            auto p = engine.get_mouse_position_in_camera(*this);
            bool move_left = world_frame.is_near_border(p, Bound2f::Border::LEFT, 10) || world_frame.is_past_border(p, Bound2f::Border::LEFT) || engine.is_key_down(EngineIO::InputEvent::RIGHT);
            bool move_right = world_frame.is_near_border(p, Bound2f::Border::RIGHT, 10) || world_frame.is_past_border(p, Bound2f::Border::RIGHT) || engine.is_key_down(EngineIO::InputEvent::LEFT);
            if (move_right && !move_left)
            {
                if (world_frame.pMin.x - 200 * delta_time < 0)
                {
                    world_frame.pMin.x = 0;
                    world_frame.pMax.x -= world_frame.pMin.x;
                    game_info.set_pos_camera(320);
                }
                else
                {
                    world_frame.pMin.x -= 200 * delta_time;
                    world_frame.pMax.x -= 200 * delta_time;
                    game_info.set_pos_camera(game_info.get_pos_camera() - 200 * delta_time);
                }
            }
            if (move_left && !move_right)
            {
                if (world_frame.pMax.x + 200 * delta_time > 3168)
                {
                    world_frame.pMin.x = 3168 - (world_frame.pMax.x - world_frame.pMin.x);
                    world_frame.pMax.x = 3168;
                    game_info.set_pos_camera(2848);
                }
                else
                {
                    world_frame.pMin.x += 200 * delta_time;
                    world_frame.pMax.x += 200 * delta_time;
                    game_info.set_pos_camera(game_info.get_pos_camera() + 200 * delta_time);
                }
            }
            //std::cout << "Camera Position:" << game_info.get_pos_camera() << std::endl;
        }

        if (game_info.get_do_restart_camera())
        {
            game_info.set_do_restart_camera(false);
            set_position(Utils::LEVEL_CAMERA_POS_INI[game_info.get_difficulty()][game_info.get_level()]);
            game_info.set_pos_camera(Utils::LEVEL_CAMERA_POS_INI[game_info.get_difficulty()][game_info.get_level()]);
        }
    }
};