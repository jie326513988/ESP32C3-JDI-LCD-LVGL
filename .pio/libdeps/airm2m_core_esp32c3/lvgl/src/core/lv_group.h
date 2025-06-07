/**
 * @file lv_group.h
 *
 */

#ifndef LV_GROUP_H
#define LV_GROUP_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../lv_conf_internal.h"

#include "../misc/lv_types.h"
#include "../misc/lv_ll.h"

/*********************
 *      DEFINES
 *********************/
/*通过lv_group_send(group,c)控制聚焦对象的预定义键*/
enum _lv_key_t {
    LV_KEY_UP        = 17,  /*0x11*/
    LV_KEY_DOWN      = 18,  /*0x12*/
    LV_KEY_RIGHT     = 19,  /*0x13*/
    LV_KEY_LEFT      = 20,  /*0x14*/
    LV_KEY_ESC       = 27,  /*0x1B*/
    LV_KEY_DEL       = 127, /*0x7F*/
    LV_KEY_BACKSPACE = 8,   /*0x08*/
    LV_KEY_ENTER     = 10,  /*0x0A, '\n'*/
    LV_KEY_NEXT      = 9,   /*0x09, '\t'*/
    LV_KEY_PREV      = 11,  /*0x0B, '*/
    LV_KEY_HOME      = 2,   /*0x02, STX*/
    LV_KEY_END       = 3,   /*0x03, ETX*/
};

/**********************
 *      TYPEDEFS
 **********************/

typedef void (*lv_group_focus_cb_t)(lv_group_t *);
typedef void (*lv_group_edge_cb_t)(lv_group_t *, bool);

/**
 * Groups can be used to logically hold objects so that they can be individually focused.
 * They are NOT for laying out objects on a screen (try layouts for that).
 */
struct _lv_group_t {
    lv_ll_t obj_ll;        /**< Linked list to store the objects in the group*/
    lv_obj_t ** obj_focus; /**< The object in focus*/

    lv_group_focus_cb_t focus_cb;              /**< A function to call when a new object is focused (optional)*/
    lv_group_edge_cb_t  edge_cb;               /**< A function to call when an edge is reached, no more focus
                                                    targets are available in this direction (to allow edge feedback
                                                    like a sound or a scroll bounce) */

    void * user_data;

    uint8_t frozen : 1;         /**< 1: can't focus to new object*/
    uint8_t editing : 1;        /**< 1：编辑模式，0：导航模式*/
    uint8_t refocus_policy : 1; /**< 1: Focus prev if focused on deletion. 0: Focus next if focused on
                                   deletion.*/
    uint8_t wrap : 1;           /**< 1: Focus next/prev can wrap at end of list. 0: Focus next/prev stops at end
                                   of list.*/
};

typedef enum {
    LV_GROUP_REFOCUS_POLICY_NEXT = 0,
    LV_GROUP_REFOCUS_POLICY_PREV = 1
} lv_group_refocus_policy_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Init the group module
 * @remarks Internal function, do not call directly.
 */
void _lv_group_init(void);

/**
 * Deinit the group module
 * @remarks Internal function, do not call directly.
 */
void _lv_group_deinit(void);

/**
 * 创建新的对象组
 *@ 返回指向新对象组的指针
 */
lv_group_t * lv_group_create(void);

/**
 * 删除组对象
 * @param group     pointer to a group
 */
void lv_group_delete(lv_group_t * group);

/**
 * 设置默认组。如果在类中启用了“add_to_def_group = true”，则新对象将被添加到此组中
 * @param group     pointer to a group (can be `NULL`)
 */
void lv_group_set_default(lv_group_t * group);

/**
 * 获取默认组
 * @return          pointer to the default group
 */
lv_group_t * lv_group_get_default(void);

/**
 * 将对象添加到组
 * @param group     pointer to a group
 * @param obj       pointer to an object to add
 */
void lv_group_add_obj(lv_group_t * group, lv_obj_t * obj);

/**
 * 交换组中的 2 个对象。对象必须位于同一组中
 * @param obj1  pointer to an object
 * @param obj2  pointer to another object
 */
void lv_group_swap_obj(lv_obj_t * obj1, lv_obj_t * obj2);

/**
 * 从组中删除对象
 * @param obj       pointer to an object to remove
 */
void lv_group_remove_obj(lv_obj_t * obj);

/**
 * 从组中删除所有对象
 * @param group     pointer to a group
 */
void lv_group_remove_all_objs(lv_group_t * group);

/**
 * 聚焦于一个物体（失焦当前）
 * @param obj       pointer to an object to focus on
 */
void lv_group_focus_obj(lv_obj_t * obj);

/**
 * 聚焦组中的下一个对象（散焦当前对象）
 * @param group     pointer to a group
 */
void lv_group_focus_next(lv_group_t * group);

/**
 * 聚焦组中的前一个对象（散焦当前对象）
 * @param group     pointer to a group
 */
void lv_group_focus_prev(lv_group_t * group);

/**
 * 不要改变当前对象的焦点
 * @param group     pointer to a group
 * @param en        true: freeze, false: release freezing (normal mode)
 */
void lv_group_focus_freeze(lv_group_t * group, bool en);

/**
 * 将控制字符发送到组的焦点对象
 * @param group     pointer to a group
 * @param c         a character (use LV_KEY_.. to navigate)
 * @return          result of focused object in group.
 */
lv_result_t lv_group_send_data(lv_group_t * group, uint32_t c);

/**
 * 为聚焦新对象时将调用的组设置函数
 * @param group         pointer to a group
 * @param focus_cb      the call back function or NULL if unused
 */
void lv_group_set_focus_cb(lv_group_t * group, lv_group_focus_cb_t focus_cb);

/**
 * 为达到焦点边缘时将调用的组设置函数
 * @param group         pointer to a group
 * @param edge_cb      the call back function or NULL if unused
 */
void lv_group_set_edge_cb(lv_group_t * group, lv_group_edge_cb_t edge_cb);

/**
 * 设置如果删除了当前关注的obj，是关注组中的下一个项目还是上一个项目。
 * @param group         pointer to a group
 * @param policy        new refocus policy enum
 */
void lv_group_set_refocus_policy(lv_group_t * group, lv_group_refocus_policy_t policy);

/**
*手动设置当前模式（编辑或导航）。
*@param group指向组的指针
*@param edit true:编辑模式；false：导航模式
*/
void lv_group_set_editing(lv_group_t * group, bool edit);

/**
 * 设置焦点next/prev是否允许从第一个->最后一个或最后一个->第一个对象换行。
 * @param group         pointer to group
 * @param               en true: wrapping enabled; false: wrapping disabled
 */
void lv_group_set_wrap(lv_group_t * group, bool en);

/**
 * 获取焦点对象或NULL（如果没有）
 * @param group 指向组的指针
 * @return      指向聚焦对象的指针
 */
lv_obj_t * lv_group_get_focused(const lv_group_t * group);

/**
 * 获取组的焦点回调函数
 * @param group pointer to a group
 * @return the call back function or NULL if not set
 */
lv_group_focus_cb_t lv_group_get_focus_cb(const lv_group_t * group);

/**
 * 获取组的边缘回调函数
 * @param group pointer to a group
 * @return the call back function or NULL if not set
 */
lv_group_edge_cb_t lv_group_get_edge_cb(const lv_group_t * group);

/**
 * 获取当前模式（编辑或导航）。
 * @param group         指向组的指针
 * @return              true：编辑模式；false：导航模式
 */
bool lv_group_get_editing(const lv_group_t * group);

/**
 * 获取焦点next/prev是否允许从第一个->最后一个或最后一个->第一个对象换行。
 * @param group         pointer to group
 * @param               en true: wrapping enabled; false: wrapping disabled
 */
bool lv_group_get_wrap(lv_group_t * group);

/**
 * 获取组中对象的数量
 * @param group         pointer to a group
 * @return              number of objects in the group
 */
uint32_t lv_group_get_obj_count(lv_group_t * group);

/**
 * 获取组数
 * @return              number of groups
 */
uint32_t lv_group_get_count(void);

/**
 * 按索引获取组
 * @return              pointer to the group
 */
lv_group_t  * lv_group_by_index(uint32_t index);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_GROUP_H*/
