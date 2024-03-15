#ifndef __i_font_hpp__
#define __i_font_hpp__

namespace espena {
  class i_font {
    public:
      virtual int get_width() = 0;
      virtual int get_height() = 0;
      virtual const unsigned char *get_buffer() = 0;
  }; // class i_font
}; // namespace espena

#endif // __i_font_hpp__