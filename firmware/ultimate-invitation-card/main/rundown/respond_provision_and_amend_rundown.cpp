#include <memory.h>
#include "respond_provision_and_amend_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/respond_intro.h"
#include "../resources/iso8859-1_text.h"

using namespace espena;

void respond_provision_and_amend_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // finn frem en avbitertang!
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_pliers ][ 0 ];
  pi.params.delay_ms = 4000;
  pb->add( pi );

  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // nei
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang inv.
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers_inv ];
  pi.params.delay_ms = 55;
  pb->add( pi );
 
  // avbitertang
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ pliers ];
  pi.params.delay_ms = 2000;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_respond1 ][ 0 ];
  pi.params.delay_ms = 6000;
  pb->add( pi );

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