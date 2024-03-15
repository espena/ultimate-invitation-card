#include <memory.h>
#include "intro_rundown.hpp"
#include "../components/i_playbook.hpp"
#include "../components/playbook.hpp"

#include "../resources/iso8859-1_roll.h"
#include "../resources/iso8859-1_text.h"

#include "../resources/dotmatrix_img.h"
#include "../resources/power_on_intro.h"

using namespace espena;

void intro_rundown::load( ::espena::i_playbook *pb ) {

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

  // Greeting
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_p13n_greeting ][ 0 ];
  pi.params.delay_ms = 4000;
  pb->add( pi );

  // Invitation text
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_invitation ][ 0 ];
  pi.params.delay_ms = 4000;
  pb->add( pi );

  // Introductionary text roller
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::roll;
  pi.buf = main_intro_roll[ 0 ];
  pi.params.line_count = sizeof( main_intro_roll ) / sizeof( main_intro_roll[ 0 ] );
  pi.params.delay_ms = 60000;
  pb->add( pi );

  // Support number
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_support ][ 0 ];
  pi.params.delay_ms = 5000;
  pb->add( pi );

}