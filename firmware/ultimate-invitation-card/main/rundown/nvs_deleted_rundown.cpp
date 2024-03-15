#include <memory.h>
#include "nvs_deleted_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"

using namespace espena;

void nvs_deleted_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // Info more menu
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_nvs_deleted ][ 0 ];
  pi.params.delay_ms = 7000;
  pb->add( pi );

}