#pragma once

#include "engine/engine.hpp"
#include "engine/rigid_body.hpp"

#include "lemmings/Game_info.hpp"
#include "lemmings/utils.hpp"

class Credit_animation : public Rigid_body
{
private:
  int type, n_frames;
  Texture txt;

  int current_frame = 0; // Frame actual de la animación

  int last_credit_frame = 0; // Contador de frames para pausar la animación de los creditos
  int frames_credits;        // Numero de frames de los creditos
  Game_info &game_info;

public:
  Credit_animation(Point3f position, Vector2f size, Game_info &_game_info, Engine &engine, int _type, int _frames_credits)
      : Rigid_body(position, size, engine.load_texture("assets/menu/credit_animation_" + std::to_string(_type) + "_0.png"), "Credit Animation"),
        type(_type), frames_credits(_frames_credits), game_info(_game_info)
  {
    txt = engine.load_texture("assets/menu/credit_animation_" + std::to_string(_type) + "_0.png");
  }

  void update_animation(Engine &engine)
  {
    int actual_credit_frame = game_info.get_credit_frame();
    if (actual_credit_frame != last_credit_frame)
    {
      last_credit_frame = actual_credit_frame;
      current_frame = last_credit_frame % frames_credits;

      std::string frame_path = "assets/menu/credit_animation_" + std::to_string(type) + "_" + std::to_string(current_frame) + ".png";
      Texture txt = engine.load_texture(frame_path.c_str());
      set_active_texture(txt);
    }
  }

  void pre_physics(Engine &engine) override
  {
    update_animation(engine);
  }
};
