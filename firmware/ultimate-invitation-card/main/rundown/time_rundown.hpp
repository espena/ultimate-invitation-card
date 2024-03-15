#ifndef __TIME_RUNDOWN_HPP__
#define __TIME_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class time_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class time
}; // namespace espena

#endif // __TIME_RUNDOWN_HPP__