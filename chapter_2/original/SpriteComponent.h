//
// Created by martin on 27-08-22.
//

#pragma once

#pragma once

#include "Component.h"
#include "SDL2/SDL.h"

class SpriteComponent : public Component
   {
   public:
      // (Lower draw order corresponds with further back)
      explicit SpriteComponent (class Actor *owner, int drawOrder = 100);

      ~SpriteComponent ();

      virtual void Draw (SDL_Renderer *renderer);

      virtual void SetTexture (SDL_Texture *texture);

      [[nodiscard]] int GetDrawOrder () const
        { return mDrawOrder; }

      [[nodiscard]] int GetTexHeight () const
        { return mTexHeight; }

      [[nodiscard]] int GetTexWidth () const
        { return mTexWidth; }

   protected:
      SDL_Texture *mTexture;
      int mDrawOrder;
      int mTexWidth;
      int mTexHeight;
   };
