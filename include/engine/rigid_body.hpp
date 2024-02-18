#pragma once

#include "engine/entity.hpp"

class Rigid_body : public Entity
{
protected:

    Vector2f speed;
    Float max_speed_sqr;
    Float max_speed = -1;

    bool _has_gravity;
    Float gravity = 0;

    static constexpr char RIGID_BODY_ID[] = "Rigid_body";
    
    void update_speed_gravity(Float gravity, Float delta_time);

    bool is_grounded(Engine& engine);

public:

    Rigid_body(Point3f position, Vector2f diagonal, Texture texture, 
        std::string _entity_name, 
        std::string _class_name = RIGID_BODY_ID);

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

    void on_collision(Engine& engine, EntityPtr other) override;

    void update_position(Engine& engine) override;
};