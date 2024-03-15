#ifndef __I_RUNDOWN_HPP__
#define __I_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"

namespace espena {
  class i_rundown {
    public:
      virtual void load( i_playbook pb ) = 0;
  }; // class i_rundown
}; // namespace espena

#endif // __I_RUNDOWN_HPP__