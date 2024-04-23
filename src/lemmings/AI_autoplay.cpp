#include <vector>
#include <utility>
#include <iostream>
#include "Lemming.hpp"
#include "geometry/point.hpp"


class AI_autoplay
{
    public:

    enum class TILE {
        EMPTY,
        DIRT,
        INIT,
        GOAL
    };

    enum class DIRECTION {
        LEFT,
        RIGHT
    };

    enum class ACTION {
        LEMMING_WALL=3,
        DIG_DOWN=7,
        FALL=8,
        MOVE_LEFT=9,
        MOVE_RIGHT=10,
        SWAP_DIRECTION=11
    };

    using MAP = std::vector<std::vector<TILE>>;
    using uint2 = std::pair<int, int>;

    protected:

    std::vector<ACTION> actions;
    std::vector<uint2> path_coordinates;
    unsigned int ability_charges[8] = {0, 0, 0, 10, 0, 0, 0, 0};

    std::vector<std::vector<TILE>> map1 = 
    {
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::INIT, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::DIRT, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::GOAL, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
    };

    std::vector<std::vector<TILE>> map = 
    {
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::INIT,  TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT,  TILE::DIRT,  TILE::DIRT,  TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT,  TILE::DIRT,  TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT,  TILE::DIRT,  TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::DIRT,  TILE::DIRT,  TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT,  TILE::DIRT,  TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::EMPTY, TILE::GOAL,  TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT,  TILE::DIRT,  TILE::DIRT,  TILE::DIRT,  TILE::EMPTY, TILE::DIRT},
    };

    int n_rows = map.size();
    int n_cols = map[0].size();

    DIRECTION initial_direction = DIRECTION::RIGHT;

    size_t executing_action = 0;

    int n_falled = 0;
    int death_by_fall_tiles = 6;



    public:

    std::string to_string(TILE tile)
    {
        switch (tile)
        {
            case TILE::EMPTY:
                return "EMPTY";
            case TILE::DIRT:
                return "DIRT";
            case TILE::INIT:
                return "INIT";
            case TILE::GOAL:
                return "GOAL";
            default:
                return "UNKNOWN";
        }
    }

    std::string to_string(DIRECTION direction)
    {
        switch (direction)
        {
            case DIRECTION::LEFT:
                return "LEFT";
            case DIRECTION::RIGHT:
                return "RIGHT";
            default:
                return "UNKNOWN";
        }
    }

    std::string to_string(ACTION action)
    {
        switch (action)
        {
            case ACTION::FALL:
                return "FALL";
            case ACTION::DIG_DOWN:
                return "DIG_DOWN";
            case ACTION::MOVE_LEFT:
                return "MOVE_LEFT";
            case ACTION::MOVE_RIGHT:
                return "MOVE_RIGHT";
            case ACTION::SWAP_DIRECTION:
                return "SWAP_DIRECTION";
            case ACTION::LEMMING_WALL:
                return "LEMMING_WALL";
            default:
                return "UNKNOWN";
        }
    }

    AI_autoplay()
    {
        generate_path();
    }

    // Returns true if the current tile is at the border of the map
    bool is_border(uint2& current_tile)
    {
        if (current_tile.first == 0 || current_tile.first == (map.size()-1) || current_tile.second == 0 || current_tile.second == (map[0].size()-1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_fall(uint2& current_tile, DIRECTION direction)
    {
        if (current_tile.first == (map.size()-1)){
            return false;
        }

        if (map[current_tile.first+1][current_tile.second] == TILE::EMPTY
            || map[current_tile.first+1][current_tile.second] == TILE::GOAL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_dig_down(uint2& current_tile, DIRECTION direction)
    {
        if (current_tile.first == (map.size()-1) || ability_charges[(int)ACTION::DIG_DOWN] == 0){
            return false;
        }

        if (map[current_tile.first+1][current_tile.second] == TILE::DIRT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_move_left(uint2& current_tile, DIRECTION direction)
    {
        if (current_tile.second == 0 || direction == DIRECTION::RIGHT){
            return false;
        }

        if (map[current_tile.first][current_tile.second-1] == TILE::EMPTY
            || map[current_tile.first][current_tile.second-1] == TILE::GOAL
            || map[current_tile.first][current_tile.second-1] == TILE::INIT)
            return true;
        else
            return false;
    }

    bool can_move_right(uint2& current_tile, DIRECTION direction)
    {
        if (current_tile.second == (map[0].size()-1) || direction == DIRECTION::LEFT){
            return false;
        }

        if (map[current_tile.first][current_tile.second+1] == TILE::EMPTY
            || map[current_tile.first][current_tile.second+1] == TILE::GOAL
            || map[current_tile.first][current_tile.second+1] == TILE::INIT)
            return true;
        else
            return false;
    }

    bool can_swap_direction(uint2& current_tile, DIRECTION direction)
    {
        if ((direction == DIRECTION::LEFT && current_tile.second == 0)
            || (direction == DIRECTION::RIGHT && current_tile.second == (map[0].size()-1))
            )
        {
            return false;
        }

        // If colliding on the movement direction
        if (
            (direction == DIRECTION::LEFT &&
                map[current_tile.first][current_tile.second-1] == TILE::DIRT)
            ||
            (direction == DIRECTION::RIGHT &&
                map[current_tile.first][current_tile.second+1] == TILE::DIRT)
            ) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_become_wall(uint2& current_tile, DIRECTION direction)
    {
        if (ability_charges[(int)ACTION::LEMMING_WALL] == 0){
            return false;
        }

        if (map[current_tile.first][current_tile.second] == TILE::EMPTY
            && map[current_tile.first+1][current_tile.second] == TILE::DIRT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void apply_action(
            std::vector<ACTION>& l_actions,
            DIRECTION &direction, 
            uint2& current_tile, ACTION action)
    {
        switch (action)
        {
            case ACTION::FALL:
                current_tile.first++;
                l_actions.push_back(ACTION::FALL);
                n_falled++;
                break;
            case ACTION::DIG_DOWN:
                map[current_tile.first+1][current_tile.second] = TILE::EMPTY;
                ability_charges[(int)ACTION::DIG_DOWN]--;
                current_tile.first++;
                l_actions.push_back(ACTION::DIG_DOWN);
                break;
            case ACTION::MOVE_LEFT:
                current_tile.second--;
                l_actions.push_back(ACTION::MOVE_LEFT);
                break;
            case ACTION::MOVE_RIGHT:
                current_tile.second++;
                l_actions.push_back(ACTION::MOVE_RIGHT);
                break;

            case ACTION::SWAP_DIRECTION:
                direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
                l_actions.push_back(ACTION::SWAP_DIRECTION);
                break;

            case ACTION::LEMMING_WALL:
                ability_charges[(int)ACTION::LEMMING_WALL]--;
                direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
                l_actions.push_back(ACTION::LEMMING_WALL);
                break;
            
            default:
                break;
        }
    }

    void undo_action(std::vector<ACTION>& l_actions,
            DIRECTION &direction, 
            uint2& current_tile, ACTION action)
    {
        switch (action)
        {
            case ACTION::FALL:
                current_tile.first--;
                n_falled--;
                break;
            case ACTION::DIG_DOWN:
                map[current_tile.first][current_tile.second] = TILE::DIRT;
                ability_charges[(int)ACTION::DIG_DOWN]++;
                current_tile.first--;
                break;
            case ACTION::MOVE_LEFT:
                current_tile.second++;
                break;
            case ACTION::MOVE_RIGHT:
                current_tile.second--;
                break;
            case ACTION::SWAP_DIRECTION:
                direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
                break;

            case ACTION::LEMMING_WALL:
                ability_charges[(int)ACTION::LEMMING_WALL]++;
                direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
                break;
            default:
                break;
        }
        
        l_actions.pop_back();
    }

    bool add_step(uint2& current_tile, DIRECTION direction)
    {
        if (map[current_tile.first][current_tile.second] == TILE::GOAL) {
            return true;
        }

        if (current_tile.first == (map.size()-1) && map[current_tile.first][current_tile.second] != TILE::GOAL) {
            return false;
        }

        // Death by falling
        if (n_falled == death_by_fall_tiles) {
            return false;
        }

        // If on ground
        if (map[current_tile.first+1][current_tile.second] == TILE::DIRT) {
            n_falled = 0;
        }

        /**************** Mandatory actions *******************/

        if (can_fall(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::FALL);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::FALL);
            
            return false;
        }

        if (can_swap_direction(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::SWAP_DIRECTION);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::SWAP_DIRECTION);
        }



        /**************** Optional actions *******************/

        if (can_dig_down(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::DIG_DOWN);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::DIG_DOWN);
        }

        if (can_move_left(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::MOVE_LEFT);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::MOVE_LEFT);
        }
        
        if (can_move_right(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::MOVE_RIGHT);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::MOVE_RIGHT);
        }

        if (can_become_wall(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::LEMMING_WALL);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::LEMMING_WALL);
        }

        return false;
    }

    uint2 get_init_tile()
    {
        uint2 init_tile;

        for (int i = 0; i < map.size(); i++) {
            for (int j = 0; j < map[i].size(); j++) {
                if (map[i][j] == TILE::INIT) {
                    init_tile = {i, j};
                }
            }
        }

        return init_tile;
    }

    void init_executor()
    {
        executing_action = 0;
    }

    void generate_path()
    {
        uint2 init_tile = get_init_tile();
        actions.clear();
        executing_action = 0;
        actions.push_back(ACTION::FALL);

        bool goal_reached = add_step(init_tile, initial_direction);

        if (goal_reached)
        {
            generate_path_coordinates();

            std::cout << "Goal reached!" << std::endl;

            std::cout << "Actions: ";
            for (auto action : actions) {
                std::cout << to_string(action) << " ";
            }
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Goal not reached!" << std::endl;
        }
    }

    void generate_path_coordinates()
    {
        uint2 current_tile = get_init_tile();
        path_coordinates.clear();
        std::vector<ACTION> l_actions;

        for (auto action : actions)
        {
            path_coordinates.push_back(current_tile);
            apply_action(l_actions, initial_direction, current_tile, action);
        }
    }

    bool execute_action(std::shared_ptr<Lemming> lemming, ACTION action)
    {
        bool performed = false;

        switch (action)
        {
            case ACTION::FALL:
                //lemming->fall();
                performed = true;
                break;
            case ACTION::DIG_DOWN:
                performed = lemming->add_skill(Utils::DIG);
                break;
            case ACTION::MOVE_LEFT:
                //lemming->move_left();
                performed = true;
                break;
            case ACTION::MOVE_RIGHT:
                //lemming->move_right();
                performed = true;
                break;
            case ACTION::SWAP_DIRECTION:
                //lemming->swap_direction();
                performed = true;
                break;
            case ACTION::LEMMING_WALL:
                performed = lemming->add_skill(Utils::BLOCK);
                break;

            default:
                break;
        }

        return performed;
    }

    bool is_executed_by_engine(ACTION action)
    {
        if (action == ACTION::FALL || action == ACTION::SWAP_DIRECTION
            || action == ACTION::MOVE_LEFT || action == ACTION::MOVE_RIGHT)
            return true;
        else
            return false;
    }

    void update_execution(Engine &engine,
            Game_info &game_info,
            EntityPtr e_map,
            std::vector<std::shared_ptr<Lemming>>& lemmings)
    {
        int speed = game_info.get_game_speed();

        while (is_executed_by_engine(actions[executing_action])) {
            executing_action++;
        }

        bool all_walls = true;

        for (auto lemming : lemmings)
        {
            if (!lemming->is_skill(Utils::BLOCK)) {
                all_walls = false;
            }

            auto position = lemming->get_position2D() + lemming->get_diagonal()*0.75f;
            auto l_p = e_map->world_to_local(position);

            std::chrono::time_point<std::chrono::steady_clock> last_falled = lemming->get_last_falling();

            // Offset to adjust tiles
            l_p.x += 0.5f / n_cols;

            Point2f fmap_p (l_p.x * n_cols, l_p.y * n_rows);

            // Round the position to the tile
            uint2 map_p ((unsigned int)fmap_p.y, 
                        (unsigned int)fmap_p.x);

            Float tile_init_x = path_coordinates[executing_action].second * 1.0f / n_cols;
            Float tile_init_y = path_coordinates[executing_action].first * 1.0f / n_rows; 

            Float distance = l_p.x - tile_init_x;
            Float mid_offset = (0.5f / n_cols);
            Float to_center = distance-mid_offset;

            //std::cout << "Map position: " << map_p.first << " " << map_p.second << " " << path_coordinates[executing_action].first << " " << path_coordinates[executing_action].second << std::endl;
            //std::cout << "Distance: " << distance << " " << to_center << " " << lemming_speed.x << " " << tile_init_x << " " << mid_offset << std::endl;
            //std::cout << executing_action << " " << to_string(actions[executing_action]) << " " << to_center << std::endl;

            if (map_p == path_coordinates[executing_action] 
                && 
                (
                    std::abs(to_center) < 0.03f
                    ||
                    // Going out from the block
                    (to_center < 0.0f && lemming->get_direction() == 0)
                    || 
                    (to_center > 0.0f && lemming->get_direction() == 1)
                )
                &&
                // Time since last fall
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_falled).count() > (1000.0f/speed)
                )
            {
                //std::cout << "Executing action: " << to_string(actions[executing_action]) << std::endl;
                if (execute_action(lemming, actions[executing_action]))
                    executing_action++;
                    
                return;
            }
        }

        if (all_walls)
        {
            std::cout << "Level finished\n";
            for (auto lemming : lemmings)
            {
                lemming->add_skill_explode_all();
            }
        }
    }

};