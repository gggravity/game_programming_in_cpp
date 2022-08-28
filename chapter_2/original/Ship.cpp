#include "Ship.h"
#include "AnimationSpriteComponent.h"
#include "Game.h"

Ship::Ship (Game *game) :
    Actor(game),
    m_right_speed(0.0f),
    m_down_speed(0.0f)
  {
    // Create an animated sprite component
    auto *asc = new AnimationSpriteComponent(this);
    std::vector<SDL_Texture *> animations = {
        game->get_texture("../../Assets/Ship01.png"),
        game->get_texture("../../Assets/Ship02.png"),
        game->get_texture("../../Assets/Ship03.png"),
        game->get_texture("../../Assets/Ship04.png"),
    };
    asc->set_animation_textures(animations);
  }

void Ship::update_actor (float delta_time)
  {
    Actor::update_actor(delta_time);

    // Update position based on speeds and delta time
    Vector2 pos = get_position();
    pos.x += m_right_speed * delta_time;
    pos.y += m_down_speed * delta_time;

    // Restrict position to the left half of screen
    if (pos.x < 25.0f)
      {
        pos.x = 25.0f;
      }
    else if (pos.x > 500.0f)
      {
        pos.x = 500.0f;
      }
    if (pos.y < 25.0f)
      {
        pos.y = 25.0f;
      }
    else if (pos.y > 743.0f)
      {
        pos.y = 743.0f;
      }
    set_position(pos);
  }

void Ship::process_keyboard (const uint8_t *state)
  {
    m_right_speed = 0.0f;
    m_down_speed = 0.0f;

    // right/left
    if (state[SDL_SCANCODE_D])
      {
        m_right_speed += 250.0f;
      }
    if (state[SDL_SCANCODE_A])
      {
        m_right_speed -= 250.0f;
      }

    // up/down
    if (state[SDL_SCANCODE_S])
      {
        m_down_speed += 300.0f;
      }
    if (state[SDL_SCANCODE_W])
      {
        m_down_speed -= 300.0f;
      }
  }
