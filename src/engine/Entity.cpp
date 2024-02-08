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
    protected:

    Point3f position;
    Vector2f diagonal;
    Texture texture;

    Vector2f direction;
    Float speed;

    bool _has_gravity = false;

    public:

    Entity(Point3f position, Vector2f diagonal, Texture texture)
    {
        this->position = position;
        this->diagonal = diagonal;
        this->texture = texture;

        direction = Vector2f(0, 0);
        speed = 0;
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

    Texture getTexture() const
    {
        return texture;
    }

    // Moves the entity speed*delta_time units
    //  in the direction vector
    virtual void update_position(Float delta_time)
    {
        position.x += direction.x * speed * delta_time;
        position.y += direction.y * speed * delta_time;
    }

    Vector2f getDirection() const
    {
        return direction;
    }

    Float getSpeed() const
    {
        return speed;
    }

    void setDirection(Vector2f direction)
    {
        this->direction = normalize(direction);
    }

    void setSpeed(Float speed)
    {
        this->speed = abs(speed);
    }

    // Returns true if this entity collides with other
    bool collides(std::shared_ptr<Entity> other) const
    {
        return bound2f().overlaps(other->bound2f());
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

    bool has_gravity() const
    {
        return _has_gravity;
    }

    void activate_gravity()
    {
        _has_gravity = true;
    }

    void deactivate_gravity()
    {
        _has_gravity = false;
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