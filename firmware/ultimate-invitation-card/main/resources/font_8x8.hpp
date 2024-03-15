#ifndef __font_8x8_hpp__
#define __font_8x8_hpp__

#include "i_font.hpp"

namespace espena {

  class font_8x8 : public i_font {

    static const unsigned char m_buffer[ 256 ][ 8 ];

    public:

      virtual int get_width();
      virtual int get_height();
      const unsigned char *get_buffer();

  }; // class font_8x8

}; // namespace espena

#endif // __font_8x8_hpp__
