#ifndef __WEE_RUNDOWN_HPP__
#define __WEE_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"
#include "../resources/wee.h"

namespace espena {
  class wee_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class wee_rundown
}; // namespace espena

#endif // __WEE_RUNDOWN_HPP__
