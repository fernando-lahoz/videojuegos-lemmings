#include "engine/rigid_body.hpp"
#include "engine/engine.hpp"


void Rigid_body::update_speed_gravity(Float gravity, Float delta_time)
{
    auto speed = get_speed();
    speed.y += gravity * delta_time;
    set_speed(speed);
}

bool Rigid_body::is_grounded(Engine& engine)
{
    // Spawn a ray from the bottom of the entity
    Point2f origin = max_corner2D();
    origin.y -= 0.001;

    Ray ray(origin, Vector2f(0, 1));

    EntityPtr ground;
    Float hit_offset;
    bool intersected = engine.intesect_ray(ray, false, 
            get_entity_id(), 
            RIGID_BODY_ID,
            hit_offset, ground);

    if (intersected && hit_offset < 0.005)
        return true;
    else
        return false;
}

Rigid_body::Rigid_body(Point3f position, Vector2f diagonal, Texture texture, 
        std::string _entity_name, std::string _class_name)
    : Entity(position, diagonal, texture, _entity_name, _class_name)
{
    speed = Vector2f(0, 0);
    max_speed_sqr = -1;

    disable_gravity();
}

void Rigid_body::set_gravity(Float new_gravity)
{
    this->gravity = new_gravity;
}

void Rigid_body::enable_gravity()
{
    _has_gravity = true;
}

void Rigid_body::disable_gravity()
{
    _has_gravity = false;
}

bool Rigid_body::has_gravity() const
{
    return _has_gravity;
}

Vector2f Rigid_body::get_speed() const
{
    return speed;
}

void Rigid_body::set_speed(Vector2f new_speed)
{
    speed = new_speed;
    
    if (max_speed > 0 && 
        speed.length_squared() > max_speed_sqr)
    {
        speed = normalize(speed) * max_speed;
    }
}

void Rigid_body::set_speedX(Float new_x_speed)
{
    auto temp_speed = get_speed();
    temp_speed.x = new_x_speed;
    set_speed(temp_speed);
}

void Rigid_body::set_speedY(Float new_y_speed)
{
    auto temp_speed = get_speed();
    temp_speed.y = new_y_speed;
    set_speed(temp_speed);
}

Float Rigid_body::get_max_speed_sqr() const
{
    return max_speed_sqr;
}

Float Rigid_body::get_max_speed() const
{
    return max_speed;
}

void Rigid_body::set_max_speed(Float new_max_speed)
{
    max_speed = new_max_speed;
    max_speed_sqr = math::pow2(new_max_speed);
}

void Rigid_body::on_collision([[maybe_unused]]Engine& engine, EntityPtr other)
{
    // If the entity is not moving, collision will not move it
    // Only rigid bodies can collide with other rigid bodies
    if (speed.length_squared() == 0 ||
        other->get_class() != "Rigid_body")
    {
        return;
    }

    auto speed = get_speed();

    // Get out of the other entity
    switch (closest_side(other))
    {
        case 0:
            position.x = other->bound2f().pMin.x - diagonal.x;
            speed.x = 0;
            break;
        case 1:
            position.x = other->bound2f().pMax.x;
            speed.x = 0;
            break;
        case 2:
            position.y = other->bound2f().pMax.y;
            speed.y = 0;
            break;
        case 3:
            position.y = other->bound2f().pMin.y - diagonal.y;
            speed.y = 0;
            break;
    }

    set_speed(speed);
}

void Rigid_body::update_position(Engine& engine)
{
    double delta_time = engine.get_delta_time();
    if (has_gravity())
    {
        update_speed_gravity(gravity, delta_time);
    }
    
    position.x += speed.x * delta_time;
    position.y += speed.y * delta_time;
}