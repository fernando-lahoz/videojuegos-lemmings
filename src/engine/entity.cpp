#include "engine/entity.hpp"

Entity::Entity(Point3f position, Vector2f diagonal,
        Texture texture, std::string_view _type, Float _max_speed)
{
    this->position = position;
    this->diagonal = diagonal;
    this->active_texture = texture;
    this->max_speed = _max_speed;
    this->max_speed_sqr = math::pow<2>(_max_speed);

    this->type = _type;

    speed = Vector2f(0, 0);
}