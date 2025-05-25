/**
 * @file lv_table.h
 *
 */

#ifndef LV_TABLE_H
#define LV_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "../label/lv_label.h"

#if LV_USE_TABLE != 0

/*Testing of dependencies*/
#if LV_USE_LABEL == 0
#error "lv_table: lv_label is required. Enable it in lv_conf.h (LV_USE_LABEL 1)"
#endif

/*********************
 *      DEFINES
 *********************/
#define LV_TABLE_CELL_NONE 0XFFFF
LV_EXPORT_CONST_INT(LV_TABLE_CELL_NONE);

/**********************
 *      TYPEDEFS
 **********************/

enum _lv_table_cell_ctrl_t {
    LV_TABLE_CELL_CTRL_MERGE_RIGHT = 1 << 0,
    LV_TABLE_CELL_CTRL_TEXT_CROP   = 1 << 1,
    LV_TABLE_CELL_CTRL_CUSTOM_1    = 1 << 4,
    LV_TABLE_CELL_CTRL_CUSTOM_2    = 1 << 5,
    LV_TABLE_CELL_CTRL_CUSTOM_3    = 1 << 6,
    LV_TABLE_CELL_CTRL_CUSTOM_4    = 1 << 7,
};

#ifdef DOXYGEN
typedef _lv_table_cell_ctrl_t lv_table_cell_ctrl_t;
#else
typedef uint32_t lv_table_cell_ctrl_t;
#endif /*DOXYGEN*/

/*Data of cell*/
typedef struct {
    lv_table_cell_ctrl_t ctrl;
    void * user_data; /**< Custom user data*/
    char txt[1]; /**< Variable length array*/
} lv_table_cell_t;

/*Data of table*/
typedef struct {
    lv_obj_t obj;
    uint32_t col_cnt;
    uint32_t row_cnt;
    lv_table_cell_t ** cell_data;
    int32_t * row_h;
    int32_t * col_w;
    uint32_t col_act;
    uint32_t row_act;
} lv_table_t;

LV_ATTRIBUTE_EXTERN_DATA extern const lv_obj_class_t lv_table_class;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * 创建表对象
 * @param parent        pointer to an object, it will be the parent of the new table
 * @return              pointer to the created table
 */
lv_obj_t * lv_table_create(lv_obj_t * parent);

/*=====================
 * Setter functions
 *====================*/

/**
 * 设置单元格的值.
 * @param obj           指向Table对象的指针
 * @param row           行的id[0..row_cnt-1]
 * @param col           列的id[0..col_cnt-1]
 * @param txt           要在单元格中显示的文本。它将被复制并保存，因此在此函数调用后不需要此变量。
 * @note                如果需要，会自动添加新的roes/columns
 */
void lv_table_set_cell_value(lv_obj_t * obj, uint32_t row, uint32_t col, const char * txt);

/**
 * 设置单元格的值。将按表分配内存来存储文本。
 * @param obj           指向Table对象的指针
 * @param row           行的id[0..row_cnt-1]
 * @param col           列的id[0..col_cnt-1]
 * @param fmt           `类似printf的格式
 * @note                如果需要，会自动添加新的roes/columns
 */
void lv_table_set_cell_value_fmt(lv_obj_t * obj, uint32_t row, uint32_t col, const char * fmt,
                                 ...) LV_FORMAT_ATTRIBUTE(4, 5);

/**
 * 设置行数
 * @param obj           table pointer to a Table object
 * @param row_cnt       number of rows
 */
void lv_table_set_row_count(lv_obj_t * obj, uint32_t row_cnt);

/**
 * 设置列数
 * @param obj       table pointer to a Table object
 * @param col_cnt   number of columns.
 */
void lv_table_set_column_count(lv_obj_t * obj, uint32_t col_cnt);

/**
 * 设置列的宽度
 * @param obj       table pointer to a Table object
 * @param col_id    id of the column [0 .. LV_TABLE_COL_MAX -1]
 * @param w         width of the column
 */
void lv_table_set_column_width(lv_obj_t * obj, uint32_t col_id, int32_t w);

/**
 * 向单元格添加控制位。
 * @param obj       pointer to a Table object
 * @param row       id of the row [0 .. row_cnt -1]
 * @param col       id of the column [0 .. col_cnt -1]
 * @param ctrl      OR-ed values from ::lv_table_cell_ctrl_t
 */
void lv_table_add_cell_ctrl(lv_obj_t * obj, uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl);

/**
 * 清除单元格的控制位。
 * @param obj       pointer to a Table object
 * @param row       id of the row [0 .. row_cnt -1]
 * @param col       id of the column [0 .. col_cnt -1]
 * @param ctrl      OR-ed values from ::lv_table_cell_ctrl_t
 */
void lv_table_clear_cell_ctrl(lv_obj_t * obj, uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl);

/**
 * 将自定义用户数据添加到单元格中。
 * @param obj       pointer to a Table object
 * @param row       id of the row [0 .. row_cnt -1]
 * @param col       id of the column [0 .. col_cnt -1]
 * @param user_data pointer to the new user_data.
 *                  Should be allocated by `lv_malloc`,
 *                  and it will be freed automatically when the table is deleted or
 *                  when the cell is dropped due to lower row or column count.
 */
void lv_table_set_cell_user_data(lv_obj_t * obj, uint16_t row, uint16_t col, void * user_data);

/**
 * 设置所选单元格
 * @param obj       pointer to a table object
 * @param row       id of the cell row to select
 * @param col       id of the cell column to select
 */
void lv_table_set_selected_cell(lv_obj_t * obj, uint16_t row, uint16_t col);

/*=====================
 * Getter functions
 *====================*/

/**
 * 获取单元格的值。
 * @param obj       pointer to a Table object
 * @param row       id of the row [0 .. row_cnt -1]
 * @param col       id of the column [0 .. col_cnt -1]
 * @return          text in the cell
 */
const char * lv_table_get_cell_value(lv_obj_t * obj, uint32_t row, uint32_t col);

/**
 * 获取行数。
 * @param obj       table pointer to a Table object
 * @return          number of rows.
 */
uint32_t lv_table_get_row_count(lv_obj_t * obj);

/**
 * 获取列数。
 * @param obj       table pointer to a Table object
 * @return          number of columns.
 */
uint32_t lv_table_get_column_count(lv_obj_t * obj);

/**
 * 获取列的宽度
 * @param obj       table pointer to a Table object
 * @param col       id of the column [0 .. LV_TABLE_COL_MAX -1]
 * @return          width of the column
 */
int32_t lv_table_get_column_width(lv_obj_t * obj, uint32_t col);

/**
 * 获取单元格是否具有控制位
 * @param obj       pointer to a Table object
 * @param row       id of the row [0 .. row_cnt -1]
 * @param col       id of the column [0 .. col_cnt -1]
 * @param ctrl      OR-ed values from ::lv_table_cell_ctrl_t
 * @return          true: all control bits are set; false: not all control bits are set
 */
bool lv_table_has_cell_ctrl(lv_obj_t * obj, uint32_t row, uint32_t col, lv_table_cell_ctrl_t ctrl);

/**
 * 获取所选单元格（按下和/或聚焦）
 * @param obj       pointer to a table object
 * @param row       pointer to variable to store the selected row (LV_TABLE_CELL_NONE: if no cell selected)
 * @param col       pointer to variable to store the selected column  (LV_TABLE_CELL_NONE: if no cell selected)
 */
void lv_table_get_selected_cell(lv_obj_t * obj, uint32_t * row, uint32_t * col);

/**
 * 将自定义用户数据获取到单元格。
 * @param obj       pointer to a Table object
 * @param row       id of the row [0 .. row_cnt -1]
 * @param col       id of the column [0 .. col_cnt -1]
 */
void * lv_table_get_cell_user_data(lv_obj_t * obj, uint16_t row, uint16_t col);

/**********************
 *      MACROS
 **********************/

#endif /*LV_USE_TABLE*/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_TABLE_H*/
