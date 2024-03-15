#ifndef __WIFI_PROVISIONING_RUNDOWN_HPP__
#define __WIFI_PROVISIONING_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class wifi_provisioning_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class wifi_provisioning_rundown
}; // namespace espena

#endif // __WIFI_PROVISIONING_HPP__