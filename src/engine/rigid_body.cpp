#include "engine/rigid_body.hpp"
#include "engine/engine.hpp"


bool Rigid_body::is_grounded(Engine& ) const
{
    return colliding_down();

    /*
    // Spawn a ray from the bottom of the entity
    Point2f origin = local_to_world(down_point);
    Ray ray(origin, Vector2f(0, 1));

    EntityPtr ground;
    Float hit_offset, hit_offset_min, hit_offset_max;
    bool intersected = engine.intesect_ray(ray, 
            get_entity_id(), 
            RIGID_BODY_ID,
            hit_offset_min, hit_offset_max,
            ground);

    if (hit_offset_min < 0) {
        hit_offset = hit_offset_max;
    }
    else {
        hit_offset = hit_offset_max;
    }

    if (intersected && ground->contains(origin))
    {
        hit_offset = 0;
    }

    if (intersected && hit_offset < 0.0005) {
        return true;
    }
    else {
        return false;
    }
    */
}


Rigid_body::Rigid_body(Point3f position, Vector2f diagonal, Texture texture, 
    std::string _entity_name, 
    std::string _class_name)
    : Entity(position, diagonal, texture, 
            _entity_name, _class_name)
{
    speed = Vector2f(0, 0);

    right_point = default_right_point();
    left_point = default_left_point();
    up_point = default_up_point();
    down_point = default_down_point();

    disable_gravity();
    constructor_set_collision_type(Collision_type::STRUCTURE);
}


// Returns true if the ray intersected
//  tmin contains the minimum hit offset
//  and tmax contains the maximum hit offset
/*
bool Rigid_body::distance(Engine &engine, Ray ray, EntityPtr collided_entity, 
        Float &tmin, Float &tmax, Float &thit)
{
    bool intersected = engine.intesect_ray_entity(ray, 
            collided_entity,
            tmin, 
            tmax);

    intersected = intersected && tmax > 0;

    Point2f origin = Point2f(ray.origin.x, ray.origin.y);
    if (collided_entity->contains(origin))
    {
        thit = 0;
    }
    else if (tmin < 0) {
        thit = tmax;
    }
    else {
        thit = tmin;
    }

    if (intersected)
    {
        engine.ray_march_alpha_end(ray, tmax, 0, tmax, collided_entity);

        if (tmin < 0)
        {
            ray.direction = -ray.direction;
            tmin = -tmin;
            engine.ray_march_alpha_end(ray, tmin, 0, tmin, collided_entity);
            tmin = -tmin;
        }
        else
        {
            engine.ray_march_alpha_end(ray, tmin, 0, tmin, collided_entity);
        }

        return true;
    }

    return false;
}

bool Rigid_body::distance_up(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
{
    Point2f p = local_to_world(up_point);
    Ray ray(p, Vector2f(0, -1));
    return distance(engine, ray, collided_entity, tmin, tmax, thit);
}

bool Rigid_body::distance_down(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
{
    Point2f p = local_to_world(down_point);
    Ray ray(p, Vector2f(0, 1));
    return distance(engine, ray, collided_entity, tmin, tmax, thit);
}

bool Rigid_body::distance_left(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
{
    Point2f p = local_to_world(left_point);
    Ray ray(p, Vector2f(-1, 0));
    return distance(engine, ray, collided_entity, tmin, tmax, thit);
}

bool Rigid_body::distance_right(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit)
{
    Point2f p = local_to_world(right_point);
    Ray ray(p, Vector2f(1, 0));
    return distance(engine, ray, collided_entity, tmin, tmax, thit);
}
*/


void Rigid_body::on_collision([[maybe_unused]]Engine& engine, 
        EntityPtr other)
{
    Entity::on_collision(engine, other);

    // If the entity is not moving, collision will not move it
    // Only rigid bodies can collide with other rigid bodies
    if (speed.length_squared() == 0 ||
        other->get_class() != "Rigid_body")
    {
        return;
    }

    auto speed = get_speed();

    //std::cout << "Closest side: " << closest_side << std::endl;

    // Only will collide when tmin is negative
    if (colliding_up())
    {
        speed.y = 0;
    }

    if (colliding_down())
    {
        speed.y = 0;
    }

    if (colliding_left())
    {
        speed.x = 0;
    }

    if (colliding_right())
    {
        speed.x = 0;
    }       

    set_speed(speed);
}

void Rigid_body::update_state(Engine& engine)
{        
    Entity::update_state(engine);
}


void Rigid_body::pre_physics(Engine& engine)
{
    Entity::pre_physics(engine);
}

void Rigid_body::on_creation(Engine& engine)
{
    Entity::on_creation(engine);
}