#pragma once

class Component
   {
   public:
      // Constructor
      // (the lower the update order, the earlier the component updates)
      explicit Component (class Actor *owner, int update_order = 100);

      // Destructor
      virtual ~Component ();

      // Update this component by delta time
      virtual void update (float delta_time);

      [[nodiscard]] int get_update_order () const
        { return m_update_order; }

   protected:
      // Owning actor
      class Actor *m_owner;

      // Update order of component
      int m_update_order;
   };
