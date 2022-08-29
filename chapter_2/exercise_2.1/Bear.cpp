//
// Created by martin on 28-08-22.
//

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <bits/stdc++.h>
#include "Bear.h"

using namespace std;

Bear::Bear (Game *game) :
    Animal(game)
  {
    // set the image coordiantes and dimensions
    image_rectangel.w = 162;
    image_rectangel.h = 128;
    image_rectangel.x = image_rectangel.w / 2;
    image_rectangel.y = 100;

    // get the text surface
    auto color { SDL_Color { 142, 90, 50, 255 } };
    text_surface = surface_from_font("The Bear ROARS", font, color);
    text_texture = SDL_CreateTextureFromSurface(game->renderer, text_surface);

    // set the dimensions with the new text surface.
    text_rectangle.w = text_surface->w;
    text_rectangle.h = text_surface->h;
    text_rectangle.x = width / 2 - text_surface->w / 2;
    text_rectangle.y = height - text_surface->h - 50;

    // load the image and get the texture
    image_surface = load_image("../../Assets/animals/bear.png");
    image_texture = texture_from_surface(image_surface, game->renderer);

    music = Mix_LoadMUS("../../Assets/mp3/bear.mp3");
  }

void Bear::update (float delta_time)
  {
    Animal::update(delta_time);
  }

void Bear::draw ()
  {
    SDL_RenderCopyEx(game->renderer,
                     image_texture,
                     nullptr,
                     &image_rectangel,
                     0,
                     nullptr,
                     SDL_FLIP_NONE);

    if (making_sound)
      {
        SDL_RenderCopy(game->renderer, text_texture, nullptr, &text_rectangle);
      }
  }


