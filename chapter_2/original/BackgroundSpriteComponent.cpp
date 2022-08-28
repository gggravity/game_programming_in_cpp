#include "BackgroundSpriteComponent.h"
#include "Actor.h"

BackgroundSpriteComponent::BackgroundSpriteComponent (class Actor *owner, int draw_order) :
    SpriteComponent(owner, draw_order),
    m_scroll_speed(0.0f)
  {
  }

void BackgroundSpriteComponent::update (float delta_time)
  {
    SpriteComponent::update(delta_time);
    for (auto &bg : m_background_textures)
      {
        // Update the x offset
        bg.m_offset.x += m_scroll_speed * delta_time;
        // If this is completely off the screen, reset offset to
        // the right of the last bg texture
        if (bg.m_offset.x < -m_screen_size.x)
          {
            bg.m_offset.x = ( float(m_background_textures.size()) - 1 ) * m_screen_size.x - 1;
          }
      }
  }

void BackgroundSpriteComponent::draw (SDL_Renderer *renderer)
  {
    // Draw each background texture
    for (auto &bg : m_background_textures)
      {
        SDL_Rect r;
        // Assume screen size dimensions
        r.w = static_cast<int>(m_screen_size.x);
        r.h = static_cast<int>(m_screen_size.y);
        // Center the rectangle around the position of the owner
        r.x = static_cast<int>(m_owner->get_position().x - float(r.w) / 2 + bg.m_offset.x);
        r.y = static_cast<int>(m_owner->get_position().y - float(r.h) / 2 + bg.m_offset.y);

        // Draw this background
        SDL_RenderCopy(renderer,
                       bg.m_texture,
                       nullptr,
                       &r
        );
      }
  }

void BackgroundSpriteComponent::set_background_textures (const std::vector<SDL_Texture *> &textures)
  {
    int count = 0;
    for (auto tex : textures)
      {
        BGTexture temp;
        temp.m_texture = tex;
        // Each texture is screen width in offset
        temp.m_offset.x = float(count) * m_screen_size.x;
        temp.m_offset.y = 0;
        m_background_textures.emplace_back(temp);
        count++;
      }
  }
