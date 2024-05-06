#pragma once

#include <vector>
#include <stack>
#include <numeric>
#include <cmath>
#include <random>
#include <iostream>

#include "lib/texture.hpp"
#include "geometry/bounding_box.hpp"
#include "engine/entity.hpp"

enum class TILE : int8_t
{
    EMPTY,
    DIRT,
    INIT,
    GOAL,
    BRIDGE,
    METAL,
    DIRECTIONAL_RIGHT,
    DIRECTIONAL_LEFT,
    DEATH,

    NONE,
    number_of_elements
};

RGBA tile_to_color(TILE tile)
{
    switch (tile)
    {
    case TILE::EMPTY:               return {255, 255, 255, 255}; //white
    case TILE::DIRT:                return {34, 177, 76, 255};   //green
    case TILE::INIT:                return {255, 255, 0, 255}; //yellow
    case TILE::GOAL:                return {255, 0, 255, 255}; //magenta
    case TILE::METAL:               return {50, 50, 50, 255}; //grey
    case TILE::DIRECTIONAL_RIGHT:   return {0, 50, 255, 255}; //blue
    case TILE::DIRECTIONAL_LEFT:    return {255, 50, 0, 255}; //red
    case TILE::DEATH:               return {0, 0, 0, 255}; // black
    default:
        return {0, 0, 0, 0};
    }
}

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
class TileSpace
{
private:
    static std::pair<std::vector<TILE>, Point2<std::size_t>>
    build_matrix_of_tiles(const Texture& texture);

    
    static void
    add_tiles_to_matrix(std::vector<TILE>& tile_buffer,
                        std::size_t pixel_width, std::size_t pixel_height,
                        const Bound2f& map_global_pos,
                        const std::vector<Bound2f>& tile_bounds, 
                        TILE tile_type);

    static void
    add_entities_to_matrix(std::vector<TILE>& tile_buffer,
                           Point2<std::size_t> dim,
                           const Bound2f& map_global_pos,
                           const std::vector<Entity*>& map_entities);

public:

    struct Box
    {
        std::vector<Box*> right = {}, left = {}, up = {}, down = {};
        Bound2i pixel_box;
        TILE tile;

        int8_t _random_color = 0;
        bool visited = false;
    };

private:

    std::vector<std::unique_ptr<Box>> box_collection;

    void spaguetti_cooking(const std::vector<TILE>& tile_buffer, Point2<std::size_t> dim);

    void coalesce();

public:
    
    TileSpace() = default;

    
    TileSpace(const Texture& texture, const Bound2f& map_global_pos,
                     const std::vector<Entity*>& map_entities,
                     const std::vector<Bound2f>& init_tiles,
                     const std::vector<Bound2f>& goal_tiles,
                     const std::vector<Bound2f>& death_tiles);

    bool save_as_png(const std::string& path);
};

//--- Implementation -----------------------------------------------------------

std::pair<std::vector<TILE>, Point2<std::size_t>>
TileSpace::build_matrix_of_tiles(const Texture& texture) 
{

    Uint8 r, g, b, a;

    SDL_Surface *surface = texture.get_surface();
    Uint32* pixels = (Uint32*)surface->pixels;

    int width = texture.get_width();
    int height = texture.get_height();

    std::vector<TILE> tile_buffer = {std::size_t(width * height), TILE::EMPTY};

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

    return std::pair(tile_buffer, Point2(std::size_t(width), std::size_t(height)));
}

void TileSpace::add_tiles_to_matrix(std::vector<TILE>& tile_buffer,
                                    std::size_t pixel_width, std::size_t pixel_height,
                                    const Bound2f& map_global_pos,
                                    const std::vector<Bound2f>& tile_bounds,
                                    TILE tile_type)
{
    for (Bound2f bound : tile_bounds)
    {
        const int min_j = std::round(((bound.pMin.x - map_global_pos.pMin.x)/map_global_pos.diagonal().x)*pixel_width);
        const int min_i = std::round(((bound.pMin.y - map_global_pos.pMin.y)/map_global_pos.diagonal().y)*pixel_height);
        const int max_j = std::round(((bound.pMax.x - map_global_pos.pMin.x)/map_global_pos.diagonal().x)*pixel_width);
        const int max_i = std::round(((bound.pMax.y - map_global_pos.pMin.y)/map_global_pos.diagonal().y)*pixel_height);

        for (int i = min_i; i < max_i && i < int(pixel_height); i++)
        {
            for (int j = min_j; j < max_j && j < int(pixel_width); j++)
            {
                tile_buffer[(i * pixel_width) + j] = tile_type;
            }
        }
    }
}

void TileSpace::add_entities_to_matrix(std::vector<TILE>& tile_buffer,
                                       Point2<std::size_t> dim,
                                       const Bound2f& map_global_pos,
                                       const std::vector<Entity*>& map_entities)
{
    for (Entity *entity : map_entities)
    {
        Uint8 r, g, b, a;

        Texture texture = entity->get_active_texture();
        SDL_Surface *surface = texture.get_surface();
        Uint32* pixels = (Uint32*)surface->pixels;
        Bound2f entity_bound = entity->bound2f();

        int width = texture.get_width();
        int height = texture.get_height();

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                Float local_x = Float(j) / width;
                Float local_y = Float(i) / height;

                Float global_x = local_x * entity_bound.diagonal().x + entity_bound.pMin.x;
                Float global_y = local_y * entity_bound.diagonal().y + entity_bound.pMin.y;
                
                int map_j = std::round(((global_x - map_global_pos.pMin.x) / map_global_pos.diagonal().x) * dim.x);
                int map_i = std::round(((global_y - map_global_pos.pMin.y) / map_global_pos.diagonal().y) * dim.y);
            
                if (map_i >= dim.y || map_j >= dim.x)
                    continue;

                Uint32 pixel_value = pixels[(i * width) + j];
                SDL_GetRGBA(pixel_value, surface->format, &r, &g, &b, &a);
                if (a >= 16)
                {
                    const std::string name = entity->get_entity_name();
                    if (name == "METAL")
                    {
                        tile_buffer[(map_i * dim.x) + map_j] = TILE::METAL;
                    }
                    else if (name == "DIRECTIONAL WALL")
                    {
                        Directional_structure *dir_wall = dynamic_cast<Directional_structure*>(entity);
                        
                        if (dir_wall != nullptr)
                        {
                            if (dir_wall->is_same_direction(-1))
                            {
                                tile_buffer[(map_i * dim.x) + map_j] = TILE::DIRECTIONAL_LEFT;
                            }
                            else
                            {
                                tile_buffer[(map_i * dim.x) + map_j] = TILE::DIRECTIONAL_RIGHT;
                            }
                        }
                        else
                        {
                            std::cout << "Dynamic Cast to Directional_structure failed\n";
                        }
                    }                   
                }
            }
        }
    }
}


void TileSpace::spaguetti_cooking(const std::vector<TILE>& tile_buffer, Point2<std::size_t> dim)
{
    int counter_box = 0;

    std::vector<Box*> prev_row_boxes;

    TILE now_searching = TILE::NONE;
    int start = 0, end = 0;

    for (std::size_t i = 0; i < dim.y; i++)
    {
        std::vector<Box*> row_boxes;
        Box* prev_box = nullptr;
        now_searching = TILE::NONE;

        for (std::size_t j = 0; j < dim.x; j++)
        {
            TILE now_looking =  tile_buffer[dim.x * i + j];

            // This is nasty, as last pixel could be different,
            // but that would be changed by blurr
            if (j == dim.x - 1)
            {
                now_looking = TILE::NONE;
                j++;
            }
            
            if (now_searching == TILE::NONE)
            {
                start = j;
                now_searching = now_looking;
                continue;
            }
            else if (now_searching != now_looking)
            {
                end = j;

                Box *box = new Box();
                box->tile = now_searching;
                box->pixel_box = {{start, int(i)}, {end, int(i) + 1}};

                start = j;
                now_searching = now_looking;

                if (prev_box != nullptr)
                {
                    box->left.push_back(prev_box);
                    prev_box->right.push_back(box);
                }
                prev_box = box;

                for (Box *upper_box : prev_row_boxes)
                {
                    const int a1 = upper_box->pixel_box.pMin.x;
                    const int b1 = upper_box->pixel_box.pMax.x;

                    const int a2 = box->pixel_box.pMin.x;
                    const int b2 = box->pixel_box.pMax.x;

                    if ((a1 <= a2 && b1 > a2) || (a2 <= a1 && b2 > a1))
                    {
                        box->up.push_back(upper_box);
                        upper_box->down.push_back(box);
                    }
                }

                row_boxes.push_back(box);

                box_collection.emplace_back(box);
            }
        }

        prev_row_boxes = std::move(row_boxes);
    }
}

void TileSpace::coalesce()
{
    std::stack<Box*> box_stack;

    Box *upper_box = box_collection[0].get();

    Box *next_upper_box = nullptr;

    do
    {
        if (!upper_box->right.empty()) {
            next_upper_box = upper_box->right[0];
        }
        else
        {
            next_upper_box = nullptr;
        }

        Box *box = upper_box;

        box_stack.push(box);

        do
        {
            box = box_stack.top();
            box_stack.pop();

            if (box->visited)
                continue;
            box->visited = true;

            Box *box_to_mix = nullptr;
            do
            {
                box_to_mix = nullptr;
                for (Box *lower : box->down)
                {
                    int a1 = box->pixel_box.pMin.x;
                    int b1 = box->pixel_box.pMax.x;
                    int a2 = lower->pixel_box.pMin.x;
                    int b2 = lower->pixel_box.pMax.x;

                    // Change this if boxes can break and/or rejoin
                    if (a1 == a2 && b1 == b2)
                    {
                        box_to_mix = lower;
                        break;
                    }
                }

                if (box_to_mix != nullptr)
                {
                    // Change this if boxes can break and/or reunite
                    box->pixel_box.pMax.y++;

                    for (Box *neighbour : box_to_mix->up)
                    {
                        std::replace(neighbour->down.begin(), neighbour->down.end(), box_to_mix, box);
                    }
                    for (Box *neighbour : box_to_mix->down)
                    {
                        std::replace(neighbour->up.begin(), neighbour->up.end(), box_to_mix, box);
                    }
                    for (Box *neighbour : box_to_mix->left)
                    {
                        std::replace(neighbour->right.begin(), neighbour->right.end(), box_to_mix, box);
                    }
                    for (Box *neighbour : box_to_mix->right)
                    {
                        std::replace(neighbour->left.begin(), neighbour->left.end(), box_to_mix, box);
                    }

                    box->down = std::move(box_to_mix->down);
                    for (Box *right_box : box_to_mix->right)
                    {
                        box->right.push_back(right_box);
                    }
                    for (Box *left_box : box_to_mix->left)
                    {
                        box->left.push_back(left_box);
                    }

                    auto past_end = std::remove_if(box_collection.begin(), box_collection.end(),
                                [box_to_mix](std::unique_ptr<Box>& ptr) {
                                    return ptr.get() == box_to_mix;
                                });
                    box_collection.erase(past_end, box_collection.end());
                }
            } while (box_to_mix != nullptr);

            for (Box *lower : box->down)
            {
                box_stack.push(lower);
            }
        } while (!box_stack.empty());

        upper_box = next_upper_box;
    } while (next_upper_box != nullptr);
    

    for (auto& box : box_collection)
    {
        auto remove_duplicates = [](auto& vec)
        {
            std::sort(vec.begin(), vec.end());
            vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        };
        remove_duplicates(box->down);
        remove_duplicates(box->right);
        remove_duplicates(box->left);
        remove_duplicates(box->up);
    }
}


bool TileSpace::save_as_png(const std::string& path)
{
    std::cout << "Saving to PNG. " << box_collection.size() << " boxes\n";

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist8(1,8); // distribution in range [1, 6]

    // Find max pMax.x and pMax.y
    int width = std::accumulate(box_collection.begin(), box_collection.end(), 0,
        [](int value, std::unique_ptr<Box>& box) {
            return std::max(value, box->pixel_box.pMax.x);
        });

    int height = std::accumulate(box_collection.begin(), box_collection.end(), 0,
        [](int value, std::unique_ptr<Box>& box) {
            return std::max(value, box->pixel_box.pMax.y);
        });

    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    Uint32* pixels = (Uint32*)surface->pixels;

    for (auto& ptr : box_collection)
    {
        Box* box = ptr.get();

        RGBA color = tile_to_color(box->tile);

        auto am_i_unique = [&](auto vec, int my_value) -> bool
        {
            for (Box *other : vec)
                if (other->tile == box->tile && other->_random_color == my_value)
                    return false;
            return true;
        };

        // This may block :(
        int my_random = dist8(rng);
        while (!am_i_unique(box->down, my_random) || !am_i_unique(box->left, my_random)
            || !am_i_unique(box->up, my_random) || !am_i_unique(box->right, my_random))
        {
            my_random = dist8(rng);
        }
        //std::cout << "Im out :)  " << counter++ << "\n";

        box->_random_color = my_random;

        auto add_to_color = [&](int r, int g, int b)
        {
            color = RGBA(
                color.r <= 200 ? color.r + r : color.r - r,
                color.g <= 200 ? color.g + g : color.g - g,
                color.b <= 200 ? color.b + b : color.b - b,
                color.a
            );
        };

        switch (my_random)
        {
        case 1: add_to_color(0, 0, 0);    break;
        case 2: add_to_color(0, 0, 40);   break;
        case 3: add_to_color(0, 40, 0);   break;
        case 4: add_to_color(0, 40, 40);  break;
        case 5: add_to_color(40, 0, 0);   break;
        case 6: add_to_color(40, 0, 40);  break;
        case 7: add_to_color(40, 40, 0);  break;
        case 8: add_to_color(40, 40, 40); break;
        }

        int min_i = box->pixel_box.pMin.y;
        int max_i = box->pixel_box.pMax.y;
        int min_j = box->pixel_box.pMin.x;
        int max_j = box->pixel_box.pMax.x;

        for (int i = min_i; i < max_i; i++)
        {
            for (int j = min_j; j < max_j; j++)
            {
                pixels[i * width + j] = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
            }
        }
    }
    
    bool result = IMG_SavePNG(surface, path.c_str()) == 0;
    SDL_FreeSurface(surface);

    return result;
}

bool save_map_as_png(const std::string& path, const std::vector<TILE>& map, Point2<std::size_t> dim)
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0, dim.x, dim.y, 32, 0, 0, 0, 0);
    Uint32* pixels = (Uint32*)surface->pixels;

    for (std::size_t i = 0; i < dim.y; i++)
    {
        for (std::size_t j = 0; j < dim.x; j++)
        {
            RGBA color = tile_to_color(map[i * dim.x + j]);
            pixels[i * dim.x + j] = SDL_MapRGBA(surface->format, color.r, color.g, color.b, color.a);
        }
    }

    bool result = IMG_SavePNG(surface, path.c_str()) == 0;
    SDL_FreeSurface(surface);

    return result;
}

//------------------------------------------------------------------------------

Float normal_cummulative(Float standar_deviation, Float a, Float b){
    return (std::erf(b/(standar_deviation*std::sqrt(2))) - std::erf(a/(standar_deviation*std::sqrt(2))))/2.0;
}

Float skew_normal_cummulative(Float standar_deviation, Float s, Float a, Float b){
    return (std::erf(s*b/(standar_deviation*std::sqrt(2))) - std::erf(s*a/(standar_deviation*std::sqrt(2))))/(2.0*s);
}

std::vector<Float> gaussian_filter(Float standar_deviation, unsigned int size)
{
    Float x_a = -0.5 - (size - 1)/2.0;
    Float x_b = 0.5 - (size - 1)/2.0;
    Float y_a = -0.5 - (size - 1)/2.0;
    Float y_b = 0.5 - (size - 1)/2.0;

    std::vector<Float> gaussian_matrix;
    gaussian_matrix.resize(size*size);
    
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            gaussian_matrix[i*size + j] = normal_cummulative(standar_deviation, x_a + j, x_b + j)*normal_cummulative(standar_deviation, y_a + i, y_b + i);
        }
    }

    return gaussian_matrix;
}

std::vector<Float> skew_gaussian_filter(Float standar_deviation, Float skewness, unsigned int size)
{
    Float x_a = -0.5 - (size - 1)/2.0;
    Float x_b = 0.5 - (size - 1)/2.0;
    Float y_a = -0.5 - (size - 1)/2.0;
    Float y_b = 0.5 - (size - 1)/2.0;

    std::vector<Float> skew_gaussian_matrix;
    skew_gaussian_matrix.resize(size*size);
    
    for (unsigned int i = 0; i < size; i++) {
        for (unsigned int j = 0; j < size; j++) {
            skew_gaussian_matrix[i*size + j] = skew_normal_cummulative(standar_deviation, 1.0/skewness, x_a + j, x_b + j)*skew_normal_cummulative(standar_deviation, skewness, y_a + i, y_b + i);
        }
    }

    return skew_gaussian_matrix;
}

// Devuelve std::vector<TILE>
// Recibe const std::vector<TILE>&
// Ambos son matrices
std::pair<std::vector<TILE>, Point2<std::size_t>>
map_blurr(const std::vector<TILE>& map, Float standar_deviation, Float skewness, unsigned int kernel_size, Point2<std::size_t> dim) {

    if (kernel_size % 2 == 0) {
        throw std::runtime_error("El kernel de la matriz debe ser impar y se ha introducido: " + kernel_size);
    }

    int offset = (kernel_size - 1)/2;
    
    std::vector<Float> g_filter = skew_gaussian_filter(standar_deviation, skewness, kernel_size);
    
    std::array<Float, static_cast<std::size_t>(TILE::number_of_elements)> tile_count;

    std::vector<TILE> blurred_map;
    blurred_map.resize(dim.x*dim.y);

    //Para cada fila
    for(int i = 0; i < dim.y; i++){

        //Para cada columna
        for(int j = 0; j < dim.x; j++){

            TILE t = map[i*dim.x + j];

            if(t == TILE::GOAL || t == TILE::INIT || t == TILE::DEATH){
                blurred_map[i*dim.x + j] = t;

            }else{

                //Realizamos la convolucion
                tile_count.fill(0.0);
                for(int k = -offset; k <= offset; k++){
                    for(int l = -offset; l <= offset; l++){

                        //Si no accedemos fuera de rango al mapa
                        if(!(i + k < offset || j + l < offset || i + k + offset >= dim.y || j + l + offset >= dim.x)){

                            TILE b = map[(i + k)*dim.x + (j + l)];

                            //Si el tile es un goal, init o death, como son triggers contribuyen al aire
                            if(b == TILE::GOAL || b == TILE::INIT || b == TILE::DEATH){
                                tile_count[static_cast<int>(TILE::EMPTY)] += g_filter[(k + offset)*kernel_size + (l + offset)];

                            //Si no calculamos de forma normal la contribucion
                            }else{
                                //Calculamos el peso de cada tile
                                tile_count[static_cast<int>(b)] += g_filter[(k + offset)*kernel_size + (l + offset)];
                            }
                        }
                    }
                }

                //Declaramos el tipo de tile y el peso mas grande encontrado
                unsigned int tile_type = 0;
                Float max = 0.0;

                //Para cada contribucion de cada tile
                for(int k = 0; k < static_cast<int>(TILE::number_of_elements); k++){

                    //Si el tile contribuye el que mas
                    if(max < tile_count[k]){

                        //Colocamos el nuevo maximo y ponemos el tipo de tile
                        max = tile_count[k];
                        tile_type = k;
                    }
                }

                //El mapa valdra el tile que mas contribuya en esa posicion
                blurred_map[i*dim.x + j] = static_cast<TILE>(tile_type);
            }
        }
    }

    return {blurred_map, dim};
}


//------------------------------------------------------------------------------

TileSpace::TileSpace(const Texture& texture, const Bound2f& map_global_pos,
                     const std::vector<Entity*>& map_entities,
                     const std::vector<Bound2f>& init_tiles,
                     const std::vector<Bound2f>& goal_tiles,
                     const std::vector<Bound2f>& death_tiles)
{
    auto [tile_buffer, dim] = build_matrix_of_tiles(texture);

    add_tiles_to_matrix(tile_buffer, dim.x, dim.y, map_global_pos, init_tiles, TILE::INIT);
    add_tiles_to_matrix(tile_buffer, dim.x, dim.y, map_global_pos, goal_tiles, TILE::GOAL);
    add_tiles_to_matrix(tile_buffer, dim.x, dim.y, map_global_pos, death_tiles, TILE::DEATH);

    add_entities_to_matrix(tile_buffer, dim, map_global_pos, map_entities);

    // If you would like to save non blurred map
    // spaguetti_cooking(tile_buffer, dim);
    // save_as_png("tile_space.png");
    // save_map_as_png("map_tiles.png", tile_buffer, dim);

    Float standar_deviation = 1.5;
    Float skewness = 4.0/3.0;
    Float contrib = skewness > 1.0 ? skewness : 1/skewness;
    unsigned int kernel_size = std::ceil(6*standar_deviation*contrib);
    if(kernel_size % 2 == 0) kernel_size++;

    auto [blurred_map, blurred_dim] = map_blurr(tile_buffer, standar_deviation, skewness, kernel_size, dim);

    spaguetti_cooking(blurred_map, blurred_dim);
    coalesce();

    // Uncomment to save as image
    //save_as_png("tile_space_blurred.png");
    //save_map_as_png("blurred_map_tiles.png", blurred_map, blurred_dim);
}