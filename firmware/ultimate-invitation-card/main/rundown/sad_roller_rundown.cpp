#include <memory.h>
#include "sad_roller_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"

using namespace espena;

void sad_roller_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  // Sooooo sorry...
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_reject_start ][ 0 ];
  pi.params.delay_ms = 1000;
  pb->add( pi );

  // Sooooo sorry -> rolling
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::roll;
  pi.buf = invitation_rejected_roll[ 0 ];
  pi.params.line_count = sizeof( invitation_rejected_roll ) / sizeof( invitation_rejected_roll[ 0 ] );
  pi.params.delay_ms = 29500;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::main;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_reject_menu ][ 0 ];
  pb->add( pi );

}