#pragma once

#include <memory>
#include "../engine/Game.cpp"
#include "../engine/Render_2D.cpp"
#include "../engine/Entity.cpp"

#include "Geralt.cpp"
#include "Apple.cpp"
#include "Geralt_eats_camera.cpp"

class Geralt_eats_game : public Game
{
    private:

    int n_apples = 0;
    int max_apples = 1;

    public:

    Camera_ptr get_camera() const override
    {
        return std::make_shared<Geralt_camera>();
    }

    void on_game_startup(Engine_ptr engine) override
    {
        auto t2 = engine->loadTexture("/home/hsunekichi/Escritorio/videojuegos-lemmings/assets/terrain.png");

        auto geralt = std::make_shared<Geralt>(Point3f(0.4, 0.4, 0), Vector2f(0.1, 0.125), engine);
        auto ground = std::make_shared<Entity>(Point3f(0, 0.75, 1), Vector2f(1, 0.25), t2);

        create_entity(geralt);
        create_entity(ground);
    }

    void on_loop_start(Engine_ptr engine, Float delta_time) override
    {
        while (n_apples < max_apples)
        {
            // Between 0.1 and 0.9
            //Float x_pos = ((Float)rand() / RAND_MAX) * 0.8 + 0.1;

            Float x_pos = 0.5;

            auto apple = std::make_shared<Apple>(Point3f(x_pos, -0.11, 0), Vector2f(0.09, 0.1), 
                    engine->loadTexture("/home/hsunekichi/Escritorio/videojuegos-lemmings/assets/apple.png"));
            
            apple->set_gravity(2);
            apple->enable_gravity();
            
            create_entity(apple);
            n_apples++;
        }
    }

    void on_entity_destruction(Engine_ptr engine, EntityPtr entity) override
    {
        if (entity->get_type() == "Apple")
        {
            n_apples--;
        }
    }
};