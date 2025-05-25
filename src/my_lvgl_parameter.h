
/*
LV_FONT_DECLARE(clock_rog_38px);
LV_FONT_DECLARE(MiSans_Bold_14px);
LV_FONT_DECLARE(ArialRoundedMTBold_14px);
LV_FONT_DECLARE(DinkieBitmap_10px); 
LV_FONT_DECLARE(MiSans_Normal_16px); 
*/
  /*
    0xf06e 眼睛打开 LV_SYMBOL_EYE_OPEN
    0xf070 眼睛关闭 LV_SYMBOL_EYE_CLOSE
    0xf07b 文件夹 LV_SYMBOL_DIRECTORY
    0xf03e 图片 LV_SYMBOL_IMAGE
    0xf158 文件 LV_SYMBOL_FILE ？
    0xF001 音频 LV_SYMBOL_AUDIO
    0xf15b 文件 LV_SYMBOL_FILE 
    0xf3e5 返回 LV_SYMBOL_BACK
  */
int8_t key_code;

#define GRADUAL_ANIM_TIME 600                    // 渐入渐出动画
#define MSGBOX_ANIM_TIME 280                     // 弹窗进入退出持续时间
#define MSGBOX_ANIM_TIME2 MSGBOX_ANIM_TIME + 150 // 弹窗进入退出等待
#define BUTTON_ANIM_TIME 160                     // 按钮收缩动画
#define PAGE_SWITCH_ANIM_TIME 300                // 上下左右页面切换动画
#define LABEL_ANIM_TIME 300                      // 标签抖动动画

#define LV_SYMBOL_BACK          "\xEF\x8F\xA5" // 62437, 0xf3e5 返回       
#define LV_SYMBOL_LETF_TRI_ARR  "\xEF\x83\x99" // 61657, 0xf0d9 左三角箭头 
#define LV_SYMBOL_RIGHT_TRI_ARR "\xEF\x83\x9A" // 61658, 0xf0da 右三角箭头 
#define LV_SYMBOL_BOOT          "\xEF\x80\xAD" // 61485, 0xf02d 书本

#define LV_SYMBOL_HORSEHEAD "\xEF\x9e\xab" // 63403, 0xf7ab 马头
#define LV_SYMBOL_SATELLITE "\xEF\x9e\xbF" // 63423, 0xf7bf 卫星
#define LV_SYMBOL_MOUNTAIN "\xEF\x9d\xbb"  // 63355, 0xf77b 山

//圆形表情
#define LV_SYMBOL_LAUGH "\xEF\x96\x99"        // 62873, 0xf599 咧嘴微笑
//#define LV_SYMBOL_LAUGH_BEAM "\xEF\x96\x9A"   // 62874, 0xf59a 咧嘴弯眼微笑
//#define LV_SYMBOL_LAUGH_SQUINT "\xEF\x96\x9B" // 62875, 0xf59b 咧嘴大笑
//#define LV_SYMBOL_LAUGH_WINK "\xEF\x96\x9C"   // 62876, 0xf59c 咧嘴眨眼微笑

#define LV_SYMBOL_FROWN_OPEN "\xEF\x95\xbA"       // 62842, 0xf57a 皱眉头
//#define LV_SYMBOL_FLUSHED "\xEF\x95\xb9"          // 62841, 0xf579 脸红的
//#define LV_SYMBOL_MEH_ROLLING_EYES "\xEF\x96\xA5" // 62885, 0xf5a5 翻白眼
//#define LV_SYMBOL_GRIN_BEAM_SWEAT "\xEF\x96\x85"  // 62851, 0xf585 咧嘴大汗淋漓

//空气质量的界面图标
#define LV_SYMBOL_TEMP "\xEE\x98\xB0" // 58928, 0xE630 温度
#define LV_SYMBOL_HUMI "\xEE\x98\x8F" // 58895, 0xE60F 湿度
#define LV_SYMBOL_CO2 "\xEE\x9A\xB1"  // 59057, 0xE6B1 co2
#define LV_SYMBOL_TVOC "\xEE\x98\x9D" // 58909, 0xE61D TVOC
#define LV_SYMBOL_HCHO "\xEE\x98\x8B" // 58891, 0xE60B HCHO


lv_obj_t *label_share[10] = {NULL}; // 通用标签
lv_obj_t *lv_obj_xk = NULL;        // 选框标签
lv_obj_t *box_share[2] = {NULL};   // 通用容器盒子

//时钟用的标签
lv_obj_t *label_batPer = NULL;     // 电池电量
lv_obj_t *label_timeHour = NULL;   // 小时标签
lv_obj_t *label_timeMinute = NULL; // 分钟标签
lv_obj_t *label_timeSecond = NULL; // 秒标签
lv_obj_t *label_timeDate = NULL;   // 月日星期标签
lv_obj_t *label_temp = NULL;       // cpu温度标签
lv_obj_t *bat_g = NULL;            // 电池绿色内容

lv_timer_t *lvTimer_share[2] = {NULL}; // 通用定时器
lv_timer_t *lvTimer_msgbox = NULL;     // 弹窗定时器

static lv_group_t *group_my;    // 我的组
static lv_group_t *group_mbox0; // 弹窗组0
static lv_group_t *group_mbox1; // 弹窗组1
static lv_group_t *group_old;   // 上一个弹窗组

// static lv_group_t *group_mbox2;      // 弹窗组2
static lv_style_t style_shadow;      // 不透明度样式
static lv_style_t style_squareShape; // 方形样式
static lv_style_t style_msgbox;      // 弹窗样式
static lv_style_t font_style;        // 字体样式

int8_t focusPos_old[10] = {0};  // 上一个界面的焦点位置
int8_t focusPos_old_index = -1; // 上一个界面的焦点位置索引

#define MY_COLOR_RED lv_color_make(255, 0, 0)       // 红
#define MY_COLOR_GREEN lv_color_make(0, 255, 0)     // 绿
#define MY_COLOR_BLUE lv_color_make(0, 0, 255)      // 蓝
#define MY_COLOR_CYAN lv_color_make(0, 255, 255)    // 青
#define MY_COLOR_MAGENTA lv_color_make(255, 0, 255) // 洋红
#define MY_COLOR_YELLOW lv_color_make(255, 255, 0)  // 黄色
#define MY_COLOR_WHITE lv_color_make(255, 255, 255) // 白
#define MY_COLOR_BLACK lv_color_make(0, 0, 0)       // 黑

#define KEY_MODE_RL     1 // 按键模式：左、右（可以触发LV_EVENT_KEY）
#define KEY_MODE_PN     0 // 按键模式：上一个焦点、下一个焦点（不能触发LV_EVENT_KEY）
#define FIRST_EVENT_ON  1 // 进入页面是有在回调里只执行一次的命令
#define FIRST_EVENT_OFF 0 // 没有在回调里只执行一次的命令

struct PAGE
{
  // 两个页面，切换时自动清除另外一个
  lv_obj_t *p[2] = {NULL, NULL};
  uint8_t index = 0;   // 当前的界面
  bool keyMode = 0;    // 按键模式
  bool firstEvent = 0; // 首次回调
};PAGE page;

// 弹窗状态 枚举
enum
{
  MBOX_STATE_SEND = 0, // 发送阶段
  MBOX_STATE_ENTER,    // 进入阶段
  MBOX_STATE_REMAIN,   // 停留阶段
  MBOX_STATE_TIMER,    // 定时器运行阶段
  MBOX_STATE_EXIT,     // 退出阶段
  //MBOX_STATE_CLEAR,    // 清空
  MBOX_STATE_FORCE,    // 强制发送
};
// 弹窗结构体
struct MBOX
{
  lv_obj_t *p = NULL;
  bool keyMode = 1;              // 按键模式
  uint8_t state = 0;             // 0-发送中 1-运行中 2-退出中 3-清空
  uint16_t recordTime = 0;       // 记录弹窗的整个运行时间，包括动画
  String title;                  // 标题
  String text;                   // 内容
  uint16_t time = 0;             // 弹窗的停留时间，不包括动画
  String button;                 // 是否有按钮，用换行隔开
  lv_event_cb_t event_cb = NULL; // 按钮的回调函数
};
MBOX mbox;
static uint8_t num[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                          11, 12, 13, 14, 15, 16, 17, 18, 19};

struct SetMenu
{
  int16_t min[10] = {0};   // 最小值
  int16_t max[10] = {0};   // 最大值
  uint16_t step[10] = {0}; // 步进值
  String unit[10];         // 单位
  uint8_t *num_u8[10] = {NULL};
  // uint16_t *num_u16[10] = {NULL};
};
SetMenu sm0;

// 通用数值
uint8_t shareNum[10] = {0};
float shareNum_f[10] = {0};