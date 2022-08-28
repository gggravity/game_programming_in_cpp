//
// Created by martin on 27-08-22.
//

#pragma once

#pragma once

#include "Component.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
   {
   public:
      // (Lower draw order corresponds with further back)
      explicit SpriteComponent (class Actor *owner, int draw_order = 100);

      ~SpriteComponent () override;

      virtual void draw (SDL_Renderer *renderer);

      virtual void set_texture (SDL_Texture *texture);

      [[nodiscard]] int get_draw_order () const
        { return m_draw_order; }

      [[nodiscard]] int get_texture_height () const
        { return m_texture_height; }

      [[nodiscard]] int get_texture_width () const
        { return m_texture_width; }

   protected:
      SDL_Texture *m_texture;
      int m_draw_order;
      int m_texture_width;
      int m_texture_height;
   };
