/**
 * @file lv_obj_scroll.h
 *
 */

#ifndef LV_OBJ_SCROLL_H
#define LV_OBJ_SCROLL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_area.h"
#include "../misc/lv_anim.h"
#include "../misc/lv_types.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/*Can't include lv_obj.h because it includes this header file*/

/** 滚动条模式：显示滚动条何时可见*/
enum _lv_scrollbar_mode_t {
    LV_SCROLLBAR_MODE_OFF,      /**< Never show scrollbars*/
    LV_SCROLLBAR_MODE_ON,       /**< Always show scrollbars*/
    LV_SCROLLBAR_MODE_ACTIVE,   /**< Show scroll bars when object is being scrolled*/
    LV_SCROLLBAR_MODE_AUTO,     /**< Show scroll bars when the content is large enough to be scrolled*/
};

#ifdef DOXYGEN
typedef _lv_scrollbar_mode_t lv_scrollbar_mode_t;
#else
typedef uint8_t lv_scrollbar_mode_t;
#endif /*DOXYGEN*/

/** 滚动跨度对齐选项。当滚动停止时，告诉对齐可捕捉的子对象的位置.*/
enum _lv_scroll_snap_t {
    LV_SCROLL_SNAP_NONE,    /**< 不要对齐，留在原地*/
    LV_SCROLL_SNAP_START,   /**< 向左/向上对齐*/
    LV_SCROLL_SNAP_END,     /**< 对齐到右侧/底部*/
    LV_SCROLL_SNAP_CENTER   /**< 对齐中心*/
};

#ifdef DOXYGEN
typedef _lv_scroll_snap_t lv_scroll_snap_t;
#else
typedef uint8_t lv_scroll_snap_t;
#endif /*DOXYGEN*/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*=====================
 * Setter functions
 *====================*/

/**
 * 设置滚动条的行为方式.
 * @param obj       pointer to an object
 * @param mode      LV_SCROLL_MODE_ON/OFF/AUTO/ACTIVE
 */
void lv_obj_set_scrollbar_mode(lv_obj_t * obj, lv_scrollbar_mode_t mode);

/**
 * 设置可以滚动方向的对象
 * @param obj       pointer to an object
 * @param dir       允许滚动方向。`lv_dir_t的元素或or值`
 */
void lv_obj_set_scroll_dir(lv_obj_t * obj, lv_dir_t dir);

/**
 * 设置水平滚动结束时捕捉孩子的位置
 * @param obj       pointer to an object
 * @param align     the snap align to set from `lv_scroll_snap_t`
 */
void lv_obj_set_scroll_snap_x(lv_obj_t * obj, lv_scroll_snap_t align);

/**
 * 设置垂直滚动结束时捕捉子对象的位置
 * @param obj       pointer to an object
 * @param align     the snap align to set from `lv_scroll_snap_t`
 */
void lv_obj_set_scroll_snap_y(lv_obj_t * obj, lv_scroll_snap_t align);

/*=====================
 * Getter functions
 *====================*/

/**
 * 获取当前滚动模式（何时隐藏滚动条）
 * @param obj       pointer to an object
 * @return          the current scroll mode from `lv_scrollbar_mode_t`
 */
lv_scrollbar_mode_t lv_obj_get_scrollbar_mode(const lv_obj_t * obj);

/**
 * 获取可以滚动方向的对象
 * @param obj       pointer to an object
 * @param dir       the allow scroll directions. An element or OR-ed values of `lv_dir_t`
 */
lv_dir_t lv_obj_get_scroll_dir(const lv_obj_t * obj);

/**
 * 当水平滚动结束时，找到捕捉孩子的位置
 * @param obj       pointer to an object
 * @return          the current snap align from `lv_scroll_snap_t`
 */
lv_scroll_snap_t lv_obj_get_scroll_snap_x(const lv_obj_t * obj);

/**
 * 当滚动垂直结束时，找到捕捉孩子的位置
 * @param  obj      pointer to an object
 * @return          the current snap align from `lv_scroll_snap_t`
 */
lv_scroll_snap_t lv_obj_get_scroll_snap_y(const lv_obj_t * obj);

/**
 * 获取当前X滚动位置。
 * @param obj       pointer to an object
 * @return          the current scroll position from the left edge.
 *                  If the object is not scrolled return 0
 *                  If scrolled return > 0
 *                  If scrolled in (elastic scroll) return < 0
 */
int32_t lv_obj_get_scroll_x(const lv_obj_t * obj);

/**
 * 获取当前Y轴滚动位置。
 * @param obj       pointer to an object
 * @return          the current scroll position from the top edge.
 *                  If the object is not scrolled return 0
 *                  If scrolled return > 0
 *                  If scrolled inside return < 0
 */
int32_t lv_obj_get_scroll_y(const lv_obj_t * obj);

/**
 * 返回对象上方区域的高度。
 * 这是对象可以向下滚动的像素数。
 * 通常为正值，但向内滚动时可能为负值。
 * @param obj       pointer to an object
 * @return          the scrollable area above the object in pixels
 */
int32_t lv_obj_get_scroll_top(lv_obj_t * obj);

/**
 * 返回对象下方区域的高度。
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area below the object in pixels
 */
int32_t lv_obj_get_scroll_bottom(lv_obj_t * obj);

/**
 * 返回对象左侧区域的宽度。
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area on the left the object in pixels
 */
int32_t lv_obj_get_scroll_left(lv_obj_t * obj);

/**
 * 返回对象右侧区域的宽度。
 * That is the number of pixels the object can be scrolled down.
 * Normally positive but can be negative when scrolled inside.
 * @param obj       pointer to an object
 * @return          the scrollable area on the right the object in pixels
 */
int32_t lv_obj_get_scroll_right(lv_obj_t * obj);

/**
 * 如果正在进行滚动动画，则获取此对象滚动结束的X和Y坐标。
 * 如果没有滚动动画，请给出当前的“x”或“y”滚动位置。
 * @param obj       pointer to an object
 * @param end       pointer to store the result
 */
void lv_obj_get_scroll_end(lv_obj_t * obj, lv_point_t * end);

/*=====================
 * Other functions
 *====================*/

/**
 * 按给定像素量滚动
 * @param obj       指向要滚动的对象的指针
 * @param x         水平滚动像素
 * @param y         垂直滚动的像素
 * @param anim_en   LV_ANIM_ON: 带动画滚动; LV_ANIM_OFF: 立即滚动
 * @note            > 0 value means scroll right/bottom (show the more content on the right/bottom)
 * @note            e.g. dy=-20表示向下滚动20像素
 */
void lv_obj_scroll_by(lv_obj_t * obj, int32_t x, int32_t y, lv_anim_enable_t anim_en);

/**
 * 按给定像素量滚动
 * `dx和dy将在内部受到限制，只允许在内容区域上滚动。
 * @param obj       指向要滚动的对象的指针
 * @param dx        水平滚动像素
 * @param dy        垂直滚动的像素
 * @param anim_en   LV_ANIM_ON: 带动画滚动; LV_ANIM_OFF: 立即滚动
 * @note            e.g. dy=-20表示向下滚动20像素
 */
void lv_obj_scroll_by_bounded(lv_obj_t * obj, int32_t dx, int32_t dy, lv_anim_enable_t anim_en);

/**
 * 滚动到对象上的给定坐标。
 * `x和y将在内部受到限制，只允许在内容区域上滚动。
 * @param obj       指向要滚动的对象的指针
 * @param x         水平滚动像素
 * @param y         垂直滚动的像素
 * @param anim_en   LV_ANIM_ON: 带动画滚动; LV_ANIM_OFF: 立即滚动
 */
void lv_obj_scroll_to(lv_obj_t * obj, int32_t x, int32_t y, lv_anim_enable_t anim_en);

/**
* 滚动到对象上给定的 X 坐标。
* `x` 将在内部受到限制，以仅允许在内容区域上滚动。
* @param obj 指向要滚动的对象
* @param x 水平滚动像素
* @param anim_en LV_ANIM_ON：滚动时带动画；LV_ANIM_OFF：立即滚动
*/
void lv_obj_scroll_to_x(lv_obj_t * obj, int32_t x, lv_anim_enable_t anim_en);

/**
 * 滚动到对象上的给定Y坐标
 * `y’将在内部被限制为仅允许在内容区域上滚动。
 * @param obj       指向要滚动的对象的指针
 * @param y         垂直滚动的像素
 * @param anim_en   LV_ANIM_ON: 带动画滚动; LV_ANIM_OFF: 立即滚动
 */
void lv_obj_scroll_to_y(lv_obj_t * obj, int32_t y, lv_anim_enable_t anim_en);

/**
* 滚动到一个对象，直到它在其父级上可见
* @param obj 指向要滚动到视图中的对象的指针
* @param anim_en LV_ANIM_ON：滚动时带动画；LV_ANIM_OFF：立即滚动
*/
void lv_obj_scroll_to_view(lv_obj_t * obj, lv_anim_enable_t anim_en);

/**
* 滚动到一个对象，直到它在其父级上可见。
* 对父级的父级执行相同操作，依此类推。
* 因此，即使对象有嵌套的可滚​​动父级，它也会滚动到视图中
* @param obj 指向要滚动到视图中的对象的指针
* @param anim_en LV_ANIM_ON：滚动时带动画；LV_ANIM_OFF：立即滚动
*/
void lv_obj_scroll_to_view_recursive(lv_obj_t * obj, lv_anim_enable_t anim_en);

/**
* 低级函数，按给定的 x 和 y 坐标滚动。
* 发送 `LV_EVENT_SCROLL`。
* @param obj 指向要滚动的对象
* @param x 像素水平滚动
* @param y 像素垂直滚动
* @return `LV_RESULT_INVALID`: 对象在 `LV_EVENT_SCROLL` 中被删除；
* `LV_RESULT_OK`: 如果对象仍然有效
*/
lv_result_t _lv_obj_scroll_by_raw(lv_obj_t * obj, int32_t x, int32_t y);

/**
* 判断当前对象是否正在滚动
* @param obj 指向对象的指针
* @return true: `obj` 正在滚动
*/
bool lv_obj_is_scrolling(const lv_obj_t * obj);

/**
* 检查 `obj` 的子项并滚动 `obj` 以满足 scroll_snap 设置
* @param obj 需要检查和捕捉其子项的对象
* @param anim_en LV_ANIM_ON/OFF
*/
void lv_obj_update_snap(lv_obj_t * obj, lv_anim_enable_t anim_en);

/**
 * 获取滚动条的面积
 * @param obj   pointer to an object
 * @param hor   pointer to store the area of the horizontal scrollbar
 * @param ver   pointer to store the area of the vertical  scrollbar
 */
void lv_obj_get_scrollbar_area(lv_obj_t * obj, lv_area_t * hor, lv_area_t * ver);

/**
* 使滚动条区域无效
* @param obj 指向对象的指针
*/
void lv_obj_scrollbar_invalidate(lv_obj_t * obj);

/**
* 检查内容是否已“滚动”并将其调整到正常位置。
* @param obj 指向对象的指针
* @param anim_en LV_ANIM_ON/OFF
*/
void lv_obj_readjust_scroll(lv_obj_t * obj, lv_anim_enable_t anim_en);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ_SCROLL_H*/
