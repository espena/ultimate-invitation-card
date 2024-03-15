#ifndef __MNU_CHANGE_RESPONSE_RUNDOWN_HPP__
#define __MNU_CHANGE_RESPONSE_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class mnu_change_response_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class mnu_change_response_rundown
}; // namespace espena

#endif // __MNU_CHANGE_RESPONSE_RUNDOWN_HPP__