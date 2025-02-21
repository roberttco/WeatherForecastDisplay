// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Dialog_plain_16Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xFF,0x30, // '!'
	0x99,0x99, // '"'
	0x0C,0x81,0x10,0x26,0x3F,0xF1,0x90,0x22,0x04,0xC7,0xFE,0x32,0x04,0x40,0x98,0x00, // '#'
	0x10,0x21,0xF6,0x99,0x12,0x1C,0x0E,0x12,0x26,0x5B,0xE1,0x02,0x00, // '$'
	0x70,0x44,0x42,0x22,0x21,0x13,0x08,0x90,0x39,0x00,0x09,0xC0,0x91,0x0C,0x88,0x44,0x44,0x22,0x20,0xE0, // '%'
	0x3C,0x0C,0x41,0x00,0x20,0x02,0x00,0xA0,0x22,0x14,0x22,0x82,0x50,0x31,0x06,0x1F,0x20, // '&'
	0xF0, // '''
	0x36,0x44,0x88,0x88,0x88,0x44,0x63, // '('
	0xC6,0x22,0x11,0x11,0x11,0x22,0x6C, // ')'
	0x10,0x22,0x4B,0xE3,0x9A,0xC4,0x08, // '*'
	0x08,0x04,0x02,0x01,0x0F,0xF8,0x40,0x20,0x10,0x08,0x00, // '+'
	0x56, // ','
	0xF0, // '-'
	0xC0, // '.'
	0x08,0x44,0x21,0x10,0x84,0x42,0x11,0x88,0x00, // '/'
	0x3C,0x42,0x42,0x81,0x81,0x81,0x81,0x81,0x81,0x42,0x42,0x3C, // '0'
	0x71,0xA0,0x40,0x81,0x02,0x04,0x08,0x10,0x20,0x47,0xF0, // '1'
	0x79,0x8A,0x08,0x10,0x20,0x82,0x08,0x20,0x82,0x07,0xF0, // '2'
	0x7C,0x83,0x01,0x01,0x03,0x3C,0x03,0x01,0x01,0x01,0x82,0x7C, // '3'
	0x06,0x05,0x02,0x82,0x42,0x22,0x11,0x09,0x04,0xFF,0x81,0x00,0x80,0x40, // '4'
	0x7E,0x40,0x40,0x40,0x7C,0x42,0x01,0x01,0x01,0x01,0x82,0x7C, // '5'
	0x1C,0x62,0x40,0x80,0xBC,0xC2,0x81,0x81,0x81,0x81,0x42,0x3C, // '6'
	0xFF,0x01,0x02,0x02,0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x20, // '7'
	0x3C,0xC3,0x81,0x81,0xC3,0x3C,0xC3,0x81,0x81,0x81,0x42,0x3C, // '8'
	0x3C,0x42,0x82,0x81,0x81,0x81,0x43,0x3D,0x01,0x02,0x46,0x38, // '9'
	0xC3, // ':'
	0x50,0x05,0x60, // ';'
	0x00,0x40,0xE1,0xC1,0xC0,0x80,0x1C,0x01,0xC0,0x0E,0x00,0x40, // '<'
	0xFF,0xC0,0x00,0x03,0xFF, // '='
	0x80,0x1C,0x00,0xE0,0x0E,0x00,0x40,0xE0,0xE1,0xC0,0x80,0x00, // '>'
	0x7A,0x10,0x41,0x0C,0x63,0x08,0x20,0x02,0x08, // '?'
	0x0F,0xC0,0x60,0xC2,0x01,0x91,0xEA,0xC8,0x66,0x40,0x99,0x02,0x64,0x09,0x90,0x27,0x21,0xA4,0x7B,0x08,0x00,0x18,0x30,0x1F,0x80, // '@'
	0x04,0x00,0x80,0x28,0x05,0x01,0x10,0x22,0x08,0x21,0x04,0x3F,0x88,0x09,0x01,0x40,0x10, // 'A'
	0xFE,0x40,0xE0,0x30,0x18,0x1F,0xFA,0x07,0x01,0x80,0xC0,0x60,0x5F,0xC0, // 'B'
	0x1F,0x10,0xD0,0x10,0x08,0x04,0x02,0x01,0x00,0x80,0x20,0x08,0x63,0xE0, // 'C'
	0xFE,0x20,0xC8,0x0A,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x28,0x33,0xF8, // 'D'
	0xFF,0x80,0x80,0x80,0x80,0xFF,0x80,0x80,0x80,0x80,0x80,0xFF, // 'E'
	0xFF,0x02,0x04,0x08,0x1F,0xA0,0x40,0x81,0x02,0x04,0x00, // 'F'
	0x1F,0x88,0x34,0x06,0x00,0x80,0x20,0x08,0x3E,0x01,0x80,0x50,0x12,0x04,0x7E, // 'G'
	0x80,0x60,0x18,0x06,0x01,0x80,0x7F,0xF8,0x06,0x01,0x80,0x60,0x18,0x06,0x01, // 'H'
	0xFF,0xF0, // 'I'
	0x24,0x92,0x49,0x24,0x92,0x70, // 'J'
	0x81,0x41,0x21,0x11,0x09,0x07,0x02,0x81,0x20,0x88,0x42,0x20,0x90,0x20, // 'K'
	0x81,0x02,0x04,0x08,0x10,0x20,0x40,0x81,0x02,0x07,0xF0, // 'L'
	0xC0,0x78,0x0E,0x82,0xD0,0x5A,0x0B,0x22,0x64,0x4C,0x51,0x8A,0x30,0x86,0x00,0xC0,0x10, // 'M'
	0xC0,0x68,0x1A,0x06,0x41,0x88,0x62,0x18,0x46,0x09,0x82,0x60,0x58,0x16,0x03, // 'N'
	0x1F,0x04,0x11,0x01,0x40,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x28,0x08,0x82,0x0F,0x80, // 'O'
	0xFC,0x82,0x81,0x81,0x81,0x82,0xFC,0x80,0x80,0x80,0x80,0x80, // 'P'
	0x1F,0x04,0x11,0x01,0x40,0x18,0x03,0x00,0x60,0x0C,0x01,0x80,0x28,0x08,0x83,0x0F,0x80,0x08,0x00,0x80, // 'Q'
	0xFC,0x20,0x88,0x12,0x04,0x81,0x20,0x8F,0xE2,0x08,0x81,0x20,0x48,0x0A,0x02, // 'R'
	0x3C,0xC6,0x80,0x80,0x80,0x70,0x1E,0x03,0x01,0x81,0xC3,0x7C, // 'S'
	0xFF,0x84,0x02,0x01,0x00,0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00, // 'T'
	0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0x80,0x60,0x14,0x08,0xFC, // 'U'
	0x80,0x30,0x05,0x01,0x20,0x22,0x08,0x41,0x04,0x40,0x88,0x11,0x01,0x40,0x28,0x02,0x00, // 'V'
	0x81,0x03,0x02,0x05,0x0A,0x12,0x14,0x24,0x28,0x44,0x51,0x09,0x12,0x12,0x24,0x14,0x50,0x28,0xA0,0x20,0x80,0x41,0x00, // 'W'
	0xC1,0xA0,0x88,0x84,0x41,0x40,0x40,0x20,0x28,0x22,0x11,0x10,0x50,0x10, // 'X'
	0x80,0xA0,0x88,0x84,0x41,0x40,0x40,0x20,0x10,0x08,0x04,0x02,0x01,0x00, // 'Y'
	0xFF,0xC0,0x10,0x08,0x04,0x02,0x01,0x00,0x80,0x40,0x20,0x10,0x08,0x03,0xFF, // 'Z'
	0xF2,0x49,0x24,0x92,0x49,0xC0, // '['
	0x86,0x10,0x84,0x10,0x84,0x10,0x84,0x10,0x80, // '\'
	0xE4,0x92,0x49,0x24,0x93,0xC0, // ']'
	0x0C,0x07,0x82,0x11,0x02, // '^'
	0xFF, // '_'
	0xC6,0x30, // '`'
	0x3C,0x8C,0x0B,0xFC,0x30,0x60,0xE3,0x7A, // 'a'
	0x80,0x80,0x80,0xBC,0xC2,0x81,0x81,0x81,0x81,0x81,0xC2,0xBC, // 'b'
	0x3C,0x86,0x04,0x08,0x10,0x20,0x21,0x3C, // 'c'
	0x01,0x01,0x01,0x3D,0x43,0x81,0x81,0x81,0x81,0x81,0x43,0x3D, // 'd'
	0x38,0x8A,0x0C,0x1F,0xF0,0x20,0x21,0x3C, // 'e'
	0x3A,0x11,0xE4,0x21,0x08,0x42,0x10,0x80, // 'f'
	0x3D,0x43,0x81,0x81,0x81,0x81,0x81,0x43,0x3D,0x01,0x42,0x3C, // 'g'
	0x80,0x80,0x80,0xBC,0xC2,0x81,0x81,0x81,0x81,0x81,0x81,0x81, // 'h'
	0xDF,0xF0, // 'i'
	0x24,0x12,0x49,0x24,0x92,0x70, // 'j'
	0x80,0x80,0x80,0x82,0x84,0x88,0x90,0xE0,0x90,0x88,0x84,0x82, // 'k'
	0xFF,0xF0, // 'l'
	0xBC,0xF6,0x38,0xE0,0x83,0x04,0x18,0x20,0xC1,0x06,0x08,0x30,0x41,0x82,0x08, // 'm'
	0xBC,0xC2,0x81,0x81,0x81,0x81,0x81,0x81,0x81, // 'n'
	0x3C,0x42,0x81,0x81,0x81,0x81,0x81,0x42,0x3C, // 'o'
	0xBC,0xC2,0x81,0x81,0x81,0x81,0x81,0xC2,0xBC,0x80,0x80,0x80, // 'p'
	0x3D,0x43,0x81,0x81,0x81,0x81,0x81,0x43,0x3D,0x01,0x01,0x01, // 'q'
	0xBE,0x21,0x08,0x42,0x10,0x80, // 'r'
	0x7D,0x06,0x06,0x07,0x80,0xC0,0xC1,0x7C, // 's'
	0x42,0x3E,0x84,0x21,0x08,0x42,0x0E, // 't'
	0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x43,0x3D, // 'u'
	0x80,0xA0,0x24,0x11,0x04,0x22,0x08,0x81,0x40,0x70,0x08,0x00, // 'v'
	0x82,0x0C,0x10,0x51,0x44,0x8A,0x24,0x89,0x14,0x50,0xA2,0x82,0x08,0x10,0x40, // 'w'
	0xC3,0x42,0x24,0x24,0x18,0x24,0x24,0x42,0xC3, // 'x'
	0x80,0xA0,0x90,0x44,0x22,0x21,0x10,0x50,0x28,0x0C,0x04,0x02,0x0E,0x00, // 'y'
	0xFE,0x04,0x10,0x41,0x04,0x10,0x40,0xFE, // 'z'
	0x19,0x08,0x42,0x10,0x98,0x21,0x08,0x42,0x10,0x60, // '{'
	0xFF,0xFF, // '|'
	0xC1,0x08,0x42,0x10,0x83,0x21,0x08,0x42,0x13,0x00 // '}'
};
const GFXglyph Dialog_plain_16Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   6,    0,   -1 }, // ' '
	  {     1,   1,  12,   7,    2,  -12 }, // '!'
	  {     3,   4,   4,   7,    1,  -12 }, // '"'
	  {     5,  11,  11,  14,    1,  -11 }, // '#'
	  {    21,   7,  14,  11,    2,  -12 }, // '$'
	  {    34,  13,  12,  16,    1,  -12 }, // '%'
	  {    54,  11,  12,  13,    1,  -12 }, // '&'
	  {    71,   1,   4,   4,    1,  -12 }, // '''
	  {    72,   4,  14,   7,    1,  -12 }, // '('
	  {    79,   4,  14,   7,    1,  -12 }, // ')'
	  {    86,   7,   8,   9,    1,  -12 }, // '*'
	  {    93,   9,   9,  14,    2,   -9 }, // '+'
	  {   104,   2,   4,   6,    1,   -2 }, // ','
	  {   105,   4,   1,   7,    1,   -5 }, // '-'
	  {   106,   1,   2,   6,    2,   -2 }, // '.'
	  {   107,   5,  13,   6,    0,  -12 }, // '/'
	  {   116,   8,  12,  11,    1,  -12 }, // '0'
	  {   128,   7,  12,  11,    2,  -12 }, // '1'
	  {   139,   7,  12,  11,    1,  -12 }, // '2'
	  {   150,   8,  12,  11,    1,  -12 }, // '3'
	  {   162,   9,  12,  11,    1,  -12 }, // '4'
	  {   176,   8,  12,  11,    1,  -12 }, // '5'
	  {   188,   8,  12,  11,    1,  -12 }, // '6'
	  {   200,   8,  12,  11,    1,  -12 }, // '7'
	  {   212,   8,  12,  11,    1,  -12 }, // '8'
	  {   224,   8,  12,  11,    1,  -12 }, // '9'
	  {   236,   1,   8,   6,    2,   -8 }, // ':'
	  {   237,   2,  10,   6,    1,   -8 }, // ';'
	  {   240,  10,   9,  14,    2,   -9 }, // '<'
	  {   252,  10,   4,  14,    2,   -7 }, // '='
	  {   257,  10,   9,  14,    2,   -9 }, // '>'
	  {   269,   6,  12,  10,    1,  -12 }, // '?'
	  {   278,  14,  14,  17,    1,  -12 }, // '@'
	  {   303,  11,  12,  12,    0,  -12 }, // 'A'
	  {   320,   9,  12,  12,    1,  -12 }, // 'B'
	  {   334,   9,  12,  12,    1,  -12 }, // 'C'
	  {   348,  10,  12,  13,    1,  -12 }, // 'D'
	  {   363,   8,  12,  11,    1,  -12 }, // 'E'
	  {   375,   7,  12,  10,    1,  -12 }, // 'F'
	  {   386,  10,  12,  13,    1,  -12 }, // 'G'
	  {   401,  10,  12,  13,    1,  -12 }, // 'H'
	  {   416,   1,  12,   6,    2,  -12 }, // 'I'
	  {   418,   3,  15,   6,    0,  -12 }, // 'J'
	  {   424,   9,  12,  11,    1,  -12 }, // 'K'
	  {   438,   7,  12,  10,    1,  -12 }, // 'L'
	  {   449,  11,  12,  14,    1,  -12 }, // 'M'
	  {   466,  10,  12,  13,    1,  -12 }, // 'N'
	  {   481,  11,  12,  14,    1,  -12 }, // 'O'
	  {   498,   8,  12,  11,    1,  -12 }, // 'P'
	  {   510,  11,  14,  14,    1,  -12 }, // 'Q'
	  {   530,  10,  12,  12,    1,  -12 }, // 'R'
	  {   545,   8,  12,  11,    1,  -12 }, // 'S'
	  {   557,   9,  12,  10,    0,  -12 }, // 'T'
	  {   571,  10,  12,  13,    1,  -12 }, // 'U'
	  {   586,  11,  12,  12,    0,  -12 }, // 'V'
	  {   603,  15,  12,  18,    1,  -12 }, // 'W'
	  {   626,   9,  12,  12,    1,  -12 }, // 'X'
	  {   640,   9,  12,  10,    0,  -12 }, // 'Y'
	  {   654,  10,  12,  13,    1,  -12 }, // 'Z'
	  {   669,   3,  14,   7,    1,  -12 }, // '['
	  {   675,   5,  13,   6,    0,  -12 }, // '\'
	  {   684,   3,  14,   7,    2,  -12 }, // ']'
	  {   690,  10,   4,  14,    2,  -12 }, // '^'
	  {   695,   8,   1,   9,    0,    3 }, // '_'
	  {   696,   4,   3,   9,    1,  -13 }, // '`'
	  {   698,   7,   9,  10,    1,   -9 }, // 'a'
	  {   706,   8,  12,  11,    1,  -12 }, // 'b'
	  {   718,   7,   9,  10,    1,   -9 }, // 'c'
	  {   726,   8,  12,  11,    1,  -12 }, // 'd'
	  {   738,   7,   9,  10,    1,   -9 }, // 'e'
	  {   746,   5,  12,   7,    1,  -12 }, // 'f'
	  {   754,   8,  12,  11,    1,   -9 }, // 'g'
	  {   766,   8,  12,  11,    1,  -12 }, // 'h'
	  {   778,   1,  12,   4,    1,  -12 }, // 'i'
	  {   780,   3,  15,   4,   -1,  -12 }, // 'j'
	  {   786,   8,  12,  10,    1,  -12 }, // 'k'
	  {   798,   1,  12,   4,    1,  -12 }, // 'l'
	  {   800,  13,   9,  16,    1,   -9 }, // 'm'
	  {   815,   8,   9,  11,    1,   -9 }, // 'n'
	  {   824,   8,   9,  11,    1,   -9 }, // 'o'
	  {   833,   8,  12,  11,    1,   -9 }, // 'p'
	  {   845,   8,  12,  11,    1,   -9 }, // 'q'
	  {   857,   5,   9,   8,    1,   -9 }, // 'r'
	  {   863,   7,   9,  10,    1,   -9 }, // 's'
	  {   871,   5,  11,   7,    0,  -11 }, // 't'
	  {   878,   8,   9,  11,    1,   -9 }, // 'u'
	  {   887,  10,   9,  10,    0,   -9 }, // 'v'
	  {   899,  13,   9,  14,    0,   -9 }, // 'w'
	  {   914,   8,   9,  11,    1,   -9 }, // 'x'
	  {   923,   9,  12,  10,    0,   -9 }, // 'y'
	  {   937,   7,   9,  10,    1,   -9 }, // 'z'
	  {   945,   5,  15,  11,    2,  -12 }, // '{'
	  {   955,   1,  16,   6,    2,  -12 }, // '|'
	  {   957,   5,  15,  11,    2,  -12 } // '}'
};
const GFXfont Dialog_plain_16 PROGMEM = {
(uint8_t  *)Dialog_plain_16Bitmaps,(GFXglyph *)Dialog_plain_16Glyphs,0x20, 0x7E, 19};