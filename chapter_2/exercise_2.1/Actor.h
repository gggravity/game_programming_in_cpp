//
// Created by martin on 28-08-22.
//

#pragma once

#include "Game.h"

struct Actor
   {
      Actor (class Game *game);

      // Called every frame to update the Actor
      virtual void update (float delta_time);

      // Called every frame to draw the Actor
      virtual void draw ();

   protected:
      class Game *game;


   };
