#include <memory>

#include <SDL2/SDL.h>

#include "engine/engine.hpp"
#include "geralt_eats/Geralt_eats_game.hpp"



int main(int, char**)
{
    try
    {
        Engine engine = Engine(new Geralt_eats_game());
        engine.start();
    }
    catch(std::exception& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

    return EXIT_SUCCESS;
}


