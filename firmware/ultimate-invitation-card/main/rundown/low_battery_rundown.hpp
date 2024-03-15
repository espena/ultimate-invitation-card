#ifndef __LOW_BATTERY_RUNDOWN_HPP__
#define __LOW_BATTERY_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class low_battery_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class low_battery_rundown
}; // namespace espena

#endif // __LOW_BATTERY_RUNDOWN_HPP__