#include <vector>
#include <chrono>
#include <set>
#include <unordered_set>

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
    /*
    // Para mostrar por consola la tecla que se ha pulsado.
    std::cout << "Key pressed: " << key.keysym.sym << std::endl;
    */
    if (key.keysym.sym >= SDLK_a && key.keysym.sym <= SDLK_z)
        return (EngineIO::InputEvent)(key.keysym.sym - SDLK_a + 65);

    if (key.keysym.sym >= SDLK_SPACE && key.keysym.sym < 256)
        return (EngineIO::InputEvent)(key.keysym.sym);

    if (key.keysym.sym >= SDLK_F1 && key.keysym.sym <= SDLK_F12)
        return (EngineIO::InputEvent)(key.keysym.sym - SDLK_F1 + 256);

    if (key.keysym.sym >= SDLK_NUMLOCKCLEAR && key.keysym.sym <= SDLK_KP_PERIOD)
        return (EngineIO::InputEvent)(key.keysym.sym - SDLK_NUMLOCKCLEAR + 268);

    switch (key.keysym.sym)
    {
    case SDLK_RIGHT:
        return EngineIO::InputEvent::RIGHT;
    case SDLK_LEFT:
        return EngineIO::InputEvent::LEFT;
    case SDLK_UP:
        return EngineIO::InputEvent::UP;
    case SDLK_DOWN:
        return EngineIO::InputEvent::DOWN;
    case SDLK_SPACE:
        return EngineIO::InputEvent::SPACE;
    case SDLK_LSHIFT:
        return EngineIO::InputEvent::SHIFT;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
        return EngineIO::InputEvent::CTRL;
    case SDLK_LALT:
    case SDLK_RALT:
        return EngineIO::InputEvent::ALT;
    case SDLK_RETURN:
        return EngineIO::InputEvent::ENTER;
    case SDLK_ESCAPE:
        return EngineIO::InputEvent::ESC;
    case SDLK_TAB:
        return EngineIO::InputEvent::TAB;
    case SDLK_BACKSPACE:
        return EngineIO::InputEvent::BACKSPACE;
    case SDLK_CAPSLOCK:
        return EngineIO::InputEvent::CAPS_LOCK;
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
    for (auto &entity : event_entities)
    {
        if (entity->is_deleted())
            continue;

        const auto it = hovered_entities.find(entity);
        if (it != hovered_entities.end())
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
    for (auto &camera : cameras)
        camera->on_event_down(*this, event);
    std::cout << event_entities.size() << std::endl;

    for (auto &entity : event_entities)
    {
        if (!entity->is_deleted())
            entity->on_event_down(*this, event);
    }
}

void Engine::send_event_up(EngineIO::InputEvent event)
{
    game->on_event_up(*this, event);
    for (auto &camera : cameras)
        camera->on_event_up(*this, event);

    for (auto &entity : event_entities)
    {
        if (!entity->is_deleted())
            entity->on_event_up(*this, event);
    }
}

void Engine::change_input_state(EngineIO::InputEvent event, bool is_down)
{
    if (is_down)
        input_state.insert(event); // input_state |= event;
    else
        input_state.erase(event); // input_state &= ~event;
}

void Engine::update_mouse_position()
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    mouse_position.x = (Float)x;
    mouse_position.y = (Float)y;
}

Point2f Engine::get_mouse_position()
{
    auto &main_camera = *cameras[0];
    return renderer->raster_to_world(mouse_position, main_camera, main_camera);
}

Point2f Engine::get_mouse_position_in_camera(Camera2D &camera)
{
    return renderer->raster_to_world(mouse_position, camera, *cameras[0]);
}

void Engine::show_cursor()
{
    SDL_ShowCursor(SDL_ENABLE);
}

void Engine::hide_cursor()
{
    SDL_ShowCursor(SDL_DISABLE);
}

void Engine::update_entities_state()
{
    for (auto &entity : entities)
    {
        if (!entity->is_deleted())
            entity->update_state(*this);
    }
}

void Engine::subscribe_to_events(Entity *entity)
{
    event_entities.insert(entity);
}

bool Engine::is_cursor_visible()
{
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
    // return renderer->frame.contains(mouse_position);
}

bool Engine::is_entity_hovered(Entity &entity) const
{
    return hovered_entities.find(&entity) != hovered_entities.end();
}

Camera2D::ID Engine::get_camera_in_which_hovered(Entity &entity) const
{
    const auto it = hovered_entities.find(&entity);
    return it != hovered_entities.end() ? it->second : -1;
}

SDL_Renderer *Engine::get_renderer()
{
    return renderer->get_sdl_renderer();
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
        Float t = min_offset + step_size * i;
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
        Float t = max_offset - step_size * i;
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

            /*
            // Omitted since the feature should be included in game settings and
            // the key could be used for other purposes.
            if (event.key.keysym.sym == SDLK_F11 && !pressedf11)
            {
                static bool toggle = true;
                if (toggle)
                    set_fullscreen();
                else
                    renderer->set_windowmode();
                toggle = !toggle;
                pressedf11 = true;
            }
            */
        }
        break;

        case SDL_KEYUP:
        {
            /*
            // Omitted since the feature should be included in game settings and
            // the key could be used for other purposes.
            if (event.key.keysym.sym == SDLK_F11 && pressedf11)
            {
                pressedf11 = false;
            }
            */

            auto IO_event = Engine::SDL_to_input_event(event.key);
            Engine::change_input_state(IO_event, false);
            Engine::send_event_up(IO_event);
        }
        break;
        // Mouse
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

    if (total_delta_ns > 0 && total_measurements > 100 &&
        new_delta > 4 * total_delta_ns / total_measurements)
    {
        // Invalid delta time (game freezed) -> replace by mean delta time
        delta_ns = total_delta_ns / total_measurements;
        delta_ns = 0;
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

    delta_time = (double)delta_ns / 1e9 * delta_time_factor;
}

void Engine::compute_physics()
{
    // Send pre-physics event to all entities
    physics.pre_physics(*this);

    physics.compute_collisions(*this);

    for (auto &camera : cameras)
        camera->update_position(*this);
    physics.update_positions(*this);

    update_entities_state();

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
                  { 
                    game->on_entity_destruction(*this, entity); 
                    erase_collision_type(entity.get(), entity->get_collision_type());
                    event_entities.erase(entity.get()); });

    entities.resize(std::distance(entities.begin(), iterator));
}

int Engine::last_entity_id = 0;

void Engine::process_new_entities()
{
    auto new_entities = game->get_new_entities();

    for (auto &entity : new_entities)
    {
        entity->set_entity_id(last_entity_id++);
        if (last_entity_id == std::numeric_limits<int>::max())
        {
            last_entity_id = 0;
        }
        entities.push_back(entity);
        entity->on_creation(*this);

        set_collision_type(entity.get(), entity->get_collision_type());
        subscribe_to_events(entity.get());
    }
}

void Engine::process_cameras()
{
    auto new_cameras = game->get_new_cameras();

    if (game->replace_main_cam)
    {
        cameras[0] = new_cameras[0];
        for (auto cam_it = new_cameras.begin() + 1; cam_it != new_cameras.end(); ++cam_it)
            cameras.push_back(*cam_it);
    }
    else
    {
        for (auto &camera : new_cameras)
            cameras.push_back(camera);
    }

    std::sort(cameras.begin() + 1, cameras.end(), [](std::shared_ptr<Camera2D> a, std::shared_ptr<Camera2D> b) -> bool
              { return !a->is_deleted() && ((b->is_deleted()) ||
                                            (a->get_layer() > b->get_layer())); });

    auto is_deleted = [](std::shared_ptr<Camera2D> camera)
    { return camera->is_deleted(); };
    auto iterator = std::find_if(cameras.begin(), cameras.end(), is_deleted);
    cameras.resize(std::distance(cameras.begin(), iterator));
}

Engine::Engine(std::shared_ptr<Game> &&game_)
    : game{std::move(game_)}
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw error::sdl_exception(ERROR_CONTEXT);

    cameras.push_back(this->game->get_main_camera());
    auto [cam_w, cam_h] = cameras[0]->get_window_frame().diagonal();

    auto [win_w, win_h] = game->get_initial_window_size();

    renderer = std::make_shared<Render_2D>(this->game->get_name(),
                                           win_w < 0 ? (int)cam_w : win_w, win_h < 0 ? (int)cam_h : win_h);
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

Camera2D &Engine::get_main_camera()
{
    return *cameras[0];
}

SoundMixer &Engine::get_sound_mixer()
{
    return mixer;
}

void Engine::set_collision_type(Entity *entity, Entity::Collision_type type)
{
    // Insert into the new entities set
    if (type == Entity::Collision_type::CHARACTER)
    {
        character_entities.insert(entity);
    }
    else if (type == Entity::Collision_type::STRUCTURE)
    {
        structure_entities.insert(entity);
    }
    else if (type == Entity::Collision_type::HUD)
    {
        hud_entities.insert(entity);
    }
}

void Engine::erase_collision_type(Entity *entity, Entity::Collision_type type)
{
    if (type == Entity::Collision_type::CHARACTER)
    {
        character_entities.erase(entity);
    }
    else if (type == Entity::Collision_type::STRUCTURE)
    {
        structure_entities.erase(entity);
    }
    else if (type == Entity::Collision_type::HUD)
    {
        hud_entities.erase(entity);
    }
}

void Engine::change_collision_type(Entity *entity, Entity::Collision_type new_type)
{
    erase_collision_type(entity, entity->get_collision_type());
    set_collision_type(entity, new_type);
}

std::set<Entity *> &Engine::get_character_entities()
{
    return character_entities;
}

std::set<Entity *> &Engine::get_structure_entities()
{
    return structure_entities;
}

std::set<Entity *> &Engine::get_hud_entities()
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
        if (entity->get_entity_id() == not_this_entity_id || entity->get_entity_name() != force_entity_name)
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

bool Engine::intersect_ray(Ray &ray,
                           int not_this_entity_id,
                           const std::vector<std::string> &force_entity_names,
                           Float &hit_offset,
                           EntityPtr &hit_entity)
{
    hit_offset = INFINITY;

    for (auto &entity : entities)
    {
        if (entity->get_entity_id() == not_this_entity_id)
        {
            continue;
        }
        bool continued = true;
        for (auto force_entity_name : force_entity_names)
        {
            if (entity->get_entity_name() == force_entity_name)
                continued = false;
        }
        if (continued)
            continue;

        auto bounding_box = entity->bound2f();
        Float offset, min_offset, max_offset = INFINITY;
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
            if (std::isnan(max_offset) || abs(max_offset) == INFINITY)
                max_offset = 0;
            if (std::isnan(min_offset))
                max_offset = 0;
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

bool Engine::alpha_box_collision_if_all_Y_force_entity_names(Bound2f box,
                                                             int not_this_entity_id,
                                                             const std::vector<std::string> &force_entity_names, bool& is_valid,
                                                             Point2f &max_collision_pixel, Physics_engine::ReturnedPixel horizontal_pixel,
                                                             Physics_engine::ReturnedPixel vertical_pixel,
                                                             EntityPtr &hit_entity)
{
    std::vector<std::pair<Float, Float>> mask;
    for (auto &entity : entities)
    {
        if (entity->get_entity_id() == not_this_entity_id)
            continue;

        bool continued = true;
        for (auto force_entity_name : force_entity_names)
        {
            if (entity->get_entity_name() == force_entity_name)
            {
                continued = false;
                break;
            }
        }
        if (continued)
            continue;

        if (!box.overlaps(entity->bound2f()))
            continue;

        std::vector<std::pair<Float, Float>> local_mask = Physics_engine::alpha_box_collision_get_height_mask(*entity, box);
        
        std::vector<std::pair<Float, Float>> new_mask;
        auto it1 = mask.begin();
        auto it2 = local_mask.begin();
        while (it1 != mask.end() && it2 != local_mask.end())
        {
            auto *upper = &it1;
            auto *lower = &it2;
            auto upper_end = mask.end();
            auto lower_end = local_mask.end();

            if (it1->first > it2->first)
            {
                std::swap(upper, lower);
                std::swap(upper_end, lower_end);
            }

            const auto [a, b] = **upper;
            const auto [A, B] = **lower;

            if (A > b) // No se tocan -> Avanzas upper
            {
                new_mask.push_back({a, b});
                ++(*upper);
            }
            else // Mezcla
            {
                auto *aux = (b < B) ? &++(*upper) : &++(*lower);
                auto aux_end = (b < B) ? upper_end : lower_end;
                auto *other = (b < B) ? &++(*lower) : &++(*upper);
                auto other_end = (b < B) ? lower_end : upper_end;
                auto b_max = std::max(b, B);
                
                while (*aux != aux_end && *other != other_end)
                {
                    const auto [c, d] = **aux;
                    if (c < b_max && d < b_max)
                    {
                        ++(*aux);
                    }
                    else if (c < b_max && d > b_max)
                    {
                        b_max = d;
                        std::swap(aux, other);
                        std::swap(aux_end, other_end);
                        ++(*aux);
                    }
                    else
                    {
                        ++(*other);
                        break;
                    }
                }
                new_mask.push_back({a, b_max});
            }
        }

        if (it1 == mask.end())
        {
            new_mask.insert( new_mask.end(), it2, local_mask.end() );
        }
        else if (it2 == local_mask.end())
        {
            new_mask.insert( new_mask.end(), it1, mask.end() );
        }

        mask.swap(new_mask);
    }
    
    is_valid = !mask.empty();


    if (is_valid && vertical_pixel == Physics_engine::GET_FIRST)
    {
        max_collision_pixel = {box.pMin.x, mask.front().first};
    }
    else if (is_valid && vertical_pixel == Physics_engine::GET_LAST)
    {
        if (mask.back().second < box.pMax.y) {
            max_collision_pixel = {box.pMin.x, box.pMax.y};
        } else {
            max_collision_pixel = {box.pMin.x, mask.back().first};
        }
        
        //std::cout << "max_collision_pixel: "<< max_collision_pixel << "\n";
    }

    // std::cout << "MASK: [ ";
    // for (auto p : mask)
    //     std::cout << "{"<< p.first << " , " << p.second << "} ";
    // std::cout << "]\n"; 

    // std::cout << "box: "<< box.pMin.y << " , " << box.pMax.y << "\n";

    return mask.size() == 1 && mask.front().first <= box.pMin.y && mask.back().second >= box.pMax.y;
}

void Engine::set_ignored_events()
{
    static constexpr uint32_t ignored_events[] = {
        // SDL_AUDIODEVICEADDED,
        // SDL_AUDIODEVICEREMOVED,
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
        // SDL_KEYDOWN,
        // SDL_KEYUP,
        SDL_JOYAXISMOTION,
        SDL_JOYBALLMOTION,
        SDL_JOYHATMOTION,
        SDL_JOYBUTTONDOWN,
        SDL_JOYBUTTONUP,
        SDL_JOYDEVICEADDED,
        SDL_JOYDEVICEREMOVED,
        SDL_MOUSEMOTION,
        // SDL_MOUSEBUTTONDOWN,
        // SDL_MOUSEBUTTONUP,
        SDL_MULTIGESTURE,
        // SDL_QUIT,
        SDL_SYSWMEVENT,
        SDL_TEXTEDITING,
        SDL_TEXTINPUT,
        SDL_USEREVENT,
        // SDL_WINDOWEVENT
    };

    for (auto event : ignored_events)
        SDL_EventState(event, SDL_IGNORE);
}

void Engine::start()
{
    end = false;
    int watchdog_counter = -1;
    bool watchdog_jumped = false;

    watchdog = std::thread{[&]()
                           {
                               std::printf("Im ON...\n");
                               using namespace std::chrono_literals;
                               using namespace std::chrono;

                               int x = 0;
                               auto time_point = steady_clock::now();
                               while (!end)
                               {
                                   std::this_thread::sleep_until(time_point + 1ms);
                                   time_point += 1ms;

                                   {
                                       std::lock_guard<std::mutex> lock{mtx};
                                       x = watchdog_counter--;
                                       switch (x)
                                       {
                                       case 0:
                                           watchdog_jumped = true;
                                           break;
                                       case -1:
                                           watchdog_counter = -1;
                                           break;
                                       }
                                   }

                                   // std::printf("...%d\n", x);
                                   switch (x)
                                   {
                                   case 0:
                                       // std::printf("Blocked...\n");
                                       mixer.block_sound();
                                       break;
                                   case -1:
                                       break;
                                       // default:
                                       // std::printf("...%d\n", x);
                                   }
                               }
                           }};

    set_ignored_events();

    game->on_game_startup(*this);

    bool quit = false;
    while (!quit && !quit_event)
    {
        // auto init = std::chrono::steady_clock::now();
        update_delta_time();
        renderer->update_resolution(*this);
        update_mouse_position();

        game->on_loop_start(*this);

        {
            std::lock_guard<std::mutex> lock{mtx};
            watchdog_counter = (total_delta_ns / total_measurements) / 1'000'000; /*ns -> ms*/
        }

        quit = process_events();

        bool local_jumped;
        {
            std::lock_guard<std::mutex> lock{mtx};
            watchdog_counter = -1; // cancel
            local_jumped = watchdog_jumped;
            watchdog_jumped = false;
        }
        if (local_jumped)
        {
            // std::printf("Resumed...\n");
            mixer.release_sound();
        }

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

        // auto end = std::chrono::steady_clock::now();

        // std::cout << "Executed in " << std::chrono::duration_cast<std::chrono::microseconds>(end - init).count() << "us\n";

        // Draw call to renderer
        hovered_entities = renderer->draw_and_return_hovered(entities, cameras, mouse_position);

        destroy_finished_preloaders();
    }

    game->on_game_shutdown(*this);

    end = true;
    watchdog.join();

    SDL_Quit();
}

Engine::~Engine()
{
    end = true;
    if (watchdog.joinable())
        watchdog.join();
}

void Engine::quit()
{
    quit_event = true;
}

Engine::EntityCollection &Engine::get_entities()
{
    return entities;
}

Texture Engine::load_texture(const std::string &path, bool cache)
{
    return renderer->load_texture(path, cache);
}

void Engine::flush_texture_cache()
{
    renderer->flush_texture_cache();
}

void Engine::send_preload_finished_event(int batch_id)
{
    game->on_preload_finished(*this, batch_id);
}

void Engine::th_preload_textures(const std::vector<std::string> &paths, int batch_id)
{
    for (auto &path : paths)
    {
        renderer->load_texture(path, true);
    }

    send_preload_finished_event(batch_id);
}

void Engine::destroy_finished_preloaders()
{
    std::unique_lock<std::mutex> lock(preloaders_mutex);

    if (preload_threads.empty())
        return;

    while (preload_threads.front().joinable())
    {
        preload_threads.front().join();
        preload_threads.pop();
    }
}

int Engine::preload_textures(const std::vector<std::string> &paths)
{
    std::unique_lock<std::mutex> lock(preloaders_mutex);

    int id = preload_id;

    // Launch thread
    preload_threads.push(std::thread(&Engine::th_preload_textures, this, paths, id));

    preload_id++;

    return id;
}

void Engine::show_window()
{
    renderer->show_window();
}

void Engine::set_window_icon(const std::string &path)
{
    renderer->set_window_icon(path);
}

void Engine::set_fullscreen()
{
    renderer->set_fullscreen();
}

void Engine::set_windowmode()
{
    renderer->set_windowmode();
}

void Engine::set_window_size(Vector2i size)
{
    renderer->set_window_size(size);
}

Vector2i Engine::get_window_size()
{
    return renderer->get_window_size();
}

void Engine::set_window_title(const std::string title)
{
    renderer->set_window_title(title);
}

double Engine::get_delta_time()
{
    return delta_time;
}

void Engine::set_delta_time_factor(double new_value)
{
    delta_time_factor = new_value;
}

double Engine::get_delta_time_factor()
{
    return delta_time_factor;
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
    return input_state.contains(key);
}

bool Engine::is_key_up(EngineIO::InputEvent key) const
{
    return !input_state.contains(key);
}

bool Engine::any_key_down() const
{
    return !input_state.empty();
}

std::set<EngineIO::InputEvent> Engine::get_all_keys_down() const
{
    return input_state;
}

bool Engine::is_left_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::LEFT);
}

bool Engine::is_right_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::RIGHT);
}

bool Engine::is_up_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::UP);
}

bool Engine::is_down_arrow_down() const
{
    return is_key_down(EngineIO::InputEvent::DOWN);
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
