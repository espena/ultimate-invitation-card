#include <memory.h>
#include "respond_with_wifi_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"
#include "../resources/respond_intro.h"
#include "../resources/matrix.h"

using namespace espena;

void respond_with_wifi_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  // The Matrix
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) the_matrix;
  pi.params.tween.frame_begin = the_matrix_out;
  pi.params.tween.frame_end = the_matrix_out_end;
  pi.params.tween.delay_ms = 100;
  pi.params.delay_ms = 4000;
  pb->add( pi );

  // roller text with matrix monologue
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::roll;
  pi.buf = matrix_roll[ 0 ];
  pi.params.line_count = sizeof( matrix_roll ) / sizeof( matrix_roll[ 0 ] );
  pi.params.delay_ms = 39000;
  pb->add( pi );
  
  // ja
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ respond_intro_004 ];
  pi.params.delay_ms = 4000;
  pi.params.que_points[ 0 ].wire = cuttable_wire::green;
  pb->add( pi );

  // nei
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = respond_intro[ respond_intro_003 ];
  pi.params.delay_ms = 4000;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red;
  pb->add( pi );
 
  // Ready..? (menu)
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::countdown;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::main;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_wirecut5 ][ 0 ];
  pb->add( pi );

}