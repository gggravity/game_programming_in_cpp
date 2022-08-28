//
// Created by martin on 26-08-22.
//

#pragma once

#include <vector>
#include "SDL2/SDL.h"

struct Vector2
    {
        float x;
        float y;
    };

struct Ball
    {
        Vector2 position;
        Vector2 velocity;
    };

class Game
   {
   public:
      Game ();

      // Initialize the game
      bool initialize ();

      // Runs the game loop until the game is over
      void run_loop ();

      // Shutdown the game
      void shutdown ();

   private:

      // Helper functions for the game loop
      void process_input ();

      void update_game ();

      void generate_output ();

      // Window created by SDL
      SDL_Window *mWindow;

      // Game should continue to run
      bool mIsRunning;

      SDL_Renderer *mRenderer;

      Uint32 mTicksCount;

      Vector2 mPaddlePos;

      int mPaddleDir;

      std::vector<Ball> mBall;

   };
