#include "Game.h"
#include "SDL2/SDL_image.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BackgroundSpriteComponent.h"

Game::Game () :
    m_window(nullptr),
    m_renderer(nullptr),
    m_is_running(true),
    m_updating_actors(false),
    m_ticks_count(0),
    m_ship(nullptr)
  {

  }

bool Game::initialize ()
  {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
      {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
      }

    m_window = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 100, 100, 1024, 768, 0);
    if (!m_window)
      {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
      }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
      {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
      }

    if (IMG_Init(IMG_INIT_PNG) == 0)
      {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
      }

    load_data();

    m_ticks_count = SDL_GetTicks();

    return true;
  }

void Game::run_loop ()
  {
    while (m_is_running)
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
              m_is_running = false;
            break;
          }
      }

    const Uint8 *state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE])
      {
        m_is_running = false;
      }

    // Process ship input
    m_ship->process_keyboard(state);
  }

void Game::update_game ()
  {
    // Compute delta time
    // Wait until 16ms has elapsed since last frame
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_ticks_count + 16))
      { }

    float delta_time = float(SDL_GetTicks() - m_ticks_count) / 1000.0f;

    if (delta_time > 0.05f)
      {
        delta_time = 0.05f;
      }
    m_ticks_count = SDL_GetTicks();

    // Update all actors
    m_updating_actors = true;
    for (auto actor : m_actors)
      {
        actor->update(delta_time);
      }
    m_updating_actors = false;

    // Move any pending actors to mActors
    for (auto pending : m_pending_actors)
      {
        m_actors.emplace_back(pending);
      }
    m_pending_actors.clear();

    // Add any dead actors to a temp vector
    std::vector<Actor *> dead_actors;
    for (auto actor : m_actors)
      {
        if (actor->get_state() == Actor::DEAD)
          {
            dead_actors.emplace_back(actor);
          }
      }

    // Delete dead actors (which removes them from mActors)
    for (auto actor : dead_actors)
      {
        delete actor;
      }
  }

void Game::generate_output ()
  {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    // Draw all sprite components
    for (auto sprite : m_sprites)
      {
        sprite->draw(m_renderer);
      }

    SDL_RenderPresent(m_renderer);
  }

void Game::load_data ()
  {
    // Create player's ship
    m_ship = new Ship(this);
    m_ship->set_position(Vector2(100.0f, 384.0f));
    m_ship->set_scale(1.5f);

    // Create actor for the background (this doesn't need a subclass)
    auto *temp = new Actor(this);
    temp->set_position(Vector2(512.0f, 384.0f));

    // Create the "far back" background
    auto *bg = new BackgroundSpriteComponent(temp);
    bg->set_screen_size(Vector2(1024.0f, 768.0f));

    std::vector<SDL_Texture *> background_textures = {
        get_texture("../../Assets/Far-back01.png"),
        get_texture("../../Assets/Far-back02.png")
    };

    bg->set_background_textures(background_textures);
    bg->set_scroll_speed(-100.0f);

    // Create the closer background
    bg = new BackgroundSpriteComponent(temp, 50);
    bg->set_screen_size(Vector2(1024.0f, 768.0f));

    background_textures = {
        get_texture("../../Assets/Stars.png"),
        get_texture("../../Assets/Stars.png")
    };

    bg->set_background_textures(background_textures);
    bg->set_scroll_speed(-200.0f);
  }

void Game::unload_data ()
  {
    // Delete actors
    // Because ~Actor calls RemoveActor, have to use a different style loop
    while (!m_actors.empty())
      {
        delete m_actors.back();
      }

    // Destroy textures
    for (const auto &i : m_textures)
      {
        SDL_DestroyTexture(i.second);
      }
    m_textures.clear();
  }

SDL_Texture *Game::get_texture (const std::string &file_name)
  {
    SDL_Texture *tex = nullptr;

    // Is the texture already in the map?
    auto iter = m_textures.find(file_name);

    if (iter != m_textures.end())
      {
        tex = iter->second;
      }
    else
      {
        // Load from file
        SDL_Surface *surf = IMG_Load(file_name.c_str());
        if (!surf)
          {
            SDL_Log("Failed to load texture file %s", file_name.c_str());
            return nullptr;
          }

        // Create texture from surface
        tex = SDL_CreateTextureFromSurface(m_renderer, surf);
        SDL_FreeSurface(surf);
        if (!tex)
          {
            SDL_Log("Failed to convert surface to texture for %s", file_name.c_str());
            return nullptr;
          }

        m_textures.emplace(file_name.c_str(), tex);
      }
    return tex;
  }

void Game::shutdown ()
  {
    unload_data();
    IMG_Quit();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
  }

void Game::add_actor (Actor *actor)
  {
    // If we're updating actors, need to add to pending
    if (m_updating_actors)
      {
        m_pending_actors.emplace_back(actor);
      }
    else
      {
        m_actors.emplace_back(actor);
      }
  }

void Game::remove_actor (Actor *actor)
  {
    // Is it in pending actors?
    auto iter = std::find(m_pending_actors.begin(), m_pending_actors.end(), actor);
    if (iter != m_pending_actors.end())
      {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, m_pending_actors.end() - 1);
        m_pending_actors.pop_back();
      }

    // Is it in actors?
    iter = std::find(m_actors.begin(), m_actors.end(), actor);
    if (iter != m_actors.end())
      {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, m_actors.end() - 1);
        m_actors.pop_back();
      }
  }

void Game::add_sprite (SpriteComponent *sprite)
  {
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int my_draw_order = sprite->get_draw_order();
    auto iter = m_sprites.begin();
    for (;
        iter != m_sprites.end() ; ++iter)
      {
        if (my_draw_order < ( *iter )->get_draw_order())
          {
            break;
          }
      }

    // Inserts element before position of iterator
    m_sprites.insert(iter, sprite);
  }

void Game::remove_sprite (SpriteComponent *sprite)
  {
    // (We can't swap because it ruins ordering)
    auto iter = std::find(m_sprites.begin(), m_sprites.end(), sprite);
    m_sprites.erase(iter);
  }
