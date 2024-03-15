#ifndef __TRANSPORT_RUNDOWN_HPP__
#define __TRANSPORT_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class transport_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class transport_rundown
}; // namespace espena

#endif // __TRANSPORT_RUNDOWN_HPP__