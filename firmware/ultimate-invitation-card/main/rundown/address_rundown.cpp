#include <memory.h>
#include "address_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/venue_video.h"
#include "../resources/iso8859-1_text.h"

using namespace espena;

void address_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Venue video
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) venue_video;
  pi.params.tween.frame_begin = venue_video_begin;
  pi.params.tween.frame_end = venue_video_end;
  pi.params.tween.delay_ms = 10;
  pi.params.delay_ms = 4500;
  pb->add( pi );

  // Info menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::none;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::venue;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_address ][ 0 ];
  pb->add( pi );

}