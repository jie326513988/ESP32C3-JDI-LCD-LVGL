/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --no-compress --font MiSans-Bold.ttf --symbols ：℃° --range 32-127 --format lvgl -o MiSans_Bold_16px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef MISANS_BOLD_16PX
#define MISANS_BOLD_16PX 1
#endif

#if MISANS_BOLD_16PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xff, 0xe0, 0x7e,

    /* U+0022 "\"" */
    0xdb, 0x6d, 0xb6, 0xd8,

    /* U+0023 "#" */
    0xd, 0x81, 0x30, 0x66, 0x3f, 0xf7, 0xfe, 0x36,
    0x6, 0xc7, 0xfe, 0xff, 0xc6, 0x60, 0xcc, 0x1b,
    0x3, 0x60,

    /* U+0024 "$" */
    0x1c, 0xe, 0x1f, 0xdf, 0xff, 0xf7, 0xe3, 0xf0,
    0xfc, 0x3f, 0xf, 0xc7, 0xff, 0xff, 0xfb, 0xf8,
    0x70, 0x38,

    /* U+0025 "%" */
    0x78, 0x33, 0xf1, 0xcc, 0xc6, 0x33, 0x30, 0xfd,
    0xc1, 0xe6, 0x0, 0x30, 0x1, 0x9e, 0xe, 0xfc,
    0x33, 0x31, 0x8c, 0xce, 0x3f, 0x30, 0x78,

    /* U+0026 "&" */
    0x1e, 0x3, 0xf0, 0x73, 0x87, 0x10, 0x78, 0x3,
    0x80, 0x7c, 0xcf, 0xee, 0xe7, 0xce, 0x7c, 0xe3,
    0xc7, 0xfc, 0x3e, 0xe0,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x3b, 0x9c, 0xee, 0x73, 0x9c, 0xe7, 0x38, 0xe7,
    0x38, 0xe0,

    /* U+0029 ")" */
    0xe3, 0x9c, 0xe3, 0x9c, 0xe7, 0x39, 0xce, 0xe7,
    0x3b, 0x80,

    /* U+002A "*" */
    0x23, 0xaf, 0xbe, 0xe8, 0x80,

    /* U+002B "+" */
    0x1c, 0x1c, 0x1c, 0x1c, 0xff, 0xff, 0x1c, 0x1c,
    0x1c,

    /* U+002C "," */
    0xfc, 0xbd, 0x0,

    /* U+002D "-" */
    0xff, 0xfc,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0x1c, 0x61, 0x8e, 0x38, 0xc7, 0x1c, 0x61, 0x8e,
    0x38, 0xc0,

    /* U+0030 "0" */
    0x3e, 0x3f, 0x9d, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xdd, 0xcf, 0xe3, 0xe0,

    /* U+0031 "1" */
    0x3f, 0xff, 0xf7, 0x1c, 0x71, 0xc7, 0x1c, 0x71,
    0xc7, 0x1c,

    /* U+0032 "2" */
    0x3e, 0x3f, 0xb8, 0xe0, 0x70, 0x38, 0x3c, 0x1c,
    0x1e, 0x1e, 0x1e, 0x1e, 0x1f, 0xff, 0xf8,

    /* U+0033 "3" */
    0xff, 0xff, 0x1e, 0x3c, 0x30, 0x7e, 0x3e, 0x7,
    0x7, 0x47, 0xc7, 0xfe, 0x7c,

    /* U+0034 "4" */
    0xf, 0x7, 0xc1, 0xf0, 0xfc, 0x37, 0x1d, 0xc7,
    0x71, 0x9c, 0xff, 0xff, 0xf0, 0x70, 0x1c, 0x7,
    0x0,

    /* U+0035 "5" */
    0xff, 0x7f, 0xb8, 0x1c, 0xf, 0xe7, 0xf9, 0x9e,
    0x7, 0x3, 0xa1, 0xf9, 0xff, 0xe3, 0xe0,

    /* U+0036 "6" */
    0xc, 0xe, 0xe, 0x7, 0x7, 0xe3, 0xfb, 0xdf,
    0xc7, 0xe3, 0xf1, 0xfd, 0xef, 0xe3, 0xe0,

    /* U+0037 "7" */
    0xff, 0xff, 0xc1, 0xc0, 0xe0, 0xf0, 0x70, 0x38,
    0x38, 0x1c, 0x1c, 0xe, 0xf, 0x7, 0x0,

    /* U+0038 "8" */
    0x3e, 0x1f, 0xce, 0x3b, 0x8e, 0xe3, 0x9f, 0xc7,
    0xf1, 0xce, 0xe1, 0xf8, 0x7f, 0x3d, 0xfe, 0x3f,
    0x0,

    /* U+0039 "9" */
    0x3e, 0x3f, 0xb9, 0xfc, 0x7e, 0x3f, 0x3d, 0xfe,
    0x7e, 0xf, 0x7, 0x3, 0x83, 0x81, 0x80,

    /* U+003A ":" */
    0xfc, 0x0, 0x0, 0xfc,

    /* U+003B ";" */
    0xfc, 0x0, 0x0, 0xfc, 0xbd, 0x0,

    /* U+003C "<" */
    0x1, 0x81, 0xc3, 0xe7, 0xcf, 0x87, 0x3, 0xe0,
    0xfc, 0x1f, 0x83, 0xc0, 0x60,

    /* U+003D "=" */
    0xff, 0xff, 0x0, 0x0, 0xff, 0xff,

    /* U+003E ">" */
    0x80, 0x70, 0x3e, 0xf, 0xc1, 0xf0, 0x3c, 0x3e,
    0x7c, 0xf8, 0x70, 0x30, 0x0,

    /* U+003F "?" */
    0x3c, 0x7e, 0xe7, 0x47, 0x7, 0xe, 0x1c, 0x18,
    0x18, 0x18, 0x0, 0x1c, 0x1c,

    /* U+0040 "@" */
    0xf, 0x81, 0xff, 0x1c, 0x1c, 0xdf, 0xfc, 0xfd,
    0xec, 0x6f, 0x63, 0x7b, 0x1b, 0xdf, 0xf3, 0x7b,
    0x9e, 0x0, 0x7f, 0x80, 0xf8, 0x0,

    /* U+0041 "A" */
    0x7, 0x0, 0xf0, 0xf, 0x0, 0xf8, 0x1f, 0x81,
    0xdc, 0x39, 0xc3, 0x9c, 0x3f, 0xe7, 0xfe, 0x70,
    0x66, 0x7, 0xe0, 0x70,

    /* U+0042 "B" */
    0xfe, 0x3f, 0xee, 0x3b, 0x8e, 0xe3, 0xbf, 0xcf,
    0xfb, 0x8f, 0xe1, 0xf8, 0x7e, 0x1f, 0xfe, 0xff,
    0x0,

    /* U+0043 "C" */
    0xf, 0x87, 0xf9, 0xe3, 0xb8, 0xe, 0x1, 0xc0,
    0x38, 0x7, 0x0, 0xe0, 0xe, 0x9, 0xe3, 0x9f,
    0xe0, 0xf8,

    /* U+0044 "D" */
    0xff, 0x1f, 0xf3, 0x8f, 0x70, 0xee, 0xf, 0xc1,
    0xf8, 0x3f, 0x7, 0xe0, 0xfc, 0x3b, 0x8f, 0x7f,
    0xcf, 0xf0,

    /* U+0045 "E" */
    0xff, 0xff, 0xf8, 0x1c, 0xe, 0x7, 0xfb, 0xfd,
    0xc0, 0xe0, 0x70, 0x38, 0x1f, 0xff, 0xf8,

    /* U+0046 "F" */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0,

    /* U+0047 "G" */
    0xf, 0x87, 0xf9, 0xc7, 0x38, 0xe, 0x1, 0xc7,
    0xf8, 0xff, 0x7, 0xe0, 0xee, 0x1d, 0xc7, 0x9f,
    0xf1, 0xf8,

    /* U+0048 "H" */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0xf, 0xff,
    0xff, 0xff, 0x7, 0xe0, 0xfc, 0x1f, 0x83, 0xf0,
    0x7e, 0xe,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xff, 0xfe,

    /* U+004A "J" */
    0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7,
    0x7, 0x7, 0xe7, 0xfe, 0x7c,

    /* U+004B "K" */
    0xe1, 0xfc, 0x7b, 0x8e, 0x73, 0x8e, 0xe1, 0xfc,
    0x3f, 0x87, 0xb8, 0xe7, 0x9c, 0x73, 0x8f, 0x70,
    0xee, 0xe,

    /* U+004C "L" */
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x1f, 0xff, 0xf8,

    /* U+004D "M" */
    0xe0, 0x3f, 0x83, 0xfc, 0x1f, 0xf1, 0xff, 0x8f,
    0xfe, 0xff, 0xb6, 0xfd, 0xf7, 0xe7, 0x3f, 0x39,
    0xf8, 0xf, 0xc0, 0x7e, 0x3, 0x80,

    /* U+004E "N" */
    0xe0, 0xfe, 0x1f, 0xc3, 0xfc, 0x7f, 0xcf, 0xf9,
    0xfb, 0xbf, 0x3f, 0xe7, 0xfc, 0x7f, 0x87, 0xf0,
    0xfe, 0xe,

    /* U+004F "O" */
    0x1f, 0x83, 0xfc, 0x70, 0xef, 0xe, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7f, 0xe, 0x70,
    0xe3, 0xfc, 0x1f, 0x80,

    /* U+0050 "P" */
    0xff, 0x3f, 0xee, 0x3f, 0x87, 0xe1, 0xf8, 0x7e,
    0x3f, 0xfe, 0xff, 0x38, 0xe, 0x3, 0x80, 0xe0,
    0x0,

    /* U+0051 "Q" */
    0x1f, 0x83, 0xfc, 0x70, 0xef, 0xe, 0xe0, 0x7e,
    0x7, 0xe0, 0x7e, 0x7, 0xe0, 0x7f, 0xf, 0x70,
    0xe3, 0xfe, 0x1f, 0xe0, 0x6, 0x0, 0x0,

    /* U+0052 "R" */
    0xff, 0x1f, 0xf3, 0x8f, 0x70, 0xee, 0x1d, 0xc7,
    0xbf, 0xe7, 0xf8, 0xe7, 0x1c, 0x73, 0x8e, 0x70,
    0xee, 0x1c,

    /* U+0053 "S" */
    0x1f, 0x1f, 0xee, 0x1f, 0x84, 0xf0, 0x3f, 0x87,
    0xf8, 0x7f, 0x3, 0xd0, 0x7e, 0x1f, 0xfe, 0x3f,
    0x0,

    /* U+0054 "T" */
    0xff, 0xff, 0xf1, 0xc0, 0x70, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x1, 0xc0, 0x70, 0x1c,
    0x0,

    /* U+0055 "U" */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xe1, 0xf8, 0x77, 0x39, 0xfe, 0x1e,
    0x0,

    /* U+0056 "V" */
    0xe0, 0x77, 0x7, 0x70, 0x67, 0xe, 0x38, 0xe3,
    0x8c, 0x19, 0xc1, 0xdc, 0x1d, 0x80, 0xf8, 0xf,
    0x80, 0xf0, 0x7, 0x0,

    /* U+0057 "W" */
    0xe1, 0xe1, 0xd8, 0x78, 0x77, 0x1e, 0x19, 0xc7,
    0x8e, 0x73, 0xf3, 0x8c, 0xfc, 0xc3, 0x33, 0x30,
    0xec, 0xfc, 0x3f, 0x3f, 0x7, 0x87, 0x81, 0xe1,
    0xe0, 0x78, 0x78, 0x1c, 0xe, 0x0,

    /* U+0058 "X" */
    0x70, 0xf3, 0x8e, 0x39, 0xc1, 0xdc, 0xf, 0x80,
    0xf0, 0xf, 0x0, 0xf8, 0x1f, 0x81, 0xdc, 0x39,
    0xe7, 0xe, 0x70, 0x70,

    /* U+0059 "Y" */
    0x70, 0x73, 0x83, 0x8e, 0x38, 0x71, 0xc1, 0xdc,
    0x6, 0xc0, 0x3e, 0x0, 0xe0, 0x7, 0x0, 0x38,
    0x1, 0xc0, 0xe, 0x0, 0x70, 0x0,

    /* U+005A "Z" */
    0xff, 0xff, 0xf0, 0x38, 0x1e, 0x7, 0x3, 0x81,
    0xe0, 0x70, 0x38, 0x1e, 0x7, 0x3, 0xff, 0xff,
    0xc0,

    /* U+005B "[" */
    0xff, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce,
    0x7f, 0xe0,

    /* U+005C "\\" */
    0xe1, 0x86, 0x1c, 0x70, 0xc3, 0xe, 0x18, 0x61,
    0xc7, 0xc,

    /* U+005D "]" */
    0xff, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0xff, 0xe0,

    /* U+005E "^" */
    0x38, 0x3c, 0x7c, 0x66, 0x66,

    /* U+005F "_" */
    0xff, 0xff,

    /* U+0060 "`" */
    0x26, 0x73,

    /* U+0061 "a" */
    0x3c, 0x7e, 0x67, 0x7, 0x3f, 0x7f, 0xe7, 0xe7,
    0xff, 0x77,

    /* U+0062 "b" */
    0xe0, 0x70, 0x38, 0x1d, 0xcf, 0xf7, 0xbf, 0x8f,
    0xc7, 0xe3, 0xf1, 0xfd, 0xff, 0xee, 0xe0,

    /* U+0063 "c" */
    0x1e, 0x3f, 0x9c, 0xdc, 0xe, 0x7, 0x3, 0x80,
    0xe6, 0x7f, 0xf, 0x0,

    /* U+0064 "d" */
    0x3, 0x81, 0xc0, 0xe7, 0x77, 0xff, 0xbf, 0x8f,
    0xc7, 0xe3, 0xf1, 0xfd, 0xef, 0xf3, 0xb8,

    /* U+0065 "e" */
    0x3e, 0x3f, 0x98, 0xfc, 0x7f, 0xff, 0xff, 0x81,
    0xc6, 0x7f, 0x1f, 0x0,

    /* U+0066 "f" */
    0x3d, 0xf7, 0x1c, 0xff, 0xf7, 0x1c, 0x71, 0xc7,
    0x1c, 0x71, 0xc0,

    /* U+0067 "g" */
    0x3b, 0xbf, 0xfd, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xef, 0x7f, 0x9d, 0xc0, 0xec, 0x77, 0xf1, 0xf0,

    /* U+0068 "h" */
    0xe0, 0x70, 0x38, 0x1d, 0xef, 0xff, 0x9f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x38,

    /* U+0069 "i" */
    0xfc, 0xf, 0xff, 0xff, 0xff, 0xc0,

    /* U+006A "j" */
    0x39, 0xc0, 0x3, 0x9c, 0xe7, 0x39, 0xce, 0x73,
    0x9c, 0xe7, 0xff, 0x80,

    /* U+006B "k" */
    0xe0, 0x38, 0xe, 0x3, 0x8e, 0xe7, 0x3b, 0x8f,
    0xc3, 0xf0, 0xfe, 0x3b, 0xce, 0x73, 0x9e, 0xe3,
    0x80,

    /* U+006C "l" */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xef, 0x70,

    /* U+006D "m" */
    0xee, 0xf7, 0xff, 0xf9, 0xcf, 0xce, 0x7e, 0x73,
    0xf3, 0x9f, 0x9c, 0xfc, 0xe7, 0xe7, 0x3f, 0x39,
    0xc0,

    /* U+006E "n" */
    0xef, 0x7f, 0xfc, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xc7, 0xe3, 0xf1, 0xc0,

    /* U+006F "o" */
    0x3e, 0x3f, 0xbd, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xef, 0x7f, 0x1f, 0x0,

    /* U+0070 "p" */
    0xee, 0x7f, 0xbd, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xef, 0xff, 0x77, 0x38, 0x1c, 0xe, 0x7, 0x0,

    /* U+0071 "q" */
    0x3b, 0xbf, 0xfd, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xef, 0x7f, 0x9d, 0xc0, 0xe0, 0x70, 0x38, 0x1c,

    /* U+0072 "r" */
    0xef, 0xff, 0x38, 0xe3, 0x8e, 0x38, 0xe3, 0x80,

    /* U+0073 "s" */
    0x3c, 0xfe, 0xe6, 0xf0, 0xfc, 0x3f, 0xf, 0xe7,
    0xff, 0x7c,

    /* U+0074 "t" */
    0x71, 0xc7, 0x3f, 0xfd, 0xc7, 0x1c, 0x71, 0xc7,
    0x1f, 0x3c,

    /* U+0075 "u" */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f,
    0xcf, 0xff, 0xbd, 0xc0,

    /* U+0076 "v" */
    0xe1, 0xd8, 0x67, 0x39, 0xce, 0x33, 0xf, 0xc3,
    0xf0, 0x78, 0x1e, 0x7, 0x80,

    /* U+0077 "w" */
    0xe3, 0x8f, 0xc7, 0x19, 0x9e, 0x73, 0xbe, 0xe7,
    0x6d, 0x86, 0xdb, 0xd, 0xbe, 0x1e, 0x7c, 0x1c,
    0x70, 0x38, 0xe0,

    /* U+0078 "x" */
    0x73, 0x9c, 0xe3, 0xf0, 0x78, 0x1e, 0x7, 0x81,
    0xf0, 0xfc, 0x73, 0xbc, 0x70,

    /* U+0079 "y" */
    0xe1, 0xd8, 0x77, 0x19, 0xce, 0x33, 0x8e, 0xc3,
    0xf0, 0x78, 0x1e, 0x3, 0x80, 0xc0, 0x70, 0x1c,
    0x6, 0x0,

    /* U+007A "z" */
    0xff, 0xff, 0xe, 0x1e, 0x1c, 0x38, 0x78, 0x70,
    0xff, 0xff,

    /* U+007B "{" */
    0x1c, 0xf3, 0x8e, 0x38, 0xef, 0x3c, 0x38, 0xe3,
    0x8e, 0x38, 0x70, 0xc0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf8,

    /* U+007D "}" */
    0xe1, 0xf0, 0xe1, 0xc3, 0x87, 0x7, 0x8f, 0x38,
    0x70, 0xe1, 0xc3, 0x9e, 0x38, 0x0,

    /* U+007E "~" */
    0x38, 0x9f, 0x7e, 0xf9, 0x1c,

    /* U+007F "" */
    0x0,

    /* U+00B0 "°" */
    0x7b, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+2103 "℃" */
    0x78, 0x3f, 0x33, 0x1f, 0xec, 0xce, 0x1f, 0x37,
    0x80, 0x79, 0xc0, 0x0, 0x70, 0x0, 0x1c, 0x0,
    0x7, 0x0, 0x1, 0xe0, 0x0, 0x3c, 0x70, 0x7,
    0xf8, 0x0, 0x7c,

    /* U+FF1A "：" */
    0xff, 0x80, 0x3f, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 76, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 85, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 10, .adv_w = 194, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 161, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 46, .adv_w = 233, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 201, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 60, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 91, .adv_w = 97, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 101, .adv_w = 97, .box_w = 5, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 111, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 116, .adv_w = 167, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 125, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 128, .adv_w = 125, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 130, .adv_w = 77, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 119, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 129, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 161, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 162, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 167, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 164, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 169, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 149, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 174, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 169, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 77, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 80, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 298, .adv_w = 167, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 311, .adv_w = 167, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 317, .adv_w = 167, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 330, .adv_w = 143, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 226, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 199, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 187, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 193, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 204, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 164, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 200, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 205, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 77, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 198, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 244, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 200, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 211, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 180, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 211, .box_w = 12, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 653, .adv_w = 180, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 671, .adv_w = 173, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 169, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 196, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 200, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 289, .box_w = 18, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 200, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 194, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 174, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 97, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 841, .adv_w = 103, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 97, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 861, .adv_w = 126, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 866, .adv_w = 122, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 868, .adv_w = 86, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 870, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 880, .adv_w = 168, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 895, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 907, .adv_w = 168, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 922, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 934, .adv_w = 109, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 168, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 961, .adv_w = 162, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 976, .adv_w = 77, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 982, .adv_w = 78, .box_w = 5, .box_h = 18, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 994, .adv_w = 163, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1011, .adv_w = 79, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1018, .adv_w = 242, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1035, .adv_w = 162, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1047, .adv_w = 163, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1059, .adv_w = 168, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1075, .adv_w = 168, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1091, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1099, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1109, .adv_w = 114, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 162, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1131, .adv_w = 161, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 237, .box_w = 15, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 162, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1176, .adv_w = 164, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1194, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1204, .adv_w = 104, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1216, .adv_w = 69, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1222, .adv_w = 104, .box_w = 7, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1236, .adv_w = 162, .box_w = 10, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1241, .adv_w = 0, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1242, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1247, .adv_w = 300, .box_w = 18, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1274, .adv_w = 256, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x2053, 0xfe6a
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
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
    0, 0, 0, 0
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
    0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -24, 0, -14, 5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, -10, -11, -32, -11, -31, -20,
    0, -33, 0, -7, -7, -4, 0, -5,
    0, 0, -13, 0, -18, -11, 0, 0,
    0, 0, 0, 0, 0, -6, -28, 0,
    0, -7, -4, -3, -6, -1, -24, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -10,
    0, 0, 0, 0, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -20, 0, -13, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -6, 0, 0, 0, 0, -4,
    -7, 0, 0, 0, -2, 0, 0, 0,
    -9, 0, -7, 0, -6, 0, -9, -5,
    0, -14, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, -3, 0, 0,
    -5, -6, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, -9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, -5,
    0, 0, 0, 0, 0, 0, -5, -5,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -5, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, -4, 0,
    -5, 0, 0, 0, -7, 0, -5, -8,
    0, 0, 0, 0, -8, 0, -10, 0,
    0, -10, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, -6, 0,
    0, 0, 0, 0, -4, 0, 0, -8,
    0, 0, 0, 0, 0, 0, -5, 0,
    -9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -21, 0, -3, 0, 0, 0, -15, 0,
    0, 0, 0, 0, -9, 0, -3, -20,
    0, 0, 0, 0, -23, 0, -21, 0,
    -11, -29, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -10, 0, -11, -5,
    5, 0, -32, -6, -19, -3, 0, 0,
    0, -18, 0, -16, 6, -6, 0, 5,
    -29, 0, -32, 0, 0, 0, 0, 0,
    0, 0, 0, -17, -15, -4, 0, 0,
    -8, -12, 0, -6, 0, 0, -6, -4,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -5, -3,
    0, 0, 0, 0, -5, 0, -9, 0,
    0, -11, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -7, 0,
    0, 0, -22, 0, -13, 0, 0, 0,
    0, -6, 0, -5, 0, -5, 0, 0,
    -18, 0, -25, 0, 0, 0, -4, 0,
    -16, -9, 0, -8, -6, 4, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -17, -2, -10, 3, -4, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -29, -1, 0, -16, 0, -9, -20, 0,
    0, 0, 0, 0, 0, 0, -21, -23,
    0, -10, 0, 0, -22, -4, -30, -20,
    0, -34, 0, 0, -4, -7, 0, -5,
    0, 0, -14, -6, -19, -15, 0, 0,
    -8, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    -5, 0, -3, 0, -6, 0, -11, -5,
    -5, -9, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, 0, -1, -2,
    0, 0, 0, -12, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, 0, -1, 0, 0, 0,
    -9, -14, -3, -4, -7, 0, 0, 0,
    0, 0, 0, 0, -5, -5, -3, 0,
    -5, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    -10, 0, -13, 0, -8, 0, -13, -4,
    -17, -16, -9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -5, 0, 0,
    3, -5, -16, 0, 0, 0, 0, 0,
    0, -6, 0, -5, 0, 0, 0, 0,
    -16, 0, -41, -3, 0, 0, 0, 0,
    -5, 0, 0, -11, -4, 0, 0, 0,
    -4, -3, 0, -5, -3, -3, -6, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -6, 0, 0, 0, -8, 0, -10, -4,
    -10, -13, -3, 0, 0, 0, 0, 0,
    0, -2, 0, 0, -7, -8, -5, 0,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -12, 2, -27, 0, -15, -10, 0,
    0, -8, 0, 0, 0, 0, -18, -13,
    0, -20, -12, -10, 0, -13, 0, 0,
    0, 0, 0, -11, -14, -12, 0, -8,
    -4, -8, -13, -13, -24, -16, -6, 0,
    -27, 0, 5, -25, 0, 0, -26, 0,
    0, 0, 0, 0, -4, 0, -28, -27,
    0, -10, 0, 0, -40, -7, -40, -25,
    0, -53, 0, 0, -5, -5, 0, 0,
    0, 0, -16, -3, -25, -13, 0, 0,
    0, -10, -24, 0, 0, 0, 0, -5,
    0, -10, 0, 0, 0, 0, 0, 0,
    -23, 0, -50, 0, -5, 0, -9, -7,
    -18, -14, -5, -10, -6, 4, 0, 0,
    0, -2, 4, -2, 2, 1, -4, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, -8, 0, -6, -6,
    -11, -13, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -8, 0, -5, 0, -6, -3,
    0, -11, 0, -4, -5, 0, 0, 0,
    0, 0, 0, -5, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, 0, -7, 0,
    -7, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -5, -3, -4,
    5, -16, -28, -20, 0, -6, 0, 0,
    0, -25, 0, -20, 0, -5, 0, 0,
    -22, -10, -44, -5, 0, 0, -5, 0,
    -10, 0, 0, -27, -29, -10, 0, 0,
    -17, -25, -5, -11, -20, -22, -24, -18,
    0, 0, -7, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, -10, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -18, -35, -14, 0, -9, 0, 0,
    0, -20, -3, -15, 0, -9, 0, 0,
    -30, -13, -44, -5, 0, 0, 0, 0,
    0, 0, 0, -24, -24, -6, 0, 0,
    -13, -20, -5, -12, -10, -8, -12, -10,
    0, -10, -23, -9, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -20, -4, -31, -1, 0, 0, 0, 0,
    0, 0, 0, -18, -15, -3, 0, 0,
    -9, -14, -2, -11, -3, -5, -10, -7,
    0, -11, 1, -27, 0, 0, -10, 0,
    -5, -9, -7, -11, 0, 0, -16, -9,
    0, -17, -10, -5, -10, -5, 0, 0,
    0, 0, 0, -8, -16, -11, 0, -2,
    -4, -10, -16, -13, -20, -20, 0, 0,
    0, -23, -38, -20, 0, -14, -4, -5,
    -5, -31, 0, -26, 0, -11, -8, -2,
    -34, -16, -41, -10, 0, 0, 0, 0,
    0, 0, 0, -31, -32, -12, 0, 0,
    -23, -28, -11, -23, -14, -14, -19, -18,
    0, -10, 0, -13, 0, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -13, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, -4, 0, 0, 0,
    0, 0, -7, -8, -11, -10, 0, 0,
    -11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, -4, -14,
    0, 0, 0, 0, -24, 0, -24, -14,
    0, -28, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, -5, 0, 0,
    -11, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, -7, -18,
    -4, 0, 0, 0, -29, 0, -24, -15,
    -16, -32, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -7, -3, -11, -3,
    -5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -6,
    0, 0, 0, 0, -28, 0, -16, -10,
    -11, -30, 0, -3, -4, 0, -3, -3,
    0, 0, 0, 0, -8, 0, -9, 0,
    0, 0, -5, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -9, 0, 0, -15,
    0, 0, 0, 0, -26, 0, -20, -13,
    -15, -28, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -1, -10, 0,
    8, -5, -20, 0, 0, 0, 0, 0,
    0, -13, 0, 0, 5, 0, 4, 0,
    -17, 0, -16, 0, 0, 0, 0, 0,
    0, 0, 0, -6, -5, 0, 0, 0,
    0, -4, 2, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, 0, -4,
    0, 0, 0, 0, -13, 0, -14, -10,
    -3, -23, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -5, -11,
    0, 0, 0, 0, -29, 0, -21, -14,
    -5, -34, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -4, -3, -2, 0,
    -8, -4, 2, -14, 0, 0, 0, 0,
    0, -10, 0, -12, 0, -9, -4, -3,
    0, -5, 0, 0, -24, -3, -12, -7,
    0, -20, 0, -4, -12, 0, 0, -2,
    0, -6, -5, -7, 0, 0, 0, 0,
    0, -1, 5, -4, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -7,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 0, -2, 0, 0,
    2, 0, 0, 1, -5, -2, 0, 0,
    0, -13, -28, 0, 0, 0, 0, -3,
    -9, -15, 0, -7, 0, 0, 3, 0,
    0, 0, 0, 0, -23, 0, 0, 0,
    -16, -14, -13, -7, -5, 3, 0, 0,
    0, -4, 3, -7, 3, 5, -1, 0,
    -10, 0, 0, 0, 0, 0, -8, 0,
    0, 0, 0, 0, -8, 0, 0, -12,
    0, 0, 0, 0, -27, 0, -21, -15,
    -10, -28, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -5, -4, -6, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, -5, 0, -7, -2,
    0, -16, 0, 0, -3, 2, 0, 0,
    0, -2, 0, -1, 0, 0, 0, 0,
    0, -10, -22, 0, 0, 0, 0, 0,
    0, -12, 0, -9, 0, 0, 0, 0,
    -19, 0, -25, 0, -20, 0, -10, -3,
    -20, -14, -13, -9, -7, 0, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, -4, -18, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -15, 0, -16, 0, -22, 0, -8, -5,
    -20, -14, -10, -7, -3, 0, 0, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -9, 0, 0, 0, 0,
    0, -13, 0, -11, -4, -7, 0, 0,
    0, -3, 0, 0, -24, 0, -12, -10,
    -2, -19, 0, -5, -11, 0, 0, -3,
    0, -6, 0, -3, 0, 0, 0, 0,
    0, -4, 0, -3, 0, 0, 0, 0,
    0, -3, 0, -5, -2, 0, -2, 0,
    0, -4, 0, 0, -21, 0, -11, -7,
    0, -17, 0, 0, -6, 0, 0, 0,
    0, -3, 0, -3, 0, 0, 0, 0
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
const lv_font_t MiSans_Bold_16px = {
#else
lv_font_t MiSans_Bold_16px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if MISANS_BOLD_16PX*/

