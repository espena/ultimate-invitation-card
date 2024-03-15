#include <memory.h>
#include "intro_not_coming_rundown.hpp"
#include "../components/i_playbook.hpp"
#include "../components/playbook.hpp"

#include "../resources/iso8859-1_roll.h"
#include "../resources/iso8859-1_text.h"
#include "../resources/dotmatrix_img.h"
#include "../resources/power_on_intro.h"
#include "../resources/neei.h"

using namespace espena;

void intro_not_coming_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Animation show text: Espen
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) power_on_intro;
  pi.params.tween.frame_begin = power_on_intro_step01;
  pi.params.tween.frame_end = power_on_intro_step02;
  pi.params.tween.delay_ms = 5;
  pi.params.delay_ms = 1000;
  pb->add( pi );

  // Text: Turns
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) power_on_intro;
  pi.params.tween.frame_begin = power_on_intro_step02;
  pi.params.tween.frame_end = power_on_intro_step03;
  pi.params.delay_ms = 700;
  pb->add( pi );

  // Text: 50
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) power_on_intro;
  pi.params.tween.frame_begin = power_on_intro_step03;
  pi.params.tween.frame_end = power_on_intro_step04;
  pi.params.tween.delay_ms = 10;
  pi.params.delay_ms = 1000;
  pb->add( pi );

  // Dissolve to Espen's face
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) power_on_intro;
  pi.params.tween.frame_begin = power_on_intro_step04;
  pi.params.tween.frame_end = power_on_intro_step05;
  pi.params.tween.delay_ms = 1;
  pb->add( pi );

  // Espen's face
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = dotmatrix_img[ img_01_espena_face ];
  pi.params.delay_ms = 3000;
  pb->add( pi );

  // Fade out
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) power_on_intro;
  pi.params.tween.frame_begin = power_on_intro_step05;
  pi.params.tween.frame_end = power_on_intro_end;
  pi.params.tween.delay_ms = 10;
  pb->add( pi );

  // Neei!
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) neei;
  pi.params.tween.frame_begin = thunder_begin;
  pi.params.tween.frame_end = thunder_end;
  pi.params.tween.delay_ms = 5;
  pi.params.delay_ms = 2000;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red;
  pb->add( pi );

  // Sad message
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_reject_start ][ 0 ];
  pi.params.que_points[ 0 ].wire = cuttable_wire::red;
  pi.params.delay_ms = 4000;
  pb->add( pi );

  // Want to alter reponse?
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invit_alter_resp ][ 0 ];
  pi.params.que_points[ 0 ].wire = cuttable_wire::red;
  pi.params.delay_ms = 6000;
  pb->add( pi );

  // Main menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::menu;
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::info;
  pi.params.event[ ::espena::menu_key::B ] = ::espena::menu_select::change_response;
  pi.params.event[ ::espena::menu_key::C ] = ::espena::menu_select::website_url;
  pi.params.event[ ::espena::menu_key::D ] = ::espena::menu_select::shutdown;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::mnu_main_responded ][ 0 ];
  pb->add( pi );

}