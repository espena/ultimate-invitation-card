#ifndef __WEBSITE_URL_RUNDOWN_HPP__
#define __WEBSITE_URL_RUNDOWN_HPP__

#include "../components/i_playbook.hpp"
#include "i_rundown.hpp"

namespace espena {
  class website_url_rundown : public i_rundown {
    public:
      static void load( espena::i_playbook *pb );
  }; // class website_url_rundown
}; // namespace espena

#endif // __WEBSITE_URL_RUNDOWN_HPP__