#include <memory.h>
#include "respond_with_wifi_intro_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/respond_intro.h"
#include "../resources/iso8859-1_text.h"

using namespace espena;

void respond_with_wifi_intro_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  // Svar
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ respond_intro_001 ];
  pi.params.delay_ms = 500;
  pb->add( pi );
 
  // utbes
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ respond_intro_002 ];
  pi.params.delay_ms = 1500;
  pb->add( pi );

  // klar til å svare?
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::ready_to_respond;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::main;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_ready_or_not ][ 0 ];
  pb->add( pi );

}