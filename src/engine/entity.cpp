#include "engine/entity.hpp"

Entity::Entity(Point3f position, Vector2f diagonal, Texture texture, 
            std::string_view _entity_name, 
            std::string_view _class_name)
{
    this->position = position;
    this->diagonal = diagonal;
    this->active_texture = texture;

    this->entity_name = _entity_name;
    this->class_name = _class_name;
}