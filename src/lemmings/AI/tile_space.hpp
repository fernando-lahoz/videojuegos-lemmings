#pragma once

#include <vector>

#include "lemmings/AI_autoplay.hpp"

class TileSpace
{
private:

public:

    TileSpace() = default;

    /**
     * @brief A TileSpace represents a data structure that describes a playable
     *        map by a set of axis-aligned boxes with one of AI_autoplay::TILE
     *        type that know the neighbours around them.
     *
     * @param texture Texture object of the described map
     * @param map_entities List of Entity objects that are other map surfaces
     * @param init_tiles List of tiles from where Lemmings can spawn
     * @param end_tiles List of tiles that Lemmings must reach
     * @param death_tiles List of tiles where Lemmings will die if reached
     */
    TileSpace(Texture texture, const std::vector<Entity*>& map_entities,
            std::vector<Bound2f> init_tiles,
            std::vector<Bound2f> end_tiles,
            std::vector<Bound2f> death_tiles);

};


#include "lemmings/AI/tile_space.ipp"
