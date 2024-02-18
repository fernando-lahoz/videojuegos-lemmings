#include "engine/entity.hpp"
#include "engine/engine.hpp"

Entity::Entity(Point3f position, Vector2f diagonal, const Texture& texture, 
            std::string_view _entity_name, 
            std::string_view _class_name)
{
    this->position = position;
    this->diagonal = diagonal;
    this->active_texture = texture;

    this->entity_name = _entity_name;
    this->class_name = _class_name;
}

std::string Entity::get_entity_name() const
{
    return entity_name;
}

std::string Entity::get_class() const
{
    return class_name;
}

Point2f Entity::get_position2D() const
{
    return Point2f(position.x, position.y);
}

Point3f Entity::get_position3D() const
{
    return position;
}

void Entity::set_position2D(Point2f p)
{
    position.x = p.x;
    position.y = p.y;
}

void Entity::set_position3D(Point3f p)
{
    position = p;
}

int Entity::get_entity_id() const
{
    return entity_id;
}

void Entity::set_entity_id(int id)
{
    entity_id = id;
}

Point2f Entity::max_corner2D() const
{
    return get_position2D() + diagonal;
}

Point3f Entity::max_corner3D() const
{
    auto maxCorner = max_corner2D();
    return Point3f(maxCorner.x, maxCorner.y, position.z);
}

Bound2f Entity::bound2f() const
{
    return Bound2f(get_position2D(), max_corner2D());
}

Texture Entity::get_active_texture() const
{
    return active_texture;
}

void Entity::set_active_texture(Texture new_texture)
{
    active_texture = new_texture;
}

bool Entity::is_deleted() const
{
    return deleted_entity;
}

void Entity::destroy()
{
    deleted_entity = true;
}

bool Entity::mouse_was_hovering() const
{
    return mouse_over;
}

void Entity::enable_mouse_hover()
{
    mouse_over = true;
}

void Entity::disable_mouse_hover()
{
    mouse_over = false;
}


bool Entity::collides(std::shared_ptr<Entity> other) const
{
    return bound2f().overlaps(other->bound2f());
}

bool Entity::contains_the_mouse(Engine& engine) const
{
    return bound2f().contains(engine.get_mouse_position());
}

bool Entity::contains_the_mouse([[maybe_unused]] Engine& engine, Point2f mouse_position) const
{
    return bound2f().contains(mouse_position);
}

int Entity::closest_side(std::shared_ptr<Entity> other)
{
    Float distance_right = other->bound2f().pMax.x - bound2f().pMin.x;
    Float distance_left = bound2f().pMax.x - other->bound2f().pMin.x;
    Float distance_up = other->bound2f().pMax.y - bound2f().pMin.y;
    Float distance_down = bound2f().pMax.y - other->bound2f().pMin.y;

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

void Entity::on_event_down(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

void Entity::on_event_up(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

void Entity::pre_physics(Engine&)
{
    // Do nothing by default
}

void Entity::update_position(Engine&)
{
    // Do nothing by default
}

void Entity::on_collision(Engine&, std::shared_ptr<Entity>)
{
    // Do nothing by default
}

void Entity::post_physics(Engine&)
{
    // Do nothing by default
}