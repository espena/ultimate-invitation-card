#ifndef __ADDRESS_RUNDOWN_HPP__
#define __ADDRESS_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class address_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class address_rundown
}; // namespace espena

#endif // __ADDRESS_RUNDOWN_HPP__