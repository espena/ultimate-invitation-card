#ifndef __WIFI_RUNDOWN_HPP__
#define __WIFI_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class wifi_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class wifi_rundown
}; // namespace espena

#endif // __WIFI_RUNDOWN_HPP__