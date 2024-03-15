#include <memory.h>
#include "happy_roller_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"

using namespace espena;

void happy_roller_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_acc_start ][ 0 ];
  pi.params.delay_ms = 4000;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::roll;
  pi.buf = invitation_accepted_roll[ 0 ];
  pi.params.line_count = sizeof( invitation_accepted_roll ) / sizeof( invitation_accepted_roll[ 0 ] );
  pi.params.delay_ms = 12000;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::main;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_acc_menu ][ 0 ];
  pb->add( pi );

}