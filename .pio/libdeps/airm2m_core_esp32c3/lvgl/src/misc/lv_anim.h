/**
 * @file lv_anim.h
 *
 */

#ifndef LV_ANIM_H
#define LV_ANIM_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf_internal.h"
#include "lv_types.h"
#include "lv_math.h"
#include "lv_timer.h"
#include "lv_ll.h"

/*********************
 *      DEFINES
 *********************/

#define LV_ANIM_REPEAT_INFINITE      0xFFFFFFFF
#define LV_ANIM_PLAYTIME_INFINITE    0xFFFFFFFF

/*
 * Macros used to set cubic-bezier anim parameter.
 * Parameters come from https://easings.net/
 *
 * Usage:
 *
 * lv_anim_t a;
 * lv_anim_init(&a);
 * ...
 * lv_anim_set_path_cb(&a, lv_anim_path_custom_bezier3);
 * LV_ANIM_SET_EASE_IN_SINE(&a); //Set cubic-bezier anim parameter to easeInSine
 * ...
 * lv_anim_start(&a);
 */

#define _PARA(a, x1, y1, x2, y2) ((a)->parameter.bezier3 =                                  \
(struct _lv_anim_bezier3_para_t) {                      \
    LV_BEZIER_VAL_FLOAT(x1), LV_BEZIER_VAL_FLOAT(y1),   \
    LV_BEZIER_VAL_FLOAT(x2), LV_BEZIER_VAL_FLOAT(y2) }  \
                                 )

#define LV_ANIM_SET_EASE_IN_SINE(a) _PARA(a, 0.12, 0, 0.39, 0)
#define LV_ANIM_SET_EASE_OUT_SINE(a) _PARA(a, 0.61, 1, 0.88, 1)
#define LV_ANIM_SET_EASE_IN_OUT_SINE(a) _PARA(a, 0.37, 0, 0.63, 1)
#define LV_ANIM_SET_EASE_IN_QUAD(a) _PARA(a, 0.11, 0, 0.5, 0)
#define LV_ANIM_SET_EASE_OUT_QUAD(a) _PARA(a, 0.5, 1, 0.89, 1)
#define LV_ANIM_SET_EASE_IN_OUT_QUAD(a) _PARA(a, 0.45, 0, 0.55, 1)
#define LV_ANIM_SET_EASE_IN_CUBIC(a) _PARA(a, 0.32, 0, 0.67, 0)
#define LV_ANIM_SET_EASE_OUT_CUBIC(a) _PARA(a, 0.33, 1, 0.68, 1)
#define LV_ANIM_SET_EASE_IN_OUT_CUBIC(a) _PARA(a, 0.65, 0, 0.35, 1)
#define LV_ANIM_SET_EASE_IN_QUART(a) _PARA(a, 0.5, 0, 0.75, 0)
#define LV_ANIM_SET_EASE_OUT_QUART(a) _PARA(a, 0.25, 1, 0.5, 1)
#define LV_ANIM_SET_EASE_IN_OUT_QUART(a) _PARA(a, 0.76, 0, 0.24, 1)
#define LV_ANIM_SET_EASE_IN_QUINT(a) _PARA(a, 0.64, 0, 0.78, 0)
#define LV_ANIM_SET_EASE_OUT_QUINT(a) _PARA(a, 0.22, 1, 0.36, 1)
#define LV_ANIM_SET_EASE_IN_OUT_QUINT(a) _PARA(a, 0.83, 0, 0.17, 1)
#define LV_ANIM_SET_EASE_IN_EXPO(a) _PARA(a, 0.7, 0, 0.84, 0)
#define LV_ANIM_SET_EASE_OUT_EXPO(a) _PARA(a, 0.16, 1, 0.3, 1)
#define LV_ANIM_SET_EASE_IN_OUT_EXPO(a) _PARA(a, 0.87, 0, 0.13, 1)
#define LV_ANIM_SET_EASE_IN_CIRC(a) _PARA(a, 0.55, 0, 1, 0.45)
#define LV_ANIM_SET_EASE_OUT_CIRC(a) _PARA(a, 0, 0.55, 0.45, 1)
#define LV_ANIM_SET_EASE_IN_OUT_CIRC(a) _PARA(a, 0.85, 0, 0.15, 1)
#define LV_ANIM_SET_EASE_IN_BACK(a) _PARA(a, 0.36, 0, 0.66, -0.56)
#define LV_ANIM_SET_EASE_OUT_BACK(a) _PARA(a, 0.34, 1.56, 0.64, 1)
#define LV_ANIM_SET_EASE_IN_OUT_BACK(a) _PARA(a, 0.68, -0.6, 0.32, 1.6)

LV_EXPORT_CONST_INT(LV_ANIM_REPEAT_INFINITE);
LV_EXPORT_CONST_INT(LV_ANIM_PLAYTIME_INFINITE);

/**********************
 *      TYPEDEFS
 **********************/

/** Can be used to indicate if animations are enabled or disabled in a case*/
typedef enum {
    LV_ANIM_OFF,
    LV_ANIM_ON,
} lv_anim_enable_t;

typedef struct {
    bool anim_list_changed;
    bool anim_run_round;
    lv_timer_t * timer;
    lv_ll_t anim_ll;
} lv_anim_state_t;

/** Get the current value during an animation*/
typedef int32_t (*lv_anim_path_cb_t)(const lv_anim_t *);

/** Generic prototype of "animator" functions.
 * First parameter is the variable to animate.
 * Second parameter is the value to set.
 * Compatible with `lv_xxx_set_yyy(obj, value)` functions
 * The `x` in `_xcb_t` means it's not a fully generic prototype because
 * it doesn't receive `lv_anim_t *` as its first argument*/
typedef void (*lv_anim_exec_xcb_t)(void *, int32_t);

/** Same as `lv_anim_exec_xcb_t` but receives `lv_anim_t *` as the first parameter.
 * It's more consistent but less convenient. Might be used by binding generator functions.*/
typedef void (*lv_anim_custom_exec_cb_t)(lv_anim_t *, int32_t);

/** Callback to call when the animation is ready*/
typedef void (*lv_anim_completed_cb_t)(lv_anim_t *);

/** Callback to call when the animation really stars (considering `delay`)*/
typedef void (*lv_anim_start_cb_t)(lv_anim_t *);

/** Callback used when the animation values are relative to get the current value*/
typedef int32_t (*lv_anim_get_value_cb_t)(lv_anim_t *);

/** Callback used when the animation is deleted*/
typedef void (*lv_anim_deleted_cb_t)(lv_anim_t *);

typedef struct _lv_anim_bezier3_para_t {
    int16_t x1;
    int16_t y1;
    int16_t x2;
    int16_t y2;
} lv_anim_bezier3_para_t; /**< Parameter used when path is custom_bezier*/

/** Describes an animation*/
struct _lv_anim_t {
    void * var;                                 /**<Variable to animate*/
    lv_anim_exec_xcb_t exec_cb;                 /**< Function to execute to animate*/
    lv_anim_custom_exec_cb_t custom_exec_cb;/**< Function to execute to animate,
                                                 same purpose as exec_cb but different parameters*/
    lv_anim_start_cb_t start_cb;         /**< Call it when the animation is starts (considering `delay`)*/
    lv_anim_completed_cb_t completed_cb; /**< Call it when the animation is fully completed*/
    lv_anim_deleted_cb_t deleted_cb;     /**< Call it when the animation is deleted*/
    lv_anim_get_value_cb_t get_value_cb; /**< Get the current value in relative mode*/
    void * user_data;                    /**< Custom user data*/
    lv_anim_path_cb_t path_cb;         /**< Describe the path (curve) of animations*/
    int32_t start_value;               /**< Start value*/
    int32_t current_value;             /**< Current value*/
    int32_t end_value;                 /**< End value*/
    int32_t duration;                /**< Animation time in ms*/
    int32_t act_time;            /**< Current time in animation. Set to negative to make delay.*/
    uint32_t playback_delay;     /**< Wait before play back*/
    uint32_t playback_duration;      /**< Duration of playback animation*/
    uint32_t repeat_delay;       /**< Wait before repeat*/
    uint32_t repeat_cnt;         /**< Repeat count for the animation*/
    union _lv_anim_path_para_t {
        lv_anim_bezier3_para_t bezier3; /**< Parameter used when path is custom_bezier*/
    } parameter;

    /*Animation system use these - user shouldn't set*/
    uint32_t last_timer_run;
    uint8_t playback_now : 1; /**< Play back is in progress*/
    uint8_t run_round : 1;    /**< Indicates the animation has run in this round*/
    uint8_t start_cb_called : 1;    /**< Indicates that the `start_cb` was already called*/
    uint8_t early_apply  : 1;    /**< 1: Apply start value immediately even is there is `delay`*/
};

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
* 初始化动画模块
*/
void _lv_anim_core_init(void);

/**
*取消动画模块的单元
 */
void _lv_anim_core_deinit(void);

/**
* 初始化动画变量。
* 例如：
* lv_anim_t a；
* lv_anim_init（/a）；
* lv_anim_set_...。一
* lv_anim_start（/a）；
* @param 指向要初始化的“lv_anim_t”变量的指针
*/
void lv_anim_init(lv_anim_t * a);

/**
 * 设置需要动画的对象
 * @param 指向初始化的“lv_anim_t”变量的指针
 * @param var 指向要设置动画的变量的指针
 */
static inline void lv_anim_set_var(lv_anim_t * a, void * var)
{
    a->var = var;
}

/**
* 设置要设置动画的函数`var`
* @param 指向初始化的“lv_anim_t”变量的指针
* @param exec_cb 动画期间要执行的函数
* 可以使用LVGL的内置功能。
* 例如lv_obj_set_x
*/
static inline void lv_anim_set_exec_cb(lv_anim_t * a, lv_anim_exec_xcb_t exec_cb)
{
    a->exec_cb = exec_cb;
}

/**
 * 设置动画的持续时间
 * @param a         指向初始化的“lv_anim_t”变量的指针
 * @param duration  动画的持续时间（以毫秒为单位）
 */
static inline void lv_anim_set_duration(lv_anim_t * a, uint32_t duration)
{
    a->duration = duration;
}

/**
 * 旧版`lv_anim_set_time` API将很快被删除，请改用`lv_aim_set_duration`。
 */
static inline void lv_anim_set_time(lv_anim_t * a, uint32_t duration)
{
    lv_anim_set_duration(a, duration);
}

/**
 * 在开始动画之前设置延迟
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param delay     delay before the animation in milliseconds
 */
static inline void lv_anim_set_delay(lv_anim_t * a, uint32_t delay)
{
    a->act_time = -(int32_t)(delay);
}

/**
 * 设置动画的开始值和结束值
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param start     the start value
 * @param end       the end value
 */
static inline void lv_anim_set_values(lv_anim_t * a, int32_t start, int32_t end)
{
    a->start_value = start;
    a->current_value = INT32_MIN;
    a->end_value = end;
}

/**
 * 与“lv_anim_set_exec_cb”类似，但“lv_anm_customexec_cb_t”接收“lv_anim_t*”作为其第一个参数，
 * 而不是“void*”。
 *当LVGL绑定到其他语言时，可以使用此函数，因为将“lv_anim_t*”作为第一个参数更为一致。
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param exec_cb   a function to execute.
 */
static inline void lv_anim_set_custom_exec_cb(lv_anim_t * a, lv_anim_custom_exec_cb_t exec_cb)
{
    a->custom_exec_cb = exec_cb;
}

/**
 * 设置动画的路径（曲线）。
 * @param a         指向初始化的“lv_anim_t”变量的指针
 * @param path_cb 用于设置动画的当前值的函数。
 */
static inline void lv_anim_set_path_cb(lv_anim_t * a, lv_anim_path_cb_t path_cb)
{
    a->path_cb = path_cb;
}

/**
 * 在动画真正开始时设置函数调用（考虑“延迟”）
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param start_cb  a function call when the animation starts
 */
static inline void lv_anim_set_start_cb(lv_anim_t * a, lv_anim_start_cb_t start_cb)
{
    a->start_cb = start_cb;
}

/**
 * 设置一个函数以使用变量的当前值并设置开始值和结束值
 * relative to the returned current value.
 * @param a             pointer to an initialized `lv_anim_t` variable
 * @param get_value_cb  a function call when the animation starts
 */
static inline void lv_anim_set_get_value_cb(lv_anim_t * a, lv_anim_get_value_cb_t get_value_cb)
{
    a->get_value_cb = get_value_cb;
}

/**
 * 设置动画完成时的函数调用
 * @param a             指向初始化的“lv_anim_t”变量的指针
 * @param completed_cb  动画完全完成时的函数调用
 */
static inline void lv_anim_set_completed_cb(lv_anim_t * a, lv_anim_completed_cb_t completed_cb)
{
    a->completed_cb = completed_cb;
}

/**
 * 在删除动画时设置函数调用。
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param deleted_cb  a function call when the animation is deleted
 */
static inline void lv_anim_set_deleted_cb(lv_anim_t * a, lv_anim_deleted_cb_t deleted_cb)
{
    a->deleted_cb = deleted_cb;
}

/**
 * 使动画在前进方向准备就绪时播放
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param time      播放动画的持续时间（毫秒）。0：禁用播放
 */
static inline void lv_anim_set_playback_duration(lv_anim_t * a, uint32_t duration)
{
    a->playback_duration = duration;
}

/**
 * 旧版`lv_anim_set_playback_time` API将很快删除，请改用`lv_anim_set_playback_duration`。
 */
static inline void lv_anim_set_playback_time(lv_anim_t * a, uint32_t duration)
{
    lv_anim_set_playback_duration(a, duration);
}

/**
 * 使动画在前进方向准备就绪时播放
 * @param a         指向已初始化的`lv_anim_t`变量的指针
 * @param delay     开始播放动画之前的延迟（毫秒）。
 */
static inline void lv_anim_set_playback_delay(lv_anim_t * a, uint32_t delay)
{
    a->playback_delay = delay;
}

/**
 * 让动画自己重复。
 * @param a         指向已初始化的`lv_anim_t`变量的指针 
 * @param cnt       重复计数或“LV_ANIM_REPEAT_INFINITE”表示无限重复。0：禁用重复。
 */
static inline void lv_anim_set_repeat_count(lv_anim_t * a, uint32_t cnt)
{
    a->repeat_cnt = cnt;
}

/**
 * 在重复动画之前设置延迟。
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param delay     重复动画之前的延迟（毫秒）。
 */
static inline void lv_anim_set_repeat_delay(lv_anim_t * a, uint32_t delay)
{
    a->repeat_delay = delay;
}

/**
 * 设置动画是应立即应用还是仅在延迟到期时应用。
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param en        true: apply the start value immediately in `lv_anim_start`;
 *                  false: apply the start value only when `delay` ms is elapsed and the animations really starts
 */
static inline void lv_anim_set_early_apply(lv_anim_t * a, bool en)
{
    a->early_apply = en;
}

/**
 * 设置动画的自定义用户数据字段。
 * @param a           pointer to an initialized `lv_anim_t` variable
 * @param user_data   pointer to the new user_data.
 */
static inline void lv_anim_set_user_data(lv_anim_t * a, void * user_data)
{
    a->user_data = user_data;
}

/**
 * 设置三次贝塞尔路径的参数
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @param x1        first control point
 * @param y1
 * @param y1        second control point
 */
static inline void lv_anim_set_bezier3_param(lv_anim_t * a, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
{
    struct _lv_anim_bezier3_para_t * para = &a->parameter.bezier3;

    para->x1 = x1;
    para->x2 = x2;
    para->y1 = y1;
    para->y2 = y2;
}

/**
 * 创建动画
 * @param a         an initialized 'anim_t' variable. Not required after call.
 * @return          pointer to the created animation (different from the `a` parameter)
 */
lv_anim_t * lv_anim_start(const lv_anim_t * a);

/**
 * 在开始动画之前获得延迟
 * @param a pointer to an initialized `lv_anim_t` variable
 * @return delay before the animation in milliseconds
 */
static inline uint32_t lv_anim_get_delay(const lv_anim_t * a)
{
    return -a->act_time;
}

/**
 * 获取用于播放动画的时间。
 * @param a 指向动画的指针。
 * @return 播放时间（毫秒）。
 */
uint32_t lv_anim_get_playtime(const lv_anim_t * a);

/**
 * 获取动画的持续时间
 * @param a pointer to an initialized `lv_anim_t` variable
 * @return  the duration of the animation in milliseconds
 */
static inline uint32_t lv_anim_get_time(const lv_anim_t * a)
{
    return a->duration;
}

/**
 * 获取动画的重复次数。
 * @param a         pointer to an initialized `lv_anim_t` variable
 * @return the repeat count or `LV_ANIM_REPEAT_INFINITE` for infinite repetition. 0: disabled repetition.
 */
static inline uint32_t lv_anim_get_repeat_count(const lv_anim_t * a)
{
    return a->repeat_cnt;
}

/**
 * 获取动画的user_data字段
 * @param   a pointer to an initialized `lv_anim_t` variable
 * @return  the pointer to the custom user_data of the animation
 */
static inline void * lv_anim_get_user_data(const lv_anim_t * a)
{
    return a->user_data;
}

/**
 *使用给定的动画师函数删除变量的动画
 * @param var       pointer to variable
 * @param exec_cb   a function pointer which is animating 'var',
 *                  or NULL to ignore it and delete all the animations of 'var
 * @return          true: at least 1 animation is deleted, false: no animation is deleted
 */
bool lv_anim_delete(void * var, lv_anim_exec_xcb_t exec_cb);

/**
 * 删除所有动画
 */
void lv_anim_delete_all(void);

/**
 * 获取变量及其“exec_cb”的动画。
 * @param var       指向变量的指针
 * @param exec_cb   为“var”设置动画的函数指针，或返回第一个匹配的“var”的NULL
 * @return          指向动画的指针。
 */
lv_anim_t * lv_anim_get(void * var, lv_anim_exec_xcb_t exec_cb);

/**
 * Get global animation refresher timer. 获取全局动画复习计时器。
 * @return 指向动画刷新定时器的指针。
 */
lv_timer_t * lv_anim_get_timer(void);

/**
 * 通过从“a”中获取动画变量来删除动画。
 * 只有带有`exec_cb`的动画才会被删除。
 * This function exists because it's logical that all anim. functions receives an
 * `lv_anim_t` as their first parameter. It's not practical in C but might make
 * the API more consequent and makes easier to generate bindings.
 * @param a         pointer to an animation.
 * @param exec_cb   a function pointer which is animating 'var',
 *                  or NULL to ignore it and delete all the animations of 'var
 * @return          true: at least 1 animation is deleted, false: no animation is deleted
 */
static inline bool lv_anim_custom_delete(lv_anim_t * a, lv_anim_custom_exec_cb_t exec_cb)
{
    return lv_anim_delete(a ? a->var : NULL, (lv_anim_exec_xcb_t)exec_cb);
}

/**
 * 获取变量及其`exec_cb`的动画。
 * 这个函数之所以存在，是因为所有动画都是合乎逻辑的。函数接收“lv_anim_t”作为其第一个参数。
 * 它在C中不实用，但可能会使API更具结果性，并更容易生成绑定。
 * @param a         pointer to an animation.
 * @param exec_cb   a function pointer which is animating 'var', or NULL to return first matching 'var'
 * @return          pointer to the animation.
 */
static inline lv_anim_t * lv_anim_custom_get(lv_anim_t * a, lv_anim_custom_exec_cb_t exec_cb)
{
    return lv_anim_get(a ? a->var : NULL, (lv_anim_exec_xcb_t)exec_cb);
}

/**
 * 获取当前正在运行的动画数量
 * @return      运行动画的数量
 */
uint16_t lv_anim_count_running(void);

/**
 * 将速度存储为一个特殊值，可以在动画中用作时间。
 * 它将根据开始和结束值在内部转换为时间
 * @param speed         the speed of the animation in with unit / sec resolution in 0..10k range
 * @return              a special value which can be used as an animation time
 */
uint32_t lv_anim_speed(uint32_t speed);

/**
 * 将速度存储为一个特殊值，可以在动画中用作时间。
 * 它将根据开始和结束值在内部转换为时间
 * @param speed         the speed of the animation in as unit / sec resolution in 0..10k range
 * @param min_time      the minimum time in 0..10k range
 * @param max_time      the maximum time in 0..10k range
 * @return              a special value in where all three values are stored and can be used as an animation time
 * @note                internally speed is stored as 10 unit/sec
 * @note                internally min/max_time are stored with 10 ms unit
 *
 */
uint32_t lv_anim_speed_clamped(uint32_t speed, uint32_t min_time, uint32_t max_time);

/**
 * 手动刷新动画的状态。
 * Useful to make the animations running in a blocking process where
 * `lv_timer_handler` can't run for a while.
 * Shouldn't be used directly because it is called in `lv_refr_now()`.
 */
void lv_anim_refr_now(void);

/**
 * 计算应用线性特征的动画的当前值
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_linear(const lv_anim_t * a);

/**
 * 计算减缓开始阶段的动画的当前值
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_ease_in(const lv_anim_t * a);

/**
 * 计算减缓结束阶段的动画的当前值
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_ease_out(const lv_anim_t * a);

/**
 * 应用“S”特性（余弦）计算动画的当前值
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_ease_in_out(const lv_anim_t * a);

/**
 * 计算结尾有过冲的动画的当前值
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_overshoot(const lv_anim_t * a);

/**
 * 计算具有3次反弹的动画的当前值
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_bounce(const lv_anim_t * a);

/**
 * 计算应用步长特征的动画的当前值。
 * (Set end value on the end of the animation)
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_step(const lv_anim_t * a);

/**
 * 自定义立方体贝塞尔动画路径，需要在->参数中指定立方体参数。贝塞尔3
 * @param a     pointer to an animation
 * @return      the current value to set
 */
int32_t lv_anim_path_custom_bezier3(const lv_anim_t * a);

/**********************
 *   GLOBAL VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_ANIM_H*/
