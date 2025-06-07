/**
 * @file lv_text.h
 *
 */

#ifndef LV_TEXT_H
#define LV_TEXT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf_internal.h"

#include "lv_types.h"
#include "lv_area.h"
#include "../font/lv_font.h"
#include "../stdlib/lv_sprintf.h"

    /*********************
     *      DEFINES
     *********************/

#define LV_TXT_ENC_UTF8 1
#define LV_TXT_ENC_ASCII 2

    /**********************
     *      TYPEDEFS
     **********************/

    /**
     * Options for text rendering.
     */

    enum _lv_text_flag_t
    {
        LV_TEXT_FLAG_NONE = 0x00,
        LV_TEXT_FLAG_EXPAND = 0x01, /**< 忽略最大宽度以避免自动换行*/
        LV_TEXT_FLAG_FIT = 0x02,    /**< 最大宽度已等于最长线。（用于跳过一些计算）*/
    };

#ifdef DOXYGEN
    typedef _lv_text_flag_t lv_text_flag_t;
#else
typedef uint8_t lv_text_flag_t;
#endif /*DOXYGEN*/

    /** Label align policy*/
    enum _lv_text_align_t
    {
        LV_TEXT_ALIGN_AUTO,   /**<自动对齐文本*/
        LV_TEXT_ALIGN_LEFT,   /**<将文本向左对齐*/
        LV_TEXT_ALIGN_CENTER, /**<将文本居中对齐*/
        LV_TEXT_ALIGN_RIGHT,  /**<将文本向右对齐*/
    };

#ifdef DOXYGEN
    typedef _lv_text_align_t lv_text_align_t;
#else
typedef uint8_t lv_text_align_t;
#endif /*DOXYGEN*/

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * 获取文本大小
     * @param size_res 指向“point_t”变量以存储结果的指针
     * @param text 指向文本的指针
     * @param font 指向文本字体的指针
     * @param letter_space 文本的字母间距
     * @param line_space 文本的行距
     * @param max_width 文本的最大宽度（打断线条以适应此大小）。设置COORD_MAX以避免
     * @param flag 以下文本的设置：：lv_text_flag_t

     * line breaks
     */
    void lv_text_get_size(lv_point_t *size_res, const char *text, const lv_font_t *font, int32_t letter_space,
                          int32_t line_space, int32_t max_width, lv_text_flag_t flag);

    /**
     * 给定给定字体的文本长度
     * @param txt a '\0' 终止字符串
     * @param length 字节计数中的“txt”长度，而不是字符（Á是1个字符，但在UTF-8中是2个字节）
     * @param font 指向字体的指针
     * @param letter_space 字母间隔
     * @return char_num长文本的长度
     */
    int32_t lv_text_get_width(const char *txt, uint32_t length, const lv_font_t *font, int32_t letter_space);

    /**********************
     *      MACROS
     **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TEXT_H*/
