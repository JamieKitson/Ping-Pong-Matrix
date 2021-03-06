const uint8_t TomThumbBitmaps[] PROGMEM = {
  0x00, 0xE8, 0xB4, 0xBE, 0xFA, 0x79, 0xE4, 0x85, 0x42, 0xDB, 0xD6, 0xC0, 
  0x6A, 0x40, 0x95, 0x80, 0xAA, 0x80, 0x5D, 0x00, 0x60, 0xE0, 0x80, 0x25, 
  0x48, 0xD6, 0xD6, 0x00, 0x75, 0x40, 0xC5, 0xEE, 0x00, 0xC5, 0xD6, 0x00, 
  0xB7, 0x92, 0xF3, 0x1E, 0x00, 0xD3, 0x56, 0x00, 0xE5, 0xA4, 0x00, 0xD7, 
  0xD6, 0x00, 0xD5, 0x96, 0x00, 0xA0, 0x46, 0x2A, 0x22, 0xE3, 0x80, 0x88, 
  0xA8, 0xE5, 0x04, 0x57, 0xC6, 0xD7, 0xDA, 0x00, 0xD7, 0xDE, 0x00, 0xD6, 
  0x46, 0x00, 0xD6, 0xDE, 0x00, 0xF3, 0xCE, 0xF3, 0xC8, 0xF3, 0xD6, 0x00, 
  0xB7, 0xDA, 0xE9, 0x2E, 0x24, 0xD6, 0x00, 0xBF, 0x5A, 0x00, 0x92, 0x4E, 
  0xBF, 0xDA, 0xBF, 0xFA, 0xD6, 0xD6, 0x00, 0xD7, 0xC8, 0x00, 0xD6, 0xF6, 
  0x00, 0xD7, 0xEA, 0xD5, 0x56, 0x00, 0xE9, 0x24, 0xB6, 0xD6, 0x00, 0xB6, 
  0xB4, 0x00, 0xB7, 0xFA, 0xBD, 0x7A, 0x00, 0xB5, 0xA4, 0x00, 0xE5, 0x4E, 
  0x00, 0xF2, 0x4E, 0x88, 0x80, 0xE4, 0x9E, 0x54, 0xE0, 0x90, 0xC7, 0xB0, 
  0x93, 0x5E, 0x00, 0xD6, 0x30, 0x27, 0xD6, 0x00, 0xDE, 0x30, 0x6B, 0xA4, 
  0x00, 0xD5, 0x96, 0x00, 0x93, 0x5A, 0x00, 0xB8, 0x20, 0x9A, 0xC0, 0x97, 
  0x6A, 0xC9, 0x2E, 0xFF, 0xD0, 0xD6, 0xD0, 0x1A, 0xB0, 0xD7, 0xC8, 0x00, 
  0xD5, 0x92, 0x00, 0xF2, 0x40, 0xF9, 0xF0, 0x5D, 0x22, 0x00, 0xB6, 0xB0, 
  0xB7, 0xA0, 0xBF, 0xF0, 0xA9, 0x50, 0xB5, 0x96, 0x00, 0xEF, 0x70, 0x6A, 
  0x26, 0xD8, 0xC8, 0xAC, 0x78
};

const GFXglyph TomThumbGlyphs[] PROGMEM = {
  {     0,   1,   1,   2,    0,   -5 },   // 0x20 ' '
  {     1,   1,   5,   2,    0,   -5 },   // 0x21 '!'
  {     2,   3,   2,   4,    0,   -5 },   // 0x22 '"'
  {     3,   3,   5,   4,    0,   -5 },   // 0x23 '#'
  {     5,   3,   5,   4,    0,   -5 },   // 0x24 '$'
  {     7,   3,   5,   4,    0,   -5 },   // 0x25 '%'
  {     9,   3,   5,   4,    0,   -5 },   // 0x26 '&'
  {    11,   1,   2,   2,    0,   -5 },   // 0x27 '''
  {    12,   2,   5,   3,    0,   -5 },   // 0x28 '('
  {    14,   2,   5,   3,    0,   -5 },   // 0x29 ')'
  {    16,   3,   3,   4,    0,   -5 },   // 0x2A '*'
  {    18,   3,   3,   4,    0,   -4 },   // 0x2B '+'
  {    20,   2,   2,   3,    0,   -2 },   // 0x2C ','
  {    21,   3,   1,   4,    0,   -3 },   // 0x2D '-'
  {    22,   1,   1,   2,    0,   -1 },   // 0x2E '.'
  {    23,   3,   5,   4,    0,   -5 },   // 0x2F '/'
  {    25,   3,   5,   4,    0,   -5 },   // 0x30 '0'
  {    28,   2,   5,   3,    0,   -5 },   // 0x31 '1'
  {    30,   3,   5,   4,    0,   -5 },   // 0x32 '2'
  {    33,   3,   5,   4,    0,   -5 },   // 0x33 '3'
  {    36,   3,   5,   4,    0,   -5 },   // 0x34 '4'
  {    38,   3,   5,   4,    0,   -5 },   // 0x35 '5'
  {    41,   3,   5,   4,    0,   -5 },   // 0x36 '6'
  {    44,   3,   5,   4,    0,   -5 },   // 0x37 '7'
  {    47,   3,   5,   4,    0,   -5 },   // 0x38 '8'
  {    50,   3,   5,   4,    0,   -5 },   // 0x39 '9'
  {    53,   1,   3,   2,    0,   -4 },   // 0x3A ':'
  {    54,   2,   4,   3,    0,   -4 },   // 0x3B ';'
  {    55,   3,   5,   4,    0,   -5 },   // 0x3C '<'
  {    57,   3,   3,   4,    0,   -4 },   // 0x3D '='
  {    59,   3,   5,   4,    0,   -5 },   // 0x3E '>'
  {    61,   3,   5,   4,    0,   -5 },   // 0x3F '?'
  {    63,   3,   5,   4,    0,   -5 },   // 0x40 '@'
  {    65,   3,   5,   4,    0,   -5 },   // 0x41 'A'
  {    68,   3,   5,   4,    0,   -5 },   // 0x42 'B'
  {    71,   3,   5,   4,    0,   -5 },   // 0x43 'C'
  {    74,   3,   5,   4,    0,   -5 },   // 0x44 'D'
  {    77,   3,   5,   4,    0,   -5 },   // 0x45 'E'
  {    79,   3,   5,   4,    0,   -5 },   // 0x46 'F'
  {    81,   3,   5,   4,    0,   -5 },   // 0x47 'G'
  {    84,   3,   5,   4,    0,   -5 },   // 0x48 'H'
  {    86,   3,   5,   4,    0,   -5 },   // 0x49 'I'
  {    88,   3,   5,   4,    0,   -5 },   // 0x4A 'J'
  {    91,   3,   5,   4,    0,   -5 },   // 0x4B 'K'
  {    94,   3,   5,   4,    0,   -5 },   // 0x4C 'L'
  {    96,   3,   5,   4,    0,   -5 },   // 0x4D 'M'
  {    98,   3,   5,   4,    0,   -5 },   // 0x4E 'N'
  {   100,   3,   5,   4,    0,   -5 },   // 0x4F 'O'
  {   103,   3,   5,   4,    0,   -5 },   // 0x50 'P'
  {   106,   3,   5,   4,    0,   -5 },   // 0x51 'Q'
  {   109,   3,   5,   4,    0,   -5 },   // 0x52 'R'
  {   111,   3,   5,   4,    0,   -5 },   // 0x53 'S'
  {   114,   3,   5,   4,    0,   -5 },   // 0x54 'T'
  {   116,   3,   5,   4,    0,   -5 },   // 0x55 'U'
  {   119,   3,   5,   4,    0,   -5 },   // 0x56 'V'
  {   122,   3,   5,   4,    0,   -5 },   // 0x57 'W'
  {   124,   3,   5,   4,    0,   -5 },   // 0x58 'X'
  {   127,   3,   5,   4,    0,   -5 },   // 0x59 'Y'
  {   130,   3,   5,   4,    0,   -5 },   // 0x5A 'Z'
  {   133,   3,   5,   4,    0,   -5 },   // 0x5B '['
  {   135,   3,   3,   4,    0,   -4 },   // 0x5C '\'
  {   137,   3,   5,   4,    0,   -5 },   // 0x5D ']'
  {   139,   3,   2,   4,    0,   -5 },   // 0x5E '^'
  {   140,   3,   1,   4,    0,   -1 },   // 0x5F '_'
  {   141,   2,   2,   3,    0,   -5 },   // 0x60 '`'
  {   142,   3,   4,   4,    0,   -4 },   // 0x61 'a'
  {   144,   3,   5,   4,    0,   -5 },   // 0x62 'b'
  {   147,   3,   4,   4,    0,   -4 },   // 0x63 'c'
  {   149,   3,   5,   4,    0,   -5 },   // 0x64 'd'
  {   152,   3,   4,   4,    0,   -4 },   // 0x65 'e'
  {   154,   3,   5,   4,    0,   -5 },   // 0x66 'f'
  {   157,   3,   5,   4,    0,   -4 },   // 0x67 'g'
  {   160,   3,   5,   4,    0,   -5 },   // 0x68 'h'
  {   163,   1,   5,   2,    0,   -5 },   // 0x69 'i'
  {   164,   3,   6,   4,    0,   -5 },   // 0x6A 'j'
  {   167,   3,   5,   4,    0,   -5 },   // 0x6B 'k'
  {   169,   3,   5,   4,    0,   -5 },   // 0x6C 'l'
  {   171,   3,   4,   4,    0,   -4 },   // 0x6D 'm'
  {   173,   3,   4,   4,    0,   -4 },   // 0x6E 'n'
  {   175,   3,   4,   4,    0,   -4 },   // 0x6F 'o'
  {   177,   3,   5,   4,    0,   -4 },   // 0x70 'p'
  {   180,   3,   5,   4,    0,   -4 },   // 0x71 'q'
  {   183,   3,   4,   4,    0,   -4 },   // 0x72 'r'
  {   185,   3,   4,   4,    0,   -4 },   // 0x73 's'
  {   187,   3,   5,   4,    0,   -5 },   // 0x74 't'
  {   190,   3,   4,   4,    0,   -4 },   // 0x75 'u'
  {   192,   3,   4,   4,    0,   -4 },   // 0x76 'v'
  {   194,   3,   4,   4,    0,   -4 },   // 0x77 'w'
  {   196,   3,   4,   4,    0,   -4 },   // 0x78 'x'
  {   198,   3,   5,   4,    0,   -4 },   // 0x79 'y'
  {   201,   3,   4,   4,    0,   -4 },   // 0x7A 'z'
  {   203,   3,   5,   4,    0,   -5 },   // 0x7B '{'
  {   205,   1,   5,   2,    0,   -5 },   // 0x7C '|'
  {   206,   3,   5,   4,    0,   -5 },   // 0x7D '}'
  {   208,   3,   2,   4,    0,   -5 }    // 0x7E '~'
};

const GFXfont TomThumb PROGMEM = {(uint8_t *)TomThumbBitmaps,    
                                  (GFXglyph *)TomThumbGlyphs, 0x20, 0x7E,     6};
