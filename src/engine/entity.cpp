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

Entity::Collision_type Entity::get_collision_type() const
{
    return collision_type;
}

void Entity::constructor_set_collision_type(Collision_type new_type)
{
    collision_type = new_type;
}

void Entity::change_collision_type(Engine &engine, Collision_type new_type)
{
    engine.change_collision_type(this, new_type);

    // Change type after the engine has been notified
    //  so it sees the old type
    collision_type = new_type;
}

Point2f Entity::world_to_local(Point2f w_p) const
{
    w_p -= get_position2D();
    
    auto d = get_diagonal();
    w_p.x = w_p.x / d.x;
    w_p.y = w_p.y / d.y;

    return w_p;
}

Vector2f Entity::world_to_local(Vector2f w_p) const
{
    auto d = get_diagonal();
    w_p.x = w_p.x / d.x;
    w_p.y = w_p.y / d.y;

    return w_p;
}

Bound2f Entity::world_to_local(Bound2f box) const
{
    return Bound2f(world_to_local(box.pMin), world_to_local(box.pMax));
}

Point2f Entity::local_to_world(Point2f l_p) const
{
    auto d = get_diagonal();
    l_p.x *= d.x;
    l_p.y *= d.y;

    l_p += get_position2D();

    return l_p;
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

Vector2f Entity::get_diagonal() const
{
    return diagonal;
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

void Entity::enable_alpha_collision()
{
    alpha_collision = true;
}

void Entity::disable_alpha_collision()
{
    alpha_collision = false;
}

void Entity::enable_alpha_mouse()
{
    alpha_mouse = true;
}

void Entity::disable_alpha_mouse()
{
    alpha_mouse = false;
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

bool Entity::colliding_up() const
{
    return _collides_up;
}

bool Entity::colliding_down() const
{
    return _collides_down;
}

bool Entity::colliding_left() const
{
    return _collides_left;
}

bool Entity::colliding_right() const
{
    return _collides_right;
}


bool Entity::collides(std::shared_ptr<Entity> other, Point2f &collision_point) const
{
    if (check_collision_right(other))
    {
        collision_point = right_point;
        return true;
    }
    else if (check_collision_left(other))
    {
        collision_point = left_point;
        return true;
    }
    else if (check_collision_up(other))
    {
        collision_point = up_point;
        return true;
    }
    else if (check_collision_down(other))
    {
        collision_point = down_point;
        return true;
    }

    return false;
}

bool Entity::check_collision_right(std::shared_ptr<Entity> other) const
{
    auto p = local_to_world(right_point);
    return other->contains(p, false);
} 

bool Entity::check_collision_left(std::shared_ptr<Entity> other) const
{
    auto p = local_to_world(left_point);
    return other->contains(p, false);
}

bool Entity::check_collision_up(std::shared_ptr<Entity> other) const
{
    auto p = local_to_world(up_point);
    return other->contains(p, false);
}

bool Entity::check_collision_down(std::shared_ptr<Entity> other) const
{
    auto p = local_to_world(down_point);
    return other->contains(p, false);
}

void Entity::override_right_point(Point2f new_p)
{
    right_point = new_p;
}

void Entity::override_left_point(Point2f new_p)
{
    left_point = new_p;
}

void Entity::override_up_point(Point2f new_p)
{
    up_point = new_p;
}

void Entity::override_down_point(Point2f new_p)
{
    down_point = new_p;
}

Point2f Entity::default_right_point() const
{
    return Point2f(1, 0.5);
}

Point2f Entity::default_left_point() const
{
    return Point2f(0, 0.5);
}

Point2f Entity::default_up_point() const
{
    return Point2f(0.5, 0);
}

Point2f Entity::default_down_point() const
{
    return Point2f(0.5, 1);
}


bool Entity::collides(std::shared_ptr<Entity> other) const
{
    if (!collisions_active)
        return false;

    if (!alpha_collision)
    {
        return bound2f().overlaps(other->bound2f());
    }

    Point2f collision_point;
    return collides(other, collision_point);
}

void Entity::enable_collisions()
{
    collisions_active = true;
}

void Entity::disable_collisions()
{
    collisions_active = false;
}

bool Entity::contains(Point2f point, bool is_mouse) const
{
    if (bound2f().contains(point))
    {
        if (is_mouse && alpha_mouse)
            return !get_active_texture().is_alpha_pixel(world_to_local(point));
        else if (is_mouse)
            return true;

        if (!is_mouse && alpha_collision)
            return !get_active_texture().is_alpha_pixel(world_to_local(point));
        else if (!is_mouse)
            return true;
    }

    return false;
}

bool Entity::destroy_box_alpha(Engine &engine, Bound2f box)
{
    return active_texture.set_alpha_box(world_to_local(box), 0, engine.get_renderer());
}

bool Entity::contains_the_mouse(Engine& engine)
{
    return engine.is_entity_hovered(*this);
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
    _collides_up = false;
    _collides_down = false;
    _collides_left = false;
    _collides_right = false;
}

void Entity::update_position(Engine&)
{
    // Do nothing by default
}

void Entity::on_collision(Engine&, std::shared_ptr<Entity> other)
{
    if (check_collision_down(other))
        _collides_down = true;

    if (check_collision_up(other))
        _collides_up = true;

    if (check_collision_left(other))
        _collides_left = true;

    if (check_collision_right(other))
        _collides_right = true;
}

void Entity::post_physics(Engine&)
{
    // Do nothing by default
}

// Called right after the entity has been inserted
//  into the engine runtime
void Entity::on_creation(Engine&)
{
    // Do nothing by default
}

void Entity::on_trigger_collision_event(Engine&, Entity*, EntityPtr)
{
    // Do nothing by default
}

void Entity::on_trigger_IO_event(Engine&, Entity*, EngineIO::InputEvent)
{
    // Do nothing by default
}