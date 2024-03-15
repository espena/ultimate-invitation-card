#include <memory.h>
#include "wifi_provisioning_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void wifi_provisioning_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::await;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wifi3 ][ 0 ];
  pb->add( pi );
  
  // Wifi 4
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wifi4 ][ 0 ];
  pi.params.delay_ms = 2000;
  pb->add( pi );

  // Wifi 6
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::await;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wifi6 ][ 0 ];
  pb->add( pi );

  // Wifi 7
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wifi7 ][ 0 ];
  pi.params.delay_ms = 10000;
  pb->add( pi );

  // Wifi 8
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::main;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wifi8 ][ 0 ];
  pb->add( pi );

}