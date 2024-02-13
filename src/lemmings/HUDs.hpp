#pragma once

#include <memory>
#include <vector>
#include "engine/engine.hpp"
#include "engine/entity.hpp"
#include "HUD.hpp"

class HUDs
{
private:
  std::vector<std::shared_ptr<Entity>> elements;
  Engine &engine;

public:
  HUDs(Engine &engine) : engine(engine)
  {
    setupElements();
  }

  void setupElements()
  {
    auto hudElement = std::make_shared<HUD>(Point3f(-0.0006, 0, 4), Vector2f(1.001, 1), engine, "assets/hud/hud_", 0, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.022, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 0);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.079, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 1);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.137, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 2);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.194, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 3);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.252, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 4);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.309, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 5);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.36666666665, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 6);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.424, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 7);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.482, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 8);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.539, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 9);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.597, 0.8208333333, 3), Vector2f(0.05833333, 0.1486111), engine, "assets/hud/hud_option_", 10);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.654, 0.8208333333, 3), Vector2f(0.325, 0.1486111), engine, "assets/hud/hud_minimap_", 0, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);
  }

  void updatePosition(float delta)
  {
    for (auto &element : elements)
    {
      Point3f currentPosition = element->get_position3D();
      element->set_position3D(Point3f(currentPosition.x + delta, currentPosition.y, currentPosition.z));
    }
  }

  void on_key_down(SDL_KeyboardEvent &key)
  {
    switch (key.keysym.sym)
    {
    case SDLK_a:
      // Mover el HUD a la izquierda
      updatePosition(-0.01); // Ajusta este valor según sea necesario
      break;
    case SDLK_d:
      // Mover el HUD a la derecha
      updatePosition(0.01); // Ajusta este valor según sea necesario
      break;
    }
  }
};
