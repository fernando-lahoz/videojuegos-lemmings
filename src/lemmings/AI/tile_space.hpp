#pragma once

#include <vector>

#include "lib/texture.hpp"
#include "geometry/bounding_box.hpp"
#include "engine/entity.hpp"

enum class TILE
{
    EMPTY,
    DIRT,
    INIT,
    GOAL,
    BRIDGE,
    METAL,
    DIRECTIONAL_RIGHT,
    DIRECTIONAL_LEFT,
    DEATH
};

class TileSpace
{
private:
    static
    std::pair<std::vector<TILE>, std::size_t>
    build_matrix_of_tiles(const Texture& texture);

    
    static
    void add_tiles_to_matrix(std::vector<TILE>& tile_buffer, std::size_t width,
                             const std::vector<Bound2f>& tile_bounds, TILE tile_type);

public:

    TileSpace() = default;

    /**
     * @brief A TileSpace represents a data structure that describes a playable
     *        map by a set of axis-aligned boxes with one of TILE
     *        type that know the neighbours around them.
     *
     * @param texture Texture object of the described map
     * @param map_entities List of Entity objects that are other map surfaces.
     *        Those are entities named DIRECTIONAL_WALL or METAL.
     * @param init_tiles List of tiles from where Lemmings can spawn.
     * @param goal_tiles List of tiles that Lemmings must reach.
     * @param death_tiles List of tiles where Lemmings will die if reached.
     */
    TileSpace(const Texture& texture, const Bound2f& map_global_pos,
                     const std::vector<Entity*>& map_entities,
                     const std::vector<Bound2f>& init_tiles,
                     const std::vector<Bound2f>& goal_tiles,
                     const std::vector<Bound2f>& death_tiles);

};

//--- Implementation -----------------------------------------------------------

std::pair<std::vector<TILE>, std::size_t> TileSpace::build_matrix_of_tiles(const Texture& texture) 
{

    Uint8 r, g, b, a;

    SDL_Surface *surface = texture.get_surface();
    Uint32* pixels = (Uint32*)surface->pixels;

    int width = texture.get_width();
    int height = texture.get_height();

    std::vector<TILE> tile_buffer = {width * height, TILE::EMPTY};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Uint32 pixel_value = pixels[(i * width) + j];
            SDL_GetRGBA(pixel_value, surface->format, &r, &g, &b, &a);
            if (a >= 16)
            {
                tile_buffer[(i * width) + j] = TILE::DIRT;
            }
        }
    }

    return std::pair(tile_buffer, std::size_t(width));
}

void TileSpace::add_tiles_to_matrix(std::vector<TILE>& tile_buffer, std::size_t width,
                         const std::vector<Bound2f>& tile_bounds, TILE tile_type)
{
    for (Bound2f bound : tile_bounds)
    {
        int min_i = std::round(bound.pMin.x);
        int max_i = std::round(bound.pMin.y);
        int min_j = std::round(bound.pMax.x);
        int max_j = std::round(bound.pMax.y);

        for (int i = min_i ; i < max_i; i++)
        {
            for (int j = min_j; j < max_j; j++)
            {
                tile_buffer[(i * width) + j] = tile_type;
            }
        }
    }
}

TileSpace::TileSpace(const Texture& texture, const Bound2f& map_global_pos,
                     const std::vector<Entity*>& map_entities,
                     const std::vector<Bound2f>& init_tiles,
                     const std::vector<Bound2f>& goal_tiles,
                     const std::vector<Bound2f>& death_tiles)
{
    auto [tile_buffer, width] = build_matrix_of_tiles(texture);

    add_tiles_to_matrix(tile_buffer, width, init_tiles, TILE::INIT);
    add_tiles_to_matrix(tile_buffer, width, goal_tiles, TILE::GOAL);
    add_tiles_to_matrix(tile_buffer, width, death_tiles, TILE::DEATH);


    // add_tiles_to_matrix(init, goal, death...);
    // add_entities_to_matrix();

    // deflate_by_rows() -> vector<Box>;
    
    // do {
        // mold_boxes();
    // } repeat until (no_changes)

    // (opt) save_init_and_goal_boxes(); 
 

    // for (Entity *entity : map_entities)
    // {
    //     Texture texture = entity->get_active_texture();
    //     SDL_Surface *surface = texture.get_surface();
    //     Uint32* pixels = (Uint32*)surface->pixels;

    //     int width = texture.get_width();
    //     int height = texture.get_height();

    //     float pixel_density_w = width / ;

    //     int min_i = std::round(bound.pMin.x);
    //     int max_i = std::round(bound.pMin.y);
    //     int min_j = std::round(bound.pMax.x);
    //     int max_j = std::round(bound.pMax.y);

    //     for (int i = min_i ; i < max_i; i++)
    //     {
    //         for (int j = min_j; j < max_j; j++)
    //         {
    //             tile_buffer[(i * width) + j] = TILE::INIT;
    //         }
    //     }
    // }

}