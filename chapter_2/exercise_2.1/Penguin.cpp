//
// Created by martin on 28-08-22.
//

#include "Penguin.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <bits/stdc++.h>

using namespace std;

Penguin::Penguin (Game *game) :
    Animal(game)
  {
    // set the image coordiantes and dimensions
    image_rectangel.w = 166;
    image_rectangel.h = 128;
    image_rectangel.x = width / 3 + image_rectangel.w / 2;
    image_rectangel.y = 300;

    // get the text surface
    auto color { SDL_Color { 54, 90, 102, 255 } };
    text_surface = surface_from_font("The Penguin Bleat", font, color);
    text_texture = SDL_CreateTextureFromSurface(game->renderer, text_surface);

    // set the dimensions with the new text surface.
    text_rectangle.w = text_surface->w;
    text_rectangle.h = text_surface->h;
    text_rectangle.x = width / 2 - text_surface->w / 2;
    text_rectangle.y = height - text_surface->h - 50;

    // load the image and get the texture
    image_surface = load_image("../../Assets/animals/penguin.png");
    image_texture = texture_from_surface(image_surface, game->renderer);

    music = Mix_LoadMUS("../../Assets/mp3/penguin.mp3");
  }

void Penguin::update (float delta_time)
  {
    Animal::update(delta_time);
  }

void Penguin::draw ()
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
