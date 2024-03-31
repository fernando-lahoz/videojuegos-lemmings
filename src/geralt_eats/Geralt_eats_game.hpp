#pragma once

#include <memory>

#include "engine/game.hpp"
#include "engine/render_2D.hpp"
#include "engine/entity.hpp"
#include "engine/fixed_text.hpp"
#include "engine/trigger.hpp"

#include "Geralt.hpp"
#include "Apple.hpp"
#include "Geralt_eats_camera.hpp"
#include "MainCamera.hpp"

class Geralt_eats_game : public Game
{
private:
    int n_apples = 0;
    int max_apples = 1;

    static Point2i lemmings_font_map(char c)
    {
        if (c >= 'A' && c <= 'M')
            return {(c - 'A'), 0};
        else if (c >= 'N' && c <= 'Z')
            return {(c - 'N'), 1};
        else if (c >= 'a' && c <= 'm')
            return {(c - 'a'), 2};
        else if (c >= 'n' && c <= 'z')
            return {(c - 'n'), 3};
        else if (c >= '0' && c <= '9')
            return {(c - '0'), 4};
        else
        {
            switch (c)
            {
            case '.':
                return {0, 5};
            case '(':
                return {1, 5};
            case ')':
                return {2, 5};
            case '\'':
                return {3, 5};
            case '!':
                return {4, 5};
            case '%':
                return {5, 5};
            case '-':
                return {6, 5};
            default:
                return {12, 5}; // white space
            }
        }
    }

public:
    Geralt_eats_game()
        : Game("Geralt_eats")
    {
    }

    std::shared_ptr<Camera2D> get_main_camera() const override
    {
        return std::make_shared<MainCamera>();
        // return std::make_shared<Geralt_camera>();
    }

    void test_task()
    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Task finished" << std::endl;
    }

    void on_game_startup(Engine &engine) override
    {
        auto ground_alpha = engine.load_texture("assets/ground_alpha.png");
        auto t2 = engine.load_texture("assets/terrain.png");
        auto t3 = engine.load_texture("assets/dehecho.png");

        auto box1 = std::make_shared<Apple>(Point3f(0.2, 0, 0), Vector2f(0.2, 0.2), t3, engine);
        auto box2 = std::make_shared<Apple>(Point3f(0.4, 0.7, 0), Vector2f(0.2, 0.2), t3, engine);

        auto &mixer = engine.get_sound_mixer();
        Music canon = mixer.load_music("assets/music/02_Lemming 1 (Pachebel's Canon).mp3");
        mixer.play_music(canon, true);


        box1->set_speed(Vector2f(0.1, 0.2));
        box2->set_speed(Vector2f(-0.1, -0.2));

        box1->change_collision_type(engine, Entity::Collision_type::CHARACTER);
        box2->change_collision_type(engine, Entity::Collision_type::STRUCTURE);

        create_entity(box1);
        create_entity(box2);
        engine.async_task([this]() { test_task(); });

        create_camera(std::make_shared<Geralt_camera>());
    }

    void on_loop_start(Engine &engine) override
    {
        
    }

    void on_entity_destruction([[maybe_unused]] Engine &engine, EntityPtr entity) override
    {
        
    }
};