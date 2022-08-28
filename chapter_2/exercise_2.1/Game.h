#pragma once

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
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

   private:
      void process_input ();

      void update_game ();

      void generate_output ();

      void load_data ();

      void unload_data ();

      vector<class Animal *> animals;

      SDL_Window *window;
      Uint32 tick_count;

   };
