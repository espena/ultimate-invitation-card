#ifndef __UNABLE_TO_SEND_RUNDOWN_HPP__
#define __UNABLE_TO_SEND_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"
#include "../resources/neei.h"

namespace espena {
  class unable_to_send_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class unable_to_send_rundown
}; // namespace espena

#endif // __UNABLE_TO_SEND_RUNDOWN_HPP__
