#pragma once

#include "engine/entity.hpp"

class Rigid_body : public Entity
{
protected:

    Vector2f speed;
    Float max_speed_sqr;
    Float max_speed = -1;

    Point2f down_point, up_point,
            left_point, right_point;

    bool _has_gravity;
    Float gravity = 0;

    enum Sides {RIGHT=1, UP=2, LEFT=4, DOWN=8};

    static constexpr char RIGID_BODY_ID[] = "Rigid_body";
    std::string _class_name;


    void update_speed_gravity(Float gravity, Float delta_time);
    bool is_grounded(Engine& engine);

public:


    Rigid_body(Point3f position, Vector2f diagonal, Texture texture, 
        std::string _entity_name, 
        std::string _class_name=RIGID_BODY_ID);

    void set_gravity(Float new_gravity);
    void enable_gravity();
    void disable_gravity();

    bool has_gravity() const;
    Vector2f get_speed() const;

    void set_speed(Vector2f new_speed);
    void set_speedX(Float new_x_speed);
    void set_speedY(Float new_y_speed);

    Float get_max_speed_sqr() const;
    Float get_max_speed() const;
    void set_max_speed(Float new_max_speed);

    void override_right_point(Point2f new_p);
    void override_left_point(Point2f new_p);
    void override_up_point(Point2f new_p);
    void override_down_point(Point2f new_p);

    Point2f default_right_point() const;
    Point2f default_left_point() const;
    Point2f default_up_point() const;
    Point2f default_down_point() const;



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
            EntityPtr other) override;

    void update_position(Engine& engine) override;
};