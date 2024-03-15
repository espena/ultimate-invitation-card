#ifndef __HAPPY_ROLLER_RUNDOWN_HPP__
#define __HAPPY_ROLLER_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"
#include "../resources/wee.h"

namespace espena {
  class happy_roller_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class happy_roller_rundown
}; // namespace espena

#endif // __HAPPY_ROLLER_RUNDOWN_HPP__
