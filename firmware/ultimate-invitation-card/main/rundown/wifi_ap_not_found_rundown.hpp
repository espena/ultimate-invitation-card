#ifndef __WIFI_AP_NOT_FOUND_RUNDOWN_HPP__
#define __WIFI_AP_NOT_FOUND_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class wifi_ap_not_found_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class wifi_login_failure_rundown
}; // namespace espena

#endif // __WIFI_AP_NOT_FOUND_RUNDWN_HPP__