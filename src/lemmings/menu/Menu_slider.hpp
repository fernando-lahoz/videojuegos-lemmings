#ifndef MENU_SLIDER
#define MENU_SLIDER
#pragma once

#include <string>

#include "engine/engine.hpp"
#include "engine/IO.hpp"
#include "lemmings/Game_info.hpp"





class Menu_slider : public Entity
{
    private:

        float box_xmin, box_xmax, ratio, size;
        Bound2f bound;
        float last_position;
        uint8_t slider_var;
        Game_info &game_info;
        Texture txt_hover, txt_off;

        Float last_mouse_position;
        bool holded = false;

        bool is_mouse_over_slider(Engine &engine)
        {
            return bound.contains(engine.get_mouse_position());
        }

    public:
        Menu_slider(Point3f _position, float _box_width, Vector2f _button_size, uint8_t _var_value, Engine &_engine, Game_info &_game_info)
            :
              Entity(Point3f(_position.x + _box_width*0.01*_game_info.get_conf_var(_var_value), _position.y, _position.z),
                     _button_size, _engine.load_texture("assets/menu/slider_button.png"), _engine, "HUD"),
              box_xmin(_position.x), box_xmax(_position.x + _box_width), ratio (_box_width / 100.0f), size(_button_size.x),
              bound(Point2f(_position.x, _position.y), Point2f(_position.x + _box_width + _button_size.x, _position.y + _button_size.y)),
              slider_var(_var_value),
              game_info(_game_info),
              txt_hover(_engine.load_texture("assets/menu/slider_button_hover.png")),
              txt_off(_engine.load_texture("assets/menu/slider_button.png"))
        {
            alpha_mouse = false;
        }

    void pre_physics(Engine &engine) override
    {
        if (holded)
        {
            const Float new_mouse_position = engine.get_mouse_position().x;
            last_mouse_position = new_mouse_position;

            auto [x, y] = get_position2D();
            x = math::clamp(last_mouse_position - size/2, box_xmin, box_xmax);
            set_active_texture(txt_hover);
            set_position2D(Point2f(x, y));

            uint8_t slider_value = (x - box_xmin) / ratio;
            game_info.set_conf_var(slider_var, slider_value);
            //   game_info.set_var(slider_var, slider_value);
        } else {
            set_active_texture(txt_off);
        }
    }


    void on_event_down([[maybe_unused]]Engine &engine, EngineIO::InputEvent event) override
    {
        if (event == EngineIO::InputEvent::MOUSE_LEFT && is_mouse_over_slider(engine))
        {
            holded = true;
            last_mouse_position = engine.get_mouse_position().x;

            auto [x, y] = get_position2D();
            x = math::clamp(last_mouse_position - size/2, box_xmin, box_xmax);
            set_position2D(Point2f(x, y));

            uint8_t slider_value = (x - box_xmin) / ratio;
            game_info.set_conf_var(slider_var, slider_value);
            //   game_info.set_var(slider_var, slider_value);
        }
    }

    void on_event_up(Engine&, EngineIO::InputEvent event) override
    {
        if (event == EngineIO::InputEvent::MOUSE_LEFT && holded) {
        holded = false;
        }
    }

};

#endif // MENU_SLIDER