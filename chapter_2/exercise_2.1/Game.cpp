#include "Game.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <bits/stdc++.h>
#include "Actor.h"
#include "Bear.h"
#include "Hippo.h"
#include "Pig.h"
#include "Narwhal.h"
#include "Penguin.h"
#include "Walrus.h"
#include "Car.h"

Game::Game () :
    window(nullptr),
    renderer(nullptr),
    is_running(false),
    tick_count(0),
    car(nullptr)
  {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
      {
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
      }

    if (TTF_Init() < 0)
      {
        cerr << "Couldn't initialize TTF lib: " << TTF_GetError() << endl;
        exit(EXIT_FAILURE);
      }

    window = SDL_CreateWindow("The safari !!!", 100, 100, width, height, 0);

    if (!window)
      {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
      }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
      {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
      }

    if (IMG_Init(IMG_INIT_PNG) == 0)
      {
        cerr << "Unable to initialize SDL_image: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
      }

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
      {
        cerr << "Unable to initialize SDL_audio: " << SDL_GetError() << endl;
        exit(EXIT_FAILURE);
      }

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    load_data();

    tick_count = SDL_GetTicks();

    is_running = true;
  }

void Game::run_loop ()
  {
    while (is_running)
      {
        process_input();
        update_game();
        generate_output();
      }
  }

void Game::process_input ()
  {
    SDL_Event event;
    while (SDL_PollEvent(&event))
      {
        switch (event.type)
          {
            case SDL_QUIT:
              is_running = false;
            break;
            case SDL_MOUSEBUTTONDOWN:
              {
                if (event.button.button == SDL_BUTTON_LEFT)
                  {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
//                    cout << "clicked mouse (" << x << ", " << y << ")" << endl;

                    // check if clicked on the car
                    if (x > car->x() && x < car->x() + car->w() &&
                        y > car->y() && y < car->y() + car->h())
                      {
                        car->is_driving = !car->is_driving;
                        continue;
                      }

                    // check if clicked on one of the animals
                    for (auto animal : animals)
                      {
                        if (x > animal->x() && x < animal->x() + animal->w() &&
                            y > animal->y() && y < animal->y() + animal->h())
                          {
                            animal->make_sound();
                          }
                        else
                          {
                            animal->making_sound = false;
                          }
                      }

                  }
              }
            break;
          }

      }

    const Uint8 *state = SDL_GetKeyboardState(nullptr);

    if (state[SDL_SCANCODE_ESCAPE])
      {
        is_running = false;
      }
    if (state[SDL_SCANCODE_Q])
      {
        is_running = false;
      }
  }

void Game::update_game ()
  {
    // Compute delta time
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), tick_count + 16))
      { }

    float delta_time = float(SDL_GetTicks() - tick_count) / 1000.0f;

    if (delta_time > 0.05f)
      {
        delta_time = 0.05f;
      }
    tick_count = SDL_GetTicks();

    if (!Mix_PlayingMusic())
      {
        for (auto animal : animals)
          {
            animal->making_sound = false;
          }
      }

    car->update(delta_time);
  }

void Game::generate_output ()
  {
    SDL_SetRenderDrawColor(renderer, 66, 66, 66, 255);

    SDL_RenderClear(renderer);

    for (auto animal : animals)
      {
        animal->draw();
      }

    car->draw();

    SDL_RenderPresent(renderer);
  }

void Game::load_data ()
  {
    auto bear = new Bear(this);
    animals.emplace_back(bear);

    auto hippo = new Hippo(this);
    animals.emplace_back(hippo);

    auto pig = new Pig(this);
    animals.emplace_back(pig);

    auto narwhal = new Narwhal(this);
    animals.emplace_back(narwhal);

    auto penguin = new Penguin(this);
    animals.emplace_back(penguin);

    auto whalrus = new Walrus(this);
    animals.emplace_back(whalrus);

    car = new Car(this);
  }

void Game::unload_data ()
  {

  }

Game::~Game ()
  {
    for (auto animal : animals)
      {
        delete animal;
      }

    unload_data();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
//    Mix_FreeMusic(music); //
    SDL_Quit();
  }
