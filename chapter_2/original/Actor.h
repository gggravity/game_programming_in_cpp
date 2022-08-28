#pragma once

#include <vector>
#include "Math.h"

class Actor
   {
   public:

      // Used to track state of actor
      enum State
          {
              ACTIVE,
              PAUSED,
              DEAD
          };

      // Constructor/destructor
      explicit Actor (class Game *game);

      virtual ~Actor ();

      // Update function called from Game (not overridable)
      void update (float delta_time);

      // Updates all the components attached to the actor (not overridable)
      void update_components (float delta_time);

      // Any actor-specific update code (overridable)
      virtual void update_actor (float delta_time);

      // Getters/setters
      [[nodiscard]] const Vector2 &get_position () const
        { return m_position; }

      void set_position (const Vector2 &pos)
        { m_position = pos; }

      [[nodiscard]] float get_scale () const
        { return m_scale; }

      void set_scale (float scale)
        { m_scale = scale; }

      [[nodiscard]] float get_rotation () const
        { return m_rotation; }

      void set_rotation (float rotation)
        { m_rotation = rotation; }

      [[nodiscard]] State get_state () const
        { return m_state; }

      void set_state (State state)
        { m_state = state; }

      class Game *get_game ()
        { return m_game; }

      // Add/remove components
      void add_component (class Component *component);

      void remove_component (class Component *component);

   private:
      // Actor's state
      State m_state;
      // Transform

      Vector2 m_position; // Center position of actor
      float m_scale;// Uniforms scale of actor (1.0f for 100%)
      float m_rotation;// Rotation angle (in radians)

      // Components held by this actor
      std::vector<class Component *> m_components;

      class Game *m_game;
   };