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
    for (auto &entity : entities)
    {
        if (entity->is_deleted())
            continue;

        if (entity->contains_the_mouse(*this, mouse_position))
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
    return renderer.raster_to_world(mouse_position, *cameras[0]);
}

Point2f Engine::get_mouse_position_in_camera(Camera2D& camera)
{
    return renderer.raster_to_world(mouse_position, camera);
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
}

// Returns true if the program should quit
bool Engine::process_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_q)
            {
                return true;
            }

            auto IO_event = Engine::SDL_to_input_event(event.key);

            Engine::change_input_state(IO_event, true);
            Engine::send_event_down(IO_event);
        }

        if (event.type == SDL_KEYUP)
        {
            auto IO_event = Engine::SDL_to_input_event(event.key);

            Engine::change_input_state(IO_event, false);
            Engine::send_event_up(IO_event);
        }

        // Mouse
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            auto IO_event = Engine::SDL_to_input_event(event.button);
            Engine::change_input_state(IO_event, true);
            Engine::send_event_down(IO_event);
        }

        if (event.type == SDL_MOUSEBUTTONUP)
        {
            auto IO_event = Engine::SDL_to_input_event(event.button);
            Engine::change_input_state(IO_event, false);
            Engine::send_event_up(IO_event);
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
    std::cout << "delta: " << delta_time << '\n';
}

void Engine::compute_physics()
{
    // Send pre-physics event to all entities
    physics.pre_physics(*this);

    for (auto& camera : cameras)
        camera->update_position(*this);
    physics.update_positions(*this);
    physics.compute_collisions(*this);

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
    }
}

Engine::Engine(std::shared_ptr<Game> &&game)
    : game{std::move(game)}
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw error::sdl_exception(ERROR_CONTEXT);

    cameras.push_back(this->game->get_main_camera());
    check_point = std::chrono::steady_clock::now();
    auto [w, h] = cameras[0]->get_window_frame().diagonal();
    renderer = Render_2D(this->game->get_name(), (int)w, (int)h);

    physics = Physics_engine();
}

Engine::Engine(Game *game)
    : Engine{std::shared_ptr<Game>(game)}
{

}

Game &Engine::get_game()
{
    return *game;
}

// Intersect a ray with all entities in the engine
// If check_z_axis is true, only entities with a z coordinate == than the
//  ray's intersection point will be considered
//  (If the ray does not move on z axis, then only entities with
//  z == than ray's origin will be considered)
bool Engine::intesect_ray(Ray &ray, bool check_z_axis, Float &hit_offset, EntityPtr &hit_entity)
{
    hit_offset = INFINITY;

    for (auto &entity : entities)
    {
        if (entity->is_deleted())
            continue;

        auto bounding_box = entity->bound2f();
        Float offset;

        if (bounding_box.intersects(ray, offset) && (offset < hit_offset) && (!check_z_axis || (entity->get_position3D().z == ray(offset).z)))
        {
            hit_entity = entity;
            hit_offset = offset;
        }
    }

    return hit_offset < INFINITY;
}

bool Engine::intesect_ray(Ray &ray,
                          bool check_z_axis,
                          int not_this_entity_id,
                          const std::string &force_class_name,
                          Float &hit_offset,
                          EntityPtr &hit_entity)
{
    hit_offset = INFINITY;

    for (auto &entity : entities)
    {
        if (entity->is_deleted() || entity->get_entity_id() == not_this_entity_id)
            continue;

        auto bounding_box = entity->bound2f();
        Float offset;

        if (bounding_box.intersects(ray, offset) && (offset < hit_offset) && (entity->get_class() == force_class_name) && (!check_z_axis || (entity->get_position3D().z == ray(offset).z)))
        {
            hit_entity = entity;
            hit_offset = offset;
        }
    }

    return hit_offset < INFINITY;
}

void Engine::start()
{
    cameras.push_back(game->get_main_camera());
    game->on_game_startup(*this);

    bool quit = false;
    while (!quit && !quit_event)
    {
        update_delta_time();
        update_mouse_position();

        game->on_loop_start(*this);
        quit = process_events();

        // Update call to physics engine
        compute_physics();

        game->on_loop_end(*this);

        // Update entitie list
        process_new_entities();
        // Sort by z buffer, dead entities go to the end
        sort_by_z_buffer();
        // Delete old entities
        delete_dead_entities();

        // Draw call to renderer
        for (auto& camera : cameras)
            renderer.draw(entities, *camera);
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
