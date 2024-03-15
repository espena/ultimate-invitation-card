#include <memory.h>
#include "transport_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void transport_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Transport menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::transport_to;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::transport_from;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::sleepover;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::info_more;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_transport1 ][ 0 ];
  pb->add( pi );

}