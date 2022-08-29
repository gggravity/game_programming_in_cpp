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
    font = load_font("../../Assets/FFF_Tusj.ttf", 80);
  }

Animal::~Animal ()
  {
    SDL_FreeSurface(text_surface);
    SDL_DestroyTexture(text_texture);
    Mix_FreeMusic(music);
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

    Mix_PlayMusic(music, false);
//    if (!Mix_PlayingMusic())
//      {
//        Mix_ResumeMusic();
//      }
  }