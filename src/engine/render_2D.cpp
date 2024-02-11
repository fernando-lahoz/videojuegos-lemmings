#include "engine/render_2D.hpp"
#include "engine/IO.hpp"

Camera2D::Camera2D()
{
    frame = Bound2f(Point2f(0, 0), Point2f(1, 1));
}

Camera2D::Camera2D(Bound2f frame)
{
    this->frame = frame;
}

Point2f Camera2D::world_to_screen(Point2f world_point)
{
    float x = (world_point.x - frame.pMin.x) / (frame.width());
    float y = (world_point.y - frame.pMin.y) / (frame.height());

    return Point2f(x, y);
}

Vector2f Camera2D::world_to_screen(Vector2f world_vector)
{
    float x = world_vector.x / frame.width();
    float y = world_vector.y / frame.height();

    return Vector2f(x, y);
}

Point2f Camera2D::screen_to_world(Point2f screen_point)
{
    float x = screen_point.x * frame.width() + frame.pMin.x;
    float y = screen_point.y * frame.height() + frame.pMin.y;

    return Point2f(x, y);
}

Vector2f Camera2D::screen_to_world(Vector2f screen_vector)
{
    float x = screen_vector.x * frame.width();
    float y = screen_vector.y * frame.height();

    return Vector2f(x, y);
}

Bound2f Camera2D::get_frame() const
{
    return frame;
}

void Camera2D::update_position([[maybe_unused]] Engine&)
{
    // Do nothing by default
}

bool Camera2D::isVisible(Entity& entity)
{
    return frame.overlaps(entity.bound2f());
}

void Camera2D::on_key_down(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

void Camera2D::on_key_up(Engine&, EngineIO::InputEvent)
{
    // Do nothing by default
}

//------------------------------------------------------------------------------

void Render_2D::clear_window(Spectrum color)
{
    SDL_SetRenderDrawColor(renderer, color.get_r(), color.get_g(), color.get_b(), color.get_a());
    SDL_RenderClear(renderer);
}

SDL_Rect Render_2D::entity_to_rect(Entity& e, Camera2D& camera)
{
    SDL_Rect rect;

    auto w_position = world_to_raster(e.get_position2D(), camera);
    //TODO: what is this cast meant for
    rect.x = (unsigned) (w_position.x);
    rect.y = (unsigned) (w_position.y);


    auto w_diag = world_to_raster(e.bound2f().diagonal(), camera);
    rect.w = (unsigned) (w_diag.x);
    rect.h = (unsigned) (w_diag.y);


    return rect;
}

void Render_2D::render_entity(Entity& entity, Camera2D& camera)
{
    if (camera.isVisible(entity))
    {
        auto rect = entity_to_rect(entity, camera);

        auto texture = entity.get_active_texture();
        SDL_RenderCopy(renderer, texture.get(), nullptr, &rect);          
    }
}

Render_2D::Render_2D(std::string window_name, int width, int height)
{
    resolution = Vector2i(width, height);

    // Window with vsync
    window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Config alpha layers
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Texture Render_2D::load_texture(const std::string& file)
{
    if (textures.find(file) != textures.end())
    {
        return textures[file];
    }
    else
    {
        Texture texture;
        texture.load(file, renderer);
        textures[file] = texture;

        return texture;
    }
}


Point2f Render_2D::world_to_raster(Point2f world_point, Camera2D& camera)
{
    auto screen_p = camera.world_to_screen(world_point);
    return Point2f(screen_p.x * resolution.x, screen_p.y * resolution.y);
}

Vector2f Render_2D::world_to_raster(Vector2f world_vector, Camera2D& camera)
{
    auto screen_v = camera.world_to_screen(world_vector);
    return Vector2f(screen_v.x * resolution.x, screen_v.y * resolution.y);
}

Point2f Render_2D::raster_to_world(Point2f raster_point, Camera2D& camera)
{
    auto screen_p = Point2f(raster_point.x / resolution.x, raster_point.y / resolution.y);
    return camera.screen_to_world(screen_p);
}

Vector2f Render_2D::raster_to_world(Vector2f raster_vector, Camera2D& camera)
{
    auto screen_v = Vector2f(raster_vector.x / resolution.x, raster_vector.y / resolution.y);
    return camera.screen_to_world(screen_v);
}



void Render_2D::draw(std::vector<EntityPtr> &entities, Camera2D& camera)
{
    clear_window(Spectrum(0.529*255, 0.808*255, 0.922*255));

    // Render drawables
    for (auto &d : entities)
    {
        render_entity(*d, camera);
    }

    SDL_RenderPresent(renderer);
}