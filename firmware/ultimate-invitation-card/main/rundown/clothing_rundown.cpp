#include <memory.h>
#include "clothing_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void clothing_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 300;
  pb->add( pi );

  // Clothing 4
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing4 ][ 0 ];
  pi.params.delay_ms = 75;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 1000;
  pb->add( pi );

  // Clothing 2
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing2 ][ 0 ];
  pi.params.delay_ms = 25;
  pb->add( pi );

  // Clothing 4
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing4 ][ 0 ];
  pi.params.delay_ms = 200;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 500;
  pb->add( pi );

  // Clothing 3
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing3 ][ 0 ];
  pi.params.delay_ms = 25;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 1500;
  pb->add( pi );

  // Clothing 4
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing4 ][ 0 ];
  pi.params.delay_ms = 150;
  pb->add( pi );

  // Clothing 2
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing2 ][ 0 ];
  pi.params.delay_ms = 50;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 1500;
  pb->add( pi );

  // Clothing 3
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing3 ][ 0 ];
  pi.params.delay_ms = 25;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 200;
  pb->add( pi );

  // Clothing 3
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing3 ][ 0 ];
  pi.params.delay_ms = 25;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 500;
  pb->add( pi );

  // Clothing 4
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing4 ][ 0 ];
  pi.params.delay_ms = 750;
  pb->add( pi );

  // Clothing 3
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 25;
  pb->add( pi );

  // Clothing 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing1 ][ 0 ];
  pi.params.delay_ms = 250;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::info_more;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_clothing5 ][ 0 ];
  pb->add( pi );

}