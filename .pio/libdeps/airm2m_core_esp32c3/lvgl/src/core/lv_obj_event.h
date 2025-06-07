/**
 * @file lv_obj_event.h
 *
 */

#ifndef LV_OBJ_EVENT_H
#define LV_OBJ_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_types.h"
#include "../misc/lv_event.h"
#include "../indev/lv_indev.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Used as the event parameter of ::LV_EVENT_HIT_TEST to check if an `point` can click the object or not.
 * `res` should be set like this:
 *   - If already set to `false` another event wants that point non clickable. If you want to respect it leave it as `false` or set `true` to overwrite it.
 *   - If already set `true` and `point` shouldn't be clickable set to `false`
 *   - If already set to `true` you agree that `point` can click the object leave it as `true`
 */
typedef struct {
    const lv_point_t * point;   /**< A point relative to screen to check if it can click the object or not*/
    bool res;                   /**< true: `point` can click the object; false: it cannot*/
} lv_hit_test_info_t;

/** Cover check results.*/
typedef enum {
    LV_COVER_RES_COVER      = 0,
    LV_COVER_RES_NOT_COVER  = 1,
    LV_COVER_RES_MASKED     = 2,
} lv_cover_res_t;

/**
 * Used as the event parameter of ::LV_EVENT_COVER_CHECK to check if an area is covered by the object or not.
 * In the event use `const lv_area_t * area = lv_event_get_cover_area(e)` to get the area to check
 * and `lv_event_set_cover_res(e, res)` to set the result.
 */
typedef struct {
    lv_cover_res_t res;
    const lv_area_t * area;
} lv_cover_check_info_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 向对象发送事件
 * @param obj           pointer to an object
 * @param event_code    the type of the event from `lv_event_t`
 * @param param         arbitrary data depending on the widget type and the event. (Usually `NULL`)
 * @return LV_RESULT_OK: `obj` was not deleted in the event; LV_RESULT_INVALID: `obj` was deleted in the event_code
 */
lv_result_t lv_obj_send_event(lv_obj_t * obj, lv_event_code_t event_code, void * param);

/**
 * 由小部件内部使用，以调用祖先小部件类型的事件处理程序
 * @param class_p   pointer to the class of the widget (NOT the ancestor class)
 * @param e         pointer to the event descriptor
 * @return          LV_RESULT_OK: the target object was not deleted in the event; LV_RESULT_INVALID: it was deleted in the event_code
 */
lv_result_t lv_obj_event_base(const lv_obj_class_t * class_p, lv_event_t * e);

/**
 * 获取事件的当前目标。它是被调用事件处理程序的对象。
 * If the event is not bubbled it's the same as "original" target.
 * @param e     pointer to the event descriptor
 * @return      the target of the event_code
 */
lv_obj_t * lv_event_get_current_target_obj(lv_event_t * e);

/**
 * 获取事件最初的目标对象。即使事件是冒泡的，情况也是一样的。
 * @param e     pointer to the event descriptor
 * @return      pointer to the original target of the event_code
 */
lv_obj_t * lv_event_get_target_obj(lv_event_t * e);

/**
 * 为对象添加事件处理程序函数。
 * 用户用于对对象发生的事件做出反应。
 * 一个对象可以有多个事件处理程序。它们将按照添加时的顺序被调用。
 * @param obj       指向对象的指针
 * @param filter    应调用事件的事件代码（例如“LV_event_CLICKED”）`LV_EVENT_ALL`可用于接收所有事件。
 * @param event_cb  新的事件功能
 * @param           user_data 自定义数据将在`event_cb中可用`
 * @return          事件的处理程序。它可以在`lv_obj_remove_event_dsc`中使用。
 */
lv_event_dsc_t * lv_obj_add_event_cb(lv_obj_t * obj, lv_event_cb_t event_cb, lv_event_code_t filter, void * user_data);

uint32_t lv_obj_get_event_count(lv_obj_t * obj);

lv_event_dsc_t * lv_obj_get_event_dsc(lv_obj_t * obj, uint32_t index);

bool lv_obj_remove_event(lv_obj_t * obj, uint32_t index);

bool lv_obj_remove_event_cb(lv_obj_t * obj, lv_event_cb_t event_cb);

bool lv_obj_remove_event_dsc(lv_obj_t * obj, lv_event_dsc_t * dsc);

/**
 * 删除带有user_data的event_cb
 * @param obj           pointer to a obj
 * @param event_cb      the event_cb of the event to remove
 * @param user_data     user_data
 * @return              the count of the event removed
 */
uint32_t lv_obj_remove_event_cb_with_user_data(lv_obj_t * obj, lv_event_cb_t event_cb, void * user_data);

/**
 * Get the input device passed as parameter to indev related events.
 * @param e     pointer to an event
 * @return      the indev that triggered the event or NULL if called on a not indev related event
 */
lv_indev_t * lv_event_get_indev(lv_event_t * e);

/**
 * Get the draw context which should be the first parameter of the draw functions.
 * Namely: `LV_EVENT_DRAW_MAIN/POST`, `LV_EVENT_DRAW_MAIN/POST_BEGIN`, `LV_EVENT_DRAW_MAIN/POST_END`
 * @param e     pointer to an event
 * @return      pointer to a draw context or NULL if called on an unrelated event
 */
lv_layer_t * lv_event_get_layer(lv_event_t * e);

/**
 * Get the old area of the object before its size was changed. Can be used in `LV_EVENT_SIZE_CHANGED`
 * @param e     pointer to an event
 * @return      the old absolute area of the object or NULL if called on an unrelated event
 */
const lv_area_t * lv_event_get_old_size(lv_event_t * e);

/**
 * Get the key passed as parameter to an event. Can be used in `LV_EVENT_KEY`
 * @param e     pointer to an event
 * @return      the triggering key or NULL if called on an unrelated event
 */
uint32_t lv_event_get_key(lv_event_t * e);

/**
 * Get the signed rotary encoder diff. passed as parameter to an event. Can be used in `LV_EVENT_ROTARY`
 * @param e     pointer to an event
 * @return      the triggering key or NULL if called on an unrelated event
 */
int32_t lv_event_get_rotary_diff(lv_event_t * e);

/**
 * Get the animation descriptor of a scrolling. Can be used in `LV_EVENT_SCROLL_BEGIN`
 * @param e     pointer to an event
 * @return      the animation that will scroll the object. (can be modified as required)
 */
lv_anim_t * lv_event_get_scroll_anim(lv_event_t * e);

/**
 * Set the new extra draw size. Can be used in `LV_EVENT_REFR_EXT_DRAW_SIZE`
 * @param e     pointer to an event
 * @param size  The new extra draw size
 */
void lv_event_set_ext_draw_size(lv_event_t * e, int32_t size);

/**
 * Get a pointer to an `lv_point_t` variable in which the self size should be saved (width in `point->x` and height `point->y`).
 * Can be used in `LV_EVENT_GET_SELF_SIZE`
 * @param e     pointer to an event
 * @return      pointer to `lv_point_t` or NULL if called on an unrelated event
 */
lv_point_t * lv_event_get_self_size_info(lv_event_t * e);

/**
 * Get a pointer to an `lv_hit_test_info_t` variable in which the hit test result should be saved. Can be used in `LV_EVENT_HIT_TEST`
 * @param e     pointer to an event
 * @return      pointer to `lv_hit_test_info_t` or NULL if called on an unrelated event
 */
lv_hit_test_info_t * lv_event_get_hit_test_info(lv_event_t * e);

/**
 * Get a pointer to an area which should be examined whether the object fully covers it or not.
 * Can be used in `LV_EVENT_HIT_TEST`
 * @param e     pointer to an event
 * @return      an area with absolute coordinates to check
 */
const lv_area_t * lv_event_get_cover_area(lv_event_t * e);

/**
 * Set the result of cover checking. Can be used in `LV_EVENT_COVER_CHECK`
 * @param e     pointer to an event
 * @param res   an element of ::lv_cover_check_info_t
 */
void lv_event_set_cover_res(lv_event_t * e, lv_cover_res_t res);

/**
 * Get the draw task which was just added.
 * Can be used in `LV_EVENT_DRAW_TASK_ADDED event`
 * @param e     pointer to an event
 * @return      the added draw task
 */
lv_draw_task_t * lv_event_get_draw_task(lv_event_t * e);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ_EVENT_H*/
