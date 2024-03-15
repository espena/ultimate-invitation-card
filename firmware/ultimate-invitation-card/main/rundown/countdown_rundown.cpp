#include <memory.h>
#include "countdown_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/countdown.h"

using namespace espena;

void countdown_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;

  // 10
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_10 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 9
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_9 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 8
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_8 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 7
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_7 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 6
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_6 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 5
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_5 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 4
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_4 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 3
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_3 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 2
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_2 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 1
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_1 ];
  pi.params.delay_ms = 750;
  pi.params.beep = 1;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_arr ];
  pi.params.delay_ms = 250;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // 0
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = countdown[ countdown_0 ];
  pi.params.delay_ms = 4000;
  pi.params.que_points[ 0 ].wire = cuttable_wire::red | cuttable_wire::green;
  pb->add( pi );
 
  // The Matrix
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::transition;
  pi.buf = ( const uint8_t* ) the_matrix;
  pi.params.tween.frame_begin = the_matrix_out;
  pi.params.tween.frame_end = the_matrix_out_end;
  pi.params.tween.delay_ms = 100;
  pi.params.delay_ms = 5000;
  pi.params.beep = 3;
  pb->add( pi );

  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = the_matrix[ the_matrix_start ];
  pi.params.delay_ms = 1000;
  pb->add( pi );

}