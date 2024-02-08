#include "../engine/Entity.cpp"


class Geralt : public Entity
{
    bool on_ground = false;

    EntityPtr ground;

    public:

    Geralt(Point3f position, Vector2f diagonal, Texture texture)
        : Entity(position, diagonal, texture)
    {
        gravity = 3;
        enable_gravity();
    }

    void update_position(Float delta_time) override
    {
        //std::cout << "direction: " << getDirection() << ", speed: " << getSpeed() << "\n";

        Entity::update_position(delta_time);
    }

    void on_collision(EntityPtr other) override
    {
        if (on_ground && other == ground)
        {
            return;
        }

        // Get out of the other entity
        switch (closest_side(other))
        {
            case 0:
                position.x = other->bound2f().pMin.x - diagonal.x;
                break;
            case 1:
                position.x = other->bound2f().pMax.x;
                break;
            case 2:
                position.y = other->bound2f().pMin.y - diagonal.y;
                break;
            case 3:
                position.y = other->bound2f().pMax.y;
                break;
        }

        // Ground collision
        if (other->bound2f().pMin.y >= bound2f().pMax.y)
        {
            auto direction = getDirection();
            direction.y = 0;
            setDirection(direction);
            
            on_ground = true;
            disable_gravity();
            ground = other;
        }
        else
        {
            setSpeed(0);
            setDirection(Vector2f(0, 0));
        }
    }

    bool jump(Float speed)
    {
        Vector2f direction = getDirection();
        
        if (on_ground)
        {
            direction.y = -1;
            setDirection(direction);

            setSpeed(speed);
            enable_gravity();

            on_ground = false;

            return true;
        }

        return false;
    }

    void pre_physics(Float delta_time) override
    {
    }

    void post_physics(Float delta_time) override
    {
        // Launch ray down to check if we are on ground
    }

    void on_key_down(SDL_KeyboardEvent key) override
    {
        Vector2f old_direction = getDirection();

        if (key.keysym.sym == SDLK_UP)
        {
            jump(1);
        }
        else if (key.keysym.sym == SDLK_DOWN)
        {
            if (!on_ground)
            {
                old_direction.y = 1;
                setDirection(old_direction);
                setSpeed(getSpeed()+0.3);
            }
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {
            old_direction.x = -1;
            setDirection(old_direction);
            setSpeed(0.3);
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            old_direction.x = 1;
            setDirection(old_direction);
            setSpeed(0.3);
        }
    }

    void on_key_up(SDL_KeyboardEvent key) override
    {
        Vector2f old_direction = getDirection();

        if (key.keysym.sym == SDLK_DOWN)
        {
            old_direction.y = 0;
            setDirection(old_direction);
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {      
            old_direction.x = 0;
            setDirection(old_direction);
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            old_direction.x = 0;
            setDirection(old_direction);
        }
    }
};

void swap(Entity &a, Entity &b)
{
    Entity temp = a;
    a = b;
    b = temp;
}
