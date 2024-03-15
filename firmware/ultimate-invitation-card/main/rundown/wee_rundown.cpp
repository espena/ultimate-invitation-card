#include <memory.h>
#include "wee_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/iso8859-1_roll.h"
#include "../resources/wee.h"

using namespace espena;

void wee_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) wee;
  pi.params.tween.frame_begin = wee_begin;
  pi.params.tween.frame_end = wee_end;
  pi.params.tween.delay_ms = 5;
  pi.params.delay_ms = 5000;
  pi.params.que_points[ 0 ].wire = cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::await;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_sending ][ 0 ];
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_sending ][ 0 ];
  pi.params.delay_ms = 2000;
  pb->add( pi );

}