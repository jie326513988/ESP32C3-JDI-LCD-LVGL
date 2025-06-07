/**
 * @file lv_obj.h
 *
 */

#ifndef LV_OBJ_H
#define LV_OBJ_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf_internal.h"

#include "../misc/lv_types.h"
#include "../misc/lv_style.h"
#include "../misc/lv_area.h"
#include "../misc/lv_color.h"
#include "../misc/lv_assert.h"

#include "lv_obj_tree.h"
#include "lv_obj_pos.h"
#include "lv_obj_scroll.h"
#include "lv_obj_style.h"
#include "lv_obj_draw.h"
#include "lv_obj_class.h"
#include "lv_obj_event.h"
#include "lv_obj_property.h"
#include "lv_group.h"

    /*********************
     *      DEFINES
     *********************/

    /**********************
     *      TYPEDEFS
     **********************/

    /**
     * Possible states of a widget.
     * OR-ed values are possible
     */
    enum _lv_state_t
    {
        LV_STATE_DEFAULT = 0x0000,   // 正常，释放状态
        LV_STATE_CHECKED = 0x0001,   // 切换或检查状态
        LV_STATE_FOCUSED = 0x0002,   // 通过键盘或编码器聚焦或通过触摸板/鼠标点击
        LV_STATE_FOCUS_KEY = 0x0004, // 通过键盘或编码器聚焦，但不通过触摸板/鼠标聚焦
        LV_STATE_EDITED = 0x0008,    // 由编码器编辑
        LV_STATE_HOVERED = 0x0010,   // 鼠标悬停（现在不支持）
        LV_STATE_PRESSED = 0x0020,   // 被按下
        LV_STATE_SCROLLED = 0x0040,  // 正在滚动
        LV_STATE_DISABLED = 0x0080,  // 禁用状态
        LV_STATE_USER_1 = 0x1000,
        LV_STATE_USER_2 = 0x2000,
        LV_STATE_USER_3 = 0x4000,
        LV_STATE_USER_4 = 0x8000,

        LV_STATE_ANY = 0xFFFF, /**< 在某些函数中可以使用特殊值来针对所有状态*/
    };

    /**
     * The possible parts of widgets.
     * The parts can be considered as the internal building block of the widgets.
     * E.g. slider = background + indicator + knob
     * Not all parts are used by every widget
     */

    enum _lv_part_t
    {
        LV_PART_MAIN = 0x000000,      /**< 类似矩形的背景*/
        LV_PART_SCROLLBAR = 0x010000, /**< 滚动条*/
        LV_PART_INDICATOR = 0x020000, /**< 指示器，例如用于滑块、条形图、开关或复选框的勾选框*/
        LV_PART_KNOB = 0x030000,      /**< 类似句柄，用于调整值*/
        LV_PART_SELECTED = 0x040000,  /**< 指示当前选定的选项或部分*/
        LV_PART_ITEMS = 0x050000,     /**< 如果小部件具有多个类似元素（例如表格单元格）则使用*/
        LV_PART_CURSOR = 0x060000,    /**< 标记特定位置，例如文本区域的光标或图表上*/

        LV_PART_CUSTOM_FIRST = 0x080000, /**< 自定义小部件的扩展点*/

        LV_PART_ANY = 0x0F0000, /**< 在某些函数中可以使用特殊值来定位所有部分*/
    };

    /**
     * On/Off features controlling the object's behavior.
     * OR-ed values are possible
     *
     * Note: update obj flags corresponding properties below
     * whenever add/remove flags or change bit definition of flags.
     */
    typedef enum
    {
        LV_OBJ_FLAG_HIDDEN = (1L << 0),           /**< 使对象隐藏。 （就像它根本不存在一样）*/
        LV_OBJ_FLAG_CLICKABLE = (1L << 1),        /**< 使对象可被输入设备点击*/
        LV_OBJ_FLAG_CLICK_FOCUSABLE = (1L << 2),  /**< 在点击时将焦点状态添加到对象*/
        LV_OBJ_FLAG_CHECKABLE = (1L << 3),        /**< 在点击对象时切换选中状态*/
        LV_OBJ_FLAG_SCROLLABLE = (1L << 4),       /**< 使对象可滚动*/
        LV_OBJ_FLAG_SCROLL_ELASTIC = (1L << 5),   /**< 允许在内部滚动但速度较慢*/
        LV_OBJ_FLAG_SCROLL_MOMENTUM = (1L << 6),  /**< 使对象在“抛出”时滚动得更远*/
        LV_OBJ_FLAG_SCROLL_ONE = (1L << 7),       /**< 仅允许滚动一个可捕捉子项*/
        LV_OBJ_FLAG_SCROLL_CHAIN_HOR = (1L << 8), /**< 允许将水平滚动传播到父项*/
        LV_OBJ_FLAG_SCROLL_CHAIN_VER = (1L << 9), /**< 允许将垂直滚动传播到父项*/
        LV_OBJ_FLAG_SCROLL_CHAIN = (LV_OBJ_FLAG_SCROLL_CHAIN_HOR | LV_OBJ_FLAG_SCROLL_CHAIN_VER),
        LV_OBJ_FLAG_SCROLL_ON_FOCUS = (1L << 10),       /**< 自动滚动对象以使其在聚焦时可见*/
        LV_OBJ_FLAG_SCROLL_WITH_ARROW = (1L << 11),     /**< 允许使用箭头键滚动焦点对象*/
        LV_OBJ_FLAG_SNAPPABLE = (1L << 12),             /**< 如果在父级上启用了滚动捕捉，它可以捕捉到此对象*/
        LV_OBJ_FLAG_PRESS_LOCK = (1L << 13),            /**< 即使按下从对象上滑落，也要保持对象按下*/
        LV_OBJ_FLAG_EVENT_BUBBLE = (1L << 14),          /**< 将事件也传播给父级*/
        LV_OBJ_FLAG_GESTURE_BUBBLE = (1L << 15),        /**< 将手势传播给父级*/
        LV_OBJ_FLAG_ADV_HITTEST = (1L << 16),           /**< 允许执行更准确的命中（点击）测试。例如考虑圆角。*/
        LV_OBJ_FLAG_IGNORE_LAYOUT = (1L << 17),         /**< 使对象可通过布局定位*/
        LV_OBJ_FLAG_FLOATING = (1L << 18),              /**< 当父级滚动时不滚动对象并忽略布局*/
        LV_OBJ_FLAG_SEND_DRAW_TASK_EVENTS = (1L << 19), /**< 发送 `LV_EVENT_DRAW_TASK_ADDED` 事件*/
        LV_OBJ_FLAG_OVERFLOW_VISIBLE = (1L << 20),      /**< 不要将子级剪裁到父级的扩展绘制大小*/
#if LV_USE_FLEX
        LV_OBJ_FLAG_FLEX_IN_NEW_TRACK = (1L << 21), /**< Start a new flex track on this item*/
#endif

        LV_OBJ_FLAG_LAYOUT_1 = (1L << 23), /**< Custom flag, free to use by layouts*/
        LV_OBJ_FLAG_LAYOUT_2 = (1L << 24), /**< Custom flag, free to use by layouts*/

        LV_OBJ_FLAG_WIDGET_1 = (1L << 25), /**< Custom flag, free to use by widget*/
        LV_OBJ_FLAG_WIDGET_2 = (1L << 26), /**< Custom flag, free to use by widget*/
        LV_OBJ_FLAG_USER_1 = (1L << 27),   /**< Custom flag, free to use by user*/
        LV_OBJ_FLAG_USER_2 = (1L << 28),   /**< Custom flag, free to use by user*/
        LV_OBJ_FLAG_USER_3 = (1L << 29),   /**< Custom flag, free to use by user*/
        LV_OBJ_FLAG_USER_4 = (1L << 30),   /**< Custom flag, free to use by user*/
    } _lv_obj_flag_t;

#if LV_USE_OBJ_PROPERTY
    enum
    {
        /*OBJ flag properties */
        LV_PROPERTY_ID(OBJ, FLAG_START, LV_PROPERTY_TYPE_INT, 0),
        LV_PROPERTY_ID(OBJ, FLAG_HIDDEN, LV_PROPERTY_TYPE_INT, 0),
        LV_PROPERTY_ID(OBJ, FLAG_CLICKABLE, LV_PROPERTY_TYPE_INT, 1),
        LV_PROPERTY_ID(OBJ, FLAG_CLICK_FOCUSABLE, LV_PROPERTY_TYPE_INT, 2),
        LV_PROPERTY_ID(OBJ, FLAG_CHECKABLE, LV_PROPERTY_TYPE_INT, 3),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLLABLE, LV_PROPERTY_TYPE_INT, 4),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_ELASTIC, LV_PROPERTY_TYPE_INT, 5),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_MOMENTUM, LV_PROPERTY_TYPE_INT, 6),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_ONE, LV_PROPERTY_TYPE_INT, 7),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_CHAIN_HOR, LV_PROPERTY_TYPE_INT, 8),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_CHAIN_VER, LV_PROPERTY_TYPE_INT, 9),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_ON_FOCUS, LV_PROPERTY_TYPE_INT, 10),
        LV_PROPERTY_ID(OBJ, FLAG_SCROLL_WITH_ARROW, LV_PROPERTY_TYPE_INT, 11),
        LV_PROPERTY_ID(OBJ, FLAG_SNAPPABLE, LV_PROPERTY_TYPE_INT, 12),
        LV_PROPERTY_ID(OBJ, FLAG_PRESS_LOCK, LV_PROPERTY_TYPE_INT, 13),
        LV_PROPERTY_ID(OBJ, FLAG_EVENT_BUBBLE, LV_PROPERTY_TYPE_INT, 14),
        LV_PROPERTY_ID(OBJ, FLAG_GESTURE_BUBBLE, LV_PROPERTY_TYPE_INT, 15),
        LV_PROPERTY_ID(OBJ, FLAG_ADV_HITTEST, LV_PROPERTY_TYPE_INT, 16),
        LV_PROPERTY_ID(OBJ, FLAG_IGNORE_LAYOUT, LV_PROPERTY_TYPE_INT, 17),
        LV_PROPERTY_ID(OBJ, FLAG_FLOATING, LV_PROPERTY_TYPE_INT, 18),
        LV_PROPERTY_ID(OBJ, FLAG_SEND_DRAW_TASK_EVENTS, LV_PROPERTY_TYPE_INT, 19),
        LV_PROPERTY_ID(OBJ, FLAG_OVERFLOW_VISIBLE, LV_PROPERTY_TYPE_INT, 20),
        LV_PROPERTY_ID(OBJ, FLAG_FLEX_IN_NEW_TRACK, LV_PROPERTY_TYPE_INT, 21),
        LV_PROPERTY_ID(OBJ, FLAG_LAYOUT_1, LV_PROPERTY_TYPE_INT, 23),
        LV_PROPERTY_ID(OBJ, FLAG_LAYOUT_2, LV_PROPERTY_TYPE_INT, 24),
        LV_PROPERTY_ID(OBJ, FLAG_WIDGET_1, LV_PROPERTY_TYPE_INT, 25),
        LV_PROPERTY_ID(OBJ, FLAG_WIDGET_2, LV_PROPERTY_TYPE_INT, 26),
        LV_PROPERTY_ID(OBJ, FLAG_USER_1, LV_PROPERTY_TYPE_INT, 27),
        LV_PROPERTY_ID(OBJ, FLAG_USER_2, LV_PROPERTY_TYPE_INT, 28),
        LV_PROPERTY_ID(OBJ, FLAG_USER_3, LV_PROPERTY_TYPE_INT, 29),
        LV_PROPERTY_ID(OBJ, FLAG_USER_4, LV_PROPERTY_TYPE_INT, 30),
        LV_PROPERTY_ID(OBJ, FLAG_END, LV_PROPERTY_TYPE_INT, 30),

        LV_PROPERTY_ID(OBJ, STATE_START, LV_PROPERTY_TYPE_INT, 31),
        LV_PROPERTY_ID(OBJ, STATE_CHECKED, LV_PROPERTY_TYPE_INT, 31),
        LV_PROPERTY_ID(OBJ, STATE_FOCUSED, LV_PROPERTY_TYPE_INT, 32),
        LV_PROPERTY_ID(OBJ, STATE_FOCUS_KEY, LV_PROPERTY_TYPE_INT, 33),
        LV_PROPERTY_ID(OBJ, STATE_EDITED, LV_PROPERTY_TYPE_INT, 34),
        LV_PROPERTY_ID(OBJ, STATE_HOVERED, LV_PROPERTY_TYPE_INT, 35),
        LV_PROPERTY_ID(OBJ, STATE_PRESSED, LV_PROPERTY_TYPE_INT, 36),
        LV_PROPERTY_ID(OBJ, STATE_SCROLLED, LV_PROPERTY_TYPE_INT, 37),
        LV_PROPERTY_ID(OBJ, STATE_DISABLED, LV_PROPERTY_TYPE_INT, 38),
        /*not used bit8-bit11*/
        LV_PROPERTY_ID(OBJ, STATE_USER_1, LV_PROPERTY_TYPE_INT, 43),
        LV_PROPERTY_ID(OBJ, STATE_USER_2, LV_PROPERTY_TYPE_INT, 44),
        LV_PROPERTY_ID(OBJ, STATE_USER_3, LV_PROPERTY_TYPE_INT, 45),
        LV_PROPERTY_ID(OBJ, STATE_USER_4, LV_PROPERTY_TYPE_INT, 46),
        LV_PROPERTY_ID(OBJ, STATE_ANY, LV_PROPERTY_TYPE_INT, 47),
        LV_PROPERTY_ID(OBJ, STATE_END, LV_PROPERTY_TYPE_INT, 47),

        /*OBJ normal properties*/
        LV_PROPERTY_ID(OBJ, PARENT, LV_PROPERTY_TYPE_POINTER, 31),

        LV_PROPERTY_OBJ_END,
    };
#endif

    /**
     * Make the base object's class publicly available.
     */
    LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_obj_class;

    /**
     * Special, rarely used attributes.
     * They are allocated automatically if any elements is set.
     */
    typedef struct
    {
        lv_obj_t **children; /**< Store the pointer of the children in an array.*/
        lv_group_t *group_p;
        lv_event_list_t event_list;

        lv_point_t scroll; /**< The current X/Y scroll offset*/

        int32_t ext_click_pad; /**< Extra click padding in all direction*/
        int32_t ext_draw_size; /**< EXTend the size in every direction for drawing.*/

        uint16_t child_cnt;          /**< Number of children*/
        uint16_t scrollbar_mode : 2; /**< How to display scrollbars, see `lv_scrollbar_mode_t`*/
        uint16_t scroll_snap_x : 2;  /**< Where to align the snappable children horizontally, see `lv_scroll_snap_t`*/
        uint16_t scroll_snap_y : 2;  /**< Where to align the snappable children vertically*/
        uint16_t scroll_dir : 4;     /**< The allowed scroll direction(s), see `lv_dir_t`*/
        uint16_t layer_type : 2;     /**< Cache the layer type here. Element of @lv_intermediate_layer_type_t */
    } _lv_obj_spec_attr_t;

    struct _lv_obj_t
    {
        const lv_obj_class_t *class_p;
        lv_obj_t *parent;
        _lv_obj_spec_attr_t *spec_attr;
        _lv_obj_style_t *styles;
#if LV_OBJ_STYLE_CACHE
        uint32_t style_main_prop_is_set;
        uint32_t style_other_prop_is_set;
#endif
        void *user_data;
#if LV_USE_OBJ_ID
        void *id;
#endif
        lv_area_t coords;
        lv_obj_flag_t flags;
        lv_state_t state;
        uint16_t layout_inv : 1;
        uint16_t readjust_scroll_after_layout : 1;
        uint16_t scr_layout_inv : 1;
        uint16_t skip_trans : 1;
        uint16_t style_cnt : 6;
        uint16_t h_layout : 1;
        uint16_t w_layout : 1;
        uint16_t is_deleting : 1;
    };

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    /**
     * Create a base object (a rectangle)
     * @param parent    pointer to a parent object. If NULL then a screen will be created.
     * @return          pointer to the new object
     */
    lv_obj_t *lv_obj_create(lv_obj_t *parent);

    /*=====================
     * Setter functions
     *====================*/

    /**
     * Set one or more flags
     * @param obj   pointer to an object
     * @param f     OR-ed values from `lv_obj_flag_t` to set.
     */
    void lv_obj_add_flag(lv_obj_t *obj, lv_obj_flag_t f);

    /**
     * Remove one or more flags
     * @param obj   pointer to an object
     * @param f     OR-ed values from `lv_obj_flag_t` to clear.
     */
    void lv_obj_remove_flag(lv_obj_t *obj, lv_obj_flag_t f);

    /**
     * Set add or remove one or more flags.
     * @param obj   pointer to an object
     * @param f     OR-ed values from `lv_obj_flag_t` to update.
     * @param v     true: add the flags; false: remove the flags
     */
    void lv_obj_update_flag(lv_obj_t *obj, lv_obj_flag_t f, bool v);

    /**
     * Add one or more states to the object. The other state bits will remain unchanged.
     * If specified in the styles, transition animation will be started from the previous state to the current.
     * @param obj       pointer to an object
     * @param state     the states to add. E.g `LV_STATE_PRESSED | LV_STATE_FOCUSED`
     */
    void lv_obj_add_state(lv_obj_t *obj, lv_state_t state);

    /**
     * Remove one or more states to the object. The other state bits will remain unchanged.
     * If specified in the styles, transition animation will be started from the previous state to the current.
     * @param obj       pointer to an object
     * @param state     the states to add. E.g `LV_STATE_PRESSED | LV_STATE_FOCUSED`
     */
    void lv_obj_remove_state(lv_obj_t *obj, lv_state_t state);

    /**
     * Add or remove one or more states to the object. The other state bits will remain unchanged.
     * @param obj       pointer to an object
     * @param state     the states to add. E.g `LV_STATE_PRESSED | LV_STATE_FOCUSED`
     * @param v         true: add the states; false: remove the states
     */
    void lv_obj_set_state(lv_obj_t *obj, lv_state_t state, bool v);

    /**
     * Set the user_data field of the object
     * @param obj   pointer to an object
     * @param user_data   pointer to the new user_data.
     */
    static inline void lv_obj_set_user_data(lv_obj_t *obj, void *user_data)
    {
        obj->user_data = user_data;
    }

    /*=======================
     * Getter functions
     *======================*/

    /**
     * 检查对象上是否设置了给定的标志或所有给定的标志。
     * @param obj   pointer to an object
     * @param f     the flag(s) to check (OR-ed values can be used)
     * @return      true: all flags are set; false: not all flags are set
     */
    bool lv_obj_has_flag(const lv_obj_t *obj, lv_obj_flag_t f);

    /**
     * Check if a given flag or any of the flags are set on an object.
     * @param obj   pointer to an object
     * @param f     the flag(s) to check (OR-ed values can be used)
     * @return      true: at least one flag is set; false: none of the flags are set
     */
    bool lv_obj_has_flag_any(const lv_obj_t *obj, lv_obj_flag_t f);

    /**
     * Get the state of an object
     * @param obj   pointer to an object
     * @return      the state (OR-ed values from `lv_state_t`)
     */
    lv_state_t lv_obj_get_state(const lv_obj_t *obj);

    /**
     * Check if the object is in a given state or not.
     * @param obj       pointer to an object
     * @param state     a state or combination of states to check
     * @return          true: `obj` is in `state`; false: `obj` is not in `state`
     */
    bool lv_obj_has_state(const lv_obj_t *obj, lv_state_t state);

    /**
     * Get the group of the object
     * @param       obj pointer to an object
     * @return      the pointer to group of the object
     */
    lv_group_t *lv_obj_get_group(const lv_obj_t *obj);

    /**
     * Get the user_data field of the object
     * @param obj   pointer to an object
     * @return      the pointer to the user_data of the object
     */
    static inline void *lv_obj_get_user_data(lv_obj_t *obj)
    {
        return obj->user_data;
    }

    /*=======================
     * Other functions
     *======================*/

    /**
     * Allocate special data for an object if not allocated yet.
     * @param obj   pointer to an object
     */
    void lv_obj_allocate_spec_attr(lv_obj_t *obj);

    /**
     * Check the type of obj.
     * @param obj       pointer to an object
     * @param class_p   a class to check (e.g. `lv_slider_class`)
     * @return          true: `class_p` is the `obj` class.
     */
    bool lv_obj_check_type(const lv_obj_t *obj, const lv_obj_class_t *class_p);

    /**
     * Check if any object has a given class (type).
     * It checks the ancestor classes too.
     * @param obj       pointer to an object
     * @param class_p   a class to check (e.g. `lv_slider_class`)
     * @return          true: `obj` has the given class
     */
    bool lv_obj_has_class(const lv_obj_t *obj, const lv_obj_class_t *class_p);

    /**
     * Get the class (type) of the object
     * @param obj   pointer to an object
     * @return      the class (type) of the object
     */
    const lv_obj_class_t *lv_obj_get_class(const lv_obj_t *obj);

    /**
     * 检查是否有任何物体仍然“活着”。
     * @param obj       指向对象的指针
     * @return          true：有效
     */
    bool lv_obj_is_valid(const lv_obj_t *obj);

#if LV_USE_OBJ_ID
    /**
     * Set an id for an object.
     * @param obj   pointer to an object
     * @param id    the id of the object
     */
    void lv_obj_set_id(lv_obj_t *obj, void *id);

    /**
     * Get the id of an object.
     * @param obj   pointer to an object
     * @return      the id of the object
     */
    void *lv_obj_get_id(const lv_obj_t *obj);

    /**
     * Get the child object by its id.
     * It will check children and grandchildren recursively.
     * Function `lv_obj_id_compare` is used to matched obj id with given id.
     *
     * @param obj       pointer to an object
     * @param id        the id of the child object
     * @return          pointer to the child object or NULL if not found
     */
    lv_obj_t *lv_obj_get_child_by_id(const lv_obj_t *obj, void *id);

    /**
     * Assign id to object if not previously assigned.
     * This function gets called automatically when LV_OBJ_ID_AUTO_ASSIGN is enabled.
     *
     * Set `LV_USE_OBJ_ID_BUILTIN` to use the builtin method to generate object ID.
     * Otherwise, these functions including `lv_obj_[assign|free|stringify]_id` and
     * `lv_obj_id_compare`should be implemented externally.
     *
     * @param class_p   the class this obj belongs to. Note obj->class_p is the class currently being constructed.
     * @param obj   pointer to an object
     */
    void lv_obj_assign_id(const lv_obj_class_t *class_p, lv_obj_t *obj);

    /**
     * Free resources allocated by `lv_obj_assign_id`.
     * This function gets called automatically when object is deleted.
     * @param obj   pointer to an object
     */
    void lv_obj_free_id(lv_obj_t *obj);

    /**
     * Compare two obj id, return 0 if they are equal.
     *
     * Set `LV_USE_OBJ_ID_BUILTIN` to use the builtin method for compare.
     * Otherwise, it must be implemented externally.
     *
     * @param id1: the first id
     * @param id2: the second id
     * @return     0 if they are equal, non-zero otherwise.
     */
    int lv_obj_id_compare(void *id1, void *id2);

    /**
     * Format an object's id into a string.
     * @param obj   pointer to an object
     * @param buf   buffer to write the string into
     * @param len   length of the buffer
     */
    const char *lv_obj_stringify_id(lv_obj_t *obj, char *buf, uint32_t len);

#if LV_USE_OBJ_ID_BUILTIN
    /**
     * Free resources used by builtin ID generator.
     */
    void lv_objid_builtin_destroy(void);
#endif

#endif /*LV_USE_OBJ_ID*/

    /**********************
     *      MACROS
     **********************/

#if LV_USE_ASSERT_OBJ
#define LV_ASSERT_OBJ(obj_p, obj_class)                                                                \
    do                                                                                                 \
    {                                                                                                  \
        LV_ASSERT_MSG(obj_p != NULL, "The object is NULL");                                            \
        LV_ASSERT_MSG(lv_obj_has_class(obj_p, obj_class) == true, "Incompatible object type.");        \
        LV_ASSERT_MSG(lv_obj_is_valid(obj_p) == true, "The object is invalid, deleted or corrupted?"); \
    } while (0)
#else
#define LV_ASSERT_OBJ(obj_p, obj_class) \
    do                                  \
    {                                   \
    } while (0)
#endif

#if LV_USE_LOG && LV_LOG_TRACE_OBJ_CREATE
#define LV_TRACE_OBJ_CREATE(...) LV_LOG_TRACE(__VA_ARGS__)
#else
#define LV_TRACE_OBJ_CREATE(...)
#endif

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ_H*/
