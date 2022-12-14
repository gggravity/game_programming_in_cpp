#pragma once

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "Actor.h"

using namespace std;

constexpr int width { 1024 };

constexpr int height { 768 };

struct Game
   {
      Game ();

      virtual ~Game ();

      void run_loop ();

      bool is_running;

      SDL_Renderer *renderer;

      vector<class Animal *> animals;

   private:
      void process_input ();

      void update_game ();

      void generate_output ();

      void load_data ();

      void unload_data ();

      SDL_Window *window;
      Uint32 tick_count;

      class Car *car;
   };
