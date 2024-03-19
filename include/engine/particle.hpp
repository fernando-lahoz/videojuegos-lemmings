#include "engine/entity.hpp"

class Particle : public Entity
{

protected:
    Float time_to_live;

public:

    Particle(Point3f position, Vector2f diagonal,
            Float time_to_live, // in seconds
            const Texture& texture, 
            Engine& engine,
            std::string_view _entity_name, 
            std::string_view _class_name="Particle")
        :
        Entity(position, diagonal, texture, engine, _entity_name, _class_name)
    {
        this->time_to_live = time_to_live;
        constructor_set_collision_type(Entity::Collision_type::HUD);
    }


    void pre_physics(Engine& engine) override
    {
        Entity::pre_physics(engine);

        time_to_live -= engine.get_delta_time();

        if (time_to_live <= 0)
        {
            destroy();
        }
    }

};