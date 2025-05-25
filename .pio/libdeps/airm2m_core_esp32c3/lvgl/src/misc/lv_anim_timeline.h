/**
 * @file lv_anim_timeline.h
 *
 */

#ifndef LV_ANIM_TIMELINE_H
#define LV_ANIM_TIMELINE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_anim.h"

/*********************
 *      DEFINES
 *********************/

#define LV_ANIM_TIMELINE_PROGRESS_MAX 0xFFFF

/**********************
 *      TYPEDEFS
 **********************/

typedef struct _lv_anim_timeline_t lv_anim_timeline_t;

/**********************
* GLOBAL PROTOTYPES
**********************/

/**
 * 创建动画时间线。
 * @return pointer to the animation timeline.
 */
lv_anim_timeline_t * lv_anim_timeline_create(void);

/**
 *删除动画时间线。
 * @param at    pointer to the animation timeline.
 */
void lv_anim_timeline_delete(lv_anim_timeline_t * at);

/**
 * 将动画添加到动画时间线。
 * @param at            pointer to the animation timeline.
 * @param start_time    the time the animation started on the timeline, note that start_time will override the value of delay.
 * @param a             pointer to an animation.
 */
void lv_anim_timeline_add(lv_anim_timeline_t * at, uint32_t start_time, const lv_anim_t * a);

/**
 * 启动动画时间线。
 * @param at    pointer to the animation timeline.
 * @return total time spent in animation timeline.
 */
uint32_t lv_anim_timeline_start(lv_anim_timeline_t * at);

/**
 * 暂停动画时间线。
 * @param at    pointer to the animation timeline.
 */
void lv_anim_timeline_pause(lv_anim_timeline_t * at);

/**
 * 设置动画时间线的播放方向。
 * @param at        pointer to the animation timeline.
 * @param reverse   whether to play in reverse.
 */
void lv_anim_timeline_set_reverse(lv_anim_timeline_t * at, bool reverse);

/**
 * 设置动画时间线的进度。
 * @param at        pointer to the animation timeline.
 * @param progress  set value 0~65535 to map 0~100% animation progress.
 */
void lv_anim_timeline_set_progress(lv_anim_timeline_t * at, uint16_t progress);

/**
 * 获取播放动画时间线所用的时间.
 * @param at    pointer to the animation timeline.
 * @return total time spent in animation timeline.
 */
uint32_t lv_anim_timeline_get_playtime(lv_anim_timeline_t * at);

/**
 * 获取动画时间线是否反向播放。
 * @param at    pointer to the animation timeline.
 * @return return true if it is reverse playback.
 */
bool lv_anim_timeline_get_reverse(lv_anim_timeline_t * at);

/**
 * 获取动画时间线的进度。
 * @param at    pointer to the animation timeline.
 * @return return value 0~65535 to map 0~100% animation progress.
 */
uint16_t lv_anim_timeline_get_progress(lv_anim_timeline_t * at);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_ANIM_TIMELINE_H*/
