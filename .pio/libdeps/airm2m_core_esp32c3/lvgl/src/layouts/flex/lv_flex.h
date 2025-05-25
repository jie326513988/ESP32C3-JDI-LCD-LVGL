/**
 * @file lv_flex.h
 *
 */

#ifndef LV_FLEX_H
#define LV_FLEX_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"
#include "../../misc/lv_area.h"

#if LV_USE_FLEX

/*********************
 *      DEFINES
 *********************/

#define _LV_FLEX_COLUMN     (1 << 0)
#define _LV_FLEX_WRAP       (1 << 2)
#define _LV_FLEX_REVERSE    (1 << 3)

/**********************
 *      TYPEDEFS
 **********************/

/*Can't include lv_obj.h because it includes this header file*/

typedef enum {
    LV_FLEX_ALIGN_START,
    LV_FLEX_ALIGN_END,
    LV_FLEX_ALIGN_CENTER,
    LV_FLEX_ALIGN_SPACE_EVENLY,
    LV_FLEX_ALIGN_SPACE_AROUND,
    LV_FLEX_ALIGN_SPACE_BETWEEN,
} lv_flex_align_t;

typedef enum {
    LV_FLEX_FLOW_ROW                 = 0x00,
    LV_FLEX_FLOW_COLUMN              = _LV_FLEX_COLUMN,
    LV_FLEX_FLOW_ROW_WRAP            = LV_FLEX_FLOW_ROW | _LV_FLEX_WRAP,
    LV_FLEX_FLOW_ROW_REVERSE         = LV_FLEX_FLOW_ROW | _LV_FLEX_REVERSE,
    LV_FLEX_FLOW_ROW_WRAP_REVERSE    = LV_FLEX_FLOW_ROW | _LV_FLEX_WRAP | _LV_FLEX_REVERSE,
    LV_FLEX_FLOW_COLUMN_WRAP         = LV_FLEX_FLOW_COLUMN | _LV_FLEX_WRAP,
    LV_FLEX_FLOW_COLUMN_REVERSE      = LV_FLEX_FLOW_COLUMN | _LV_FLEX_REVERSE,
    LV_FLEX_FLOW_COLUMN_WRAP_REVERSE = LV_FLEX_FLOW_COLUMN | _LV_FLEX_WRAP | _LV_FLEX_REVERSE,
} lv_flex_flow_t;

/**********************
 * GLOBAL VARIABLES
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 将flex布局初始化为默认值
 * @param flex 指向flex布局描述符的指针
 */
void lv_flex_init(void);

/**
 * 设置项目应如何流动
 * @param obj 指向对象的指针。父级必须具有柔性布局，否则什么都不会发生。
 * @param flow `lv_flex_flow_t`的一个元素。
 */
void lv_obj_set_flex_flow(lv_obj_t * obj, lv_flex_flow_t flow);

/**
 * 设置如何放置（对齐位置）项目和轨迹
 * @param obj 指向对象的指针。父级必须具有柔性布局，否则什么都不会发生。
 * @param main_place 将项目放置在主轴上的何处（在其轨迹中）。`lv_flex_align_t`的任何值。
 * @param cross_place 将项目放置在横轴上的轨迹中的何处`LV_FLEX_ALIGN_START/END/CENTER`
 * @param track_cross_place 在横向方向上将轨道放置在哪里。`lv_flex_align_t`的任何值。
 */
void lv_obj_set_flex_align(lv_obj_t * obj, lv_flex_align_t main_place, lv_flex_align_t cross_place,
                           lv_flex_align_t track_cross_place);

/**
 * 设置对象生长的宽度或高度（在主轴上），以填充自由空间
 * @param obj 指向对象的指针。父级必须具有柔性布局，否则什么都不会发生。
 * @param grow a value设置与其他生长项目成比例占用多少可用空间。
 */
void lv_obj_set_flex_grow(lv_obj_t * obj, uint8_t grow);

/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_FLEX*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_FLEX_H*/
