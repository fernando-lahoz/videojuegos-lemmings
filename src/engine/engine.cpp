#include <vector>
#include <chrono>

#include <SDL2/SDL.h>

#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/physics.hpp"
#include "engine/game.hpp"
#include "engine/engine.hpp"
#include "engine/IO.hpp"
#include "lib/error.hpp"

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libavutil/avutil.h>
#include <libswscale/swscale.h>
}

EngineIO::InputEvent Engine::SDL_to_input_event(SDL_KeyboardEvent key)
{
    switch (key.keysym.sym)
    {
    case SDLK_RIGHT:
        return EngineIO::InputEvent::RIGHT_ARROW;
    case SDLK_LEFT:
        return EngineIO::InputEvent::LEFT_ARROW;
    case SDLK_UP:
        return EngineIO::InputEvent::UP_ARROW;
    case SDLK_DOWN:
        return EngineIO::InputEvent::DOWN_ARROW;
    case SDLK_w:
        return EngineIO::InputEvent::W;
    case SDLK_a:
        return EngineIO::InputEvent::A;
    case SDLK_s:
        return EngineIO::InputEvent::S;
    case SDLK_d:
        return EngineIO::InputEvent::D;
    case SDLK_SPACE:
        return EngineIO::InputEvent::SPACE;
    case SDLK_LSHIFT:
        return EngineIO::InputEvent::SHIFT;
    case SDLK_LCTRL:
        return EngineIO::InputEvent::CTRL;
    case SDLK_LALT:
        return EngineIO::InputEvent::ALT;
    case SDLK_RETURN:
        return EngineIO::InputEvent::ENTER;
    case SDLK_ESCAPE:
        return EngineIO::InputEvent::ESC;
    case SDLK_TAB:
        return EngineIO::InputEvent::TAB;
    case SDLK_BACKSPACE:
        return EngineIO::InputEvent::BACKSPACE;
    default:
        return EngineIO::InputEvent::NONE;
    }
}

EngineIO::InputEvent Engine::SDL_to_input_event(SDL_MouseButtonEvent button)
{
    switch (button.button)
    {
    case SDL_BUTTON_LEFT:
        return EngineIO::InputEvent::MOUSE_LEFT;
    case SDL_BUTTON_RIGHT:
        return EngineIO::InputEvent::MOUSE_RIGHT;
    case SDL_BUTTON_MIDDLE:
        return EngineIO::InputEvent::MOUSE_MIDDLE;
    default:
        return EngineIO::InputEvent::NONE;
    }
}

void Engine::send_mouse_hover()
{
    for (auto& entity : entities)
    {
        if (entity->is_deleted())
            continue;

        if (hovered_entities.contains(entity.get()))
        {
            entity->enable_mouse_hover();
            entity->on_event_down(*this, EngineIO::InputEvent::MOUSE_HOVER);
        }
        else if (entity->mouse_was_hovering())
        {
            entity->disable_mouse_hover();
            entity->on_event_up(*this, EngineIO::InputEvent::MOUSE_HOVER);
        }
    }
}

void Engine::send_event_down(EngineIO::InputEvent event)
{
    game->on_event_down(*this, event);
    for (auto& camera : cameras)
        camera->on_event_down(*this, event);

    for (auto &entity : entities)
    {
        if (!entity->is_deleted())
            entity->on_event_down(*this, event);
    }
}

void Engine::send_event_up(EngineIO::InputEvent event)
{
    game->on_event_up(*this, event);
    for (auto& camera : cameras)
        camera->on_event_up(*this, event);

    for (auto &entity : entities)
    {
        if (!entity->is_deleted())
            entity->on_event_up(*this, event);
    }
}

void Engine::change_input_state(EngineIO::InputEvent event, bool is_down)
{
    if (is_down)
        input_state |= event;
    else
        input_state &= ~event;
}

void Engine::update_mouse_position()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouse_position.x = (Float) x;
    mouse_position.y = (Float) y;
}

Point2f Engine::get_mouse_position()
{
    auto& main_camera = *cameras[0];
    return renderer.raster_to_world(mouse_position, main_camera, main_camera);
}

Point2f Engine::get_mouse_position_in_camera(Camera2D& camera)
{
    return renderer.raster_to_world(mouse_position, camera, *cameras[0]);
}

void Engine::show_cursor()
{
    SDL_ShowCursor(SDL_ENABLE);
}

void Engine::hide_cursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

bool Engine::is_cursor_visible()
{
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    //return renderer.frame.contains(mouse_position);
}

bool Engine::is_entity_hovered(const Entity& entity)
{
    return hovered_entities.contains(&entity);
}

SDL_Renderer* Engine::get_renderer()
{
    return renderer.get_sdl_renderer();
}

bool Engine::ray_march_alpha_init(Ray &ray, Float &offset, 
        Float min_offset,
        Float max_offset, 
        EntityPtr entity) const
{
    Float search_distance = max_offset - min_offset;

    int n_samples = 100;
    Float step_size = search_distance / n_samples;

    for (int i = 0; i < n_samples; i++)
    {
        Float t = min_offset + step_size*i;
        Point3f p3 = ray(t);
        Point2f p = Point2f(p3.x, p3.y);

        if (entity->contains(p))
        {
            offset = t;
            return true;
        }
    }

    return false;
}


bool Engine::ray_march_alpha_end(Ray &ray, Float &offset, 
        Float min_offset,
        Float max_offset, 
        EntityPtr entity) const
{
    Float search_distance = max_offset - min_offset;

    int n_samples = 100;
    Float step_size = search_distance / n_samples;

    for (int i = 0; i < n_samples; i++)
    {
        Float t = max_offset - step_size*i;
        Point3f p3 = ray(t);
        Point2f p = Point2f(p3.x, p3.y);

        if (entity->contains(p))
        {
            offset = t;
            return true;
        }
    }

    return false;
}



// Returns true if the program should quit
bool Engine::process_events()
{
    static bool pressedf11 = false;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
        case SDL_KEYDOWN:
        {
            auto IO_event = Engine::SDL_to_input_event(event.key);

            Engine::change_input_state(IO_event, true);
            Engine::send_event_down(IO_event);

            if (event.key.keysym.sym == SDLK_F11 && !pressedf11) {
                static bool toggle = true;
                if (toggle) set_fullscreen();
                else renderer.set_windowmode();
                toggle = !toggle;
                pressedf11 = true;
            }
                
            
        }
        break;
        case SDL_KEYUP:
        {
            if (event.key.keysym.sym == SDLK_F11 && pressedf11) {  pressedf11 = false; }
            auto IO_event = Engine::SDL_to_input_event(event.key);

            Engine::change_input_state(IO_event, false);
            Engine::send_event_up(IO_event);
        }
        break;
        //Mouse
        case SDL_MOUSEBUTTONDOWN:
        {
            auto IO_event = Engine::SDL_to_input_event(event.button);
            Engine::change_input_state(IO_event, true);
            Engine::send_event_down(IO_event);
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            auto IO_event = Engine::SDL_to_input_event(event.button);
            Engine::change_input_state(IO_event, false);
            Engine::send_event_up(IO_event);
        }
        break;
        }
    }
    
    send_mouse_hover();

    return false;
}

// Returns delta time in seconds
void Engine::update_delta_time()
{
    TimePoint new_check_point = std::chrono::steady_clock::now();

    uint64_t new_delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
                             new_check_point - check_point)
                             .count();

    check_point = new_check_point;

    if (total_delta_ns > 0 && new_delta > 4 * total_delta_ns / total_measurements)
    {
        // Invalid delta time (game freezed) -> replace by mean delta time
        delta_ns = total_delta_ns / total_measurements;
    }
    else if ((total_measurements & 0xFFFF) == 0)
    {
        // Mean delta time can grow over time, so we reset after some thousand
        // measurements to the last valid delta time
        delta_ns = new_delta;
        total_delta_ns = new_delta;
        total_measurements = 1;
    }
    else
    {
        delta_ns = new_delta;
        total_delta_ns += new_delta;
        total_measurements++;
    }

    delta_time = (double)delta_ns / 1e9;
}

void Engine::compute_physics()
{
    // Send pre-physics event to all entities
    physics.pre_physics(*this);

    physics.compute_collisions(*this);

    for (auto& camera : cameras)
        camera->update_position(*this);
    physics.update_positions(*this);

    // Send post-physics event to all entities
    physics.post_physics(*this);
}

// Sorts the drawables in descending z order.
//  Dead entities are moved to the end of the list.
void Engine::sort_by_z_buffer()
{
    std::sort(entities.begin(), entities.end(), [](EntityPtr a, EntityPtr b) -> bool
              { return !a->is_deleted() && ((b->is_deleted()) ||
                                            (a->get_position3D().z > b->get_position3D().z)); });
}

// Removes all entities with a deleted flag, assuming an ordered vector with
//  all dead entities at the end
void Engine::delete_dead_entities()
{
    auto is_deleted = [](EntityPtr entity)
    { return entity->is_deleted(); };
    auto iterator = std::find_if(entities.begin(), entities.end(), is_deleted);


    std::for_each(iterator, entities.end(), [this](EntityPtr entity)
                  { game->on_entity_destruction(*this, entity); });

    entities.resize(std::distance(entities.begin(), iterator));
}

void Engine::process_new_entities()
{
    auto new_entities = game->get_new_entities();

    for (auto &entity : new_entities)
    {
        entity->set_entity_id(entities.size());
        entities.push_back(entity);

        entity->on_creation(*this);
    }
}

void Engine::process_cameras()
{
    auto new_cameras = game->get_new_cameras();

    if (game->replace_main_cam) {
        cameras[0] = new_cameras[0];
        for (auto cam_it = new_cameras.begin() + 1; cam_it != new_cameras.end(); ++cam_it)
            cameras.push_back(*cam_it);
    }
    else {
        for (auto &camera : new_cameras)
            cameras.push_back(camera);
    }

    std::sort(cameras.begin() + 1, cameras.end(), [](std::shared_ptr<Camera2D> a, std::shared_ptr<Camera2D> b) -> bool
              { return !a->is_deleted() && ((b->is_deleted()) ||
                                            (a->get_layer() > b->get_layer())); });
            
    auto is_deleted = [](std::shared_ptr<Camera2D> camera) { return camera->is_deleted(); };
    auto iterator = std::find_if(cameras.begin(), cameras.end(), is_deleted);
    cameras.resize(std::distance(cameras.begin(), iterator));
}

Engine::Engine(std::shared_ptr<Game> &&game)
    : game{std::move(game)}
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw error::sdl_exception(ERROR_CONTEXT);

    cameras.push_back(this->game->get_main_camera());
    auto [w, h] = cameras[0]->get_window_frame().diagonal();
    renderer = Render_2D(this->game->get_name(), (int)w, (int)h);
    physics = Physics_engine();

    check_point = std::chrono::steady_clock::now();
}

Engine::Engine(Game *game)
    : Engine{std::shared_ptr<Game>(game)}
{

}

Game &Engine::get_game()
{
    return *game;
}

Camera2D& Engine::get_main_camera()
{
    return *cameras[0];
}

SoundMixer& Engine::get_sound_mixer()
{
    return mixer;
}

void Engine::change_collision_type(int entity_id, Entity::Collision_type type)
{
    auto old_type = entities[entity_id]->get_collision_type();

    // Erase from the old entities set
    if (old_type == Entity::Collision_type::CHARACTER)
    {
        character_entities.erase(entity_id);
    }
    else if (old_type == Entity::Collision_type::STRUCTURE)
    {
        structure_entities.erase(entity_id);
    }
    else if (old_type == Entity::Collision_type::HUD)
    {
        hud_entities.erase(entity_id);
    }

    // Insert into the new entities set
    if (type == Entity::Collision_type::CHARACTER)
    {
        character_entities.insert(entity_id);
    }
    else if (type == Entity::Collision_type::STRUCTURE)
    {
        structure_entities.insert(entity_id);
    }
    else if (type == Entity::Collision_type::HUD)
    {
        hud_entities.insert(entity_id);
    }
}

std::unordered_set<int>& Engine::get_character_entities()
{
    return character_entities;
}

std::unordered_set<int>& Engine::get_structure_entities()
{
    return structure_entities;
}

std::unordered_set<int>& Engine::get_hud_entities()
{
    return hud_entities;
}



bool Engine::intersect_ray(Ray &ray, 
            int not_this_entity_id,
            const std::string &force_entity_name,
            Float &hit_offset, 
            EntityPtr &hit_entity)
{
    hit_offset = INFINITY;

    for (auto &entity : entities)
    {
        if (entity->get_entity_id() == not_this_entity_id
            || entity->get_entity_name() != force_entity_name)
        {
            continue;
        }

        auto bounding_box = entity->bound2f();
        Float offset, min_offset, max_offset;
        Point2f origin;
        bool intersects = false;
        origin.x = ray.origin.x;
        origin.y = ray.origin.y;

        intersects = bounding_box.all_intersections(ray, min_offset, max_offset);

        if (min_offset > 0)
            offset = min_offset;
        else
            offset = max_offset;

        if (bounding_box.contains(origin)) 
        {
            offset = 0;
            intersects = true;
        }

        if (intersects)
        {
            intersects = ray_march_alpha_init(ray, offset, offset, max_offset, entity);

            if (intersects && offset < hit_offset)
            {
                hit_offset = offset;
                hit_entity = entity;
            }
        }
    }

    return hit_offset < INFINITY;
}


void Engine::set_ignored_events()
{
    static constexpr uint32_t ignored_events[] = {
        SDL_AUDIODEVICEADDED,
        SDL_AUDIODEVICEREMOVED,
        SDL_CONTROLLERAXISMOTION,
        SDL_CONTROLLERBUTTONDOWN,
        SDL_CONTROLLERBUTTONUP,
        SDL_CONTROLLERDEVICEADDED,
        SDL_CONTROLLERDEVICEREMOVED,
        SDL_CONTROLLERDEVICEREMAPPED,
        SDL_DOLLARGESTURE,
        SDL_DOLLARRECORD,
        SDL_DROPFILE,
        SDL_DROPTEXT,
        SDL_DROPBEGIN,
        SDL_DROPCOMPLETE,
        SDL_FINGERMOTION,
        SDL_FINGERDOWN,
        SDL_FINGERUP,
        //SDL_KEYDOWN,
        //SDL_KEYUP,
        SDL_JOYAXISMOTION,
        SDL_JOYBALLMOTION,
        SDL_JOYHATMOTION,
        SDL_JOYBUTTONDOWN,
        SDL_JOYBUTTONUP,
        SDL_JOYDEVICEADDED,
        SDL_JOYDEVICEREMOVED,
        SDL_MOUSEMOTION,
        //SDL_MOUSEBUTTONDOWN,
        //SDL_MOUSEBUTTONUP,
        SDL_MOUSEBUTTONUP,
        SDL_MULTIGESTURE,
        //SDL_QUIT,
        SDL_SYSWMEVENT,
        SDL_TEXTEDITING,
        SDL_TEXTINPUT,
        SDL_USEREVENT,
        //SDL_WINDOWEVENT
    };

    for (auto event : ignored_events)
        SDL_EventState(event, SDL_IGNORE);
}


void Engine::start()
{
    set_ignored_events();

    game->on_game_startup(*this);

    bool quit = false;
    while (!quit && !quit_event)
    {
        auto init = std::chrono::steady_clock::now();
        update_delta_time();
        renderer.update_resolution(*this);
        update_mouse_position();

        game->on_loop_start(*this);
        quit = process_events();

        // Update call to physics engine
        compute_physics();

        // Update entitie list
        process_new_entities();
        // Sort by z buffer, dead entities go to the end
        sort_by_z_buffer();
        // Delete old entities
        delete_dead_entities();

        game->on_loop_end(*this);

        process_cameras();

        auto end = std::chrono::steady_clock::now();

        std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - init).count() << "us\n";

        // Draw call to renderer
        hovered_entities = renderer.draw_and_return_hovered(entities, cameras, mouse_position);
    }

    game->on_game_shutdown(*this);

    SDL_Quit();
}

void Engine::quit()
{
    quit_event = true;
}

Engine::EntityCollection &Engine::get_entities()
{
    return entities;
}

Texture Engine::load_texture(const std::string &path)
{
    return renderer.load_texture(path);
}

void Engine::set_window_icon(const std::string& path)
{
    renderer.set_window_icon(path);
}

void Engine::set_fullscreen()
{
    renderer.set_fullscreen();
}

double Engine::get_delta_time()
{
    return delta_time;
}

void Engine::destroy_all_entities()
{
    for (auto &entity : entities)
    {
        entity->destroy();
    }
}

/********************** Input events **********************/

bool Engine::is_key_down(EngineIO::InputEvent key) const
{
    return input_state & key;
}

bool Engine::is_key_up(EngineIO::InputEvent key) const
{
    return !(input_state & key);
}

bool Engine::any_key_down() const
{
    return input_state != 0;
}

long long Engine::get_all_keys_down() const
{
    return input_state;
}

bool Engine::is_left_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::LEFT_ARROW);
}

bool Engine::is_right_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::RIGHT_ARROW);
}

bool Engine::is_up_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::UP_ARROW);
}

bool Engine::is_down_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::DOWN_ARROW);
}

bool Engine::is_w_down() const
{
    return is_key_down(EngineIO::InputEvent::W);
}

bool Engine::is_a_down() const
{
    return is_key_down(EngineIO::InputEvent::A);
}

bool Engine::is_s_down() const
{
    return is_key_down(EngineIO::InputEvent::S);
}

bool Engine::is_d_down() const
{
    return is_key_down(EngineIO::InputEvent::D);
}

bool Engine::is_space_down() const
{
    return is_key_down(EngineIO::InputEvent::SPACE);
}

bool Engine::is_shift_down() const
{
    return is_key_down(EngineIO::InputEvent::SHIFT);
}

bool Engine::is_ctrl_down() const
{
    return is_key_down(EngineIO::InputEvent::CTRL);
}

bool Engine::is_alt_down() const
{
    return is_key_down(EngineIO::InputEvent::ALT);
}

bool Engine::is_enter_down() const
{
    return is_key_down(EngineIO::InputEvent::ENTER);
}

bool Engine::is_esc_down() const
{
    return is_key_down(EngineIO::InputEvent::ESC);
}

bool Engine::is_backspace_down() const
{
    return is_key_down(EngineIO::InputEvent::BACKSPACE);
}

bool Engine::is_tab_down() const
{
    return is_key_down(EngineIO::InputEvent::TAB);
}
