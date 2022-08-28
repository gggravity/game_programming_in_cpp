#include <bits/stdc++.h>
#include "Game.h"

using namespace std;

int main (int argc, char **argv)
  {
    Game game;

    if (game.is_running)
      {
        game.run_loop();
      }

    return 0;
  }