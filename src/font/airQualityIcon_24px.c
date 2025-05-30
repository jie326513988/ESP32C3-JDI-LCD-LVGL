/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: --bpp 1 --size 24 --no-compress --font airQualityIcon.ttf --range 58891,58895,58909,58928,59057 --format lvgl -o airQualityIcon_24px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef AIRQUALITYICON_24PX
#define AIRQUALITYICON_24PX 1
#endif

#if AIRQUALITYICON_24PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E60B "" */
    0x0, 0x18, 0x0, 0x1, 0xc0, 0x4, 0xe, 0x0,
    0x0, 0x0, 0x40, 0x0, 0x6, 0x0, 0x0, 0x0,
    0xc0, 0x38, 0x6, 0x1, 0xc0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x7, 0xe0, 0x8, 0xc0, 0xc0, 0x1c,
    0x1, 0xc3, 0x80, 0x7, 0xf0, 0x0, 0x0, 0x5,
    0x34, 0x98, 0x2a, 0x25, 0x21, 0xd1, 0xe9, 0xa,
    0x89, 0x48, 0x53, 0x49, 0x80,

    /* U+E60F "" */
    0x0, 0x80, 0x0, 0x80, 0x1, 0xc0, 0x3, 0xc0,
    0x3, 0xe0, 0x7, 0x60, 0xe, 0x30, 0xc, 0x38,
    0x1c, 0x18, 0x38, 0x1c, 0x30, 0xc, 0x60, 0x6,
    0x6f, 0x7, 0xc9, 0x83, 0xcd, 0x3, 0xc3, 0x63,
    0xc2, 0xa3, 0xe4, 0x67, 0x60, 0x6, 0x70, 0xe,
    0x3c, 0x3c, 0x1f, 0xf8, 0x7, 0xe0,

    /* U+E61D "" */
    0x0, 0xf, 0x0, 0x0, 0xff, 0x0, 0x7, 0xfc,
    0x0, 0x1f, 0xf8, 0x0, 0x7f, 0xe0, 0x1, 0xff,
    0x80, 0x7, 0xfc, 0x3, 0xcf, 0xf0, 0x1f, 0x8f,
    0x0, 0x7e, 0x0, 0x1, 0xf8, 0x0, 0x7, 0xe0,
    0x0, 0xf, 0xe, 0x0, 0x0, 0x3c, 0x0, 0x0,
    0xf0, 0x0, 0x3, 0x80, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xf, 0xc5, 0xe3, 0x88, 0xa4, 0xd1, 0x22,
    0x91, 0x40, 0x8a, 0x45, 0x2, 0x11, 0x34, 0x48,
    0x43, 0x8e,

    /* U+E630 "" */
    0xe, 0x4, 0x43, 0x10, 0xf4, 0x31, 0xe, 0x43,
    0xf0, 0xc4, 0x39, 0xf, 0x43, 0x10, 0xc6, 0x40,
    0xa0, 0x18, 0x6, 0x1, 0x80, 0xd0, 0x66, 0x38,
    0x78,

    /* U+E6B1 "" */
    0x0, 0x30, 0x0, 0x2, 0x2, 0x0, 0x0, 0x4,
    0x0, 0x0, 0x0, 0x4, 0x63, 0xc, 0xc0, 0xc6,
    0x18, 0x0, 0x0, 0x0, 0x0, 0xe7, 0x80, 0x67,
    0xff, 0xcc, 0xdc, 0x31, 0xd8, 0x38, 0x1, 0xc0,
    0xe0, 0x1, 0x83, 0xdd, 0xe3, 0xcf, 0x4a, 0x63,
    0xb8, 0x88, 0x43, 0xf1, 0x30, 0xa3, 0xe2, 0x53,
    0x27, 0xc3, 0xbc, 0x8f, 0x80, 0x3, 0xb3, 0x80,
    0x0, 0xe3, 0xf0, 0x1f, 0x80, 0x70, 0x78, 0x0,
    0x7f, 0xc0, 0x0, 0x7e, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 384, .box_w = 21, .box_h = 20, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 384, .box_w = 16, .box_h = 23, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 99, .adv_w = 384, .box_w = 22, .box_h = 24, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 165, .adv_w = 384, .box_w = 10, .box_h = 20, .ofs_x = 7, .ofs_y = -1},
    {.bitmap_index = 190, .adv_w = 384, .box_w = 23, .box_h = 24, .ofs_x = 1, .ofs_y = -3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x4, 0x12, 0x25, 0xa6
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58891, .range_length = 167, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 5, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
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
    .kern_dsc = NULL,
    .kern_scale = 0,
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
const lv_font_t airQualityIcon_24px = {
#else
lv_font_t airQualityIcon_24px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 24,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if AIRQUALITYICON_24PX*/

