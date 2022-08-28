#include "AnimationSpriteComponent.h"

AnimationSpriteComponent::AnimationSpriteComponent (Actor *owner, int draw_order) :
    SpriteComponent(owner, draw_order),
    m_current_frame(0.0f),
    m_animation_fps(24.0f)
  {

  }

void AnimationSpriteComponent::update (float delta_time)
  {
    SpriteComponent::update(delta_time);
    if (!m_animation_textures.empty())
      {
        // Update the current frame based on frame rate and delta time
        m_current_frame += m_animation_fps * delta_time;

        // Wrap current frame if needed
        while (m_current_frame >= static_cast<float>(m_animation_textures.size()))
          {
            m_current_frame -= static_cast<float>(m_animation_textures.size());
          }

        // Set the current texture
        set_texture(m_animation_textures[static_cast<int>(m_current_frame)]);
      }
  }

void AnimationSpriteComponent::set_animation_textures (const std::vector<SDL_Texture *> &textures)
  {
    m_animation_textures = textures;
    if (!m_animation_textures.empty())
      {
        // Set the active texture to first frame
        m_current_frame = 0.0f;
        set_texture(m_animation_textures[0]);
      }
  }
