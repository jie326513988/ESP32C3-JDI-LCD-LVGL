/**
 * @file lv_obj_pos.h
 *
 */

#ifndef LV_OBJ_POS_H
#define LV_OBJ_POS_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_area.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    /** No flags */
    LV_OBJ_POINT_TRANSFORM_FLAG_NONE = 0x00,

    /** Consider the transformation properties of the parents too */
    LV_OBJ_POINT_TRANSFORM_FLAG_RECURSIVE = 0x01,

    /** Execute the inverse of the transformation (-angle and 1/zoom) */
    LV_OBJ_POINT_TRANSFORM_FLAG_INVERSE = 0x02,

    /** Both inverse and recursive*/
    LV_OBJ_POINT_TRANSFORM_FLAG_INVERSE_RECURSIVE = 0x03,
} lv_obj_point_transform_flag_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 设置对象相对于设定路线的位置。
 * @param obj       pointer to an object
 * @param x         new x coordinate
 * @param y         new y coordinate
 * @note            With default alignment it's the distance from the top left corner
 * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
 * @note            The position is interpreted on the content area of the parent
 * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
 */
void lv_obj_set_pos(lv_obj_t * obj, int32_t x, int32_t y);

/**
 * 设置对象的x坐标
 * @param obj       pointer to an object
 * @param x         new x coordinate
 * @note            With default alignment it's the distance from the top left corner
 * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
 * @note            The position is interpreted on the content area of the parent
 * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
 */
void lv_obj_set_x(lv_obj_t * obj, int32_t x);

/**
 * 设置对象的y坐标
 * @param obj       pointer to an object
 * @param y         new y coordinate
 * @note            With default alignment it's the distance from the top left corner
 * @note            E.g. LV_ALIGN_CENTER alignment it's the offset from the center of the parent
 * @note            The position is interpreted on the content area of the parent
 * @note            The values can be set in pixel or in percentage of parent size with `lv_pct(v)`
 */
void lv_obj_set_y(lv_obj_t * obj, int32_t y);

/**
 * 设置对象的大小。
 * @param obj       pointer to an object
 * @param w         the new width
 * @param h         the new height
 * @note            possible values are:
 *                  pixel               simple set the size accordingly
 *                  LV_SIZE_CONTENT     set the size to involve all children in the given direction
 *                  lv_pct(x)           to set size in percentage of the parent's content area size (the size without paddings).
 *                                      x should be in [0..1000]% range
 */
void lv_obj_set_size(lv_obj_t * obj, int32_t w, int32_t h);

/**
 * 重新计算对象的大小
 * @param obj       pointer to an object
 * @return          true：大小已更改
 */
bool lv_obj_refr_size(lv_obj_t * obj);

/**
 * 设置对象的宽度
 * @param obj       pointer to an object
 * @param w         the new width
 * @note            possible values are:
 *                  pixel               simple set the size accordingly
 *                  LV_SIZE_CONTENT     set the size to involve all children in the given direction
 *                  lv_pct(x)           to set size in percentage of the parent's content area size (the size without paddings).
 *                                      x should be in [0..1000]% range
 */
void lv_obj_set_width(lv_obj_t * obj, int32_t w);

/**
 * 设置对象的高度
 * @param obj       pointer to an object
 * @param h         the new height
 * @note            possible values are:
 *                  pixel               simple set the size accordingly
 *                  LV_SIZE_CONTENT     set the size to involve all children in the given direction
 *                  lv_pct(x)           to set size in percentage of the parent's content area size (the size without paddings).
 *                                      x should be in [0..1000]% range
 */
void lv_obj_set_height(lv_obj_t * obj, int32_t h);

/**
 * 设置宽度减去左右填充和边框宽度。
 * @param obj       pointer to an object
 * @param w         the width without paddings in pixels
 */
void lv_obj_set_content_width(lv_obj_t * obj, int32_t w);

/**
 * 设置高度减去顶部和底部填充以及边框宽度。
 * @param obj       pointer to an object
 * @param h         the height without paddings in pixels
 */
void lv_obj_set_content_height(lv_obj_t * obj, int32_t h);

/**
 * 为对象设置布局
 * @param obj       pointer to an object
 * @param layout    pointer to a layout descriptor to set
 */
void lv_obj_set_layout(lv_obj_t * obj, uint32_t layout);

/**
 * 测试和对象是否按布局定位
 * @param obj       pointer to an object to test
 * @return true:    positioned by a layout; false: not positioned by a layout
 */
bool lv_obj_is_layout_positioned(const lv_obj_t * obj);

/**
 *标记对象以进行布局更新。
 * @param obj      pointer to an object whose children needs to be updated
 */
void lv_obj_mark_layout_as_dirty(lv_obj_t * obj);

/**
 * 更新对象的布局。
 * @param obj      pointer to an object whose children needs to be updated
 */
void lv_obj_update_layout(const lv_obj_t * obj);

/**
 * 更改对象的对齐方式。
 * @param obj       pointer to an object to align
 * @param align     type of alignment (see 'lv_align_t' enum) `LV_ALIGN_OUT_...` can't be used.
 */
void lv_obj_set_align(lv_obj_t * obj, lv_align_t align);

/**
 * 更改对象的对齐方式并设置新的坐标。
 * Equivalent to:
 * lv_obj_set_align(obj, align);
 * lv_obj_set_pos(obj, x_ofs, y_ofs);
 * @param obj       pointer to an object to align
 * @param align     type of alignment (see 'lv_align_t' enum) `LV_ALIGN_OUT_...` can't be used.
 * @param x_ofs     x coordinate offset after alignment
 * @param y_ofs     y coordinate offset after alignment
 */
void lv_obj_align(lv_obj_t * obj, lv_align_t align, int32_t x_ofs, int32_t y_ofs);

/**
 * 将一个对象与另一个对象对齐。
 * @param obj       pointer to an object to align
 * @param base      pointer to another object (if NULL `obj`s parent is used). 'obj' will be aligned to it.
 * @param align     type of alignment (see 'lv_align_t' enum)
 * @param x_ofs     x coordinate offset after alignment
 * @param y_ofs     y coordinate offset after alignment
 * @note            if the position or size of `base` changes `obj` needs to be aligned manually again
 */
void lv_obj_align_to(lv_obj_t * obj, const lv_obj_t * base, lv_align_t align, int32_t x_ofs,
                     int32_t y_ofs);
/**
*将对象与其父对象的中心对齐。
*@param obj指向要对齐的对象的指针
*@注意，如果父级大小发生变化，则需要再次手动对齐obj
*/
static inline void lv_obj_center(lv_obj_t * obj)
{
    lv_obj_align(obj, LV_ALIGN_CENTER, 0, 0);
}

/**
 * 将对象的坐标复制到某个区域
 * @param obj       pointer to an object
 * @param coords    pointer to an area to store the coordinates
 */
void lv_obj_get_coords(const lv_obj_t * obj, lv_area_t * coords);

/**
 * 获取对象的x坐标。
 * @param obj       pointer to an object
 * @return          distance of `obj` from the left side of its parent plus the parent's left padding
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @note            Zero return value means the object is on the left padding of the parent, and not on the left edge.
 * @note            Scrolling of the parent doesn't change the returned value.
 * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
 */
int32_t lv_obj_get_x(const lv_obj_t * obj);

/**
 * 获取对象的x2坐标。
 * @param obj       pointer to an object
 * @return          distance of `obj` from the right side of its parent plus the parent's right padding
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @note            Zero return value means the object is on the right padding of the parent, and not on the right edge.
 * @note            Scrolling of the parent doesn't change the returned value.
 * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
 */
int32_t lv_obj_get_x2(const lv_obj_t * obj);

/**
 * 获取对象的y坐标。
 * @param obj       pointer to an object
 * @return          distance of `obj` from the top side of its parent plus the parent's top padding
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @note            Zero return value means the object is on the top padding of the parent, and not on the top edge.
 * @note            Scrolling of the parent doesn't change the returned value.
 * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
 */
int32_t lv_obj_get_y(const lv_obj_t * obj);

/**
 * 获取对象的y2坐标。
 * @param obj       pointer to an object
 * @return          distance of `obj` from the bottom side of its parent plus the parent's bottom padding
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @note            Zero return value means the object is on the bottom padding of the parent, and not on the bottom edge.
 * @note            Scrolling of the parent doesn't change the returned value.
 * @note            The returned value is always the distance from the parent even if `obj` is positioned by a layout.
 */
int32_t lv_obj_get_y2(const lv_obj_t * obj);

/**
 * 获取对象的实际设置x坐标，即与设置对齐的偏移量
 * @param obj       pointer to an object
 * @return          the set x coordinate
 */
int32_t lv_obj_get_x_aligned(const lv_obj_t * obj);

/**
 * 获取对象的实际设置y坐标，即与设置对齐的偏移量
 * @param obj       pointer to an object
 * @return          the set y coordinate
 */
int32_t lv_obj_get_y_aligned(const lv_obj_t * obj);

/**
 * 获取对象的宽度
 * @param obj       pointer to an object
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @return          the width in pixels
 */
int32_t lv_obj_get_width(const lv_obj_t * obj);

/**
 * 获取物体的高度
 * @param obj       pointer to an object
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @return          the height in pixels
 */
int32_t lv_obj_get_height(const lv_obj_t * obj);

/**
 * 获取左右填充和边框宽度减去的宽度。
 * @param obj       pointer to an object
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @return          the width which still fits into its parent without causing overflow (making the parent scrollable)
 */
int32_t lv_obj_get_content_width(const lv_obj_t * obj);

/**
 * 获取高度减去顶部和底部填充以及边框宽度。
 * @param obj       pointer to an object
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @return          the height which still fits into the parent without causing overflow (making the parent scrollable)
 */
int32_t lv_obj_get_content_height(const lv_obj_t * obj);

/**
 * 获取通过填充和边框宽度减少的面积。
 * @param obj       pointer to an object
 * @note            The position of the object is recalculated only on the next redraw. To force coordinate recalculation
 *                  call `lv_obj_update_layout(obj)`.
 * @param area      the area which still fits into the parent without causing overflow (making the parent scrollable)
 */
void lv_obj_get_content_coords(const lv_obj_t * obj, lv_area_t * area);

/**
 * 获取小部件“部分”所占的宽度。例如，表格所有列的宽度。
 * @param obj       pointer to an objects
 * @return          the width of the virtually drawn content
 * @note            This size independent from the real size of the widget.
 *                  It just tells how large the internal ("virtual") content is.
 */
int32_t lv_obj_get_self_width(const lv_obj_t * obj);

/**
 * 获取小部件“部分”所占的高度。例如，表格所有行的高度。
 * @param obj       pointer to an objects
 * @return          the width of the virtually drawn content
 * @note            This size independent from the real size of the widget.
 *                  It just tells how large the internal ("virtual") content is.
 */
int32_t lv_obj_get_self_height(const lv_obj_t * obj);

/**
 * 处理对象的内部（“虚拟”）内容的大小是否已发生改变。
 * @param obj       pointer to an object
 * @return          false: nothing happened; true: refresh happened
 */
bool lv_obj_refresh_self_size(lv_obj_t * obj);

void lv_obj_refr_pos(lv_obj_t * obj);

void lv_obj_move_to(lv_obj_t * obj, int32_t x, int32_t y);

void lv_obj_move_children_by(lv_obj_t * obj, int32_t x_diff, int32_t y_diff, bool ignore_floating);

/**
 * 使用对象的角度和缩放样式属性来变换点
 * @param obj           pointer to an object whose style properties should be used
 * @param p             a point to transform, the result will be written back here too
 * @param flags         OR-ed valued of :cpp:enum:`lv_obj_point_transform_flag_t`
 */
void lv_obj_transform_point(const lv_obj_t * obj, lv_point_t * p, lv_obj_point_transform_flag_t flags);

/**
 * 使用对象的角度和缩放样式属性转换点数组
 * @param obj           pointer to an object whose style properties should be used
 * @param points        the array of points to transform, the result will be written back here too
 * @param count         number of points in the array
 * @param flags         OR-ed valued of :cpp:enum:`lv_obj_point_transform_flag_t`
 */
void lv_obj_transform_point_array(const lv_obj_t * obj, lv_point_t points[], size_t count,
                                  lv_obj_point_transform_flag_t flags);

/**
 * 使用对象的角度和缩放样式属性变换区域
 * @param obj           pointer to an object whose style properties should be used
 * @param area          an area to transform, the result will be written back here too
 * @param flags         OR-ed valued of :cpp:enum:`lv_obj_point_transform_flag_t`
 */
void lv_obj_get_transformed_area(const lv_obj_t * obj, lv_area_t * area, lv_obj_point_transform_flag_t flags);

/**
 * 将对象的某个区域标记为无效。
 * The area will be truncated to the object's area and marked for redraw.
 * @param obj       pointer to an object
 * @param           area the area to redraw
 */
void lv_obj_invalidate_area(const lv_obj_t * obj, const lv_area_t * area);

/**
 * 将对象标记为无效，以重新绘制其区域
 * @param obj       pointer to an object
 */
void lv_obj_invalidate(const lv_obj_t * obj);

/**
 * 判断物体的某个区域现在是否可见（即使是部分可见）
 * @param obj       pointer to an object
 * @param area      the are to check. The visible part of the area will be written back here.
 * @return true     visible; false not visible (hidden, out of parent, on other screen, etc)
 */
bool lv_obj_area_is_visible(const lv_obj_t * obj, lv_area_t * area);

/**
 * 判断一个物体现在是否可见（即使是部分可见）
 * @param obj   pointer to an object
 * @return      true：可见；false不可见（隐藏、不在父屏幕上、在其他屏幕上等）
 */
bool lv_obj_is_visible(const lv_obj_t * obj);

/**
 * 设置扩展可点击区域的大小
 * @param obj       pointer to an object
 * @param size      extended clickable area in all 4 directions [px]
 */
void lv_obj_set_ext_click_area(lv_obj_t * obj, int32_t size);

/**
 * 获取对象可被点击的区域。
 * 它是对象的正常区域加上扩展的点击区域。
 * @param obj       pointer to an object
 * @param area      store the result area here
 */
void lv_obj_get_click_area(const lv_obj_t * obj, lv_area_t * area);

/**
 * 对屏幕空间中特定点的对象进行命中测试。
 * @param obj       object to hit-test
 * @param point     screen-space point (absolute coordinate)
 * @return          true: if the object is considered under the point
 */
bool lv_obj_hit_test(lv_obj_t * obj, const lv_point_t * point);

/**
 * 将宽度限制在最小和最大宽度之间。如果最小/最大宽度以百分比表示，请使用 ref_width
 * @param width         width to clamp
 * @param min_width     the minimal width
 * @param max_width     the maximal width
 * @param ref_width     the reference width used when min/max width is in percentage
 * @return              the clamped width
 */
int32_t lv_clamp_width(int32_t width, int32_t min_width, int32_t max_width, int32_t ref_width);

/**
 * 将高度限制在最小高度和最大高度之间。如果最小/最大高度以百分比值表示，请使用 ref_height
 * @param height         height to clamp
 * @param min_height     the minimal height
 * @param max_height     the maximal height
 * @param ref_height     the reference height used when min/max height is in percentage
 * @return              the clamped height
 */
int32_t lv_clamp_height(int32_t height, int32_t min_height, int32_t max_height, int32_t ref_height);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ_POS_H*/
