#pragma once

#include <vector>
#include "engine/entity.hpp"

class Trigger : public Entity
{

    protected:

    std::vector<EntityPtr> asociated_entities;

    public:

    Trigger(Point2f position, Float depth,
            Vector2f diagonal,
            Engine& engine,
            std::string _entity_name, 
            std::string _class_name="Trigger");

    void add_asociated_entity(EntityPtr entity);
    std::vector<EntityPtr> get_asociated_entities() const;


    void on_collision([[maybe_unused]]Engine& engine, 
            EntityPtr other,
            bool is_alpha,
            size_t collision_point_id) override;

    void update_state(Engine& engine) override;

    void pre_physics(Engine&) override;
    void on_creation(Engine&) override;
    
    void on_event_down(Engine&, EngineIO::InputEvent) override;
    void on_event_up(Engine&, EngineIO::InputEvent) override;

    void trigger_collision_event(Engine& engine, EntityPtr other);
    void trigger_IO_event(Engine& engine, EngineIO::InputEvent event);
};
