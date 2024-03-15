#include <memory.h>
#include "wifi_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void wifi_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Wifi 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::wifi_provisioning;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::none;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wifi1 ][ 0 ];
  pb->add( pi );

}