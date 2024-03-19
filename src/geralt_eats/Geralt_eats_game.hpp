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
#include "Lemming_hero.hpp"
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

    void on_game_startup(Engine &engine) override
    {
        auto ground_alpha = engine.load_texture("assets/ground_alpha.png");
        auto t2 = engine.load_texture("assets/terrain.png");
        auto t3 = engine.load_texture("assets/dehecho.png");

        auto lemm = engine.load_texture("assets/maps/bkg/map_0_0.png");

        auto geralt = std::make_shared<Geralt>(Point3f(0.4, 0.1, 0), Vector2f(0.1, 0.125), engine);
        // auto ground = std::make_shared<Rigid_body>(Point3f(0, 0.45, 0), Vector2f(1, 0.25), ground_alpha, "Ground");
        auto ground = std::make_shared<Rigid_body>(Point3f(-0.2, 0.3, 0), Vector2f(2, 1), lemm, engine, "MAP");
        // auto lemming = std::make_shared<Lemming_hero>(Point3f(0.47, 0.4, 0), Vector2f(0.08, 0.08), engine);
        auto lemming = std::make_shared<Lemming_hero>(Point3f(0.47, 0.4, 0), Vector2f(0.1, 0.125), engine);

        auto ground2 = std::make_shared<Rigid_body>(Point3f(0.7, 0, 0), Vector2f(0.3, 1), t2, engine, "Ground");

        auto &mixer = engine.get_sound_mixer();
        Music canon = mixer.load_music("assets/music/02_Lemming 1 (Pachebel's Canon).mp3");
        mixer.play_music(canon, true);

        auto hud = std::make_shared<Rigid_body>(Point3f(100, 100.8, 0), Vector2f(1, 0.2), engine.load_texture("assets/menu/title.png"), engine, "Ground");

        auto trigger = std::make_shared<Trigger>(Point3f(0.05, 0.2, 0), Vector2f(0.3, 0.8), engine, "Trigger");
        trigger->add_asociated_entity(geralt);
        trigger->set_active_texture(engine.load_texture("assets/dehecho.png"));

        create_entity(hud);

        create_entity(lemming);
        create_entity(geralt);
        create_entity(ground);
        create_entity(trigger);
        // create_entity(ground2);

        create_camera(std::make_shared<Geralt_camera>());
    }

    void on_loop_start(Engine &engine) override
    {
        while (n_apples < max_apples)
        {
            // Float x_pos = ((Float)rand() / RAND_MAX) * 0.8 + 0.1;
            Float x_pos = 0.5;

            auto apple = std::make_shared<Apple>(
                Point3f(x_pos, -0.11, 0),
                Vector2f(0.09, 0.1),
                engine);

            apple->set_gravity(2);

            // create_entity(apple);
            n_apples++;
        }
    }

    void on_entity_destruction([[maybe_unused]] Engine &engine, EntityPtr entity) override
    {
        if (entity->get_entity_name() == "Apple")
        {
            n_apples--;
        }
    }
};