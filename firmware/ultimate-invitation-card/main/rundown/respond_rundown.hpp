#ifndef __RESPOND_RUNDOWN_HPP__
#define __RESPOND_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class respond_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class respond_rundown
}; // namespace espena

#endif // __RESPOND_RUNDOWN_HPP__