#include <memory>

#include <SDL2/SDL.h>

#include "engine/engine.hpp"
#include "geralt_eats/Geralt_eats_game.hpp"
#include "engine/physics.cpp"

int main(int, char**)
{
    try
    {
        //Engine engine = Engine(new Geralt_eats_game());
        //engine.start();
    }
    catch(std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

    Engine engine = Engine(new Geralt_eats_game());
    auto flat_ground = engine.load_texture("assets/terrain.png");

    auto geralt = std::make_shared<Geralt>(Point2f(0, 0), Vector2f(1, 1), engine);
    auto ground = std::make_shared<Entity>(Point2f(0, 0), 1, Vector2f(1, 1), flat_ground, engine, "Ground", Entity::Physics_type::RIGID_BODY, Entity::Collision_check::AABB, Entity::Collision_type::STATIC_BODY, Entity::Cursor_type::AABB, "Ground");

    Collision_point cp;
    check_alpha_collision(geralt, ground, cp);



    return EXIT_SUCCESS;
}


