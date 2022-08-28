#include "Game.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <bits/stdc++.h>
#include "Actor.h"
#include "Bear.h"

Game::Game () :
    window(nullptr),
    renderer(nullptr),
    is_running(false),
    tick_count(0)
  {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
      {
        cerr << "Unable to initialize SDL: " << SDL_GetError() << endl;
      }

    if (TTF_Init() < 0)
      {
        cerr << "Couldn't initialize TTF lib: " << TTF_GetError() << endl;
      }

    window = SDL_CreateWindow("The safari !!!", 100, 100, width, height, 0);

    if (!window)
      {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
      }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
      {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
      }

    if (IMG_Init(IMG_INIT_PNG) == 0)
      {
        cerr << "Unable to initialize SDL_image: " << SDL_GetError() << endl;
      }

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
                    cout << "clicked mouse (" << x << ", " << y << ")" << endl;
                    for (auto animal : animals)
                      {
                        if (x > animal->x() && x < animal->x() + animal->w())
                          {
                            animal->make_sound();
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
  }

void Game::generate_output ()
  {
    SDL_SetRenderDrawColor(renderer, 123, 123, 123, 255);

    SDL_RenderClear(renderer);

    for (auto animal : animals)
      {
        animal->draw();
      }

    SDL_RenderPresent(renderer);
  }

void Game::load_data ()
  {
    auto bear = new Bear(this);
    animals.emplace_back(bear);
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
    SDL_Quit();
  }
