//
// Created by martin on 28-08-22.
//

#pragma once

#include "Animal.h"

struct Penguin : Animal
   {
        explicit Penguin (Game *game);

        void update (float delta_time) override;

        void draw () override;
   };
