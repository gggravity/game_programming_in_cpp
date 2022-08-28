//
// Created by martin on 28-08-22.
//

#include <bits/stdc++.h>
#include "Animal.h"

using namespace std;

Animal::Animal (class Game *game) :
    Actor(game),
    making_sound(false)
  {

  }

Animal::~Animal ()
  {
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
  }

void Animal::update (float delta_time)
  {

  }

void Animal::draw ()
  {
  }

void Animal::make_sound ()
  {
    making_sound = !making_sound;

    for (auto animal : game->animals)
      {
        if (animal != this)
          {
            animal->making_sound = false;
          }
      }
  }

SDL_Surface *load_image (const string &file_name)
  {
    // Load from file
    SDL_Surface *surface { IMG_Load(file_name.c_str()) };

    if (!surface)
      {
        SDL_Log("Failed to load texture file %s", file_name.c_str());
      }
    else
      {
        cout << "Loaded texture file " << file_name << " succesfull." << endl;
      }
    return surface;
  }

SDL_Texture *texture_from_surface (SDL_Surface *surface, SDL_Renderer *renderer)
  {
// Create texture from surface
    SDL_Texture *texture { SDL_CreateTextureFromSurface(renderer, surface) };
    SDL_FreeSurface(surface);
    if (!texture)
      {
        SDL_Log("Failed to convert surface to texture.");
      }
    else
      {
        cout << "converted surface to texture succesfull." << endl;
      }
    return texture;
  }

TTF_Font *load_font (const string &file_name, int size)
  {
    auto font { TTF_OpenFont(file_name.c_str(), size) };

    if (!font)
      {
        cerr << "Unable to load font " << TTF_GetError() << endl;
      }
    else
      {
        cout << "font loaded succesfull!" << endl;
      }
    return font;
  }

SDL_Surface *surface_from_font (const string &text, TTF_Font *font, SDL_Color color)
  {
    auto m_text_surface = TTF_RenderText_Solid(font, text.c_str(), color);

    if (m_text_surface == nullptr)
      {
        cerr << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
      }
    else
      {
        cout << "rendered text surface!" << endl;
      }
    return m_text_surface;
  }