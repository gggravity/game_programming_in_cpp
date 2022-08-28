#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor (Game *game) :
    m_state(ACTIVE),
    m_position(),
    m_scale(1.0f),
    m_rotation(0.0f),
    m_game(game)
  {
    m_game->add_actor(this);
  }

Actor::~Actor ()
  {
    m_game->remove_actor(this);

    // Need to delete components
    // Because ~Component calls RemoveComponent, need a different style loop
    while (!m_components.empty())
      {
        delete m_components.back();
      }
  }

void Actor::update (float delta_time)
  {
    if (m_state == ACTIVE)
      {
        update_components(delta_time);
        update_actor(delta_time);
      }
  }

void Actor::update_components (float delta_time)
  {
    for (auto comp : m_components)
      {
        comp->update(delta_time);
      }
  }

void Actor::update_actor (float delta_time)
  {
  }

void Actor::add_component (struct Component *component)
  {
    // Find the insertion point in the sorted vector
    // (The first element with an order higher than me)
    int my_order = component->get_update_order();
    auto iter = m_components.begin();
    for (;
        iter != m_components.end() ;
        ++iter)
      {
        if (my_order < ( *iter )->get_update_order())
          {
            break;
          }
      }

    // Inserts element before position of iterator
    m_components.insert(iter, component);
  }

void Actor::remove_component (struct Component *component)
  {
    auto iter = std::find(m_components.begin(), m_components.end(), component);
    if (iter != m_components.end())
      {
        m_components.erase(iter);
      }
  }
