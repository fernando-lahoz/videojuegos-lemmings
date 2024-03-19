#pragma once

#include <memory>
#include <vector>
#include <queue>
#include <chrono>
#include <string>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <set>

#include "lib/texture.hpp"
#include "geometry/ray.hpp"
#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/game.hpp"
#include "engine/physics.hpp"
#include "engine/sound_mixer.hpp"
#include "IO.hpp"

class Engine
{ 
public:
    using TimePoint = std::chrono::time_point<std::chrono::steady_clock,
                                              std::chrono::nanoseconds>;

    using EntityCollection = std::vector<std::shared_ptr<Entity>>;

    using CameraCollection = std::vector<std::shared_ptr<Camera2D>>;

private:
    void send_event_down(EngineIO::InputEvent key);
    void send_event_up(EngineIO::InputEvent key);
    bool process_events();
    void update_delta_time();
    void compute_physics();
    void sort_by_z_buffer();
    void delete_dead_entities();
    void process_new_entities();
    void process_cameras();
    void update_entities_state();

    void th_preload_textures(const std::vector<std::string>& paths, int batch_id);
    void send_preload_finished_event(int batch_id);
    void destroy_finished_preloaders();

    void send_mouse_hover();
    void update_mouse_position();
    void change_input_state(EngineIO::InputEvent key, bool is_down);
    void set_ignored_events();
    
    void set_collision_type(Entity* entity, Entity::Collision_type type);
    void erase_collision_type(Entity* entity, Entity::Collision_type type);

    EngineIO::InputEvent SDL_to_input_event(SDL_KeyboardEvent key);
    EngineIO::InputEvent SDL_to_input_event(SDL_MouseButtonEvent key);

    std::shared_ptr<Game> game;
    CameraCollection cameras;
    std::shared_ptr<Render_2D> renderer;
    Physics_engine physics;
    SoundMixer mixer;

    TimePoint check_point;
    uint64_t delta_ns = 0, total_delta_ns = 0, total_measurements = 1;
    double delta_time; // Delta time in seconds

    int preload_id = 0;
    std::mutex preloaders_mutex;
    std::queue<std::thread> preload_threads;

    EntityCollection entities;

    std::set<Entity*> hud_entities;
    std::set<Entity*> structure_entities;
    std::set<Entity*> character_entities;
    std::unordered_set<Entity*> hovered_entities;
    std::vector<Entity*> event_entities;

    Point2f mouse_position;
    bool quit_event = false;
    

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
    void quit();

    Texture load_texture(const std::string& path);
    
    // Returns the id of the batch loading
    // The event will be sent with this id
    int preload_textures(const std::vector<std::string>& paths);

    void set_window_icon(const std::string& path);
    void set_fullscreen();
    EntityCollection& get_entities();
    double get_delta_time();
    void destroy_all_entities();
    Game& get_game();
    Camera2D& get_main_camera();
    SoundMixer& get_sound_mixer();
    SDL_Renderer *get_renderer();

    // Returns world position of mouse viewed by main camera
    Point2f get_mouse_position();
    // Returns world position of mouse viewed by camera
    Point2f get_mouse_position_in_camera(Camera2D& camera);
    
    void show_cursor();
    void hide_cursor();
    bool is_cursor_visible();

    bool is_entity_hovered(Entity& entity);
    void change_collision_type(Entity* entity, Entity::Collision_type new_type);
    void subscribe_to_events(Entity* entity);

    std::set<Entity*>& get_hud_entities();
    std::set<Entity*>& get_structure_entities();
    std::set<Entity*>& get_character_entities();

    /*
    bool intesect_ray(Ray &ray, 
            bool check_z_axis,
            Float &hit_offset, 
            EntityPtr &hit_entity);
    */

    // Intersect a ray with all entities in the engine
    //  except for the entity with name not_this_entity
    // If check_z_axis is true, only entities with a z coordinate == than the
    //  ray's intersection point will be considered 
    //  (If the ray does not move on z axis, then only entities with 
    //  z == than ray's origin will be considered)
    // Class name specifies a class of entity wanted for the intersection
    bool intersect_ray(Ray &ray, 
            int not_this_entity_id,
            const std::string &force_entity_name,
            Float &hit_offset,
            EntityPtr &hit_entity);
    
    bool intersect_ray(Ray &ray, 
            int not_this_entity_id,
            const std::vector<std::string> &force_entity_names,
            Float &hit_offset,
            EntityPtr &hit_entity);

    /*
    bool intesect_ray_entity(Ray &ray, 
            EntityPtr entity,
            Float &hit_offset1, 
            Float &hit_offset2);
    */
            
    bool ray_march_alpha_init(Ray &ray, Float &offset, 
                            Float min_offset, 
                            Float max_offset, 
                            EntityPtr entity) const;

    bool ray_march_alpha_end(Ray &ray, Float &offset, 
                            Float min_offset, 
                            Float max_offset, 
                            EntityPtr entity) const;

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
