#include "Component.h"
#include "Actor.h"

Component::Component (Actor *owner, int update_order) :
    m_owner(owner),
    m_update_order(update_order)
  {
    // Add to actor's vector of components
    m_owner->add_component(this);
  }

Component::~Component ()
  {
    m_owner->remove_component(this);
  }

void Component::update (float delta_time)
  {
  }
