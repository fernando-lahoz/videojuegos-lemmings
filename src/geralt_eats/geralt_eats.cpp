#include <vector>
#include <thread>
#include <chrono>

#include "src/lib/types.h"

#include "src/engine/Render_2D.cpp"
#include "src/engine/Entity.cpp"
#include "src/engine/Physics.cpp"

#include "src/geralt_eats/Geralt.cpp"


class Main_loop
{
    using TimePoint = std::chrono::time_point<
            std::chrono::steady_clock, 
            std::chrono::nanoseconds>;

    std::vector<EntityPtr> entities;
    Camera2D camera;
    Render_2D renderer;
    Physics_engine physics;

    TimePoint check_point;

    std::shared_ptr<Geralt> main_character;


    void send_key_down_event(SDL_KeyboardEvent key)
    {
        for (auto& entity : entities)
        {
            entity->on_key_down(key);
        }
    }

    void send_key_up_event(SDL_KeyboardEvent key)
    {
        for (auto& entity : entities)
        {
            entity->on_key_up(key);
        }
    }


    // Returns true if the program should quit
    bool processEvents()
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                return true;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE
                    || event.key.keysym.sym == SDLK_q)
                {
                    return true;
                }

                send_key_down_event(event.key);
            }

            if (event.type == SDL_KEYUP)
            {
                send_key_up_event(event.key);
            }
        }

        return false;
    }


    // Returns delta time in seconds
    double get_delta_time()
    {
        TimePoint new_check_point = std::chrono::steady_clock::now();

        uint64_t delta = std::chrono::duration_cast<std::chrono::nanoseconds>(
                new_check_point - check_point).count();

        check_point = new_check_point;

        return (double)delta / 1e9;
    }

    void compute_physics(double delta_time)
    {
        // Send pre-physics event to all entities
        physics.pre_physics(entities, delta_time);

        physics.update_positions(entities, delta_time);
        physics.compute_collisions(entities);
        
        // Send post-physics event to all entities
        physics.post_physics(entities, delta_time);
    }

    public:

    Main_loop()
    : renderer(800, 800), 
        camera(Bound2f(Point2f(0, 0), Point2f(1, 1))),
        physics()
    {
        SDL_Init(SDL_INIT_VIDEO);
        check_point = std::chrono::steady_clock::now();
    }

    void start()
    {
        auto t2 = renderer.loadTexture("assets/terrain.png");

        main_character = std::make_shared<Geralt>(Point3f(0.4, 0.4, 0), Vector2f(0.1, 0.125), renderer);
        
        entities.push_back(main_character);
        entities.push_back(std::make_shared<Entity>(Point3f(0, 0.75, 1), Vector2f(1, 0.25), t2));
        
        bool quit = false;
        while(!quit)
        {
            double delta_time = get_delta_time();
            quit = processEvents();

            // Update call to physics engine
            compute_physics(delta_time);
            
            // Draw call to renderer
            renderer.draw(entities, camera);
        }
    }
};


int main()
{
    Main_loop main_loop;

    main_loop.start();

    return 0;
}


