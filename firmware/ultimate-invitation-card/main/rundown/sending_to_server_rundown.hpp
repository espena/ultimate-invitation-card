#ifndef __SENDING_TO_SERVER_RUNDOWN_HPP__
#define __SENDING_TO_SERVER_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class sending_to_server_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class sending_to_server
}; // namespace espena

#endif // __SENDING_TO_SERVER_RUNDOWN_HPP__