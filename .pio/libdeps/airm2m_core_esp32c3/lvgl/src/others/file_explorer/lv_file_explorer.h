/**
 * @file lv_file_explorer.h
 *
 */

#ifndef LV_FILE_EXPLORER_H
#define LV_FILE_EXPLORER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_conf_internal.h"
#include "../../core/lv_obj.h"

#if LV_USE_FILE_EXPLORER != 0

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LV_EXPLORER_SORT_NONE,
    LV_EXPLORER_SORT_KIND,
} lv_file_explorer_sort_t;

#if LV_FILE_EXPLORER_QUICK_ACCESS
typedef enum {
    LV_EXPLORER_HOME_DIR,
    LV_EXPLORER_MUSIC_DIR,
    LV_EXPLORER_PICTURES_DIR,
    LV_EXPLORER_VIDEO_DIR,
    LV_EXPLORER_DOCS_DIR,
    LV_EXPLORER_FS_DIR,
} lv_file_explorer_dir_t;
#endif

/*Data of canvas*/
typedef struct {
    lv_obj_t obj;
    lv_obj_t * cont;
    lv_obj_t * head_area;
    lv_obj_t * browser_area;
    lv_obj_t * file_table;
    lv_obj_t * path_label;
#if LV_FILE_EXPLORER_QUICK_ACCESS
    lv_obj_t * quick_access_area;
    lv_obj_t * list_device;
    lv_obj_t * list_places;
    char * home_dir;
    char * music_dir;
    char * pictures_dir;
    char * video_dir;
    char * docs_dir;
    char * fs_dir;
#endif
    const char * sel_fn;
    char   current_path[LV_FILE_EXPLORER_PATH_MAX_LEN];
    lv_file_explorer_sort_t sort;
} lv_file_explorer_t;

extern const lv_obj_class_t lv_file_explorer_class;

/***********************
 * GLOBAL VARIABLES
 ***********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
lv_obj_t * lv_file_explorer_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

#if LV_FILE_EXPLORER_QUICK_ACCESS
/**
 * 设置file_explorer
 * @param obj   pointer to a label object
 * @param dir   the dir from 'lv_file_explorer_dir_t' enum.
 * @param path   path

 */
void lv_file_explorer_set_quick_access_path(lv_obj_t * obj, lv_file_explorer_dir_t dir, const char * path);
#endif

/**
 * 设置file_explorer排序
 * @param obj   pointer to a file explorer object
 * @param sort  the sort from 'lv_file_explorer_sort_t' enum.
 */
void lv_file_explorer_set_sort(lv_obj_t * obj, lv_file_explorer_sort_t sort);

/*=====================
 * Getter functions
 *====================*/

/**
 * 获取文件资源管理器所选文件
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer selected file name
 */
const char * lv_file_explorer_get_selected_file_name(const lv_obj_t * obj);

/**
 * 获取文件资源管理器当前路径
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer cur path
 */
const char * lv_file_explorer_get_current_path(const lv_obj_t * obj);

/**
 * 获取文件资源管理器头部区域obj
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer head area obj(lv_obj)
 */
lv_obj_t * lv_file_explorer_get_header(lv_obj_t * obj);

/**
 * 获取文件资源管理器头部区域obj
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer quick access area obj(lv_obj)
 */
lv_obj_t * lv_file_explorer_get_quick_access_area(lv_obj_t * obj);

/**
 * 获取文件资源管理器路径obj（lv_label）
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer path obj(lv_label)
 */
lv_obj_t * lv_file_explorer_get_path_label(lv_obj_t * obj);

#if LV_FILE_EXPLORER_QUICK_ACCESS
/**
 * 获取文件资源管理器位置列表obj（lv_list）
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer places list obj(lv_list)
 */
lv_obj_t * lv_file_explorer_get_places_list(lv_obj_t * obj);

/**
 * 获取文件资源管理器设备列表obj（lv_list）
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer device list obj(lv_list)
 */
lv_obj_t * lv_file_explorer_get_device_list(lv_obj_t * obj);
#endif

/**
 * 获取文件资源管理器文件列表obj（lv_table）
 * @param obj   pointer to a file explorer object
 * @return      pointer to the file explorer file table obj(lv_table)
 */
lv_obj_t * lv_file_explorer_get_file_table(lv_obj_t * obj);

/**
 * 设置file_explorer排序
 * @param obj   pointer to a file explorer object
 * @return the current mode from 'lv_file_explorer_sort_t'
 */
lv_file_explorer_sort_t lv_file_explorer_get_sort(const lv_obj_t * obj);

/*=====================
 * Other functions
 *====================*/

/**
 * 打开指定路径
 * @param obj   pointer to a file explorer object
 * @param dir   指向路径的指针
 */
void lv_file_explorer_open_dir(lv_obj_t * obj, const char * dir);

/**********************
 *      MACROS
 **********************/

#endif  /*LV_USE_FILE_EXPLORER*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_FILE_EXPLORER_H*/
