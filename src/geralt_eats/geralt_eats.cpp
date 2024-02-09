#include <memory>

#include <SDL2/SDL.h>

#include "engine/engine.hpp"
#include "geralt_eats/Geralt_eats_game.hpp"



int main(int, char**)
{
    auto game = std::make_shared<Geralt_eats_game>();
    
    Engine engine(game);
    engine.start();

    return 0;
}


