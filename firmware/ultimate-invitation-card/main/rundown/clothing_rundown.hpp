#ifndef __CLOTHING_RUNDOWN_HPP__
#define __CLOTHING_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class clothing_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class clothing_rundown
}; // namespace espena

#endif // __CLOTHING_RUNDOWN_HPP__