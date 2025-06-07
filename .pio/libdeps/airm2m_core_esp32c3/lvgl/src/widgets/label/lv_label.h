/**
 * @file lv_label.h
 *
 */

#ifndef LV_LABEL_H
#define LV_LABEL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"

#if LV_USE_LABEL != 0

#include "../../misc/lv_types.h"
#include "../../core/lv_obj.h"
#include "../../font/lv_font.h"
#include "../../font/lv_symbol_def.h"
#include "../../misc/lv_text.h"
#include "../../draw/lv_draw.h"

/*********************
 *      DEFINES
 *********************/
#define LV_LABEL_DOT_NUM 3
#define LV_LABEL_POS_LAST 0xFFFF
#define LV_LABEL_TEXT_SELECTION_OFF LV_DRAW_LABEL_NO_TXT_SEL
#if LV_WIDGETS_HAS_DEFAULT_VALUE
#define LV_LABEL_DEFAULT_TEXT "Text"
#else
#define LV_LABEL_DEFAULT_TEXT ""
#endif

LV_EXPORT_CONST_INT(LV_LABEL_DOT_NUM);
LV_EXPORT_CONST_INT(LV_LABEL_POS_LAST);
LV_EXPORT_CONST_INT(LV_LABEL_TEXT_SELECTION_OFF);

/**********************
 *      TYPEDEFS
 **********************/

/** Long mode behaviors. Used in 'lv_label_ext_t'*/
enum _lv_label_long_mode_t
{
    LV_LABEL_LONG_WRAP,            /**<保持对象宽度,换行比对象宽度长并扩展对象高度*/
    LV_LABEL_LONG_DOT,             /**<如果文本太长,请保持大小并在末尾写点*/
    LV_LABEL_LONG_SCROLL,          /**<保持大小并来回滚动文本*/
    LV_LABEL_LONG_SCROLL_CIRCULAR, /**<保持大小并循环滚动文本*/
    LV_LABEL_LONG_CLIP,            /**<保持大小并将文本剪裁掉*/
};

#ifdef DOXYGEN
typedef _lv_label_long_mode_t lv_label_long_mode_t;
#else
typedef uint8_t lv_label_long_mode_t;
#endif /*DOXYGEN*/

typedef struct {
    lv_obj_t obj;
    char * text;
    union {
        char * tmp_ptr; /*Pointer to the allocated memory containing the character replaced by dots*/
        char tmp[LV_LABEL_DOT_NUM + 1]; /*Directly store the characters if <=4 characters*/
    } dot;
    uint32_t dot_end;  /*The real text length, used in dot mode*/

#if LV_LABEL_LONG_TXT_HINT
    lv_draw_label_hint_t hint;
#endif

#if LV_LABEL_TEXT_SELECTION
    uint32_t sel_start;
    uint32_t sel_end;
#endif

    lv_point_t size_cache; /*Text size cache*/
    lv_point_t offset; /*Text draw position offset*/
    lv_label_long_mode_t long_mode : 3; /*Determine what to do with the long texts*/
    uint8_t static_txt : 1;             /*Flag to indicate the text is static*/
    uint8_t expand : 1;                 /*Ignore real width (used by the library with LV_LABEL_LONG_SCROLL)*/
    uint8_t dot_tmp_alloc : 1;          /*1: dot is allocated, 0: dot directly holds up to 4 chars*/
    uint8_t invalid_size_cache : 1;     /*1: Recalculate size and update cache*/
} lv_label_t;

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_label_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 创建标签对象
 * @param parent    pointer to an object, it will be the parent of the new label.
 * @return          pointer to the created button
 */
lv_obj_t * lv_label_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * 为标签设置新文本。将按标签分配内存来存储文本。
 * @param obj           pointer to a label object
 * @param text          '\0' terminated character string. NULL to refresh with the current text.
 */
void lv_label_set_text(lv_obj_t * obj, const char * text);

/**
 * 为标签设置新的格式化文本。将按标签分配内存来存储文本。
 * @param obj           pointer to a label object
 * @param fmt           `printf`-like format
 * @example lv_label_set_text_fmt(label1, "%d user", user_num);
 */
void lv_label_set_text_fmt(lv_obj_t * obj, const char * fmt, ...) LV_FORMAT_ATTRIBUTE(2, 3);

/**
 * 设置静态文本。它不会被标签保存，因此“text”变量必须在标签存在时处于“活动”状态。
 * @param obj           pointer to a label object
 * @param text          pointer to a text. NULL to refresh with the current text.
 */
void lv_label_set_text_static(lv_obj_t * obj, const char * text);

/**
 * 使用长于对象大小的文本设置标签的行为
 * @param obj           pointer to a label object
 * @param long_mode     the new mode from 'lv_label_long_mode' enum.
 *                      In LV_LONG_WRAP/DOT/SCROLL/SCROLL_CIRC the size of the label should be set AFTER this function
 */
void lv_label_set_long_mode(lv_obj_t * obj, lv_label_long_mode_t long_mode);

/**
 * 设置文本选择的开始位置
 * @param obj       pointer to a label object
 * @param index     character index from where selection should start. `LV_LABEL_TEXT_SELECTION_OFF` for no selection
 */
void lv_label_set_text_selection_start(lv_obj_t * obj, uint32_t index);

/**
 * 设置文本选择的结束位置
 * @param obj       pointer to a label object
 * @param index     character index where selection should end. `LV_LABEL_TEXT_SELECTION_OFF` for no selection
 */
void lv_label_set_text_selection_end(lv_obj_t * obj, uint32_t index);

/*=====================
 * Getter functions
 *====================*/

/**
 * 获取标签的文本
 * @param obj       pointer to a label object
 * @return          the text of the label
 */
char * lv_label_get_text(const lv_obj_t * obj);

/**
 * 获取标签的长模式
 * @param obj       pointer to a label object
 * @return          the current long mode
 */
lv_label_long_mode_t lv_label_get_long_mode(const lv_obj_t * obj);

/**
 * 获取字母的相对x和y坐标
 * @param obj       pointer to a label object
 * @param char_id   index of the character [0 ... text length - 1].
 *                  Expressed in character index, not byte index (different in UTF-8)
 * @param pos       store the result here (E.g. index = 0 gives 0;0 coordinates if the text if aligned to the left)
 */
void lv_label_get_letter_pos(const lv_obj_t * obj, uint32_t char_id, lv_point_t * pos);

/**
 * 获取标签相对点上的字母索引。
 * @param obj       pointer to label object
 * @param pos_in    pointer to point with coordinates on a the label
 * @param bidi      whether to use bidi processed
 * @return          The index of the letter on the 'pos_p' point (E.g. on 0;0 is the 0. letter if aligned to the left)
 *                  Expressed in character index and not byte index (different in UTF-8)
 */
uint32_t lv_label_get_letter_on(const lv_obj_t * obj, lv_point_t * pos_in, bool bidi);

/**
 * 检查字符是否绘制在点下。
 * @param obj       pointer to a label object
 * @param pos       Point to check for character under
 * @return          whether a character is drawn under the point
 */
bool lv_label_is_char_under_pos(const lv_obj_t * obj, lv_point_t * pos);

/**
 * @brief 获取选择开始索引。
 * @param obj       指向标签对象的指针。
 * @return          选择开始索引`如果未选择任何内容，则LV_LABEL_TEXT_SELECTION_OFF。
 */
uint32_t lv_label_get_text_selection_start(const lv_obj_t * obj);

/**
 * @brief 获取选择结束索引。
 * @param obj       pointer to a label object.
 * @return          selection end index. `LV_LABEL_TXT_SEL_OFF` if nothing is selected.
 */
uint32_t lv_label_get_text_selection_end(const lv_obj_t * obj);

/*=====================
 * Other functions
 *====================*/

/**
 * 在标签中插入文本。标签文本不能是静态的。
 * @param obj       指向标签对象的指针
 * @param pos       要插入的字符索引。用字符索引而不是字节索引表示。
                    0：在第一个字符之前。LV_LABEL_POS_LAST：在最后一个字符之后。
 * @param txt       指向要插入的文本的指针
 */
void lv_label_ins_text(lv_obj_t * obj, uint32_t pos, const char * txt);

/**
 * 从标签中删除字符。标签文本不能是静态的。
 * @param obj       pointer to a label object
 * @param pos       字符索引从哪里剪切。用字符索引而不是字节索引表示。
 *                  0：从第一个字符前面开始
 * @param cnt       要剪切的字符数
 */
void lv_label_cut_text(lv_obj_t * obj, uint32_t pos, uint32_t cnt);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_LABEL*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_LABEL_H*/
