/**
 * @file lv_event.h
 *
 */

#ifndef LV_EVENT_H
#define LV_EVENT_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lv_types.h"
#include "../lv_conf_internal.h"

#include "lv_array.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef void (*lv_event_cb_t)(lv_event_t * e);

typedef struct {
    lv_event_cb_t cb;
    void * user_data;
    uint32_t filter;
} lv_event_dsc_t;

/**
 * Type of event being sent to the object.
 */
typedef enum
{
    LV_EVENT_ALL = 0,

    /** 输入设备事件*/
    LV_EVENT_PRESSED,             /**< 对象已被按下*/
    LV_EVENT_PRESSING,            /**< 对象正在被按下（按下时持续调用）*/
    LV_EVENT_PRESS_LOST,          /**< 对象仍被按下,但光标/手指已从对象上滑出 */
    LV_EVENT_SHORT_CLICKED,       /**< 对象被按下一小段时间,然后松开。如果滚动则不调用。*/
    LV_EVENT_LONG_PRESSED,        /**< 对象已被按下至少 `long_press_time`。如果滚动则不调用。*/
    LV_EVENT_LONG_PRESSED_REPEAT, /**< 在每个 `long_press_repeat_time` 毫秒的 `long_press_time` 之后调用。如果滚动则不调用。*/
    LV_EVENT_CLICKED,             /**< 如果未滚动则在释放时调用（无论长按与否）*/
    LV_EVENT_RELEASED,            /**< 在任何情况下,当对象被释放时调用*/
    LV_EVENT_SCROLL_BEGIN,        /**< 滚动开始。事件参数是指向滚动动画的指针。可以修改*/
    LV_EVENT_SCROLL_THROW_BEGIN, // 滚动 投掷 开始？
    LV_EVENT_SCROLL_END,  /**< 滚动结束*/
    LV_EVENT_SCROLL,      /**< 滚动*/
    LV_EVENT_GESTURE,     /**< 检测到手势。使用 `lv_indev_get_gesture_dir(lv_indev_active());` 获取手势 */
    LV_EVENT_KEY,         /**< 向对象发送了一个键。使用 `lv_indev_get_key(lv_indev_active());` 获取该键*/
    LV_EVENT_ROTARY,      /**< 编码器或滚轮已旋转。使用 `lv_event_get_rotary_diff(e);` 获取旋转计数*/
    LV_EVENT_FOCUSED,     /**< 对象已聚焦*/
    LV_EVENT_DEFOCUSED,   /**< 对象已失焦*/
    LV_EVENT_LEAVE,       /**< 对象已失焦但仍处于选中状态*/
    LV_EVENT_HIT_TEST,    /**< 执行高级命中测试*/
    LV_EVENT_INDEV_RESET, /**< Indev 已重置*/
    LV_EVENT_HOVER_OVER,  /**< Indev 悬停在对象上*/
    LV_EVENT_HOVER_LEAVE, /**< Indev 悬停离开对象*/

    /** Drawing events*/
    LV_EVENT_COVER_CHECK,        /** 23 <检查对象是否完全覆盖某个区域。事件参数为`lv_cover_check_info_t*`*/
    LV_EVENT_REFR_EXT_DRAW_SIZE, /** 24 <在对象周围获得所需的额外绘制区域（例如阴影）。事件参数为“int32_t*”以存储大小*/
    LV_EVENT_DRAW_MAIN_BEGIN,    /** 25 <开始主绘图阶段*/
    LV_EVENT_DRAW_MAIN,          /** 26 <执行主绘图*/
    LV_EVENT_DRAW_MAIN_END,      /** 27 <完成主绘图阶段*/
    LV_EVENT_DRAW_POST_BEGIN,    /** 28 <开始绘制后阶段（绘制所有子项时）*/
    LV_EVENT_DRAW_POST,          /** 29 <执行绘制后阶段（绘制所有子项时）*/
    LV_EVENT_DRAW_POST_END,      /** 30 <完成绘制后阶段（绘制所有子项时）*/
    LV_EVENT_DRAW_TASK_ADDED,    /** 31 <添加绘图任务*/

    /**特殊活动*/
    LV_EVENT_VALUE_CHANGED, /**<对象的值已更改（即滑块已移动）*/
    LV_EVENT_INSERT,        /**<将文本插入到对象中。正在插入事件数据“char*”*/
    LV_EVENT_REFRESH,       /**<通知对象刷新上面的内容（为用户）*/
    LV_EVENT_READY,         /**<进程已完成*/
    LV_EVENT_CANCEL,        /**<进程已取消*/

    /** Other events*/
    LV_EVENT_CREATE,              /**< 37 正在创建对象*/ 
    LV_EVENT_DELETE,              /**< 38 正在删除对象*/
    LV_EVENT_CHILD_CHANGED,       /**< 39 子项已删除、添加，或其大小、位置已更改 */
    LV_EVENT_CHILD_CREATED,       /**< 40 孩子是被创造出来的，总是向所有的父母冒泡*/
    LV_EVENT_CHILD_DELETED,       /**< 41 孩子被删除了，总是向所有家长冒泡*/
    LV_EVENT_SCREEN_UNLOAD_START, /**< 42 屏幕卸载开始，调用scr_load时立即启动*/
    LV_EVENT_SCREEN_LOAD_START,   /**< 43 屏幕加载已启动，当屏幕更改延迟到期时激发*/
    LV_EVENT_SCREEN_LOADED,       /**< 44 已加载屏幕*/
    LV_EVENT_SCREEN_UNLOADED,     /**< 45 屏幕已卸载*/
    LV_EVENT_SIZE_CHANGED,        /**< 46 对象坐标/大小已更改*/
    LV_EVENT_STYLE_CHANGED,       /**< 47 对象的样式已更改*/
    LV_EVENT_LAYOUT_CHANGED,      /**< 48 由于布局重新计算，子级位置已更改*/
    LV_EVENT_GET_SELF_SIZE,       /**< 49 获取小部件的内部大小*/

    /** 可选LVGL组件事件*/
    LV_EVENT_INVALIDATE_AREA,
    LV_EVENT_RESOLUTION_CHANGED,
    LV_EVENT_COLOR_FORMAT_CHANGED,
    LV_EVENT_REFR_REQUEST,
    LV_EVENT_REFR_START,
    LV_EVENT_REFR_READY,
    LV_EVENT_RENDER_START,
    LV_EVENT_RENDER_READY,
    LV_EVENT_FLUSH_START,
    LV_EVENT_FLUSH_FINISH,
    LV_EVENT_FLUSH_WAIT_START,
    LV_EVENT_FLUSH_WAIT_FINISH,

    LV_EVENT_VSYNC,

    _LV_EVENT_LAST, /** Number of default events*/

    LV_EVENT_PREPROCESS = 0x8000, /** This is a flag that can be set with an event so it's processed
                                    before the class default event processing */
} lv_event_code_t;

typedef lv_array_t lv_event_list_t;

struct _lv_event_t {
    void * current_target;
    void * original_target;
    lv_event_code_t code;
    void * user_data;
    void * param;
    lv_event_t * prev;
    uint8_t deleted : 1;
    uint8_t stop_processing : 1;
    uint8_t stop_bubbling : 1;
};

/**
 * @brief Event callback.
 * Events are used to notify the user of some action being taken on the object.
 * For details, see ::lv_event_t.
 */

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void _lv_event_push(lv_event_t * e);

void _lv_event_pop(lv_event_t * e);

lv_result_t lv_event_send(lv_event_list_t * list, lv_event_t * e, bool preprocess);

lv_event_dsc_t * lv_event_add(lv_event_list_t * list, lv_event_cb_t cb, lv_event_code_t filter, void * user_data);
bool lv_event_remove_dsc(lv_event_list_t * list, lv_event_dsc_t * dsc);

uint32_t lv_event_get_count(lv_event_list_t * list);

lv_event_dsc_t * lv_event_get_dsc(lv_event_list_t * list, uint32_t index);

lv_event_cb_t lv_event_dsc_get_cb(lv_event_dsc_t * dsc);

void * lv_event_dsc_get_user_data(lv_event_dsc_t * dsc);

bool lv_event_remove(lv_event_list_t * list, uint32_t index);

void lv_event_remove_all(lv_event_list_t * list);

/**
 * Get the object originally targeted by the event. It's the same even if the event is bubbled.
 * @param e     pointer to the event descriptor
 * @return      the target of the event_code
 */
void * lv_event_get_target(lv_event_t * e);

/**
 * Get the current target of the event. It's the object which event handler being called.
 * If the event is not bubbled it's the same as "normal" target.
 * @param e     pointer to the event descriptor
 * @return      pointer to the current target of the event_code
 */
void * lv_event_get_current_target(lv_event_t * e);

/**
 * Get the event code of an event
 * @param e     pointer to the event descriptor
 * @return      the event code. (E.g. `LV_EVENT_CLICKED`, `LV_EVENT_FOCUSED`, etc)
 */
lv_event_code_t lv_event_get_code(lv_event_t * e);

/**
 * Get the parameter passed when the event was sent
 * @param e     pointer to the event descriptor
 * @return      pointer to the parameter
 */
void * lv_event_get_param(lv_event_t * e);

/**
 * Get the user_data passed when the event was registered on the object
 * @param e     pointer to the event descriptor
 * @return      pointer to the user_data
 */
void * lv_event_get_user_data(lv_event_t * e);

/**
 * Stop the event from bubbling.
 * This is only valid when called in the middle of an event processing chain.
 * @param e     pointer to the event descriptor
 */
void lv_event_stop_bubbling(lv_event_t * e);

/**
 * Stop processing this event.
 * This is only valid when called in the middle of an event processing chain.
 * @param e     pointer to the event descriptor
 */
void lv_event_stop_processing(lv_event_t * e);

/**
 * Register a new, custom event ID.
 * It can be used the same way as e.g. `LV_EVENT_CLICKED` to send custom events
 * @return      the new event id
 * @example
 * uint32_t LV_EVENT_MINE = 0;
 * ...
 * e = lv_event_register_id();
 * ...
 * lv_obj_send_event(obj, LV_EVENT_MINE, &some_data);
 */
uint32_t lv_event_register_id(void);

/**
 * Nested events can be called and one of them might belong to an object that is being deleted.
 * Mark this object's `event_temp_data` deleted to know that its `lv_obj_send_event` should return `LV_RESULT_INVALID`
 * @param target     pointer to an event target which was deleted
 */
void _lv_event_mark_deleted(void * target);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_EVENT_H*/
