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

   private:
      bool is_driving;
      SDL_Rect image_rectangel;
      SDL_Texture *image_texture;
      SDL_Surface *image_surface;
      Mix_Music *music{};
   };
