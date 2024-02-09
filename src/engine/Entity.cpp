#pragma once

#include "../geometry/Vector.cpp"
#include "../geometry/Point.cpp"
#include "../geometry/BoundingBox.cpp"
#include "../lib/Spectrum.cpp"
#include "../lib/Pair.cpp"
#include "../lib/Texture.cpp"

#include <memory>

class Entity
{
    private:
    Texture active_texture;
    Vector2f speed;
    Float max_speed_sqr;
    Float max_speed;

    protected:

    bool _has_gravity = false;
    Float gravity = 0;

    Point3f position;
    Vector2f diagonal;


    public:

    Entity(Point3f position, Vector2f diagonal, Texture texture, Float _max_speed=1.5)
    {
        this->position = position;
        this->diagonal = diagonal;
        this->active_texture = texture;
        this->max_speed = _max_speed;
        this->max_speed_sqr = pow2(_max_speed);

        speed = Vector2f(0, 0);
    }

    Point2f getPosition2D() const
    {
        return Point2f(position.x, position.y);
    }

    Point3f getPosition3D() const
    {
        return position;
    }

    void setPosition2D(Point2f p)
    {
        position.x = p.x;
        position.y = p.y;
    }

    void setPosition3D(Point3f p)
    {
        position = p;
    }

    Point2f maxCorner2D() const
    {
        return getPosition2D() + diagonal;
    }

    Point3f maxCorner3D() const
    {
        auto maxCorner = maxCorner2D();
        return Point3f(maxCorner.x, maxCorner.y, position.z);
    }

    Bound2f bound2f() const
    {
        return Bound2f(getPosition2D(), maxCorner2D());
    }

    Texture getActiveTexture() const
    {
        return active_texture;
    }

    void setActiveTexture(Texture new_texture)
    {
        active_texture = new_texture;
    }

    // Moves the entity speed*delta_time units
    //  in the direction vector
    virtual void update_position(Float delta_time)
    {
        if (has_gravity())
        {
            update_speed_gravity(gravity, delta_time);
        }

        if (speed.lengthSquared() > max_speed_sqr)
        {
            speed = normalize(speed) * max_speed;
        }
        
        position.x += speed.x * delta_time;
        position.y += speed.y * delta_time;
    }

    void set_gravity(Float new_gravity)
    {
        this->gravity = new_gravity;
    }

    void enable_gravity()
    {
        _has_gravity = true;
    }

    void disable_gravity()
    {
        _has_gravity = false;
    }

    bool has_gravity() const
    {
        return _has_gravity;
    }

    Vector2f getSpeed() const
    {
        return speed;
    }

    void setSpeed(Vector2f new_speed)
    {
        speed = new_speed;
    }

    void setSpeedX(Float new_x_speed)
    {
        speed.x = new_x_speed;
    }

    void setSpeedY(Float new_y_speed)
    {
        speed.y = new_y_speed;
    }

    // Returns true if this entity collides with other
    //  uses excusive comparisons
    bool collides(std::shared_ptr<Entity> other) const
    {
        return bound2f().overlaps(other->bound2f());
    }

    void update_speed_gravity(Float gravity, Float delta_time)
    {
        auto speed = getSpeed();
        speed.y += gravity * delta_time;
        setSpeed(speed);
    }

    // Returns the side of this entity that is closest to other
    // 0: right
    // 1: left
    // 2: up
    // 3: down
    int closest_side(std::shared_ptr<Entity> other)
    {
        Float distance_right = other->bound2f().pMax.x - bound2f().pMin.x;
        Float distance_left = bound2f().pMax.x - other->bound2f().pMin.x;
        Float distance_up = bound2f().pMax.y - other->bound2f().pMin.y;
        Float distance_down = other->bound2f().pMax.y - bound2f().pMin.y;

        Float min_distance = std::min({distance_right, distance_left, distance_up, distance_down});

        if (min_distance == distance_right)
        {
            return 0;
        }
        else if (min_distance == distance_left)
        {
            return 1;
        }
        else if (min_distance == distance_up)
        {
            return 2;
        }
        else // Down
        {
            return 3;
        }
    }

    virtual void on_key_down(SDL_KeyboardEvent key)
    {
        // Do nothing by default
    }

    virtual void on_key_up(SDL_KeyboardEvent key)
    {
        // Do nothing by default
    }

    virtual void on_collision(std::shared_ptr<Entity> other)
    {
        // Do nothing by default
    }

    virtual void pre_physics(Float delta_time)
    {
        // Do nothing by default
    }

    virtual void post_physics(Float delta_time)
    {
        // Do nothing by default
    }
};


typedef std::shared_ptr<Entity> EntityPtr;