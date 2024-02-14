#include "engine/entity.hpp"
#include "engine/engine.hpp"

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

bool Entity::collides(std::shared_ptr<Entity> other, Point2f &collision_point) const
{
    if (bound2f().overlaps(other->bound2f()))
    {        
        // Get intersection
        Bound2f intersection = bound2f() - other->bound2f();
        auto txt = get_active_texture();
        auto other_txt = other->get_active_texture();

        Point2f n_samples = Point2f(10, 10);
        Point2f offset = Point2f(intersection.diagonal() / n_samples.to_vector());

        for (int i = 0; i < n_samples.x; i++)
        {
            for (int j = 0; j < n_samples.y; j++)
            {
                Point2f sample_point = intersection.pMin;
                sample_point.x += i * offset.x;
                sample_point.y += j * offset.y;


                auto lsample = world_to_local(sample_point);
                auto other_lsample = other->world_to_local(sample_point);

                if (!txt.is_alpha_pixel(lsample) && !other_txt.is_alpha_pixel(other_lsample))
                {
                    collision_point = sample_point;
                    return true;
                }
            }
        }
    }    

    return false;
}

bool Entity::collides(std::shared_ptr<Entity> other) const
{
    Point2f collision_point;
    return collides(other, collision_point);
}

bool Entity::contains(Point2f point) const
{
    if (bound2f().contains(point))
    {
        return !get_active_texture().is_alpha_pixel(world_to_local(point));
    }

    return false;
}

bool Entity::contains_the_mouse(Engine& engine) const
{
    auto mouse_p = engine.get_mouse_position();
    if (bound2f().contains(mouse_p))
    {
        auto lmouse_p = world_to_local(mouse_p);
        auto txt = get_active_texture();
        return !txt.is_alpha_pixel(lmouse_p);
    }

    return false;
}

bool Entity::contains_the_mouse([[maybe_unused]] Engine& engine, Point2f mouse_position) const
{
    if (bound2f().contains(mouse_position))
    {
        auto lmouse_p = world_to_local(mouse_position);
        auto txt = get_active_texture();
        return !txt.is_alpha_pixel(lmouse_p);
    }

    return false;
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