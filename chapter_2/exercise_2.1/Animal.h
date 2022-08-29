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

      virtual ~Animal ();

      void update (float delta_time) override;

      void draw () override;

      void make_sound ();

      bool making_sound;

      Mix_Music *music{};

      TTF_Font *font;

      [[nodiscard]] int x () const
        { return image_rectangel.x; }

      [[nodiscard]] int y () const
        { return image_rectangel.y; }

      [[nodiscard]] int w () const
        { return image_rectangel.w; }

      [[nodiscard]] int h () const
        { return image_rectangel.h; }

   protected:
      SDL_Rect image_rectangel { };
      SDL_Texture *image_texture { };
      SDL_Surface *image_surface { };

      SDL_Rect text_rectangle { };
      SDL_Texture *text_texture { };
      SDL_Surface *text_surface { };
   };

SDL_Surface *load_image (const string &file_name);

SDL_Texture *texture_from_surface (SDL_Surface *surface, SDL_Renderer *renderer);

TTF_Font *load_font (const string &file_name, int size);

SDL_Surface *surface_from_font (const string &text, TTF_Font *font, SDL_Color color);