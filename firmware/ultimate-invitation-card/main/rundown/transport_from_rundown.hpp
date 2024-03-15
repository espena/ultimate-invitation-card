#ifndef __TRANSPORT_FROM_RUNDOWN_HPP__
#define __TRANSPORT_FROM_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class transport_from_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class transport_from_rundown
}; // namespace espena

#endif // __TRANSPORT_FROM_RUNDOWN_HPP__