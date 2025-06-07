/**
 * @file lv_timer.h
 */

#ifndef LV_TIMER_H
#define LV_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf_internal.h"
#include "../tick/lv_tick.h"
#include "lv_types.h"
#include "lv_ll.h"

/*********************
 *      DEFINES
 *********************/
#ifndef LV_ATTRIBUTE_TIMER_HANDLER
#define LV_ATTRIBUTE_TIMER_HANDLER
#endif

#define LV_NO_TIMER_READY 0xFFFFFFFF

/**********************
 *      TYPEDEFS
 **********************/

/**
 * Timers execute this type of functions.
 */
typedef void (*lv_timer_cb_t)(lv_timer_t *);

/**
 * Timer handler resume this type of function.
 */
typedef void (*lv_timer_handler_resume_cb_t)(void * data);

/**
 * Descriptor of a lv_timer
 */
struct _lv_timer_t {
    uint32_t period; /**< How often the timer should run*/
    uint32_t last_run; /**< Last time the timer ran*/
    lv_timer_cb_t timer_cb; /**< Timer function*/
    void * user_data; /**< Custom user data*/
    int32_t repeat_count; /**< 1: One time;  -1 : infinity;  n>0: residual times*/
    uint32_t paused : 1;
    uint32_t auto_delete : 1;
};

typedef struct {
    lv_ll_t timer_ll; /*Linked list to store the lv_timers*/

    bool lv_timer_run;
    uint8_t idle_last;
    bool timer_deleted;
    bool timer_created;
    uint32_t timer_time_until_next;

    bool already_running;
    uint32_t periodic_last_tick;
    uint32_t busy_time;
    uint32_t idle_period_start;
    uint32_t run_cnt;

    lv_timer_handler_resume_cb_t resume_cb;
    void * resume_data;
} lv_timer_state_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init the lv_timer module
 */
void _lv_timer_core_init(void);

/**
 * Deinit the lv_timer module
 */
void _lv_timer_core_deinit(void);

//! @cond Doxygen_Suppress

/**
 * Call it periodically to handle lv_timers.
 * @return time till it needs to be run next (in ms)
 */
LV_ATTRIBUTE_TIMER_HANDLER uint32_t lv_timer_handler(void);

//! @endcond

/**
 * Call it in the super-loop of main() or threads. It will run lv_timer_handler()
 * with a given period in ms. You can use it with sleep or delay in OS environment.
 * This function is used to simplify the porting.
 * @param period the period for running lv_timer_handler()
 * @return the time after which it must be called again
 */
static inline LV_ATTRIBUTE_TIMER_HANDLER uint32_t lv_timer_handler_run_in_period(uint32_t period)
{
    static uint32_t last_tick = 0;

    if(lv_tick_elaps(last_tick) >= period) {
        last_tick = lv_tick_get();
        return lv_timer_handler();
    }
    return 1;
}

/**
 * Call it in the super-loop of main() or threads. It will automatically call lv_timer_handler() at the right time.
 * This function is used to simplify the porting.
 */
LV_ATTRIBUTE_TIMER_HANDLER void lv_timer_periodic_handler(void);

/**
 * 将恢复回调设置为计时器处理程序
 * @param cb the function to call when timer handler is resumed
 * @param data pointer to a resume data
 */
void lv_timer_handler_set_resume_cb(lv_timer_handler_resume_cb_t cb, void * data);

/**
 * 创建一个“空”计时器。它需要至少用初始化
 * `lv_timer_set_cb` and `lv_timer_set_period`
 * @return pointer to the created timer
 */
lv_timer_t * lv_timer_create_basic(void);

/**
 * 创建新的lv_timer
 * @param timer_xcb 定期呼叫的回拨。
 *                 （参数名称中的“x”表示它不是一个完全泛型的函数，因为它不遵循“func_name（object，callback，…）”约定）
 * @param period 呼叫周期，单位为毫秒
 * @param user_data 自定义参数
 * @return 指向新计时器的指针
 */
lv_timer_t * lv_timer_create(lv_timer_cb_t timer_xcb, uint32_t period, void * user_data);

/**
 * Delete a lv_timer
 * @param timer pointer to an lv_timer
 */
void lv_timer_delete(lv_timer_t * timer);

/**
 * 暂停计时器。
 * @param timer pointer to an lv_timer
 */
void lv_timer_pause(lv_timer_t * timer);

/**
 * Resume a timer.
 * @param timer pointer to an lv_timer
 */
void lv_timer_resume(lv_timer_t * timer);

/**
 * Set the callback to the timer (the function to call periodically)
 * @param timer pointer to a timer
 * @param timer_cb the function to call periodically
 */
void lv_timer_set_cb(lv_timer_t * timer, lv_timer_cb_t timer_cb);

/**
 * 为lv_timer设置新周期
 * @param timer pointer to a lv_timer
 * @param period the new period
 */
void lv_timer_set_period(lv_timer_t * timer, uint32_t period);

/**
 * 准备一个lv_timer。它不会等待它的期限。
 * @param timer pointer to a lv_timer.
 */
void lv_timer_ready(lv_timer_t * timer);

/**
 * 设置计时器重复的次数。
 * @param timer 指向lv_timer的指针。
 * @param repeat_count -1：无穷大；0：停止；n> 0：剩余时间
 */
void lv_timer_set_repeat_count(lv_timer_t * timer, int32_t repeat_count);

/**
 *设置在调用“repeat_count”次时是否自动删除lv_timer。
 *@param timer指向lv_timer的指针。
 *@param auto_delete true:自动删除；false：当调用“repeat_count”次时，计时器将暂停。
 */
void lv_timer_set_auto_delete(lv_timer_t * timer, bool auto_delete);

/**
 * Set custom parameter to the lv_timer.
 * @param timer pointer to a lv_timer.
 * @param user_data custom parameter
 */
void lv_timer_set_user_data(lv_timer_t * timer, void * user_data);

/**
 * 重置lv_timer。
 * 它将在毫秒后被称为先前设置的时段。
 * @param timer pointer to a lv_timer.
 */
void lv_timer_reset(lv_timer_t * timer);

/**
 * 启用或禁用整个lv_timer处理
 * @param en true:lv_timer处理正在运行，false:lvtimer处理已暂停
 */
void lv_timer_enable(bool en);

/**
 * Get idle percentage
 * @return the lv_timer idle in percentage
 */
uint32_t lv_timer_get_idle(void);

/**
 * Get the time remaining until the next timer will run
 * @return the time remaining in ms
 */
uint32_t lv_timer_get_time_until_next(void);

/**
 * Iterate through the timers
 * @param timer NULL to start iteration or the previous return value to get the next timer
 * @return the next timer or NULL if there is no more timer
 */
lv_timer_t * lv_timer_get_next(lv_timer_t * timer);

/**
 * Get the user_data passed when the timer was created
 * @param timer pointer to the lv_timer
 * @return pointer to the user_data
 */
static inline void * lv_timer_get_user_data(lv_timer_t * timer)
{
    return timer->user_data;
}

/**
 * Get the pause state of a timer
 * @param timer pointer to a lv_timer
 * @return true: timer is paused; false: timer is running
 */
static inline bool lv_timer_get_paused(lv_timer_t * timer)
{
    return timer->paused;
}

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
