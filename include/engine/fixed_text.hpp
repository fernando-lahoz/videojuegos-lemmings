#pragma once

#include "engine/entity.hpp"
#include "geometry/vector.hpp"

class FixedText : public Entity
{
public:
    using MappingFunction = Point2i (*)(char);
private:
    Vector2i texture_letter_size;
    MappingFunction map;

protected:

public:
    FixedText(Point3f position, Vector2f letter_size, const Texture& font_texture,
            Vector2i texture_letter_size, MappingFunction map,
            std::string_view text, Engine &engine, std::string_view _class_name = "Text");

    virtual ~FixedText() = default;

    friend class Render_2D;
};