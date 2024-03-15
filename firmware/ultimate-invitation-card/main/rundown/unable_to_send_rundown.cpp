#include <memory.h>
#include "unable_to_send_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"
#include "../resources/wee.h"

using namespace espena;

void unable_to_send_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_send_err ][ 0 ];
  pi.params.delay_ms = 7000;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_send_retry ][ 0 ];
  pi.params.delay_ms = 7000;
  pb->add( pi );

  // Main menu (response not sent)
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::info;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::change_response;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::send_response;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::shutdown;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::mnu_main_not_sent ][ 0 ];
  pb->add( pi );

}