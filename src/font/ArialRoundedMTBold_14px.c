/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font Arial Rounded MT Bold Regular.ttf --range 32-127 --format lvgl -o ArialRoundedMTBold_14px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef ARIALROUNDEDMTBOLD_14PX
#define ARIALROUNDEDMTBOLD_14PX 1
#endif

#if ARIALROUNDEDMTBOLD_14PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf8, 0x3c,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x12, 0x32, 0x36, 0xff, 0x26, 0x24, 0x64, 0xff,
    0x6c, 0x4c, 0x48,

    /* U+0024 "$" */
    0x8, 0x8, 0x3e, 0x6b, 0x6b, 0x78, 0x3e, 0xf,
    0x4b, 0x6b, 0x6b, 0x3e, 0x8, 0x8, 0x8,

    /* U+0025 "%" */
    0x70, 0x8d, 0x88, 0xd9, 0xd, 0x90, 0x72, 0x0,
    0x6e, 0x5, 0xb0, 0x9b, 0x9, 0xb1, 0x1b, 0x10,
    0xe0,

    /* U+0026 "&" */
    0x3c, 0x19, 0x86, 0x61, 0xf8, 0x3c, 0x1e, 0x4f,
    0xd3, 0x3c, 0xc7, 0x39, 0xe3, 0xd8,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x32, 0x64, 0xcc, 0xcc, 0xcc, 0x46, 0x23,

    /* U+0029 ")" */
    0xc4, 0x62, 0x33, 0x33, 0x33, 0x26, 0x4c,

    /* U+002A "*" */
    0x21, 0x3a, 0xe5, 0x2c,

    /* U+002B "+" */
    0x30, 0x63, 0xff, 0xf3, 0x6, 0xc, 0x0,

    /* U+002C "," */
    0xf6,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x22, 0x26, 0x64, 0x44, 0xcc, 0x80,

    /* U+0030 "0" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0031 "1" */
    0x18, 0xdf, 0xf1, 0x8c, 0x63, 0x18, 0xc6,

    /* U+0032 "2" */
    0x3d, 0x8b, 0x1c, 0x30, 0xe3, 0x8f, 0x3c, 0x71,
    0xc3, 0xf8,

    /* U+0033 "3" */
    0x3c, 0xcd, 0x1a, 0x30, 0x47, 0x81, 0xa3, 0x46,
    0xdc, 0xe0,

    /* U+0034 "4" */
    0x6, 0xe, 0xe, 0x16, 0x36, 0x66, 0x46, 0xff,
    0x6, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x81, 0x6, 0xf, 0xd9, 0x81, 0x83, 0xc7,
    0x99, 0xe0,

    /* U+0036 "6" */
    0x38, 0xcb, 0x1e, 0xf, 0xdd, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0037 "7" */
    0xfe, 0x1c, 0x30, 0xc1, 0x86, 0xc, 0x18, 0x30,
    0xe0, 0x80,

    /* U+0038 "8" */
    0x7d, 0xdf, 0x1e, 0x3c, 0xe7, 0x31, 0xe3, 0xc7,
    0x8d, 0xf0,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7d, 0xdf, 0x83, 0xc6,
    0x98, 0xe0,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0x60,

    /* U+003C "<" */
    0x6, 0x3d, 0xe6, 0xf, 0x7, 0xc3, 0x81,

    /* U+003D "=" */
    0xff, 0xfc, 0x7, 0xff, 0xe0,

    /* U+003E ">" */
    0xc1, 0xe0, 0xf0, 0x71, 0xff, 0x38, 0x40,

    /* U+003F "?" */
    0x3c, 0xcd, 0x1a, 0x30, 0xe3, 0x86, 0xc, 0x0,
    0x30, 0x60,

    /* U+0040 "@" */
    0xf, 0xc0, 0xc1, 0xc, 0x4, 0xdf, 0x9f, 0x9c,
    0xec, 0x67, 0xc3, 0x3e, 0x39, 0xf1, 0x97, 0x9d,
    0x9f, 0xf0, 0xe0, 0x13, 0x83, 0x7, 0xe0,

    /* U+0041 "A" */
    0x18, 0xe, 0x7, 0x6, 0xc3, 0x61, 0xb1, 0x8c,
    0xfe, 0xc1, 0xe0, 0xf0, 0x60,

    /* U+0042 "B" */
    0xfe, 0xc7, 0xc3, 0xc3, 0xc6, 0xfc, 0xc3, 0xc3,
    0xc3, 0xc3, 0xfe,

    /* U+0043 "C" */
    0x1e, 0x31, 0x98, 0x78, 0x1c, 0x6, 0x3, 0x7,
    0x83, 0x63, 0xbf, 0x87, 0x80,

    /* U+0044 "D" */
    0xfe, 0x61, 0xb0, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc3, 0x61, 0xbf, 0x80,

    /* U+0045 "E" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xff,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x1f, 0x1c, 0x66, 0xf, 0x0, 0xc0, 0x31, 0xfc,
    0xf, 0x3, 0x60, 0xdc, 0x71, 0xf0,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xd1, 0xe3, 0x66,
    0xfc, 0xf0,

    /* U+004B "K" */
    0xc3, 0x63, 0xb3, 0x9b, 0x8f, 0x87, 0xe3, 0xb1,
    0x8c, 0xc7, 0x61, 0xb0, 0x40,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0xff, 0xf8,

    /* U+004D "M" */
    0xe1, 0xfc, 0xff, 0x3f, 0xcf, 0xd2, 0xf7, 0xbd,
    0xef, 0x7b, 0xde, 0xf3, 0x3c, 0xcc,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xd3, 0xdb, 0xcb, 0xcf,
    0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0x1e, 0x18, 0x66, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x87, 0x61, 0x9f, 0xe1, 0xe0,

    /* U+0050 "P" */
    0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1e, 0xc, 0x31, 0x86, 0x60, 0x6c, 0xd, 0x81,
    0xb0, 0x37, 0x6e, 0x63, 0x8f, 0xf0, 0x7b, 0x0,
    0x20,

    /* U+0052 "R" */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc7, 0xfc, 0xcc, 0xc6,
    0xc7, 0xc3, 0xc3,

    /* U+0053 "S" */
    0x3c, 0xc6, 0xc3, 0xe0, 0xfc, 0x7e, 0x1f, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0054 "T" */
    0xff, 0xff, 0xc6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x0,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe7, 0x7e, 0x3c,

    /* U+0056 "V" */
    0xc1, 0xe0, 0xf8, 0xcc, 0x66, 0x33, 0x30, 0xd8,
    0x6c, 0x3c, 0xe, 0x6, 0x0,

    /* U+0057 "W" */
    0xc7, 0x1e, 0x38, 0xf1, 0xc6, 0xca, 0x66, 0xdb,
    0x36, 0xd9, 0xb6, 0xcf, 0x1e, 0x38, 0xe1, 0xc7,
    0xc, 0x18,

    /* U+0058 "X" */
    0x63, 0x63, 0x36, 0x36, 0x1c, 0x1c, 0x3c, 0x36,
    0x66, 0xe3, 0xc3,

    /* U+0059 "Y" */
    0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x1c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0x3, 0x81, 0xc1, 0xc1, 0xc0, 0xc0, 0xe0,
    0xe0, 0x60, 0x60, 0x3f, 0xe0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0x8c, 0xc4, 0x44, 0x66, 0x22, 0x20,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x30, 0xe7, 0x9a, 0xcf, 0x30,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xd0,

    /* U+0061 "a" */
    0x7d, 0x8d, 0x19, 0xfe, 0x78, 0xf3, 0xbb,

    /* U+0062 "b" */
    0xc1, 0x83, 0x7, 0xee, 0xd8, 0xf1, 0xe3, 0xc7,
    0xdb, 0xf0,

    /* U+0063 "c" */
    0x3c, 0xcf, 0xe, 0xc, 0x18, 0x59, 0x9e,

    /* U+0064 "d" */
    0x6, 0xc, 0x1b, 0xfe, 0xf8, 0xf1, 0xe3, 0xc6,
    0xdd, 0xf8,

    /* U+0065 "e" */
    0x3c, 0xcf, 0x1f, 0xfc, 0x18, 0x59, 0x9e,

    /* U+0066 "f" */
    0x39, 0x86, 0x3e, 0x61, 0x86, 0x18, 0x61, 0x86,
    0x0,

    /* U+0067 "g" */
    0x7f, 0xdf, 0x1e, 0x3c, 0x78, 0xdb, 0xbf, 0x87,
    0x8d, 0xf0,

    /* U+0068 "h" */
    0xc1, 0x83, 0x7, 0xee, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x18,

    /* U+0069 "i" */
    0xf3, 0xff, 0xfc,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0xfe,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0x6d, 0xdb, 0x3e, 0x7c, 0xcd,
    0x9b, 0x10,

    /* U+006C "l" */
    0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xfb, 0xb3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c,
    0xcf, 0x33,

    /* U+006E "n" */
    0xfd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,

    /* U+006F "o" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0x1c,

    /* U+0070 "p" */
    0xfd, 0xdb, 0x1e, 0x3c, 0x78, 0xfb, 0x7e, 0xc1,
    0x83, 0x0,

    /* U+0071 "q" */
    0x7e, 0xdf, 0x1e, 0x3c, 0x78, 0xdb, 0xbf, 0x6,
    0xc, 0x18,

    /* U+0072 "r" */
    0xfe, 0x31, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0x7b, 0x3c, 0x3e, 0x3e, 0x3c, 0xde,

    /* U+0074 "t" */
    0x63, 0x19, 0xe6, 0x31, 0x8c, 0x63, 0xe,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xbf,

    /* U+0076 "v" */
    0xc2, 0x8d, 0x9b, 0x22, 0xc7, 0x8e, 0xc,

    /* U+0077 "w" */
    0xc4, 0x79, 0xcf, 0x39, 0xa5, 0x67, 0xbc, 0xf7,
    0x8c, 0x61, 0x8c,

    /* U+0078 "x" */
    0xc7, 0xd9, 0xb1, 0xc3, 0x8d, 0xbb, 0xe3,

    /* U+0079 "y" */
    0xc3, 0x8d, 0x9b, 0x26, 0xc5, 0xe, 0x1c, 0x10,
    0x63, 0x80,

    /* U+007A "z" */
    0xfe, 0x1c, 0x71, 0xc3, 0x8e, 0x38, 0x7f,

    /* U+007B "{" */
    0x19, 0xcc, 0x63, 0x19, 0x8c, 0x31, 0x8c, 0x63,
    0x8c,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0x61, 0xc3, 0xc, 0x30, 0xc1, 0x86, 0x30, 0xc3,
    0xc, 0x71, 0x80,

    /* U+007E "~" */
    0xf3, 0xfe, 0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 75, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 107, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 124, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 133, .box_w = 8, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 33, .adv_w = 191, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 170, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 54, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 65, .adv_w = 79, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 72, .adv_w = 79, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 79, .adv_w = 98, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 83, .adv_w = 131, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 90, .adv_w = 70, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 75, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 92, .adv_w = 70, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 63, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 133, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 133, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 70, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 70, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 202, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 209, .adv_w = 131, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 214, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 221, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 219, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 254, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 177, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 170, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 70, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 170, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 177, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 177, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 453, .adv_w = 161, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 464, .adv_w = 149, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 140, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 170, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 210, .box_w = 13, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 135, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 140, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 552, .adv_w = 145, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 79, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 572, .adv_w = 63, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 79, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 585, .adv_w = 131, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 590, .adv_w = 112, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 591, .adv_w = 75, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 592, .adv_w = 133, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 133, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 133, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 75, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 652, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 61, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 61, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 672, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 61, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 198, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 719, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 729, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 121, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 79, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 747, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 121, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 182, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 789, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 86, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 805, .adv_w = 63, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 809, .adv_w = 86, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 820, .adv_w = 131, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    9, 43,
    9, 72,
    9, 75,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 58,
    34, 87,
    34, 88,
    35, 13,
    35, 15,
    35, 34,
    35, 54,
    36, 13,
    36, 15,
    37, 13,
    37, 15,
    37, 34,
    37, 55,
    37, 56,
    37, 58,
    39, 13,
    39, 15,
    39, 34,
    39, 66,
    39, 70,
    39, 74,
    39, 77,
    39, 80,
    39, 83,
    40, 13,
    40, 15,
    40, 34,
    40, 40,
    43, 13,
    43, 15,
    43, 27,
    43, 28,
    43, 34,
    44, 10,
    44, 36,
    44, 40,
    44, 48,
    44, 66,
    44, 70,
    44, 80,
    44, 86,
    44, 87,
    44, 88,
    44, 90,
    45, 34,
    45, 36,
    45, 40,
    45, 48,
    45, 52,
    45, 53,
    45, 54,
    45, 55,
    45, 56,
    45, 58,
    45, 88,
    45, 90,
    47, 13,
    47, 15,
    47, 34,
    48, 13,
    48, 15,
    48, 34,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    49, 13,
    49, 15,
    49, 34,
    49, 66,
    49, 70,
    49, 80,
    50, 53,
    50, 55,
    50, 56,
    50, 58,
    50, 71,
    50, 72,
    50, 75,
    50, 81,
    50, 90,
    51, 10,
    51, 36,
    51, 40,
    51, 53,
    51, 54,
    51, 55,
    51, 58,
    51, 66,
    51, 70,
    51, 80,
    51, 86,
    51, 87,
    51, 88,
    51, 90,
    52, 13,
    52, 15,
    53, 13,
    53, 14,
    53, 15,
    53, 27,
    53, 28,
    53, 34,
    53, 36,
    53, 40,
    53, 48,
    53, 50,
    53, 66,
    53, 68,
    53, 70,
    53, 73,
    53, 74,
    53, 78,
    53, 80,
    53, 83,
    53, 84,
    53, 86,
    53, 88,
    53, 90,
    53, 91,
    54, 13,
    54, 15,
    54, 34,
    55, 13,
    55, 14,
    55, 15,
    55, 27,
    55, 28,
    55, 34,
    55, 36,
    55, 40,
    55, 48,
    55, 50,
    55, 66,
    55, 70,
    55, 74,
    55, 80,
    55, 83,
    55, 86,
    55, 90,
    56, 13,
    56, 14,
    56, 15,
    56, 27,
    56, 28,
    56, 48,
    56, 66,
    56, 69,
    56, 70,
    56, 80,
    56, 83,
    56, 86,
    56, 90,
    57, 36,
    57, 40,
    57, 48,
    58, 13,
    58, 14,
    58, 15,
    58, 27,
    58, 28,
    58, 34,
    58, 36,
    58, 40,
    58, 48,
    58, 52,
    58, 66,
    58, 69,
    58, 70,
    58, 74,
    58, 80,
    58, 81,
    58, 82,
    58, 86,
    58, 87,
    66, 67,
    66, 72,
    66, 81,
    66, 85,
    66, 87,
    66, 88,
    66, 90,
    67, 13,
    67, 15,
    67, 67,
    67, 77,
    67, 86,
    67, 87,
    67, 88,
    67, 90,
    68, 13,
    68, 15,
    68, 73,
    68, 76,
    68, 77,
    68, 90,
    69, 87,
    70, 13,
    70, 15,
    70, 67,
    70, 72,
    70, 81,
    70, 87,
    70, 88,
    70, 89,
    70, 90,
    70, 91,
    71, 1,
    71, 2,
    71, 10,
    71, 13,
    71, 15,
    71, 32,
    71, 66,
    71, 70,
    71, 71,
    71, 74,
    71, 77,
    71, 80,
    72, 13,
    72, 15,
    72, 66,
    72, 70,
    72, 72,
    72, 77,
    72, 80,
    72, 81,
    72, 83,
    76, 66,
    76, 68,
    76, 69,
    76, 70,
    76, 72,
    76, 74,
    76, 77,
    76, 80,
    76, 81,
    76, 82,
    76, 84,
    76, 86,
    76, 90,
    77, 88,
    78, 86,
    79, 86,
    79, 87,
    80, 13,
    80, 15,
    80, 87,
    80, 89,
    80, 90,
    81, 13,
    81, 15,
    81, 88,
    81, 90,
    81, 91,
    83, 13,
    83, 14,
    83, 15,
    83, 27,
    83, 28,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 72,
    83, 75,
    83, 76,
    83, 77,
    83, 80,
    83, 81,
    83, 82,
    83, 83,
    83, 84,
    83, 85,
    83, 86,
    83, 87,
    84, 13,
    84, 15,
    84, 88,
    87, 13,
    87, 15,
    87, 66,
    87, 68,
    87, 69,
    87, 70,
    87, 80,
    87, 82,
    88, 13,
    88, 15,
    88, 66,
    88, 68,
    88, 69,
    88, 70,
    88, 80,
    88, 82,
    89, 68,
    89, 69,
    89, 70,
    89, 80,
    90, 13,
    90, 15,
    90, 66,
    90, 68,
    90, 69,
    90, 70,
    90, 72,
    90, 80,
    90, 84,
    91, 68,
    91, 69,
    91, 70,
    91, 80
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -6, -3, 19, -6, -6, -3, -3, -20,
    -9, -11, -14, -6, -3, -9, -11, -9,
    -9, -9, -11, -14, -17, -9, -6, 6,
    -9, -25, -28, -17, -6, -9, -3, -3,
    -9, -9, -3, -6, -9, -3, -14, -17,
    -3, -3, -6, -9, -11, -11, -9, -3,
    -9, -9, -9, -14, -11, -6, -3, -11,
    -14, -11, -9, -28, -11, -25, -14, -28,
    -9, -9, -3, -6, -3, -9, -11, -9,
    -9, -6, 3, -6, -9, -31, -34, -20,
    -9, -9, -9, -9, -3, 6, -11, 8,
    6, 14, 6, 3, -6, -3, -3, -11,
    -6, -6, -9, -3, -6, -6, -6, -6,
    -3, -3, -6, -9, -25, -11, -28, -11,
    -11, -14, -6, -6, -3, -3, -11, -14,
    -14, -3, -3, -9, -14, -9, -14, -11,
    -9, -9, -6, -9, -11, -11, -25, -11,
    -28, -6, -6, -11, -3, -3, -3, -3,
    -11, -11, -3, -11, -9, -9, -9, -11,
    -3, -14, -6, -6, 3, -6, -6, -6,
    -6, -3, -9, -6, -6, -6, -3, -22,
    -11, -25, -11, -11, -14, -6, -6, -3,
    -6, -14, -14, -14, -3, -14, -11, -17,
    -11, -9, -3, -3, -3, -6, -6, -6,
    -3, -11, -14, -3, -3, -3, -3, -3,
    -3, -9, -11, -6, -9, -6, -6, -3,
    -9, -11, -3, -3, -3, -6, -3, -3,
    -6, -3, 25, 8, 8, -9, -11, 11,
    -3, -3, 8, 3, 3, -3, -6, -9,
    -6, -6, -6, -3, -6, -3, -3, -9,
    -6, -9, -9, -9, -6, -6, -9, -6,
    -9, -6, -6, -6, -3, -3, -3, -3,
    -9, -11, -3, -6, -3, -9, -11, -3,
    -3, -3, -25, -3, -28, -3, -3, -6,
    -6, -6, -6, -6, -3, -6, -3, -9,
    -3, -9, -3, -6, 3, -6, -3, -9,
    -11, -6, -14, -17, -3, -6, -3, -3,
    -3, -3, -17, -20, -3, -3, -3, -3,
    -3, -3, -6, -3, -3, -3, -17, -20,
    -3, -3, -3, -3, -3, -3, -3, -3,
    -3, -3, -3
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 323,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
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
const lv_font_t ArialRoundedMTBold_14px = {
#else
lv_font_t ArialRoundedMTBold_14px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
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



#endif /*#if ARIALROUNDEDMTBOLD_14PX*/

