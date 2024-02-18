#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/fixed_text.hpp"

#include "Geralt.hpp"
#include "Apple.hpp"
#include "Geralt_eats_camera.hpp"

class Geralt_eats_game : public Game
{
private:

    int n_apples = 0;
    int max_apples = 1;

    static Point2i lemmings_font_map(char c) 
    {
        if (c >= 'A' && c <= 'M')       return {(c - 'A'), 0};
        else if (c >= 'N' && c <= 'Z')  return {(c - 'N'), 1};
        else if (c >= 'a' && c <= 'm')  return {(c - 'a'), 2};
        else if (c >= 'n' && c <= 'z')  return {(c - 'n'), 3};
        else if (c >= '0' && c <= '9')  return {(c - '0'), 4};
        else {
            switch (c)
            {
            case '.':   return {0, 5};
            case '(':   return {1, 5};
            case ')':   return {2, 5};
            case '\'':  return {3, 5};
            case '!':   return {4, 5};
            case '%':   return {5, 5};
            case '-':   return {6, 5};
            default:    return {12, 5}; //white space
            }
        }
    }

public:

    Geralt_eats_game()
    : Game("Geralt_eats")
    { }

    std::shared_ptr<Camera2D> get_camera() const override
    {
        return std::make_shared<Geralt_camera>();
    }

    void on_game_startup(Engine& engine) override
    {
        auto t2 = engine.load_texture("assets/terrain.png");

        auto geralt = std::make_shared<Geralt>(Point3f(0.4, 0.4, 0), Vector2f(0.1, 0.125), engine);
        auto ground = std::make_shared<Rigid_body>(Point3f(0, 0.75, 0), Vector2f(1, 0.25), t2, "Ground");

        create_entity(geralt);
        create_entity(ground);
        create_entity(std::make_shared<FixedText>(Point3f(0, 0, -1), Vector2f(0.05, 0.05),
                    engine.load_texture("assets/font/font-purple.png"),
                    Vector2i(16, 30), lemmings_font_map, "Geralt Eats Apples!!"));
    }

    void on_loop_start([[maybe_unused]]Engine& engine) override
    {
        while (n_apples < max_apples)
        {
            // Between 0.1 and 0.9
            //Float x_pos = ((Float)rand() / RAND_MAX) * 0.8 + 0.1;

            Float x_pos = 0.5;

            auto apple = std::make_shared<Apple>(
                    Point3f(x_pos, -0.11, 0), 
                    Vector2f(0.09, 0.1), 
                    engine);
            
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