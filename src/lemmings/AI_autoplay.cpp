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
        FALL,
        DIG_DOWN,
        MOVE_LEFT,
        MOVE_RIGHT,
        SWAP_DIRECTION
    };

    using MAP = std::vector<std::vector<TILE>>;
    using uint2 = std::pair<int, int>;

    protected:

    std::vector<ACTION> actions;
    std::vector<uint2> path_coordinates;

    std::vector<std::vector<TILE>> map = 
    {
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::INIT, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::GOAL, TILE::DIRT, TILE::EMPTY},
        {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
    };

    int n_rows = map.size();
    int n_cols = map[0].size();

    DIRECTION initial_direction = DIRECTION::RIGHT;

    size_t executing_action = 0;



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
        if (current_tile.first == (map.size()-1)){
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
            || map[current_tile.first][current_tile.second-1] == TILE::GOAL)
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
            || map[current_tile.first][current_tile.second+1] == TILE::GOAL)
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
                break;
            case ACTION::DIG_DOWN:
                map[current_tile.first+1][current_tile.second] = TILE::EMPTY;
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
                l_actions.pop_back();
                break;
            case ACTION::DIG_DOWN:
                map[current_tile.first][current_tile.second] = TILE::DIRT;
                current_tile.first--;
                l_actions.pop_back();
                break;
            case ACTION::MOVE_LEFT:
                current_tile.second++;
                l_actions.pop_back();
                break;
            case ACTION::MOVE_RIGHT:
                current_tile.second--;
                l_actions.pop_back();
                break;
            case ACTION::SWAP_DIRECTION:
                direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
                l_actions.pop_back();
                break;
            default:
                break;
        }
    }

    bool add_step(uint2& current_tile, DIRECTION direction)
    {
        if (map[current_tile.first][current_tile.second] == TILE::GOAL) {
            return true;
        }

        if (current_tile.first == (map.size()-1) && map[current_tile.first][current_tile.second] != TILE::GOAL) {
            return false;
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

    void generate_path()
    {
        uint2 init_tile = get_init_tile();
        actions.clear();
        executing_action = 0;

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
            default:
                break;
        }

        return performed;
    }

    void update_execution(Engine &engine,
            EntityPtr e_map,
            std::vector<std::shared_ptr<Lemming>>& lemmings)
    {
        for (auto lemming : lemmings)
        {
            auto position = lemming->get_position2D();
            auto l_p = e_map->world_to_local(position);
            Point2f fmap_p (l_p.x * n_cols, l_p.y * n_rows);

            // Round the position to the tile
            uint2 map_p ((unsigned int)fmap_p.y, 
                        (unsigned int)fmap_p.x);
            
            //std::cout << "Expected: " << path_coordinates[executing_action].first << " " << path_coordinates[executing_action].second << std::endl;
            if (map_p == path_coordinates[executing_action])
            {
                std::cout << "Executing action: " << to_string(actions[executing_action]) << std::endl;
                if (execute_action(lemming, actions[executing_action]))
                    executing_action++;
                    
                return;
            }
        }
    }

};