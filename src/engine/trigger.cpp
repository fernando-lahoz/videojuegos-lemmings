#include "engine/trigger.hpp"
#include "lib/texture.hpp"


Trigger::Trigger(Point3f position, Vector2f diagonal,
        std::string _entity_name, 
        std::string _class_name)
    : Entity(position, diagonal, Texture(), _entity_name, _class_name)
{
    disable_alpha_collision();
    disable_alpha_mouse();
    constructor_set_collision_type(Entity::Collision_type::STRUCTURE);
}

void Trigger::add_asociated_entity(EntityPtr entity)
{
    asociated_entities.push_back(entity);
}

std::vector<EntityPtr> Trigger::get_asociated_entities() const
{
    return asociated_entities;
}

void Trigger::on_collision([[maybe_unused]]Engine& engine, 
        [[maybe_unused]]EntityPtr other)
{
    trigger_collision_event(engine, other);
}

void Trigger::update_state([[maybe_unused]]Engine& engine)
{
    // Do nothing
}

void Trigger::pre_physics([[maybe_unused]]Engine& engine)
{
    // Do nothing
}

void Trigger::on_creation([[maybe_unused]]Engine& engine)
{
    // Do nothing
}


void Trigger::on_event_down(Engine& engine, EngineIO::InputEvent event)
{
    trigger_IO_event(engine, event);
}

void Trigger::on_event_up(Engine& engine, EngineIO::InputEvent event)
{
    trigger_IO_event(engine, event);
}

void Trigger::trigger_collision_event(Engine& engine, EntityPtr other)
{
    for (auto asociated_entity : asociated_entities)
    {
        asociated_entity->on_trigger_collision_event(engine, this, other);
    }
}

void Trigger::trigger_IO_event(Engine& engine, EngineIO::InputEvent event)
{
    for (auto asociated_entity : asociated_entities)
    {
        asociated_entity->on_trigger_IO_event(engine, this, event);
    }
}