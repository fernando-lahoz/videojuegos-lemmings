#include "engine/fixed_text.hpp"

FixedText::FixedText(Point3f position, Vector2f letter_size,
        const Texture& font_texture, Vector2i texture_letter_size,
        MappingFunction map, std::string_view text, std::string_view _class_name)
    : Entity{ position, letter_size, font_texture, text, _class_name }, 
      texture_letter_size{texture_letter_size},
      map{map}
{

}

