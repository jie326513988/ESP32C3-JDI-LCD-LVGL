void demo_label()
{
  /*更改活动屏幕的背景色*/
  // lv_obj_set_style_bg_color(lv_screen_active(), lv_color_make(255, 0, 255), LV_PART_MAIN);

  /*Create a white label, set its text and align it to the center*/
  // lv_obj_t * label = lv_label_create(lv_screen_active());
  // lv_label_set_text(label, "Hello world");
  // lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
  // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);

  /*lv_obj_t *ta1 = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta1, 70, 30);
  lv_obj_align(ta1, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_bg_color(ta1, lv_color_make(255, 0, 0), LV_STATE_DEFAULT);*/

  // 设置文本框的大小和位置
  /*
  lv_obj_t *ta1 = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta1, 70, 30);
  lv_obj_align(ta1, LV_ALIGN_CENTER, 0, 30);
  lv_obj_set_style_bg_color(ta1, lv_color_make(255, 0, 0), LV_STATE_DEFAULT); // rgb
  */

  // 设置文本框的大小和位置
  lv_obj_t *ta2 = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta2, 70, 30);
  lv_obj_align(ta2, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_bg_color(ta2, lv_color_make(0, 0, 255), LV_STATE_DEFAULT); // rgb

  lv_obj_t *label2 = lv_label_create(lv_scr_act());
  // lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL);
  // lv_obj_set_width(label2, 70 - 4);
  lv_obj_align(label2, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_text_color(label2, lv_color_make(255, 255, 255), LV_PART_MAIN); // 设置字体颜色
  // lv_label_set_text_fmt(label2, "%d", 123);
  lv_label_set_text(label2, "a ba a ba");

  // 设置文本框的大小和位置
  lv_obj_t *ta = lv_textarea_create(lv_scr_act());
  lv_obj_set_size(ta, 124, 30);
  lv_obj_align(ta, LV_ALIGN_CENTER, 0, -56);
  lv_obj_set_style_bg_color(ta, lv_color_make(0, 255, 0), LV_STATE_DEFAULT); // rgb

  lv_obj_t *label = lv_label_create(lv_scr_act());
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_set_width(label, 124 - 4);
  lv_label_set_text(label, "Hello Arduino, I'm LVGL! -V9.1.0");
  lv_obj_align(label, LV_ALIGN_CENTER, 0, -56);
}

void demo_img()
{
  // 1.准备一张图片
  LV_IMG_DECLARE(maomao);
  // 2.创建一个lv_img对象
  lv_obj_t *img1 = lv_image_create(lv_screen_active());
  // 3.给对象设置图片
  lv_image_set_src(img1, &maomao);
  // 4.设置图片位置
  lv_obj_align(img1, LV_ALIGN_BOTTOM_MID, 0, 0);
}

void demo_gif()
{
  /*
    // 1.准备一张图片
    LV_IMG_DECLARE(qft);
    // 2.创建一个lv_img对象
    lv_obj_t *gif1 = lv_gif_create(lv_screen_active());
    // 3.给对象设置图片
    lv_gif_set_src(gif1, &qft);
    // 4.设置图片位置
    lv_obj_align(gif1, LV_ALIGN_BOTTOM_MID, 0, 0);
  */

  // qft 千反田 tw 跳舞 xiaomai 小埋 yqs 摇汽水 liuhua 六花
  LV_IMG_DECLARE(liuhua);
  lv_obj_t *gif2 = lv_gif_create(lv_screen_active());
  lv_gif_set_src(gif2, &liuhua);
  lv_obj_align(gif2, LV_ALIGN_CENTER, 0, 0);
}

/*
void _lv_anim_core_init(void);                                                                  // 初始化。动画模块
void lv_anim_init(lv_anim_t *a);                                                                // 初始化一个动画变量
static inline void lv_anim_set_var(lv_anim_t *a, void *var);                                    // 设置一个变量为animate
static inline void lv_anim_set_exec_cb(lv_anim_t *a, lv_anim_exec_xcb_t exec_cb);               // 设置一个函数来动画' var '
static inline void lv_anim_set_time(lv_anim_t *a, uint32_t duration);                           // 设置动画的持续时间
static inline void lv_anim_set_delay(lv_anim_t *a, uint32_t delay);                             // 在开始动画前设置一个延迟
static inline void lv_anim_set_values(lv_anim_t *a, int32_t start, int32_t end);                // 设置动画的开始和结束值
static inline void lv_anim_set_custom_exec_cb(lv_anim_t *a, lv_anim_custom_exec_cb_t exec_cb);  //*类似于' lv_anim_set_exec_cb '但' lv_anim_custom_exec_cb_t '接收' lv_anim_t * '作为它的第一个参数而不是' void * '。当LVGL被绑定到其他语言时，这个函数可能会被使用使用' lv_anim_t * '作为第一个参数更一致。
static inline void lv_anim_set_path_cb(lv_anim_t *a, lv_anim_path_cb_t path_cb);                // 设置动画的路径(曲线)
static inline void lv_anim_set_start_cb(lv_anim_t *a, lv_anim_start_cb_t start_cb);             // 设置一个函数调用时，动画真正开始(考虑' delay ')
static inline void lv_anim_set_get_value_cb(lv_anim_t *a, lv_anim_get_value_cb_t get_value_cb); // 设置一个函数使用变量的当前值并设置起始值和结束值相对于返回的当前值。
static inline void lv_anim_set_ready_cb(lv_anim_t *a, lv_anim_ready_cb_t ready_cb);             // 当动画准备好时，设置一个函数调用
static inline void lv_anim_set_playback_time(lv_anim_t *a, uint32_t time);                      // 回放时间，使动画回放时，正方向准备好了
static inline void lv_anim_set_playback_delay(lv_anim_t *a, uint32_t delay);                    // 开始动画时候回放延时，使动画回放时，正向方向准备好了
static inline void lv_anim_set_repeat_count(lv_anim_t *a, uint16_t cnt);                        // 让动画重复本身。
static inline void lv_anim_set_repeat_delay(lv_anim_t *a, uint32_t delay);                      // 在重复动画之前设置一个延迟。
static inline void lv_anim_set_early_apply(lv_anim_t *a, bool en);                              // 设置是否动画应该立即应用或仅当延迟过期。
static inline void lv_anim_set_user_data(lv_anim_t *a, void *user_data);                        // 设置动画的自定义用户数据字段。
lv_anim_t *lv_anim_start(const lv_anim_t *a);                                                   // 创建一个动画
static inline uint32_t lv_anim_get_delay(lv_anim_t *a);                                         // 在开始动画之前获得一个延迟
bool lv_anim_del(void *var, lv_anim_exec_xcb_t exec_cb);                                        // 用给定的animator函数删除一个变量的动画
void lv_anim_del_all(void);                                                                     // 删除所有动画动画
lv_anim_t *lv_anim_get(void *var, lv_anim_exec_xcb_t exec_cb);                                  // 获取一个变量及其exec_cb的动画。
static inline bool lv_anim_custom_del(lv_anim_t *a, lv_anim_custom_exec_cb_t exec_cb);          //*通过从' a '中获取动画变量来删除一个动画。只有带有exec_cb的动画才会被删除。
                                                                                                // 这个函数存在是因为它是逻辑上所有的动物。函数接收一个' lv_anim_t '作为他们的
                                                                                                // 第一个参数。这在C语言中是不实用的，但有可能API更顺位，更容易生成绑定。
static inline lv_anim_t *lv_anim_custom_get(lv_anim_t *a, lv_anim_custom_exec_cb_t exec_cb);    // 设置动画的自定义用户数据字段获取一个变量及其exec_cb的动画。这个函数存在是因
                                                                                                // 为它是逻辑上所有的动物。函数接收一个' lv_anim_t '作为他们的第一个参数。这在
                                                                                                // C语言中是不实用的，但有可能API更顺位，更容易生成绑定。
uint16_t lv_anim_count_running(void);                                                           // 获取当前运行动画的数量
uint32_t lv_anim_speed_to_time(uint32_t speed, int32_t start, int32_t end);                     // 计算动画的时间与给定的速度和开始和结束值
void lv_anim_refr_now(void);                                                                    // 手动刷新动画状态。
*/