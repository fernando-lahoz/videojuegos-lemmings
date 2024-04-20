#include <iostream>
#include <vector>
#include <utility>



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

// Returns true if the current tile is at the border of the map
bool is_border(MAP& map, uint2& current_tile)
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

bool can_fall(MAP& map, uint2& current_tile, DIRECTION direction)
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

bool can_dig_down(MAP& map, uint2& current_tile, DIRECTION direction)
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

bool can_move_left(MAP& map, uint2& current_tile, DIRECTION direction)
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

bool can_move_right(MAP& map, uint2& current_tile, DIRECTION direction)
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

bool can_swap_direction(MAP& map, uint2& current_tile, DIRECTION direction)
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

void apply_action(MAP& map, 
        std::vector<ACTION>& actions, 
        DIRECTION &direction, 
        uint2& current_tile, ACTION action)
{
    switch (action)
    {
        case ACTION::FALL:
            current_tile.first++;
            actions.push_back(ACTION::FALL);
            break;
        case ACTION::DIG_DOWN:
            map[current_tile.first+1][current_tile.second] = TILE::EMPTY;
            current_tile.first++;
            actions.push_back(ACTION::DIG_DOWN);
            break;
        case ACTION::MOVE_LEFT:
            current_tile.second--;
            actions.push_back(ACTION::MOVE_LEFT);
            break;
        case ACTION::MOVE_RIGHT:
            current_tile.second++;
            actions.push_back(ACTION::MOVE_RIGHT);
            break;

        case ACTION::SWAP_DIRECTION:
            direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
            actions.push_back(ACTION::SWAP_DIRECTION);
            break;
        
        default:
            break;
    }
}

void undo_action(MAP& map, std::vector<ACTION>& actions, 
        DIRECTION &direction, uint2& current_tile, ACTION action)
{
    switch (action)
    {
        case ACTION::FALL:
            current_tile.first--;
            actions.pop_back();
            break;
        case ACTION::DIG_DOWN:
            map[current_tile.first][current_tile.second] = TILE::DIRT;
            current_tile.first--;
            actions.pop_back();
            break;
        case ACTION::MOVE_LEFT:
            current_tile.second++;
            actions.pop_back();
            break;
        case ACTION::MOVE_RIGHT:
            current_tile.second--;
            actions.pop_back();
            break;
        case ACTION::SWAP_DIRECTION:
            direction = (direction == DIRECTION::LEFT) ? DIRECTION::RIGHT : DIRECTION::LEFT;
            actions.pop_back();
            break;
        default:
            break;
    }
}

bool add_step(MAP& map, uint2& current_tile, DIRECTION direction, std::vector<ACTION>& actions)
{
    if (map[current_tile.first][current_tile.second] == TILE::GOAL) {
        return true;
    }

    if (current_tile.first == (map.size()-1) && map[current_tile.first][current_tile.second] != TILE::GOAL) {
        return false;
    }

    /**************** Mandatory actions *******************/

    if (can_fall(map, current_tile, direction))
    {
        apply_action(map, actions, 
                direction, current_tile, ACTION::FALL);

        if (add_step(map, current_tile, direction, actions))
            return true;

        undo_action(map, actions, 
                direction, current_tile, ACTION::FALL);

        return false;
    }

    if (can_swap_direction(map, current_tile, direction))
    {
        apply_action(map, actions, 
                direction, current_tile, ACTION::SWAP_DIRECTION);

        if (add_step(map, current_tile, direction, actions))
            return true;

        undo_action(map, actions, 
                direction, current_tile, ACTION::SWAP_DIRECTION);
    }



    /**************** Optional actions *******************/

    if (can_dig_down(map, current_tile, direction))
    {
        apply_action(map, actions, 
                direction, current_tile, ACTION::DIG_DOWN);

        if (add_step(map, current_tile, direction, actions))
            return true;

        undo_action(map, actions, 
                direction, current_tile, ACTION::DIG_DOWN);
    }

    if (can_move_left(map, current_tile, direction))
    {
        apply_action(map, actions, 
                direction, current_tile, ACTION::MOVE_LEFT);

        if (add_step(map, current_tile, direction, actions))
            return true;

        undo_action(map, actions, 
                direction, current_tile, ACTION::MOVE_LEFT);
    }
    
    if (can_move_right(map, current_tile, direction))
    {
        apply_action(map, actions, 
                direction, current_tile, ACTION::MOVE_RIGHT);

        if (add_step(map, current_tile, direction, actions))
            return true;

        undo_action(map, actions, 
                direction, current_tile, ACTION::MOVE_RIGHT);
    }

    return false;
}


int main() {
    
    using uint2 = std::pair<int, int>;

    std::vector<ACTION> actions;

    std::vector<std::vector<TILE>> map = 
    {
        {TILE::DIRT, TILE::INIT, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
        {TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
        {TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT},
        {TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::EMPTY, TILE::DIRT},
        {TILE::DIRT, TILE::EMPTY, TILE::EMPTY, TILE::GOAL, TILE::DIRT},
        {TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT, TILE::DIRT}
    };

    uint2 init_tile;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == TILE::INIT) {
                init_tile = {i, j};
            }
        }
    }

    DIRECTION initial_direction = DIRECTION::RIGHT;

    bool goal_reached = add_step(map, init_tile, initial_direction, actions);

    if (goal_reached)
    {
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

    return 0;
}


