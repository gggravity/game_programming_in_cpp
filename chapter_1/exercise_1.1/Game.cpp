//
// Created by martin on 26-08-22.
//

const int thickness = 15;
const float paddleH = 100.0f;

#include "Game.h"

Game::Game () :
    mWindow(nullptr),
    mIsRunning(true),
    mRenderer(nullptr),
    mPaddlePos_1 { 0.0f, 768.0f / 2.0f },
    mPaddlePos_2 { 1024.0f - 15.0f, 768.0f / 2.0f },
    mBallPos { 1024.0f / 2.0f, 768.0f / 2.0f },
    mTicksCount(0),
    mPaddleDir_1(0),
    mPaddleDir_2(0),
    mBallVel { 100.0f, 20.0f }
  {

  }

bool Game::initialize ()
  {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
      {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
      }

    mWindow = SDL_CreateWindow(
        "Game Programming in C++ (Chapter 1)", // Window title
        100, // Top left x-coordinate of window
        100, // Top left y-coordinate of window
        1024, // Width of window
        768, // Height of window
        0 // Flags (0 for no flags set)
    );

    if (!mWindow)
      {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
      }

    mRenderer = SDL_CreateRenderer(
        mWindow, // Window to create renderer for
        -1, // Usually -1
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    return true;
  }

void Game::run_loop ()
  {
    while (mIsRunning)
      {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
      }
  }

void Game::shutdown ()
  {
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
    SDL_DestroyRenderer(mRenderer);
  }

void Game::process_input ()
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
      {
        switch (event.type)
          {
            // If this is an SDL_QUIT event, end loop
            case SDL_QUIT:
              mIsRunning = false;
            break;
          }
      }

    // Get state of keyboard
    const Uint8 *state = SDL_GetKeyboardState(nullptr);// If escape is pressed, also end loop

    if (state[SDL_SCANCODE_ESCAPE])
      {
        mIsRunning = false;
      }

    mPaddleDir_1 = 0;

    if (state[SDL_SCANCODE_W])
      {
        mPaddleDir_1 -= 1;
      }

    if (state[SDL_SCANCODE_S])
      {
        mPaddleDir_1 += 1;
      }

    mPaddleDir_2 = 0;

    if (state[SDL_SCANCODE_I])
      {
        mPaddleDir_2 -= 1;
      }

    if (state[SDL_SCANCODE_K])
      {
        mPaddleDir_2 += 1;
      }

  }

void Game::update_game ()
  {
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
      { }

    // Delta time is the difference in ticks from last frame// (converted to seconds)
    float deltaTime = float(SDL_GetTicks() - mTicksCount) / 1000.0f;

    // Clamp maximum delta time value
    if (deltaTime > 0.05f)
      {
        deltaTime = 0.05f;
      }

    // Update paddle position based on direction
    if (mPaddleDir_1 != 0)
      {
        mPaddlePos_1.y += float(mPaddleDir_1) * 300.0f * deltaTime;
        // Make sure paddle doesn't move off-screen!
        if (mPaddlePos_1.y < ( paddleH / 2.0f + thickness ))
          {
            mPaddlePos_1.y = paddleH / 2.0f + thickness;
          }
        else if (mPaddlePos_1.y > ( 768.0f - paddleH / 2.0f - thickness ))
          {
            mPaddlePos_1.y = 768.0f - paddleH / 2.0f - thickness;
          }
      }

    if (mPaddleDir_2 != 0)
      {
        mPaddlePos_2.y += float(mPaddleDir_2) * 300.0f * deltaTime;
        // Make sure paddle doesn't move off-screen!
        if (mPaddlePos_2.y < ( paddleH / 2.0f + thickness ))
          {
            mPaddlePos_2.y = paddleH / 2.0f + thickness;
          }
        else if (mPaddlePos_2.y > ( 768.0f - paddleH / 2.0f - thickness ))
          {
            mPaddlePos_2.y = 768.0f - paddleH / 2.0f - thickness;
          }
      }


    // Update ball position based on ball velocity
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    // Bounce if needed
    // Did we intersect with the paddle?
    float diff_1 = mPaddlePos_1.y - mBallPos.y;
    float diff_2 = mPaddlePos_2.y - mBallPos.y;

    // Take absolute value of difference
    diff_1 = ( diff_1 > 0.0f ) ? diff_1 : -diff_1;
    diff_2 = ( diff_2 > 0.0f ) ? diff_2 : -diff_2;

    if (diff_1 <= paddleH / 2.0f && // Our y-difference is small enough
        mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && // We are in the correct x-position
        mBallVel.x < 0.0f)// The ball is moving to the left
      {
        mBallVel.x *= -1.0f;
      }
    else if (diff_2 <= paddleH / 2.0f && // Our y-difference is small enough
        mBallPos.x >= 1024.0f - 25.0f && mBallPos.x <= 1024.0f - 20.0f && // We are in the correct x-position
        mBallVel.x > 0.0f)// The ball is moving to the right
      {
        mBallVel.x *= -1.0f;
      }
    else if (mBallPos.x <= 0.0f || mBallPos.x >= 1024.0f) // Did the ball go off the screen? (if so, end game)
      {
        mIsRunning = false;
      }
    if (mBallPos.y <= thickness && mBallVel.y < 0.0f) // Did the ball collide with the top wall?
      {
        mBallVel.y *= -1;
      }
    else if (mBallPos.y >= ( 768 - thickness ) && mBallVel.y > 0.0f) // Did the ball collide with the bottom wall?
      {
        mBallVel.y *= -1;
      }
  }

void Game::generate_output ()
  {
    SDL_SetRenderDrawColor(
        mRenderer,
        0, // R
        0, // G
        255, // B
        255 // A
    );

    // clear the back buffer to the current draw color
    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

    // Draw top wall
    SDL_Rect wall
        {
            0, // Top left x
            0, // Top left y
            1024,// Width
            thickness // Height
        };

    SDL_RenderFillRect(mRenderer, &wall);

    // Draw bottom wall
    wall.y = 768 - thickness;
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw paddle
    SDL_Rect paddle_1
        {
            static_cast<int>(mPaddlePos_1.x),
            static_cast<int>(mPaddlePos_1.y - paddleH / 2),
            thickness,
            static_cast<int>(paddleH)
        };
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &paddle_1);

    // Draw paddle
    SDL_Rect paddle_2
        {
            static_cast<int>(mPaddlePos_2.x),
            static_cast<int>(mPaddlePos_2.y - paddleH / 2),
            thickness,
            static_cast<int>(paddleH)
        };

    SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
    SDL_RenderFillRect(mRenderer, &paddle_2);

    SDL_Rect ball
        {
            static_cast<int>(mBallPos.x - thickness / 2.0f),
            static_cast<int>(mBallPos.y - thickness / 2.0f),
            thickness,
            thickness
        };
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderFillRect(mRenderer, &ball);

    // swap the front and back buffers
    SDL_RenderPresent(mRenderer);
  }
