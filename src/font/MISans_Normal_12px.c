/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --bpp 1 --size 12 --no-compress --font MiSans-Normal.ttf --symbols ° --range 32-127 --format lvgl -o MISans_Normal_12px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef MISANS_NORMAL_12PX
#define MISANS_NORMAL_12PX 1
#endif

#if MISANS_NORMAL_12PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfc, 0x40,

    /* U+0022 "\"" */
    0xb6, 0x80,

    /* U+0023 "#" */
    0x12, 0x12, 0x14, 0x7f, 0x24, 0x24, 0xfe, 0x28,
    0x48, 0x48,

    /* U+0024 "$" */
    0x23, 0xab, 0x4a, 0x30, 0xc5, 0x2d, 0x5c, 0x40,

    /* U+0025 "%" */
    0x61, 0x49, 0x25, 0x12, 0x86, 0x80, 0x40, 0x4c,
    0x49, 0x24, 0xa1, 0x80,

    /* U+0026 "&" */
    0x38, 0x44, 0x44, 0x4c, 0x30, 0x50, 0x8a, 0x86,
    0xc6, 0x7b,

    /* U+0027 "'" */
    0xe0,

    /* U+0028 "(" */
    0x16, 0xaa, 0xa5,

    /* U+0029 ")" */
    0x29, 0x55, 0x5a,

    /* U+002A "*" */
    0x5f, 0xa0,

    /* U+002B "+" */
    0x21, 0x9, 0xf2, 0x10,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x12, 0x22, 0x44, 0x44,

    /* U+0030 "0" */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x49, 0xc0,

    /* U+0031 "1" */
    0x7c, 0x92, 0x49, 0x24,

    /* U+0032 "2" */
    0x39, 0x30, 0x41, 0x8, 0x21, 0x8, 0x43, 0xf0,

    /* U+0033 "3" */
    0xf8, 0x21, 0x8, 0x38, 0x30, 0x41, 0xcd, 0xe0,

    /* U+0034 "4" */
    0x18, 0x62, 0x8a, 0x49, 0x28, 0xbf, 0x8, 0x20,

    /* U+0035 "5" */
    0x79, 0x4, 0x10, 0x79, 0x30, 0x41, 0xcd, 0xe0,

    /* U+0036 "6" */
    0x10, 0x82, 0x10, 0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0037 "7" */
    0xf8, 0x44, 0x21, 0x10, 0x88, 0x42, 0x0,

    /* U+0038 "8" */
    0x7b, 0x38, 0x63, 0x7b, 0x38, 0x61, 0xcd, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x38, 0x61, 0xcd, 0xe0, 0x84, 0x10, 0x80,

    /* U+003A ":" */
    0x82,

    /* U+003B ";" */
    0x83, 0x0,

    /* U+003C "<" */
    0xc, 0xcc, 0x30, 0x60, 0x60, 0x40,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0x81, 0x81, 0x83, 0x33, 0x0, 0x0,

    /* U+003F "?" */
    0x74, 0x42, 0x11, 0x10, 0x80, 0x1, 0x0,

    /* U+0040 "@" */
    0x3e, 0x31, 0x90, 0x73, 0xda, 0x2d, 0x16, 0x75,
    0x80, 0x60, 0xf, 0x0,

    /* U+0041 "A" */
    0x18, 0x18, 0x18, 0x2c, 0x24, 0x24, 0x7e, 0x42,
    0x42, 0x81,

    /* U+0042 "B" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x61, 0x87, 0xe0,

    /* U+0043 "C" */
    0x3c, 0x87, 0x4, 0x8, 0x10, 0x20, 0x60, 0x42,
    0x78,

    /* U+0044 "D" */
    0xf9, 0xa, 0x1c, 0x18, 0x30, 0x60, 0xc3, 0x85,
    0xf0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0x83, 0xe8, 0x20, 0x83, 0xf0,

    /* U+0046 "F" */
    0xfc, 0x21, 0x8, 0x7e, 0x10, 0x84, 0x0,

    /* U+0047 "G" */
    0x3c, 0x8f, 0x4, 0x8, 0x11, 0xe0, 0xc1, 0x42,
    0x78,

    /* U+0048 "H" */
    0x83, 0x6, 0xc, 0x18, 0x3f, 0xe0, 0xc1, 0x83,
    0x4,

    /* U+0049 "I" */
    0xff, 0xc0,

    /* U+004A "J" */
    0x11, 0x11, 0x11, 0x11, 0x9e,

    /* U+004B "K" */
    0x85, 0x12, 0x45, 0xe, 0x1a, 0x24, 0x44, 0x8d,
    0x8,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x83, 0xf0,

    /* U+004D "M" */
    0x80, 0xe0, 0xf0, 0x74, 0x5b, 0x6c, 0xa6, 0x23,
    0x11, 0x80, 0xc0, 0x40,

    /* U+004E "N" */
    0x83, 0x87, 0x8d, 0x19, 0x32, 0x62, 0xc7, 0x87,
    0x4,

    /* U+004F "O" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0xc3,
    0x42, 0x3c,

    /* U+0050 "P" */
    0xfa, 0x38, 0x61, 0x8f, 0xe8, 0x20, 0x82, 0x0,

    /* U+0051 "Q" */
    0x3c, 0x42, 0xc3, 0x81, 0x81, 0x81, 0x81, 0xc7,
    0x46, 0x3e, 0x1,

    /* U+0052 "R" */
    0xfa, 0x38, 0x61, 0x8f, 0xe9, 0x22, 0x8a, 0x10,

    /* U+0053 "S" */
    0x7b, 0x38, 0x20, 0x60, 0x60, 0x41, 0x8d, 0xe0,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20,

    /* U+0055 "U" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x44,
    0x70,

    /* U+0056 "V" */
    0x81, 0x42, 0x42, 0x42, 0x24, 0x24, 0x24, 0x18,
    0x18, 0x18,

    /* U+0057 "W" */
    0x84, 0x30, 0xc5, 0x28, 0xa5, 0x24, 0xa4, 0x92,
    0x8c, 0x51, 0x8c, 0x30, 0x86, 0x10,

    /* U+0058 "X" */
    0x42, 0x88, 0x91, 0xc1, 0x3, 0xa, 0x12, 0x45,
    0x84,

    /* U+0059 "Y" */
    0x82, 0x89, 0x11, 0x42, 0x82, 0x4, 0x8, 0x10,
    0x20,

    /* U+005A "Z" */
    0xfc, 0x10, 0x84, 0x10, 0x82, 0x10, 0x83, 0xf0,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x70,

    /* U+005C "\\" */
    0x84, 0x44, 0x42, 0x22, 0x31,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0xf0,

    /* U+005E "^" */
    0x21, 0x94, 0x90,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x10,

    /* U+0061 "a" */
    0x70, 0x42, 0xf8, 0xc5, 0xe0,

    /* U+0062 "b" */
    0x82, 0x8, 0x2e, 0xce, 0x18, 0x61, 0xce, 0xe0,

    /* U+0063 "c" */
    0x7e, 0x61, 0x8, 0x65, 0xc0,

    /* U+0064 "d" */
    0x4, 0x10, 0x5d, 0xce, 0x18, 0x61, 0xcd, 0xd0,

    /* U+0065 "e" */
    0x7b, 0x38, 0x7f, 0x83, 0x17, 0x80,

    /* U+0066 "f" */
    0x34, 0x4f, 0x44, 0x44, 0x44,

    /* U+0067 "g" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0xcd, 0xe0,

    /* U+0068 "h" */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x8c, 0x40,

    /* U+0069 "i" */
    0x9f, 0xc0,

    /* U+006A "j" */
    0x20, 0x12, 0x49, 0x24, 0x9e,

    /* U+006B "k" */
    0x84, 0x21, 0x3b, 0x53, 0x92, 0x94, 0x40,

    /* U+006C "l" */
    0xaa, 0xaa, 0xb0,

    /* U+006D "m" */
    0xb7, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x22,

    /* U+006E "n" */
    0xb6, 0x63, 0x18, 0xc6, 0x20,

    /* U+006F "o" */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,

    /* U+0070 "p" */
    0xbb, 0x38, 0x61, 0x87, 0x3b, 0xa0, 0x82, 0x0,

    /* U+0071 "q" */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0x4, 0x10,

    /* U+0072 "r" */
    0xbc, 0x88, 0x88, 0x80,

    /* U+0073 "s" */
    0x74, 0x60, 0xe0, 0xc5, 0xc0,

    /* U+0074 "t" */
    0x44, 0xf4, 0x44, 0x44, 0x70,

    /* U+0075 "u" */
    0x8c, 0x63, 0x18, 0xcd, 0xa0,

    /* U+0076 "v" */
    0x85, 0x24, 0x92, 0x30, 0xc3, 0x0,

    /* U+0077 "w" */
    0x88, 0xc6, 0x55, 0x2a, 0xa5, 0x51, 0x98, 0x88,

    /* U+0078 "x" */
    0x49, 0x23, 0x8, 0x31, 0x2c, 0x80,

    /* U+0079 "y" */
    0x85, 0x14, 0x92, 0x30, 0xc3, 0x8, 0x20, 0x80,

    /* U+007A "z" */
    0xf8, 0xc4, 0x44, 0x63, 0xe0,

    /* U+007B "{" */
    0x29, 0x24, 0xa2, 0x49, 0x10,

    /* U+007C "|" */
    0xff, 0xf0,

    /* U+007D "}" */
    0x89, 0x24, 0x8a, 0x49, 0x40,

    /* U+007E "~" */
    0xc9, 0x80,

    /* U+007F "" */
    0x0,

    /* U+00B0 "°" */
    0x69, 0x96
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 55, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 50, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 64, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 110, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 37, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 46, .adv_w = 58, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 49, .adv_w = 58, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 52, .adv_w = 85, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 54, .adv_w = 116, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 58, .adv_w = 49, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 86, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 60, .adv_w = 46, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 75, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 75, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 99, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 46, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 49, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 144, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 150, .adv_w = 116, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 153, .adv_w = 116, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 159, .adv_w = 94, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 109, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 141, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 137, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 46, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 90, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 167, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 119, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 150, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 321, .adv_w = 121, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 126, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 183, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 410, .adv_w = 65, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 420, .adv_w = 84, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 423, .adv_w = 87, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 424, .adv_w = 49, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 425, .adv_w = 103, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 451, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 66, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 470, .adv_w = 111, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 46, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 47, .box_w = 3, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 484, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 47, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 169, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 521, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 529, .adv_w = 72, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 67, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 151, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 98, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 576, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 67, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 586, .adv_w = 42, .box_w = 1, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 588, .adv_w = 67, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 593, .adv_w = 100, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 595, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 596, .adv_w = 78, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 96, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 1, .glyph_id_start = 97,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 2,
    1, 0, 0, 0, 0, 3, 4, 3,
    5, 6, 0, 7, 8, 9, 10, 11,
    12, 13, 14, 0, 0, 0, 0, 0,
    15, 0, 16, 17, 18, 19, 20, 21,
    22, 0, 0, 23, 24, 25, 0, 0,
    19, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 0, 0, 0, 0,
    0, 0, 37, 38, 39, 0, 40, 41,
    42, 43, 0, 0, 44, 45, 43, 43,
    38, 38, 42, 46, 47, 48, 42, 49,
    50, 51, 49, 52, 0, 0, 0, 0,
    0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 0, 2,
    1, 0, 0, 0, 0, 3, 4, 3,
    5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 0, 0, 0, 0, 0,
    16, 0, 17, 0, 18, 0, 0, 0,
    18, 0, 0, 19, 0, 0, 0, 0,
    18, 0, 18, 0, 20, 21, 22, 23,
    24, 25, 26, 27, 0, 0, 0, 0,
    0, 0, 28, 0, 29, 29, 29, 30,
    29, 0, 31, 31, 0, 32, 33, 33,
    29, 33, 29, 33, 34, 35, 36, 37,
    38, 39, 37, 40, 0, 0, 0, 0,
    0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -17, 0, -11, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -5, -3, -17, -5, -17, -11,
    0, -19, 0, -3, -2, 0, 0, -4,
    0, 0, -5, 0, -7, -5, 0, 0,
    0, 0, 0, 0, 0, -7, -17, 0,
    0, -9, -4, -4, -6, -2, -20, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -13, 0, -10, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -7, 0, 0, 0, 0, -6,
    -3, 0, 0, 0, -4, 0, 0, 0,
    -5, 0, -5, 0, -7, 0, -5, -3,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, -3, 0, 0,
    -5, -7, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, -2, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, -5, 0,
    -4, 0, 0, 0, -5, 0, -4, -6,
    0, 0, 0, 0, -5, 0, -8, 0,
    0, -7, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, -5, 0,
    0, 0, 0, 0, -3, 0, 0, -8,
    0, 0, 0, 0, 0, 0, -4, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -13, 0, -4, 0, 0, 0, -11, 0,
    0, 0, 0, 0, -10, 0, -2, -12,
    0, 0, 0, 0, -19, 0, -15, 0,
    -3, -20, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, -5, -4,
    4, 0, -27, -5, -18, -4, 0, 0,
    0, -14, 0, -14, 1, -6, 0, 2,
    -18, 0, -20, 0, 0, 0, 0, 0,
    0, 0, 0, -16, -16, -5, 0, 0,
    -9, -11, 0, -7, 0, 0, -7, -7,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -4, -4,
    0, 0, 0, 0, -4, 0, -3, 0,
    0, -7, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, 0, -21, 0, -10, 0, 0, 0,
    0, -6, 0, -5, 0, -4, 0, 0,
    -13, 0, -16, 0, 0, 0, -2, 0,
    -8, -4, 0, -7, -5, 2, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -9, -4, -6, 2, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -17, -2, 0, -7, 0, -5, -11, 0,
    0, 0, 0, 0, 0, 0, -13, -15,
    0, -7, 0, 0, -18, -3, -19, -13,
    0, -18, 0, 0, -3, -1, 0, -1,
    0, 0, -4, -2, -9, -6, 0, 0,
    -6, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    -4, 0, -1, 0, -5, 0, -7, -4,
    -4, -7, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -1, -2,
    0, 0, 0, -7, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -1, 0, 0, 0,
    -4, -5, -2, -2, -4, 0, 0, 0,
    0, 0, 0, 0, -4, -4, -2, 0,
    -4, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -7, 0, -12, 0, -6, 0, -7, -3,
    -7, -10, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -2, 0, 0,
    3, -5, -13, 0, 0, 0, 0, 0,
    0, -5, 0, -6, 0, 0, 0, 0,
    -12, 0, -30, -2, 0, 0, 0, 0,
    -4, 0, 0, -10, -7, 0, 0, 0,
    -4, -3, 0, -4, -2, -1, -7, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -4, 0, 0, 0, -6, 0, -7, -3,
    -3, -9, -2, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -5, -6, -4, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -7, 4, -17, 0, -8, -6, 0,
    0, -5, 0, 0, 0, 0, -8, -6,
    0, -10, -4, -4, 0, -10, 0, 0,
    0, 0, 0, -5, -10, -5, 0, -3,
    -2, -2, -9, -10, -13, -12, 5, 0,
    -17, 0, 5, -17, 0, 0, -13, 0,
    0, 0, 0, 0, -5, 0, -22, -17,
    0, -8, 0, 0, -30, -5, -26, -16,
    0, -33, 0, 0, -4, -4, 0, 0,
    0, 0, -7, -5, -15, -10, 0, 0,
    0, -8, -19, 0, 0, 0, 0, -1,
    0, -5, 0, 0, 0, 0, 0, 0,
    -14, 0, -33, 0, -4, 0, -5, -3,
    -5, -6, -4, -6, -5, 4, 0, 0,
    0, 1, 5, 0, 6, 6, 2, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, -6, 0, -4, -4,
    -8, -10, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -5, 0, -4, 0, -3, -2,
    0, -4, 0, -3, -4, 0, 0, 0,
    0, 0, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -2, 1,
    -1, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -4, -2, -3,
    4, -13, -20, -16, 0, -7, 0, 0,
    0, -19, 0, -15, 0, -4, 0, 0,
    -18, -6, -26, -2, 0, 0, -4, 0,
    -5, 0, 0, -23, -23, -7, 0, 0,
    -17, -21, -5, -15, -21, -19, -21, -18,
    0, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, -7, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -13, -24, -7, 0, -5, 0, 0,
    0, -12, -4, -10, 0, -3, 0, 0,
    -19, -7, -29, 0, 0, 0, 0, 0,
    0, 0, 0, -16, -14, -2, 0, 0,
    -9, -11, -2, -7, -5, -5, -7, -6,
    0, -7, -16, -5, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -13, -3, -19, 2, 0, 0, 0, 0,
    0, 0, 0, -12, -10, -2, 0, 0,
    -7, -9, 0, -8, -2, -3, -5, -4,
    0, -5, 2, -15, 0, 0, -5, 0,
    -2, -3, -5, -4, 0, 0, -8, -4,
    0, -7, -1, -1, -5, -3, 0, 0,
    0, 0, 0, -3, -6, -3, 0, -1,
    0, -5, -7, -8, -10, -10, 0, 0,
    0, -15, -22, -12, 0, -9, 0, -3,
    -2, -20, 0, -17, 0, -7, -3, 0,
    -18, -10, -33, -4, 0, 0, 0, 0,
    0, 0, 0, -20, -20, -7, 0, 0,
    -15, -17, -5, -15, -8, -8, -9, -11,
    0, -8, 0, -10, 0, 0, 0, 0,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, -10, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, -3, 0, 0, 0,
    0, 0, -6, -6, -8, -8, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, -3, -10,
    0, 0, 0, 0, -20, 0, -14, -11,
    0, -17, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, 0, 0,
    -7, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, 0, -5, -13,
    -3, 0, 0, 0, -23, 0, -14, -10,
    -6, -20, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, -4, -1,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, 0, 0, 0, -21, 0, -10, -6,
    -3, -20, 0, -2, -2, 0, -2, -1,
    0, 0, 0, 0, -2, 0, -3, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, 0, 0, -10,
    0, 0, 0, 0, -20, 0, -12, -8,
    -6, -16, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -1, -3, 0,
    6, -6, -13, 0, 0, 0, 0, 0,
    0, -8, 0, 0, 4, 0, 4, 0,
    -11, 0, -14, 0, 0, 0, 0, 0,
    0, 0, 0, -4, -3, 0, 0, 0,
    0, -3, 2, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, 0, -5,
    0, 0, 0, 0, -17, 0, -9, -7,
    -2, -14, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, -3, -9,
    0, 0, 0, 0, -23, 0, -15, -12,
    -3, -19, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -1, -2, 0,
    -4, -3, 2, -5, 0, 0, 0, 0,
    0, -6, 0, -4, 0, -5, -1, -3,
    0, -4, 0, 0, -19, -2, -8, -4,
    0, -14, 0, -2, -4, 0, 0, -1,
    0, -2, -1, -3, 0, 0, 0, 0,
    0, -3, 3, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
    1, 0, 0, 1, -2, -1, 0, 0,
    0, -9, -20, 0, 0, 0, 0, -3,
    -10, -10, 0, -5, 0, 0, 2, 0,
    0, 0, 0, 0, -17, 0, 0, 0,
    -7, -6, -10, -4, -2, 2, 0, 0,
    0, -2, 3, -3, 4, 4, 2, 0,
    -6, 0, 0, 0, 0, 0, -6, 0,
    0, 0, 0, 0, -5, 0, 0, -6,
    0, 0, 0, 0, -20, 0, -10, -8,
    -4, -14, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 1, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 3, 0,
    0, 0, 0, 0, -4, 0, -3, 0,
    0, -9, 0, 0, -1, 2, 0, 0,
    0, -1, 0, -1, 0, 0, 0, 0,
    0, -8, -15, 0, 0, 0, 0, 0,
    0, -5, 0, -6, 0, 0, 0, 0,
    -9, 0, -17, 0, -21, 0, -5, -2,
    -10, -8, -10, -4, -2, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -4, -10, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, -14, 0, -19, 0, -5, -3,
    -10, -8, -8, -3, -2, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -4, 0, 0, 0, 0,
    0, -7, 0, -5, -5, -3, 0, 0,
    0, -2, 0, 0, -21, 0, -7, -5,
    3, -9, 0, -3, -4, 0, 0, -2,
    0, -4, 0, -2, 0, 0, 0, 0,
    0, -7, 0, -4, 0, 0, 0, 0,
    0, -8, 0, -4, -5, 0, -1, 0,
    0, -6, 0, 0, -17, 0, -8, -5,
    0, -11, 0, -1, -3, 0, 0, 0,
    0, -1, 0, -1, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 52,
    .right_class_cnt     = 40,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t MISans_Normal_12px = {
#else
lv_font_t MISans_Normal_12px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if MISANS_NORMAL_12PX*/

