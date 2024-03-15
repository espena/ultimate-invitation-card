#ifndef __INFO_NVS_DELETED_HPP__
#define __INFO_NVS_DELETED_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class nvs_deleted_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class nvs_deleted_rundown
}; // namespace espena

#endif // __NVS_DELETED_HPP__