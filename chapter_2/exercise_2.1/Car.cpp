//
// Created by martin on 29-08-22.
//

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Car.h"

Car::Car (struct Game *game) :
    Actor(game),
    image_surface(nullptr),
    image_texture(nullptr),
    image_rectangel { 0, 0, 0, 0 },
    music(nullptr),
    is_driving(true)
  {
    // set the image coordiantes and dimensions
    image_rectangel.w = 288;
    image_rectangel.h = 105;
    image_rectangel.x = width / 2 - image_rectangel.w / 2;
    image_rectangel.y = 500;

    // load the image and get the texture
    image_surface = load_image("../../Assets/classic_car.png");
    image_texture = texture_from_surface(image_surface, game->renderer);

    // load sound effect
    music = Mix_LoadMUS("../../Assets/mp3/car.mp3");

    Mix_PlayMusic(music, true);
  }

Car::~Car ()
  {
    Mix_FreeMusic(music);
    SDL_FreeSurface(image_surface);
    SDL_DestroyTexture(image_texture);
  }

void Car::update (float delta_time)
  {
    if (is_driving)
      {
        if (!Mix_PlayingMusic())
          {
            Mix_PlayMusic(music, true);
          }
        image_rectangel.x++;
        if (image_rectangel.x > width)
          {
            image_rectangel.x = -image_rectangel.w;
          }
      }
//    else
//      {
//        if (Mix_PlayingMusic())
//          {
//            Mix_HaltMusic();
//          }
//      }
  }

void Car::draw ()
  {
    SDL_RenderCopyEx(game->renderer,
                     image_texture,
                     nullptr,
                     &image_rectangel,
                     0,
                     nullptr,
                     SDL_FLIP_HORIZONTAL);
  }

