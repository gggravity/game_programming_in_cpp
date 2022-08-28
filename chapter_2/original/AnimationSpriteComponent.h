#pragma once

#include <vector>
#include "SpriteComponent.h"

class AnimationSpriteComponent : public SpriteComponent
   {
   public:
      explicit AnimationSpriteComponent (class Actor *owner, int draw_order = 100);

      // Update animation every frame (overriden from component)
      void update (float delta_time) override;

      // Set the textures used for animation
      void set_animation_textures (const std::vector<SDL_Texture *> &textures);

      // Set/get the animation FPS
      [[nodiscard]] float get_animation_fps () const
        { return m_animation_fps; }

      void set_anim_fps (float fps)
        { m_animation_fps = fps; }

   private:

      // All textures in the animation
      std::vector<SDL_Texture *> m_animation_textures;

      // Current frame displayed
      float m_current_frame;

      // Animation frame rate
      float m_animation_fps;
   };