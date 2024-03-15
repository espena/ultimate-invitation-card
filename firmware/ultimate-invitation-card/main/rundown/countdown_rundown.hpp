#ifndef __COUNTDOWN_RUNDOWN_HPP__
#define __COUNTDOWN_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"
#include "../resources/matrix.h"

namespace espena {
  class countdown_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class countdown_rundown
}; // namespace espena

#endif // __COUNTDOWN_RUNDOWN_HPP__