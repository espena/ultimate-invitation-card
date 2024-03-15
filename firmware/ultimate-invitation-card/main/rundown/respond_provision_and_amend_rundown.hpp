#ifndef __RESPOND_PROVISION_AND_AMEND_RUNDOWN_HPP__
#define __RESPOND_PROVISION_AND_AMEND_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class respond_provision_and_amend_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class respond_provision_and_amend_rundown
}; // namespace espena

#endif // __RESPOND_PROVISION_AND_AMEND_RUNDOWN_HPP__