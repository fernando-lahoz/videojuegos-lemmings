#include "../engine/Entity.cpp"

class Geralt : public Entity
{
    bool on_ground = false;
    EntityPtr ground;

    public:

    Geralt(Point3f position, Vector2f diagonal, Texture texture)
        : Entity(position, diagonal, texture)
    {
        speed = 0.3;
        activate_gravity();
    }

    void on_collision(EntityPtr other) override
    {
        speed = 0;

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
            on_ground = true;
            deactivate_gravity();
            ground = other;
        }
    }

    bool jump(Vector2f direction, Float speed)
    {
        if (on_ground)
        {
            setSpeed(speed);
            setDirection(direction);
            on_ground = false;

            return true;
        }

        return false;
    }

    void pre_physics(Float delta_time) override
    {
        if (on_ground)
        {
            speed = 0;
        }
    }

    void post_physics(Float delta_time) override
    {
        if (on_ground)
        {
            // Check down distance with the ground
            Float ground_distance = ground->bound2f().pMin.y - bound2f().pMax.y;
            if (ground_distance > 0.01)
            {
                on_ground = false;
                activate_gravity();
            }
        }
    }

    void on_key_down(SDL_KeyboardEvent key) override
    {
        if (key.keysym.sym == SDLK_UP)
        {
            jump(Vector2f(0, -1), 1);
        }
        else if (key.keysym.sym == SDLK_DOWN)
        {
            setSpeed(0.3);
            setDirection(Vector2f(0, 1));
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {
            setSpeed(0.3);
            setDirection(Vector2f(-1, 0));
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            setSpeed(0.3);
            setDirection(Vector2f(1, 0));
        }
    }
};

void swap(Entity &a, Entity &b)
{
    Entity temp = a;
    a = b;
    b = temp;
}
