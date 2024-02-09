#include <iostream>
#include <iomanip>

#include <SDL2/SDL.h>

#include "lib/types.hpp"
#include "lib/spectrum.hpp"
#include "geometry/vector.hpp"
#include "geometry/point.hpp"
#include "geometry/ray.hpp"
#include "geometry/bounding_box.hpp"
#include "geometry/transform.hpp"
#include "math/math.hpp"
#include "math/matrix3x3.hpp"
#include "math/matrix4x4.hpp"

int main(int,char**) {

    std::cout << Vector3f{1, 2, 3} << '\n';
    std::cout << Point3f{1, 2, 3}.to_vector().max_component() << '\n';
    std::cout << math::pow<34, uint64_t>(3) << '\n';
    std::cout << std::setprecision(20) << 1.45999 << math::next_float_up(1.45999) << '\n';

    std::cout << (BoundingBox2<int>)(BoundingBox2<Float>(Point2f(1.464, 2.74), Point2f(1, 2))) << '\n';
    std::cout << ((Vector2i)Vector2f(1, 2)).length() << '\n';


    int init_flags = SDL_INIT_TIMER | SDL_INIT_VIDEO;
    if (SDL_Init(init_flags) != 0) {
        std::cerr << "SDL failed to init: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    int window_flags = SDL_WINDOW_SHOWN;
    SDL_Window *window = SDL_CreateWindow("Hello World!",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600, window_flags);
    if (window == nullptr) {
        std::cerr << "SDL failed to create window: " << SDL_GetError() << '\n';
        return EXIT_FAILURE;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            
            default:
                break;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}