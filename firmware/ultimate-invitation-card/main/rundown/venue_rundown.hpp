#ifndef __VENUE_RUNDOWN_HPP__
#define __VENUE_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class venue_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class venue_rundown
}; // namespace espena

#endif // __VENUE_RUNDOWN_HPP__