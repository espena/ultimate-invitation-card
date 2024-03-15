#ifndef __SAD_ROLLER_RUNDOWN_HPP__
#define __SAD_ROLLER_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"
#include "../resources/neei.h"

namespace espena {
  class sad_roller_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class sad_roller_rundown
}; // namespace espena

#endif // __SAD_ROLLER_RUNDOWN_HPP__
