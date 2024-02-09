#pragma once

#include <memory>
#include <vector>

#include "lib/texture.hpp"

class Entity;
class Game;

class Engine
{
private:
    void send_key_down_event(SDL_KeyboardEvent key);
    void send_key_up_event(SDL_KeyboardEvent key);
    bool process_events();
    double get_delta_time();
    void compute_physics(double delta_time);
    void sort_by_z_buffer();
    void delete_dead_entities();
    void process_new_entities();

public:
    Engine(std::shared_ptr<Game> game);
    void start();
    Texture load_texture(const char* path);
    std::vector<std::shared_ptr<Entity>>* get_entities();
};

using Engine_ptr = Engine*;