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
      bool Initialize ();

      // Runs the game loop until the game is over
      void RunLoop ();

      // Shutdown the game
      void Shutdown ();

   private:

      // Helper functions for the game loop
      void ProcessInput ();

      void UpdateGame ();

      void GenerateOutput ();

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
