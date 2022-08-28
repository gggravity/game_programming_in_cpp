//
// Created by martin on 28-08-22.
//

#pragma once

#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Actor.h"

struct Animal : Actor
   {
      explicit Animal (class Game *game);

      void update (float delta_time) override;

      void draw () override;

      virtual void make_sound ();

      int x ()
        { return image_rectangel.x; }

      int y ()
        { return image_rectangel.y; }

      int w ()
        { return image_rectangel.w; }

      int h ()
        { return image_rectangel.h; }

   protected:
      SDL_Rect image_rectangel;
      SDL_Texture *image_texture;
      SDL_Surface *image_surface;
   };

SDL_Surface *load_image (const string &file_name);

SDL_Texture *texture_from_surface (SDL_Surface *surface, SDL_Renderer *renderer);

TTF_Font *load_font (const string &file_name, int size);

SDL_Surface *surface_from_font (const string &text, TTF_Font *font, SDL_Color color);