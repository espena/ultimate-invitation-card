#ifndef __i_display_hpp__
#define __i_display_hpp__

#include <cstdint>
#include "playbook_item.hpp"
#include "i_font.hpp"

namespace espena {
  class i_display {
    public:
      virtual void write_text( const uint8_t *buf ) = 0;
      virtual void roll_text( const uint8_t *buf, unsigned int line_count, que_point que_points[ 4 ] ) = 0;
      virtual void draw_image( const uint8_t *buf ) = 0;
      virtual void overlay( const uint8_t *buf ) = 0;
      virtual void transition( const uint8_t *buf, int frame_begin, int frame_end, int delay_ms ) = 0;
      virtual void delay( unsigned int ms ) = 0;
      virtual void clear( bool invert ) = 0;
  }; // class i_display
}; // namespace espena

#endif // __i_display_hpp__