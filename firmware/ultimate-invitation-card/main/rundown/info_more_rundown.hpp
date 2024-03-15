#ifndef __INFO_MORE_RUNDOWN_HPP__
#define __INFO_MORE_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class info_more_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class info_more_rundown
}; // namespace espena

#endif // __INFO_MORE_RUNDOWN_HPP__