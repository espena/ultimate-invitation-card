#include <memory.h>
#include "info_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void info_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Info menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::time;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::venue;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::info_more;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::main;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::mnu_info ][ 0 ];
  pb->add( pi );

}