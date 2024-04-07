#include "engine/fixed_text.hpp"

FixedText::FixedText(Point2f position, Float depth, Vector2f letter_size,
        const Texture& font_texture, Vector2i texture_letter_size,
        MappingFunction map, std::string_view, Engine& engine, std::string_view _class_name)
    : Entity{ position, depth, letter_size, font_texture, engine, _class_name, _class_name},
      texture_letter_size{texture_letter_size},
      map{map}
{
    collision_check_type = Collision_check::NONE;
    physics_type = Physics_type::NONE;
    cursor_type = Cursor_type::AABB;

}

