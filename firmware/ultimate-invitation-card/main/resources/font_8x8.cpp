#include "font_8x8.hpp"

using namespace espena;

int font_8x8::get_width() {
  return 8;
}

int font_8x8::get_height() {
  return 8;
}

const unsigned char *font_8x8::get_buffer() {
  return m_buffer[ 0 ];
}

const unsigned char font_8x8::m_buffer[ 256 ][ 8 ] = {
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0000 (nul)
  { 0x00, 0x04, 0x02, 0xFF, 0x02, 0x04, 0x00, 0x00 },   // U+0001 (Up arrow)
  { 0x00, 0x20, 0x40, 0xFF, 0x40, 0x20, 0x00, 0x00 },   // U+0002 (Down arrow)
  { 0x08, 0x1c, 0x3e, 0x7f, 0x7f, 0x1c, 0x1c, 0x1c },   // U+0003 (Left arrow)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0004
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0005
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0006
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0007
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0008
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0009
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+000A
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+000B
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+000C
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+000D
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+000E
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+000F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0010
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0011
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0012
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0013
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0014
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0015
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0016
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0017
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0018
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0019
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+001A
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+001B
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+001C
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+001D
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+001E
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+001F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0020 (space)
  { 0x00, 0x00, 0x06, 0x5F, 0x5F, 0x06, 0x00, 0x00 },   // U+0021 (!)
  { 0x00, 0x03, 0x03, 0x00, 0x03, 0x03, 0x00, 0x00 },   // U+0022 (")
  { 0x14, 0x7F, 0x7F, 0x14, 0x7F, 0x7F, 0x14, 0x00 },   // U+0023 (#)
  { 0x24, 0x2E, 0x6B, 0x6B, 0x3A, 0x12, 0x00, 0x00 },   // U+0024 ($)
  { 0x46, 0x66, 0x30, 0x18, 0x0C, 0x66, 0x62, 0x00 },   // U+0025 (%)
  { 0x30, 0x7A, 0x4F, 0x5D, 0x37, 0x7A, 0x48, 0x00 },   // U+0026 (&)
  { 0x04, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0027 (')
  { 0x00, 0x1C, 0x3E, 0x63, 0x41, 0x00, 0x00, 0x00 },   // U+0028 (()
  { 0x00, 0x41, 0x63, 0x3E, 0x1C, 0x00, 0x00, 0x00 },   // U+0029 ())
  { 0x08, 0x2A, 0x3E, 0x1C, 0x1C, 0x3E, 0x2A, 0x08 },   // U+002A (*)
  { 0x08, 0x08, 0x3E, 0x3E, 0x08, 0x08, 0x00, 0x00 },   // U+002B (+)
  { 0x00, 0x80, 0xE0, 0x60, 0x00, 0x00, 0x00, 0x00 },   // U+002C (,)
  { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00 },   // U+002D (-)
  { 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00 },   // U+002E (.)
  { 0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00 },   // U+002F (/)
  { 0x3E, 0x7F, 0x71, 0x59, 0x4D, 0x7F, 0x3E, 0x00 },   // U+0030 (0)
  { 0x40, 0x42, 0x7F, 0x7F, 0x40, 0x40, 0x00, 0x00 },   // U+0031 (1)
  { 0x62, 0x73, 0x59, 0x49, 0x6F, 0x66, 0x00, 0x00 },   // U+0032 (2)
  { 0x22, 0x63, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 },   // U+0033 (3)
  { 0x18, 0x1C, 0x16, 0x53, 0x7F, 0x7F, 0x50, 0x00 },   // U+0034 (4)
  { 0x27, 0x67, 0x45, 0x45, 0x7D, 0x39, 0x00, 0x00 },   // U+0035 (5)
  { 0x3C, 0x7E, 0x4B, 0x49, 0x79, 0x30, 0x00, 0x00 },   // U+0036 (6)
  { 0x03, 0x03, 0x71, 0x79, 0x0F, 0x07, 0x00, 0x00 },   // U+0037 (7)
  { 0x36, 0x7F, 0x49, 0x49, 0x7F, 0x36, 0x00, 0x00 },   // U+0038 (8)
  { 0x06, 0x4F, 0x49, 0x69, 0x3F, 0x1E, 0x00, 0x00 },   // U+0039 (9)
  { 0x00, 0x00, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00 },   // U+003A (:)
  { 0x00, 0x80, 0xE6, 0x66, 0x00, 0x00, 0x00, 0x00 },   // U+003B (;)
  { 0x08, 0x1C, 0x36, 0x63, 0x41, 0x00, 0x00, 0x00 },   // U+003C (<)
  { 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x00, 0x00 },   // U+003D (=)
  { 0x00, 0x41, 0x63, 0x36, 0x1C, 0x08, 0x00, 0x00 },   // U+003E (>)
  { 0x02, 0x03, 0x51, 0x59, 0x0F, 0x06, 0x00, 0x00 },   // U+003F (?)
  { 0x3E, 0x7F, 0x41, 0x5D, 0x5D, 0x1F, 0x1E, 0x00 },   // U+0040 (@)
  { 0x7e, 0x7f, 0x09, 0x09, 0x7f, 0x7e, 0x00, 0x00 },   // U+0041 (A)
  { 0x41, 0x7f, 0x7f, 0x49, 0x49, 0x7f, 0x36, 0x00 },   // U+0042 (B)
  { 0x3e, 0x7f, 0x41, 0x41, 0x41, 0x63, 0x22, 0x00 },   // U+0043 (C)
  { 0x41, 0x7f, 0x7f, 0x41, 0x41, 0x7f, 0x3e, 0x00 },   // U+0044 (D)
  { 0x41, 0x7f, 0x7f, 0x49, 0x5d, 0x41, 0x63, 0x00 },   // U+0045 (E)
  { 0x41, 0x7f, 0x7f, 0x49, 0x1d, 0x01, 0x03, 0x00 },   // U+0046 (F)
  { 0x3e, 0x7f, 0x41, 0x41, 0x51, 0x73, 0x72, 0x00 },   // U+0047 (G)
  { 0x7f, 0x7f, 0x08, 0x08, 0x7f, 0x7f, 0x00, 0x00 },   // U+0048 (H)
  { 0x00, 0x00, 0x41, 0x7f, 0x7f, 0x41, 0x00, 0x00 },   // U+0049 (I)
  { 0x30, 0x70, 0x40, 0x41, 0x7f, 0x3f, 0x01, 0x00 },   // U+004A (J)
  { 0x41, 0x7f, 0x7f, 0x49, 0x1c, 0x77, 0x63, 0x00 },   // U+004B (K)
  { 0x41, 0x7f, 0x7f, 0x41, 0x40, 0x40, 0x60, 0x00 },   // U+004C (L)
  { 0x7f, 0x7f, 0x06, 0x0c, 0x06, 0x7f, 0x7f, 0x00 },   // U+004D (M)
  { 0x00, 0x7f, 0x7f, 0x0e, 0x38, 0x7f, 0x7f, 0x00 },   // U+004E (N)
  { 0x3e, 0x7f, 0x41, 0x41, 0x41, 0x7f, 0x3e, 0x00 },   // U+004F (O)
  { 0x41, 0x7f, 0x7f, 0x49, 0x09, 0x0f, 0x06, 0x00 },   // U+0050 (P)
  { 0x3e, 0x7f, 0x41, 0x61, 0xe1, 0xff, 0xbe, 0x00 },   // U+0051 (Q)
  { 0x41, 0x7f, 0x7f, 0x49, 0x19, 0x77, 0x66, 0x00 },   // U+0052 (R)
  { 0x00, 0x26, 0x6f, 0x4d, 0x59, 0x7b, 0x32, 0x00 },   // U+0053 (S)
  { 0x00, 0x03, 0x41, 0x7f, 0x7f, 0x41, 0x03, 0x00 },   // U+0054 (T)
  { 0x00, 0x3f, 0x7f, 0x40, 0x40, 0x7f, 0x3f, 0x00 },   // U+0055 (U)
  { 0x00, 0x1f, 0x3f, 0x60, 0x60, 0x3f, 0x1f, 0x00 },   // U+0056 (V)
  { 0x7f, 0x7f, 0x30, 0x18, 0x30, 0x7f, 0x7f, 0x00 },   // U+0057 (W)
  { 0x00, 0x63, 0x77, 0x1c, 0x1c, 0x77, 0x63, 0x00 },   // U+0058 (X)
  { 0x00, 0x07, 0x4f, 0x78, 0x78, 0x4f, 0x07, 0x00 },   // U+0059 (Y)
  { 0x00, 0x67, 0x73, 0x59, 0x4d, 0x67, 0x73, 0x00 },   // U+005A (Z)
  { 0x00, 0x7F, 0x7F, 0x41, 0x41, 0x00, 0x00, 0x00 },   // U+005B ([)
  { 0x01, 0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x00 },   // U+005C (\)
  { 0x00, 0x41, 0x41, 0x7F, 0x7F, 0x00, 0x00, 0x00 },   // U+005D (])
  { 0x08, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x08, 0x00 },   // U+005E (^)
  { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },   // U+005F (_)
  { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 },   // U+0060 (`) (changed to overline)
  { 0x20, 0x74, 0x54, 0x54, 0x3c, 0x78, 0x40, 0x00 },   // U+0040 (a)
  { 0x41, 0x7f, 0x3f, 0x44, 0x44, 0x7c, 0x38, 0x00 },   // U+0040 (b)
  { 0x38, 0x7c, 0x44, 0x44, 0x6c, 0x28, 0x00, 0x00 },   // U+0040 (c)
  { 0x38, 0x7c, 0x44, 0x45, 0x3f, 0x7f, 0x40, 0x00 },   // U+0040 (d)
  { 0x38, 0x7c, 0x54, 0x54, 0x5c, 0x18, 0x00, 0x00 },   // U+0040 (e)
  { 0x00, 0x48, 0x7e, 0x7f, 0x49, 0x03, 0x02, 0x00 },   // U+0040 (f)
  { 0x18, 0xbc, 0xa4, 0xa4, 0xf8, 0x7c, 0x04, 0x00 },   // U+0040 (g)
  { 0x41, 0x7f, 0x7f, 0x44, 0x04, 0x7c, 0x78, 0x00 },   // U+0040 (h)
  { 0x00, 0x00, 0x44, 0x7d, 0x7d, 0x40, 0x00, 0x00 },   // U+0040 (i)
  { 0x00, 0x60, 0xe0, 0x80, 0x84, 0xfd, 0x7d, 0x00 },   // U+0040 (j)
  { 0x41, 0x7f, 0x7f, 0x48, 0x1c, 0x76, 0x62, 0x00 },   // U+0040 (k)
  { 0x00, 0x41, 0x7f, 0x7f, 0x40, 0x00, 0x00, 0x00 },   // U+0040 (l)
  { 0x7c, 0x7c, 0x18, 0x30, 0x18, 0x7c, 0x7c, 0x00 },   // U+0040 (m)
  { 0x04, 0x7c, 0x78, 0x04, 0x04, 0x7c, 0x78, 0x00 },   // U+0040 (n)
  { 0x00, 0x38, 0x7c, 0x44, 0x44, 0x7c, 0x38, 0x00 },   // U+0040 (o)
  { 0x84, 0xfc, 0xf8, 0xa4, 0x24, 0x3c, 0x18, 0x00 },   // U+0040 (p)
  { 0x18, 0x3c, 0x24, 0xa4, 0xf8, 0xfc, 0x84, 0x00 },   // U+0040 (q)
  { 0x44, 0x7c, 0x78, 0x4c, 0x04, 0x0c, 0x08, 0x00 },   // U+0040 (r)
  { 0x48, 0x5c, 0x5c, 0x54, 0x74, 0x74, 0x20, 0x00 },   // U+0040 (s)
  { 0x04, 0x3e, 0x7f, 0x44, 0x44, 0x20, 0x00, 0x00 },   // U+0040 (t)
  { 0x3c, 0x7c, 0x40, 0x40, 0x3c, 0x7c, 0x40, 0x00 },   // U+0040 (u)
  { 0x00, 0x1c, 0x3c, 0x60, 0x60, 0x3c, 0x1c, 0x00 },   // U+0040 (v)
  { 0x7c, 0x7c, 0x30, 0x18, 0x30, 0x7c, 0x7c, 0x00 },   // U+0040 (w)
  { 0x00, 0x44, 0x6c, 0x38, 0x38, 0x6c, 0x44, 0x00 },   // U+0040 (x)
  { 0x00, 0x1c, 0xbc, 0xa0, 0xa0, 0xfc, 0x7c, 0x00 },   // U+0040 (y)
  { 0x00, 0x4c, 0x64, 0x74, 0x5c, 0x4c, 0x64, 0x00 },   // U+0040 (z)
  { 0x08, 0x08, 0x3E, 0x77, 0x41, 0x41, 0x00, 0x00 },   // U+007B ({)
  { 0x00, 0x00, 0x00, 0x77, 0x77, 0x00, 0x00, 0x00 },   // U+007C (|)
  { 0x41, 0x41, 0x77, 0x3E, 0x08, 0x08, 0x00, 0x00 },   // U+007D (})
  { 0x02, 0x03, 0x01, 0x03, 0x02, 0x03, 0x01, 0x00 },   // U+007E (~)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+007F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0080
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0081
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0082
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0083
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0084
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0085
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0086
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0087
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0088
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0089
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+008A
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+008B
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+008C
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+008D
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+008E
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+008F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0090
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0091
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0092
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0093
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0094
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0095
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0096
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0097
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0098
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+0099
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+009A
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+009B
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+009C
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+009D
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+009E
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+009F
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A0
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A1
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A2
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A3
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A4
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A5
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A6
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A7
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A8
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00A9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00AA
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00AB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00AC
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00AD
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00AE
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00AF
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B0
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B1
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B2
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B3
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B4
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B5
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B6
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B7
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B8
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00B9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00BA
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00BB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00BC
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00BD
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00BE
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00BF
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C0
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C1
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C2
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C3
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C4
  { 0x00, 0x7c, 0x7f, 0x15, 0x15, 0x7f, 0x7c, 0x00 },   // U+00C5 (Å)
  { 0x7e, 0x7f, 0x09, 0x7f, 0x7f, 0x49, 0x41, 0x00 },   // U+00C6 (Æ)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C7
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C8
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00C9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00CA
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00CB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00CC
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00CD
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00CE
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00CF
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D0
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D1
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D2
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D3
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D4
  { 0x78, 0x7E, 0x25, 0x25, 0x7E, 0x78, 0x00, 0x00 },   // U+00D5
  { 0x7e, 0x7f, 0x09, 0x7f, 0x7f, 0x49, 0x41, 0x00 },   // U+00D6
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D7
  { 0x5e, 0x3f, 0x51, 0x49, 0x45, 0x7e, 0x3d, 0x00 },   // U+00D8 (Ø)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00D9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00DA
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00DB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00DC
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00DD
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00DE
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00DF
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E0
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E1
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E2
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E3
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E4
  { 0x20, 0x54, 0x55, 0x55, 0x3c, 0x78, 0x40, 0x00 },   // U+00E5 (å)
  { 0x20, 0x74, 0x54, 0x78, 0x7c, 0x54, 0x58, 0x00 },   // U+00E6 (æ)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E7
  { 0x7e, 0x7f, 0x51, 0x49, 0x45, 0x1f, 0x1f, 0x00 },   // U+00E8
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00E9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00EA
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00EB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00EC
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00ED
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00EE
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00EF
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F0
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F1
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F2
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F3
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F4
  { 0x78, 0x7E, 0x25, 0x25, 0x7E, 0x78, 0x00, 0x00 },   // U+00F5
  { 0x7e, 0x7f, 0x09, 0x7f, 0x7f, 0x49, 0x41, 0x00 },   // U+00F6
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F7
  { 0x00, 0xb8, 0x7c, 0x74, 0x5c, 0x7c, 0x3a, 0x00 },   // U+00F8 (ø)
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00F9
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00FA
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00FB
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00FC
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00FD
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },   // U+00FE
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }    // U+00FF
};