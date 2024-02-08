#include "../engine/Entity.cpp"
#include "../engine/Render_2D.cpp"


class Geralt : public Entity
{
    bool on_ground = false;
    Texture txt_left, txt_right;

    EntityPtr ground;

    public:

    Geralt(Point3f position, Vector2f diagonal, Render_2D &render)
        : Entity(position, diagonal, render.loadTexture("assets/geralt_right.png"))
    {
        gravity = 3;
        enable_gravity();

        txt_left = render.loadTexture("assets/geralt_left.png");
        txt_right = render.loadTexture("assets/geralt_right.png");
    }

    void update_position(Float delta_time) override
    {
        //std::cout << "direction: " << getSpeed() << "\n";

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
            setSpeedY(0);

            on_ground = true;
            disable_gravity();
            ground = other;
        }
        else
        {
            setSpeed(Vector2f(0, 0));
        }
    }

    bool jump(Float new_speed)
    {
        Vector2f speed = getSpeed();

        if (on_ground)
        {
            speed.y = -1;

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

    void look_left()
    {
        setActiveTexture(txt_left);
    }

    void look_right()
    {
        setActiveTexture(txt_right);
    }

    void on_key_down(SDL_KeyboardEvent key) override
    {
        Vector2f old_speed = getSpeed();

        if (key.keysym.sym == SDLK_UP)
        {
            jump(1);
            return;
        }
        else if (key.keysym.sym == SDLK_DOWN)
        {
            if (!on_ground)
            {
                old_speed.y = old_speed.y + 0.3;
            }
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {
            look_left();
            old_speed.x = -0.3;
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            look_right();
            old_speed.x = 0.3;
        }

        setSpeed(old_speed);
    }

    void on_key_up(SDL_KeyboardEvent key) override
    {
        Vector2f old_speed = getSpeed();

        if (key.keysym.sym == SDLK_DOWN)
        {
            old_speed.y = 0;
        }
        else if (key.keysym.sym == SDLK_LEFT)
        {      
            old_speed.x = 0;
        }
        else if (key.keysym.sym == SDLK_RIGHT)
        {
            old_speed.x = 0;
        }

        setSpeed(old_speed);
    }
};

void swap(Entity &a, Entity &b)
{
    Entity temp = a;
    a = b;
    b = temp;
}
