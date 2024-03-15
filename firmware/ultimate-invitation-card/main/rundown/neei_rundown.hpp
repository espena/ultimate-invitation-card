#ifndef __NEEI_RUNDOWN_HPP__
#define __NEEI_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"
#include "../resources/neei.h"

namespace espena {
  class neei_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class neei_rundown
}; // namespace espena

#endif // __NEEI_RUNDOWN_HPP__
