#include <memory>

#include "../engine/engine.hpp"
#include "geralt_eats_game.cpp"



int main()
{
    auto game = std::make_shared<Geralt_eats_game>();
    
    Engine engine(game);
    engine.start();

    return 0;
}


