//
// Created by martin on 28-08-22.
//

#include "Narwhal.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <bits/stdc++.h>

using namespace std;

Narwhal::Narwhal (Game *game) :
    Animal(game)
  {
    // set the image coordiantes and dimensions
    image_rectangel.w = 166;
    image_rectangel.h = 128;
    image_rectangel.x = image_rectangel.w / 2;
    image_rectangel.y = 300;

    // load font and get the text surface
    auto font { load_font("../../Assets/FFF_Tusj.ttf", 80) };
    auto color { SDL_Color { 82, 140, 219, 255 } };
    text_surface = surface_from_font("The Narwhal Sings", font, color);
    text_texture = SDL_CreateTextureFromSurface(game->renderer, text_surface);

    // set the dimensions with the new text surface.
    text_rectangle.w = text_surface->w;
    text_rectangle.h = text_surface->h;
    text_rectangle.x = width / 2 - text_surface->w / 2;
    text_rectangle.y = height - text_surface->h - 50;

    // load the image and get the texture
    image_surface = load_image("../../Assets/animals/narwhal.png");
    image_texture = texture_from_surface(image_surface, game->renderer);
  }

void Narwhal::update (float delta_time)
  {
    Animal::update(delta_time);
  }

void Narwhal::draw ()
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
