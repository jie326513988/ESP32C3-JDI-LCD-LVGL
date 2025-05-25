/**
 * @file struct _lv_obj_tree.h
 *
 */

#ifndef LV_OBJ_TREE_H
#define LV_OBJ_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../misc/lv_types.h"
#include "../misc/lv_anim.h"
#include "../display/lv_display.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LV_OBJ_TREE_WALK_NEXT,
    LV_OBJ_TREE_WALK_SKIP_CHILDREN,
    LV_OBJ_TREE_WALK_END,
} lv_obj_tree_walk_res_t;

typedef lv_obj_tree_walk_res_t (*lv_obj_tree_walk_cb_t)(lv_obj_t *, void *);

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 删除一个对象及其所有子对象。
 * 同时从对象组中删除对象，并删除所有动画（如果有的话）。
 * 向已删除的对象发送“LV_EVENT_DELETED”。
 * @param obj       pointer to an object
 */
void lv_obj_delete(lv_obj_t * obj);

/**
 * 删除对象的所有子项。
 * 同时从对象组中删除对象，并删除所有动画（如果有的话）。
 * 向已删除的对象发送“LV_EVENT_DELETED”。
 * @param obj       pointer to an object
 */
void lv_obj_clean(lv_obj_t * obj);

/**
 * 延迟一段时间后删除对象
 * @param obj       pointer to an object
 * @param delay_ms  time to wait before delete in milliseconds
 */
void lv_obj_delete_delayed(lv_obj_t * obj, uint32_t delay_ms);

/**
 * 一个易于在动画就绪回调中使用的函数，用于在动画就绪时删除对象
 * @param a         pointer to the animation
 */
void lv_obj_delete_anim_completed_cb(lv_anim_t * a);

/**
 * 用于异步删除对象的辅助函数。
 * Useful for cases where you can't delete an object directly in an `LV_EVENT_DELETE` handler (i.e. parent).
 * @param obj       object to delete
 * @see lv_async_call
 */
void lv_obj_delete_async(lv_obj_t * obj);

/**
 * 移动对象的父对象。将保留相对坐标。
 *
 * @param obj    pointer to an object whose parent needs to be changed
 * @param parent pointer to the new parent
 */
void lv_obj_set_parent(lv_obj_t * obj, lv_obj_t * parent);

/**
 * 交换两个对象的位置。
 * 在列表框中使用时，它可用于对列表框项目进行排序。
 * @param obj1  pointer to the first object
 * @param obj2  pointer to the second object
 */
void lv_obj_swap(lv_obj_t * obj1, lv_obj_t * obj2);

/**
 * 将对象移动到其父级中的给定索引。
 * 在列表框中使用时，它可用于对列表框项目进行排序。
 * @param obj  指向要移动的对象的指针。
 * @param index  父级中的新索引-1从后面数
 * @note 移动到底层：lv_obj_move_to_index(obj, 0)
 * @note 移动到顶层：lv_obj_move_to_index(obj, lv_obj_get_index(obj)-1）
 */
void lv_obj_move_to_index(lv_obj_t * obj, int32_t index);

/**
 * 获取对象的屏幕
 * @param obj       pointer to an object
 * @return          pointer to the object's screen
 */
lv_obj_t * lv_obj_get_screen(const lv_obj_t * obj);

/**
 * 获取对象的显示
 * @param obj       pointer to an object
 * @return          pointer to the object's display
 */
lv_display_t * lv_obj_get_display(const lv_obj_t * obj);

/**
* 获取对象的父对象
* @param obj 指向对象的指针
* @return 对象的父对象。（如果 `obj` 是屏幕，则返回 NULL）
*/
lv_obj_t * lv_obj_get_parent(const lv_obj_t * obj);

/**
 * 根据子对象的索引获取对象的子对象。
 * @param obj 指向应获取其子代的对象
 * @param idx 子代的索引。
 * 0：最老的（首先创建的）子代
 * 1：第二老的子代
 * child count-1：最小的子代
 * -1：最小的子代
 * -2：第二小的子代
 * @return 指向子代的指针，如果索引无效，则返回 NULL
 */
lv_obj_t * lv_obj_get_child(const lv_obj_t * obj, int32_t idx);

/**
* 通过子对象的索引获取其子对象。仅考虑具有给定类型的子对象。
* @param obj 指向应获取其子对象的对象的指针
* @param idx 子对象的索引。
* 0：最老的（首先创建的）子对象
* 1：第二老的子对象
* child count-1：最小的子对象
* -1：最小的子对象
* -2：第二小的子对象
* @param class_p 要检查的子对象的类型
* @return 指向子对象的指针，如果索引无效，则返回 NULL
*/
lv_obj_t * lv_obj_get_child_by_type(const lv_obj_t * obj, int32_t idx,
                                    const lv_obj_class_t * class_p);

/**
* 返回对象的兄弟对象
* @param obj 指向应获取其兄弟对象的指针
* @param idx 0：`obj` 本身
* -1：第一个较年长的兄弟对象
* -2：下一个较年长的兄弟对象
* 1：第一个较年轻的兄弟对象
* 2：下一个较年轻的兄弟对象
* 等等
* @return 指向所请求兄弟对象的指针，若无此类兄弟对象，则返回 NULL
*/
lv_obj_t * lv_obj_get_sibling(const lv_obj_t * obj, int32_t idx);

/**
* 返回对象的兄弟。仅考虑具有给定类型的兄弟。
* @param obj 指向应获取其兄弟的对象
* @param idx 0：`obj` 本身
* -1：第一个较年长的兄弟
* -2：下一个较年长的兄弟
* 1：第一个较年轻的兄弟
* 2：下一个较年轻的兄弟
* 等等
* @param class_p 要检查的子项的类型
* @return 指向请求的兄弟的指针，如果没有这样的兄弟，则返回 NULL
*/
lv_obj_t * lv_obj_get_sibling_by_type(const lv_obj_t * obj, int32_t idx,
                                      const lv_obj_class_t * class_p);

/**
* 获取子代数量
* @param obj 指向对象的指针
* @return 子代数量
*/
uint32_t lv_obj_get_child_count(const lv_obj_t * obj);

/**
* 获取具有给定类型的子项数量。
* @param obj 指向对象的指针
* @param class_p 要检查的子项的类型
* @return 子项数量
*/

uint32_t lv_obj_get_child_count_by_type(const lv_obj_t * obj, const lv_obj_class_t * class_p);

/**
* 获取子项的索引。
* @param obj 指向对象的指针
* @return 对象的子项索引。
* 例如 0：最老的（第一个创建的子项）。
* （如果找不到子项或不存在父项，则为 -1）
*/
int32_t lv_obj_get_index(const lv_obj_t * obj);

/**
* 获取子项的索引。仅考虑具有给定类型的子项。
* @param obj 指向对象的指针
* @param class_p 要检查的子项的类型
* @return 对象的子项索引。
* 例如 0：最老的（具有给定类的第一个创建的子项）。
* （如果找不到子项或不存在父项，则为 -1）
*/
int32_t lv_obj_get_index_by_type(const lv_obj_t * obj, const lv_obj_class_t * class_p);

/**
* 遍历任何对象的所有子对象。
* @param start_obj 从此对象开始集成
* @param cb 在对象上调用此回调
* @param user_data 指向任何用户相关数据的指针（将传递给 `cb`）
*/
void lv_obj_tree_walk(lv_obj_t * start_obj, lv_obj_tree_walk_cb_t cb, void * user_data);

/**
* 遍历任何对象的所有子对象并打印其 ID。
* @param start_obj 从此对象开始集成
*/
void lv_obj_dump_tree(lv_obj_t * start_ob);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_OBJ_TREE_H*/
