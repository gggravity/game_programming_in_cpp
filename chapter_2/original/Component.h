//
// Created by martin on 27-08-22.
//
#pragma once

#pragma once

class Component
   {
   public:
      // Constructor
      // (the lower the update order, the earlier the component updates)
      explicit Component (class Actor *owner, int updateOrder = 100);

      // Destructor
      virtual ~Component ();

      // Update this component by delta time
      virtual void Update (float deltaTime);

      [[nodiscard]] int GetUpdateOrder () const
        { return mUpdateOrder; }

   protected:
      // Owning actor
      class Actor *mOwner;

      // Update order of component
      int mUpdateOrder;
   };
