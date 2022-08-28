#pragma once

#include <cstdint>
#include "Actor.h"

class Ship : public Actor
   {
   public:
      explicit Ship (class Game *game);

      void update_actor (float delta_time) override;

      void process_keyboard (const uint8_t *state);

      [[nodiscard]] float get_right_speed () const
        { return m_right_speed; }

      [[nodiscard]] float get_down_speed () const
        { return m_down_speed; }

   private:
      float m_right_speed;
      float m_down_speed;
   };