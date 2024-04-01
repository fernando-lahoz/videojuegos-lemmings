#include "engine/entity.hpp"
#include "engine/engine.hpp"

Entity::Entity(Point3f position, Vector2f diagonal, const Texture& texture, 
            Engine &engine,
            std::string_view _entity_name, 
            bool is_rigid_body,
            Collision_type _collision_type,
            Cursor_collision_type _cursor_collision_type,
            std::string_view _class_name)
    :
    collision_type(_collision_type),
    cursor_collision_type(_cursor_collision_type),
    _is_rigid_body(is_rigid_body),
    active_texture(texture),
    deleted_entity(false),
    entity_id(-1),
    mouse_over(false),
    position(position),
    class_name(_class_name),
    entity_name(_entity_name),
    diagonal(diagonal),
    speed(0, 0)
{
    //engine.subscribe_to_events(this);
}

Entity::Collision_type Entity::get_collision_type() const
{
    return collision_type;
}


Entity::Cursor_collision_type Entity::get_cursor_collision_type() const
{
    return cursor_collision_type;
}

bool Entity::is_rigid_body() const
{
    return _is_rigid_body;
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


bool Entity::alpha_collides(std::shared_ptr<Entity> other, size_t &collision_point_id) const
{
    for (size_t i = 0; i < collision_points.size(); i++)
    {        
        Point2f world_point = local_to_world(collision_points[i]);

        if (other->contains(world_point, false))
        {
            collision_point_id = i;
            return true;
        }
    }

    return false;
}


bool Entity::set_collision_point(size_t id, Point2f new_p)
{
    if (id >= collision_points.size())
        return false;

    collision_points[id] = new_p;

    return true;
}

bool Entity::is_colliding(size_t id) const
{
    if (id >= vector_is_colliding.size())
        return false;

    return vector_is_colliding[id];
}



size_t Entity::add_collision_point(Point2f new_p)
{
    collision_points.push_back(new_p);
    vector_is_colliding.push_back(false);

    return collision_points.size() - 1;
}


bool Entity::contains(Point2f point, bool is_mouse) const
{
    if (bound2f().contains(point))
    {
        if (is_mouse && cursor_collision_type == Cursor_collision_type::ALPHA)
            return !get_active_texture().is_alpha_pixel(world_to_local(point));
        else if (is_mouse)
            return true;

        if (!is_mouse && collision_type == Collision_type::ALPHA)
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
    for (size_t i = 0; i < vector_is_colliding.size(); i++)
    {
        vector_is_colliding[i] = false;
    }
}

void Entity::update_state(Engine&)
{
    // Do nothing by default
}

void Entity::on_collision(Engine&, std::shared_ptr<Entity> , bool, size_t collision_point_id)
{
    vector_is_colliding[collision_point_id] = true;
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