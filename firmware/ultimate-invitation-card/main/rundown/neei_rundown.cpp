#include <memory.h>
#include "neei_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"
#include "../resources/wee.h"

using namespace espena;

void neei_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  // Thunderstorm
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) neei;
  pi.params.tween.frame_begin = thunder_begin;
  pi.params.tween.frame_end = thunder_end;
  pi.params.tween.delay_ms = 5;
  pi.params.delay_ms = 0;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red;
  pb->add( pi );

  // Noooo!
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = neei[ neei_txt ];
  pi.params.delay_ms = 3000;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red;
  pb->add( pi );
 
  // Sending to server
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_sending ][ 0 ];
  pi.params.delay_ms = 2000;
  pb->add( pi );

  // Sending to server (waiting)
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::await;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_sending ][ 0 ];
  pb->add( pi );

}