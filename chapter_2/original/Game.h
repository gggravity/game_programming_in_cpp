#pragma once

#include "SDL2/SDL.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include <unordered_map>
#include <string>
#include <vector>

class Game
   {
   public:
      Game ();

      bool initialize ();

      void run_loop ();

      void shutdown ();

      void add_actor (Actor *actor);

      void remove_actor (class Actor *actor);

      void add_sprite (SpriteComponent *sprite);

      void remove_sprite (class SpriteComponent *sprite);

      SDL_Texture *get_texture (const std::string &file_name);

   private:
      void process_input ();

      void update_game ();

      void generate_output ();

      void load_data ();

      void unload_data ();

      // Map of textures loaded
      std::unordered_map<std::string, SDL_Texture *> m_textures;

      // All the actors in the game
      std::vector<class Actor *> m_actors;
      // Any pending actors
      std::vector<class Actor *> m_pending_actors;

      // All the sprite components drawn
      std::vector<class SpriteComponent *> m_sprites;

      SDL_Window *m_window;
      SDL_Renderer *m_renderer;
      Uint32 m_ticks_count;
      bool m_is_running;
      // Track if we're updating actors right now
      bool m_updating_actors;

      // Game-specific
      class Ship *m_ship; // Player's ship
   };
