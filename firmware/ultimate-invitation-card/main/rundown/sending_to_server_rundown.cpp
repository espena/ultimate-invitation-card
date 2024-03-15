#include <memory.h>
#include "sending_to_server_rundown.hpp"
#include "../components/i_playbook.hpp"
#include "../components/playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void sending_to_server_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
 // Sending to server message
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_sending_to_server ][ 0 ];
  pi.params.delay_ms = 500;
  pb->add( pi );
  
}