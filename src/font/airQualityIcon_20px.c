/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --no-compress 
 * --font airQualityIcon.ttf 
 * --range 58891,58895,58909,58928,59057 
 * --format lvgl -o airQualityIcon_20px.c
 ******************************************************************************/

#include "lvgl.h"

#ifndef AIRQUALITYICON_20PX
#define AIRQUALITYICON_20PX 1
#endif

#if AIRQUALITYICON_20PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E60B "" */
    0x0, 0x60, 0x4, 0x18, 0x0, 0x20, 0x30, 0x0,
    0x0, 0x30, 0x18, 0xc, 0xe, 0x0, 0x0, 0x0,
    0x7c, 0x4, 0x60, 0xc0, 0x70, 0xc, 0x60, 0x0,
    0xe0, 0x0, 0x0, 0x2b, 0x56, 0xb, 0x16, 0x43,
    0xc7, 0x90, 0xad, 0x58,

    /* U+E60F "" */
    0x0, 0x0, 0x18, 0x0, 0xc0, 0xf, 0x0, 0xe8,
    0x6, 0x60, 0x63, 0x3, 0xc, 0x30, 0x73, 0x81,
    0x9b, 0xcf, 0x94, 0x3c, 0xa1, 0xe3, 0xcf, 0x1a,
    0x78, 0xb3, 0x60, 0x33, 0x1, 0x8e, 0x38, 0x1f,
    0x0,

    /* U+E61D "" */
    0x0, 0x3c, 0x0, 0x1f, 0x80, 0xf, 0xf0, 0x3,
    0xfc, 0x0, 0xff, 0x0, 0x3f, 0xc0, 0xe7, 0xe0,
    0x7c, 0xf0, 0x3f, 0x0, 0x7, 0xc0, 0x1, 0xe3,
    0x80, 0x0, 0xe0, 0x0, 0x38, 0x0, 0x0, 0xf,
    0x8b, 0x9d, 0x15, 0x29, 0x45, 0x4a, 0x11, 0x51,
    0x84, 0x24, 0xa5, 0x8, 0xe6,

    /* U+E630 "" */
    0x1c, 0x11, 0x18, 0x8e, 0x47, 0x23, 0xd1, 0x88,
    0xe4, 0x72, 0x21, 0x10, 0x50, 0x18, 0xc, 0x17,
    0x16, 0xc6, 0x3e, 0x0,

    /* U+E6B1 "" */
    0x4, 0xc0, 0x0, 0x4, 0x0, 0x0, 0x2, 0x63,
    0x22, 0x18, 0xcc, 0x0, 0xcc, 0xc, 0xff, 0xdb,
    0x66, 0x3e, 0x10, 0x6, 0xc, 0x1, 0x86, 0x77,
    0x3a, 0x22, 0x46, 0x89, 0x9c, 0xe1, 0xdd, 0x38,
    0x0, 0xdf, 0x0, 0xe, 0x78, 0x1f, 0x3, 0xe,
    0x0, 0x3e, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 320, .box_w = 18, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 36, .adv_w = 320, .box_w = 13, .box_h = 20, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 320, .box_w = 18, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 114, .adv_w = 320, .box_w = 9, .box_h = 17, .ofs_x = 6, .ofs_y = -1},
    {.bitmap_index = 134, .adv_w = 320, .box_w = 18, .box_h = 19, .ofs_x = 1, .ofs_y = -2}
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
const lv_font_t airQualityIcon_20px = {
#else
lv_font_t airQualityIcon_20px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 21,          /*The maximum line height required by the font*/
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



#endif /*#if AIRQUALITYICON_20PX*/

