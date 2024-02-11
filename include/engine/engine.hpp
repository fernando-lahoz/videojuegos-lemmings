#pragma once

#include <memory>
#include <vector>
#include <chrono>
#include <string>

#include "lib/texture.hpp"
#include "geometry/ray.hpp"
#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/game.hpp"
#include "engine/physics.hpp"
#include "IO.hpp"

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
    void change_input_state(SDL_KeyboardEvent key, bool is_down);
    EngineIO::InputEvent SDL_to_input_event(SDL_KeyboardEvent key);

    std::shared_ptr<Game> game;
    std::shared_ptr<Camera2D> camera;
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

    long long input_state = 0;

    /**
     * Creates a game engine while adquiring ownership of the object.
     * 
     * @param game Game object pointer. Must be allocated on the heap.
     * 
     * @throws `std::runtime_error`, if it fails to initialize internal systems.
     */
    Engine(Game* game);
    Engine(std::shared_ptr<Game>&& game);

    void start();

    Texture load_texture(const std::string& path);
    EntityCollection& get_entities();
    double get_delta_time();
    void destroy_all_entities();
    std::shared_ptr<Game> get_game();
    


    bool intesect_ray(Ray &ray, 
            bool check_z_axis,
            Float &hit_offset, 
            EntityPtr &hit_entity);

    // Intersect a ray with all entities in the engine
    //  except for the entity with name not_this_entity
    // If check_z_axis is true, only entities with a z coordinate == than the
    //  ray's intersection point will be considered 
    //  (If the ray does not move on z axis, then only entities with 
    //  z == than ray's origin will be considered)
    // Class name specifies a class of entity wanted for the intersection
    bool intesect_ray(Ray &ray, 
            bool check_z_axis,
            int not_this_entity_id,
            const std::string &force_class_name,
            Float &hit_offset, 
            EntityPtr &hit_entity);


    /********************** Input events **********************/

    bool is_key_down(EngineIO::InputEvent key) const;
    bool is_key_up(EngineIO::InputEvent key) const;
    bool any_key_down() const;
    long long get_all_keys_down() const;
    
    bool is_left_arrow_down() const;
    bool is_right_arrow_down() const;
    bool is_up_arrow_down() const;
    bool is_down_arrow_down() const;

    bool is_w_down() const;
    bool is_a_down() const;
    bool is_s_down() const;
    bool is_d_down() const;

    bool is_space_down() const;
    bool is_shift_down() const;
    bool is_ctrl_down() const;
    bool is_alt_down() const;

    bool is_enter_down() const;
    bool is_esc_down() const;
    bool is_tab_down() const;
    bool is_backspace_down() const;

};
