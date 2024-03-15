#include <memory.h>
#include "time_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"

using namespace espena;

void time_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Time text
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_time ][ 0 ];
  pi.params.delay_ms = 5000;
  pb->add( pi );

  // Time roller
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::roll;
  pi.buf = time_roll[ 0 ];
  pi.params.line_count = sizeof( time_roll ) / sizeof( time_roll[ 0 ] );
  pi.params.delay_ms = 11000;
  pb->add( pi );

  // Time menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::info;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::mnu_time ][ 0 ];
  pb->add( pi );

}