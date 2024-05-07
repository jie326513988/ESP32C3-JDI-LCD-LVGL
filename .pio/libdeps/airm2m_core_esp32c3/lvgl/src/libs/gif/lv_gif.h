/**
 * @file lv_gif.h
 *
 */

#ifndef LV_GIF_H
#define LV_GIF_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../../../lvgl.h"
#if LV_USE_GIF

#include "gifdec.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    lv_image_t img;
    gd_GIF * gif;
    lv_timer_t * timer;
    lv_draw_buf_t imgdsc;
    uint32_t last_call;
} lv_gif_t;

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_gif_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 创建gif对象
 * @param parent    pointer to an object, it will be the parent of the new gif.
 * @return          pointer to the gif obj
 */
lv_obj_t * lv_gif_create(lv_obj_t * parent);

/**
 * 将gif数据设置为显示在对象上
 * @param obj       pointer to a gif object
 * @param src       1) pointer to an ::lv_image_dsc_t descriptor (which contains gif raw data) or
 *                  2) path to a gif file (e.g. "S:/dir/anim.gif")
 */
void lv_gif_set_src(lv_obj_t * obj, const void * src);

/**
 * 重新启动gif动画。
 * @param obj pointer to a gif obj
 */
void lv_gif_restart(lv_obj_t * obj);

/**
 * 暂停gif动画。
 * @param obj pointer to a gif obj
 */
void lv_gif_pause(lv_obj_t * obj);

/**
 * 恢复gif动画。
 * @param obj pointer to a gif obj
 */
void lv_gif_resume(lv_obj_t * obj);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_GIF*/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_GIF_H*/
