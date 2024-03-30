#pragma once

#include "engine/entity.hpp"

/*
class Rigid_body : public Entity
{
protected:

    enum Sides {RIGHT=1, UP=2, LEFT=4, DOWN=8};

    static constexpr char RIGID_BODY_ID[] = "Rigid_body";
    std::string _class_name;


    void update_speed_gravity(Float gravity, Float delta_time);
    bool is_grounded(Engine& engine) const;

public:

    Rigid_body(Point3f position, Vector2f diagonal, Texture texture,
        Engine& engine, 
        std::string _entity_name, 
        std::string _class_name=RIGID_BODY_ID);

    // Returns true if the ray intersected
    //  tmin contains the minimum hit offset
    //  and tmax contains the maximum hit offset
    
    bool distance(Engine &engine, Ray ray, EntityPtr collided_entity, 
            Float &tmin, Float &tmax, Float &thit);

    bool distance_up(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit);
    bool distance_down(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit);
    bool distance_left(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit);
    bool distance_right(Engine &engine, EntityPtr collided_entity, Float &tmin, Float &tmax, Float &thit);
    


    void on_collision([[maybe_unused]]Engine& engine, 
            EntityPtr other, 
            size_t collision_point_id) override;

    void update_state(Engine& engine) override;

    void pre_physics(Engine&) override;
    void on_creation(Engine&) override;
};

*/