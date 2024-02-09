#pragma once

#include "../lib/Texture.cpp"
#include <memory>
#include <vector>

class Entity;
class Game;

class Engine
{
    void send_key_down_event(SDL_KeyboardEvent key);
    void send_key_up_event(SDL_KeyboardEvent key);
    bool processEvents();
    double get_delta_time();
    void compute_physics(double delta_time);
    void sort_by_z_buffer();
    void delete_dead_entities();
    void process_new_entities();

    public:

    Engine(std::shared_ptr<Game> game);
    void start();
    Texture loadTexture(const char* path);
    std::vector<std::shared_ptr<Entity>>* get_entities();
};

typedef Engine* Engine_ptr;