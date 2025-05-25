/**
 *@file lv_conf.h
 *v9.1.1-dev的配置文件
 */
/*
*将此文件复制为`lv_conf.h`
1.就在“lvgl”文件夹旁边
2.或任何其他地方，以及
*-定义`LV_CONF_INCLUDE_IMPLE`
*-将路径添加为包含路径
*/
/*clang格式关闭*/
#if 1 /*将其设置为“1”以启用内容*/

#ifndef LV_CONF_H
#define LV_CONF_H

/*如果您需要在此处包含任何内容，请在`__ASSEMBLY_`保护区内执行*/
#if 0 && defined(__ASSEMBLY__)
#include "my_include.h"
#endif

/*====================
   COLOR SETTINGS
 *====================*/

/*Color depth: 8 (A8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888)*/
#define LV_COLOR_DEPTH 16

/*=========================
STDLIB包装设置
*=========================*/
/*可能的值
 *-LV_STDLIB_BUILTIN:LVGL的内置实现
 *-LV_STDLIB_CLIB：标准C函数，如malloc、strlen等
 *-LV_STDLIB_MICROPYTHON:MICROPYTHON实现
 *-LV_STDLIB_RTTHREAD:RT线程实现
 *-LV_STDLIB_CUSTOM：外部实现功能
 */
#define LV_USE_STDLIB_MALLOC LV_STDLIB_CLIB
#define LV_USE_STDLIB_STRING LV_STDLIB_CLIB
#define LV_USE_STDLIB_SPRINTF LV_STDLIB_CLIB

#define LV_STDINT_INCLUDE <stdint.h>
#define LV_STDDEF_INCLUDE <stddef.h>
#define LV_STDBOOL_INCLUDE <stdbool.h>
#define LV_INTTYPES_INCLUDE <inttypes.h>
#define LV_LIMITS_INCLUDE <limits.h>
#define LV_STDARG_INCLUDE <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
/*可用于“lv_malloc（）”的内存大小（以字节为单位）（>=2kB）*/
#define LV_MEM_SIZE (64 * 1024U) /*[bytes]*/

/*“lv_malloc（）”的内存扩展大小（以字节为单位）*/
#define LV_MEM_POOL_EXPAND_SIZE 0

/*设置内存池的地址，而不是将其分配为普通数组。也可以在外部SRAM中*/
#define LV_MEM_ADR 0 /*0: unused*/
                     /*不提供地址，而是提供一个内存分配器，该内存分配器将被调用以获取LVGL的内存池。例如my_malloc*/
#if LV_MEM_ADR == 0
#undef LV_MEM_POOL_INCLUDE
#undef LV_MEM_POOL_ALLOC
#endif
#endif /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
   HAL SETTINGS
 *====================*/

/*默认显示刷新、输入设备读取和动画步骤周期*/
#define LV_DEF_REFR_PERIOD 10 /*[ms]*/

/*默认每英寸点数。用于初始化默认大小，如小部件大小、样式填充。
 *（不那么重要，您可以调整它以修改默认大小和空间）*/
#define LV_DPI_DEF 130 /*[px/inch]*/

/*=================
 * OPERATING SYSTEM
 *=================*/
/*选择要使用的操作系统。可能的选项：
 * - LV_OS_NONE
 * - LV_OS_PTHREAD
 * - LV_OS_FREERTOS
 * - LV_OS_CMSIS_RTOS2
 * - LV_OS_RTTHREAD
 * - LV_OS_WINDOWS
 * - LV_OS_MQX
 * - LV_OS_CUSTOM */
#define LV_USE_OS LV_OS_NONE

#if LV_USE_OS == LV_OS_CUSTOM
#define LV_OS_CUSTOM_INCLUDE <stdint.h>
#endif

/*========================
 * RENDERING CONFIGURATION
 *========================*/

// 每行像素数据按X字节对齐
#define LV_DRAW_BUF_STRIDE_ALIGN 1

// 缓冲区起始地址按X字节对齐
#define LV_DRAW_BUF_ALIGN 1

/* 如果小部件具有 `style_opa < 255`（不是 `bg_opa`、`text_opa` 等）或不是 NORMAL 混合模式
 * 它会在渲染之前缓冲到“简单”层中。小部件可以缓冲成较小的块。
 * “变换层”（如果设置了 `transform_angle/zoom`）使用较大的缓冲区，不能以块的形式绘制。 */

/*简单层块的目标缓冲区大小。*/
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE (24 * 1024) /*[bytes]*/

/*绘图线程的堆栈大小。
 *注意：如果启用了FreeType或ThorVG，建议将其设置为32KB或更大。
 */
#define LV_DRAW_THREAD_STACK_SIZE (0 * 1024) /*[bytes]*/

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW == 1

/*
 *有选择地禁用颜色格式支持以减小代码大小。
 *注意：某些功能在内部使用某些颜色格式，例如。
 *-梯度使用RGB888
 *-具有透明度的位图可以使用ARGB888
 */

#define LV_DRAW_SW_SUPPORT_RGB565 1
#define LV_DRAW_SW_SUPPORT_RGB565A8 1
#define LV_DRAW_SW_SUPPORT_RGB888 0
#define LV_DRAW_SW_SUPPORT_XRGB8888 0
#define LV_DRAW_SW_SUPPORT_ARGB8888 0
#define LV_DRAW_SW_SUPPORT_L8 0
#define LV_DRAW_SW_SUPPORT_AL88 0
#define LV_DRAW_SW_SUPPORT_A8 0

/*设置绘制单位的数量。
 *>1需要在`LV_USE_OS中启用操作系统`
 *>1表示多个线程将并行渲染屏幕*/
#define LV_DRAW_SW_DRAW_UNIT_CNT 1

/*使用Arm-2D加速sw渲染*/
#define LV_USE_DRAW_ARM2D_SYNC 0

/*启用本地氦气组件进行编译*/
#define LV_USE_NATIVE_HELIUM_ASM 0

/*0：使用一个简单的渲染器，该渲染器只能绘制带有渐变、图像、文本和直线的简单矩形
 *1：使用能够绘制圆角、阴影、斜线和圆弧的复杂渲染器*/
#define LV_DRAW_SW_COMPLEX 1

#if LV_DRAW_SW_COMPLEX == 1
/*允许缓冲一些阴影计算。
 *LV_DRAW_SW_SHADOW_CACHE_SIZE是要缓冲的最大阴影大小，其中阴影大小为“SHADOW_width+radius”`
 *缓存具有LV_DRAW_SW_SHADOW_CACHE_SIZE^2 RAM成本*/
#define LV_DRAW_SW_SHADOW_CACHE_SIZE 0

/*设置最大缓存圆数据的数量。
 *保存1/4圆的周长用于消除混叠
 *半径*4字节用于每个圆（保存最常用的半径）
 *0:禁用缓存*/

#define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
#endif

#define LV_USE_DRAW_SW_ASM LV_DRAW_SW_ASM_NONE

#if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
#define LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
#endif

/*允许在软件中绘制复杂的渐变：角度为线性、径向或圆锥形*/
#define LV_USE_DRAW_SW_COMPLEX_GRADIENTS 0
#endif

/*在iMX RTxxx平台上使用恩智浦的VG Lite GPU*/
#define LV_USE_DRAW_VGLITE 0

#if LV_USE_DRAW_VGLITE
/*对于屏幕尺寸>352像素的情况，建议启用blit质量降级解决方案*/
#define LV_USE_VGLITE_BLIT_SPLIT 0

#if LV_USE_OS
/*启用VGLite异步绘制。对多个任务进行排队，并将它们闪存一次到GPU*/
#define LV_USE_VGLITE_DRAW_ASYNC 1
#endif

/* 启用 VGLite 断言。 */
#define LV_USE_VGLITE_ASSERT 0
#endif

/* 在 iMX RTxxx 平台上使用 NXP 的 PXP。 */
#define LV_USE_DRAW_PXP 0

#if LV_USE_DRAW_PXP
/* 启用 PXP 断言。 */
#define LV_USE_PXP_ASSERT 0
#endif

/* 在 RA 平台上使用 Renesas Dave2D。 */
#define LV_USE_DRAW_DAVE2D 0

/* 使用缓存的 SDL 纹理进行绘制*/
#define LV_USE_DRAW_SDL 0

/* 使用 VG-Lite GPU。 */
#define LV_USE_DRAW_VG_LITE 0

#if LV_USE_DRAW_VG_LITE
/* 启用 VG-Lite 自定义外部“gpu_init()”函数 */
#define LV_VG_LITE_USE_GPU_INIT 0

/* 启用 VG-Lite 断言。 */
#define LV_VG_LITE_USE_ASSERT 0

/* VG-Lite 刷新提交触发阈值。GPU 将尝试批量处理这些绘制任务。 */
#define LV_VG_LITE_FLUSH_MAX_COUNT 8

/* 启用边框以模拟阴影
 * 注意：这通常会提高性能，
 * 但不能保证与软件相同的渲染质量。 */
#define LV_VG_LITE_USE_BOX_SHADOW 0

/* VG-Lite 渐变最大缓存数。
 * 注意：单个渐变图像的内存使用量为 4K 字节。
 */
#define LV_VG_LITE_GRAD_CACHE_CNT 32

#endif

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/

/*-------------
 * Logging
 *-----------*/

/*启用日志模块*/
#define LV_USE_LOG 1
#if LV_USE_LOG

/*添加日志的重要性：
 *LV_LOG_LEVEL_TRACE大量日志提供详细信息
 *LV_LOG_LEVEL_INFO记录重要事件
 *LV_LOG_LEVEL_WARN如果发生了不必要的事情但没有引起问题，则记录
 *LV_LOG_LEVEL_ERROR系统可能出现故障时的唯一关键问题
 *LV_LOG_LEVEL_USER仅用户添加的日志
 *LV_LOG_LEVEL_NONE不记录任何内容*/
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

/*1：使用“printf”打印日志；
 *0:用户需要使用`lv_log_register_print_cb（）注册回调`*/
#define LV_LOG_PRINTF 0

/*设置回调以打印日志。
 *例如`my_print`。原型应该是`void my_print（lv_log_level_t级别，const char*buf）`
 *可以被`lv_log_register_print_cb覆盖`*/
// #定义LV_LOG_PRINT_CB

/*1：启用打印时间戳；
 *0:禁用打印时间戳*/
#define LV_LOG_USE_TIMESTAMP 0

/*1：打印日志的文件和行号；
 *0:不打印日志的文件和行号*/
#define LV_LOG_USE_FILE_LINE 1

/*在生成大量日志的模块中启用/禁用LV_LOG_TRACE*/
#define LV_LOG_TRACE_MEM 1
#define LV_LOG_TRACE_TIMER 1
#define LV_LOG_TRACE_INDEV 1
#define LV_LOG_TRACE_DISP_REFR 1
#define LV_LOG_TRACE_EVENT 1
#define LV_LOG_TRACE_OBJ_CREATE 1
#define LV_LOG_TRACE_LAYOUT 1
#define LV_LOG_TRACE_ANIM 1
#define LV_LOG_TRACE_CACHE 1

#endif /*LV_USE_LOG*/

/*-------------
 * Asserts
 *-----------*/

/*如果操作失败或发现无效数据，请启用断言。
 *如果启用LV_USE_LOG，则故障时将打印错误消息*/
#define LV_USE_ASSERT_NULL 1          // 检查参数是否为NULL。（非常快，推荐）
#define LV_USE_ASSERT_MALLOC 1        // 检查内存是否已成功分配。（非常快，推荐）
#define LV_USE_ASSERT_STYLE 0         // 检查样式是否正确初始化。（非常快，推荐）
#define LV_USE_ASSERT_MEM_INTEGRITY 0 // 在关键操作后检查“LV_MEM”的完整性。缓慢的
#define LV_USE_ASSERT_OBJ 0           // 检查对象的类型和存在（例如未删除）。缓慢的

/*当断言发生时添加自定义处理程序，例如重新启动MCU*/
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while (1); // 默认情况下停止

/*-------------
 * Debug
 *-----------*/

/*1：在重新绘制的区域上随机绘制彩色矩形*/
#define LV_USE_REFR_DEBUG 0

/*1:为ARGB层绘制红色覆盖层，为RGB层绘制绿色覆盖层*/
#define LV_USE_LAYER_DEBUG 0

/*1：为每个Draw_unit的任务绘制不同颜色的覆盖图。
 *还要在白色背景上添加绘图单元的索引号。
 *对于图层，在黑色背景上添加绘制单位的索引号*/
#define LV_USE_PARALLEL_DRAW_DEBUG 0

/*-------------
 * Others
 *-----------*/

#define LV_ENABLE_GLOBAL_CUSTOM 0
#if LV_ENABLE_GLOBAL_CUSTOM
/*Header to include for the custom 'lv_global' function"*/
#define LV_GLOBAL_CUSTOM_INCLUDE <stdint.h>
#endif

/*默认缓存大小（以字节为单位）。
 *由 `lv_lodepng` 等图像解码器使用，将解码后的图像保存在内存中。
 *如果大小未设置为 0，则当缓存已满时，解码器将无法解码。
 *如果大小为 0，则不启用缓存功能，解码后的内存将在使用后立即释放。*/
#define LV_CACHE_DEF_SIZE 4096

/*图像头缓存条目的默认数量。缓存用于存储图像的头
 *主要逻辑类似于`LV_CACHE_DEF_SIZE`，但用于图像头。*/
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 0

/*每个渐变允许的停止数。增加此值以允许更多停止。
 *这会为每个额外的停止添加 (sizeof(lv_color_t) + 1) 个字节*/
#define LV_GRADIENT_MAX_STOPS 2

/*调整颜色混合函数舍入。GPU 可能会以不同的方式计算颜色混合（混合）。
 * 0：向下舍入，64：从 x.75 向上舍入，128：从一半向上舍入，192：从 x.25 向上舍入，254：向上舍入 */
#define LV_COLOR_MIX_ROUND_OFS 0

/* 为每个 lv_obj_t 添加 2 x 32 位变量以加快获取样式属性的速度 */
#define LV_OBJ_STYLE_CACHE 1

/* 向 `lv_obj_t` 添加 `id` 字段 */
#define LV_USE_OBJ_ID 0

/* 创建 obj 时自动分配 ID */
#define LV_OBJ_ID_AUTO_ASSIGN LV_USE_OBJ_ID

/*使用内置的 obj ID 处理程序函数：
 * - lv_obj_assign_id：在创建小部件时调用。为每个小部件类使用单独的计数器作为 ID。
 * - lv_obj_id_compare：比较 ID 以确定它是否与请求的值匹配。
 * - lv_obj_stringify_id：返回例如“button3”
 * - lv_obj_free_id：不执行任何操作，因为没有为 ID 分配内存。
 * 禁用时，这些函数需要由用户实现。*/
#define LV_USE_OBJ_ID_BUILTIN 1

/*使用 obj 属性设置/获取 API*/
#define LV_USE_OBJ_PROPERTY 0

/*启用属性名称支持*/
#define LV_USE_OBJ_PROPERTY_NAME 1

/*VG-Lite 模拟器 */
/*要求：LV_USE_THORVG_INTERNAL 或 LV_USE_THORVG_EXTERNAL */
#define LV_USE_VG_LITE_THORVG 0

#if LV_USE_VG_LITE_THORVG

/*启用 LVGL 的混合模式支持*/
#define LV_VG_LITE_THORVG_LVGL_BLEND_SUPPORT 0

/*启用 YUV 颜色格式支持*/
#define LV_VG_LITE_THORVG_YUV_SUPPORT 0

/*启用线性渐变扩展支持*/
#define LV_VG_LITE_THORVG_LINEAR_GRADIENT_EXT_SUPPORT 0

/*启用 16 像素对齐*/
#define LV_VG_LITE_THORVG_16PIXELS_ALIGN 1

/*缓冲区地址对齐*/
#define LV_VG_LITE_THORVG_BUF_ADDR_ALIGN 64

/*启用多线程渲染*/
#define LV_VG_LITE_THORVG_THREAD_RENDER 0

#endif

/*========================
 * 编译器设置
 *=======================*/

/*对于大端系统，设置为 1*/
#define LV_BIG_ENDIAN_SYSTEM 0

/*为 `lv_tick_inc` 函数定义自定义属性*/
#define LV_ATTRIBUTE_TICK_INC

/*为 `lv_timer_handler` 函数定义自定义属性*/
#define LV_ATTRIBUTE_TIMER_HANDLER

/*为 `lv_display_flush_ready` 函数定义自定义属性*/
#define LV_ATTRIBUTE_FLUSH_READY

/*缓冲区所需的对齐大小*/
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1

/*将在需要对齐内存的地方添加（默认情况下，使用 -Os 数据可能不会与边界对齐）。
 * 例如 __attribute__((aligned(4)))*/
#define LV_ATTRIBUTE_MEM_ALIGN

/*用于标记大型常量数组（例如字体的位图）的属性*/
#define LV_ATTRIBUTE_LARGE_CONST

/*用于 RAM 中大型数组声明的编译器前缀*/
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY

/*将性能关键函数放入更快的内存（例如 RAM）*/
#define LV_ATTRIBUTE_FAST_MEM

/*将整数常量导出到绑定。此宏与 LV_<CONST> 形式的常量一起使用，
 *还应出现在 LVGL 绑定 API（例如 MicroPython）上。*/
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning /*默认值仅防止 GCC 警告*/

/*以此为前缀为所有全局外部数据*/
#define LV_ATTRIBUTE_EXTERN_DATA

/*使用 `float` 作为 `lv_value_precise_t` */
#define LV_USE_FLOAT 0

/*==================
 *   FONT USAGE
 *===================*/

/*Montserrat fonts with ASCII range and some symbols using bpp = 4
 *https://fonts.google.com/specimen/Montserrat*/
#define LV_FONT_MONTSERRAT_8 0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 0
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/*展示特殊功能*/
#define LV_FONT_MONTSERRAT_28_COMPRESSED 0 /*bpp = 3*/
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW 0 /*希伯来语、阿拉伯语、波斯语字母及其所有形式*/
#define LV_FONT_SIMSUN_14_CJK 0            /*1000 个最常见的 CJK 部首*/
#define LV_FONT_SIMSUN_16_CJK 0            /*1000 个最常见的 CJK 部首*/

/*像素完美的单空间字体*/
#define LV_FONT_UNSCII_8 0
#define LV_FONT_UNSCII_16 0

/*可以在此处声明自定义字体。
 *您也可以使用这些字体作为默认字体，它们将在全局范围内可用。
 *例如#define LV_FONT_CUSTOM_DECLARE LV_FONT_DECLARE（my_FONT_1）LV_FONT_DECLARE（my_FONT_2）*/
#define LV_FONT_CUSTOM_DECLARE LV_FONT_DECLARE(MISans_16px)

/*始终设置默认字体*/
#define LV_FONT_DEFAULT &MISans_16px // lv_font_montserrat_14 // MISans_16px

/*启用处理大字体和/或包含大量字符的字体。
 *限制取决于字体大小、字体大小和bpp。
 *如果字体需要，将触发编译器错误.*/
#define LV_FONT_FMT_TXT_LARGE 0

/*启用/禁用对压缩字体的支持.*/
#define LV_USE_FONT_COMPRESSED 0

/*未找到图示符dsc时启用绘图占位符*/
#define LV_USE_FONT_PLACEHOLDER 1

/*=================
 *  TEXT SETTINGS
 *=================*/

/**
 * 为字符串选择字符编码。
 * 您的 IDE 或编辑器应具有相同的字符编码
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/* 可以在这些字符上中断（换行）文本 */
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

/*如果一个单词至少这么长，则会在“最漂亮”的地方中断
 *若要禁用，请将其设置为 <= 0 的值*/
#define LV_TXT_LINE_BREAK_LONG_LEN 0

/*长单词中在换行前一行中放置的最少字符数。
 *取决于 LV_TXT_LINE_BREAK_LONG_LEN。*/
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3

/*长单词中在换行后一行中放置的最少字符数。
 *取决于 LV_TXT_LINE_BREAK_LONG_LEN。*/
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/*支持双向文本。允许混合从左到右和从右到左的文本。
 *方向将根据 Unicode 双向算法进行处理：
 *https://www.w3.org/International/articles/inline-bidi-markup/uba-basics*/
#define LV_USE_BIDI 0
#if LV_USE_BIDI
/*设置默认方向。支持的值：
 *`LV_BASE_DIR_LTR` 从左到右
 *`LV_BASE_DIR_RTL` 从右到左
 *`LV_BASE_DIR_AUTO` 检测文本基本方向*/
#define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

/*启用阿拉伯语/波斯语处理
 *在这些语言中，字符应根据其在文本中的位置替换为另一种形式*/
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*==================
 * WIDGETS
 *================*/

/*Documentation of the widgets: https://docs.lvgl.io/latest/en/html/widgets/index.html*/

#define LV_WIDGETS_HAS_DEFAULT_VALUE 1

#define LV_USE_ANIMIMG 1 // 动画图像

#define LV_USE_ARC 0 // 圆弧

#define LV_USE_BAR 1 // 进度条

#define LV_USE_BUTTON 1  // 按钮

#define LV_USE_BUTTONMATRIX 0 //矩阵按钮

#define LV_USE_CALENDAR 0 //日历
#if LV_USE_CALENDAR
#define LV_CALENDAR_WEEK_STARTS_MONDAY 0
#if LV_CALENDAR_WEEK_STARTS_MONDAY
#define LV_CALENDAR_DEFAULT_DAY_NAMES            \
    {                                            \
        "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su" \
    }
#else
#define LV_CALENDAR_DEFAULT_DAY_NAMES            \
    {                                            \
        "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" \
    }
#endif

#define LV_CALENDAR_DEFAULT_MONTH_NAMES                                                                                          \
    {                                                                                                                            \
        "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" \
    }
#define LV_USE_CALENDAR_HEADER_ARROW 1
#define LV_USE_CALENDAR_HEADER_DROPDOWN 1
#define LV_USE_CALENDAR_CHINESE 0
#endif /*LV_USE_CALENDAR*/

#define LV_USE_CANVAS 0 //画布

#define LV_USE_CHART 0 //图表

#define LV_USE_CHECKBOX 0 //复选框

#define LV_USE_DROPDOWN 0 //Requires: lv_label 下拉列表

#define LV_USE_IMAGE 1 //Requires: lv_label //图像
 
#define LV_USE_IMAGEBUTTON 1  //图像按钮

#define LV_USE_KEYBOARD 0 //键盘

#define LV_USE_LABEL 1
#if LV_USE_LABEL
#define LV_LABEL_TEXT_SELECTION 1  /*启用选择标签文本*/
#define LV_LABEL_LONG_TXT_HINT 1   /*在标签中存储一些额外信息，以加快绘制非常长的文本的速度*/
#define LV_LABEL_WAIT_CHAR_COUNT 3 /*等待图表的计数*/
#endif

#define LV_USE_LED 0

#define LV_USE_LINE 1 //线条

#define LV_USE_LIST 0 //列表

#define LV_USE_LOTTIE 0 /*需要：lv_canvas、thorvg*/

#define LV_USE_MENU 0 //菜单

#define LV_USE_MSGBOX 0 //弹窗

#define LV_USE_ROLLER 0 /*需要：lv_label*/ //滚轮

#define LV_USE_SCALE 0 //标尺

#define LV_USE_SLIDER 0  // 滑动条 需要：lv_bar 

#define LV_USE_SPAN 0 //富文本
#if LV_USE_SPAN
/*一行文本可以包含最大数量的跨度描述符*/
#define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif

#define LV_USE_SPINBOX 0 //微调框

#define LV_USE_SPINNER 0 //环形加载器

#define LV_USE_SWITCH 1 //开关

#define LV_USE_TEXTAREA 0 /*Requires: lv_label*/  //拼音输入法
#if LV_USE_TEXTAREA != 0
#define LV_TEXTAREA_DEF_PWD_SHOW_TIME 3000 /*ms*/
#endif

#define LV_USE_TABLE 0 // 表格

#define LV_USE_TABVIEW 0 // 选项卡

#define LV_USE_TILEVIEW 0 // 平铺视图

#define LV_USE_WIN 0 // 窗口

/*==================
 * THEMES
 *==================*/

/*一个简单、令人印象深刻且非常完整的主题*/
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT

/*0：亮模式；1：暗模式*/
#define LV_THEME_DEFAULT_DARK 0

/*1：按下时启用增长*/
#define LV_THEME_DEFAULT_GROW 1

/*默认过渡时间（单位：[ms]）*/
#define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/*一个非常简单的主题，是自定义主题的良好起点*/
#define LV_USE_THEME_SIMPLE 1

/*专为单色显示器设计的主题*/
#define LV_USE_THEME_MONO 1

/*==================
 * LAYOUTS
 *==================*/
/*类似于 CSS 中的 Flexbox 的布局。*/
#define LV_USE_FLEX 1

/*类似于 CSS 中的 Grid 的布局。*/
#define LV_USE_GRID 0

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/

/* 通用 API 的文件系统接口 */

/*用于fopen、fread等的API*/
#define LV_USE_FS_STDIO 1
#if LV_USE_FS_STDIO
#define LV_FS_STDIO_LETTER '\A'    /*设置驱动器可访问的大写字母（例如“A”）*/
#define LV_FS_STDIO_PATH "/LFS/"   /*设置工作目录。文件/目录路径将附加到它。*/
#define LV_FS_STDIO_CACHE_SIZE 128 /*>0以在lv_fs_read（）中缓存此数量的字节*/
#endif

/*API for open, read, etc*/
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
#define LV_FS_POSIX_LETTER '\0'  /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#define LV_FS_POSIX_PATH ""      /*Set the working directory. File/directory paths will be appended to it.*/
#define LV_FS_POSIX_CACHE_SIZE 0 /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*API for CreateFile, ReadFile, etc*/
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
#define LV_FS_WIN32_LETTER '\0'  /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#define LV_FS_WIN32_PATH ""      /*Set the working directory. File/directory paths will be appended to it.*/
#define LV_FS_WIN32_CACHE_SIZE 0 /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*API for FATFS (needs to be added separately). Uses f_open, f_read, etc*/
#define LV_USE_FS_FATFS 0
#if LV_USE_FS_FATFS
#define LV_FS_FATFS_LETTER '\0'  /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#define LV_FS_FATFS_CACHE_SIZE 0 /*>0 to cache this number of bytes in lv_fs_read()*/
#endif

/*API for memory-mapped file access. */
#define LV_USE_FS_MEMFS 0
#if LV_USE_FS_MEMFS
#define LV_FS_MEMFS_LETTER '\0' /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#endif

/*API for LittleFs. */
#define LV_USE_FS_LITTLEFS 0
#if LV_USE_FS_LITTLEFS
#define LV_FS_LITTLEFS_LETTER '\0' /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#endif

/*API for Arduino LittleFs. */
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
#if LV_USE_FS_ARDUINO_ESP_LITTLEFS
#define LV_FS_ARDUINO_ESP_LITTLEFS_LETTER '\0' /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#endif

/*API for Arduino Sd. */
#define LV_USE_FS_ARDUINO_SD 0
#if LV_USE_FS_ARDUINO_SD
#define LV_FS_ARDUINO_SD_LETTER '\0'        /*Set an upper cased letter on which the drive will accessible (e.g. 'A')*/
#define LV_FS_ARDUINO_SD_CS_PIN 0           /*Set the pin connected to the chip select line of the SD card */
#define LV_FS_ARDUINO_SD_FREQUENCY 40000000 /*Set the frequency used by the chip of the SD CARD */
#endif

/*LODEPNG 解码器库*/
#define LV_USE_LODEPNG 0

/*PNG 解码器 (libpng) 库*/
#define LV_USE_LIBPNG 0

/*BMP 解码器库*/
#define LV_USE_BMP 0

/* JPG + split JPG 解码器库。
 * Split JPG 是针对嵌入式系统优化的自定义格式。*/
#define LV_USE_TJPGD 1

/* libjpeg-turbo 解码器库。
 * 支持完整的 JPEG 规范和高性能 JPEG 解码。*/
#define LV_USE_LIBJPEG_TURBO 0

/*GIF 解码器库*/
#define LV_USE_GIF 1
#if LV_USE_GIF
/*GIF 解码器加速*/
#define LV_GIF_CACHE_DECODE_DATA 1
#endif

/*将垃圾箱图像解码到RAM*/
#define LV_BIN_DECODER_RAM_LOAD 0

/*RLE解压库*/
#define LV_USE_RLE 0

/*QR码库*/
#define LV_USE_QRCODE 0

/*条形码库*/
#define LV_USE_BARCODE 0

/*FreeType库*/
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
/*让FreeType使用LVGL内存和文件移植*/
#define LV_FREETYPE_USE_LVGL_PORT 0

/*FreeType中字形的缓存数量，即可以缓存的字形数量。 *值越高，使用的内存就越多。*/
#define LV_FREETYPE_CACHE_FT_GLYPH_CNT 256
#endif

/* 内置 TTF 解码器 */
#define LV_USE_TINY_TTF 0
#if LV_USE_TINY_TTF
/* 启用从文件加载 TTF 数据 */
#define LV_TINY_TTF_FILE_SUPPORT 0
#endif

/*Rlottie 库*/
#define LV_USE_RLOTTIE 0

/* 启用矢量图形 API*/
#define LV_USE_VECTOR_GRAPHIC 0

/* 从 src/libs 文件夹启用 ThorVG（矢量图形库）*/
#define LV_USE_THORVG_INTERNAL 0

/* 假设 ThorVG 已安装并链接到项目，则启用它*/
#define LV_USE_THORVG_EXTERNAL 0

/*使用 lvgl 内置 LZ4 库*/
#define LV_USE_LZ4_INTERNAL 0

/*使用外部 LZ4 库*/
#define LV_USE_LZ4_EXTERNAL 0

/*用于图像解码和播放视频的 FFmpeg 库
 *支持所有主要图像格式，因此不要启用其他图像解码器*/
#define LV_USE_FFMPEG 0
#if LV_USE_FFMPEG
/*将输入信息转储到 stderr*/
#define LV_FFMPEG_DUMP_FORMAT 0
#endif

/*==================
 * OTHERS
 *==================*/

/*1：启用API为对象拍摄快照*/
#define LV_USE_SNAPSHOT 0

/*1：启用系统监视器组件*/
#define LV_USE_SYSMON 0
#if LV_USE_SYSMON
/*获取空闲百分比。例如uint32_t my_get_idle(void)*/
#define LV_SYSMON_GET_IDLE lv_timer_get_idle

/*1：显示CPU使用率和FPS计数
 *需要`LV_USE_SYSMON=1`*/
#define LV_USE_PERF_MONITOR 1
#if LV_USE_PERF_MONITOR
#define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_LEFT

/*0:在屏幕上显示性能数据，1:使用日志打印性能数据*/
#define LV_USE_PERF_MONITOR_LOG_MODE 1
#endif

/*1：显示已用内存和内存碎片
 *需要`LV_USE_STDLIB_MALLOC=LV_STDLIB_BUILTIN`
 *需要`LV_USE_SYSMON=1`*/
#define LV_USE_MEM_MONITOR 0
#if LV_USE_MEM_MONITOR
#define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT
#endif

#endif /*LV_USE_SYSMON*/

/*1:启用运行时性能探查器*/
#define LV_USE_PROFILER 0
#if LV_USE_PROFILER
/*1：启用内置分析器*/
#define LV_USE_PROFILER_BUILTIN 1
#if LV_USE_PROFILER_BUILTIN
/*默认分析器跟踪缓冲区大小*/
#define LV_PROFILER_BUILTIN_BUF_SIZE (16 * 1024) /*[bytes]*/
#endif

/*要包含分析器的标头*/
#define LV_PROFILER_INCLUDE "lvgl/src/misc/lv_profiler_builtin.h"

/*分析器起点函数*/
#define LV_PROFILER_BEGIN LV_PROFILER_BUILTIN_BEGIN

/*分析器终点函数*/
#define LV_PROFILER_END LV_PROFILER_BUILTIN_END

/*带有自定义标签的分析器起点函数*/
#define LV_PROFILER_BEGIN_TAG LV_PROFILER_BUILTIN_BEGIN_TAG

/*带有自定义标签的分析器端点函数*/
#define LV_PROFILER_END_TAG LV_PROFILER_BUILTIN_END_TAG
#endif

/*1: 启用Monkey测试*/
#define LV_USE_MONKEY 0

/*1: 启用网格导航*/
#define LV_USE_GRIDNAV 0

/*1: 启用lv_obj片段*/
#define LV_USE_FRAGMENT 0

/*1: 支持在标签或跨度窗口小部件中使用图像作为字体 */
#define LV_USE_IMGFONT 0

/*1：启用观察者模式实现*/
#define LV_USE_OBSERVER 1

/*1：启用拼音输入法*/
/*需要：lv_keyboard*/
#define LV_USE_IME_PINYIN 0
#if LV_USE_IME_PINYIN
/*1:使用默认词库*/
/*如果不使用默认词库，设置词库后务必使用`lv_ime_pinyin`*/
#define LV_IME_PINYIN_USE_DEFAULT_DICT 1
/*设置最多可以显示的候选面板数量*/
/*这个需要根据屏幕大小调整*/
#define LV_IME_PINYIN_CAND_TEXT_NUM 6

/*使用9键输入(k9)*/
#define LV_IME_PINYIN_USE_K9_MODE 1
#if LV_IME_PINYIN_USE_K9_MODE == 1
#define LV_IME_PINYIN_K9_CAND_TEXT_NUM 3
#endif /*LV_IME_PINYIN_USE_K9_MODE*/
#endif

/*1：启用文件资源管理器*/
/*需要：lv_table*/
#define LV_USE_FILE_EXPLORER 0
#if LV_USE_FILE_EXPLORER
/*路径的最大长度*/
#define LV_FILE_EXPLORER_PATH_MAX_LEN (128)
/*快速访问栏，1：使用，0：不使用*/
/*需要：lv_list*/
#define LV_FILE_EXPLORER_QUICK_ACCESS 0
#endif

/*==================
 * DEVICES
 *==================*/

/*使用SDL在PC上打开窗口并处理鼠标和键盘*/
#define LV_USE_SDL 0
#if LV_USE_SDL
#define LV_SDL_INCLUDE_PATH <SDL2/SDL.h>
#define LV_SDL_RENDER_MODE LV_DISPLAY_RENDER_MODE_DIRECT      /*LV_DISPLAY_RENDER_MODE_DIRECT is recommended for best performance*/
#define LV_SDL_BUF_COUNT 1                                    /*1 or 2*/
#define LV_SDL_FULLSCREEN 0                                   /*1: Make the window full screen by default*/
#define LV_SDL_DIRECT_EXIT 1                                  /*1: Exit the application when all SDL windows are closed*/
#define LV_SDL_MOUSEWHEEL_MODE LV_SDL_MOUSEWHEEL_MODE_ENCODER /*LV_SDL_MOUSEWHEEL_MODE_ENCODER/CROWN*/
#endif

/*Use X11 to open window on Linux desktop and handle mouse and keyboard*/
#define LV_USE_X11 0
#if LV_USE_X11
#define LV_X11_DIRECT_EXIT 1   /*Exit the application when all X11 windows have been closed*/
#define LV_X11_DOUBLE_BUFFER 1 /*Use double buffers for rendering*/
/*select only 1 of the following render modes (LV_X11_RENDER_MODE_PARTIAL preferred!)*/
#define LV_X11_RENDER_MODE_PARTIAL 1 /*Partial render mode (preferred)*/
#define LV_X11_RENDER_MODE_DIRECT 0  /*direct render mode*/
#define LV_X11_RENDER_MODE_FULL 0    /*Full render mode*/
#endif

/*Driver for /dev/fb*/
#define LV_USE_LINUX_FBDEV 0
#if LV_USE_LINUX_FBDEV
#define LV_LINUX_FBDEV_BSD 0
#define LV_LINUX_FBDEV_RENDER_MODE LV_DISPLAY_RENDER_MODE_PARTIAL
#define LV_LINUX_FBDEV_BUFFER_COUNT 0
#define LV_LINUX_FBDEV_BUFFER_SIZE 60
#endif

/*Use Nuttx to open window and handle touchscreen*/
#define LV_USE_NUTTX 0

#if LV_USE_NUTTX
#define LV_USE_NUTTX_LIBUV 0

/*Use Nuttx custom init API to open window and handle touchscreen*/
#define LV_USE_NUTTX_CUSTOM_INIT 0

/*Driver for /dev/lcd*/
#define LV_USE_NUTTX_LCD 0
#if LV_USE_NUTTX_LCD
#define LV_NUTTX_LCD_BUFFER_COUNT 0
#define LV_NUTTX_LCD_BUFFER_SIZE 60
#endif

/*Driver for /dev/input*/
#define LV_USE_NUTTX_TOUCHSCREEN 0

#endif

/*/dev/dri/card 的驱动程序*/
#define LV_USE_LINUX_DRM 0

/*TFT_eSPI 的接口*/
#define LV_USE_TFT_ESPI 0

/*evdev 输入设备的驱动程序*/
#define LV_USE_EVDEV 0

/*libinput 输入设备的驱动程序*/
#define LV_USE_LIBINPUT 0

#if LV_USE_LIBINPUT
#define LV_LIBINPUT_BSD 0

/*Full keyboard support*/
#define LV_LIBINPUT_XKB 0
#if LV_LIBINPUT_XKB
/*"setxkbmap -query" can help find the right values for your keyboard*/
#define LV_LIBINPUT_XKB_KEY_MAP                                                           \
    {                                                                                     \
        .rules = NULL, .model = "pc101", .layout = "us", .variant = NULL, .options = NULL \
    }
#endif
#endif

/*Drivers for LCD devices connected via SPI/parallel port*/
#define LV_USE_ST7735 0
#define LV_USE_ST7789 0
#define LV_USE_ST7796 0
#define LV_USE_ILI9341 0

#define LV_USE_GENERIC_MIPI (LV_USE_ST7735 | LV_USE_ST7789 | LV_USE_ST7796 | LV_USE_ILI9341)

/*Driver for Renesas GLCD*/
#define LV_USE_RENESAS_GLCDC 0

/*LVGL Windows后端*/
#define LV_USE_WINDOWS 0

/*使用OpenGL在PC上打开窗口并处理鼠标和键盘*/
#define LV_USE_OPENGLES 0
#if LV_USE_OPENGLES
#define LV_USE_OPENGLES_DEBUG 1 /* Enable or disable debug for opengles */
#endif

/*==================
 * EXAMPLES
 *==================*/

/*启用要与库一起构建的示例*/
#define LV_BUILD_EXAMPLES 0

/*===================
 * DEMO USAGE
 ====================*/

/*Show some widget. It might be required to increase `LV_MEM_SIZE` */
#define LV_USE_DEMO_WIDGETS 0

/*Demonstrate the usage of encoder and keyboard*/
#define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

/*Benchmark your system*/
#define LV_USE_DEMO_BENCHMARK 0

/*Render test for each primitives. Requires at least 480x272 display*/
#define LV_USE_DEMO_RENDER 0

/*Stress test for LVGL*/
#define LV_USE_DEMO_STRESS 0

/*Music player demo*/
#define LV_USE_DEMO_MUSIC 0
#if LV_USE_DEMO_MUSIC
#define LV_DEMO_MUSIC_SQUARE 0
#define LV_DEMO_MUSIC_LANDSCAPE 0
#define LV_DEMO_MUSIC_ROUND 0
#define LV_DEMO_MUSIC_LARGE 0
#define LV_DEMO_MUSIC_AUTO_PLAY 0
#endif

/*Flex 布局演示*/
#define LV_USE_DEMO_FLEX_LAYOUT 0

/*类似智能手机的多语言演示*/
#define LV_USE_DEMO_MULTILANG 0

/*Widget 转换演示*/
#define LV_USE_DEMO_TRANSFORM 0

/*演示滚动设置*/
#define LV_USE_DEMO_SCROLL 0

/*矢量图形演示*/
#define LV_USE_DEMO_VECTOR_GRAPHIC 0

/*--END OF LV_CONF_H--*/

#endif /*LV_CONF_H*/

#endif /*“内容启用”结束*/