#pragma once

#include <memory>
#include <vector>
#include <chrono>
#include <string>

#include "lib/texture.hpp"
#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/game.hpp"
#include "engine/physics.hpp"

class Engine
{
private:
    void send_key_down_event(SDL_KeyboardEvent key);
    void send_key_up_event(SDL_KeyboardEvent key);
    bool process_events();
    void update_delta_time();
    void compute_physics();
    void sort_by_z_buffer();
    void delete_dead_entities();
    void process_new_entities();

    std::unique_ptr<Game> game;
    std::unique_ptr<Camera2D> camera;
    Render_2D renderer;
    Physics_engine physics;

    using TimePoint = std::chrono::time_point<std::chrono::steady_clock,
                                              std::chrono::nanoseconds>;
    TimePoint check_point;
    uint64_t delta_ns = 0, total_delta_ns = 0, total_measurements = 1;
    double delta_time; // Delta time in seconds

    using EntityCollection = std::vector<std::shared_ptr<Entity>>;
    EntityCollection entities;

public:

    /**
     * Creates a game engine while adquiring ownership of the object.
     * 
     * @param game Game object pointer. Must be allocated on the heap.
     * 
     * @throws `std::runtime_error`, if it fails to initialize internal systems.
     */
    Engine(Game* game);
    Engine(std::unique_ptr<Game>&& game);

    void start();

    Texture load_texture(const std::string& path);
    EntityCollection& get_entities();
    double get_delta_time();
};
