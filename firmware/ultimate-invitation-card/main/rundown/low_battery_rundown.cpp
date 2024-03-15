#include <memory.h>
#include "low_battery_rundown.hpp"
#include "../components/i_playbook.hpp"
#include "../components/playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void low_battery_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
 // Battery low warning
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_low_battery ][ 0 ];
  pi.params.delay_ms = 7000;
  pb->add( pi );
  
}