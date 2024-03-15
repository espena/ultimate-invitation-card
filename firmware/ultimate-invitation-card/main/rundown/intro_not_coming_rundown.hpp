#ifndef __INTRO_NOT_COMING_RUNDOWN_HPP__
#define __INTRO_NOT_COMING_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class intro_not_coming_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class intro_not_coming_rundown
}; // namespace espena

#endif // __INTRO_NOT_COMING_RUNDOWN_HPP__