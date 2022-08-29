//
// Created by martin on 29-08-22.
//

#pragma once

#include "Actor.h"

struct Car : Actor
   {
      explicit Car (class Game *game);

      virtual ~Car ();

      void update (float delta_time) override;

      void draw () override;

      [[nodiscard]] int x () const
        { return image_rectangel.x; }

      [[nodiscard]] int y () const
        { return image_rectangel.y; }

      [[nodiscard]] int w () const
        { return image_rectangel.w; }

      [[nodiscard]] int h () const
        { return image_rectangel.h; }

      bool is_driving;

   private:
      SDL_Rect image_rectangel;
      SDL_Texture *image_texture;
      SDL_Surface *image_surface;
      Mix_Music *music;
   };
