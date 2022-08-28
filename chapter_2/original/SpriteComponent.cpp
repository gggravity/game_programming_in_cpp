#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent (Actor *owner, int draw_order) :
    Component(owner),
    m_texture(nullptr),
    m_draw_order(draw_order),
    m_texture_width(0),
    m_texture_height(0)
  {
    m_owner->get_game()->add_sprite(this);
  }

SpriteComponent::~SpriteComponent ()
  {
    m_owner->get_game()->remove_sprite(this);
  }

void SpriteComponent::draw (SDL_Renderer *renderer)
  {
    if (m_texture)
      {
        SDL_Rect r;

        // Scale the width/height by owner's scale
        r.w = static_cast<int>(float(m_texture_width) * m_owner->get_scale());
        r.h = static_cast<int>(float(m_texture_height) * m_owner->get_scale());

        // Center the rectangle around the position of the owner
        r.x = static_cast<int>(m_owner->get_position().x - float(r.w) / 2);
        r.y = static_cast<int>(m_owner->get_position().y - float(r.h) / 2);

        // Draw (have to convert angle from radians to degrees, and clockwise to counter)
        SDL_RenderCopyEx(renderer,
                         m_texture,
                         nullptr,
                         &r,
                         -Math::ToDegrees(m_owner->get_rotation()),
                         nullptr,
                         SDL_FLIP_NONE);
      }
  }

void SpriteComponent::set_texture (SDL_Texture *texture)
  {
    m_texture = texture;

    // Set width/height
    SDL_QueryTexture(texture, nullptr, nullptr, &m_texture_width, &m_texture_height);
  }
