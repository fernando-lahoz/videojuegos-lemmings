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
  const Point3f positions[12] = {Point3f(0.022, 0.8208333333, 3), Point3f(0.079, 0.8208333333, 3), Point3f(0.137, 0.8208333333, 3), Point3f(0.194, 0.8208333333, 3), Point3f(0.252, 0.8208333333, 3), Point3f(0.309, 0.8208333333, 3), Point3f(0.36666666665, 0.8208333333, 3), Point3f(0.424, 0.8208333333, 3), Point3f(0.482, 0.8208333333, 3), Point3f(0.539, 0.8208333333, 3), Point3f(0.597, 0.8208333333, 3), Point3f(-1, 0.8208333333, 3)};
  const Vector2f size = Vector2f(0.05833333, 0.1486111);
  int option_selected = 6;

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

    hudElement = std::make_shared<HUD>(positions[0], size, engine, "assets/hud/hud_option_", 0, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.03172222222, 0.8694111111, 1), Vector2f(0.04027777777, 0.05555555555), engine, "assets/hud/hud_option_0_button_", 15, true, true, true);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.0351, 0.828, 1), Vector2f(0.02638888888, 0.03194444444), engine, "assets/hud/hud_option_0_button_", 13, true, true, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.033, 0.934, 1), Vector2f(0.03333333333, 0.013888888888), engine, "assets/hud/hud_option_0_button_", 14, true, true, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[1], size, engine, "assets/hud/hud_option_", 1, false, false, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.08733333333, 0.88611111107, 1), Vector2f(0.03888888889, 0.044444444), engine, "assets/hud/hud_option_1_button_", 11, true, true, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(0.08733333333, 0.9402777777, 1), Vector2f(0.03888888889, 0.01666666666), engine, "assets/hud/hud_option_1_button_", 12, true, true, false);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[2], size, engine, "assets/hud/hud_option_", 2);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[3], size, engine, "assets/hud/hud_option_", 3);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[4], size, engine, "assets/hud/hud_option_", 4);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[5], size, engine, "assets/hud/hud_option_", 5);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[6], size, engine, "assets/hud/hud_option_", 6);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[7], size, engine, "assets/hud/hud_option_", 7);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[8], size, engine, "assets/hud/hud_option_", 8);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[9], size, engine, "assets/hud/hud_option_", 9);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(positions[10], size, engine, "assets/hud/hud_option_", 10);
    engine.get_game()->create_entity(hudElement);
    elements.push_back(hudElement);

    hudElement = std::make_shared<HUD>(Point3f(positions[option_selected].x, positions[option_selected].y, 2), size, engine, "assets/hud/hud_option_selected_", 0, false, false, false);
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
