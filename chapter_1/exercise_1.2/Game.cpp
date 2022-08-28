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
    mPaddlePos { 10.0f, 768.0f / 2.0f },
    mPaddleDir(0),
    mTicksCount(0)
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

    mBall.push_back({ { 1024.0f / 2.0f, 768.0f / 2.0f },
                      { -50.0f,        135.0f } });

    mBall.push_back({ { 1024.0f / 2.0f, 768.0f / 2.0f },
                      { 50.0f,         35.0f } });

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

    mPaddleDir = 0;

    if (state[SDL_SCANCODE_W])
      {
        mPaddleDir -= 1;
      }

    if (state[SDL_SCANCODE_S])
      {
        mPaddleDir += 1;
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
    if (mPaddleDir != 0)
      {
        mPaddlePos.y += float(mPaddleDir) * 300.0f * deltaTime;
        // Make sure paddle doesn't move off-screen!
        if (mPaddlePos.y < ( paddleH / 2.0f + thickness ))
          {
            mPaddlePos.y = paddleH / 2.0f + thickness;
          }
        else if (mPaddlePos.y > ( 768.0f - paddleH / 2.0f - thickness ))
          {
            mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
          }
      }

    for (auto &ball : mBall)
      {
        // Update ball position based on ball velocity
        ball.position.x += ball.velocity.x * deltaTime;
        ball.position.y += ball.velocity.y * deltaTime;

        // Bounce if needed
        // Did we intersect with the paddle?
        float diff = mPaddlePos.y - ball.position.y;

        // Take absolute value of difference
        diff = ( diff > 0.0f ) ? diff : -diff;

        if (diff <= paddleH / 2.0f && // Our y-difference is small enough
            ball.position.x <= 25.0f && ball.position.x >= 20.0f && // We are in the correct x-position
            ball.velocity.x < 0.0f)// The ball is moving to the left
          {
            ball.velocity.x *= -1.0f;
          }
        else if (ball.position.x <= 0.0f) // Did the ball go off the screen? (if so, end game)
          {
            mIsRunning = false;
          }
        else if (ball.position.x >= ( 1024.0f - thickness )
                 && ball.velocity.x > 0.0f) // Did the ball collide with the right wall?
          {
            ball.velocity.x *= -1.0f;
          }
        if (ball.position.y <= thickness && ball.velocity.y < 0.0f) // Did the ball collide with the top wall?
          {
            ball.velocity.y *= -1;
          }
        else if (ball.position.y >= ( 768 - thickness )
                 && ball.velocity.y > 0.0f) // Did the ball collide with the bottom wall?
          {
            ball.velocity.y *= -1;
          }
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

    // Draw right wall
    wall.x = 1024 - thickness;
    wall.y = 0;
    wall.w = thickness;
    wall.h = 1024;
    SDL_RenderFillRect(mRenderer, &wall);

    // Draw paddle
    SDL_Rect paddle
        {
            static_cast<int>(mPaddlePos.x),
            static_cast<int>(mPaddlePos.y - paddleH / 2),
            thickness,
            static_cast<int>(paddleH)
        };
    SDL_RenderFillRect(mRenderer, &paddle);

    for (auto &b : mBall)
      {
        SDL_Rect ball
            {
                static_cast<int>(b.position.x - thickness / 2.0f),
                static_cast<int>(b.position.y - thickness / 2.0f),
                thickness,
                thickness
            };

        SDL_RenderFillRect(mRenderer, &ball);
      }
    // swap the front and back buffers
    SDL_RenderPresent(mRenderer);
  }
