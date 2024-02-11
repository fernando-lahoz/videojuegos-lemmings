#pragma once

#include <exception>
#include <string>

#include <SDL2/SDL.h>

#define ERROR_CONTEXT __PRETTY_FUNCTION__

namespace error {

inline std::runtime_error sdl_exception(std::string_view context)
{
    return std::runtime_error(std::string(context) + std::string(": ") + SDL_GetError());
}

} //namespace error
