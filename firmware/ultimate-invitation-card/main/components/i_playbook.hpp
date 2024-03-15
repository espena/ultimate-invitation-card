#ifndef __i_playbook_hpp__
#define __i_playbook_hpp__

#include "event/i_event_dispatcher.hpp"
#include "playbook_item.hpp"

namespace espena {
  class i_playbook : public components::event::i_event_dispatcher {
    public:
      virtual std::string name() = 0;
      virtual void add( ::espena::playbook_item item ) = 0;
      virtual void run() = 0;
      virtual void resume() = 0;
      virtual void reset() = 0;
  }; // class i_playbook
}; // namespace espena

#endif // __i_playbook_hpp__