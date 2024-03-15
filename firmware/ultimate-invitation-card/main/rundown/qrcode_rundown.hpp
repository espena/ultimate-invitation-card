#ifndef __QRCODE_RUNDOWN_HPP__
#define __QRCODE_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class qrcode_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class qrcode_rundown
}; // namespace espena

#endif // __QRCODE_RUNDOWN_HPP__