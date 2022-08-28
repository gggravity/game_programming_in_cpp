//
// Created by martin on 28-08-22.
//

#pragma once

#include "Animal.h"

struct Bear : Animal
   {
      explicit Bear (Game *game);

      virtual ~Bear ();

      void update (float delta_time) override;

      void draw () override;

      void make_sound () override;

   private:

      SDL_Rect text_rectangle;
      SDL_Texture *text_texture;
      SDL_Surface *text_surface;
   };
