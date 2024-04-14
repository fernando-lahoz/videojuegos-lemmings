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
#include "electric_field.hpp"

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
        return std::make_shared<Geralt_camera>();
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
        auto lemmings_terrain = engine.load_texture("assets/maps/bkg/map_0_0.png");
        auto flat_ground = engine.load_texture("assets/terrain.png");
        auto t3 = engine.load_texture("assets/dehecho.png");
        auto cielo_txt = engine.load_texture("assets/cielo.jpeg");
        auto energy_ball_txt = engine.load_texture("assets/energy_ball.png");
        auto wall_txt = engine.load_texture("assets/wall_alpha.png");

        auto geralt = std::make_shared<Geralt>(Point2f(1, 0.3), Vector2f(0.25, 0.3), engine);
        //auto ground = std::make_shared<Entity>(Point2f(-2, 0), 1, Vector2f(7, 2.25), lemmings_terrain, engine, "Ground", Entity::Physics_type::RIGID_BODY, Entity::Collision_check::ALPHA, Entity::Collision_type::STATIC_BODY, Entity::Cursor_type::AABB, "Ground");
        auto ground = std::make_shared<Entity>(Point2f(-10, 1.5), 1, Vector2f(20, 0.75), flat_ground, engine, "Ground", Entity::Physics_type::RIGID_BODY, Entity::Collision_check::AABB, Entity::Collision_type::STATIC_BODY, Entity::Cursor_type::AABB, "Ground");
        auto wall = std::make_shared<Entity>(Point2f(3.5, 0), 1, Vector2f(0.5, 2.25), wall_txt, engine, "Ground", Entity::Physics_type::RIGID_BODY, Entity::Collision_check::ALPHA, Entity::Collision_type::STATIC_BODY, Entity::Cursor_type::AABB, "Ground");


        auto cielo = std::make_shared<Entity>(Point2f(0, 0), 10, Vector2f(4, 2.24), cielo_txt, engine, "Cielo", Entity::Physics_type::NONE, Entity::Collision_check::NONE, Entity::Collision_type::STATIC_BODY, Entity::Cursor_type::AABB, "Cielo");
        ground->disable_gravity();
        cielo->disable_gravity();
        wall->disable_gravity();

        auto &mixer = engine.get_sound_mixer();
        Music canon = mixer.load_music("assets/music/02_Lemming 1 (Pachebel's Canon).mp3");
        //mixer.play_music(canon, true);

        engine.set_gravity(9.8);

        //box2->set_speed(Vector2f(-0.1, -0.2));

        //auto field = std::make_shared<Electric_field>(engine, Point2f(0.5, 0.7), Vector2f(0.44, 0.4), 10, 1000);

        
        engine.create_entity(geralt);
        engine.create_entity(ground);
        engine.create_entity(cielo);
        engine.create_entity(wall);
        //engine.create_entity(field);

        create_camera(std::make_shared<Geralt_camera>());
    }

    void on_loop_start(Engine &engine) override
    {
        
    }

    void on_entity_destruction([[maybe_unused]] Engine &engine, EntityPtr entity) override
    {
        
    }
};