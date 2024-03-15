#include <memory.h>
#include "bring_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void bring_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Bring 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_bring1 ][ 0 ];
  pi.params.delay_ms = 5000;
  pb->add( pi );

  // Bring 2
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_bring2 ][ 0 ];
  pi.params.delay_ms = 5000;
  pb->add( pi );

  // Bring 2
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::info_more;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_bring3 ][ 0 ];
  pb->add( pi );

}