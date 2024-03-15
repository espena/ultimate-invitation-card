#ifndef __BRING_RUNDOWN_HPP__
#define __BRING_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class bring_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class bring_rundown
}; // namespace espena

#endif // __BRING_RUNDOWN_HPP__