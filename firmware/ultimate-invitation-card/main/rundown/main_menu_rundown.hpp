#ifndef __MAIN_MENU_RUNDOWN_HPP__
#define __MAIN_MENU_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class main_menu_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class main_menu_rundown
}; // namespace espena

#endif // __MAIN_MENU_RUNDOWN_HPP__