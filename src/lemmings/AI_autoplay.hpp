#pragma once

#include <vector>
#include <utility>
#include <iostream>
#include "lemmings/Lemming.hpp"
#include "geometry/point.hpp"
#include "engine/physics.hpp"
#include "lemmings/AI/tile_space.hpp"

class AI_autoplay
{
public:
    enum class TILE
    {
        EMPTY,
        DIRT,
        INIT,
        GOAL,
        BRIDGE,
        METAL,
        DIRECTIONAL_RIGHT,
        DIRECTIONAL_LEFT
    };

    enum class DIRECTION
    {
        LEFT,
        RIGHT
    };

    enum class ACTION
    {
        LEMMING_WALL = 3,
        BUILD = 4,
        DIG_STRAIGHT = 5,
        DIG_DOWN = 7,
        FALL = 8,
        MOVE_LEFT = 9,
        MOVE_RIGHT = 10,
        SWAP_DIRECTION = 11
    };

    using MAP = std::vector<std::vector<TILE>>;
    using uint2 = std::pair<int, int>;

protected:
    std::vector<ACTION> actions;
    std::vector<uint2> path_coordinates;

    std::vector<std::vector<TILE>> map1 =
        {
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::INIT, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::GOAL, TILE::DIRT, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
    };

    std::vector<std::vector<TILE>> map3 =
        {
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::INIT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::EMPTY, TILE::GOAL, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
            {TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY},
    };

    std::vector<std::vector<TILE>> map11 =
        {
            {TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
            {TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
            {TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
            {TILE::DIRT, TILE::EMPTY, TILE::INIT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
            {TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::GOAL, TILE::EMPTY, TILE::DIRT, TILE::DIRT},
            {TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
            {TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::EMPTY, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
    };

    unsigned int ability_charges1[8] = {0, 0, 0, 0, 0, 0, 0, 1};
    unsigned int ability_charges3[8] = {0, 0, 0, 10, 0, 0, 0, 0};
    unsigned int ability_charges11[8] = {0, 0, 0, 0, 10, 1, 0, 0};
    unsigned int ability_charges[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    std::vector<std::vector<TILE>> map_original = map11;
    std::vector<std::vector<TILE>> map = map_original;

    bool ground_padding = true;

    int n_rows = map.size();
    int n_cols = map[0].size();

    DIRECTION initial_direction = DIRECTION::RIGHT;

    size_t executing_action = 0;

    int n_falled = 0;
    int death_by_fall_tiles = 6;
    int bob_the_builder = -1;

    bool active_ai = false;

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
        case TILE::BRIDGE:
            return "BRIDGE";
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
        case ACTION::BUILD:
            return "BUILD";
        case ACTION::DIG_STRAIGHT:
            return "DIG_STRAIGHT";
        default:
            return "UNKNOWN";
        }
    }

    AI_autoplay()
    {
    }

    // Returns true if the current tile is at the border of the map
    bool is_border(uint2 &current_tile)
    {
        if (current_tile.first == 0 || current_tile.first == (map.size() - 1) || current_tile.second == 0 || current_tile.second == (map[0].size() - 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_fall(uint2 &current_tile, DIRECTION)
    {
        if (current_tile.first == (map.size() - 1))
        {
            return false;
        }

        if (map[current_tile.first + 1][current_tile.second] == TILE::EMPTY || map[current_tile.first + 1][current_tile.second] == TILE::GOAL)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_dig_down(uint2 &current_tile, DIRECTION)
    {
        if (current_tile.first == (map.size() - 1) || ability_charges[(int)ACTION::DIG_DOWN] == 0)
        {
            return false;
        }

        if (map[current_tile.first + 1][current_tile.second] == TILE::DIRT || map[current_tile.first + 1][current_tile.second] == TILE::BRIDGE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_move_left(uint2 &current_tile, DIRECTION direction)
    {
        if (current_tile.second == 0 || direction == DIRECTION::RIGHT || map[current_tile.first + 1][current_tile.second - 1] == TILE::BRIDGE)
        {
            return false;
        }

        if (map[current_tile.first][current_tile.second - 1] == TILE::EMPTY || map[current_tile.first][current_tile.second - 1] == TILE::GOAL || map[current_tile.first][current_tile.second - 1] == TILE::INIT ||
            (map[current_tile.first - 1][current_tile.second - 1] == TILE::EMPTY && map[current_tile.first][current_tile.second - 1] == TILE::DIRT))
            return true;
        else
            return false;
    }

    bool can_move_right(uint2 &current_tile, DIRECTION direction)
    {
        if (current_tile.second == (map[0].size() - 1) || direction == DIRECTION::LEFT || map[current_tile.first + 1][current_tile.second + 1] == TILE::BRIDGE)
        {
            return false;
        }

        if (map[current_tile.first][current_tile.second + 1] == TILE::EMPTY || map[current_tile.first][current_tile.second + 1] == TILE::GOAL || map[current_tile.first][current_tile.second + 1] == TILE::INIT ||
            (map[current_tile.first - 1][current_tile.second + 1] == TILE::EMPTY && map[current_tile.first][current_tile.second + 1] == TILE::DIRT))
            return true;
        else
            return false;
    }

    bool can_swap_direction(uint2 &current_tile, DIRECTION direction)
    {
        if ((direction == DIRECTION::LEFT && current_tile.second == 0) || (direction == DIRECTION::RIGHT && current_tile.second == (map[0].size() - 1)))
        {
            return false;
        }

        // If colliding on the movement direction
        if ((
                direction == DIRECTION::LEFT &&
                map[current_tile.first][current_tile.second - 1] == TILE::DIRT &&
                map[current_tile.first - 1][current_tile.second - 1] == TILE::DIRT) ||
            (direction == DIRECTION::RIGHT &&
             map[current_tile.first][current_tile.second + 1] == TILE::DIRT &&
             map[current_tile.first - 1][current_tile.second + 1] == TILE::DIRT))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_become_wall(uint2 &current_tile, DIRECTION)
    {
        if (ability_charges[(int)ACTION::LEMMING_WALL] == 0)
        {
            return false;
        }

        if (map[current_tile.first][current_tile.second] == TILE::EMPTY && map[current_tile.first + 1][current_tile.second] == TILE::DIRT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_build(uint2 &current_tile, DIRECTION direction)
    {
        if (ability_charges[(int)ACTION::BUILD] == 0 || current_tile.first == (map.size() - 1))
        {
            return false;
        }

        int offset = (direction == DIRECTION::LEFT) ? -1 : 1;

        if (
            (
                map[current_tile.first + 1][current_tile.second] == TILE::DIRT ||
                map[current_tile.first + 1][current_tile.second] == TILE::BRIDGE) &&
            map[current_tile.first][current_tile.second + offset] != TILE::DIRT && map[current_tile.first + 1][current_tile.second + offset] != TILE::BRIDGE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool can_dig_straight(uint2 &current_tile, DIRECTION direction)
    {
        if (ability_charges[(int)ACTION::DIG_STRAIGHT] == 0)
        {
            return false;
        }

        int offset = (direction == DIRECTION::LEFT) ? -1 : 1;

        if (map[current_tile.first][current_tile.second + offset] == TILE::DIRT)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void apply_action(
        std::vector<ACTION> &l_actions,
        DIRECTION &direction,
        uint2 &current_tile, ACTION action)
    {
        int dir_offset = (direction == DIRECTION::LEFT) ? -1 : 1;

        switch (action)
        {
        case ACTION::FALL:
            current_tile.first++;
            l_actions.push_back(ACTION::FALL);
            n_falled++;
            break;
        case ACTION::DIG_DOWN:
            map[current_tile.first + 1][current_tile.second] = TILE::EMPTY;
            ability_charges[(int)ACTION::DIG_DOWN]--;
            current_tile.first++;
            l_actions.push_back(ACTION::DIG_DOWN);
            break;
        case ACTION::MOVE_LEFT:
            current_tile.second--;

            if (map[current_tile.first][current_tile.second] == TILE::DIRT &&
                map[current_tile.first - 1][current_tile.second] == TILE::EMPTY)
                current_tile.first--;

            l_actions.push_back(ACTION::MOVE_LEFT);
            break;
        case ACTION::MOVE_RIGHT:
            current_tile.second++;

            if (map[current_tile.first][current_tile.second] == TILE::DIRT &&
                map[current_tile.first - 1][current_tile.second] == TILE::EMPTY)
                current_tile.first--;

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

        case ACTION::BUILD:
            ability_charges[(int)ACTION::BUILD]--;

            if (map[current_tile.first + 1][current_tile.second + dir_offset] == TILE::EMPTY)
                map[current_tile.first + 1][current_tile.second + dir_offset] = TILE::BRIDGE;

            current_tile.second += dir_offset;
            l_actions.push_back(ACTION::BUILD);
            break;

        case ACTION::DIG_STRAIGHT:
            ability_charges[(int)ACTION::DIG_STRAIGHT]--;
            map[current_tile.first][current_tile.second + dir_offset] = TILE::EMPTY;
            current_tile.second += dir_offset;
            l_actions.push_back(ACTION::DIG_STRAIGHT);
            break;

        default:
            break;
        }
    }

    void undo_action(std::vector<ACTION> &l_actions,
                     DIRECTION &direction,
                     uint2 &current_tile, ACTION action)
    {
        int dir_offset = (direction == DIRECTION::LEFT) ? -1 : 1;

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

            if (map[current_tile.first + 1][current_tile.second] == TILE::EMPTY)
                current_tile.first++;

            break;
        case ACTION::MOVE_RIGHT:
            current_tile.second--;

            if (map[current_tile.first + 1][current_tile.second] == TILE::EMPTY)
                current_tile.first++;

            break;
        case ACTION::SWAP_DIRECTION:
            direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
            break;

        case ACTION::LEMMING_WALL:
            ability_charges[(int)ACTION::LEMMING_WALL]++;
            direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
            break;

        case ACTION::BUILD:
            ability_charges[(int)ACTION::BUILD]++;

            if (map[current_tile.first + 1][current_tile.second] == TILE::BRIDGE)
                map[current_tile.first + 1][current_tile.second] = TILE::EMPTY;

            current_tile.second -= dir_offset;

            break;

        case ACTION::DIG_STRAIGHT:
            ability_charges[(int)ACTION::DIG_STRAIGHT]++;
            map[current_tile.first][current_tile.second] = TILE::DIRT;

            current_tile.second -= dir_offset;

            break;

        default:
            break;
        }

        l_actions.pop_back();
    }

    bool add_step(uint2 &current_tile, DIRECTION direction)
    {
        if (map[current_tile.first][current_tile.second] == TILE::GOAL)
        {
            return true;
        }

        if (current_tile.first == (map.size() - 1) && map[current_tile.first][current_tile.second] != TILE::GOAL)
        {
            return false;
        }

        // Death by falling
        if (n_falled == death_by_fall_tiles)
        {
            return false;
        }

        // If on ground
        if (map[current_tile.first + 1][current_tile.second] == TILE::DIRT)
        {
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

        // Has to go before swap direction
        if (can_dig_straight(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::DIG_STRAIGHT);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::DIG_STRAIGHT);
        }

        if (can_swap_direction(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::SWAP_DIRECTION);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::SWAP_DIRECTION);

            return false;
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

        if (can_build(current_tile, direction))
        {
            apply_action(actions, direction, current_tile, ACTION::BUILD);

            if (add_step(current_tile, direction))
                return true;

            undo_action(actions, direction, current_tile, ACTION::BUILD);
        }

        return false;
    }

    uint2 get_init_tile()
    {
        uint2 init_tile;

        for (size_t i = 0; i < map.size(); i++)
        {
            for (size_t j = 0; j < map[i].size(); j++)
            {
                if (map[i][j] == TILE::INIT)
                {
                    init_tile = {i, j};
                }
            }
        }

        return init_tile;
    }

    void init_executor(int level_id)
    {
        if (level_id == -1)
        {
            active_ai = false;
            return;
        }
        else
        {
            active_ai = true;
        }

        executing_action = 0;
        bob_the_builder = -1;
        initial_direction = DIRECTION::RIGHT;

        if (level_id == 1)
        {
            map = map1;
            map_original = map1;

            for (int i = 0; i < 8; i++)
            {
                ability_charges[i] = ability_charges1[i];
            }
        }
        else if (level_id == 3)
        {
            map = map3;
            map_original = map3;

            for (int i = 0; i < 8; i++)
            {
                ability_charges[i] = ability_charges3[i];
            }
        }
        else if (level_id == 11)
        {
            map = map11;
            map_original = map11;

            for (int i = 0; i < 8; i++)
            {
                ability_charges[i] = ability_charges11[i];
            }
        }

        generate_path();
    }

    void generate_path()
    {
        uint2 init_tile = get_init_tile();
        actions.clear();
        executing_action = 0;

        map = map_original;
        bool goal_reached = add_step(init_tile, initial_direction);

        if (goal_reached)
        {
            map = map_original;
            generate_path_coordinates();

            // std::cout << "Goal reached!" << std::endl;

            // std::cout << "Actions: ";
            // for (auto action : actions) {
            //     std::cout << to_string(action) << " ";
            // }
            // std::cout << std::endl;
        }
        else
        {
            std::cout << "WARNING: AI did not found a solution for the level" << std::endl;
        }
    }

    void generate_path_coordinates()
    {
        uint2 current_tile = get_init_tile();
        path_coordinates.clear();
        std::vector<ACTION> l_actions;

        for (auto action : actions)
        {
            uint2 tile_coords = current_tile;

            path_coordinates.push_back(tile_coords);
            apply_action(l_actions, initial_direction, current_tile, action);
        }
    }

    bool execute_action(std::shared_ptr<Lemming> lemming, ACTION action)
    {
        bool performed = false;

        switch (action)
        {
        case ACTION::FALL:
            // lemming->fall();
            performed = true;
            break;
        case ACTION::DIG_DOWN:
            performed = lemming->add_skill(Utils::DIG);
            break;
        case ACTION::MOVE_LEFT:
            // lemming->move_left();
            performed = true;
            break;
        case ACTION::MOVE_RIGHT:
            // lemming->move_right();
            performed = true;
            break;
        case ACTION::SWAP_DIRECTION:
            // lemming->swap_direction();
            performed = true;
            break;
        case ACTION::LEMMING_WALL:
            performed = lemming->add_skill(Utils::BLOCK);
            break;

        case ACTION::BUILD:
            performed = lemming->add_skill(Utils::BUILD);
            break;

        case ACTION::DIG_STRAIGHT:
            performed = lemming->add_skill(Utils::BASH);
            break;

        default:
            break;
        }

        return performed;
    }

    bool is_executed_by_engine(ACTION action)
    {
        if (action == ACTION::FALL || action == ACTION::SWAP_DIRECTION || action == ACTION::MOVE_LEFT || action == ACTION::MOVE_RIGHT)
            return true;
        else
            return false;
    }

    void update_execution(Engine &engine,
                          Game_info &game_info,
                          EntityPtr e_map,
                          std::vector<std::shared_ptr<Lemming>> &lemmings)
    {
        if (!active_ai)
            return;

        int speed = game_info.get_game_speed();

        while (is_executed_by_engine(actions[executing_action]))
        {
            executing_action++;
        }

        bool all_walls = true;

        int l_n_rows = map.size();
        int l_n_cols = map[0].size();

        if (ground_padding)
            l_n_rows--;

        for (int i = 0; i < lemmings.size(); i++)
        {
            auto lemming = lemmings[i];

            if (lemming->is_deleted())
                continue;

            if (!lemming->is_skill(Utils::BLOCK))
            {
                all_walls = false;
            }

            auto position = lemming->get_position2D() + lemming->get_diagonal() * 0.75f;
            auto l_p = e_map->world_to_local(position);

            std::chrono::time_point<std::chrono::steady_clock> last_falled = lemming->get_last_falling();

            Point2f fmap_p(l_p.x * l_n_cols, l_p.y * l_n_rows);

            // Round the position to the tile
            uint2 map_p((unsigned int)fmap_p.y,
                        (unsigned int)fmap_p.x);

            Float tile_init_x = path_coordinates[executing_action].second * 1.0f / l_n_cols;
            // Float tile_init_y = path_coordinates[executing_action].first * 1.0f / l_n_rows;

            Float distance = l_p.x - tile_init_x;
            Float mid_offset = (0.5f / l_n_cols);
            Float to_center = distance - mid_offset;

            // std::cout << "Map position: " << map_p.first << " " << map_p.second << " " << path_coordinates[executing_action].first << " " << path_coordinates[executing_action].second << std::endl;
            // std::cout << executing_action << " " << to_string(actions[executing_action]) << " " << to_center << " " << lemming->get_direction() << std::endl;

            if (map_p == path_coordinates[executing_action] &&
                actions[executing_action] != ACTION::BUILD &&
                actions[executing_action] != ACTION::DIG_STRAIGHT &&
                (std::abs(to_center) < 0.03f ||
                 // Going out from the block
                 (to_center < 0.0f && lemming->get_direction() == -1) ||
                 (to_center > 0.0f && lemming->get_direction() == 1)) &&
                // Time since last fall
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - last_falled).count() > (1000.0f / speed))
            {

                // std::cout << "Executing action: " << to_string(actions[executing_action]) << std::endl;
                if (execute_action(lemming, actions[executing_action]))
                    executing_action++;

                return;
            }
            else if (actions[executing_action] == ACTION::DIG_STRAIGHT)
            {
                if (lemming->get_state() != Utils::Lemming_State::WALKING)
                {
                    continue;
                }

                // Check if there is a wall close
                Bound2f lemming_bound = lemming->bound2f();
                lemming_bound.pMin.x = lemming_bound.pMax.x - 15;
                lemming_bound.pMax.x = lemming_bound.pMax.x - 10;
                lemming_bound.pMin.y -= 30;
                lemming_bound.pMax.y -= 30;

                if (Physics_engine::alpha_box_collision(*e_map, lemming_bound))
                {
                    if (execute_action(lemming, actions[executing_action]))
                        executing_action++;
                }
            }
            else if (actions[executing_action] == ACTION::BUILD)
            {
                // If the lemming is in the building tile
                //  (check only x, as the AI does not know that building goes up)
                if (map_p.second == path_coordinates[executing_action].second && bob_the_builder == -1)
                {
                    bob_the_builder = i;
                }

                if (bob_the_builder == i)
                {
                    // Check if bob is inside the tile
                    if (map_p.second == path_coordinates[executing_action].second)
                    {
                        // Bob begins or continues building
                        if (!lemming->is_skill(Utils::BUILD))
                            execute_action(lemming, actions[executing_action]);
                    }
                    else
                    {
                        // Bob has finished building in the tile
                        executing_action++;
                        bob_the_builder = -1;
                    }

                    return;
                }
            }
        }

        if (all_walls)
        {
            if (!game_info.get_all_die() && lemmings.size() > 0)
            {
                game_info.set_spawn_ended();
                game_info.set_all_die(true);
                for (auto lemming : lemmings)
                {
                    lemming->set_dead_marked(true);
                }
                engine.get_sound_mixer().play_sound(game_info.get_sound_asset(Game_info::OH_NO_SOUND), game_info.get_effects_volume());
            }
        }
    }
};