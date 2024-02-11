#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/render_2D.hpp"
#include "engine/entity.hpp"

#include "Geralt.hpp"
#include "Apple.hpp"
#include "Geralt_eats_camera.hpp"

class Geralt_eats_game : public Game
{
    private:

    int n_apples = 0;
    int max_apples = 1;

    public:

    std::unique_ptr<Camera2D> get_camera() const override
    {
        return std::make_unique<Geralt_camera>();
    }

    void on_game_startup(Engine& engine) override
    {
        auto t2 = engine.load_texture("assets/terrain.png");

        auto geralt = std::make_shared<Geralt>(Point3f(0.4, 0.4, 0), Vector2f(0.1, 0.125), engine);
        auto ground = std::make_shared<Rigid_body>(Point3f(0, 0.75, 0), Vector2f(1, 0.25), t2, "Ground");

        create_entity(geralt);
        create_entity(ground);
    }

    void on_loop_start([[maybe_unused]]Engine& engine) override
    {
        while (n_apples < max_apples)
        {
            // Between 0.1 and 0.9
            //Float x_pos = ((Float)rand() / RAND_MAX) * 0.8 + 0.1;

            Float x_pos = 0.5;

            auto apple = std::make_shared<Apple>(Point3f(x_pos, -0.11, 0), Vector2f(0.09, 0.1), 
                    engine.load_texture("assets/apple.png"));
            
            apple->set_gravity(2);
            apple->enable_gravity();
            
            create_entity(apple);
            n_apples++;
        }
    }

    void on_entity_destruction([[maybe_unused]]Engine& engine, EntityPtr entity) override
    {
        if (entity->get_entity_name() == "Apple")
        {
            n_apples--;
        }
    }
};