/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font MiSans-Medium.ttf --range 32-127 --format lvgl -o MiSans_Medium_16px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef MISANS_MEDIUM_16PX
#define MISANS_MEDIUM_16PX 1
#endif

#if MISANS_MEDIUM_16PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xf,

    /* U+0022 "\"" */
    0xbb, 0xb9,

    /* U+0023 "#" */
    0x9, 0x6, 0x41, 0x91, 0xff, 0x13, 0x4, 0x83,
    0x23, 0xfe, 0x22, 0x9, 0x82, 0x40, 0x90,

    /* U+0024 "$" */
    0x18, 0x1c, 0x7e, 0xdb, 0xd8, 0xd8, 0xf8, 0x7c,
    0x1e, 0x1b, 0x1b, 0xdb, 0xfe, 0x3c, 0x18,

    /* U+0025 "%" */
    0x78, 0x26, 0x62, 0x33, 0x21, 0x99, 0x7, 0x90,
    0x1, 0x0, 0xb, 0xc0, 0xb3, 0x9, 0x98, 0x4c,
    0xc4, 0x66, 0x41, 0xe0,

    /* U+0026 "&" */
    0x1e, 0xc, 0x61, 0x8c, 0x31, 0x83, 0xe0, 0x78,
    0x1f, 0x16, 0x76, 0xc7, 0xd8, 0x71, 0x9e, 0x1f,
    0x60,

    /* U+0027 "'" */
    0xf0,

    /* U+0028 "(" */
    0x36, 0x64, 0xcc, 0xcc, 0xcc, 0x66, 0x63,

    /* U+0029 ")" */
    0xc6, 0x66, 0x33, 0x33, 0x33, 0x66, 0x6c,

    /* U+002A "*" */
    0x27, 0xcd, 0xf2, 0x0,

    /* U+002B "+" */
    0x18, 0x30, 0x67, 0xf1, 0x83, 0x6, 0x0,

    /* U+002C "," */
    0xf7, 0x80,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x18, 0x84, 0x63, 0x11, 0x8c, 0x46, 0x31, 0x0,

    /* U+0030 "0" */
    0x3e, 0x31, 0x98, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xb1, 0x98, 0xc7, 0xc0,

    /* U+0031 "1" */
    0x3f, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x30,

    /* U+0032 "2" */
    0x3c, 0xc6, 0x43, 0x3, 0x3, 0x6, 0xe, 0x1c,
    0x38, 0x70, 0x60, 0xff,

    /* U+0033 "3" */
    0xfe, 0xe, 0xc, 0x18, 0x30, 0x3c, 0x6, 0x3,
    0x3, 0x83, 0xc6, 0x7c,

    /* U+0034 "4" */
    0xe, 0x7, 0x7, 0x82, 0xc3, 0x63, 0x31, 0x99,
    0x8c, 0xff, 0x83, 0x1, 0x80, 0xc0,

    /* U+0035 "5" */
    0x7e, 0xc0, 0xc0, 0xc0, 0xfc, 0xc6, 0x3, 0x3,
    0x3, 0x83, 0xc6, 0x7c,

    /* U+0036 "6" */
    0x8, 0x18, 0x30, 0x20, 0x7c, 0x66, 0xc3, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0037 "7" */
    0xfe, 0xc, 0x10, 0x60, 0xc3, 0x6, 0x8, 0x30,
    0x61, 0x83, 0x0,

    /* U+0038 "8" */
    0x3c, 0xe7, 0xc3, 0xc3, 0x66, 0x3c, 0x66, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0x67, 0x3e, 0x6,
    0xc, 0xc, 0x18, 0x10,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0xf0, 0x3, 0xde,

    /* U+003C "<" */
    0x1, 0x7, 0x1c, 0x70, 0xe0, 0xe0, 0x38, 0x1e,
    0x7, 0x1,

    /* U+003D "=" */
    0xfe, 0x0, 0x7, 0xf0,

    /* U+003E ">" */
    0x80, 0xc0, 0x70, 0x1c, 0x7, 0x7, 0x1c, 0x70,
    0xc0, 0x0,

    /* U+003F "?" */
    0x3d, 0x8c, 0x18, 0x30, 0xe3, 0x86, 0xc, 0x0,
    0x0, 0x60, 0xc0,

    /* U+0040 "@" */
    0xf, 0x83, 0xc, 0x40, 0x2c, 0xfb, 0x99, 0x99,
    0x99, 0x99, 0x99, 0x99, 0xce, 0xe4, 0x0, 0x30,
    0x1, 0xf8,

    /* U+0041 "A" */
    0xc, 0x1, 0xc0, 0x38, 0xd, 0x81, 0xb0, 0x22,
    0xc, 0x61, 0xfc, 0x60, 0x8c, 0x19, 0x1, 0x60,
    0x30,

    /* U+0042 "B" */
    0xfe, 0x61, 0xb0, 0xd8, 0x6c, 0x67, 0xe3, 0xd,
    0x83, 0xc1, 0xe0, 0xf0, 0xdf, 0xc0,

    /* U+0043 "C" */
    0x1f, 0xc, 0x36, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0, 0x18, 0x3, 0xc, 0x7c,

    /* U+0044 "D" */
    0xfe, 0x30, 0xcc, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x6c, 0x33, 0xf8,

    /* U+0045 "E" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff,

    /* U+0046 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0047 "G" */
    0x1f, 0xc, 0x76, 0x3, 0x0, 0xc0, 0x30, 0xfc,
    0xf, 0x3, 0xc0, 0xd8, 0x33, 0x1c, 0x7c,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6,
    0x8f, 0x1b, 0xe0,

    /* U+004B "K" */
    0xc1, 0xb0, 0xcc, 0x63, 0x30, 0xd8, 0x3e, 0xe,
    0xc3, 0x18, 0xc6, 0x30, 0xcc, 0x1b, 0x6,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xff,

    /* U+004D "M" */
    0xc0, 0x3e, 0x7, 0xe0, 0x7f, 0xf, 0xd1, 0xbd,
    0x9b, 0xcf, 0x3c, 0x63, 0xc6, 0x3c, 0x3, 0xc0,
    0x3c, 0x3,

    /* U+004E "N" */
    0xc0, 0xf8, 0x3f, 0xf, 0xc3, 0xd8, 0xf3, 0x3c,
    0xcf, 0x1b, 0xc3, 0xf0, 0xfc, 0x1f, 0x3,

    /* U+004F "O" */
    0x1f, 0x6, 0x31, 0x83, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x6c, 0x18, 0xc6, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfe, 0x61, 0xb0, 0x78, 0x3c, 0x1e, 0x1b, 0xf9,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0x0,

    /* U+0051 "Q" */
    0x1f, 0x6, 0x31, 0x83, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0x6c, 0x78, 0xc7, 0xf,
    0xe0, 0x6,

    /* U+0052 "R" */
    0xfc, 0x63, 0x30, 0xd8, 0x6c, 0x36, 0x33, 0xf1,
    0x98, 0xc4, 0x63, 0x30, 0xd8, 0x60,

    /* U+0053 "S" */
    0x3e, 0x31, 0xf0, 0x58, 0xe, 0x3, 0xe0, 0x7c,
    0x7, 0x1, 0x80, 0xf8, 0xc7, 0xc0,

    /* U+0054 "T" */
    0xff, 0x86, 0x3, 0x1, 0x80, 0xc0, 0x60, 0x30,
    0x18, 0xc, 0x6, 0x3, 0x1, 0x80,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xc0, 0x68, 0x19, 0x83, 0x30, 0x43, 0x18, 0x63,
    0x4, 0x40, 0xd8, 0x1b, 0x1, 0x40, 0x38, 0x6,
    0x0,

    /* U+0057 "W" */
    0xc1, 0x82, 0x41, 0x82, 0x63, 0x86, 0x63, 0xc6,
    0x62, 0x44, 0x26, 0x4c, 0x36, 0x6c, 0x34, 0x6c,
    0x14, 0x28, 0x1c, 0x38, 0x1c, 0x38, 0x18, 0x10,

    /* U+0058 "X" */
    0x60, 0xc8, 0x63, 0x10, 0x6c, 0xe, 0x3, 0x0,
    0xe0, 0x68, 0x13, 0xc, 0x66, 0x19, 0x83,

    /* U+0059 "Y" */
    0xc0, 0xd8, 0x66, 0x18, 0xcc, 0x33, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+005A "Z" */
    0xff, 0x1, 0x81, 0x80, 0x80, 0xc0, 0xc0, 0x60,
    0x60, 0x20, 0x30, 0x30, 0x1f, 0xf0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xf0,

    /* U+005C "\\" */
    0xc2, 0x10, 0xc2, 0x10, 0xc6, 0x10, 0xc6, 0x10,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,

    /* U+005E "^" */
    0x10, 0x70, 0xa3, 0x24, 0x60,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x4c, 0x80,

    /* U+0061 "a" */
    0x3c, 0xdc, 0x18, 0x37, 0xfc, 0xf1, 0xe7, 0x76,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xe6, 0xdc,

    /* U+0063 "c" */
    0x3e, 0x63, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0x63,
    0x3e,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3b, 0x67, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0x67, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x63,
    0x3e,

    /* U+0066 "f" */
    0x3b, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0067 "g" */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x3b, 0x3, 0x66, 0x3c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xee, 0xf8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x30,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xf0, 0xf8,
    0xcc, 0xcc, 0xc6, 0xc6,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xdb, 0x70,

    /* U+006D "m" */
    0xdd, 0xee, 0xf7, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xdd, 0xdf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6,
    0xdc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x3b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7d, 0x8f, 0x7, 0x87, 0xc3, 0xc1, 0xe3, 0x7c,

    /* U+0074 "t" */
    0x63, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0x70,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xf7, 0x76,

    /* U+0076 "v" */
    0xc1, 0x43, 0x62, 0x66, 0x26, 0x34, 0x3c, 0x1c,
    0x18,

    /* U+0077 "w" */
    0xc3, 0x1a, 0x38, 0xd1, 0x44, 0xca, 0x62, 0xdb,
    0x16, 0x50, 0xe3, 0x87, 0x1c, 0x18, 0xc0,

    /* U+0078 "x" */
    0x63, 0x66, 0x34, 0x1c, 0x18, 0x3c, 0x34, 0x66,
    0xc3,

    /* U+0079 "y" */
    0xc1, 0x21, 0x98, 0xcc, 0xc2, 0x61, 0xa0, 0x70,
    0x38, 0x18, 0xc, 0x4, 0x6, 0x0,

    /* U+007A "z" */
    0xfe, 0x1c, 0x30, 0xc3, 0x6, 0x18, 0x60, 0xfe,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x1b, 0xc, 0x31, 0x8c, 0x63,
    0xc,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xe0, 0xc3, 0xc, 0x30, 0xc0, 0xc4, 0x30, 0xc3,
    0xc, 0x33, 0x80,

    /* U+007E "~" */
    0xe7, 0x38,

    /* U+007F "" */
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 74, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 71, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 91, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 6, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 150, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 36, .adv_w = 214, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 185, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 50, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 74, .adv_w = 82, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 81, .adv_w = 82, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 88, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 92, .adv_w = 158, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 99, .adv_w = 69, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 101, .adv_w = 118, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 102, .adv_w = 66, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 105, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 164, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 108, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 153, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 157, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 66, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 69, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 236, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 246, .adv_w = 158, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 250, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 260, .adv_w = 129, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 214, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 175, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 174, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 182, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 193, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 191, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 187, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 65, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 127, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 172, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 147, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 228, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 190, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 477, .adv_w = 203, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 163, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 203, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 526, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 183, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 175, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 253, .box_w = 16, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 169, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 166, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 156, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 667, .adv_w = 91, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 675, .adv_w = 89, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 91, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 691, .adv_w = 116, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 696, .adv_w = 118, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 697, .adv_w = 69, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 699, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 719, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 93, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 769, .adv_w = 151, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 66, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 791, .adv_w = 135, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 66, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 228, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 150, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 851, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 863, .adv_w = 100, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 124, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 95, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 209, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 926, .adv_w = 138, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 940, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 948, .adv_w = 92, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 957, .adv_w = 60, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 961, .adv_w = 92, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 972, .adv_w = 138, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 974, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0}
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
    0
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
    0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -23, 0, -15, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, -8, -6, -26, -8, -26, -16,
    0, -28, 0, -5, -3, -1, 0, -6,
    0, 0, -9, 0, -11, -8, 0, 0,
    0, 0, 0, 0, 0, -8, -24, 0,
    0, -11, -5, -5, -7, -2, -26, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, 0, 0, 0, -12, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -18, 0, -13, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -8, 0, 0, 0, 0, -7,
    -5, 0, 0, 0, -5, 0, 0, 0,
    -7, 0, -7, 0, -9, 0, -7, -4,
    0, -13, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, -4, 0, 0,
    -6, -8, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, -3, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, -7, 0,
    -5, 0, 0, 0, -7, 0, -5, -8,
    0, 0, 0, 0, -7, 0, -10, 0,
    0, -10, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, 0, 0, -7, 0,
    0, 0, 0, 0, -5, 0, 0, -10,
    0, 0, 0, 0, 0, 0, -6, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -18, 0, -5, 0, 0, 0, -15, 0,
    0, 0, 0, 0, -14, 0, -3, -17,
    0, 0, 0, 0, -25, 0, -20, 0,
    -5, -27, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, 0, -8, -5,
    5, 0, -35, -7, -23, -5, 0, 0,
    0, -18, 0, -18, 2, -8, 0, 3,
    -25, 0, -28, 0, 0, 0, 0, 0,
    0, 0, 0, -21, -20, -7, 0, 0,
    -11, -15, 0, -10, 0, 0, -10, -9,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -6, -5,
    0, 0, 0, 0, -6, 0, -5, 0,
    0, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, -27, 0, -13, 0, 0, 0,
    0, -8, 0, -7, 0, -5, 0, 0,
    -18, 0, -22, 0, 0, 0, -3, 0,
    -12, -6, 0, -10, -7, 3, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -14, -5, -9, 3, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -24, -3, 0, -12, 0, -7, -16, 0,
    0, 0, 0, 0, 0, 0, -18, -20,
    0, -9, 0, 0, -24, -4, -26, -18,
    0, -26, 0, 0, -4, -3, 0, -2,
    0, 0, -8, -4, -13, -10, 0, 0,
    -8, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -5, 0, -2, 0, -6, 0, -10, -5,
    -5, -10, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -1, -2,
    0, 0, 0, -11, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, -1, 0, 0, 0,
    -6, -9, -3, -3, -6, 0, 0, 0,
    0, 0, 0, 0, -5, -5, -3, 0,
    -5, 0, -10, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -9, 0, -15, 0, -8, 0, -10, -4,
    -12, -13, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -4, 0, 0,
    5, -7, -18, 0, 0, 0, 0, 0,
    0, -7, 0, -8, 0, 0, 0, 0,
    -16, 0, -40, -3, 0, 0, 0, 0,
    -5, 0, 0, -13, -8, 0, 0, 0,
    -5, -4, 0, -5, -3, -3, -9, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -6, 0, 0, 0, -8, 0, -10, -4,
    -6, -12, -3, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -7, -8, -5, 0,
    0, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 4, -24, 0, -12, -8, 0,
    0, -7, 0, 0, 0, 0, -13, -9,
    0, -15, -8, -6, 0, -13, 0, 0,
    0, 0, 0, -8, -14, -8, 0, -6,
    -2, -3, -13, -13, -19, -16, 3, 0,
    -24, 0, 6, -23, 0, 0, -19, 0,
    0, 0, 0, 0, -6, 0, -29, -24,
    0, -10, 0, 0, -40, -7, -36, -22,
    0, -45, 0, 0, -5, -5, 0, 0,
    0, 0, -11, -5, -21, -13, 0, 0,
    0, -10, -25, 0, 0, 0, 0, -3,
    0, -8, 0, 0, 0, 0, 0, 0,
    -20, 0, -46, 0, -5, 0, -7, -5,
    -9, -9, -5, -9, -7, 5, 0, 0,
    0, 0, 5, -1, 7, 6, 1, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, -8, 0, -6, -6,
    -11, -13, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -7, 0, -5, 0, -5, -3,
    0, -7, 0, -4, -5, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -3, 1,
    -3, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -5, -3, -4,
    5, -17, -28, -20, 0, -9, 0, 0,
    0, -26, 0, -20, 0, -6, 0, 0,
    -24, -8, -37, -4, 0, 0, -5, 0,
    -8, 0, 0, -30, -30, -10, 0, 0,
    -22, -28, -6, -19, -27, -25, -27, -23,
    0, 0, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -9, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -18, -34, -11, 0, -7, 0, 0,
    0, -17, -5, -14, 0, -5, 0, 0,
    -26, -10, -40, -1, 0, 0, 0, 0,
    0, 0, 0, -23, -20, -4, 0, 0,
    -13, -17, -3, -12, -8, -8, -10, -8,
    0, -10, -22, -7, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -18, -4, -27, 2, 0, 0, 0, 0,
    0, 0, 0, -17, -14, -3, 0, 0,
    -9, -12, 0, -11, -3, -5, -8, -6,
    0, -8, 2, -22, 0, 0, -8, 0,
    -3, -5, -7, -6, 0, 0, -12, -6,
    0, -12, -3, -3, -8, -4, 0, 0,
    0, 0, 0, -5, -9, -6, 0, -2,
    -1, -8, -10, -12, -15, -16, 0, 0,
    0, -20, -31, -17, 0, -13, -1, -5,
    -3, -27, 0, -23, 0, -10, -5, 0,
    -26, -13, -44, -6, 0, 0, 0, 0,
    0, 0, 0, -28, -28, -10, 0, 0,
    -20, -24, -8, -22, -12, -12, -14, -16,
    0, -10, 0, -13, 0, 0, 0, 0,
    0, -10, 0, 0, 0, 0, 0, 0,
    0, -13, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, -7, -8, -11, -10, 0, 0,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -12, 0, -4, -13,
    0, 0, 0, 0, -27, 0, -20, -15,
    0, -24, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -4, 0, 0,
    -10, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -14, 0, -7, -18,
    -4, 0, 0, 0, -30, 0, -20, -14,
    -9, -28, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -3, -7, -2,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, 0, 0, 0, -28, 0, -15, -9,
    -6, -28, 0, -3, -3, 0, -3, -2,
    0, 0, 0, 0, -3, 0, -6, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, 0, -13,
    0, 0, 0, 0, -26, 0, -16, -11,
    -10, -22, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -1, -5, 0,
    8, -7, -17, 0, 0, 0, 0, 0,
    0, -11, 0, 0, 5, 0, 5, 0,
    -15, 0, -18, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -4, 0, 0, 0,
    0, -4, 2, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, 0, 0, -7,
    0, 0, 0, 0, -21, 0, -13, -10,
    -3, -20, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, 0, -5, -12,
    0, 0, 0, 0, -30, 0, -22, -16,
    -5, -27, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -2, -2, 0,
    -6, -4, 3, -8, 0, 0, 0, 0,
    0, -8, 0, -7, 0, -7, -2, -5,
    0, -5, 0, 0, -25, -3, -12, -6,
    0, -20, 0, -3, -7, 0, 0, -1,
    0, -3, -3, -4, 0, 0, 0, 0,
    0, -3, 5, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, 0,
    2, 0, 0, 2, -3, -2, 0, 0,
    0, -12, -28, 0, 0, 0, 0, -5,
    -12, -13, 0, -7, 0, 0, 3, 0,
    0, 0, 0, 0, -23, 0, 0, 0,
    -11, -9, -13, -6, -4, 3, 0, 0,
    0, -3, 4, -5, 5, 5, 2, 0,
    -8, 0, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, -7, 0, 0, -9,
    0, 0, 0, 0, -27, 0, -15, -12,
    -7, -21, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 3, 0,
    0, 0, 0, 0, -5, 0, -5, 0,
    0, -13, 0, 0, -2, 2, 0, 0,
    0, -2, 0, -1, 0, 0, 0, 0,
    0, -10, -21, 0, 0, 0, 0, 0,
    0, -8, 0, -8, 0, 0, 0, 0,
    -13, 0, -23, 0, -27, 0, -8, -3,
    -15, -12, -13, -7, -4, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -5, -14, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -10, 0, -18, 0, -25, 0, -8, -5,
    -16, -12, -10, -5, -3, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -6, 0, 0, 0, 0,
    0, -10, 0, -8, -7, -5, 0, 0,
    0, -3, 0, 0, -27, 0, -10, -8,
    2, -14, 0, -4, -7, 0, 0, -3,
    0, -6, 0, -3, 0, 0, 0, 0,
    0, -7, 0, -4, 0, 0, 0, 0,
    0, -9, 0, -5, -5, 0, -2, 0,
    0, -7, 0, 0, -23, 0, -11, -7,
    0, -16, 0, -1, -5, 0, 0, 0,
    0, -2, 0, -2, 0, 0, 0, 0
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
    .cmap_num = 1,
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
const lv_font_t MiSans_Medium_16px = {
#else
lv_font_t MiSans_Medium_16px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if MISANS_MEDIUM_16PX*/

