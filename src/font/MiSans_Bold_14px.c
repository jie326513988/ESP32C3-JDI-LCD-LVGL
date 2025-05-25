/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --font MiSans-Bold.ttf --symbols ：周一二三四五六七日天℃° --range 32-127 --format lvgl -o MiSans_Bold_14px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef MISANS_BOLD_14PX
#define MISANS_BOLD_14PX 1
#endif

#if MISANS_BOLD_14PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xfc, 0xf0,

    /* U+0022 "\"" */
    0xfe, 0xf5, 0x20,

    /* U+0023 "#" */
    0x1b, 0x19, 0xbf, 0xff, 0xf3, 0x67, 0xff, 0xfe,
    0xcc, 0x64, 0x36, 0x0,

    /* U+0024 "$" */
    0x18, 0x3c, 0x7e, 0xff, 0xd8, 0xf8, 0x7e, 0x1f,
    0x1b, 0xdb, 0xfe, 0x3c, 0x18,

    /* U+0025 "%" */
    0x70, 0x67, 0xc6, 0x36, 0x71, 0xf3, 0x7, 0x30,
    0x3, 0x78, 0x37, 0xe3, 0x33, 0x31, 0xf9, 0x7,
    0x80,

    /* U+0026 "&" */
    0x3c, 0x1f, 0x86, 0x61, 0x80, 0x30, 0x3e, 0xec,
    0xf3, 0x1c, 0xff, 0x9f, 0x60,

    /* U+0027 "'" */
    0x6d, 0x20,

    /* U+0028 "(" */
    0x66, 0x6c, 0xcc, 0xcc, 0xc6, 0x66,

    /* U+0029 ")" */
    0x66, 0x63, 0x33, 0x33, 0x36, 0x66,

    /* U+002A "*" */
    0xe7, 0xff, 0xc0,

    /* U+002B "+" */
    0x18, 0x33, 0xff, 0xf1, 0x83, 0x6, 0x0,

    /* U+002C "," */
    0xf5, 0x80,

    /* U+002D "-" */
    0xff, 0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0xc, 0x61, 0x86, 0x38, 0xc3, 0x1c, 0x61, 0x80,

    /* U+0030 "0" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0x7e, 0x3c,

    /* U+0031 "1" */
    0x3f, 0xff, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0032 "2" */
    0x3d, 0xfd, 0x18, 0x30, 0xe3, 0x8e, 0x38, 0xff,
    0xfc,

    /* U+0033 "3" */
    0xff, 0xfc, 0x71, 0xc7, 0xc5, 0xc1, 0xe3, 0xfc,
    0xf0,

    /* U+0034 "4" */
    0xe, 0xf, 0x7, 0x86, 0xc7, 0x63, 0x33, 0xff,
    0xff, 0x6, 0x3, 0x0,

    /* U+0035 "5" */
    0xff, 0xff, 0x7, 0xef, 0xe8, 0xc1, 0xe3, 0xfc,
    0xf0,

    /* U+0036 "6" */
    0x1c, 0x38, 0x30, 0x7c, 0x7e, 0xe3, 0xc3, 0xe7,
    0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xfc, 0x30, 0x61, 0xc3, 0xe, 0x18, 0x70,
    0xc0,

    /* U+0038 "8" */
    0x3e, 0x7f, 0x63, 0x7e, 0x7e, 0xc3, 0xc3, 0xc3,
    0x7f, 0x3c,

    /* U+0039 "9" */
    0x3c, 0xfe, 0xc3, 0xc3, 0xff, 0x7e, 0xe, 0x1c,
    0x1c, 0x38,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0xf, 0x58,

    /* U+003C "<" */
    0x1, 0x7, 0x1f, 0x7c, 0xf0, 0xf0, 0x7c, 0x1f,
    0x7, 0x1,

    /* U+003D "=" */
    0xff, 0xfc, 0x7, 0xff, 0xe0,

    /* U+003E ">" */
    0x0, 0xc0, 0xf0, 0x3c, 0xf, 0xf, 0x7c, 0xf0,
    0xc0, 0x0,

    /* U+003F "?" */
    0x3c, 0xfd, 0x98, 0x30, 0xc3, 0x6, 0x0, 0x18,
    0x30,

    /* U+0040 "@" */
    0x1f, 0x83, 0xfe, 0x7f, 0xed, 0xfb, 0xd9, 0xbd,
    0x9b, 0xdf, 0xf7, 0xee, 0x3f, 0x81, 0xf0,

    /* U+0041 "A" */
    0xe, 0x1, 0xc0, 0x6c, 0xd, 0x83, 0x30, 0x7f,
    0xf, 0xe3, 0x6, 0x60, 0xdc, 0x1c,

    /* U+0042 "B" */
    0xfe, 0xff, 0xc3, 0xc3, 0xfe, 0xfe, 0xc3, 0xc3,
    0xff, 0xfe,

    /* U+0043 "C" */
    0x1e, 0x3f, 0xd8, 0xf8, 0xc, 0x6, 0x3, 0x0,
    0xc6, 0x7f, 0x8f, 0x0,

    /* U+0044 "D" */
    0xfc, 0x7f, 0xb0, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x86, 0xff, 0x7e, 0x0,

    /* U+0045 "E" */
    0xff, 0xff, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0, 0xc0,
    0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0x6, 0xf, 0xff, 0xf0, 0x60, 0xc1,
    0x80,

    /* U+0047 "G" */
    0x1e, 0x3f, 0xd8, 0x58, 0xc, 0x7e, 0x3f, 0x6,
    0xc3, 0x7f, 0x8f, 0x0,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x7f, 0xff, 0xfe, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xc0,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xb3, 0x7e,
    0x78,

    /* U+004B "K" */
    0xc3, 0xe3, 0xb3, 0x1b, 0xf, 0x87, 0xe3, 0x39,
    0x8e, 0xc7, 0x61, 0xc0,

    /* U+004C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xff, 0xff,

    /* U+004D "M" */
    0xc0, 0x7c, 0x1f, 0xc7, 0xf8, 0xff, 0xb7, 0xbe,
    0xf3, 0x9e, 0x23, 0xc0, 0x78, 0xc,

    /* U+004E "N" */
    0xc1, 0xf0, 0xfc, 0x7f, 0x3d, 0xde, 0xef, 0x3f,
    0x8f, 0xc3, 0xe0, 0xc0,

    /* U+004F "O" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xd, 0x86, 0x7f, 0x8f, 0x80,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xfe, 0xfc, 0xc0,
    0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1e, 0x1f, 0xe6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xd, 0x87, 0x7f, 0x87, 0xf0, 0x8,

    /* U+0052 "R" */
    0xfe, 0x7f, 0xb0, 0xd8, 0x6f, 0xf7, 0xf3, 0x39,
    0x8c, 0xc7, 0x61, 0x80,

    /* U+0053 "S" */
    0x3c, 0xfe, 0xc2, 0xc0, 0x78, 0x1e, 0x3, 0xc3,
    0xff, 0x7c,

    /* U+0054 "T" */
    0xff, 0xff, 0xc6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x0,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xc7, 0x7f, 0x1f, 0x0,

    /* U+0056 "V" */
    0xe0, 0xec, 0x19, 0xc7, 0x18, 0xc3, 0x18, 0x77,
    0x6, 0xc0, 0xf8, 0xe, 0x1, 0xc0,

    /* U+0057 "W" */
    0xe3, 0x87, 0x63, 0xc6, 0x63, 0xc6, 0x73, 0xce,
    0x76, 0xec, 0x36, 0x6c, 0x36, 0x7c, 0x3c, 0x78,
    0x1c, 0x38, 0x1c, 0x38,

    /* U+0058 "X" */
    0x71, 0xc6, 0x30, 0xee, 0xf, 0x80, 0xe0, 0x1c,
    0x7, 0xc1, 0xdc, 0x71, 0xcc, 0x38,

    /* U+0059 "Y" */
    0xe1, 0xdc, 0xe3, 0x30, 0xfc, 0x1e, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0,

    /* U+005A "Z" */
    0xff, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xe0, 0xe0,
    0xe0, 0xff, 0xff, 0xc0,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+005C "\\" */
    0xc1, 0x86, 0x18, 0x30, 0xc3, 0x6, 0x18, 0x60,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0xff,

    /* U+005E "^" */
    0x38, 0x71, 0xb6, 0x60,

    /* U+005F "_" */
    0xff, 0xfc,

    /* U+0060 "`" */
    0x4e, 0x30,

    /* U+0061 "a" */
    0x3d, 0xfd, 0x19, 0xff, 0xf8, 0xff, 0xbb,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xe7,
    0xfe, 0xdc,

    /* U+0063 "c" */
    0x3c, 0xff, 0x16, 0xc, 0x18, 0x9f, 0x9e,

    /* U+0064 "d" */
    0x3, 0x3, 0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7,
    0x7f, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x7e, 0x63, 0xff, 0x7f, 0x62, 0x7e, 0x3c,

    /* U+0066 "f" */
    0x3b, 0xd9, 0xff, 0xb1, 0x8c, 0x63, 0x18,

    /* U+0067 "g" */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b,
    0x43, 0x7e, 0x3c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x77, 0xfc, 0x78, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+0069 "i" */
    0xf3, 0xff, 0xfc,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0xfe,

    /* U+006B "k" */
    0xc0, 0xc0, 0xce, 0xdc, 0xd8, 0xf8, 0xfc, 0xdc,
    0xce, 0xc6,

    /* U+006C "l" */
    0xdb, 0x6d, 0xb6, 0xfc,

    /* U+006D "m" */
    0xdd, 0xef, 0xff, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63,

    /* U+006E "n" */
    0xdd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0070 "p" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xe7, 0xfe, 0xdc,
    0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b,
    0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0xfe, 0x30, 0xc3, 0xc, 0x30,

    /* U+0073 "s" */
    0x79, 0xfb, 0x27, 0x81, 0xc9, 0xbf, 0x3c,

    /* U+0074 "t" */
    0x61, 0x8f, 0xff, 0x61, 0x86, 0x18, 0x7c, 0xf0,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0xbb,

    /* U+0076 "v" */
    0xe3, 0xb1, 0x99, 0xce, 0xc3, 0x61, 0xf0, 0x70,
    0x38,

    /* U+0077 "w" */
    0xe7, 0x3b, 0x39, 0x99, 0xcc, 0xdb, 0x63, 0xde,
    0x1e, 0xf0, 0xe3, 0x87, 0x18,

    /* U+0078 "x" */
    0x63, 0x3b, 0xf, 0x83, 0x81, 0xc1, 0xf1, 0xdd,
    0xc6,

    /* U+0079 "y" */
    0xe3, 0xb1, 0x98, 0xce, 0xe3, 0x61, 0xf0, 0x70,
    0x38, 0x1c, 0xc, 0xe, 0x0,

    /* U+007A "z" */
    0xff, 0xfc, 0x71, 0xc3, 0xe, 0x3f, 0xff,

    /* U+007B "{" */
    0x1c, 0xf3, 0xc, 0x33, 0xcf, 0xc, 0x30, 0xc3,
    0xc7,

    /* U+007C "|" */
    0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xe3, 0xc3, 0xc, 0x30, 0xf3, 0xcc, 0x30, 0xcf,
    0x38,

    /* U+007E "~" */
    0x31, 0x3f, 0x93, 0x80,

    /* U+007F "" */
    0x0,

    /* U+00B0 "°" */
    0x76, 0xf7, 0xb7, 0x0,

    /* U+2103 "℃" */
    0x70, 0x79, 0xb3, 0xfe, 0x26, 0x3c, 0x5c, 0x27,
    0x30, 0x0, 0x60, 0x0, 0xc0, 0x1, 0xc0, 0x1,
    0xc6, 0x3, 0xfc, 0x1, 0xe0,

    /* U+4E00 "一" */
    0xff, 0xff, 0xff,

    /* U+4E03 "七" */
    0xc, 0x0, 0x60, 0x3, 0x0, 0x18, 0x60, 0xff,
    0x7f, 0xe3, 0xf0, 0x1, 0x80, 0xc, 0x20, 0x61,
    0x83, 0xc, 0x1f, 0xe0, 0x7e, 0x0,

    /* U+4E09 "三" */
    0x7f, 0xe7, 0xfe, 0x0, 0x0, 0x0, 0x7f, 0xe7,
    0xfe, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff,
    0xf0,

    /* U+4E8C "二" */
    0x7f, 0xe7, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0xff, 0xff,
    0xf0,

    /* U+4E94 "五" */
    0xff, 0xff, 0xff, 0xc, 0x1, 0x80, 0x7f, 0xc7,
    0xfc, 0x18, 0xc1, 0x8c, 0x30, 0xcf, 0xff, 0xff,
    0xf0,

    /* U+516D "六" */
    0xe, 0x0, 0x60, 0x6, 0xf, 0xff, 0xff, 0xf0,
    0x0, 0x19, 0x83, 0x9c, 0x30, 0xc7, 0x6, 0x60,
    0x7c, 0x3, 0x40, 0x20,

    /* U+5468 "周" */
    0x7f, 0xf6, 0x3, 0x62, 0x36, 0xfb, 0x62, 0x37,
    0xff, 0x60, 0x36, 0x3, 0x6f, 0xb6, 0x8b, 0x6f,
    0xbc, 0x3, 0xc0, 0xf0,

    /* U+56DB "四" */
    0xff, 0xff, 0xff, 0xdb, 0x3d, 0xb3, 0xdb, 0x3d,
    0xb3, 0xf3, 0xff, 0x1f, 0xc0, 0x3f, 0xff, 0xff,
    0xfc, 0x3,

    /* U+5929 "天" */
    0x7f, 0xe7, 0xfe, 0x6, 0x0, 0x60, 0x6, 0xf,
    0xff, 0xff, 0xf0, 0x60, 0xf, 0x1, 0xf8, 0x39,
    0xcf, 0xf, 0xc0, 0x30,

    /* U+65E5 "日" */
    0xff, 0xff, 0xfc, 0xf, 0x3, 0xc0, 0xff, 0xff,
    0xff, 0x3, 0xc0, 0xf0, 0x3f, 0xff, 0xff, 0xc0,
    0xc0,

    /* U+FF1A "：" */
    0xfc, 0x0, 0x3f
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 67, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 74, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 100, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 7, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 141, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 32, .adv_w = 204, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 176, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 52, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 64, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 70, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 76, .adv_w = 101, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 79, .adv_w = 146, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 86, .adv_w = 70, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 88, .adv_w = 109, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 90, .adv_w = 67, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 113, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 146, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 143, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 67, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 70, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 199, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 146, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 214, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 125, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 198, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 174, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 169, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 179, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 179, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 67, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 174, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 140, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 214, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 184, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 157, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 184, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 436, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 171, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 175, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 253, .box_w = 16, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 175, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 170, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 152, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 561, .adv_w = 90, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 575, .adv_w = 110, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 579, .adv_w = 107, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 581, .adv_w = 75, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 583, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 147, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 617, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 95, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 68, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 68, .box_w = 4, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 662, .adv_w = 142, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 69, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 212, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 143, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 714, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 725, .adv_w = 105, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 123, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 100, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 142, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 141, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 207, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 142, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 144, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 797, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 91, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 813, .adv_w = 60, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 816, .adv_w = 91, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 825, .adv_w = 142, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 829, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 98, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 834, .adv_w = 263, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 855, .adv_w = 224, .box_w = 12, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 858, .adv_w = 224, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 880, .adv_w = 224, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 224, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 224, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 931, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 951, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 971, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 989, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1009, .adv_w = 224, .box_w = 10, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1026, .adv_w = 224, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x2053, 0x4d50, 0x4d53, 0x4d59, 0x4ddc, 0x4de4, 0x50bd,
    0x53b8, 0x562b, 0x5879, 0x6535, 0xfe6a
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 96, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 65131, .glyph_id_start = 97,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 13, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
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
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -21, 0, -12, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, -9, -10, -28, -10, -28, -18,
    0, -29, 0, -6, -6, -4, 0, -5,
    0, 0, -11, 0, -16, -10, 0, 0,
    0, 0, 0, 0, 0, -5, -24, 0,
    0, -6, -4, -3, -5, 0, -21, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, 0, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -17, 0, -11, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, 0, 0, 0, -3,
    -6, 0, 0, 0, -2, 0, 0, 0,
    -8, 0, -6, 0, -6, 0, -8, -4,
    0, -12, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, -2, 0, 0,
    -4, -5, 0, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -4, 0,
    0, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, -4, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, -3, 0,
    -4, 0, 0, 0, -6, 0, -4, -7,
    0, 0, 0, 0, -7, 0, -9, 0,
    0, -9, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, -5, 0,
    0, 0, 0, 0, -4, 0, 0, -7,
    0, 0, 0, 0, 0, 0, -4, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -19, 0, -3, 0, 0, 0, -13, 0,
    0, 0, 0, 0, -8, 0, -2, -17,
    0, 0, 0, 0, -20, 0, -18, 0,
    -10, -25, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, -10, -4,
    5, 0, -28, -5, -17, -3, 0, 0,
    0, -16, 0, -14, 6, -6, 0, 4,
    -26, 0, -28, 0, 0, 0, 0, 0,
    0, 0, 0, -15, -13, -3, 0, 0,
    -7, -10, 0, -6, 0, 0, -5, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -5, -3,
    0, 0, 0, 0, -5, 0, -8, 0,
    0, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -6, 0,
    0, 0, -19, 0, -11, 0, 0, 0,
    0, -5, 0, -4, 0, -5, 0, 0,
    -16, 0, -22, 0, 0, 0, -3, 0,
    -14, -8, 0, -7, -5, 4, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -15, -2, -9, 2, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -26, -1, 0, -14, 0, -8, -17, 0,
    0, 0, 0, 0, 0, 0, -18, -20,
    0, -9, 0, 0, -19, -4, -26, -18,
    0, -30, 0, 0, -4, -6, 0, -4,
    0, 0, -12, -5, -17, -13, 0, 0,
    -7, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -5, 0, -3, 0, -5, 0, -10, -5,
    -5, -8, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -1, -2,
    0, 0, 0, -11, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -1, 0, 0, 0,
    -8, -12, -2, -4, -6, 0, 0, 0,
    0, 0, 0, 0, -4, -4, -2, 0,
    -5, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    -9, 0, -11, 0, -7, 0, -11, -4,
    -15, -14, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -4, 0, 0,
    3, -5, -14, 0, 0, 0, 0, 0,
    0, -5, 0, -4, 0, 0, 0, 0,
    -14, 0, -36, -3, 0, 0, 0, 0,
    -4, 0, 0, -9, -4, 0, 0, 0,
    -4, -3, 0, -4, -2, -2, -5, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -5, 0, 0, 0, -7, 0, -9, -4,
    -9, -11, -3, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -6, -7, -4, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -10, 1, -24, 0, -13, -9, 0,
    0, -7, 0, 0, 0, 0, -16, -11,
    0, -17, -11, -9, 0, -11, 0, 0,
    0, 0, 0, -9, -12, -10, 0, -7,
    -3, -7, -11, -11, -21, -14, -5, 0,
    -23, 0, 5, -22, 0, 0, -23, 0,
    0, 0, 0, 0, -4, 0, -25, -24,
    0, -9, 0, 0, -35, -6, -35, -22,
    0, -46, 0, 0, -4, -5, 0, 0,
    0, 0, -14, -3, -22, -11, 0, 0,
    0, -9, -21, 0, 0, 0, 0, -4,
    0, -9, 0, 0, 0, 0, 0, 0,
    -20, 0, -44, 0, -4, 0, -8, -6,
    -16, -12, -4, -9, -5, 3, 0, 0,
    0, -2, 3, -1, 1, 1, -3, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, -7, 0, -5, -5,
    -10, -11, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -7, 0, -4, 0, -5, -3,
    0, -10, 0, -3, -4, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -6, 0,
    -6, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -4, -2, -3,
    5, -14, -25, -18, 0, -6, 0, 0,
    0, -22, 0, -18, 0, -5, 0, 0,
    -19, -9, -39, -4, 0, 0, -4, 0,
    -9, 0, 0, -23, -25, -9, 0, 0,
    -15, -22, -5, -10, -17, -19, -21, -15,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -9, 0, 0, 0, 0, 0,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -15, -30, -12, 0, -8, 0, 0,
    0, -17, -2, -13, 0, -8, 0, 0,
    -26, -11, -39, -4, 0, 0, 0, 0,
    0, 0, 0, -21, -21, -5, 0, 0,
    -12, -17, -4, -11, -9, -7, -11, -9,
    0, -9, -20, -8, 0, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -18, -4, -27, -1, 0, 0, 0, 0,
    0, 0, 0, -16, -13, -3, 0, 0,
    -8, -13, -2, -10, -2, -4, -9, -6,
    0, -10, 1, -23, 0, 0, -9, 0,
    -4, -8, -6, -10, 0, 0, -14, -8,
    0, -15, -9, -4, -9, -4, 0, 0,
    0, 0, 0, -7, -14, -10, 0, -2,
    -3, -9, -14, -11, -17, -18, 0, 0,
    0, -20, -33, -17, 0, -12, -3, -4,
    -4, -27, 0, -23, 0, -10, -7, -2,
    -30, -14, -36, -9, 0, 0, 0, 0,
    0, 0, 0, -27, -28, -11, 0, 0,
    -20, -24, -10, -20, -12, -12, -17, -16,
    0, -9, 0, -11, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -11, 0, 0, 0, -4, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, -6, -7, -9, -9, 0, 0,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, -4, -12,
    0, 0, 0, 0, -21, 0, -21, -12,
    0, -24, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -4, 0, 0,
    -9, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -11, 0, -6, -15,
    -4, 0, 0, 0, -25, 0, -21, -13,
    -14, -28, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -3, -10, -3,
    -4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -24, 0, -14, -9,
    -10, -26, 0, -3, -3, 0, -2, -2,
    0, 0, 0, 0, -7, 0, -8, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, 0, -13,
    0, 0, 0, 0, -22, 0, -17, -11,
    -13, -24, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -1, -9, 0,
    7, -4, -17, 0, 0, 0, 0, 0,
    0, -11, 0, 0, 5, 0, 4, 0,
    -15, 0, -14, 0, 0, 0, 0, 0,
    0, 0, 0, -6, -4, 0, 0, 0,
    0, -3, 2, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, -3,
    0, 0, 0, 0, -11, 0, -12, -9,
    -2, -20, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -4, -10,
    0, 0, 0, 0, -26, 0, -18, -13,
    -4, -30, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, -3, -2, 0,
    -7, -3, 2, -12, 0, 0, 0, 0,
    0, -9, 0, -10, 0, -8, -4, -2,
    0, -5, 0, 0, -21, -3, -11, -6,
    0, -18, 0, -3, -10, 0, 0, -2,
    0, -5, -4, -6, 0, 0, 0, 0,
    0, -1, 4, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, -2, 0, 0,
    2, 0, 0, 1, -4, -1, 0, 0,
    0, -11, -25, 0, 0, 0, 0, -3,
    -8, -13, 0, -6, 0, 0, 2, 0,
    0, 0, 0, 0, -20, 0, 0, 0,
    -14, -12, -11, -6, -4, 2, 0, 0,
    0, -3, 3, -6, 3, 4, -1, 0,
    -9, 0, 0, 0, 0, 0, -7, 0,
    0, 0, 0, 0, -7, 0, 0, -11,
    0, 0, 0, 0, -23, 0, -18, -13,
    -9, -25, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -3, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, -4, 0, -6, -2,
    0, -14, 0, 0, -2, 1, 0, 0,
    0, -2, 0, -1, 0, 0, 0, 0,
    0, -9, -19, 0, 0, 0, 0, 0,
    0, -11, 0, -8, 0, 0, 0, 0,
    -17, 0, -22, 0, -17, 0, -9, -2,
    -17, -12, -11, -8, -6, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -4, -16, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -13, 0, -14, 0, -19, 0, -7, -4,
    -18, -12, -9, -6, -3, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -8, 0, 0, 0, 0,
    0, -11, 0, -10, -3, -6, 0, 0,
    0, -2, 0, 0, -21, 0, -11, -9,
    -1, -17, 0, -4, -10, 0, 0, -2,
    0, -5, 0, -3, 0, 0, 0, 0,
    0, -3, 0, -2, 0, 0, 0, 0,
    0, -3, 0, -4, -2, 0, -1, 0,
    0, -3, 0, 0, -18, 0, -10, -6,
    0, -15, 0, 0, -5, 0, 0, 0,
    0, -3, 0, -2, 0, 0, 0, 0
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
const lv_font_t MiSans_Bold_14px = {
#else
lv_font_t MiSans_Bold_14px = {
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



#endif /*#if MISANS_BOLD_14PX*/

