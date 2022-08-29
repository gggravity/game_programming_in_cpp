//
// Created by martin on 28-08-22.
//

#pragma once

#include <bits/stdc++.h>
#include "Game.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

using namespace std;

struct Actor
   {
      Actor (class Game *game);

      // Called every frame to update the Actor
      virtual void update (float delta_time);

      // Called every frame to draw the Actor
      virtual void draw ();

   protected:
      class Game *game;

   };

SDL_Surface *load_image (const string &file_name);

SDL_Texture *texture_from_surface (SDL_Surface *surface, SDL_Renderer *renderer);

TTF_Font *load_font (const string &file_name, int size);

SDL_Surface *surface_from_font (const string &text, TTF_Font *font, SDL_Color color);