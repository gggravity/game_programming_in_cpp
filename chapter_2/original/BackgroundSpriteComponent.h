//
// Created by martin on 27-08-22.
//

#pragma once

#include <vector>
#include "SpriteComponent.h"
#include "Math.h"

class BackgroundSpriteComponent : public SpriteComponent
   {
   public:

      // Set draw order to default to lower (so it's in the background)
      explicit BackgroundSpriteComponent (class Actor *owner, int draw_order = 10);

      // Update/draw overriden from parent
      void update (float delta_time) override;

      void draw (SDL_Renderer *renderer) override;

      // Set the textures used for the background
      void set_background_textures (const std::vector<SDL_Texture *> &textures);

      // Get/set screen size and scroll speed
      void set_screen_size (const Vector2 &size)
        { m_screen_size = size; }

      void set_scroll_speed (float speed)
        { m_scroll_speed = speed; }

      [[nodiscard]] float get_scroll_speed () const
        { return m_scroll_speed; }

   private:

      // Struct to encapsulate each BG image and its offset
      struct BGTexture
          {
              SDL_Texture *m_texture{};
              Vector2 m_offset;
          };

      std::vector<BGTexture> m_background_textures;
      Vector2 m_screen_size;
      float m_scroll_speed;
   };