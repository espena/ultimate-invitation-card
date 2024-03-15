#include <memory.h>
#include "qrcode_rundown.hpp"
#include "../components/i_playbook.hpp"

#include "../resources/iso8859-1_text.h"
#include "../resources/dotmatrix_img.h"

using namespace espena;

void qrcode_rundown::load( ::espena::i_playbook *pb ) {

  ::espena::playbook_item pi;
  
  // QR advice
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::text;
  pi.buf = iso8859_1_text[ iso8859_1_text_id::txt_qrcode_advice ][ 0 ];
  pi.params.delay_ms = 4000;
  pb->add( pi );

  // Venue QR code
  memset( &pi, 0x00, sizeof( pi ) );
  pi.type = ::espena::playbook_item_type::image;
  pi.buf = dotmatrix_img[ img_02_venue_qrcode ];
  pi.params.event[ ::espena::menu_key::A ] = ::espena::menu_select::venue;
  pb->add( pi );

}