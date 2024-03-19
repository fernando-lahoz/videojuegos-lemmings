#include "engine/entity.hpp"

class Particle : public Entity
{

    Particle(Point3f position, Vector2f diagonal, const Texture& texture, 
            std::string_view _entity_name, 
            std::string_view _class_name="Particle")
        :
        Entity(position, diagonal, texture, _entity_name, _class_name)
    {
        constructor_set_collision_type(Entity::Collision_type::HUD);
    }

};