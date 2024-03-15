#include <memory.h>
#include "transport_to_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"

using namespace espena;

void transport_to_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Transport TO start text
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_transport_to_start ][ 0 ];
  pi.params.delay_ms = 5000;
  pb->add( pi );

  // Transport TO roller
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::roll;
  pi.buf = transport_to_roll[ 0 ];
  pi.params.line_count = sizeof( transport_to_roll ) / sizeof( transport_to_roll[ 0 ] );
  pi.params.delay_ms = 40000;
  pb->add( pi );

  // Transport TO end / menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::transport_to;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::transport;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_transport_to_menu ][ 0 ];
  pb->add( pi );

}