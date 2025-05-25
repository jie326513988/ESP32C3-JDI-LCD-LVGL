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

  // 基本对象
  lv_obj_t *obj1 = lv_obj_create(lv_screen_active());
  lv_obj_set_scrollbar_mode(obj1, LV_SCROLLBAR_MODE_OFF);
  lv_obj_align(obj1, LV_ALIGN_TOP_MID, 0, 5);
  lv_obj_set_size(obj1, 72, 30);
  lv_obj_set_style_bg_color(obj1, MY_COLOR_GREEN, LV_STATE_DEFAULT);
  // 设置标签
  lv_obj_t *label = lv_label_create(obj1);
  lv_obj_set_scrollbar_mode(label, LV_SCROLLBAR_MODE_OFF);
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_width(label, 72);
  //lv_label_set_text(label, "Hello Arduino, I'm LVGL! -V9.1.0");
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

  // qft 千反田，tw 跳舞，xiaomai 小埋，yqs 摇汽水，liuhua 六花
  LV_IMG_DECLARE(liuhua);
  lv_obj_t *gif2 = lv_gif_create(lv_screen_active());
  lv_gif_set_src(gif2, &liuhua);
  lv_obj_align(gif2, LV_ALIGN_CENTER, 0, 0);
}

lv_point_precise_t *my_draw_rectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
  static lv_point_precise_t line_points[5]; // 静态数组，存储矩形的点
  line_points[0] = (lv_point_precise_t){x, y};
  line_points[1] = (lv_point_precise_t){x + w, y};
  line_points[2] = (lv_point_precise_t){x + w, y + h};
  line_points[3] = (lv_point_precise_t){x, y + h};
  line_points[4] = (lv_point_precise_t){x, y}; // 闭合矩形
  return line_points;
}

// 开机时进入哪个界面
void pageStartupEnters()
{
  // 更新闹钟时间差
  updatealarmClockDifference(1);

  // 0点唤醒的 并且 不是时钟界面
  if (RTC_ac_wp > 0 && RTC_disPage_old != page_clock)
  {
    // 5秒内视为有闹钟
    if (abs(AC_timeTarget) <= 5)
    {
      AC_timeTarget = AC_WAKE_UP; // 标记唤醒时有闹钟
    }
    else esp_sleep(0);
  }

  // 开机长按确认键10秒进入按键校准界面
  int16_t count = 0;
  while (analogRead(KEY_ADC_PIN) <= 100)
  {
    delay(10);
    count++;
    if (count > 100)
    {
      eep_keyADCUp = 5000;
      eep_keyADCUp = 5000;
      break;
    }
  }

  bool anim = 1; // 是否启用动画
  //Serial.printf("eep_keyADCUp:%d\n",eep_keyADCUp);
  //Serial.printf("eep_keyADCDown:%d\n",eep_keyADCDown);
  if (eep_keyADCUp >= 5000 || eep_keyADCDown >= 5000)
  {
    display_keyADC_cali_init();
    buzzer_active();
  }
  else if (eep_disPage == page_clock)
  {
    // 检查闹钟 5秒内视为有闹钟
    if (abs(AC_timeTarget) <= 5)
    {
      RTC_timedWakeUp = 0;
      AC_timeTarget = AC_WAKE_UP; // 标记唤醒时有闹钟
    }

    display_clock_init();

    // 是定时唤醒的标记不需要动画
    if (RTC_timedWakeUp == 1)  
    {
      anim = 0;
      //添加屏幕保护刷屏 单位分钟
      RTC_clock_count++;
      if (RTC_clock_count > 120)
      {
        RTC_clock_count = 0;
        display_screenSaver_init();
        lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_OVER_LEFT, 100, 0, true);
        return;
      }
    }
    // 不是定时唤醒 打开定时读取时间
    else bitWrite(backgroundTask, BGT_CLOCK_READ, 1);
  }
  else if (eep_disPage == page_acc)
  {
    display_acc_init();
    bitWrite(backgroundTask, BGT_ACC_READ, 1); // 标记打开任务
  }
  else if (eep_disPage == page_mainSet)
  {
    display_mainSet_init();
  }
  else if (eep_disPage == page_air)
  {
    display_air_init();
    bitWrite(backgroundTask, BGT_AIR_READ, 1); // 标记打开任务
  }
  else if (eep_disPage == page_alarmClock)
  {
    display_alarmClock_init();
  }
  else if (eep_disPage == page_fileExplorer)
  {
    fileManagerInit(1);
    display_fileExplorer_init();
  }
  else if (eep_disPage == page_memoSet)
  {
    display_memoSet_init();
  }
  else if (eep_disPage == page_memo)
  {
    display_memo_init();
  }
  else//防止错误
  {
    display_jitterSet_init();
  }

  //Serial.printf("eep_disPage:%d\n", eep_disPage);
  if (anim) //需要动画
  {
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, 1000, 0, false);
    onGlobalJitter(1000); // 打开全局抖动
  }
  else // 不需要动画
  {
    lv_screen_load(page.p[page.index]);
  }
}

//********** 在事件内添加动画，动画不会重叠 返回1动画播放中 返回0动画启动
bool addAnimation_event(lv_obj_t *obj1, void (*animFunctions)(lv_obj_t *obj2), lv_anim_exec_xcb_t exec_cb)
{
  lv_anim_t *a = lv_anim_get(obj1, exec_cb); //button_width_shrink_anim_cb
  if (a != NULL) return 1; // 如果动画正在播放，直接返回
  animFunctions(obj1);     // 调用动画函数
  return 0;
}

//****** 自写弹窗 带动画
/*
lv_anim_path_linear 线性动画
lv_anim_path_step 最后一步改变
lv_anim_path_ease_in 开始时很慢
lv_anim_path_ease_out 最后慢
lv_anim_path_ease_in_out 开始和结束都很慢
lv_anim_path_overshoot 超过结束值
lv_anim_path_bounce 从最终值反弹一点（比如撞墙）
*/
// 弹窗动画 对X轴变化
void my_msgbox_anim_x_cb(void *var, int32_t v) 
{
  //lv_obj_set_x((lv_obj_t *)var, v);
  lv_obj_align((lv_obj_t *)var, LV_ALIGN_LEFT_MID, v, 0);
  //Serial.printf("v:%d\n",v);
}
// 弹窗退出动画结束时删除自己
void my_msgbox_exit_anim_end_cd(lv_anim_t *a) 
{
  // lv_obj_delete((lv_obj_t *)a->var);
  lv_obj_delete(mbox.p); // 删除对象
  mbox.p = NULL;         // 对象地址清空
  mbox.keyMode = KEY_MODE_RL;

  if (group_old != NULL)
  {
    lv_indev_set_group(indev, group_old); // 将组邦定到按键 group_my
    lv_obj_t *obj = lv_group_get_focused(group_old);
    group_old = NULL;
    if (obj != NULL)
      lv_obj_set_state(obj, LV_STATE_PRESSED, false); // 设置状态
  }

  // 检查清空标志
  /*if (bitRead(mbox.state, MBOX_STATE_CLEAR) == 1)
  {
    mbox.title.clear();
    mbox.text.clear();
    mbox.time = 0;
    mbox.recordTime = 0;
    mbox.button.clear();
    mbox.event_cb = NULL;
    bitWrite(mbox.state, MBOX_STATE_CLEAR, 0);
  }*/

  // 定时器存在，删除定时器
  if (lvTimer_msgbox)
  {
    lv_timer_delete(lvTimer_msgbox);
    lvTimer_msgbox = NULL;
  }

  bitWrite(mbox.state, MBOX_STATE_EXIT, 0);   // 标记退出完毕
  bitWrite(mbox.state, MBOX_STATE_REMAIN, 0); // 标记停留阶段结束
  bitWrite(mbox.state, MBOX_STATE_TIMER, 0);  // 取消标记定时器运行阶段
  bitWrite(mbox.state, MBOX_STATE_ENTER, 0);  // 标记进入阶段结束
  /*Serial.println("弹窗退出完毕");
  Serial.print("mbox.state:");
  Serial.println(mbox.state, BIN);
  Serial.println();*/
}
// 弹窗退出 设置多少秒后退出的定时器回调
void my_msgbox_setExit_timer_cb(lv_timer_t *e)
{
  bitWrite(mbox.state, MBOX_STATE_EXIT, 1); // 标记退出中
  int16_t x = lv_obj_get_x(mbox.p);
  lv_anim_t b;
  lv_anim_init(&b);                                         // 动画初始化
  lv_anim_set_var(&b, mbox.p);                              // 设置需要动画的对象
  lv_anim_set_values(&b, x, -78);                           // 设置动画的开始值和结束值
  lv_anim_set_duration(&b, MSGBOX_ANIM_TIME);               // 设置动画的持续时间
  lv_anim_set_exec_cb(&b, my_msgbox_anim_x_cb);             // 设置需要变化的值
  lv_anim_set_path_cb(&b, lv_anim_path_ease_in);            // 设置变化特效
  lv_anim_set_completed_cb(&b, my_msgbox_exit_anim_end_cd); // 设置动画完成时的函数调用
  lv_anim_start(&b);                                        // 动画开始
  //Serial.println("弹窗退出动画开始");
}
// 弹窗退出 供用户调用
void my_msgbox_exit(uint32_t delay_ms)
{
  if (mbox.p == NULL)
  {
    //Serial.println("无弹窗返回");
    return;
  }
  if (bitRead(mbox.state, MBOX_STATE_EXIT))
  {
    //Serial.println("弹窗退出中返回");
    return;
  }

  //Serial.println("弹窗退出开始创建");

  if (lvTimer_msgbox)
  {
    lv_timer_pause(lvTimer_msgbox);  // 暂停
    lv_timer_delete(lvTimer_msgbox); // 删除
    lvTimer_msgbox = NULL;
  }

  if (delay_ms < 5) // 小于5ms直接运行
  {
    my_msgbox_setExit_timer_cb(NULL);
    return;
  } 

  bitWrite(mbox.state, MBOX_STATE_TIMER, 1); // 标记定时器运行阶段
  // 创建一个单次定时器
  lvTimer_msgbox = lv_timer_create(my_msgbox_setExit_timer_cb, delay_ms, NULL);
  lv_timer_set_repeat_count(lvTimer_msgbox, 1);
  lv_timer_set_auto_delete(lvTimer_msgbox, false);
}
// 弹窗进入动画结束回调
void my_msgbox_enter_anim_end_cd(lv_anim_t *a)
{
  //Serial.println("弹窗进入动画结束");
  bitWrite(mbox.state, MBOX_STATE_ENTER, 0);  // 标记进入阶段结束
  bitWrite(mbox.state, MBOX_STATE_REMAIN, 1); // 标记进入停留阶段
}
// 强制发送弹窗 供用户调用
void my_msgbox_forceSend(String title_in, String text_in, uint16_t time, String button, lv_event_cb_t event_cb)
{
  bitWrite(mbox.state, MBOX_STATE_FORCE, 1); // 标记强制发送
  my_msgbox_send(title_in, text_in, time, button, event_cb);
}
// 正常发送弹窗 供用户调用
void my_msgbox_send(String title_in, String text_in, uint16_t time, String button, lv_event_cb_t event_cb)
{
  //Serial.println("弹窗发送");
  //Serial.printf("title_in:%s\n", title_in.c_str());
  //Serial.printf("text_in:%s\n", text_in.c_str());
  //Serial.printf("time:%d\n", time);
  bitWrite(mbox.state, MBOX_STATE_SEND, 1); // 标记发送阶段
  if(title_in) mbox.title = title_in;
  if(text_in)  mbox.text = text_in;
  mbox.time = time;
  if(button)   mbox.button = button;
  if(event_cb) mbox.event_cb = event_cb;
}
// 弹窗进入，供my_msgbox_loop调用，用户勿调用
void my_msgbox(String title_in, String text_in, uint16_t time, String button, lv_event_cb_t event_cb) 
{
  //uint8_t index = msgboxInit();
  bitWrite(mbox.state, MBOX_STATE_ENTER, 1); // 标记进入阶段
  bitWrite(mbox.state, MBOX_STATE_SEND, 0); // 标记发送结束

  // 进入前先清空
  mbox.title.clear();
  mbox.text.clear();
  mbox.time = 0;
  mbox.button.clear();
  mbox.event_cb = NULL;

  const char *title = title_in.c_str();
  const char *text = text_in.c_str();
  // 计算按钮的数量
  uint8_t butNum = 0;
  String button_name[3];
  for (uint8_t i = 0; i < button.length(); i++)
  {
    if (button[i] != '\n') button_name[butNum] += button[i];
    else                   butNum++;
    if (butNum >= 3) break;
  }

  // 大框
  mbox.p = lv_obj_create(lv_layer_top());
  lv_obj_set_scrollbar_mode(mbox.p, LV_SCROLLBAR_MODE_OFF); //关闭滑动条
  //uint16_t width_title = lv_text_get_width(title, strlen(title), lv_obj_get_style_text_font(mbox.p, 0), 0);
  //uint16_t width_text = lv_text_get_width(text, strlen(text), lv_obj_get_style_text_font(mbox.p, 0), 0);
  //uint16_t width_title_zl = (width_title / 69);
  //uint16_t width_text_zl = (width_text / 69);
  //Serial.printf("width_text:%d\n", width_text);
  //Serial.printf("width_text_zl:%d\n", width_text_zl);
  //lv_obj_set_size(mbox.p, 78, 48 + ((width_title_zl + width_text_zl) * 20));
  lv_obj_set_size(mbox.p, 78, 144);
  lv_obj_align(mbox.p, LV_ALIGN_LEFT_MID, -78, 0);
  lv_obj_set_style_text_color(mbox.p, MY_COLOR_BLACK, LV_STATE_DEFAULT);   // 字体颜色
  lv_obj_set_style_border_color(mbox.p, MY_COLOR_BLACK, LV_STATE_DEFAULT); // 边框颜色
  lv_obj_set_style_border_width(mbox.p, 2, LV_STATE_DEFAULT);              // 边框宽度
  lv_obj_set_style_pad_all(mbox.p, 0, LV_STATE_DEFAULT);                   // 边距
  lv_obj_set_style_radius(mbox.p, 9, LV_STATE_DEFAULT);                    // 设置圆角
  lv_obj_set_style_bg_opa(mbox.p, LV_OPA_100, LV_STATE_DEFAULT);

  lv_obj_update_layout(mbox.p); // 更新布局
  uint16_t i_w = lv_obj_get_width(mbox.p);
  uint16_t i_h = lv_obj_get_height(mbox.p);
  uint16_t i_r = lv_obj_get_style_radius(mbox.p, LV_STATE_DEFAULT);

  // 内边框
  lv_obj_t *innerBorder = lv_obj_create(mbox.p);
  lv_obj_set_style_bg_opa(innerBorder, LV_OPA_0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(innerBorder, MY_COLOR_CYAN, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(innerBorder, 2, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(innerBorder, i_r - 2, LV_STATE_DEFAULT);
  lv_obj_set_size(innerBorder, i_w - 4, i_h - 4);
  lv_obj_align(innerBorder, LV_ALIGN_CENTER, 0, 0);

  // 标题
  lv_obj_t *box_title = lv_label_create(mbox.p);
  // lv_obj_set_style_border_width(box_title, 0, LV_STATE_DEFAULT); // 边框宽度
  // lv_obj_set_style_pad_all(box_title, 0, LV_STATE_DEFAULT);      // 边距
  lv_obj_set_width(box_title, 66);                                                // 设置宽度
  lv_obj_align(box_title, LV_ALIGN_TOP_MID, 1, 2);                                // 设置对齐方式
  lv_obj_set_style_text_color(box_title, MY_COLOR_WHITE, LV_STATE_DEFAULT);       // 设置文本颜色
  lv_label_set_long_mode(box_title, LV_LABEL_LONG_WRAP);                          // 设置文本长字符模式
  lv_obj_set_style_text_align(box_title, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 设置文本对齐方式
  lv_label_set_text(box_title, title);                                            // 打印文本
  
  // 标题的背景
  lv_obj_t *title_bg = lv_obj_create(mbox.p);
  lv_obj_set_style_border_width(title_bg, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(title_bg, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(title_bg, 0, LV_STATE_DEFAULT); // 边距
  lv_obj_set_style_radius(title_bg, 0, LV_STATE_DEFAULT);  // 设置圆角
  lv_obj_update_layout(mbox.p);// 更新布局
  lv_obj_set_size(title_bg, i_w - 8, lv_obj_get_height(box_title));
  lv_obj_align(title_bg, LV_ALIGN_TOP_MID, 0, 2);
  lv_obj_swap(title_bg, box_title); // 交换层级

  // 内容
  lv_obj_t *box_text = lv_label_create(mbox.p);
  lv_obj_set_width(box_text, 66);                                                // 设置宽度
  lv_obj_align_to(box_text, box_title, LV_ALIGN_OUT_BOTTOM_MID, 0, 1);           // 设置对齐方式
  lv_label_set_long_mode(box_text, LV_LABEL_LONG_WRAP);                          // 设置文本长字符模式
  lv_obj_set_style_text_align(box_text, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT); // 设置文本对齐方式
  lv_label_set_text(box_text, text);                                             // 打印文本

  // 更新大框的尺寸
  uint8_t additional = 14; //额外高度
  if (butNum == 0) additional = 8; //没有按钮时只需要8
  lv_obj_update_layout(mbox.p); // 更新布局
  i_h = lv_obj_get_height(box_title) + lv_obj_get_height(box_text) + additional + (butNum * 23);
  lv_obj_set_size(mbox.p, 78, i_h);
  lv_obj_align(mbox.p, LV_ALIGN_LEFT_MID, -7, 0);
  // 更新内框的尺寸
  lv_obj_set_size(innerBorder, i_w - 4, i_h - 4);
  lv_obj_align(innerBorder, LV_ALIGN_CENTER, 0, 0);
  lv_obj_move_to_index(innerBorder, lv_obj_get_index(mbox.p) - 2); // 移动到顶层-1

  // Serial.printf("box_title_higth:%d\n", lv_obj_get_height(box_title));
  // Serial.printf("box_text_higth:%d\n", lv_obj_get_height(box_text));
  // Serial.printf("i_h:%d\n", i_h);

  // 按钮存在
  if (butNum != 0)
  {
    // 记录现在的组，以便在退出时恢复
    group_old = lv_indev_get_group(indev);
    // 启用弹窗组
    lv_indev_set_group(indev, group_mbox0);
    // 使能 lv_layer_top 点击
    // lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_add_flag(lv_layer_top(), LV_OBJ_FLAG_SCROLL_WITH_ARROW);
    mbox.keyMode = KEY_MODE_PN; // 切换至焦点模式

    // 设置文本的背景
    lv_obj_t *text_bg = lv_obj_create(mbox.p);
    lv_obj_set_style_bg_color(text_bg, MY_COLOR_YELLOW, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(text_bg, 0, LV_STATE_DEFAULT); // 边框宽度
    lv_obj_set_style_pad_all(text_bg, 0, LV_STATE_DEFAULT);      // 边距
    lv_obj_set_style_radius(text_bg, 0, LV_STATE_DEFAULT);       // 设置圆角
    lv_obj_update_layout(mbox.p); // 更新布局
    lv_obj_set_size(text_bg, i_w - 8, lv_obj_get_height(box_text));
    lv_obj_align_to(text_bg, title_bg, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_swap(text_bg, box_text); //交换层级

    // 绘制按钮
    lv_obj_t *but[butNum];
    lv_obj_t *label[butNum];
    lv_color_t color[3] = {MY_COLOR_RED, MY_COLOR_GREEN, MY_COLOR_CYAN};
    for (uint8_t i = 0; i < butNum; i++)
    {
      // 创建按钮
      but[i] = lv_button_create(mbox.p);
      lv_obj_set_size(but[i], 65, 19);
      if (i == 0)
        lv_obj_align_to(but[i], box_text, LV_ALIGN_OUT_BOTTOM_MID, -4, 5);
      else
        lv_obj_align_to(but[i], but[i - 1], LV_ALIGN_OUT_BOTTOM_MID, 0, 4);
      lv_obj_set_style_radius(but[i], 4, LV_STATE_DEFAULT);                       // 设置圆角
      lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 添加不透明度样式
      lv_obj_set_style_bg_color(but[i], color[i], LV_STATE_DEFAULT);              // 设置背景颜色
      lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
      lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
      lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
      lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
      lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色

      // 创建标签
      label[i] = lv_label_create(but[i]);
      lv_obj_align(label[i], LV_ALIGN_CENTER, 0, 1);            // 设置对齐方式
      if (i == 0)
        lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, 0); // 设置字体颜色
      else
        lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, 0); // 设置字体颜色
      lv_label_set_text(label[i], button_name[i].c_str());         // 打印文本

      // 将按键邦定到组
      lv_group_add_obj(group_mbox0, but[i]);
      // 添加按钮聚焦动画
      lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
      // 添加按钮按下回调
      lv_obj_add_event_cb(but[i], event_cb, LV_EVENT_PRESSED, &num[i]);
    }

    // 创建线条
    static lv_point_precise_t line_points[] = {{0, 0}, {69, 0}};
    lv_obj_t * line1;
    line1 = lv_line_create(mbox.p);
    lv_line_set_points(line1, line_points, 2); 
    lv_obj_set_style_line_width(line1, 2, 0);
    lv_obj_set_style_line_color(line1,MY_COLOR_CYAN,0);
    //lv_obj_set_style_outline_opa(line1, LV_OPA_0, 0);
    //lv_obj_add_style(line1, &style_shadow, LV_STATE_DEFAULT); // 添加不透明度样式
    //lv_obj_set_style_line_rounded(line1, true, 0);
    lv_obj_align_to(line1, text_bg, LV_ALIGN_OUT_BOTTOM_MID, 0, 1);
    //lv_obj_center(line1);
  }

  // lv_obj_set_style_border_color(box_title, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  // lv_obj_set_style_border_width(box_title, 1, LV_STATE_DEFAULT);
  // lv_obj_set_style_bg_color(box_title, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  // lv_obj_set_style_bg_color(box_content, lv_color_make(255, 255, 0), LV_STATE_DEFAULT);
  // lv_obj_set_style_bg_opa(box_title, LV_OPA_100, LV_STATE_DEFAULT);
  // lv_obj_set_style_bg_opa(box_content, LV_OPA_100, LV_STATE_DEFAULT);

  // 给弹窗添加进入动画
  //Serial.println("弹窗创建");
  //Serial.printf("title_in:%s\n",title_in.c_str());
  //Serial.printf("text_in:%s\n",text_in.c_str());
  //Serial.printf("time:%d\n",time);
  //int16_t x = lv_obj_get_x(mbox.p);
  //Serial.printf("x:%d\n",x);

  lv_anim_t a;
  lv_anim_init(&a);                                          // 动画初始化
  lv_anim_set_var(&a, mbox.p);                               // 设置需要动画的对象
  lv_anim_set_values(&a, -78, -7);                           // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);                // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, my_msgbox_anim_x_cb);              // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_bounce);              // 设置变化特效
  lv_anim_set_completed_cb(&a, my_msgbox_enter_anim_end_cd); // 设置动画完成时的函数调用
  lv_anim_start(&a);     // 动画开始
                                      
  if (time > 0) //一段时间后退出
  {
    //lv_obj_delete_delayed(mbox.p, time);
    my_msgbox_exit(MSGBOX_ANIM_TIME + time);
  }
}
// 弹窗监测 放到loop任务中使用，用户勿调用
void my_msgbox_loop()
{
  if(mbox.state == 0)  return; 

  // 强制发送时
  if (bitRead(mbox.state, MBOX_STATE_FORCE) == 1) 
  {
    // Serial.println("强制发送");
    mbox.state = 0;     // 状态清零重新开始
    if (mbox.p != NULL) // 删除现在的弹窗
    {
      lv_obj_delete(mbox.p); // 删除对象
      mbox.p = NULL;         // 对象地址清空
      // 定时器存在，删除定时器
      if (lvTimer_msgbox)
      {
        lv_timer_delete(lvTimer_msgbox);
        lvTimer_msgbox = NULL;
      }
    }
    bitWrite(mbox.state, MBOX_STATE_SEND, 1); // 标记发送阶段
    my_msgbox(mbox.title, mbox.text, mbox.time, mbox.button, mbox.event_cb);
    return;
  }

  if(bitRead(mbox.state, MBOX_STATE_ENTER) == 1) return;  // 进入阶段 返回
  if(bitRead(mbox.state, MBOX_STATE_EXIT) == 1)  return;  // 退出阶段 返回
  //if(bitRead(mbox.state, MBOX_STATE_TIMER) == 1)  return; // 定时阶段 返回

  // 有新的弹窗进入，挤掉现在的弹窗
  if (mbox.p != NULL && bitRead(mbox.state, MBOX_STATE_SEND) == 1)
  {
    //Serial.println("新的弹窗挤入1");
    if (millis() - mbox.recordTime < 800) return; // 最少运行800毫秒
    //Serial.println("新的弹窗挤入2");
    //bitWrite(mbox.state, MBOX_STATE_CLEAR, 0); // 标记不清空
    my_msgbox_exit(0);                         // 退出当前弹窗
    return;
  }

  if(bitRead(mbox.state, MBOX_STATE_REMAIN) == 1) return;

  //bitWrite(mbox.state, MBOX_STATE_CLEAR, 1); // 标记下次退出需要清空内容和标志位
  mbox.recordTime = millis();                // 记录整体运行时间，包括动画运行时间
  my_msgbox(mbox.title, mbox.text, mbox.time, mbox.button, mbox.event_cb);
}

//关闭LVGL的定时器和rtos任务
void offLVGLTimer()
{
  if (lvTimer_share[0] != NULL)
  {
    lv_timer_delete(lvTimer_share[0]);
    lvTimer_share[0] = NULL;
    //Serial.println("关闭LVGL的定时器");
    //*** 码表和定位信息界面
    if (eep_disPage == page_stopwatch || eep_disPage == page_locateInfo)
      bitWrite(backgroundTask, BGT_LOCATE_INFO_READ, 0); // 关闭卫星读取任务
    //*** 前置光设置界面
    else if (eep_disPage == page_frontLightSet)
      bitWrite(backgroundTask, BGT_AMBIENT_LIGHT, 0); // 关闭环境光读取任务
  }
}
// 通用 退出至设置菜单
void exitToMainSet()
{
  display_mainSet_init();

  //Serial.print("get_focusPos_old[" + String(focusPos_old_index) + "]:");
  //Serial.println(focusPos_old[focusPos_old_index]);

  // 决定怎么滚动对齐
  if (focusPos_old[focusPos_old_index] >= 2) 
    lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_CENTER); // 对齐中心
  else
    lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_NONE); // 不要对齐，留在原地

  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, GRADUAL_ANIM_TIME, 100, true);
  onGlobalJitter();     // 打开全局抖动
  focusPosOld_return(); // 回到刚才的焦点
}
// 通用 弹窗的退出返回，返回则返回至主设置页面
void backPage_mainSet(lv_event_t *e) 
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出
  {
    offLVGLTimer();     // 关闭LVGL定时器
    my_msgbox_exit(10); // 退出弹窗
    exitToMainSet();    // 退出至设置菜单
  }
  else if (data[0] == 1) // 返回
  {
   my_msgbox_exit(10); // 退出弹窗
  }
}
// 通用 退出至设置菜单的回调
void backPage_mainSet_event(lv_event_t *e)
{
  offLVGLTimer();  // 关闭LVGL定时器
  exitToMainSet(); // 退出至设置菜单
}
void msgbox_exit_cb(lv_event_t *e) // 通用 弹窗退出回调
{
  buzzerSen(30);
  my_msgbox_exit(5); // 退出弹窗
}
//key-按键模式： 0左右切换 1焦点切换
//first： 是否有在回调里只执行一次的命令
uint8_t pageInit(bool key, bool first)
{
  page.keyMode = key;
  page.firstEvent = first;
  page.index++;
  if(page.index > 1) page.index = 0;
  return page.index;
}

//****** 动画相关
void button_width_shrink_anim_init(lv_obj_t *obj) // 按键横向向内收缩初始化
{
  buzzerSen(30);
  uint8_t w = lv_obj_get_width(obj);
  // Serial.printf("w:%d\n", w);
  lv_anim_t a;
  lv_anim_init(&a);                                              // 动画初始化
  lv_anim_set_var(&a, obj);                                      // 设置需要动画的对象
  lv_anim_set_values(&a, w, w - 10);                             // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, BUTTON_ANIM_TIME);                    // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, button_width_shrink_anim_cb);          // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_bounce);                  // 设置变化特效
  lv_anim_set_completed_cb(&a, button_width_shrink_anim_end_cb); // 设置动画完成时的函数调用
  // lv_anim_set_user_data(&a, user_data);                          // 添加当前的用户数据
  lv_anim_start(&a);
}
void button_width_shrink_anim_cb(void *var, int32_t v) // 按钮横向收缩变化
{
  lv_obj_set_width((lv_obj_t *)var, v);
}
void markAnimIdle(lv_anim_t *a) // 标记按钮动画空闲
{
  bool *state = (bool *)lv_anim_get_user_data(a);
  if (state != NULL)
  {
    //Serial.printf("state2:%p\n", state);   // 输出地址
    //Serial.printf("*state2:%d\n", *state); // 输出值
    //Serial.print("animState[" + String(animStateIndex) + "]2:");
    //Serial.println(animState[animStateIndex]);
    *state = 0;
  }
}
void button_width_shrink_anim_end_cb(lv_anim_t *a) // 按钮横向收缩动画结束回调
{
  uint8_t w = lv_obj_get_width((lv_obj_t *)a->var);
  // Serial.printf("h2:%d\n",h);
  lv_anim_t b;
  lv_anim_init(&b);                                     // 动画初始化
  lv_anim_set_var(&b, a->var);                          // 设置需要动画的对象
  lv_anim_set_values(&b, w, w + 10);                    // 设置动画的开始值和结束值
  lv_anim_set_duration(&b, BUTTON_ANIM_TIME);           // 设置动画的持续时间
  lv_anim_set_exec_cb(&b, button_width_shrink_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&b, lv_anim_path_bounce);         // 设置变化特效
  //lv_anim_set_completed_cb(&b, markAnimIdle); // 设置动画完成时的函数调用
  //lv_anim_set_user_data(&b, lv_anim_get_user_data(a));
  lv_anim_start(&b);
}
void button_height_expand_anim_cb(void *var, int32_t v) // 按钮高度扩展变化
{
  lv_obj_set_height((lv_obj_t *)var, v);
  lv_obj_scroll_to_view((lv_obj_t *)var, LV_ANIM_ON);
}
void buttonFocus_anim_event(lv_event_t *e) // 按钮聚焦播放外框缩放动画
{
  //Serial.println("按钮聚焦");
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init, button_width_shrink_anim_cb); // 添加动画不重叠
  if (run == 1) return;
  //button_width_shrink_anim_init(obj);
  LV_UNUSED(obj);
}

void button_editNumEject_anim_cb(void *var, int32_t v) // 标签从下弹出动画变化
{
  lv_obj_align((lv_obj_t *)var, LV_ALIGN_BOTTOM_MID, 0, v); // 对齐方式
}

void label_y_bounce_anim_cb(void *var, int32_t v)         // Y轴弹跳动画变化回调
{
  lv_obj_set_y((lv_obj_t *)var, v);
  //Serial.printf("y1:%d\n", v);
}
void label_y_bounce_anim_init(lv_obj_t *obj, int16_t val) // Y轴弹跳动画
{
  int16_t y = lv_obj_get_y(obj);
  //Serial.printf("y0:%d\n", y);
  lv_anim_t a;
  lv_anim_init(&a);                                // 动画初始化
  lv_anim_set_var(&a, obj);                        // 设置需要动画的对象
  lv_anim_set_values(&a, y + val, y);              // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, BUTTON_ANIM_TIME);      // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, label_y_bounce_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);  // 设置变化特效
  // lv_anim_set_completed_cb(&a, label_y_up_anim_end_cb); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void label_x_bounce_anim_cb(void *var, int32_t v)         // X轴弹跳动画变化回调
{
  lv_obj_set_x((lv_obj_t *)var, v);
  //Serial.printf("x1:%d\n", v);
}
void label_x_bounce_anim_init(lv_obj_t *obj, int16_t val) // X轴弹跳动画
{
  int16_t x = lv_obj_get_x(obj);
  //Serial.printf("x0:%d\n", x);
  //Serial.printf("val:%d\n", val);
  lv_anim_t a;
  lv_anim_init(&a);                                // 动画初始化
  lv_anim_set_var(&a, obj);                        // 设置需要动画的对象
  lv_anim_set_values(&a, x + val, x);              // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, BUTTON_ANIM_TIME);      // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, label_x_bounce_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);  // 设置变化特效
  // lv_anim_set_completed_cb(&a, label_y_up_anim_end_cb); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void buttonFocus_anim_event1(lv_event_t *e)  // 按钮聚焦播放文字随机跳动动画 lv_obj_get_x/y
{
  //Serial.println("按钮聚焦1");
  lv_obj_t *obj = lv_event_get_target_obj(e);  // 按钮对象
  lv_obj_t *child0 = lv_obj_get_child(obj, 0); // 第0个子代，按钮的即文本标签

  lv_anim_t *a = lv_anim_get(child0, label_y_bounce_anim_cb);
  if (a != NULL) return; // 如果动画正在播放，直接返回
  //Serial.printf("y:%d\n",lv_obj_get_y(child0));
  label_y_bounce_anim_init(child0, random(-5, 5));

  lv_anim_t *b = lv_anim_get(child0, label_x_bounce_anim_cb);
  if (b != NULL) return; // 如果动画正在播放，直接返回
  //Serial.printf("x:%d\n",lv_obj_get_x(child0));
  label_x_bounce_anim_init(child0, random(-10, 10));
}

void label_y_bounce_anim_cb1(void *var, int32_t v)         // Y轴弹跳动画变化回调
{
  //lv_align_t s = lv_obj_get_style_align((lv_obj_t *)var, 0);
  //lv_obj_align((lv_obj_t *)var, s, 0, v);
  lv_obj_set_y((lv_obj_t *)var, v);
  //Serial.printf("y1:%d\n", v);
}
void label_y_bounce_anim_init1(lv_obj_t *obj, int16_t val) // Y轴弹跳动画
{
  int16_t y = lv_obj_get_y_aligned(obj);
  //Serial.printf("y0:%d\n", y);
  lv_anim_t a;
  lv_anim_init(&a);                                // 动画初始化
  lv_anim_set_var(&a, obj);                        // 设置需要动画的对象
  lv_anim_set_values(&a, y + val, y);              // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, LABEL_ANIM_TIME);      // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, label_y_bounce_anim_cb1); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);  // 设置变化特效
  // lv_anim_set_completed_cb(&a, label_y_up_anim_end_cb); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void label_x_bounce_anim_cb1(void *var, int32_t v)         // X轴弹跳动画变化回调
{
  //lv_align_t s = lv_obj_get_style_align((lv_obj_t *)var, 0);
  //lv_obj_set_align((lv_obj_t *)var, s);
  lv_obj_set_x((lv_obj_t *)var, v);
  //lv_obj_align((lv_obj_t *)var, s, v, 0);
  //Serial.printf("x1:%d\n", v);
}
void label_x_bounce_anim_init1(lv_obj_t *obj, int16_t val) // X轴弹跳动画
{
  int16_t x = lv_obj_get_x_aligned(obj);

  //Serial.printf("x0:%d\n", x); lv_obj_get_x
  //Serial.printf("val:%d\n", val);
  lv_anim_t a;
  lv_anim_init(&a);                                // 动画初始化
  lv_anim_set_var(&a, obj);                        // 设置需要动画的对象
  lv_anim_set_values(&a, x + val, x);              // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, LABEL_ANIM_TIME);      // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, label_x_bounce_anim_cb1); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);  // 设置变化特效
  // lv_anim_set_completed_cb(&a, label_y_up_anim_end_cb); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void buttonFocus_anim_event2(lv_event_t *e)  // 按钮聚焦播放文字随机跳动动画 lv_obj_get_x_aligned
{
  //Serial.println("按钮聚焦2");
  lv_obj_t *obj = lv_event_get_target_obj(e);  // 按钮对象
  lv_obj_t *child0 = lv_obj_get_child(obj, 0); // 第0个子代，按钮的即文本标签

  lv_anim_t *a = lv_anim_get(child0, label_y_bounce_anim_cb1);
  if (a != NULL) return; // 如果动画正在播放，直接返回
  //Serial.printf("y:%d\n",lv_obj_get_y(child0));
  label_y_bounce_anim_init1(child0, random(-5, 5));

  lv_anim_t *b = lv_anim_get(child0, label_x_bounce_anim_cb1);
  if (b != NULL) return; // 如果动画正在播放，直接返回
  //Serial.printf("x:%d\n",lv_obj_get_x(child0));
  label_x_bounce_anim_init1(child0, random(-10, 10));
}

// 动画回调 关闭全局抖动
void offGlobalJitter_anim_cb(lv_anim_t *a)
{
  eep_doudong = 0;
}
// 事件回调 关闭全局抖动
void offGlobalJitter_event_cb(lv_event_t *e) 
{
  uint16_t *data = (uint16_t *)lv_event_get_user_data(e);
  uint16_t i = data[0];
  if (i > 0)
  {
    // 创建一个单次定时器
    lv_timer_t *timer = lv_timer_create(offGlobalJitter_timer_cb, 200, NULL);
    lv_timer_set_repeat_count(timer, 1);
    lv_timer_set_auto_delete(timer, true);
  }
  else eep_doudong = 0;
  //Serial.printf("eep_doudong:%d\n",eep_doudong);
}
// 定时器回调 关闭全局抖动
void offGlobalJitter_timer_cb(lv_timer_t *e) 
{
  eep_doudong = 0;
  //Serial.printf("eep_doudong:%d\n",eep_doudong);
}
// 定时开启全局抖动
void onGlobalJitter(uint16_t time)
{
  eep_doudong = 1; // 打开全局抖动
  // 一段时间后关闭全局抖动
  uint32_t time1 =0;
  if(time > 0) time1 = time;
  else         time1 = GRADUAL_ANIM_TIME - 100;
  // 创建一个单次定时器
  lv_timer_t *timer = lv_timer_create(offGlobalJitter_timer_cb, GRADUAL_ANIM_TIME - 100, NULL);
  lv_timer_set_repeat_count(timer, 1);
  lv_timer_set_auto_delete(timer, true);
}
// 获取上一个界面的焦点索引值并聚焦
void focusPosOld_return()
{
  //Serial.print("get_focusPos_old[" + String(focusPos_old_index) + "]:");
  //Serial.println(focusPos_old[focusPos_old_index]);
  if (focusPos_old_index <= -1) return;
  if (focusPos_old[focusPos_old_index] >= 0)
  {
    lv_obj_t *child = lv_obj_get_child(page.p[page.index], focusPos_old[focusPos_old_index]);
    lv_obj_set_state(child, LV_STATE_PRESSED, false); // 取消按下状态
    lv_group_focus_obj(child);                        // 聚焦
    LV_UNUSED(child);
  }
  focusPos_old_index--;
}
// 保存上一个界面的焦点索引值
void focusPosOld_save()
{
  focusPos_old_index++;
  lv_obj_t *focused_obj = lv_group_get_focused(group_my);
  if (focused_obj == NULL) focusPos_old[focusPos_old_index] = -1; // 如果没有聚焦对象，返回-1
  else                     focusPos_old[focusPos_old_index] = lv_obj_get_index(focused_obj);
  //Serial.printf("save_focusPos_old[%d]:%d\n", focusPos_old_index, focusPos_old[focusPos_old_index]);
}

//****** 全局抖动演示界面
void display_jitterSet_event(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target_obj(e);
  //Serial.print("code:");Serial.println(code);
  if (code == LV_EVENT_VALUE_CHANGED) //对象的值已更改（即滑块已移动）
  {
    bool state = lv_obj_has_state(obj, LV_STATE_CHECKED);
    eep_doudong = state;
    //LV_LOG_USER("State: %s\n", state ? "On" : "Off");
  }
  else if(code == LV_EVENT_DEFOCUSED)
  {
    //lv_group_remove_all_objs(group_my); // 从组中删除所有对象
    //Serial.print("全局抖动code:");Serial.println(code);
    uint8_t key = lv_indev_get_key(lv_indev_active());
    //Serial.print("全局抖动key:");Serial.println(key);
    if (key == LV_KEY_NEXT)
    {
      display_mainSet_init();
      lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_MOVE_TOP, PAGE_SWITCH_ANIM_TIME, 0, true);
    }
    else if (key == LV_KEY_PREV)
    {
      display_acc_init();
      lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_MOVE_BOTTOM, PAGE_SWITCH_ANIM_TIME, 0, true);
      bitWrite(backgroundTask, BGT_ACC_READ, 1); // 打开加速度读取任务
    }
  }
  LV_UNUSED(obj);
}
void display_jitterSet_init()
{
  eepSavePage(page_jitterSet);

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_size(page.p[index], TFT_HOR_RES, TFT_VER_RES);
  //lv_obj_align(page1, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF); //关闭滑动条

  //lv_obj_t *page1 = lv_screen_active();
  //page1 = lv_screen_active();
  //lv_obj_set_scrollbar_mode(page1, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  
  LV_IMG_DECLARE(qft);
  lv_obj_t *gif = lv_gif_create(page.p[index]);
  lv_gif_set_src(gif, &qft);
  lv_obj_align(gif, LV_ALIGN_BOTTOM_MID, 0, 0);

  // 基本对象
  lv_obj_t *obj1 = lv_obj_create(page.p[index]);
  lv_obj_align(obj1, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_size(obj1, 72, 30);
  lv_obj_set_style_bg_color(obj1, MY_COLOR_GREEN, LV_STATE_DEFAULT);
  lv_obj_set_scrollbar_mode(obj1, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  // 设置标签
  lv_obj_t *label = lv_label_create(obj1);
  lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_width(label, 72);
  lv_label_set_text(label, "Arduino LVGL9");
  //lv_obj_set_style_text_font(label, &MISans_1, 0);

  // lv_obj_set_flex_flow(lv_screen_active(), LV_FLEX_FLOW_COLUMN);
  //lv_obj_set_flex_align(lv_screen_active(), LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  
  //使用新样式创建标签
  lv_obj_t *label2 = lv_label_create(page.p[index]);
  //lv_obj_set_style_text_font(label2, &MISans_1, 0);
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SCROLL_CIRCULAR);
  lv_obj_set_style_anim_duration(label2, 3000, 0);
  lv_obj_set_width(label2, 43);
  lv_label_set_text(label2, String(F("抖动演示")).c_str());
  lv_obj_center(label2);
  lv_obj_align(label2, LV_ALIGN_LEFT_MID, 1, -20);

  // 创建开关
  lv_obj_t *sw = lv_switch_create(page.p[index]);
  lv_obj_align(sw, LV_ALIGN_RIGHT_MID, -4, -20);
  lv_obj_set_size(sw, 20, 11);
  lv_obj_set_style_bg_color(sw, lv_color_hex(0xff0000), LV_PART_MAIN); //开关 关闭的背景颜色
  lv_obj_set_style_bg_color(sw, lv_color_hex(0x00ffff), LV_PART_INDICATOR | LV_STATE_CHECKED); //开关 打开的背景颜色
  lv_obj_set_style_bg_color(sw, lv_color_hex(0xffffff), LV_PART_KNOB); //手柄颜色
  
  // 设置聚焦样式
  lv_obj_set_style_outline_width(sw, 2, LV_STATE_FOCUS_KEY);                      // 聚焦框的宽度
  lv_obj_set_style_outline_pad(sw, 1, LV_STATE_FOCUS_KEY);                        // 聚焦框的间隙
  lv_obj_set_style_outline_opa(sw, LV_OPA_100, LV_STATE_FOCUS_KEY);               // 聚焦框的不透明度
  lv_obj_set_style_outline_width(sw, 0, LV_PART_MAIN);                            // 失焦时的宽度
  lv_obj_set_style_outline_color(sw, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色

  lv_obj_add_event_cb(sw, display_jitterSet_event, LV_EVENT_VALUE_CHANGED, NULL); // 开关改变触发时的回调函数
  lv_obj_add_event_cb(sw, display_jitterSet_event, LV_EVENT_DEFOCUSED, NULL);     // 开关失焦触发时的回调函数
  lv_obj_add_flag(sw, LV_OBJ_FLAG_EVENT_BUBBLE);                                  // ?设置一个或多个标志
  if (eep_doudong) lv_obj_add_state(sw, LV_STATE_CHECKED); // 添加状态

  lv_group_add_obj(group_my, sw);    // 将对象邦定到组
  lv_group_add_obj(group_my, page.p[index]); // 将对象邦定到组
  
  // 设置初始焦点对象
  lv_group_focus_obj(sw);
}

//********** 图片界面
void display_picture_msgbox_cb(lv_event_t *e) 
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出
  {
    eep_doudong = 0;
   my_msgbox_exit(5); // 退出弹窗
    //Serial.printf("RTC_disPage_old:%d\n", RTC_disPage_old);
    if (RTC_disPage_old == page_fileExplorer)
    {
      // 回到上一个界面
      display_fileExplorer_init();
      lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, 500, 0, true);
      onGlobalJitter(400);  // 打开全局抖动
      //focusPosOld_return(); // 回到刚才的焦点
      lv_obj_t *child = lv_obj_get_child(page.p[page.index], focusPos_old[focusPos_old_index + 1]);
      lv_obj_set_state(child, LV_STATE_PRESSED, false); // 取消按下状态
      lv_group_focus_obj(child);                        // 聚焦
      LV_UNUSED(child);
      /*for (uint8_t i = 0; i < 10; i++)
      {
        Serial.printf("focusPos_old[%d]:%d\n", i, focusPos_old[i]);
      }
      Serial.printf("focusPos_old[%d]:%d\n", focusPos_old_index, focusPos_old[focusPos_old_index]);
      */
    }
  }
  else if (data[0] == 1) // 返回
  {
   my_msgbox_exit(0); // 退出弹窗
  }
}
void display_picture_event_msgbox(lv_event_t *e) // 当屏幕被聚焦时，弹出退出弹窗
{
  uint8_t key = lv_indev_get_key(lv_indev_active());
  // Serial.printf("key:%d", key);
  if (key == LV_KEY_RIGHT || key == LV_KEY_LEFT)
  {
    my_msgbox_send(F("图片"), F("查看器"), 0, F("退出\n返回\n"), display_picture_msgbox_cb);
  }
}
// 图片路径 抖动使能 退出菜单使能
void display_picture_init(String path, bool doudong = 1, bool menu = 0)
{
  eepSavePage(page_picture, 0);

  pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_style_pad_top(page.p[page.index], 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 0, LV_STATE_DEFAULT);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  path = "A:" + path;
  lv_obj_t *wp = lv_image_create(page.p[page.index]);
  lv_image_set_src(wp, path.c_str());
  lv_obj_center(wp);

  if (doudong) // 需要抖动
  {
    // uint16_t *delay1 = (uint16_t *)malloc(1 * sizeof(uint16_t));
    // lv_obj_add_event_cb(page.p[page.index], offGlobalJitter_event_cb, LV_EVENT_SCREEN_LOADED, &delay1);
    eep_doudong = doudong;
  }
  if (menu) // 需要返回菜单
  {
    lv_group_add_obj(group_my, page.p[page.index]);
    lv_obj_add_event_cb(page.p[page.index], display_picture_event_msgbox, LV_EVENT_KEY, NULL);
  }
}

//********** 屏幕保护界面
// 创建定时器
void display_screenSaver_timer_cb(lv_timer_t *e) 
{
  static uint8_t colorIndex = 0;
  lv_color_t color[8] = {MY_COLOR_WHITE, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED,
                         MY_COLOR_BLACK, MY_COLOR_CYAN};
  lv_obj_set_style_bg_color(page.p[page.index], color[colorIndex % 8], 0);
  colorIndex++;
  //if (colorIndex % 2) jdi_display.displayOff();
  //else jdi_display.displayOn();
  //Serial.printf("colorIndex:%d\n", colorIndex);
  if (colorIndex >= 16)
  {
    colorIndex = 0;
    display_clock_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
}
void display_screenSaver_init()
{
  pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(page.p[page.index], MY_COLOR_CYAN, 0);
  // 创建一个定时器
  lv_timer_t *timer = lv_timer_create(display_screenSaver_timer_cb, 100, NULL);
  lv_timer_set_repeat_count(timer, 16);
  lv_timer_set_auto_delete(timer, true);
}

//****** 设置菜单
void display_mainSet_event2(lv_event_t *e) // 自动设置滚动方式的事件
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target_obj(e);
  if (key_code == LV_KEY_PREV) // 上一个
  {
    // lv_obj_t *focused_obj = lv_group_get_focused(group_my);
    // int focusPos = lv_obj_get_index(focused_obj);
    // Serial.print("focusPos1:"); Serial.println(focusPos);
    lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_NONE); // 不要对齐，留在原地
    int top = lv_obj_get_scroll_top(page.p[page.index]);
    lv_obj_scroll_by(page.p[page.index], 0, top, LV_ANIM_ON);
  }
  else if (key_code == LV_KEY_NEXT) // 下一个
  {
    lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_CENTER);  // 对齐中心
  }

  // lv_obj_update_layout(page.p[page.index]);
  // int16_t scroll_y = lv_obj_get_scroll_y(page.p[page.index]);
  // Serial.printf("scroll_y:%d\n",scroll_y);
}
void mainSet_event3_anim_cb(void *var, int32_t v)
{
 lv_obj_align((lv_obj_t *)var, LV_ALIGN_CENTER, 0, v);
}
void display_mainSet_event3(lv_event_t *e) // 最后一个对象聚焦时弹出版本和作者
{
  if (lv_obj_has_flag(label_share[0], LV_OBJ_FLAG_HIDDEN))
  {
    lv_anim_t a;
    lv_anim_init(&a);                                // 动画初始化
    lv_anim_set_var(&a, label_share[1]);             // 设置需要动画的对象
    lv_anim_set_values(&a, 60, 0);                   // 设置动画的开始值和结束值
    lv_anim_set_duration(&a, 300);                   // 设置动画的持续时间
    lv_anim_set_delay(&a, 300);                      // 在开始动画之前设置延迟
    lv_anim_set_exec_cb(&a, mainSet_event3_anim_cb); // 设置需要变化的值
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out );    // 设置变化特效
    // lv_anim_set_completed_cb(&a, button_width_shrink_anim_end_cb); // 设置动画完成时的函数调用
    //  lv_anim_set_user_data(&a, user_data);                       // 添加当前的用户数据
    lv_anim_start(&a);
    lv_obj_remove_flag(label_share[0], LV_OBJ_FLAG_HIDDEN);
  }
}
void display_mainSet_EVENT_FOCUSED(lv_event_t *e) // page聚焦切换上一个界面
{
  Serial.println("page聚焦");
  uint8_t key = lv_indev_get_key(lv_indev_active());
  
  //****** page聚焦切换页面
  if (key == LV_KEY_PREV) //上一个焦点
  {
    display_jitterSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_MOVE_BOTTOM, PAGE_SWITCH_ANIM_TIME, 0, true);
  }
  if (page.firstEvent) // 首次进入该事件时 
  {
    //page.firstEvent = 0;

    // 手动定位到第一个焦点
    /*lv_obj_t *child = lv_obj_get_child(page.p[page.index], 0);
    lv_group_focus_obj(child);
    */
    // 设置滚动模式-不要对齐，留在原地
    //lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_NONE);
  }
}
void display_mainSet_EVENT_DEFOCUSED(lv_event_t *e) // page失焦 设置滚动对齐方式
{
  Serial.println("page失焦");
  uint8_t key = lv_indev_get_key(lv_indev_active());

  //****** page聚焦切换页面
  if (key == LV_KEY_PREV) // 上一个
  {
    lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_CENTER);
  }
  else if (key == LV_KEY_NEXT) // 下一个
  {
    lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_NONE);
  }
}
void display_mainSet_event_skip(lv_event_t *e) // 跳转事件1
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  Serial.printf("跳转事件:%d\n", i);
  uint8_t index = 0;
  if      (i == index++) // 跳转配网界面
  {
    bitWrite(backgroundTask, BGT_CONFIG_NETWORK, 1);
  }
  else if (i == index++) // 跳转休眠设置界面
  {
    focusPosOld_save(); // 保存上一个界面的焦点
    display_sleepSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // wifi选择界面
  {
    File file = LittleFS.open(wifiRecord, "r");
    if (!file)
    {
      my_msgbox_send(F("WIFI"), F("无记录"), 1000);
      return;
    }
    String str;
    for (uint16_t i = 0; i < file.size(); i++)
      str += char(file.read());
    file.close();
    focusPosOld_save(); // 保存上一个界面的焦点
    display_wifiSelect_init(str);
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 时钟设置界面
  {
    focusPosOld_save(); // 保存上一个界面的焦点
    display_clockSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 跳转文件管理器界面
  {
    focusPosOld_save(); // 保存上一个界面的焦点
    fileManagerInit(1); // 耗时30ms，应考虑放到后台任务执行
    display_fileExplorer_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 闹钟界面
  {
    focusPosOld_save();              // 保存上一个界面的焦点
    display_alarmClock_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 蜂鸣器
  {
    //alarmClockTimeDifference(0);
    //i2s_playSpecified("/op.mid");
    //delay(1000);
    
    /*note_t note[12] = {NOTE_C, NOTE_Cs, NOTE_D, NOTE_Eb, NOTE_E, NOTE_F, NOTE_Fs, NOTE_G, NOTE_Gs, NOTE_A, NOTE_Bb, NOTE_B};
    ledcWriteNote(BUZZER_CHANNEL, note[3], 4);
    delay(100);
    ledcWriteNote(BUZZER_CHANNEL, note[4], 4);
    delay(150);
    ledcWriteNote(BUZZER_CHANNEL, note[3], 6);
    delay(200);
    ledcWrite(BUZZER_CHANNEL, 0);*/
    focusPosOld_save(); //保存上一个界面的焦点
    display_buzzerSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 电量计
  {
    // 检查电量计是否存在
    if (i2cChipExist(BATSOC_I2C_ADDR) == 0)
    {
      my_msgbox_forceSend(F("电量计"), F("不存在"), 0, F("退出\n"), msgbox_exit_cb);
      return;
    }

    focusPosOld_save(); // 保存上一个界面的焦点
    display_batSOC_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 跳转空气质量界面
  {
    //display_screenSaver_init();
    //lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_OVER_LEFT, 100, 0, true);
    //my_msgbox_forceSend(F("空气模块"), F("未完成"), 0, F("退出\n"), msgbox_exit_cb);

    /*focusPosOld_save(); // 保存上一个界面的焦点
    display_keyADC_cali_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
    */

    /*bitWrite(backgroundTask, BGT_AIR_READ, 1);
    focusPosOld_save(); //保存上一个界面的焦点
    display_air_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
    */

    bitWrite(backgroundTask, BGT_AIR_READ, 1); // 打开串口任务
    bitWrite(backgroundTask, BGT_MQTT, 1);     // 打开MQTT任务
    focusPosOld_save(); // 保存上一个界面的焦点
    display_uartAir_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 位置信息
  {
    //my_msgbox_forceSend(F("北斗模块"), F("未插入"), 0, F("退出\n"), msgbox_exit_cb);
    //box2d_world_init();
    
    // 打开定位信息读取任务
    bitWrite(backgroundTask, BGT_LOCATE_INFO_READ, 1);
    focusPosOld_save(); // 保存上一个界面的焦点
    display_locateInfo_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 码表界面
  {
    //my_msgbox_forceSend(F("北斗模块"), F("未插入"), 0, F("退出\n"), msgbox_exit_cb);
    //box2d_world_init();
    
    // 打开定位信息读取任务
    bitWrite(backgroundTask, BGT_LOCATE_INFO_READ, 1);
    focusPosOld_save(); // 保存上一个界面的焦点
    display_stopwatch_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 备忘录设置界面
  {
    focusPosOld_save(); // 保存上一个界面的焦点
    display_memoSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == index++) // 前置光界面
  {
    focusPosOld_save(); // 保存上一个界面的焦点
    display_frontLightSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
    
    //打开环境光读取
    bitWrite(backgroundTask, BGT_AMBIENT_LIGHT, 1); 
  }
  else if (i == index++) // 今日宜忌
  {
    bitWrite(backgroundTask, BGT_GET_WanNianLi, 1);
  }
  else if (i == index++) // 打开 检查更新 任务
  {
    bitWrite(backgroundTask, BGT_CHECK_UPDATE, 1);
  }
}
void display_mainSet_init()
{
  eepSavePage(page_mainSet);

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF); //关闭滑动条
  //lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_CENTER);
  lv_obj_set_style_pad_top(page.p[page.index], 5, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 5, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  //参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值    控制Y轴排布
  //参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER    
  //参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。             控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  //lv_obj_set_flex_grow(page2, 5);
  
  // 设置垂直滚动结束时捕捉子对象的位置
  lv_obj_set_scroll_snap_y(page.p[page.index], LV_SCROLL_SNAP_NONE);  // 不要对齐，留在原地

  String obj_name[15];
  uint8_t count = 0;
  obj_name[count++] = F("配网");
  obj_name[count++] = F("休眠设置");
  obj_name[count++] = F("WiFi选择");
  obj_name[count++] = F("时钟校准");
  obj_name[count++] = F("文件\n管理器");
  obj_name[count++] = F("闹钟");
  obj_name[count++] = F("蜂鸣器");
  obj_name[count++] = F("电量计");
  obj_name[count++] = F("空气质量");
  obj_name[count++] = F("位置信息");
  obj_name[count++] = F("码表");
  obj_name[count++] = F("备忘录");
  obj_name[count++] = F("前置光");
  obj_name[count++] = F("今日宜忌");
  obj_name[count++] = F("检查更新");

  lv_obj_t *but[count];
  lv_obj_t *label[count];
  for (uint8_t i = 0; i < count; i++)
  {
    // 将项目添加到列
    but[i] = lv_button_create(page.p[page.index]);
    uint16_t text_width = lv_text_get_width(obj_name[i].c_str(), obj_name[i].length(), lv_obj_get_style_text_font(but[i], 0), 0);
    uint16_t text_width_zl =  text_width / 65;
    lv_obj_set_size(but[i], 68, 22 + (text_width_zl * 20));
    //lv_obj_align(but[i], LV_ALIGN_CENTER, 0, 0); // 对齐方式
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_ANY); // 移除阴影

    // 青色和绿色交替
    if (!(i & 1)) //  偶数
      lv_obj_set_style_bg_color(but[i], MY_COLOR_CYAN, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_bg_color(but[i], MY_COLOR_GREEN, LV_STATE_DEFAULT);

    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色

    lv_obj_set_style_border_width(but[i], 1, 0);                // 设置边框宽度
    lv_obj_set_style_border_color(but[i], MY_COLOR_MAGENTA, 0); // 设置边框颜色

    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    lv_obj_set_width(label[i], 66);
    lv_obj_align(label[i], LV_ALIGN_CENTER, 0, 0);        // 对齐方式
    lv_label_set_long_mode(label[i], LV_LABEL_LONG_WRAP); // 设置文本长字符模式
    lv_obj_set_style_text_align(label[i], LV_TEXT_ALIGN_CENTER, 0);
    // lv_label_set_text_fmt(label[i], obj_name[i].c_str(), timeArray[i]); // 标签文本
    lv_label_set_text(label[i], obj_name[i].c_str()); // 标签文本
    lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);

    lv_group_add_obj(group_my, but[i]);                                                 // 将对象邦定到组
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);        // 按钮聚焦动画
    lv_obj_add_event_cb(but[i], display_mainSet_event_skip, LV_EVENT_PRESSED, &num[i]); // 按钮按下事件
  }
  lv_obj_add_event_cb(but[count - 1], display_mainSet_event3, LV_EVENT_FOCUSED, NULL); // 弹窗作者和版本的事件

  // 自动设置滚动方式的事件
  lv_obj_add_event_cb(but[1], display_mainSet_event2, LV_EVENT_FOCUSED, NULL);   // 聚焦事件
  lv_obj_add_event_cb(but[1], display_mainSet_event2, LV_EVENT_DEFOCUSED, NULL); // 失焦事件

  /*
    // 无空气质量传感器，隐藏对象
  #if AIR_TYPE == 0
        lv_obj_add_flag(but[5], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(but[11], LV_OBJ_FLAG_HIDDEN);
  #endif
  #if FUEL_GAUGE_TYPE == 0
        lv_obj_add_flag(but[7], LV_OBJ_FLAG_HIDDEN);
  #endif
  */
  //lv_obj_update_layout(page.p[page.index]);
  //int32_t num = lv_obj_get_child_count(page.p[page.index]);
  //LV_LOG_USER("page.p[page.index]对象数量:%u", num);

  // 将对象邦定到组
  lv_group_add_obj(group_my, page.p[page.index]);
  // 聚焦触发 切换页面
  lv_obj_add_event_cb(page.p[page.index], display_mainSet_EVENT_FOCUSED, LV_EVENT_FOCUSED, NULL);
  lv_obj_add_event_cb(page.p[page.index], display_mainSet_EVENT_DEFOCUSED, LV_EVENT_DEFOCUSED, NULL);

  lv_obj_t *label_bottom;
  label_share[0] = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(label_share[0], 80, 45);
  lv_obj_add_style(label_share[0], &style_shadow, LV_STATE_ANY);      // 移除阴影
  lv_obj_add_style(label_share[0], &style_squareShape, LV_STATE_ANY); // 设置为方形
  lv_obj_set_style_bg_opa(label_share[0], LV_OPA_0, 0);

  label_share[1] = lv_obj_create(label_share[0]);
  lv_obj_set_size(label_share[1], 80, 45);
  lv_obj_align(label_share[1], LV_ALIGN_CENTER, 0, 0); // 对齐方式
  lv_obj_add_style(label_share[1], &style_shadow, LV_STATE_ANY); // 移除阴影     
  lv_obj_add_style(label_share[1], &style_squareShape, LV_STATE_ANY); // 设置为方形
  lv_obj_set_style_bg_color(label_share[1], MY_COLOR_MAGENTA, LV_STATE_DEFAULT);

  // 标签对象 
  label_bottom = lv_label_create(label_share[1]);                      // 创建标签
  lv_label_set_long_mode(label_bottom, LV_LABEL_LONG_SCROLL_CIRCULAR); // 长字符模式
  lv_obj_set_style_anim_duration(label_bottom, 3000, 0);               // 滚动时间
  lv_obj_set_width(label_bottom, 70);                                  // 设置宽度
  lv_label_set_text(label_bottom, String(F("By 甘草酸不酸")).c_str());
  lv_obj_set_style_text_color(label_bottom, MY_COLOR_WHITE, 0);
  lv_obj_align(label_bottom, LV_ALIGN_LEFT_MID, -12, -9); // 对齐方式
  // 标签对象
  label_bottom = lv_label_create(label_share[1]); // 创建标签
  lv_obj_set_style_text_align(label_bottom, LV_TEXT_ALIGN_CENTER, 0); // 文本对齐方式
  lv_label_set_text(label_bottom, version);                           // 标签文本
  lv_obj_set_style_text_color(label_bottom, MY_COLOR_WHITE, 0);       // 文本颜色
  lv_obj_align(label_bottom, LV_ALIGN_CENTER, 0, 10);                 // 对齐方式
  lv_obj_add_flag(label_share[0], LV_OBJ_FLAG_HIDDEN); // 隐藏对象

  //lv_obj_update_layout(page.p[page.index]);
  // 设置按钮为可聚焦状态
  // lv_obj_add_state(but[0], LV_STATE_FOCUS_KEY);
  // lv_group_focus_obj(but[0]); // 将焦点设为第一个子对象处
  // lv_group_focus_next(group_my);
}

//****** 加速度计界面
float roll_zero = 0.0;  // 俯仰零点
float pitch_zero = 0.0; // 横滚零点
void updateAcc_timer_cb(lv_timer_t *time) // 定时更新加速度数据
{
  if (eep_disPage != page_acc)
  {
    bitWrite(backgroundTask, BGT_ACC_READ, 0); // 标记关闭
    return;
  }

  if (eep_accDispMod == 0) // 原始数据
  {
    lv_label_set_text_fmt(label_share[0], "X:%d", acc.x);
    lv_label_set_text_fmt(label_share[1], "Y:%d", acc.y);
    lv_label_set_text_fmt(label_share[2], "Z:%d", acc.z);
  }
  else if (eep_accDispMod == 1)  // 原始滤波数据
  {
    lv_label_set_text_fmt(label_share[0], "X:%d", acc.x);
    lv_label_set_text_fmt(label_share[1], "Y:%d", acc.y);
    lv_label_set_text_fmt(label_share[2], "Z:%d", acc.z);
  }
  else if (eep_accDispMod == 2)  // 角度原始数据
  {
     // 俯仰
     float roll = atan2(acc.y, acc.z) * 180.0 / PI;
     // 横滚
     float pitch = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z)) * 180.0 / PI;
     lv_label_set_text_fmt(label_share[0], "X:%.1f°", roll);
     lv_label_set_text_fmt(label_share[1], "Y:%.1f°", pitch);
     lv_label_set_text(label_share[2], "Z:N/A");
  }
  else if (eep_accDispMod == 3)  // 角度调零数据
  {
     // 俯仰
     float roll = atan2(acc.y, acc.z) * 180.0 / PI;
     roll -= roll_zero; // 补偿零点
     // 横滚
     float pitch = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z)) * 180.0 / PI;
     pitch -= pitch_zero; // 补偿零点
     lv_label_set_text_fmt(label_share[0], "X:%.1f°", roll);
     lv_label_set_text_fmt(label_share[1], "Y:%.1f°", pitch);
     lv_label_set_text(label_share[2], "Z:N/A");
  }
  /*char *c = (char *)lv_event_get_user_data(e);
  //lv_event_dsc_get_user_data
  lv_obj_t *obj = lv_event_get_target_obj(e);
  if     (c[0] == 'x') lv_label_set_text_fmt(obj, "X：%d", acc.x);
  else if(c[0] == 'y') lv_label_set_text_fmt(obj, "Y：%d", acc.y);
  else if(c[0] == 'z') lv_label_set_text_fmt(obj, "Z：%d", acc.z);*/
}
void display_acc_event(lv_event_t *e) //短按事件
{
  //lv_event_code_t code = lv_event_get_code(e);
  //lv_obj_t *obj = lv_event_get_target_obj(e);
  //Serial.print("acc code:");Serial.println(code);
  uint8_t key = lv_indev_get_key(lv_indev_active());
  //Serial.print("acc key:");Serial.println(key);
  if (key == LV_KEY_LEFT || key == LV_KEY_RIGHT)
  {
    // 删除定时器
    if (lvTimer_share[0] != NULL)
    {
      lv_timer_delete(lvTimer_share[0]);
      lvTimer_share[0] = NULL;
    }
    // 关闭加速度读取任务
    bitWrite(backgroundTask, BGT_ACC_READ, 0);
    if (key == LV_KEY_RIGHT)
    {
      display_jitterSet_init(); // 切换至抖动设置界面
      lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_MOVE_TOP, PAGE_SWITCH_ANIM_TIME, 0, true);
    }
    else if(key == LV_KEY_LEFT)
    {
      display_clock_init(); // 切换至时钟界面
      lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_MOVE_BOTTOM, PAGE_SWITCH_ANIM_TIME, 0, true);
      bitWrite(backgroundTask, BGT_CLOCK_READ, 1); //打开时钟读取任务
    }
  }
  else if(key == LV_KEY_ENTER)
  {
    /*while (getKey() == 1)
    {
      Serial.println("11111");
      vTaskDelay(1);
    }*/

    // 获取第4个子对象的子对象
    lv_obj_t *label = lv_obj_get_child(lv_obj_get_child(page.p[page.index], 4), 0); 

    lv_anim_t *a = lv_anim_get(label, label_y_bounce_anim_cb);
    if (a != NULL) return ; // 如果动画正在播放，直接返回

    buzzerSen(30);

    String text; 
    eep_accDispMod++;
    if (eep_accDispMod > 3) eep_accDispMod = 0;
    if      (eep_accDispMod == 0) text = F("原始");
    else if (eep_accDispMod == 1) text = F("原始滤波");
    else if (eep_accDispMod == 2) text = F("角度原始");
    else if (eep_accDispMod == 3) text = F("角度调零");
    lv_label_set_text(label, text.c_str());
    label_y_bounce_anim_init(label, 10);
    //uint8_t y = lv_obj_get_y(label_share[0]);
    //Serial.printf("label_share[0]_y:%d\n", y);

    // 添加随机跳动
    label_y_bounce_anim_init(label_share[0], random(-5, 5));
    label_y_bounce_anim_init(label_share[1], random(-5, 5));
    label_y_bounce_anim_init(label_share[2], random(-5, 5));
    label_x_bounce_anim_init(label_share[0], random(-5, 5));
    label_x_bounce_anim_init(label_share[1], random(-5, 5));
    label_x_bounce_anim_init(label_share[2], random(-5, 5));
    eepSaveState = 1; // 标记保存eeprom
  }
}
void acc_zero_cb() // 长按时间 蜂鸣器播放结束的回调
{
  //printf("音乐播放完成！\n");
  
   // 自动跳转至角度调零页面
  if (eep_disPage != page_acc)
  {
    bitWrite(backgroundTask, BGT_ACC_READ, 0); // 标记关闭
    return;
  }
  eep_accDispMod = 3;
  String text = F("角度调零");
  lv_obj_t *label = lv_obj_get_child(lv_obj_get_child(page.p[page.index], 4), 0);
  lv_anim_t *a = lv_anim_get(label, label_y_bounce_anim_cb);
  lv_label_set_text(label, text.c_str());
  label_y_bounce_anim_init(label, 10);
  // 添加随机跳动
  label_y_bounce_anim_init(label_share[0], random(-5, 5));
  label_y_bounce_anim_init(label_share[1], random(-5, 5));
  label_y_bounce_anim_init(label_share[2], random(-5, 5));
  label_x_bounce_anim_init(label_share[0], random(-5, 5));
  label_x_bounce_anim_init(label_share[1], random(-5, 5));
  label_x_bounce_anim_init(label_share[2], random(-5, 5));
  eepSaveState = 1; // 标记保存eeprom
  my_msgbox_send(F("角度"), F("调零完成"), 800);
  // 俯仰
  roll_zero = atan2(acc.y, acc.z) * 180.0 / PI;
  // 横滚
  pitch_zero = atan2(-acc.x, sqrt(acc.y * acc.y + acc.z * acc.z)) * 180.0 / PI;
}
void display_acc_event1(lv_event_t *e) // 长按事件
{
  //lv_event_code_t code = lv_event_get_code(e);
  //lv_obj_t *obj = lv_event_get_target_obj(e);
  //Serial.print("acc code:");Serial.println(code);
  uint8_t i = 0;
  uint16_t *melody = (uint16_t *)malloc((3 * 7 + 1) * sizeof(uint16_t)); //频率，时长，延时
  melody[i++] = 3500; melody[i++] = 100; melody[i++] = 60;
  melody[i++] = 4500; melody[i++] = 100; melody[i++] = 60;
  melody[i++] = 2000; melody[i++] = 150; melody[i++] = 300;

  melody[i++] = 3000; melody[i++] = 300; melody[i++] = 600;
  melody[i++] = 3000; melody[i++] = 300; melody[i++] = 600;
  melody[i++] = 3000; melody[i++] = 300; melody[i++] = 600;

  melody[i++] = 4900; melody[i++] = 500; melody[i++] = 800; 

  melody[i] = 0;
  buzzer_music_rtos_init(melody, acc_zero_cb);

  //uint8_t key = lv_indev_get_key(lv_indev_active());
  //Serial.print("key:");Serial.println(key);
}
void display_acc_init()
{
  eepSavePage(page_acc);

  LV_FONT_DECLARE(MiSans_Bold_16px);

  pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_size(page.p[page.index], TFT_HOR_RES, TFT_VER_RES);
  lv_obj_align(page.p[page.index], LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF); //关闭滑动条
  lv_obj_set_style_pad_top(page.p[page.index], 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 0, LV_STATE_DEFAULT);

  lv_group_add_obj(group_my, page.p[page.index]); // 将对象邦定到组
  lv_obj_add_event_cb(page.p[page.index], display_acc_event, LV_EVENT_KEY, NULL);
  lv_obj_add_event_cb(page.p[page.index], display_acc_event1, LV_EVENT_LONG_PRESSED, NULL);

  lv_obj_t *title_bg;
  title_bg = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(title_bg, 74, 30);
  lv_obj_align(title_bg, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_set_style_bg_color(title_bg, MY_COLOR_GREEN, 0);
  lv_obj_set_scrollbar_mode(title_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_add_style(title_bg, &style_shadow, 0);               // 添加阴影不透明度样式
  lv_obj_add_style(title_bg, &style_squareShape, 0);          // 添加方形样式
  lv_obj_t *title_label;
  title_label = lv_label_create(title_bg);
  lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(title_label, String("加速度计").c_str());

  lv_obj_t *obj[3];
  for (uint8_t i = 0; i < 3; i++)
  {
    // 对象
    obj[i] = lv_obj_create(page.p[page.index]);
    lv_obj_set_size(obj[i], 76, 30);
    lv_obj_align(obj[i], LV_ALIGN_TOP_MID, 0, (i + 1) * 30 + 2);
    lv_obj_set_style_bg_color(obj[i], MY_COLOR_CYAN, LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(obj[i], LV_SCROLLBAR_MODE_OFF);  // 关闭滑动条
    lv_obj_add_style(obj[i], &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
    lv_obj_set_style_radius(obj[i], 0, 0);                     // 设置圆角
    lv_obj_set_style_pad_all(obj[i], 4, 0);                    // 设置边距
    lv_obj_set_style_text_color(obj[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    // 标签
    label_share[i] = lv_label_create(obj[i]); // X
    lv_obj_align(label_share[i], LV_ALIGN_LEFT_MID, -3, 0);
    lv_obj_set_style_text_font(label_share[i], &MiSans_Bold_16px, 0);
  }

  // 底部模式提示 对象
  lv_obj_t *bottom_bg= lv_obj_create(page.p[page.index]);
  lv_obj_set_size(bottom_bg, 74, 20);
  lv_obj_align(bottom_bg, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_bg_color(bottom_bg, MY_COLOR_BLACK, 0);
  lv_obj_set_scrollbar_mode(bottom_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_add_style(bottom_bg, &style_shadow, 0);               // 添加阴影不透明度样式
  lv_obj_add_style(bottom_bg, &style_squareShape, 0);          // 添加方形样式
  // 底部模式提示 标签
  lv_obj_t *bottom_label = lv_label_create(bottom_bg);
  lv_obj_align(bottom_label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(bottom_label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  String text;
  if      (eep_accDispMod == 0) text = F("原始");
  else if (eep_accDispMod == 1) text = F("原始滤波");
  else if (eep_accDispMod == 2) text = F("角度原始");
  else if (eep_accDispMod == 3) text = F("角度调零");
  lv_label_set_text(bottom_label, text.c_str());

  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(updateAcc_timer_cb, 100, NULL); // 定时更新

  //int32_t num = lv_obj_get_child_count(page2);
  //LV_LOG_USER("page2对象数量:%u", num);
}

//****** 时钟界面
void updateClock_timer_cb(lv_timer_t *time) // 定时更新时钟数据
{
  if (eep_disPage != page_clock)
  {
    bitWrite(backgroundTask, BGT_CLOCK_READ, 0); // 标记关闭
    return;
  }

  // 秒标签已删除，返回
  if (label_timeSecond == NULL) return;
  // 打开了备忘录功能并且有句子，返回
  //if (eep_memoClockEn && eep_inAWord.length() > 1 && ((RTC_clock_count & 1) == 0)) return;

  String hour = String(curTime.hour);
  String minute = String(curTime.minute);
  if (curTime.hour <= 9) hour = "0" + String(curTime.hour);
  if (curTime.minute <= 9) minute = "0" + String(curTime.minute);
  lv_label_set_text_fmt(label_timeHour, "%s", hour);
  lv_label_set_text_fmt(label_timeMinute, "%s", minute);
  lv_label_set_text_fmt(label_timeSecond, "%d", curTime.second);
  lv_label_set_text_fmt(label_temp, "%.0f℃", cpuTemp);

  // 更新电池绿色内容
#if FUEL_GAUGE_TYPE == 0
  bat_soc = batVccToPer(bat_vcc);
#else
  get_bat_soc();
#endif 

  uint8_t w = map(bat_soc, 0, 100, 3, 21);
  lv_obj_set_size(bat_g, w, 9);
  //更新电量
  if (bat_soc >= 10.0) lv_label_set_text_fmt(label_batPer, "%d%%", (uint8_t)bat_soc);
  else               lv_label_set_text_fmt(label_batPer, "%.1f%%", bat_soc);
  if (bat_soc > 60) // 大于60显示绿色
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_GREEN, LV_STATE_DEFAULT);   // 背景颜色
  else if (bat_soc > 30) // 大于30显示洋红
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_MAGENTA, LV_STATE_DEFAULT); // 背景颜色
  else // 小于等于30显示红色
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_RED, LV_STATE_DEFAULT);     // 背景颜色
}
//定时器回调 永久休眠
void sleep_zero_time_cb(lv_timer_t *a) // 播放完低电图片后永久休眠的回调
{
  esp_sleep(0);
}
//定时器回调 时钟界面定时器休眠策略
void clockTimedWakeUp_time_cb(lv_timer_t *t) // 定时唤醒的事件回调的定时器回调
{
  // 播放低电量图片
  if (bat_vcc < BAT_LOW2) // BAT_LOW2
  {
    // 自定义图片打开成功
    if (eep_batSleepPicEn && eep_batSleepPic.length() > 1)
    {
      File file = LittleFS.open(eep_batSleepPic);
      if (file)
      {
        display_picture_init(eep_batSleepPic, 0);
        lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
        eep_doudong = 1;
      }
      file.close();
    }

    // 创建一个单次定时器,3秒后让系统永久休眠
    lv_timer_t *timer = lv_timer_create(sleep_zero_time_cb, 3000, NULL); // 3秒后打开
    lv_timer_set_repeat_count(timer, 1);
    lv_timer_set_auto_delete(timer, true);
  }
  else // 正常休眠
  { 
    clock_read();
    sleepTime = 60000 - (curTime.second * 1000);
    if (sleepTime <= 0) sleepTime = 100;
    if (eep_clockSleepOffScreen) sleepTime = 0; // 时钟界面息屏打开不再定时唤醒
    esp_sleep(sleepTime);
  }
}
void clockSleep_event_cb(lv_event_t *e) // 定时唤醒的事件回调
{
  // 创建一个单次定时器
  lv_timer_t *timer = lv_timer_create(clockTimedWakeUp_time_cb, 50, NULL); // 0.05秒后打开
  lv_timer_set_repeat_count(timer, 1);
  lv_timer_set_auto_delete(timer, true);
}
void display_clock_event(lv_event_t *e)
{
  //lv_event_code_t code = lv_event_get_code(e);
  //lv_obj_t *obj = lv_event_get_target_obj(e);
  uint8_t key = lv_indev_get_key(lv_indev_active());
  if (key == LV_KEY_RIGHT)
  {
    // 删除时钟数据更新定时器
    if (lvTimer_share[0] != NULL)
    {
      lv_timer_delete(lvTimer_share[0]);
      lvTimer_share[0] = NULL;
    }
    // 关闭时钟读取任务
    bitWrite(backgroundTask, BGT_CLOCK_READ, 0);
    display_acc_init(); //切换至加速度界面界面
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_MOVE_TOP, PAGE_SWITCH_ANIM_TIME, 0, true);
    bitWrite(backgroundTask, BGT_ACC_READ, 1); // 打开加速度读取任务
  }
}
void display_clock_init()
{
  eepSavePage(page_clock);

  LV_FONT_DECLARE(rog_38px);
  LV_FONT_DECLARE(MiSans_Bold_14px);
  LV_FONT_DECLARE(ArialRoundedMTBold_14px);
  LV_FONT_DECLARE(DinkieBitmap_10px);
  
  clock_read();
  uint8_t index = pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_size(page.p[index], TFT_HOR_RES, TFT_VER_RES);
  lv_obj_align(page.p[index], LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);             // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_squareShape, 0);                      // 添加正方形样式
  lv_group_add_obj(group_my, page.p[index]);                                   // 将对象邦定到组
  lv_obj_add_event_cb(page.p[index], display_clock_event, LV_EVENT_KEY, NULL); // 设置回调

  //****************** 时钟的背景 ******************
  lv_obj_t *clock_bg = lv_obj_create(page.p[index]);
  lv_obj_set_scrollbar_mode(clock_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_set_size(clock_bg, 72, 79);
  // lv_obj_set_style_bg_color(clock_bg, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(clock_bg, 0, LV_STATE_DEFAULT);                  // 设置边距
  lv_obj_set_style_radius(clock_bg, 0, LV_STATE_DEFAULT);                   // 设置圆角
  lv_obj_set_style_border_color(clock_bg, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 边框颜色
  lv_obj_set_style_border_width(clock_bg, 2, LV_STATE_DEFAULT);             // 边框宽度
  lv_obj_align(clock_bg, LV_ALIGN_TOP_MID, 0, 0);
  // 画时间
  label_timeHour = lv_label_create(clock_bg); // 小时
  lv_obj_set_style_pad_all(label_timeHour, 0, LV_STATE_DEFAULT); //设置边距
  lv_obj_align(label_timeHour, LV_ALIGN_TOP_MID, 0, 5);
  String hour = String(curTime.hour);
  String minute = String(curTime.minute);
  if (curTime.hour <= 9) hour = "0" + String(curTime.hour);
  if (curTime.minute <= 9) minute = "0" + String(curTime.minute);
  lv_label_set_text_fmt(label_timeHour, "%s", hour);
  lv_obj_set_style_text_color(label_timeHour, MY_COLOR_BLACK, LV_STATE_DEFAULT);//字体颜色
  lv_obj_set_style_text_font(label_timeHour, &rog_38px, LV_STATE_DEFAULT);

  label_timeMinute = lv_label_create(clock_bg); // 分钟
  lv_obj_set_style_pad_all(label_timeMinute, 0, LV_STATE_DEFAULT); //设置边距
  lv_obj_align(label_timeMinute, LV_ALIGN_TOP_MID, 0, 42);
  lv_label_set_text_fmt(label_timeMinute, "%s", minute);
  lv_obj_set_style_text_color(label_timeMinute, MY_COLOR_BLACK, LV_STATE_DEFAULT);//字体颜色
  lv_obj_set_style_text_font(label_timeMinute, &rog_38px, LV_STATE_DEFAULT);

  if (RTC_timedWakeUp == 0) // 非定时唤醒
  {
    label_timeSecond = lv_label_create(clock_bg);                    // 秒
    lv_obj_set_style_pad_all(label_timeSecond, 1, LV_STATE_DEFAULT); // 设置边距
    lv_obj_align(label_timeSecond, LV_ALIGN_RIGHT_MID, 1, 34);
    lv_label_set_text_fmt(label_timeSecond, "%d", curTime.second);
    lv_obj_set_style_text_color(label_timeSecond, MY_COLOR_RED, LV_STATE_DEFAULT); // 字体颜色
    lv_obj_set_style_text_font(label_timeSecond, &DinkieBitmap_10px, LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(label_timeSecond, MY_COLOR_GREEN, LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(label_timeSecond, LV_OPA_100, LV_STATE_DEFAULT);
  }
  //****************** 日期背景 ****************** 
  lv_obj_t *date_bg = lv_obj_create(page.p[index]);
  lv_obj_set_scrollbar_mode(date_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_add_style(date_bg, &style_squareShape, 0);
  lv_obj_set_style_bg_color(date_bg, MY_COLOR_CYAN, LV_STATE_DEFAULT);
  lv_obj_set_size(date_bg, 72, 19);
  lv_obj_set_pos(date_bg, 0, 78);
  
  // 月日星期
  String date = String(curTime.month) + "-" + String(curTime.dayOfMonth) + " 周";
  date += weekDigitalToChinese(curTime.dayOfWeek);
  label_timeDate = lv_label_create(date_bg); // 月日星期
  lv_obj_set_style_pad_all(label_timeDate, 0, LV_STATE_DEFAULT); // 设置边距
  lv_obj_align(label_timeDate, LV_ALIGN_CENTER, 0, 1);
  lv_label_set_text_fmt(label_timeDate, "%s", date);
  lv_obj_set_style_text_color(label_timeDate, MY_COLOR_BLACK, LV_STATE_DEFAULT);// 字体颜色
  lv_obj_set_style_text_font(label_timeDate, &MiSans_Bold_14px, LV_STATE_DEFAULT);

  //****************** 温度的背景 ****************** 
  lv_obj_t *temp_bg = lv_obj_create(page.p[index]);
  lv_obj_set_scrollbar_mode(temp_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_add_style(temp_bg, &style_squareShape, 0);
  lv_obj_set_size(temp_bg, 72, 20);
  lv_obj_set_pos(temp_bg, 0, 101);
  lv_obj_set_style_bg_color(temp_bg, MY_COLOR_BLUE, LV_STATE_DEFAULT);
  label_temp = lv_label_create(temp_bg); // cpu温度
  lv_obj_set_style_pad_all(label_temp, 0, LV_STATE_DEFAULT); //设置边距
  lv_obj_align(label_temp, LV_ALIGN_LEFT_MID, 6, 0);
  lv_label_set_text_fmt(label_temp, "%.0f℃", cpuTemp);
  lv_obj_set_style_text_color(label_temp, MY_COLOR_WHITE, LV_STATE_DEFAULT);//字体颜色
  lv_obj_set_style_text_font(label_temp, &MiSans_Bold_14px, LV_STATE_DEFAULT);
  //****** 画cpu图标
  /*lv_point_precise_t *line_points = my_draw_rectangle(58, 110, 7, 7);
  lv_obj_t *line1 = lv_line_create(page.p[index]);
  lv_line_set_points(line1, line_points, 5);                            // 点数量
  lv_obj_set_style_line_width(line1, 1, LV_STATE_DEFAULT);              // 线宽度
  lv_obj_set_style_line_color(line1, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 线颜色
  lv_obj_set_style_line_rounded(line1, true, LV_STATE_DEFAULT);         // 线圆角
  */
  LV_IMAGE_DECLARE(img_cpu);
  lv_obj_t *img1 = lv_image_create(temp_bg);
  lv_image_set_src(img1, &img_cpu);
  lv_obj_align(img1, LV_ALIGN_RIGHT_MID, -6, 0);

  //****************** 电量背景 ******************
  lv_obj_t *power_bg = lv_obj_create(page.p[index]);
  lv_obj_set_scrollbar_mode(power_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_set_style_bg_color(power_bg, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  lv_obj_add_style(power_bg, &style_squareShape, 0);
  lv_obj_set_size(power_bg, 72, 19);
  lv_obj_align(power_bg, LV_ALIGN_BOTTOM_MID, 0, 0);
  // 画电池的白色外框
  lv_obj_t *bat = lv_obj_create(power_bg);
  lv_obj_set_size(bat, 25, 13);
  lv_obj_set_style_bg_color(bat, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_set_style_pad_all(bat, 0, LV_STATE_DEFAULT);               // 设置边距
  lv_obj_set_style_radius(bat, 2, LV_STATE_DEFAULT);                // 设置圆角
  lv_obj_set_style_border_width(bat, 0, LV_STATE_DEFAULT);          // 边框宽度
  lv_obj_align(bat, LV_ALIGN_LEFT_MID, 3, 0);
  // 画电池的绿色内容
  bat_g = lv_obj_create(bat);

#if FUEL_GAUGE_TYPE == 0
  bat_soc = batVccToPer(bat_vcc);
#else
  get_bat_soc();
#endif

  uint8_t w = map(bat_soc, 0, 100, 3, 21);
  lv_obj_set_size(bat_g, w, 9);
  if (bat_soc > 60) // 大于60显示绿色
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_GREEN, LV_STATE_DEFAULT);   // 背景颜色
  else if (bat_soc > 30) // 大于30显示洋红
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_MAGENTA, LV_STATE_DEFAULT); // 背景颜色
  else // 小于等于30显示红色
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_RED, LV_STATE_DEFAULT);     // 背景颜色

  lv_obj_set_style_pad_all(bat_g, 0, LV_STATE_DEFAULT);               // 设置边距
  lv_obj_set_style_radius(bat_g, 1, LV_STATE_DEFAULT);                // 设置圆角
  lv_obj_set_style_border_width(bat_g, 0, LV_STATE_DEFAULT);          // 边框宽度
  lv_obj_align(bat_g, LV_ALIGN_LEFT_MID, 2, 0);
  // 画电池的白色头
  lv_obj_t *bat_w = lv_obj_create(power_bg);
  lv_obj_set_size(bat_w, 2, 9);
  lv_obj_set_style_bg_color(bat_w, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_set_style_pad_all(bat_w, 0, LV_STATE_DEFAULT);               // 设置边距
  lv_obj_set_style_radius(bat_w, 1, LV_STATE_DEFAULT);                // 设置圆角
  lv_obj_set_style_border_width(bat_w, 0, LV_STATE_DEFAULT);          // 边框宽度
  lv_obj_align_to(bat_w, bat, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
  // 画电量百分比
  label_batPer = lv_label_create(power_bg);
  lv_obj_align(label_batPer, LV_ALIGN_RIGHT_MID, -1, 1);
  if (bat_soc >= 10.0) lv_label_set_text_fmt(label_batPer, "%d%%", (uint8_t)bat_soc);
  else                 lv_label_set_text_fmt(label_batPer, "%.1f%%", bat_soc);
  lv_obj_set_style_text_color(label_batPer, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 字体颜色
  lv_obj_set_style_text_font(label_batPer, &ArialRoundedMTBold_14px, LV_STATE_DEFAULT);

  //******** 添加自定义的句子
  if (eep_memoClockEn && eep_inAWord.length() > 1 && ((RTC_clock_count & 1) == 0)) // 偶数
  {
    lv_color_t color[8] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW, MY_COLOR_MAGENTA,
                           MY_COLOR_BLUE, MY_COLOR_RED, MY_COLOR_WHITE, MY_COLOR_BLACK};

    //****************** 一句话
    lv_obj_t *sentence_bg = lv_obj_create(page.p[index]); //背景
    lv_obj_add_style(sentence_bg, &style_squareShape, 0);          // 添加正方形样式
    lv_obj_set_scrollbar_mode(sentence_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
    lv_obj_add_style(sentence_bg, &style_squareShape, 0); 
    lv_obj_set_style_bg_color(sentence_bg, color[eep_memoBg], LV_STATE_DEFAULT);
    lv_obj_set_pos(sentence_bg, 0, 97);
    lv_obj_set_size(sentence_bg, 72, 47);

    const char *inAWord = eep_inAWord.c_str();
    lv_obj_t *sentence = lv_label_create(sentence_bg); // 句子
    lv_obj_add_style(sentence, &style_squareShape, 0); // 添加正方形样式
    const lv_font_t *font = lv_obj_get_style_text_font(sentence, 0);
    // 对长字符分行时，缩短其间隔
    uint8_t line = 1;
    String result = autoLineFeed(inAWord, 72, font, &line); // 自动根据指定像素值添加换行符
    //Serial.printf("line:%d\n", line);
    lv_obj_align(sentence, LV_ALIGN_CENTER, 0, 1);
    lv_label_set_text(sentence, result.c_str());
    lv_obj_set_style_text_color(sentence, color[eep_memoFC], 0); // 字体颜色
    if (line >= 4)
      lv_obj_align(sentence, LV_ALIGN_TOP_MID, 0, -2);
    if (line >= 3)                                       // 三行以上时缩短行间距
      lv_obj_set_style_text_line_space(sentence, -4, 0); // 设置行间距
  }

  //******** 创建定时器并保存句柄
  if (RTC_timedWakeUp == 0) // 非定时唤醒
  {
    lvTimer_share[0] = lv_timer_create(updateClock_timer_cb, 1000, NULL); // 定时更新
  }
  else // 定时唤醒
  {
    lv_obj_add_event_cb(page.p[index], clockSleep_event_cb, LV_EVENT_SCREEN_LOADED, NULL);
  }
}

//****** 退出至时钟设置界面
void backPage_clockSet(lv_event_t *e) 
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出
  {
   my_msgbox_exit(10); // 退出弹窗
    display_clockSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter();     // 打开全局抖动
    focusPosOld_return(); // 回到刚才的焦点
  }
  else if (data[0] == 1) // 返回
  {
   my_msgbox_exit(0); // 退出弹窗
    }
}
//****** 时钟手动校准界面
void clockManualCal_end_cb(lv_event_t *e) // 弹窗退出保存返回
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0 || data[0] == 1) // 退出手动校准界面 || 保存
  {
   my_msgbox_exit(10); // 退出弹窗
    display_clockSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter();     // 打开全局抖动
    focusPosOld_return(); // 回到刚才的焦点
    if (data[0] == 1)
    {
      adapter.writeDateTime(sdjzTime);          // 写入芯片
    }
  }
  else if (data[0] == 2) // 返回手动校准界面
  {
   my_msgbox_exit(0); // 退出弹窗
  }
}
void clockManualCal_event0(lv_event_t *e) // 退出弹窗
{
    my_msgbox_send(F("手动校准"), F("是否退出"), 0, F("退出\n保存\n返回\n"), clockManualCal_end_cb);
}
void clockManualCal_event1(lv_event_t *e) // 切换标签编辑模式的事件 
{
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *obj = lv_event_get_target_obj(e);
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  //Serial.printf("code:%d\n",code);

  if (code == LV_EVENT_PRESSED) // 切换编辑状态
  {
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;
    if (page.keyMode == KEY_MODE_PN) // 进入编辑模式，修改成白底黑字
    {
      page.keyMode = KEY_MODE_RL;
      lv_obj_set_style_bg_color(obj, MY_COLOR_BLACK, LV_STATE_DEFAULT); // 设置背景颜色
      lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
    else  // 取消编辑模式，恢复原来的样式
    {
      page.keyMode = KEY_MODE_PN;
      lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                             MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
      lv_obj_set_style_bg_color(obj, color[i % 6], LV_STATE_DEFAULT); // 设置背景颜色
      if ((i % 6) < 3)
        lv_obj_set_style_text_color(child, MY_COLOR_BLACK, LV_STATE_DEFAULT);
      else
        lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
  }
  else if(code == LV_EVENT_KEY)  // 数值加减
  {
    uint8_t key = lv_indev_get_key(lv_indev_active());
    if (key == LV_KEY_ENTER) return;

    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;  

    // 数值加减
    if (key == LV_KEY_LEFT) // 减
    {
      if (*sm0.num_u8[i] == sm0.min[i])
        *sm0.num_u8[i] = sm0.max[i];
      else
        *sm0.num_u8[i] -= sm0.step[i];
    }
    else if (key == LV_KEY_RIGHT) // 加
    {
      if (*sm0.num_u8[i] == sm0.max[i])
        *sm0.num_u8[i] = sm0.min[i];
      else
        *sm0.num_u8[i] += sm0.step[i];
    }

    String text = String(lv_label_get_text(child));
    int pos = text.indexOf("：");
    text = text.substring(0, pos + 3);
    text += String(*sm0.num_u8[i]);
    // Serial.printf("text:%s", text);
    lv_label_set_text(child, text.c_str()); // 标签文本
  }

  LV_UNUSED(obj);
  LV_UNUSED(child);
}
void display_clockManualCal_init()
{
  eepSavePage(page_clockManualCal, 0);

  uint8_t j = 0;
  sm0.num_u8[j++] = &sdjzTime.year;       // 年
  sm0.num_u8[j++] = &sdjzTime.month;      // 月
  sm0.num_u8[j++] = &sdjzTime.dayOfMonth; // 日
  sm0.num_u8[j++] = &sdjzTime.hour;       // 时
  sm0.num_u8[j++] = &sdjzTime.minute;     // 分
  sm0.num_u8[j++] = &sdjzTime.second;     // 秒
  sm0.num_u8[j++] = &sdjzTime.dayOfWeek;  // 星期 0=星期天
  j = 0;
  sm0.step[j++] = 1; // 加减的步进值
  sm0.step[j++] = 1; 
  sm0.step[j++] = 1; 
  sm0.step[j++] = 1; 
  sm0.step[j++] = 1; 
  sm0.step[j++] = 1; 
  sm0.step[j++] = 1; 
  j = 0;
  sm0.min[j++] = 0;  // 最小值
  sm0.min[j++] = 1; 
  sm0.min[j++] = 1; 
  sm0.min[j++] = 0; 
  sm0.min[j++] = 0;
  sm0.min[j++] = 0; 
  sm0.min[j++] = 0; 
  j = 0;
  sm0.max[j++] = 99;  // 最大值
  sm0.max[j++] = 12; 
  sm0.max[j++] = 31; 
  sm0.max[j++] = 23;
  sm0.max[j++] = 59;
  sm0.max[j++] = 59;
  sm0.max[j++] = 6;

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_ON);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[index], 3, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 3, LV_STATE_DEFAULT);

  String obj_name[7];
  uint8_t count = 0;
  if (eep_language == 0)
  {
    obj_name[count++] = F("年：%d");
    obj_name[count++] = F("月：%d");
    obj_name[count++] = F("日：%d");
    obj_name[count++] = F("时：%d");
    obj_name[count++] = F("分：%d");
    obj_name[count++] = F("秒：%d");
    obj_name[count++] = F("星期：%d");
  }
  else
  {
    obj_name[count++] = F("Year：%d");
    obj_name[count++] = F("Month：%d");
    obj_name[count++] = F("Day：%d");
    obj_name[count++] = F("Hour：%d");
    obj_name[count++] = F("Minute：%d");
    obj_name[count++] = F("Second：%d");
    obj_name[count++] = F("Week：%d");
  }
  
  lv_obj_t *but[7];
  lv_obj_t *label[7];

  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};

  if (sdjzTime.dayOfWeek == 0) sdjzTime.dayOfWeek = 7;

  uint16_t timeArray[7];
  for (uint8_t i = 0; i < 7; i++)
    timeArray[i] = *sm0.num_u8[i];

  for (uint8_t i = 0; i < 7; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[index]);
    lv_obj_set_size(but[i], 72, 20);                                            // 设置大小
    lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 24);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
    // 标签对象
    label[i] = lv_label_create(but[i]);                                 // 创建标签
    lv_obj_align(label[i], LV_ALIGN_LEFT_MID, 6, 0);                    // 居中对齐
    lv_label_set_text_fmt(label[i], obj_name[i].c_str(), timeArray[i]); // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);
    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);

    // 按钮触发功能
    lv_obj_add_event_cb(but[i], clockManualCal_event1, LV_EVENT_PRESSED, &num[i]); // 切换编辑状态
    lv_obj_add_event_cb(but[i], clockManualCal_event1, LV_EVENT_KEY, &num[i]);     // 编辑状态下的数值加减
  }

  lv_obj_t *but_exit = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but_exit, 72, 25);                                            // 设置大小
  lv_obj_align(but_exit, LV_ALIGN_TOP_MID, 0, 7 * 24);                          // 设置对齐方式
  lv_obj_set_style_bg_color(but_exit, MY_COLOR_GREEN, LV_STATE_DEFAULT);        // 设置背景颜色
  lv_obj_add_style(but_exit, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but_exit, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but_exit, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_exit, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_exit, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_exit, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but_exit, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_exit, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  lv_obj_t *label_exit = lv_label_create(but_exit);                             // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_CENTER, 0, 0);                              // 对齐方式
  lv_label_set_text(label_exit, "退出");                                        // 标签文本
  if ((7 % 6) < 3)
    lv_obj_set_style_text_color(label_exit, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  else
    lv_obj_set_style_text_color(label_exit, MY_COLOR_WHITE, LV_STATE_DEFAULT);

  lv_obj_add_event_cb(but_exit, clockManualCal_event0, LV_EVENT_PRESSED, NULL);  // 退出回调
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);

  lv_group_add_obj(group_my, but_exit);

  // 将对象邦定到组
  //lv_group_add_obj(group_my, page.p[index]);
  // 聚焦触发 弹出退出返回框
  //lv_obj_add_event_cb(page.p[index], display_clockManualCal_event0, LV_EVENT_FOCUSED, NULL);
}
//****** 时钟设置界面
void clockSet_event(lv_event_t *e) // 跳转事件
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  //Serial.printf("跳转事件:%d\n", i);

  if (i == 0) // 手动校准
  {
    clock_read();
    sdjzTime = curTime;
    focusPosOld_save(); // 保存上一个界面的焦点
    display_clockManualCal_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else if (i == 1) // 联网校准
  {
    bitWrite(backgroundTask, BGT_CLOCK_AUTU_CALI, 1);
  }
  else if (i == 2) // 卫星校准
  {
    my_msgbox_send(F("卫星校准"), F("未完成"), 1000);
  }
}
void display_clockSet_init()
{
  eepSavePage(page_clockSet, 0);

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 3, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  // 参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值 控制Y轴排布
  // 参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER
  // 参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。 控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // lv_obj_set_flex_grow(page.p[page.index], 3); //设置对象生长的宽度或高度（在主轴上），以填充自由空间
  lv_obj_set_style_pad_row(page.p[page.index], 5, LV_STATE_DEFAULT); // 设置行间距为5像素

  uint8_t optNum = 3;
  String obj_name[optNum] = {F("手动校准"), F("联网校准"), F("卫星校准")};
  lv_obj_t *but[optNum];
  lv_obj_t *label[optNum];
  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
  for (uint8_t i = 0; i < optNum; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[page.index]);
    lv_obj_set_size(but[i], 72, 25);                                            // 设置大小
    //lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 46);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
    
    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    lv_obj_align(label[i], LV_ALIGN_CENTER, 0, 0);        // 对齐方式
    lv_label_set_text(label[i], obj_name[i].c_str());     // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);

    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
    // 按钮触发功能
    lv_obj_add_event_cb(but[i], clockSet_event, LV_EVENT_PRESSED, &num[i]);
  }

  lv_obj_t *but_exit = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but_exit, 72, 25); // 设置大小
  // lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 5 * 46);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but_exit, MY_COLOR_RED, LV_STATE_DEFAULT);          // 设置背景颜色
  lv_obj_add_style(but_exit, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but_exit, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but_exit, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_exit, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_exit, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_exit, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but_exit, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_exit, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  lv_obj_t *label_exit = lv_label_create(but_exit);                             // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_CENTER, 0, 0);                              // 对齐方式
  lv_label_set_text(label_exit, "退出");                                        // 标签文本
  if ((optNum % 6) < 3)
    lv_obj_set_style_text_color(label_exit, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  else
    lv_obj_set_style_text_color(label_exit, MY_COLOR_WHITE, LV_STATE_DEFAULT);

  lv_obj_add_event_cb(but_exit, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);

  lv_group_add_obj(group_my, but_exit);
}

//****** 空气质量界面
void display_air_event_msgbox(lv_event_t *e) // 当屏幕被聚焦时，弹窗弹窗
{
  uint8_t key = lv_indev_get_key(lv_indev_active());
  if (key == LV_KEY_RIGHT || key == LV_KEY_LEFT)
    my_msgbox_send(F("空气质量"), F("是否退出"), 0, F("退出\n返回\n"), backPage_mainSet);
}
void update_air_timer_cb(lv_timer_t *time) // 定时空气质量数据
{
  if (eep_disPage != page_air)
  {
    // bitWrite(backgroundTask, BGT_ACC_READ, 0); // 标记关闭
    return;
  }
  String airDescribe[] = {F("质量优"), F("轻污染"), F("中污染"), F("重污染")};
  lv_color_t color[] = {MY_COLOR_CYAN, MY_COLOR_YELLOW, MY_COLOR_MAGENTA, MY_COLOR_RED};
  uint8_t state = 0;
  lv_label_set_text_fmt(label_share[0], "VOC:%d", vocIndex);
  lv_label_set_text_fmt(label_share[1], "NOx:%d", noxIndex);

  if (vocIndex >= 400)
    state = 3;
  else if (vocIndex >= 250)
    state = 2;
  else if (vocIndex >= 150)
    state = 1;
  else
    state = 0;
  lv_obj_t *parent = lv_obj_get_parent(label_share[0]); // 获取父对象
  lv_obj_t *child = lv_obj_get_child(parent, 1);        // 获取父对象的第二大孩子
  lv_label_set_text(child, airDescribe[state].c_str());
  lv_obj_set_style_bg_color(parent, color[state], 0);

  if (noxIndex >= 300)
    state = 3;
  else if (noxIndex >= 150)
    state = 2;
  else if (noxIndex >= 20)
    state = 1;
  else
    state = 0;
  parent = lv_obj_get_parent(label_share[1]);
  child = lv_obj_get_child(parent, 1);
  lv_label_set_text(child, airDescribe[state].c_str());
  lv_obj_set_style_bg_color(parent, color[state], 0);

  String illustrate = "%d秒";
  if (sgp41_runTime <= 9)
    illustrate += F(",加热中");
  else if (noxIndex == 0)
    illustrate += F(",数据计算中");
  lv_coord_t scroll_offset = lv_obj_get_scroll_x(label_share[2]);
  lv_label_set_text_fmt(label_share[2], illustrate.c_str(), sgp41_runTime);
}
void display_air_init()
{
  eepSavePage(page_air);
  //LV_FONT_DECLARE(MiSans_Bold_16px);
  LV_FONT_DECLARE(MiSans_Bold_14px);

  uint8_t index = pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_size(page.p[index], TFT_HOR_RES, TFT_VER_RES);
  lv_obj_align(page.p[index], LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF); //关闭滑动条
  lv_obj_set_style_pad_top(page.p[index], 3, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 3, LV_STATE_DEFAULT);

  // 将对象邦定到组
  lv_group_add_obj(group_my, page.p[index]);
  // 聚焦触发 弹出退出返回框
  lv_obj_add_event_cb(page.p[index], display_air_event_msgbox, LV_EVENT_KEY, NULL);

  uint8_t count = 0;
  lv_obj_t *obj[4];
  lv_obj_t *label;

  for (uint8_t i = 0; i < 4; i++)
  {
    // 基本对象
    obj[i] = lv_obj_create(page.p[index]);
    uint8_t step = 30;
    if (i == 1 || i == 2) step = 40;
    lv_obj_set_size(obj[i], 72, step);
    //lv_obj_align(obj[i], LV_ALIGN_TOP_MID, 0, i * step);
    if(i > 0) lv_obj_align_to(obj[i], obj[i - 1], LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    if(i == 0) lv_obj_set_style_bg_color(obj[i], MY_COLOR_GREEN, LV_STATE_DEFAULT);
    else lv_obj_set_style_bg_color(obj[i], MY_COLOR_CYAN, LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(obj[i], LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
    lv_obj_add_style(obj[i], &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
    lv_obj_set_style_text_color(obj[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
  }

  String obj_name0 = F("空气质量");
  label = lv_label_create(obj[0]);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_label_set_text(label, obj_name0.c_str());

  //  voc指数
  label_share[0] = lv_label_create(obj[1]);
  lv_obj_align(label_share[0], LV_ALIGN_TOP_LEFT, -12, -11);
  lv_obj_set_style_text_font(label_share[0], &MiSans_Bold_14px, 0);
  //  voc指数-质量描述
  lv_obj_t *label_0 = lv_label_create(obj[1]);
  lv_obj_align(label_0, LV_ALIGN_BOTTOM_LEFT, -12, +14);
  lv_obj_set_style_text_font(label_0, &MISans_16px, 0);

  //  nox指数
  label_share[1] = lv_label_create(obj[2]);
  lv_obj_align(label_share[1], LV_ALIGN_TOP_LEFT, -12, -11);
  lv_obj_set_style_text_font(label_share[1], &MiSans_Bold_14px, 0);
  //  nox指数-质量描述
  label_0 = lv_label_create(obj[2]);
  lv_obj_align(label_0, LV_ALIGN_BOTTOM_LEFT, -12, +14);
  lv_obj_set_style_text_font(label_0, &MISans_16px, 0);

  // 运行时间
  label_share[2] = lv_label_create(obj[3]);
  lv_obj_align(label_share[2], LV_ALIGN_LEFT_MID, -12, 0);
  lv_obj_set_width(label_share[2], 68);
  lv_label_set_long_mode(label_share[2], LV_LABEL_LONG_SCROLL); // 设置文本长字符模式
  lv_obj_set_style_anim_duration(label_share[2], 495, 0);
  lv_obj_set_style_text_font(label_share[2], &MISans_16px, 0);

  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(update_air_timer_cb, 1000, NULL); // 定时更新

  //int32_t num = lv_obj_get_child_count(page2);
  //LV_LOG_USER("page2对象数量:%u", num);
}

//****** 闹钟界面
void display_alarmClock_anim_cb(void *var, int32_t v) // 闹钟编辑界面弹出动画
{
  lv_obj_align((lv_obj_t *)var, LV_ALIGN_CENTER, v, 0); // 设置对齐方式
}
uint8_t getAlarmClockNumber() // 获取闹钟的数量
{
  File file = LittleFS.open(alarmClockRecord);
  if (!file)  return 0;

  uint8_t count = 0; //行计数

  while(file.available())
  {
    char c = file.read();
    if (c == '\n')
    {
      count++;
    }
  }
  file.close();
  return count;
}
void display_alarmClock_event_msgbox(lv_event_t *e) // 当屏幕被聚焦时，弹出退出弹窗
{
  uint8_t key = lv_indev_get_key(lv_indev_active());
  if (key == LV_KEY_PREV)
  {
    my_msgbox_send(F("闹钟"), F("是否退出"), 0, F("退出\n返回\n"), backPage_mainSet);
  }
}
void display_alarmClock_event0(lv_event_t *e)       // 按钮聚焦更改线条颜色
{
  lv_obj_t *obj = lv_event_get_target_obj(e);
  lv_obj_t *child = lv_obj_get_child(obj, 3);
  lv_obj_set_style_line_color(child, MY_COLOR_MAGENTA, 0);

  /*uint8_t key = lv_indev_get_key(lv_indev_active());
  lv_obj_t *focused_obj = lv_group_get_focused(group_my);
  lv_event_code_t code = lv_event_get_code(e);
  uint8_t focusPos = lv_obj_get_index(focused_obj);
  Serial.printf("focusPos:%d\n",focusPos);
  Serial.printf("key:%d\n",key);*/

  /*
  if (focusPos != 0 || focusPos != 5)
    lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_CENTER); // 设置滚动结束时焦点的对齐方式
  else
    lv_obj_set_scroll_snap_y(obj, LV_SCROLL_SNAP_NONE); // 设置滚动结束时焦点的对齐方式
  */

  LV_UNUSED(obj);
}
void display_alarmClock_event1(lv_event_t *e)       // 按钮失焦更改线条颜色
{
  lv_obj_t *obj = lv_event_get_target_obj(e);
  lv_obj_t *child = lv_obj_get_child(obj, 3);
  lv_obj_set_style_line_color(child, MY_COLOR_CYAN, 0);
  LV_UNUSED(obj);
}
void display_alarmClock_event3(lv_event_t *e)       // 切换至编辑界面
{
  buzzerSen(30);
  // lv_obj_t *obj = lv_event_get_target_obj(e);
  // lv_obj_set_state(obj, LV_STATE_PRESSED, false); // 取消按下状态
  display_alarmClock_edit_init();
}
void display_alarmClock_init()
{
  LV_FONT_DECLARE(MiSans_Bold_14px);

  eepSavePage(page_alarmClock, 1); // 保存现在的界面

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[index], 3, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 3, LV_STATE_DEFAULT);

  lv_obj_set_scroll_snap_y(page.p[index], LV_SCROLL_SNAP_CENTER); // 设置滚动结束时焦点的对齐方式

  uint8_t acNum = getAlarmClockNumber();
  if (acNum == 0) // 无文件退出
  {
    my_msgbox_send(F("闹钟"), F("记录丢失"), 0, F("退出\n返回\n"), backPage_mainSet);
    return;
  }

  uint16_t sw_state = 0; // 开关状态位
  String text_time[acNum]; // 时间
  String text_week[acNum]; // 星期
  File file = LittleFS.open(alarmClockRecord);
  for (uint8_t i = 0; i < acNum; i++)
  {
    // 提取开关状态位
    char c = file.read();
    if (c == '1') bitWrite(sw_state, i, 1);
    // 提取星期
    for (uint8_t j = 0; j < 7; j++)
    {
      char c = file.read();
      if(c > '0') text_week[i] += c;
    }
    // 提取小时
    text_time[i] += char(file.read());
    text_time[i] += char(file.read());
    text_time[i] += ":";
    // 提取分钟
    text_time[i] += char(file.read());
    text_time[i] += char(file.read());
    file.read(); //跳过/r 0x0d
    file.read(); //跳过/n 0x0a
  }
  file.close();

  // 创建线条
  static lv_point_precise_t line_points[] = {{0, 0}, {54, 0}};

  /*Create style*/
  /*static lv_style_t style_line;
  lv_style_init(&style_line);
  lv_style_set_line_width(&style_line, 2);
  lv_style_set_line_color(&style_line, MY_COLOR_CYAN);
  //lv_style_set_line_rounded(&style_line, true);*/

  lv_obj_t *but[acNum];
  lv_obj_t *label_time[acNum];
  lv_obj_t *label_week[acNum];
  lv_obj_t *sw[acNum];
  for (uint8_t i = 0; i < acNum; i++)
  {
    // 按钮对象-即外框
    but[i] = lv_button_create(page.p[index]);
    lv_obj_set_size(but[i], 72, 40);                   // 设置大小
    lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 44); // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);    // 设置背景颜色
    //lv_obj_set_style_bg_color(but[i], MY_COLOR_YELLOW, LV_STATE_FOCUS_KEY); // 聚焦时设置背景颜色
    lv_obj_set_style_bg_opa(but[i], LV_OPA_100, LV_STATE_DEFAULT); // 设置背景不透明度
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);     // 设置阴影样式
    lv_obj_set_style_pad_all(but[i], 0, 0);                        // 设置边界
    lv_obj_set_style_border_width(but[i], 0, 0);                   // 边框宽度
    lv_obj_set_style_radius(but[i], 6, 0);                         // 设置圆角

    lv_obj_set_style_border_width(but[i], 3, 0);              // 设置边框宽度
    lv_obj_set_style_border_color(but[i], MY_COLOR_BLACK, 0); // 设置边框颜色

    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);                // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                  // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);         // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                  // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_MAGENTA, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                     // 关闭滑动条

    // 时间标签对象
    label_time[i] = lv_label_create(but[i]);                // 创建标签
    lv_obj_align(label_time[i], LV_ALIGN_LEFT_MID, 2, -9);  // 对齐方式
    lv_label_set_text(label_time[i], text_time[i].c_str()); // 标签文本
    lv_obj_set_style_text_font(label_time[i], &MiSans_Bold_14px, 0);
    lv_obj_set_style_text_color(label_time[i], MY_COLOR_BLACK, 0); // 字体颜色

    // 星期标签对象
    label_week[i] = lv_label_create(but[i]);                // 创建标签
    lv_obj_align(label_week[i], LV_ALIGN_BOTTOM_MID, 0, 3); // 对齐方式
    lv_label_set_text(label_week[i], text_week[i].c_str()); // 标签文本
    lv_obj_set_style_text_font(label_week[i], &MISans_16px, 0);
    lv_obj_set_style_text_color(label_week[i], MY_COLOR_BLACK, 0); // 字体颜色

    // 创建开关
    sw[i] = lv_switch_create(but[i]);
    lv_obj_set_size(sw[i], 20, 11);
    lv_obj_align(sw[i], LV_ALIGN_TOP_RIGHT, -2, 2);
    lv_obj_set_style_bg_color(sw[i], MY_COLOR_RED, LV_PART_MAIN);                           // 开关 关闭的背景颜色
    lv_obj_set_style_bg_color(sw[i], MY_COLOR_GREEN, LV_PART_INDICATOR | LV_STATE_CHECKED); // 开关 打开的背景颜色
    lv_obj_set_style_bg_color(sw[i], MY_COLOR_WHITE, LV_PART_KNOB);                         // 手柄颜色
    if (bitRead(sw_state, i) == 1)
      lv_obj_add_state(sw[i], LV_STATE_CHECKED); // 添加状态
    //else
      //lv_obj_add_state(sw[i], LV_STATE_DEFAULT); // 添加状态

    // 创建线条
    lv_obj_t *line1;
    line1 = lv_line_create(but[i]);
    lv_line_set_points(line1, line_points, 2);
    lv_obj_center(line1);
    lv_obj_align(line1, LV_ALIGN_CENTER, 0, -1);
    lv_obj_set_style_line_width(line1, 2, 0);
    lv_obj_set_style_line_color(line1, MY_COLOR_CYAN, 0);
    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画 
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(but[i], display_alarmClock_event0, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(but[i], display_alarmClock_event1, LV_EVENT_DEFOCUSED, NULL);
    // 按钮触发功能
    lv_obj_add_event_cb(but[i], display_alarmClock_event3, LV_EVENT_PRESSED, NULL); // 切换编辑状态
  }

  // 将对象邦定到组
  lv_group_add_obj(group_my, page.p[index]);
  // 聚焦触发 弹出退出返回框
  lv_obj_add_event_cb(page.p[index], display_alarmClock_event_msgbox, LV_EVENT_FOCUSED, NULL);
}

//****** 闹钟编辑界面
void alarmClock_edit_exit1(lv_anim_t *a)       // 退出
{
  lv_obj_delete(box_share[0]);         // 删除对象
  box_share[0] = NULL;                 // 对象地址清空
  lv_indev_set_group(indev, group_my); // 将组邦定到按键

  //****** 更改记录文件
  // 拼装记录
  bool change = 0;
  String record,record_old;
  String hour = String(shareNum[8]);
  String minute = String(shareNum[9]);
  String week;
  if (shareNum[8] <= 9) hour = "0" + hour;
  if (shareNum[9] <= 9) minute = "0" + minute;
  for (uint8_t i = 0; i < 8; i++)
  {
    // Serial.print("shareNum[" + String(i) + "]:");
    // Serial.println(shareNum[i]);
    String s = String(shareNum[i]);
    record += s;
    //拼装星期
    if (i > 0 && shareNum[i] > 0) week += s;
  }
  record += hour + minute;

  // 打开记录文件
  File file = LittleFS.open(alarmClockRecord, "r+");
  file.seek(focusPos_old[focusPos_old_index] * 14); //偏移至正确位置
  //获取旧内容
  for (uint8_t i = 0; i < 12; i++) record_old += char(file.read());
  //字符串不同就更改文件
  if (strcmp(record.c_str(), record_old.c_str()) != 0)
  {
    //Serial.println("更改文件");
    file.seek(focusPos_old[focusPos_old_index] * 14);
    file.print(record);
    change = 1;
  }
  file.close();

  // 获取闹钟主界面刚才被聚焦的对象
  lv_obj_t *child = lv_obj_get_child(page.p[page.index], focusPos_old[focusPos_old_index]);
  //Serial.printf("focusPos_old:%d\n", focusPos_old[focusPos_old_index]);
  // lv_obj_set_state(child, LV_STATE_PRESSED, false); // 取消按下状态
  // lv_group_focus_obj(child);                        // 聚焦当前按钮

  if (change)
  {
    // 更新内容
    lv_obj_t *label_time = lv_obj_get_child(child, 0); // 时间
    lv_obj_t *label_week = lv_obj_get_child(child, 1); // 星期
    lv_obj_t *sw = lv_obj_get_child(child, 2);         // 开关
    String time = hour + ":" + minute;
    lv_label_set_text(label_time, time.c_str()); // 标签文本
    lv_label_set_text(label_week, week.c_str()); // 标签文本
    if (shareNum[0] == 1)
      lv_obj_set_state(sw, LV_STATE_CHECKED, true); // 切换为打开状态
    else
      lv_obj_set_state(sw, LV_STATE_CHECKED, false); // 切换为关闭状态

    updatealarmClockDifference();
  }
  LV_UNUSED(child);

  // 回到刚才的焦点
  focusPosOld_return();
  
  //Serial.printf("record_old:%s\n", record_old);
 // Serial.printf("record:%s\n", record);
}
void alarmClock_edit_exit0(lv_event_t *e)      // 弹窗退出返回 至主设置界面
{
  // 检查是否在退出中 防止重复触发
  lv_anim_t *b = lv_anim_get(box_share[0], display_alarmClock_anim_cb);
  if (b != NULL) return;

  lv_anim_t a;
  lv_anim_init(&a);                                    // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                   // 设置需要动画的对象
  lv_anim_set_values(&a, 0, 72);                       // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);          // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_overshoot);     // 设置变化特效
  lv_anim_set_completed_cb(&a, alarmClock_edit_exit1); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void alarmClock_edit_sw_event(lv_event_t *e)   // 开启/关闭切换
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  shareNum[0] = !shareNum[0];
  String str = F("已开启");
  if (shareNum[0] == 0) str = F("已关闭");
  lv_label_set_text(obj, str.c_str()); // 标签文本
}
void alarmClock_edit_seek_event(lv_event_t *e) // 星期切换
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];

  if (shareNum[i] == 0) shareNum[i] = i;
  else                  shareNum[i] = 0;

  lv_label_set_text_fmt(obj, "%d", i); // 标签文本
  if (shareNum[i] != 0)
    lv_obj_set_style_text_color(obj, MY_COLOR_RED, 0); // 字体颜色
  else
    lv_obj_set_style_text_color(obj, MY_COLOR_BLACK, 0); // 字体颜色
}
void alarmClock_edit_time_event(lv_event_t *e) // 小时和分钟切换编辑模式和编辑
{
  lv_obj_t *obj = lv_event_get_target_obj(e);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];

  uint8_t key = lv_indev_get_key(lv_indev_active());
  if (key == LV_KEY_ENTER)
  {
    lv_obj_t *obj = lv_event_get_target_obj(e);
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;

    if (page.keyMode == KEY_MODE_PN)
    {
      lv_obj_set_style_text_color(obj, MY_COLOR_RED, 0);
      page.keyMode = KEY_MODE_RL;
    }
    else if (page.keyMode == KEY_MODE_RL)
    {
      lv_obj_set_style_text_color(obj, MY_COLOR_BLACK, 0);
      page.keyMode = KEY_MODE_PN;
    }
  }
  else if(page.keyMode == KEY_MODE_RL) //编辑模式进行加减操作
  {
    lv_obj_t *obj = lv_event_get_target_obj(e);
    addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if (key == LV_KEY_LEFT) // 减
    {
      if (*sm0.num_u8[i] == sm0.min[i])
        *sm0.num_u8[i] = sm0.max[i];
      else
        *sm0.num_u8[i] -= sm0.step[i];
    }
    else if (key == LV_KEY_RIGHT) // 加
    {
      if (*sm0.num_u8[i] == sm0.max[i])
        *sm0.num_u8[i] = sm0.min[i];
      else
        *sm0.num_u8[i] += sm0.step[i];
    }
    String str = String(*sm0.num_u8[i]);
    if (*sm0.num_u8[i] <= 9)  str = "0" + str;
    lv_label_set_text_fmt(obj, "%s", str); // 标签文本
  }

}
void display_alarmClock_edit_init()
{
  LV_FONT_DECLARE(MiSans_Bold_14px);
  LV_FONT_DECLARE(MiSans_Medium_16px);

  //****** 可调数值初始化
  uint8_t j = 0;
  sm0.num_u8[j++] = &shareNum[8];
  sm0.num_u8[j++] = &shareNum[9];
  j = 0;
  sm0.step[j++] = 1; // 加减的步进值
  sm0.step[j++] = 1; // 加减的步进值
  j = 0;
  sm0.min[j++] = 0;  // 最小值
  sm0.min[j++] = 0;  // 最小值
  j = 0;
  sm0.max[j++] = 23; // 最大值
  sm0.max[j++] = 59; // 最大值

  eepSavePage(page_alarmClockEdit, 0); // 保存现在的界面
  focusPosOld_save();                  // 保存上一个界面的焦点

  // 启用弹窗组
  lv_indev_set_group(indev, group_mbox1);
  page.keyMode == KEY_MODE_PN;

  // 创建容器盒子
  box_share[0] = lv_obj_create(lv_layer_top());      // lv_screen_active() lv_layer_top() lv_layer_sys()
  lv_obj_set_scrollbar_mode(box_share[0], LV_SCROLLBAR_MODE_OFF);
  lv_obj_add_style(box_share[0], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box_share[0], &style_squareShape, LV_STATE_DEFAULT); // 添加方向样式
  lv_obj_set_style_bg_opa(box_share[0], LV_OPA_0, 0);

  // 创建实际盒子 即 外边框
  lv_obj_t *box = lv_obj_create(box_share[0]);
  lv_obj_set_scrollbar_mode(box, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(box, 72, 120);
  lv_obj_align(box, LV_ALIGN_CENTER, 0, 0); // 设置对齐方式
  // 删除滚动条样式以获得干净的开始
  // lv_obj_remove_style(box, NULL, LV_PART_SCROLLBAR | LV_STATE_ANY);
  lv_obj_add_style(box, &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
  lv_obj_set_style_pad_top(box, 6, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(box, 6, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(box, 12, 0);                  // 设置圆角
  lv_obj_set_style_border_width(box, 2, 0);             // 设置边框宽度
  lv_obj_set_style_border_color(box, MY_COLOR_CYAN, 0); // 设置边框颜色
  // lv_obj_set_style_bg_opa(box, LV_OPA_0, 0);

  // 创建内边框
  lv_obj_t *innerBorder = lv_obj_create(box_share[0]);
  lv_obj_set_size(innerBorder, 68, 116);
  lv_obj_align(innerBorder, LV_ALIGN_CENTER, 0, 0);             // 设置对齐方式
  lv_obj_add_style(innerBorder, &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
  lv_obj_set_style_pad_top(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(innerBorder, 10, 0);                     // 设置圆角
  lv_obj_set_style_border_width(innerBorder, 1, 0);                // 设置边框宽度
  lv_obj_set_style_border_color(innerBorder, MY_COLOR_MAGENTA, 0); // 设置边框颜色
  lv_obj_set_style_bg_opa(innerBorder, LV_OPA_0, 0);

  // 打开记录文件，偏移至正确位置
  File file = LittleFS.open(alarmClockRecord);
  file.seek(focusPos_old[focusPos_old_index] * 14);
  //提取开关状态
  char c = file.read();
  if (c == '1') shareNum[0] = 1;
  else shareNum[0] = 0;
  // 提取星期
  for (uint8_t i = 1; i <= 7; i++)
  {
    char c = file.read();
    shareNum[i] = c - 48;
    //Serial.printf("shareNum[i]:%d\n", shareNum[i]);
  }
  // 提取时间
  String hour, minute;
  hour += char(file.read()); // 提取小时
  hour += char(file.read());
  minute += char(file.read()); // 提取分钟
  minute += char(file.read());
  shareNum[8] = atoi(hour.c_str());
  shareNum[9] = atoi(minute.c_str());
  file.close();
  lv_obj_t *label_sw;
  lv_obj_t *label_week[7];
  lv_obj_t *label_hour;
  lv_obj_t *label_minute;
  lv_obj_t *label_exit;
  // 开启/关闭
  label_sw = lv_label_create(box);      // 创建标签
  lv_obj_align(label_sw, LV_ALIGN_CENTER, 0, -46); // 对齐方式
  String str = F("已开启");
  if (shareNum[0] == 0) str = F("已关闭");
  lv_label_set_text(label_sw, str.c_str()); // 标签文本
  lv_obj_set_style_text_color(label_sw, MY_COLOR_BLACK, 0);  // 字体颜色
  lv_obj_add_flag(label_sw, LV_OBJ_FLAG_SCROLLABLE);         // 使对象可滚动
  lv_obj_add_flag(label_sw, LV_OBJ_FLAG_SCROLL_ON_FOCUS);    // 自动滚动对象以使其在聚焦时可见
  // 星期
  int8_t x[7] = {-24, -8, +8, +24, -18, 0, +18};
  int8_t y[2] = {+35, +50};
  for (uint8_t i = 1; i <= 7; i++)
  {
    label_week[i - 1] = lv_label_create(box); // 创建标签
    if (i <= 4)
      lv_obj_align(label_week[i - 1], LV_ALIGN_CENTER, x[i - 1], y[0]);
    else
      lv_obj_align(label_week[i - 1], LV_ALIGN_CENTER, x[i - 1], y[1]);
    lv_label_set_text_fmt(label_week[i - 1], "%d", i); // 标签文本
    lv_obj_set_style_text_font(label_week[i - 1], &MiSans_Bold_14px, 0);
    if (shareNum[i] != 0)
      lv_obj_set_style_text_color(label_week[i - 1], MY_COLOR_RED, 0); // 字体颜色
    else
      lv_obj_set_style_text_color(label_week[i - 1], MY_COLOR_BLACK, 0); // 字体颜色

    // 添加按钮按下回调
    lv_obj_add_event_cb(label_week[i - 1], alarmClock_edit_seek_event, LV_EVENT_PRESSED, &num[i]);
  }

  // 小时
  label_hour = lv_label_create(box);          // 创建标签
  lv_obj_set_width(label_hour, 26);
  lv_obj_align(label_hour, LV_ALIGN_CENTER, -16, -4);  // 对齐方式
  lv_label_set_text_fmt(label_hour, "%s", hour); // 标签文本
  lv_obj_set_style_text_font(label_hour, &MiSans_Medium_16px, 0);
  // 添加按钮按下回调
  lv_obj_add_event_cb(label_hour, alarmClock_edit_time_event, LV_EVENT_KEY, &num[0]);
  
  // 分钟
  label_minute = lv_label_create(box); // 创建标签
  lv_obj_set_width(label_minute, 26);
  lv_obj_align(label_minute, LV_ALIGN_CENTER, +16, -4); // 对齐方式
  lv_label_set_text_fmt(label_minute, "%s", minute);    // 标签文本
  lv_obj_set_style_text_font(label_minute, &MiSans_Medium_16px, 0);
  // 添加按钮按下回调
  lv_obj_add_event_cb(label_minute, alarmClock_edit_time_event, LV_EVENT_KEY, &num[1]);
  
  // 时间
  lv_obj_t *label = lv_label_create(box);                // 创建标签
  lv_obj_align(label, LV_ALIGN_CENTER, 0, -23); // 对齐方式
  lv_label_set_text(label, "时间");             // 标签文本

  // 星期
  label = lv_label_create(box);                // 创建标签
  lv_obj_align(label, LV_ALIGN_CENTER, 0, +18); // 对齐方式
  lv_label_set_text(label, "星期");             // 标签文本

  // 冒号
  label = lv_label_create(box);                // 创建标签
  lv_obj_align(label, LV_ALIGN_CENTER, 0, -4); // 对齐方式
  lv_label_set_text(label, ":");             // 标签文本
  lv_obj_set_style_text_font(label, &MiSans_Medium_16px, 0);

  // 退出
  label_exit = lv_label_create(box);                 // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_CENTER, 0, 72);  // 对齐方式
  lv_label_set_text(label_exit, String("退出").c_str());             // 标签文本
  lv_obj_add_flag(label_exit, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  lv_obj_add_flag(label_exit, LV_OBJ_FLAG_CLICKABLE);       // 使对象可被输入设备点击
  lv_obj_add_flag(label_exit, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见

  // 创建线条
  static lv_point_precise_t line_points0[] = {{0, 0}, {55, 0}};
  // 创建线条
  lv_obj_t *line;
  line = lv_line_create(box);
  lv_line_set_points(line, line_points0, 2);
  lv_obj_center(line);
  lv_obj_align(line, LV_ALIGN_CENTER, 0, -35);
  lv_obj_set_style_line_width(line, 2, 0);
  lv_obj_set_style_line_color(line, MY_COLOR_MAGENTA, 0);
  line = lv_line_create(box);
  lv_line_set_points(line, line_points0, 2);
  lv_obj_center(line);
  lv_obj_align(line, LV_ALIGN_CENTER, 0, +5);
  lv_obj_set_style_line_width(line, 2, 0);
  lv_obj_set_style_line_color(line, MY_COLOR_MAGENTA, 0);
  line = lv_line_create(box);
  lv_line_set_points(line, line_points0, 2);
  lv_obj_center(line);
  lv_obj_align(line, LV_ALIGN_CENTER, 0, +60);
  lv_obj_set_style_line_width(line, 2, 0);
  lv_obj_set_style_line_color(line, MY_COLOR_MAGENTA, 0);

  lv_obj_t *zj[] = {
      label_sw,
      label_hour,
      label_minute,
      label_week[0],
      label_week[1],
      label_week[2],
      label_week[3],
      label_week[4],
      label_week[5],
      label_week[6],
      label_exit,
  };
  for (uint8_t i = 0; i < 11; i++)
  {
    /*lv_obj_set_style_outline_width(zj[i], 2, LV_STATE_FOCUS_KEY);                // 聚焦框的宽度
    lv_obj_set_style_outline_pad(zj[i], 0, LV_STATE_FOCUS_KEY);                  // 聚焦框的间隙
    lv_obj_set_style_outline_opa(zj[i], LV_OPA_100, LV_STATE_FOCUS_KEY);         // 聚焦框的不透明度
    lv_obj_set_style_outline_width(zj[i], 0, LV_STATE_DEFAULT);                  // 失焦时的宽度
    lv_obj_set_style_outline_color(zj[i], MY_COLOR_MAGENTA, LV_STATE_FOCUS_KEY); // 聚焦框颜色*/
    lv_obj_set_style_outline_width(zj[i], 0, LV_STATE_DEFAULT);   // 失焦时的宽度
    lv_obj_set_style_outline_width(zj[i], 0, LV_STATE_FOCUS_KEY); // 聚焦时的宽度
    lv_obj_set_style_bg_opa(zj[i], LV_OPA_100, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_bg_color(zj[i], MY_COLOR_CYAN, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_radius(zj[i], 4, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_pad_top(zj[i], -5, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(zj[i], -5, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(zj[i], 3, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(zj[i], 3, LV_STATE_DEFAULT);
    // 设置文本长字符模式
    lv_label_set_long_mode(zj[i], LV_LABEL_LONG_SCROLL); 
    // 将对象邦定到组
    lv_group_add_obj(group_mbox1, zj[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(zj[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
  }

  // 添加按钮按下回调
  lv_obj_add_event_cb(label_exit, alarmClock_edit_exit0, LV_EVENT_PRESSED, NULL);
  // 添加按钮按下回调
  lv_obj_add_event_cb(label_sw, alarmClock_edit_sw_event, LV_EVENT_PRESSED, NULL);

  // 添加进入动画
  lv_anim_t a;
  lv_anim_init(&a);                                    // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                   // 设置需要动画的对象
  lv_anim_set_values(&a, 36, 0);                       // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);          // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_bounce);        // 设置变化特效
  // lv_anim_set_completed_cb(&a, NULL); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}

//****** 蜂鸣器设置界面
void display_buzzerSet_event0(lv_event_t *e) // 当背景对象被聚焦时，弹出弹窗或定位到第1个对象
{
  if (page.firstEvent) // 首次进入该事件时 手动定位到第一个焦点
  {
    // Serial.println("下一个焦点");
    page.firstEvent = 0;
    lv_obj_t *child = lv_obj_get_child(page.p[page.index], 0);
    lv_group_focus_obj(child);
    LV_UNUSED(child);
  }
}
void display_buzzerSet_event1(lv_event_t *e) // 切换标签编辑模式的事件
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  // Serial.printf("code:%d\n",code);

  if (code == LV_EVENT_PRESSED) // 切换编辑状态
  {
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;
    if (page.keyMode == KEY_MODE_PN) // 进入编辑模式，修改成白底黑字
    {
      page.keyMode = KEY_MODE_RL;
      lv_obj_set_style_bg_color(obj, MY_COLOR_BLACK, LV_STATE_DEFAULT); // 设置背景颜色
      lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
    else // 退出编辑模式，恢复原来的样式
    {
      eepSaveState = 1;
      page.keyMode = KEY_MODE_PN;
      lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                             MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
      lv_obj_set_style_bg_color(obj, color[i % 6], LV_STATE_DEFAULT); // 设置背景颜色
      if ((i % 6) < 3)
        lv_obj_set_style_text_color(child, MY_COLOR_BLACK, LV_STATE_DEFAULT);
      else
        lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
  }
  else if (code == LV_EVENT_KEY) // 数值加减
  {
    uint8_t key = lv_indev_get_key(lv_indev_active());
    if (key == LV_KEY_ENTER) return;
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;  
    // 数值加减
    if (key == LV_KEY_LEFT) // 减
    {
      if (*sm0.num_u8[i] == sm0.min[i])
        *sm0.num_u8[i] = sm0.max[i];
      else
        *sm0.num_u8[i] -= sm0.step[i];
    }
    else if (key == LV_KEY_RIGHT) // 加
    {
      if (*sm0.num_u8[i] == sm0.max[i])
        *sm0.num_u8[i] = sm0.min[i];
      else
        *sm0.num_u8[i] += sm0.step[i];
    }

    String text = String(lv_label_get_text(child));
    int pos = text.indexOf(":");
    text = text.substring(0, pos + 1);
    text += String(*sm0.num_u8[i]);
    // Serial.printf("text:%s", text);
    lv_label_set_text(child, text.c_str()); // 标签文本
    buzzer_setNote();                       // 应用生效
  }

  LV_UNUSED(obj);
  LV_UNUSED(child);
}
void display_buzzerSet_event2(lv_event_t *e) // 蜂鸣器使能切换
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  eep_buzzerEn = !eep_buzzerEn;
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  if (eep_buzzerEn)
  {
    bitWrite(backgroundTask, BGT_BUZZER, 1);
    lv_label_set_text(child, String("已启用").c_str());
  }
  else
  {
    bitWrite(backgroundTask, BGT_BUZZER, 0);
    lv_label_set_text(child, String("已停用").c_str());
  }
  eepSaveState = 1;
}
void display_buzzerSet_init()
{
  eepSavePage(page_buzzerSet, 0);

  uint8_t j = 0;
  sm0.num_u8[j++] = &eep_buzzerNote;   // 音符
  sm0.num_u8[j++] = &eep_buzzerOctave; // 音程
  sm0.num_u8[j++] = &eep_buzzerVolume; // 音量
  j = 0;
  sm0.step[j++] = 1; // 加减的步进值
  sm0.step[j++] = 1;
  sm0.step[j++] = 1;
  j = 0;
  sm0.min[j++] = 0; // 最小值
  sm0.min[j++] = 0;
  sm0.min[j++] = 1;
  j = 0;
  sm0.max[j++] = 11; // 最大值
  sm0.max[j++] = 8;
  sm0.max[j++] = 5;

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 3, LV_STATE_DEFAULT);

  String obj_name[3];
  uint8_t count = 0;
  obj_name[count++] = F("音符:%d");
  obj_name[count++] = F("音程:%d");
  obj_name[count++] = F("音量:%d"); 
  lv_obj_t *but[3];
  lv_obj_t *label[3];

  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};

  uint16_t timeArray[3];
  for (uint8_t i = 0; i < 3; i++)
    timeArray[i] = *sm0.num_u8[i];

  for (uint8_t i = 0; i < 3; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[index]);
    lv_obj_set_size(but[i], 72, 20);                                            // 设置大小
    lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 28);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
    
    // 标签对象
    label[i] = lv_label_create(but[i]);                                 // 创建标签
    lv_obj_align(label[i], LV_ALIGN_LEFT_MID, 5, 0);                    // 居中对齐
    lv_label_set_text_fmt(label[i], obj_name[i].c_str(), timeArray[i]); // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);
    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);

    // 按钮触发功能
    lv_obj_add_event_cb(but[i], display_buzzerSet_event1, LV_EVENT_PRESSED, &num[i]); // 切换编辑状态
    lv_obj_add_event_cb(but[i], display_buzzerSet_event1, LV_EVENT_KEY, &num[i]);     // 编辑状态下的数值加减
  }

  lv_obj_t *but1 = lv_button_create(page.p[index]);
  lv_obj_set_size(but1, 72, 20);                                               // 设置大小
  lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 3 * 28);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_BLUE, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  lv_obj_t *label1 = lv_label_create(but1);                                    // 创建标签
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);                                 // 居中对齐
  if (eep_buzzerEn)
    lv_label_set_text(label1, String("已启用").c_str()); // 标签文本
  else
    lv_label_set_text(label1, String("已停用").c_str());                                       // 标签文本 
  lv_obj_add_event_cb(but1, display_buzzerSet_event2, LV_EVENT_PRESSED, NULL); // 使能切换
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);   // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);

  but1 = lv_button_create(page.p[index]);
  lv_obj_set_size(but1, 72, 25);                                               // 设置大小
  lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 4 * 28);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_MAGENTA, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  label1 = lv_label_create(but1);                                             // 创建标签
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);                                 // 居中对齐
  lv_label_set_text(label1, "退出");                                           // 标签文本
  lv_obj_add_event_cb(but1, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);   // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);
}

//****** 文件管理器界面
struct fileManager_struct // 文件管理器结构体
{
 // bool ergodic = 1; // 遍历全部 1需要初始化 0不需要
  String dir[5];        // 显示的文件夹名称
  String file[5];       // 显示的文件名称
  // size_t size[5];               // 文件管理器 显示的文件文件大小
  String path = "/";            // 要访问的路径
  uint8_t level = 0;            // 层级
  uint16_t dirCount = 0;        // 当前文件夹计数
  uint16_t fileCount = 0;       // 文件计数
  uint16_t total = 0;           // 文件和文件的计数
  uint8_t page = 1;             // 当前的位置,一页5个文件
  uint8_t indexRecord = 0;      // 记录的索引
  uint8_t pageRecord[10] = {1}; // 每一层的当前位置记录
  uint32_t remainingBytes;      // 剩余字节
  String filePath;              // 选中文件的完整路径
  uint8_t type = 0;             // 选中文件的类型
};
fileManager_struct fm;

//****** 文件管理器初始化
void fileManagerInit(bool ergodic)
{
   // 耗时30ms，应考虑放到后台任务执行
   
  // 文件夹和文件的索引
  uint16_t dirIndex = 0;
  uint16_t fileIndex = 0;
  int16_t dirIndex1 = 0;
  int16_t fileIndex1 = 0;
  // 可以加入数组的开始值
  uint16_t startPos = (fm.page - 1) * 5;
  //Serial.printf("startPos:%d\n", startPos);
  //Serial.printf("ergodic:%d\n", ergodic);
  // 计数清零
  if (ergodic)
  {
    fm.dirCount = 0;
    fm.fileCount = 0;
  }
  for (uint8_t i = 0; i < 5; i++)
  {
    fm.dir[i].clear();
    fm.file[i].clear();
  }
  // 统计文件和文件夹
  File root, file;
  root = LittleFS.open(fm.path,"r"); // 建立"目录"对象,默认根目录
  file = root.openNextFile();   // 检查该路径是否有文件或文件夹
  if(ergodic) // 需遍历本层的全部文件夹&文件
  {
    while (file)
    {
      if (file.isDirectory()) fm.dirCount++;  // 本层 文件夹累积
      else                    fm.fileCount++; // 本层 文件累积
      file = root.openNextFile(); // 检查该路径是否有文件或文件夹
    }
    // 结束时重新开始
    root.rewindDirectory();     // 重新启动指向目录第一个文件的指针
    file = root.openNextFile(); // 检查该路径是否有文件或文件夹
  }

  while (file)
  {
    String name = file.name();
    if (file.isDirectory()) // 收集文件夹 并 排除系统卷信息
    {
      int16_t startSeekPos = startPos;
      if (dirIndex1 >= startSeekPos)
      {
        if (dirIndex < 5) fm.dir[dirIndex++] = name;
      }
      else dirIndex1++;
    }
    else // 收集文件
    {
      // 需遍历全部
      int16_t startSeekPos = startPos - fm.dirCount; // 开始寻找的位置
      if (fileIndex1 >= startSeekPos)
      {
        if (fileIndex < 5) fm.file[fileIndex++] = name;
      }
      else fileIndex1++;
    }

    // 退出 加一起大于等于5 && 本次计算的文件夹数量和真实文件夹数量一样
    if ((dirIndex + fileIndex >= 5) && fm.dirCount == dirIndex)
      break;

    file = root.openNextFile(); // 检查该路径是否有文件或文件夹
  }
  file.close();
  root.close();

  /*Serial.printf("fm.dirCount:%d\n", fm.dirCount);
  Serial.printf("fm.fileCount:%d\n", fm.fileCount);
  Serial.printf("fileIndex:%d\n", fileIndex);
  Serial.printf("dirIndex:%d\n", dirIndex);
  Serial.printf("fileIndex1:%d\n", fileIndex1);
  Serial.printf("dirIndex1:%d\n", dirIndex1);
  Serial.printf("fm.page:%d\n", fm.page);
  for (uint8_t i = 0; i < 5; i++)
  {
    Serial.printf("fm.dir[%d]:%s\n", i, fm.dir[i].c_str());
    Serial.printf("fm.file[%d]:%s\n", i, fm.file[i].c_str());
    // Serial.print("fm.file[" + String(i) + "]:");Serial.println(fm.file[i]);
  }
  Serial.println();*/
}
void fileManagerSavePage() // 保存当前的层的页数
{
  //Serial.printf("fm.pageRecord1[%d]:%d\n", fm.indexRecord, fm.pageRecord[fm.indexRecord]);
  fm.pageRecord[fm.indexRecord] = fm.page;
  fm.indexRecord++;
  fm.page = fm.pageRecord[fm.indexRecord];
  //Serial.printf("fm.pageRecord11[%d]:%d\n", fm.indexRecord, fm.pageRecord[fm.indexRecord]);
  //Serial.println();
}
void fileManagerGetPage()  // 获取上一层的页数
{ 
  fm.pageRecord[fm.indexRecord] = fm.page; // 保存当前的层的页数
  //Serial.printf("fm.pageRecord2[%d]:%d\n", fm.indexRecord, fm.pageRecord[fm.indexRecord]);
  fm.indexRecord--;
  //Serial.printf("fm.pageRecord22[%d]:%d\n", fm.indexRecord, fm.pageRecord[fm.indexRecord]);
  fm.page = fm.pageRecord[fm.indexRecord];
  //Serial.println();
}

void fileExplorer_label_head_event(lv_event_t *e)    // 文件管理器返回事件
{
  // 退出至设置菜单
  if(fm.path == "/") 
  {
    exitToMainSet();                // 退出至设置菜单
    lv_obj_delete_async(lv_obj_xk); // 删除选框
  }
  // 返回上一层
  else 
  {
    // 移除最后一个斜杠
    uint8_t pos = fm.path.lastIndexOf("/");
    if (pos == 0) pos = 1;
    fm.path = fm.path.substring(0, pos);

    fileManagerGetPage(); // 获取上一层的页数
    fileManagerInit(1);
    display_fileExplorer_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, 500, 0, true);
    onGlobalJitter(400);  // 打开全局抖动
    focusPosOld_return(); // 回到刚才的焦点
  }
}
void fileExplorer_label_bottom_event(lv_event_t *e)  // 文件管理器上下页
{
  //lv_obj_t *obj = lv_event_get_target_obj(e);
  //lv_event_code_t code = lv_event_get_code(e);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  if (i == 0) // 上一页
  {
    if (fm.page > 1) fm.page--;
    else return;
  }
  else if (i == 1)  // 下一页
  {
    uint16_t maxPage = ceil(((float)fm.fileCount + (float)fm.dirCount) / 5.0);
    //Serial.printf("fm.dirCount:%d\n",fm.dirCount);
    //Serial.printf("fm.fileCount:%d\n",fm.fileCount);
    //Serial.printf("maxPage:%d\n",maxPage);
    if (fm.page < maxPage) fm.page++;
    else return;
  }

  fileManagerInit(0);
  display_fileExplorer_init();
  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, 200, 0, true);
  onGlobalJitter(150); // 打开全局抖动

  // 设置焦点
  if (i == 0) // 上一页
  {
    int16_t num = lv_obj_get_child_count(page.p[page.index]);
    lv_obj_t *child = lv_obj_get_child(page.p[page.index], num - 3);
    lv_group_focus_obj(child);
  }
  else if (i == 1)  // 下一页
  {
    int16_t num = lv_obj_get_child_count(page.p[page.index]);
    lv_obj_t *child = lv_obj_get_child(page.p[page.index], num - 2);
    lv_group_focus_obj(child);
  }
}
void fileExplorer_label_PRESSED_event(lv_event_t *e) // 文件管理器文件或文件夹点击
{
  lv_obj_t *obj = lv_event_get_target_obj(e);
  //lv_event_code_t code = lv_event_get_code(e);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  String str = lv_label_get_text(obj);
  //Serial.print("str:"); Serial.println(str);
  // 进入文件夹
  if (i == 0)
  {
    fm.path += str;
    focusPosOld_save();    // 保存焦点
    fileManagerSavePage(); // 保存当前的层的页数
    // 进入下一层
    fileManagerInit(1);
    display_fileExplorer_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, 500, 0, true);
    onGlobalJitter(400); // 打开全局抖动
  }
  // 打开文件菜单
  else if (i == 1)
  {
    focusPosOld_save(); // 保存焦点
    display_fileExplorerMenu_init();
  }
}

void xk_move_anim_x(void *var, int32_t v)
{
  lv_obj_set_x((lv_obj_t *)var, v);
}
void xk_move_anim_y(void *var, int32_t v)
{
  lv_obj_set_y((lv_obj_t *)var, v);
}
void xk_move_anim_w(void *var, int32_t v)
{
  lv_obj_set_width((lv_obj_t *)var, v);
}
void xk_move_anim_h(void *var, int32_t v) 
{
  lv_obj_set_height((lv_obj_t *)var, v);
}
void fileExplorer_xk_anim_event(lv_event_t *e) // 移动选框动画
{
  buzzerSen(30);
  //Serial.printf("选框移动\n");

  if (lv_obj_is_valid(lv_obj_xk) == false)
  {
    Serial.printf("选框对象已删除\n");
    return;
  }
  lv_obj_t *obj = lv_event_get_target_obj(e);

  //lv_event_code_t code = lv_event_get_code(e);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  //Serial.printf("焦点:%d\n", lv_obj_get_index(obj));

  lv_obj_t *parent = lv_obj_get_parent(obj); // 获取父对象
  lv_obj_update_layout(parent);

  // 获取选框现在的参数
  int16_t x0 = lv_obj_get_x(lv_obj_xk);
  int16_t y0 = lv_obj_get_y(lv_obj_xk);
  int16_t w0 = lv_obj_get_width(lv_obj_xk);
  int16_t h0 = lv_obj_get_height(lv_obj_xk);

  int16_t x1;
  int16_t y1;
  int16_t w1;
  int16_t h1;

  // 获取目标的参数
  if (i == 0) // 适应字体长度的选框
  {
    x1 = lv_obj_get_x(obj) - 3;
    y1 = lv_obj_get_y(obj);
    w1 = lv_obj_get_width(obj) + 6;
    h1 = lv_obj_get_height(obj);
  }
  else if (i == 1) // 长选框
  {
    x1 = 0;
    y1 = lv_obj_get_y(obj) - 1;
    w1 = 144;
    h1 = lv_obj_get_height(obj) + 2;
  }

  //Serial.printf("i:%d\n", i);
  /*Serial.printf("x0:%d\n", x0);
  Serial.printf("y0:%d\n", y0);
  Serial.printf("w0:%d\n", w0);
  Serial.printf("h0:%d\n", h0);
  Serial.printf("x1:%d\n", x1);
  Serial.printf("y1:%d\n", y1);
  Serial.printf("w1:%d\n", w1);
  Serial.printf("h1:%d\n", h1);
  Serial.println();*/
  

  lv_anim_t a;
  lv_anim_init(&a);                             // 动画初始化
  lv_anim_set_var(&a, lv_obj_xk);               // 设置需要动画的对象
  lv_anim_set_values(&a, x0, x1);               // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, 350);                // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, xk_move_anim_x);      // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_bounce); // 设置变化特效
  // lv_anim_set_completed_cb(&a, label_y_up_anim_end_cb); // 设置动画完成时的函数调用
  lv_anim_start(&a);

  lv_anim_set_values(&a, y0, y1);          // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, 350);           // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, xk_move_anim_y); // 设置需要变化的值
  lv_anim_start(&a);

  lv_anim_set_values(&a, w0, w1);          // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, 350);           // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, xk_move_anim_w); // 设置需要变化的值
  lv_anim_start(&a);

  lv_anim_set_values(&a, h0, h1);          // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, 350);           // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, xk_move_anim_h); // 设置需要变化的值
  lv_anim_start(&a);
}

void set_style_outline(lv_obj_t *obj) // 设置聚焦样式
{
  /*lv_obj_set_style_outline_width(obj, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(obj, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(obj, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(obj, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(obj, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
*/

  lv_obj_set_style_outline_width(obj, 0, LV_STATE_DEFAULT);   // 失焦时的宽度
  lv_obj_set_style_outline_width(obj, 0, LV_STATE_FOCUS_KEY); // 聚焦时的宽度

  //lv_obj_set_style_bg_opa(obj, LV_OPA_100, LV_STATE_FOCUS_KEY);
  //lv_obj_set_style_bg_color(obj, MY_COLOR_CYAN, LV_STATE_FOCUS_KEY);
  //lv_obj_set_style_radius(obj, 4, LV_STATE_FOCUS_KEY);
  //lv_obj_set_style_pad_top(obj, 3, LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_bottom(obj, 3, LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_right(obj, 3, LV_STATE_DEFAULT);
  //lv_obj_set_style_pad_left(obj, 3, LV_STATE_DEFAULT);
}

void display_fileExplorer_init()
{
  eepSavePage(page_fileExplorer, 1);
  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 0, LV_STATE_DEFAULT);
  // lv_obj_set_style_transform_rotation 变换旋转

  // 创建选框
  lv_obj_xk = lv_obj_create(page.p[page.index]);
  lv_obj_set_scrollbar_mode(lv_obj_xk, LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(lv_obj_xk, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(lv_obj_xk, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_bg_opa(lv_obj_xk, LV_OPA_100, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(lv_obj_xk, MY_COLOR_CYAN, LV_STATE_DEFAULT);
  lv_obj_align(lv_obj_xk, LV_ALIGN_DEFAULT, 0, 0);
  lv_obj_set_size(lv_obj_xk, 72, 144);
  lv_obj_set_style_radius(lv_obj_xk, 4, 0); // 设置圆角

  //****** 头部返回图标和字
  lv_obj_t *label_head_icon = lv_label_create(page.p[page.index]);
  lv_obj_align(label_head_icon, LV_ALIGN_TOP_LEFT, 2, 0);
  lv_obj_set_style_text_color(label_head_icon, MY_COLOR_RED, 0);
  lv_label_set_text(label_head_icon, LV_SYMBOL_BACK);                                          // 显示返回图标
  lv_obj_add_flag(label_head_icon, LV_OBJ_FLAG_CLICKABLE);                                     // 使对象可被输入设备点击
  lv_group_add_obj(group_my, label_head_icon);                                                 // 添加到组
  set_style_outline(label_head_icon);                                                          // 设置聚焦样式
  lv_obj_add_event_cb(label_head_icon, fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[0]); // 聚焦移动选框
  lv_obj_add_event_cb(label_head_icon, fileExplorer_label_head_event, LV_EVENT_PRESSED, NULL); // 退出回调

  //****** 头部路径
  lv_obj_t *label_head_text = lv_label_create(page.p[page.index]);
  lv_obj_align(label_head_text, LV_ALIGN_TOP_LEFT, 22, 0);
  lv_obj_set_width(label_head_text, 51);
  lv_label_set_long_mode(label_head_text, LV_LABEL_LONG_SCROLL);
  lv_obj_set_style_text_color(label_head_text, MY_COLOR_BLUE, 0);
  lv_label_set_text_fmt(label_head_text, "%s", fm.path.c_str()); // 显示路径

  // 剩余字节 = 总大小 - 所有文件占用大小
  // int32_t syzj = LittleFS.totalBytes() - LittleFS.usedBytes();
  // String syzj_s = byteConversion(syzj);

  for (uint8_t i = 0, j = 0; i < 5; i++)
  {
    // 先显示文件夹
    if (fm.dir[i].length() > 1)
    {
      //显示图标
      lv_obj_t *label_file_icon = lv_label_create(page.p[page.index]);
      lv_obj_align(label_file_icon, LV_ALIGN_TOP_LEFT, 1, 19 + i * 22);
      lv_label_set_text(label_file_icon, LV_SYMBOL_DIRECTORY);

      //显示名称
      label_share[i] = lv_label_create(page.p[page.index]);
      lv_obj_align(label_share[i], LV_ALIGN_TOP_LEFT, 19, 19 + i * 22);
      lv_label_set_text_fmt(label_share[i], "%s", fm.dir[i].c_str());
      lv_obj_set_width(label_share[i], 51);
      lv_label_set_long_mode(label_share[i], LV_LABEL_LONG_SCROLL);
      // lv_obj_set_style_anim_duration(label_share[i], 3000, 0);
      lv_group_add_obj(group_my, label_share[i]); // 添加到组
      set_style_outline(label_share[i]);          // 设置聚焦样式
      lv_obj_add_event_cb(label_share[i], fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[1]); // 聚焦移动选框
      lv_obj_add_event_cb(label_share[i], fileExplorer_label_PRESSED_event, LV_EVENT_PRESSED, &num[0]);
    }
    else if(fm.file[j].length() > 1)
    {
      // 显示图标
      lv_obj_t *label_file_icon = lv_label_create(page.p[page.index]);
      lv_obj_align(label_file_icon, LV_ALIGN_TOP_LEFT, 1, 19 + i * 22);
      uint8_t type = fileFormat(fm.file[j]);
      if (type == FILE_JPG || type == FILE_BMP) // 图片
        lv_label_set_text(label_file_icon, LV_SYMBOL_IMAGE);
      else if (type == FILE_MID)  // 音频
        lv_label_set_text(label_file_icon, LV_SYMBOL_AUDIO);
      else if (type == FILE_TXT) // 文本
      {
        lv_obj_align(label_file_icon, LV_ALIGN_TOP_LEFT, 2, 19 + i * 22);
        lv_label_set_text(label_file_icon, LV_SYMBOL_BOOT);
      }
      else // 其他
      {
        lv_obj_align(label_file_icon, LV_ALIGN_TOP_LEFT, 3, 19 + i * 22);
        lv_label_set_text(label_file_icon, LV_SYMBOL_FILE);
      }

      // 显示名称
      label_share[i] = lv_label_create(page.p[page.index]);
      lv_obj_align(label_share[i], LV_ALIGN_TOP_LEFT, 19, 19 + i * 22);
      lv_label_set_text_fmt(label_share[i], "%s", fm.file[j].c_str());
      lv_obj_set_width(label_share[i], 51);
      lv_label_set_long_mode(label_share[i],LV_LABEL_LONG_SCROLL);
      // lv_obj_set_style_anim_duration(label_share[i], 3000, 0);
      lv_group_add_obj(group_my, label_share[i]); // 添加到组
      set_style_outline(label_share[i]);          // 设置聚焦样式
      lv_obj_add_event_cb(label_share[i], fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[1]); // 聚焦移动选框
      lv_obj_add_event_cb(label_share[i], fileExplorer_label_PRESSED_event, LV_EVENT_PRESSED, &num[1]);
      j++;
    }
  }

  //****** 显示底部
  lv_obj_t *label_bottom = lv_label_create(page.p[page.index]);
  lv_obj_set_style_text_color(label_bottom, MY_COLOR_RED, 0);
  lv_obj_align(label_bottom, LV_ALIGN_BOTTOM_LEFT, 2, 2);
  lv_label_set_text(label_bottom, LV_SYMBOL_LETF_TRI_ARR); // 显示左三角图标
  lv_obj_add_flag(label_bottom, LV_OBJ_FLAG_CLICKABLE);    // 使对象可被输入设备点击
  lv_group_add_obj(group_my, label_bottom);                // 添加到组
  set_style_outline(label_bottom);                         // 设置聚焦样式
  lv_obj_add_event_cb(label_bottom, fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[0]); // 聚焦移动选框
  lv_obj_add_event_cb(label_bottom, fileExplorer_label_bottom_event, LV_EVENT_PRESSED, &num[0]);

  label_bottom = lv_label_create(page.p[page.index]);
  lv_obj_set_style_text_color(label_bottom, MY_COLOR_RED, 0);
  lv_obj_align(label_bottom, LV_ALIGN_BOTTOM_RIGHT, -2, 2);
  lv_label_set_text(label_bottom, LV_SYMBOL_RIGHT_TRI_ARR); // 显示右三角图标
  lv_obj_add_flag(label_bottom, LV_OBJ_FLAG_CLICKABLE);     // 使对象可被输入设备点击
  lv_group_add_obj(group_my, label_bottom);                 // 添加到组
  set_style_outline(label_bottom);                          // 设置聚焦样式
  lv_obj_add_event_cb(label_bottom, fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[0]); // 退出回调
  lv_obj_add_event_cb(label_bottom, fileExplorer_label_bottom_event, LV_EVENT_PRESSED, &num[1]);

  //显示页数
  label_bottom = lv_label_create(page.p[page.index]);
  lv_obj_set_style_text_color(label_bottom, MY_COLOR_BLUE, 0);
  lv_obj_align(label_bottom, LV_ALIGN_BOTTOM_MID, 0, 2);
  uint16_t curPage = fm.page; // 当前页
  uint16_t maxPage = ceil(((float)fm.fileCount + (float)fm.dirCount) / 5.0);
  lv_label_set_text_fmt(label_bottom, "%d/%d", curPage, maxPage);

  // lv_obj_t *child = lv_obj_get_child(page.p[page.index], 0);
  lv_group_focus_obj(label_head_icon);
  // lv_obj_add_state(label_head_icon, LV_STATE_FOCUS_KEY);

  // lv_obj_remove_style(lv_obj_xk, NULL, LV_PART_MAIN);
  // lv_obj_add_event_cb(lv_obj_xk, fileExplorer_xk_event, LV_EVENT_PRESSED, NULL);
}

//****** 文件管理器的菜单
void open_picture_cb(lv_timer_t *time) // 打开图片
{
  display_picture_init(fm.filePath, 1, 1);
  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, GRADUAL_ANIM_TIME, 100, true);
}
void fileExplorerMenu_exit0_anim_end(lv_anim_t *a)  // 退出动画结束回调 
{
  lv_obj_set_parent(lv_obj_xk, page.p[page.index]); // 交换父对象
  lv_obj_move_to_index(lv_obj_xk, 0);               // 移至底层
  lv_obj_set_size(lv_obj_xk, 0, 0);                 // 设置大小

  lv_obj_delete(box_share[0]);         // 删除对象
  box_share[0] = NULL;                 // 对象地址清空
  lv_indev_set_group(indev, group_my); // 将组邦定到按键

  // 回到刚才的焦点
  focusPosOld_return();
  eepSavePage(page_fileExplorer, 1);
}
void fileExplorerMenu_midi_msgbox_cb(lv_event_t *e) // 文件管理器菜单退出midi播放
{
  stopMidi();
 my_msgbox_exit(0); // 退出弹窗
}
void fileExplorerMenu_exit(lv_event_t *e)           // 文件管理器菜单 退出回调
{
  // 检查是否在退出中 防止重复触发
  lv_anim_t *b = lv_anim_get(box_share[0], display_alarmClock_anim_cb);
  if (b != NULL) return;

  lv_anim_t a;
  lv_anim_init(&a);                                    // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                   // 设置需要动画的对象
  lv_anim_set_values(&a, 0, 72);                       // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);          // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_overshoot);     // 设置变化特效
  lv_anim_set_completed_cb(&a, fileExplorerMenu_exit0_anim_end); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void fileExplorerMenu_open(lv_event_t *e)           // 文件管理器菜单 打开回调
{
  if (fm.type == FILE_MID)
  {
    String name = removeDirectoryName(fm.filePath);
    my_msgbox_forceSend(F("MIDI"), name, 0, F("退出\n"), fileExplorerMenu_midi_msgbox_cb);
    //Serial.print("fm.filePath:");Serial.println(fm.filePath);
    stopMidi();
    //const char *p = fm.filePath.c_str();
    midi_rtos_init((void *)fm.filePath.c_str());
  }
  else if(fm.type == FILE_JPG)
  {
    fileExplorerMenu_exit(e);
    // 创建一个单次定时器
    lv_timer_t *timer = lv_timer_create(open_picture_cb, 550, NULL); // 0.55秒后打开图片
    lv_timer_set_repeat_count(timer, 1);
    lv_timer_set_auto_delete(timer, true);
    // String name = removeDirectoryName(fm.filePath);
    // my_msgbox_forceSend(F("未完成"), name, 0, F("退出\n"), msgbox_exit_cb);
  }
}
void fileExplorerMenu_set0(lv_event_t *e)           // 文件管理器菜单 设置为回调
{
  if (fm.type == FILE_MID)
  {
    eep_alarmSound = fm.filePath;
    //Serial.print("eep_alarmSound:");Serial.println(eep_alarmSound);
    eep.begin("eepUser", false);
    eep.putString("alarmSound", eep_alarmSound); // 自定义闹铃
    eep.end();
    my_msgbox_forceSend(F("设置成功"), LV_SYMBOL_LAUGH, 800);
  }
  else if(fm.type == FILE_JPG)
  {
    eep_batSleepPic = fm.filePath;
    //Serial.print("eep_batSleepPic:");Serial.println(eep_batSleepPic);
    eep.begin("eepUser", false);
    eep.putString("batSleepPic", eep_batSleepPic); // 自定义休眠图片
    eep.end();
    my_msgbox_forceSend(F("设置成功"), LV_SYMBOL_LAUGH, 800);
  }
}
void fileExplorerMenu_set1(lv_event_t *e)           // 文件管理器菜单 设置为回调
{
    eep_sleepPic = fm.filePath;
    //Serial.print("eep_sleepPic:");Serial.println(eep_sleepPic);
    eep.begin("eepUser", false);
    eep.putString("sleepPic", eep_sleepPic); // 自定义休眠图片
    eep.end();
    my_msgbox_forceSend(F("设置成功"), LV_SYMBOL_LAUGH, 800);
}
void fileExplorerMenu_anim_cb0(lv_anim_t *a)        // 进入动画结束回调
{
  lv_obj_t *child0 = lv_obj_get_child(box_share[0], 0); //box对象
  lv_obj_t *child1 = lv_obj_get_child(child0, 0);//打开按钮对象

  lv_obj_set_parent(lv_obj_xk, child0); // 交换父对象
  lv_obj_move_to_index(lv_obj_xk, 0);   // 移至底层
  lv_obj_set_size(lv_obj_xk, 0, 0); 

  lv_group_focus_obj(child1);//聚焦到打开按钮
  // lv_obj_add_state(label_head_icon, LV_STATE_FOCUS_KEY);
}
void display_fileExplorerMenu_init()
{
  LV_FONT_DECLARE(ArialRoundedMTBold_14px);

  eepSavePage(page_fileExplorerMenu, 0); // 保存现在的界面

  int8_t focusPos = -1; 
  String size;  // 文件大小
  uint8_t dirNum = 0; // 文件夹数量

  // 获取上一个焦点
  lv_obj_t *focused_obj = lv_group_get_focused(group_my);
  if (focused_obj != NULL)
    focusPos = lv_obj_get_index(focused_obj);
    
  //Serial.printf("focusPos:%d\n", focusPos);

  // 计算有几个文件夹
  for (uint8_t i = 0; i < 5; i++)
    if (fm.dir[i].length() > 1)
      dirNum++;

  // 拼装文件的路径
  uint8_t filePos = focusPos / 2 - 2 - dirNum; // 4、8、6、12、10换算成01234
  if (fm.path == "/")
    fm.filePath = fm.path + fm.file[filePos];
  else
    fm.filePath = fm.path + "/" + fm.file[filePos];

  //Serial.printf("dirNum:%d\n", dirNum);
  //Serial.printf("filePos:%d\n", filePos);

  // 获取文件的大小和类型
  File file = LittleFS.open(fm.filePath);
  size = byteConversion(file.size());
  fm.type = fileFormat(fm.file[filePos]);

  // 启用弹窗组
  lv_indev_set_group(indev, group_mbox1);
  page.keyMode == KEY_MODE_PN;

  // 创建容器盒子
  box_share[0] = lv_obj_create(lv_screen_active()); // lv_screen_active() lv_layer_top() lv_layer_sys()
  lv_obj_align(box_share[0], LV_ALIGN_CENTER, 0, 0); // 设置对齐方式
  lv_obj_set_scrollbar_mode(box_share[0], LV_SCROLLBAR_MODE_OFF);
  lv_obj_add_style(box_share[0], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box_share[0], &style_squareShape, LV_STATE_DEFAULT); // 添加方向样式
  lv_obj_set_style_bg_opa(box_share[0], LV_OPA_0, 0);

  uint16_t box_h = 90;
  // 创建实际盒子 即 外边框
  lv_obj_t *box = lv_obj_create(box_share[0]);
  lv_obj_set_scrollbar_mode(box, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(box, 72, box_h);
  lv_obj_align(box, LV_ALIGN_CENTER, 0, 0); // 设置对齐方式
  // 删除滚动条样式以获得干净的开始
  // lv_obj_remove_style(box, NULL, LV_PART_SCROLLBAR | LV_STATE_ANY);
  lv_obj_add_style(box, &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
  lv_obj_set_style_pad_top(box, 6, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(box, 6, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(box, 7, 0);                  // 设置圆角
  lv_obj_set_style_border_width(box, 2, 0);             // 设置边框宽度
  lv_obj_set_style_border_color(box, MY_COLOR_CYAN, 0); // 设置边框颜色
  // lv_obj_set_style_bg_opa(box, LV_OPA_0, 0);

  // 创建内边框
  lv_obj_t *innerBorder = lv_obj_create(box_share[0]);
  lv_obj_set_size(innerBorder, 68, box_h - 4); 
  lv_obj_align(innerBorder, LV_ALIGN_CENTER, 0, 0);             // 设置对齐方式
  lv_obj_add_style(innerBorder, &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
  lv_obj_set_style_pad_top(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(innerBorder, 5, 0);                     // 设置圆角
  lv_obj_set_style_border_width(innerBorder, 1, 0);                // 设置边框宽度
  lv_obj_set_style_border_color(innerBorder, MY_COLOR_MAGENTA, 0); // 设置边框颜色
  lv_obj_set_style_bg_opa(innerBorder, LV_OPA_0, 0);

  //lv_obj_set_parent(lv_obj_xk, box);
  //lv_obj_set_size(lv_obj_xk, 0, 0);

  /*lv_obj_delete(lv_obj_xk);
  lv_obj_xk = lv_obj_create(box);
  lv_obj_set_scrollbar_mode(lv_obj_xk, LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(lv_obj_xk, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(lv_obj_xk, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_bg_opa(lv_obj_xk, LV_OPA_100, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(lv_obj_xk, MY_COLOR_CYAN, LV_STATE_DEFAULT);
  lv_obj_align(lv_obj_xk, LV_ALIGN_DEFAULT, 0, 0);
  lv_obj_set_size(lv_obj_xk, 0, 0);*/

  int16_t label_x = -3;
  lv_obj_t *label_open;
  lv_obj_t *label_set0;
  lv_obj_t *label_size;
  lv_obj_t *label_exit;
  lv_obj_t *opt[10];
  uint8_t optPos = 0;
  // 开启/关闭
  label_open = lv_label_create(box);                      // 创建标签
  lv_obj_align(label_open, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
  lv_label_set_text(label_open, String("打开").c_str());  // 标签文本
  // lv_obj_set_style_text_color(label_sw, MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_add_flag(label_open, LV_OBJ_FLAG_CLICKABLE);       // 使对象可被输入设备点击
  lv_obj_add_flag(label_open, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  lv_obj_add_flag(label_open, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见
  opt[optPos++] = label_open;// 添加进数组

  // 设置为？
  String str;
  if      (fm.type == FILE_MID) str = F("设为闹铃");
  else if (fm.type == FILE_JPG) str = F("设为低电量壁纸");
  if (str.length() > 1)
  {
    label_x += 21;
    label_set0 = lv_label_create(box); // 创建标签
    uint16_t text_width = lv_text_get_width(str.c_str(), str.length(), lv_obj_get_style_text_font(label_set0, 0), 0);
    if (text_width >= 66)
      lv_obj_set_width(label_set0, 66);                     // 设置宽度
    lv_obj_align(label_set0, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
    lv_label_set_text(label_set0, str.c_str());             // 标签文本
    lv_obj_add_flag(label_set0, LV_OBJ_FLAG_CLICKABLE);     // 使对象可被输入设备点击
    opt[optPos++] = label_set0;                             // 添加进数组

    // 设置回调
    lv_obj_add_event_cb(label_set0, fileExplorerMenu_set0, LV_EVENT_PRESSED, NULL);
    // lv_obj_add_flag(label_set0, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
    // lv_obj_add_flag(label_set0, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见
  }
  // 设置为？
  String str1;
  if (fm.type == FILE_JPG) str1 = F("设为休眠壁纸");
  if (str1.length() > 1)
  {
    label_x += 21;
    label_set0 = lv_label_create(box); // 创建标签
    uint16_t text_width = lv_text_get_width(str1.c_str(), str1.length(), lv_obj_get_style_text_font(label_set0, 0), 0);
    if (text_width >= 66)
      lv_obj_set_width(label_set0, 66);                     // 设置宽度
    lv_obj_align(label_set0, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
    lv_label_set_text(label_set0, str1.c_str());             // 标签文本
    lv_obj_add_flag(label_set0, LV_OBJ_FLAG_CLICKABLE);     // 使对象可被输入设备点击
    opt[optPos++] = label_set0;                             // 添加进数组

    // 设置回调
    lv_obj_add_event_cb(label_set0, fileExplorerMenu_set1, LV_EVENT_PRESSED, NULL);
    // lv_obj_add_flag(label_set0, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
    // lv_obj_add_flag(label_set0, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见
  }

  //lv_obj_update_layout(box_share[0]);
  // 退出
  label_x += 21;
  label_exit = lv_label_create(box);                      // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
  lv_label_set_text(label_exit, String("返回").c_str());  // 标签文本
  lv_obj_add_flag(label_exit, LV_OBJ_FLAG_CLICKABLE);     // 使对象可被输入设备点击
  // lv_obj_add_flag(label_exit, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  // lv_obj_add_flag(label_exit, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见
  opt[optPos++] = label_exit; // 添加进数组

  // 大小
  label_size = lv_label_create(box);                        // 创建标签
  lv_obj_align(label_size, LV_ALIGN_BOTTOM_MID, 0, 5);      // 对齐方式
  lv_label_set_text(label_size, size.c_str());              // 标签文本
  lv_obj_set_style_text_font(label_size, &ArialRoundedMTBold_14px, 0);
  lv_obj_add_flag(label_size, LV_OBJ_FLAG_CLICKABLE);       // 使对象可被输入设备点击
  //lv_obj_add_flag(label_size, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  //lv_obj_add_flag(label_size, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见

  // 批量设置
  for (uint8_t i = 0; i < optPos; i++)
  {
    set_style_outline(opt[i]);
    // 设置文本长字符模式
    lv_label_set_long_mode(opt[i], LV_LABEL_LONG_SCROLL); 
    // 将对象邦定到组
    lv_group_add_obj(group_mbox1, opt[i]);
    // 添加按钮聚焦动画
    //lv_obj_add_event_cb(opt[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    // 聚焦移动选框
    lv_obj_add_event_cb(opt[i], fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[0]);      
  }

  // 重新设置盒子高度
  box_h = box_h + (optPos - 3) * 21;
  lv_obj_set_size(box, 72, box_h);
  lv_obj_set_size(innerBorder, 68, box_h - 4);

  // 打开回调
  lv_obj_add_event_cb(label_open, fileExplorerMenu_open, LV_EVENT_PRESSED, NULL);
  // 退出回调
  lv_obj_add_event_cb(label_exit, fileExplorerMenu_exit, LV_EVENT_PRESSED, NULL);

  // 添加进入动画
  lv_anim_t a;
  lv_anim_init(&a);                                    // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                   // 设置需要动画的对象
  lv_anim_set_values(&a, 36, 0);                       // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);          // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb); // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);      // 设置变化特效
  lv_anim_set_completed_cb(&a, fileExplorerMenu_anim_cb0); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}

//****** 电量计界面
void updateBatSOC_timer_cb(lv_timer_t *time)
{
  if (eep_disPage != page_batSOC) return;

  lv_label_set_text(label_share[0], String(bat_vcc, 2).c_str());              // 标签文本
  lv_label_set_text(label_share[1], String(bat_soc, 2).c_str());              // 标签文本
  lv_label_set_text(label_share[2], String(lipo.getChangeRate(), 2).c_str()); // 标签文本
}
void display_batSOC_init()
{
  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(updateBatSOC_timer_cb, 1000, NULL); // 定时更新

  eepSavePage(page_batSOC, 1);

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 3, LV_STATE_DEFAULT);

  String obj_name[3];
  uint8_t count = 0;
  obj_name[count++] = F("电压");
  obj_name[count++] = F("电量");
  obj_name[count++] = F("趋势");

  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};

  get_bat_soc();
  float text_fmt[3] = {bat_vcc, bat_soc, lipo.getChangeRate()};

  for (uint8_t i = 0; i < 3; i++)
  {
    // 按钮对象
    lv_obj_t *but1 = lv_button_create(page.p[index]);
    lv_obj_set_size(but1, 72, 36);                                            // 设置大小
    lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, i * 40);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but1, color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条

    // 标签对象
    lv_obj_t *label1 = lv_label_create(but1);       // 创建标签
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, -9);  // 对齐方式
    lv_label_set_text(label1, obj_name[i].c_str()); // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label1, MY_COLOR_BLACK, 0);
    else
      lv_obj_set_style_text_color(label1, MY_COLOR_WHITE, 0);

    // 标签对象
    label_share[i] = lv_label_create(but1);               // 创建标签
    lv_obj_align(label_share[i], LV_ALIGN_CENTER, 0, 9); // 对齐方式
    // lv_label_set_text(label_share[i], "000");             // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label_share[i], MY_COLOR_BLACK, 0);
    else
      lv_obj_set_style_text_color(label_share[i], MY_COLOR_WHITE, 0);

    // 将对象邦定到组
    lv_group_add_obj(group_my, but1);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    //lv_obj_add_event_cb(but1, buttonFocus_anim_event1, LV_EVENT_FOCUSED, NULL);
  }

  lv_obj_t *but_exit = lv_button_create(page.p[index]);
  lv_obj_set_size(but_exit, 72, 20);                                             // 设置大小
  lv_obj_align(but_exit, LV_ALIGN_TOP_MID, 0, 3 * 40);                           // 设置对齐方式
  lv_obj_set_style_bg_color(but_exit, MY_COLOR_MAGENTA, LV_STATE_DEFAULT);       // 设置背景颜色
  lv_obj_add_style(but_exit, &style_shadow, LV_STATE_DEFAULT);                   // 设置阴影样式
  lv_obj_add_style(but_exit, &style_squareShape, LV_STATE_DEFAULT);              // 设置方型样式
  lv_obj_set_style_outline_width(but_exit, 2, LV_STATE_FOCUS_KEY);               // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_exit, 0, LV_STATE_FOCUS_KEY);                 // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_exit, LV_OPA_100, LV_STATE_FOCUS_KEY);        // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_exit, 0, LV_STATE_DEFAULT);                 // 失焦时的宽度
  lv_obj_set_style_outline_color(but_exit, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);  // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_exit, LV_SCROLLBAR_MODE_OFF);                    // 关闭滑动条

  // lv_obj_set_style_pad_top(but_exit, 0, 0);                                      // 设置边距
  // lv_obj_set_style_pad_bottom(but_exit, 0, 0);                                   // 设置边距
  // lv_obj_set_style_pad_left(but_exit, 20, 0);                                    // 设置边距
  // lv_obj_set_style_pad_right(but_exit, 20, 0);                                   // 设置边距

  lv_obj_add_event_cb(but_exit, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);

  lv_obj_t *label_exit = lv_label_create(but_exit);      // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_CENTER, 0, 0);       // 居中对齐
  lv_label_set_text(label_exit, String("退出").c_str()); // 标签文本

  lv_group_add_obj(group_my, but_exit);
}

//****** 定位信息界面
void locateInfo_timer_cb(lv_timer_t *time)
{
  if (eep_disPage != page_locateInfo) return;

  overTime = 0;

  uint8_t optMax = 10;
  String obj_name[optMax];
  uint8_t count = 0;
  String bz = F("%s"); //
  obj_name[count++] = F("状态:"); 
  obj_name[count++]; //时间
  obj_name[count++]; //日期
  obj_name[count++]; //纬度
  obj_name[count++]; //经度
  obj_name[count++] = F("速度:");
  obj_name[count++] = F("方位:");
  obj_name[count++] = F("卫星数:");
  obj_name[count++] = F("精度:");
  obj_name[count++] = F("海拔:");

  String text_fmt[optMax]; // 变量参数
  count = 0;               // 变量参数的位置

  int8_t dayAdd = 0;

  // 状态
  if(locateInfo.state) 
  {
    if(locateInfo.state[0] == 'A') text_fmt[count] = F("有效");
    else                           text_fmt[count] = F("无效");
  }

  // 时间
  count++;
  if (locateInfo.UTCTime)
  {
    uint8_t hours = (locateInfo.UTCTime[0] - '0') * 10 + (locateInfo.UTCTime[1] - '0');
    uint8_t minutes = (locateInfo.UTCTime[2] - '0') * 10 + (locateInfo.UTCTime[3] - '0');
    uint8_t seconds = (locateInfo.UTCTime[4] - '0') * 10 + (locateInfo.UTCTime[5] - '0');
    // 添加时区偏移
    hours += 8;
    // 校正时间
    if (hours >= 24)
    {
      hours -= 24;
      dayAdd++; 
    } 
    else if (hours < 0)
    {
      hours += 24;
      dayAdd--; 
    } 
    text_fmt[count] = String(hours) + "时" + String(minutes) + "分" + String(seconds) + "秒";
  }
  else obj_name[count] = F("时间");

  // 日期
  count++;
  if (locateInfo.UTCDate)
  {
    int8_t day = (locateInfo.UTCDate[0] - '0') * 10 + (locateInfo.UTCDate[1] - '0');
    int8_t month = (locateInfo.UTCDate[2] - '0') * 10 + (locateInfo.UTCDate[3] - '0');
    int16_t year = (locateInfo.UTCDate[4] - '0') * 10 + (locateInfo.UTCDate[5] - '0');
    dateAddSub(year, month, day, dayAdd);
    text_fmt[count] = String(year) + "年" + String(month) + "月" + String(day) + "日";
  }
  else obj_name[count] = F("日期");

  // 纬度
  count++;
  if (locateInfo.latitude)
  {
    // 解析纬度
    double latitude = atof(locateInfo.latitude.c_str());
    int lat_degrees = (int)(latitude / 100);
    double lat_minutes_full = latitude - (lat_degrees * 100);
    int lat_minutes = (int)lat_minutes_full;
    double lat_seconds = (lat_minutes_full - lat_minutes) * 60;
    text_fmt[count] = locateInfo.NS + String(lat_degrees) + "°" +
                      String(lat_minutes) + "\'" +
                      String(lat_seconds, 0) + "\"";
  }
  else obj_name[count] = F("latitude");

  // 经度
  count++;
  if (locateInfo.longitude) 
  {
    // 解析经度
    double latitude = atof(locateInfo.longitude.c_str());
    int lat_degrees = (int)(latitude / 100);
    double lat_minutes_full = latitude - (lat_degrees * 100);
    int lat_minutes = (int)lat_minutes_full;
    double lat_seconds = (lat_minutes_full - lat_minutes) * 60;
    text_fmt[count] = locateInfo.EW + String(lat_degrees) + "°" +
                      String(lat_minutes) + "\'" +
                      String(lat_seconds, 0) + "\"";
  }
  else obj_name[count] = F("longitude");

  // 地面速度 转换为公里
  count++;
  if (locateInfo.groundSpeed)  
  {
    //double speed = atof(locateInfo.groundSpeed.c_str()) * 1.85;
    //text_fmt[count] = String(speed, 1);
    text_fmt[count] = locateInfo.groundSpeed;
  }

  // 方位角
  count++;
  if(locateInfo.azimuthAngle) text_fmt[count] = locateInfo.azimuthAngle;

  // 卫星数量
  count++;
  if(locateInfo.satelliteNum) text_fmt[count] = locateInfo.satelliteNum;

  // 精度
  count++;
  if(locateInfo.HDOP) text_fmt[count] = locateInfo.HDOP;

  // 海拔
  count++;
  if(locateInfo.MSL) text_fmt[count] = locateInfo.MSL;

  for (uint8_t i = 0; i < optMax; i++)
  {
    obj_name[i] += bz;
    lv_label_set_text_fmt(label_share[i], obj_name[i].c_str(), text_fmt[i].c_str());
  }
}
void display_locateInfo_init()
{
  LV_FONT_DECLARE(MISans_Normal_12px);

  eepSavePage(page_locateInfo, 0);

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 3, LV_STATE_DEFAULT);

  uint8_t optMax = 10;
  String obj_name[optMax];
  uint8_t count = 0;
  /*obj_name[count++] = F("状态");
  obj_name[count++] = F("UTC时间");
  obj_name[count++] = F("UTC日期");
  obj_name[count++]= F("纬度");
  obj_name[count++]= F("经度");
  obj_name[count++] = F("速度");
  obj_name[count++] = F("方位角");
  obj_name[count++] = F("卫星数量");
  obj_name[count++] = F("水平精度");
  obj_name[count++] = F("平均海平面高度");
  */
  lv_obj_t *but[optMax];

  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                              MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};

  for (uint8_t i = 0; i < optMax; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[index]);
    lv_obj_set_size(but[i], 72, 20);                                            // 设置大小
    lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 24);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条

    // 标签对象
    label_share[i] = lv_label_create(but[i]); // 创建标签
    lv_label_set_long_mode(label_share[i], LV_LABEL_LONG_SCROLL_CIRCULAR); // 长字符模式
    lv_obj_set_style_anim_duration(label_share[i], 5000, 0);               // 滚动时间
    lv_obj_set_width(label_share[i], 72);                                  // 设置宽度
    lv_label_set_text(label_share[i], obj_name[i].c_str());                // 标签文本
    lv_obj_align(label_share[i], LV_ALIGN_LEFT_MID, 0, 0);                 // 对齐方式
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label_share[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label_share[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);
    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);

    // 按钮触发功能
    //lv_obj_add_event_cb(but[i], display_buzzerSet_event1, LV_EVENT_PRESSED, &num[i]); // 切换编辑状态
    //lv_obj_add_event_cb(but[i], display_buzzerSet_event1, LV_EVENT_KEY, &num[i]);     // 编辑状态下的数值加减
  }

  lv_obj_set_style_text_font(label_share[3], &MISans_Normal_12px, 0); //LV_FONT_DECLARE(MISans_Normal_12px);
  lv_obj_set_style_text_font(label_share[4], &MISans_Normal_12px, 0);

  lv_obj_t *but_exit = lv_button_create(page.p[index]);
  lv_obj_set_size(but_exit, 72, 20);                                               // 设置大小
  lv_obj_align(but_exit, LV_ALIGN_TOP_MID, 0, optMax * 24);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but_exit, MY_COLOR_MAGENTA, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but_exit, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but_exit, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but_exit, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_exit, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_exit, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_exit, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but_exit, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_exit, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  lv_obj_t *label_exit = lv_label_create(but_exit);                                // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_CENTER, 0, 0);                                 // 居中对齐
  lv_label_set_text(label_exit, String("退出").c_str());                           // 标签文本
  lv_obj_add_event_cb(but_exit, backPage_mainSet_event, LV_EVENT_PRESSED, NULL);   // 退出回调
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);   // 添加聚焦动画
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but_exit);

  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(locateInfo_timer_cb, 500, NULL); // 定时更新
}

//****** 码表界面
void display_stopwatch_event_msgbox(lv_event_t *e)  // 当屏幕被聚焦时，弹出退出弹窗
{
  uint8_t key = lv_indev_get_key(lv_indev_active());
  //Serial.printf("key:%d", key);
  if (key == LV_KEY_RIGHT || key == LV_KEY_LEFT)
  {
    my_msgbox_send(F("码表"), F("是否退出"), 0, F("退出\n返回\n"), backPage_mainSet);
  }
}
void stopwatch_timer_cb(lv_timer_t *time)
{
  if (eep_disPage != page_stopwatch) return;

  overTime = 0;
  int8_t dayAdd = 0;
  //static bool weekUpdate = 1;

  // 地面速度
  if (locateInfo.groundSpeed.length() > 1)
  {
    float speed = atof(locateInfo.groundSpeed.c_str());
    if (speed > 9)
    {
      lv_obj_align(label_share[0], LV_ALIGN_CENTER, 0, 3); // 对齐方式
      lv_label_set_text_fmt(label_share[0], "%d", speed);
      lv_obj_add_flag(label_share[8], LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
      uint16_t speed_i0 = speed; // 提取整数部分
      uint16_t speed_i1 = (speed - speed_i0) * 10; // 提取小数部分
      lv_obj_align(label_share[0], LV_ALIGN_CENTER, -19, 3); // 对齐方式
      lv_obj_remove_flag(label_share[8], LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text_fmt(label_share[0], "%d", speed_i0);
      lv_label_set_text_fmt(label_share[8], ".%d", speed_i1);
    }
  }

  // 卫星数量
  if (locateInfo.satelliteNum.length() > 1)
    lv_label_set_text(label_share[2], locateInfo.satelliteNum.c_str());

  // 精度
  if (locateInfo.HDOP.length() > 1)
    lv_label_set_text(label_share[3], locateInfo.HDOP.c_str());

  // 海拔
  if (locateInfo.MSL.length() > 1)
  {
    int16_t haiba = atoi(locateInfo.MSL.c_str());
    lv_label_set_text(label_share[4], String(haiba).c_str());
  }

  // 时间
  if (locateInfo.UTCTime.length() > 1)
  {
    uint8_t hours = (locateInfo.UTCTime[0] - '0') * 10 + (locateInfo.UTCTime[1] - '0');
    uint8_t minutes = (locateInfo.UTCTime[2] - '0') * 10 + (locateInfo.UTCTime[3] - '0');
    //uint8_t seconds = (locateInfo.UTCTime[4] - '0') * 10 + (locateInfo.UTCTime[5] - '0');
    // 添加时区偏移
    hours += 8;
    // 校正时间
    if (hours >= 24)
    {
      hours -= 24;
      dayAdd++; 
    } 
    else if (hours < 0)
    {
      hours += 24;
      dayAdd--; 
    } 
    String str = String(hours) + ":" + String(minutes);
    lv_label_set_text(label_share[5], str.c_str()); // 标签文本
  }

  // 星期
  //if (weekUpdate)
  //{`
    //weekUpdate = 0;
    clock_read();
    uint8_t week = curTime.dayOfWeek;
    if (week == 0) week = 7;
    String week_s = "W" + String(week);
    lv_label_set_text(label_share[6], week_s.c_str()); // 标签文本
  //}
  // 日期
  if (locateInfo.UTCDate.length() > 1)
  {
    int8_t day = (locateInfo.UTCDate[0] - '0') * 10 + (locateInfo.UTCDate[1] - '0');
    int8_t month = (locateInfo.UTCDate[2] - '0') * 10 + (locateInfo.UTCDate[3] - '0');
    int16_t year = (locateInfo.UTCDate[4] - '0') * 10 + (locateInfo.UTCDate[5] - '0');
    dateAddSub(year, month, day, dayAdd);
    String str = String(month) +  "/" + String(day);
    lv_label_set_text(label_share[7], str.c_str()); // 标签文本
  }

// 更新电量
#if FUEL_GAUGE_TYPE == 0
  bat_soc = batVccToPer(bat_vcc);
#else
  get_bat_soc();
#endif
}
void display_stopwatch_init()
{
  LV_FONT_DECLARE(DinkieBitmap_10px);
  LV_FONT_DECLARE(ArialRoundedMTBold_14px);
  LV_FONT_DECLARE(rog_38px);
  LV_FONT_DECLARE(rog_30px);

  eepSavePage(page_stopwatch, 0);

  pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 2, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 0, LV_STATE_DEFAULT);
  lv_group_add_obj(group_my, page.p[page.index]);
  lv_obj_add_event_cb(page.p[page.index], display_stopwatch_event_msgbox, LV_EVENT_KEY, NULL);

  // 速度背景
  lv_obj_t *speed_gb = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(speed_gb, 68, 37);                                      // 设置大小
  lv_obj_align(speed_gb, LV_ALIGN_TOP_MID, 0, 0);                         // 设置对齐方式
  lv_obj_set_style_bg_color(speed_gb, MY_COLOR_YELLOW, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(speed_gb, &style_shadow, LV_STATE_DEFAULT);            // 设置阴影样式
  lv_obj_add_style(speed_gb, &style_squareShape, LV_STATE_DEFAULT);       // 设置方型样式
  lv_obj_set_style_outline_width(speed_gb, 2, 0);                         // 边框宽度
  lv_obj_set_style_outline_color(speed_gb, MY_COLOR_MAGENTA, 0);          // 边框颜色
  lv_obj_set_scrollbar_mode(speed_gb, LV_SCROLLBAR_MODE_OFF);             // 关闭滑动条
  // 速度标签
  label_share[0] = lv_label_create(speed_gb); // 创建标签
  // lv_label_set_long_mode(label_share[0], LV_LABEL_LONG_SCROLL_CIRCULAR); // 长字符模式
  // lv_obj_set_style_anim_duration(label_share[0], 5000, 0);               // 滚动时间
  // lv_obj_set_width(label_share[0], 70);                                  // 设置宽度
  lv_label_set_text(label_share[0], "9");                // 标签文本
  lv_obj_align(label_share[0], LV_ALIGN_CENTER, -19, 3); // 对齐方式
  lv_obj_set_style_text_font(label_share[0], &rog_38px, LV_STATE_DEFAULT);
  label_share[8] = lv_label_create(speed_gb);                                    // 创建标签
  lv_label_set_text(label_share[8], ".9");                                       // 标签文本
  lv_obj_align_to(label_share[8], label_share[0], LV_ALIGN_OUT_RIGHT_MID, 0, 0); // 对齐方式
  lv_obj_set_style_text_font(label_share[8], &rog_30px, LV_STATE_DEFAULT);

  // 里程背景
  lv_obj_t *mileage_gb = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(mileage_gb, 72, 19);                                    // 设置大小
  lv_obj_align(mileage_gb, LV_ALIGN_TOP_MID, 0, 41);                      // 设置对齐方式
  lv_obj_set_style_bg_color(mileage_gb, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(mileage_gb, &style_shadow, LV_STATE_DEFAULT);          // 设置阴影样式
  lv_obj_add_style(mileage_gb, &style_squareShape, LV_STATE_DEFAULT);     // 设置方型样式
  lv_obj_set_scrollbar_mode(mileage_gb, LV_SCROLLBAR_MODE_OFF);           // 关闭滑动条
  // 里程标签
  label_share[1] = lv_label_create(mileage_gb);        // 创建标签
  lv_label_set_text(label_share[1], "0.0");           // 标签文本
  lv_obj_align(label_share[1], LV_ALIGN_CENTER, 0, 1); // 对齐方式
  // 显示单位
  lv_obj_t *label = lv_label_create(mileage_gb);  // 创建标签
  lv_label_set_text(label, "KM");                 // 标签文本
  lv_obj_align(label, LV_ALIGN_BOTTOM_RIGHT, -1, 0); // 对齐方式
  lv_obj_set_style_text_font(label, &DinkieBitmap_10px, LV_STATE_DEFAULT);
  //lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  // 显示马头图标
  label = lv_label_create(mileage_gb);           // 创建标签
  lv_label_set_text(label, LV_SYMBOL_HORSEHEAD); // 标签文本
  lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);  // 对齐方式

  // 卫星数量背景
  lv_obj_t *satellite_gb = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(satellite_gb, 72, 19);                                    // 设置大小
  lv_obj_align(satellite_gb, LV_ALIGN_TOP_MID, 0, 62);                      // 设置对齐方式
  lv_obj_set_style_bg_color(satellite_gb, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(satellite_gb, &style_shadow, LV_STATE_DEFAULT);          // 设置阴影样式
  lv_obj_add_style(satellite_gb, &style_squareShape, LV_STATE_DEFAULT);     // 设置方型样式
  lv_obj_set_scrollbar_mode(satellite_gb, LV_SCROLLBAR_MODE_OFF);           // 关闭滑动条
  // 卫星数量标签
  label_share[2] = lv_label_create(satellite_gb);      // 创建标签
  lv_label_set_text(label_share[2], "99");             // 标签文本
  lv_obj_align(label_share[2], LV_ALIGN_CENTER, 0, 1); // 对齐方式
  // 显示定位精度
  label_share[3] = lv_label_create(satellite_gb);          // 创建标签
  lv_label_set_text(label_share[3], "9M");                 // 标签文本
  lv_obj_align(label_share[3], LV_ALIGN_BOTTOM_RIGHT, -1, 0); // 对齐方式
  lv_obj_set_style_text_font(label_share[3], &DinkieBitmap_10px, LV_STATE_DEFAULT);
  //lv_obj_set_style_text_color(label_share[3], MY_COLOR_WHITE, LV_STATE_DEFAULT);
  // 显示单位
  /*label = lv_label_create(satellite_gb);             // 创建标签
  lv_label_set_text(label, "HDOP");                  // 标签文本
  lv_obj_align(label, LV_ALIGN_BOTTOM_RIGHT, -1, 0); // 对齐方式
  lv_obj_set_style_text_color(label, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(label, &DinkieBitmap_10px, LV_STATE_DEFAULT);
  lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);*/
  // 显示卫星图标
  label = lv_label_create(satellite_gb);           // 创建标签
  lv_label_set_text(label, LV_SYMBOL_SATELLITE); // 标签文本
  lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);  // 对齐方式

  //********** 海拔背景********** 
  lv_obj_t *altitude_gb = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(altitude_gb, 72, 19);                                    // 设置大小
  lv_obj_align(altitude_gb, LV_ALIGN_TOP_MID, 0, 83);                      // 设置对齐方式
  lv_obj_set_style_bg_color(altitude_gb, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(altitude_gb, &style_shadow, LV_STATE_DEFAULT);          // 设置阴影样式
  lv_obj_add_style(altitude_gb, &style_squareShape, LV_STATE_DEFAULT);     // 设置方型样式
  lv_obj_set_scrollbar_mode(altitude_gb, LV_SCROLLBAR_MODE_OFF);           // 关闭滑动条
  // 海拔标签
  label_share[4] = lv_label_create(altitude_gb);       // 创建标签
  lv_label_set_text(label_share[4], "999");             // 标签文本
  lv_obj_align(label_share[4], LV_ALIGN_CENTER, 0, 1); // 对齐方式
  // 显示单位
  label = lv_label_create(altitude_gb);              // 创建标签
  lv_label_set_text(label, "M");                     // 标签文本
  lv_obj_align(label, LV_ALIGN_BOTTOM_RIGHT, -1, 0); // 对齐方式
  lv_obj_set_style_text_font(label, &DinkieBitmap_10px, LV_STATE_DEFAULT);
  //lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  // 显示山图标
  label = lv_label_create(altitude_gb);           // 创建标签
  lv_label_set_text(label, LV_SYMBOL_MOUNTAIN); // 标签文本
  lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);  // 对齐方式

  //********** 时间外框 **********
  lv_obj_t *date_gb = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(date_gb, 70, 19);                // 设置大小
  lv_obj_align(date_gb, LV_ALIGN_TOP_MID, 0, 106); // 设置对齐方式
  // lv_obj_set_style_bg_color(date_gb, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(date_gb, &style_shadow, LV_STATE_DEFAULT);      // 设置阴影样式
  lv_obj_add_style(date_gb, &style_squareShape, LV_STATE_DEFAULT); // 设置方型样式
  lv_obj_set_scrollbar_mode(date_gb, LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_set_style_outline_width(date_gb, 1, 0);                   // 边框宽度
  lv_obj_set_style_outline_color(date_gb, MY_COLOR_BLACK, 0);      // 边框颜色
  // 时间标签
  label_share[5] = lv_label_create(date_gb);             // 创建标签
  lv_label_set_text(label_share[5], "99:99");            // 标签文本
  lv_obj_align(label_share[5], LV_ALIGN_LEFT_MID, 2, 0); // 对齐方式
  lv_obj_set_style_text_color(label_share[5], MY_COLOR_RED, LV_STATE_DEFAULT);
  // 星期标签
  label_share[6] = lv_label_create(date_gb);               // 创建标签
  lv_label_set_text(label_share[6], "W9");                 // 标签文本
  lv_obj_align(label_share[6], LV_ALIGN_TOP_RIGHT, -1, 0); // 对齐方式
  lv_obj_set_style_text_color(label_share[6], MY_COLOR_BLACK, LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(label_share[6], &DinkieBitmap_10px, LV_STATE_DEFAULT);
  // 日期标签
  label_share[7] = lv_label_create(date_gb);              // 创建标签
  lv_label_set_text(label_share[7], "99/99");                 // 标签文本
  lv_obj_align(label_share[7], LV_ALIGN_BOTTOM_RIGHT, -1, 0); // 对齐方式
  lv_obj_set_style_text_color(label_share[7], MY_COLOR_BLACK, LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(label_share[7], &DinkieBitmap_10px, LV_STATE_DEFAULT);

  //****************** 电量背景 ******************
  lv_obj_t *power_bg = lv_obj_create(page.p[page.index]);
  lv_obj_set_scrollbar_mode(power_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_set_style_bg_color(power_bg, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  lv_obj_add_style(power_bg, &style_squareShape, 0);
  lv_obj_set_size(power_bg, 72, 18);
  lv_obj_align(power_bg, LV_ALIGN_BOTTOM_MID, 0, 0);
  // 画电池的白色外框
  lv_obj_t *bat = lv_obj_create(power_bg);
  lv_obj_set_size(bat, 25, 13);
  lv_obj_set_style_bg_color(bat, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_set_style_pad_all(bat, 0, LV_STATE_DEFAULT);               // 设置边距
  lv_obj_set_style_radius(bat, 2, LV_STATE_DEFAULT);                // 设置圆角
  lv_obj_set_style_border_width(bat, 0, LV_STATE_DEFAULT);          // 边框宽度
  lv_obj_align(bat, LV_ALIGN_LEFT_MID, 3, 0);
  // 画电池的绿色内容
  bat_g = lv_obj_create(bat);

#if FUEL_GAUGE_TYPE == 0
  bat_soc = batVccToPer(bat_vcc);
#else
  get_bat_soc();
#endif

  uint8_t w = map(bat_soc, 0, 100, 3, 21);
  lv_obj_set_size(bat_g, w, 9);
  if (bat_soc > 60) // 大于60显示绿色
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_GREEN, LV_STATE_DEFAULT);   // 背景颜色
  else if (bat_soc > 30) // 大于30显示洋红
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_MAGENTA, LV_STATE_DEFAULT); // 背景颜色
  else // 小于等于30显示红色
    lv_obj_set_style_bg_color(bat_g, MY_COLOR_RED, LV_STATE_DEFAULT);     // 背景颜色

  lv_obj_set_style_pad_all(bat_g, 0, LV_STATE_DEFAULT);               // 设置边距
  lv_obj_set_style_radius(bat_g, 1, LV_STATE_DEFAULT);                // 设置圆角
  lv_obj_set_style_border_width(bat_g, 0, LV_STATE_DEFAULT);          // 边框宽度
  lv_obj_align(bat_g, LV_ALIGN_LEFT_MID, 2, 0);
  // 画电池的白色头
  lv_obj_t *bat_w = lv_obj_create(power_bg);
  lv_obj_set_size(bat_w, 2, 9);
  lv_obj_set_style_bg_color(bat_w, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_set_style_pad_all(bat_w, 0, LV_STATE_DEFAULT);               // 设置边距
  lv_obj_set_style_radius(bat_w, 1, LV_STATE_DEFAULT);                // 设置圆角
  lv_obj_set_style_border_width(bat_w, 0, LV_STATE_DEFAULT);          // 边框宽度
  lv_obj_align_to(bat_w, bat, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
  // 画电量百分比
  label_batPer = lv_label_create(power_bg);
  lv_obj_align(label_batPer, LV_ALIGN_RIGHT_MID, -1, 1);
  if (bat_soc >= 10.0) lv_label_set_text_fmt(label_batPer, "%d%%", (uint8_t)bat_soc);
  else                 lv_label_set_text_fmt(label_batPer, "%.1f%%", bat_soc);
  lv_obj_set_style_text_color(label_batPer, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 字体颜色
  lv_obj_set_style_text_font(label_batPer, &ArialRoundedMTBold_14px, LV_STATE_DEFAULT);

  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(stopwatch_timer_cb, 500, NULL); // 定时更新
}

//****** 按键ADC校准
int16_t keyADC_old = -1;
int16_t keyADC_cali_adc_max = -5000;
int16_t keyADC_cali_adc_min = 5000;
void keyADC_cali_msgbox_end(lv_event_t *e) 
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出
  {
    // 关闭定时器
    if (lvTimer_share[0] != NULL)
    {
      lv_timer_delete(lvTimer_share[0]);
      lvTimer_share[0] = NULL;
    }
    eep.begin("eepUser", false);
    eep.putUInt("keyADCUp", eep_keyADCUp);
    eep.putUInt("keyADCDown", eep_keyADCDown);
    eep.end();
   my_msgbox_exit(5); // 退出弹窗
    exitToMainSet();           // 退出至设置菜单
  }
  else if (data[0] == 1) // 重来
  {
    lv_label_set_text(label_share[1], String("向上推").c_str());
    lv_anim_t *b = lv_anim_get(label_share[1], label_y_bounce_anim_cb);
    if (b != NULL)
    {
      lv_anim_delete(b, label_y_bounce_anim_cb);
      lv_obj_align(label_share[1], LV_ALIGN_TOP_MID, 0, 22);
      lv_obj_update_layout(label_share[1]);
      uint8_t y = lv_obj_get_y(label_share[1]);
      lv_anim_init(b);                                      // 动画初始化
      lv_anim_set_var(b, label_share[1]);                   // 设置需要动画的对象
      lv_anim_set_values(b, y - 8, y);                      // 设置动画的开始值和结束值
      lv_anim_set_duration(b, 200);                         // 设置动画的持续时间
      lv_anim_set_exec_cb(b, label_y_bounce_anim_cb);       // 设置需要变化的值
      lv_anim_set_path_cb(b, lv_anim_path_ease_out);        // 设置变化特效
      lv_anim_set_repeat_count(b, LV_ANIM_REPEAT_INFINITE); // 动画重复
      lv_anim_set_repeat_delay(b, 1200);                    // 在重复动画之前设置延迟。
      lv_anim_start(b);
    }
   my_msgbox_exit(0); // 退出弹窗
  }
}
void width_change_anim_cb0(void *var, int32_t v) // 进度条增加
{
  lv_obj_set_width((lv_obj_t *)var, v);
}
void width_change_anim_cb1(void *var, int32_t v) // 进度条减少
{
  lv_obj_set_width((lv_obj_t *)var, v);
}
void keyADC_cali_up_end(lv_anim_t *a)
{
  Serial.printf("keyADC_cali_adc_max:%d\n",keyADC_cali_adc_max);
  Serial.printf("keyADC_cali_adc_min:%d\n",keyADC_cali_adc_min);
  Serial.printf("keyADC_old:%d\n",keyADC_old);
  while (buzzerRun == 1) delay(10);
  if (keyADC_cali_adc_max <= 30 && keyADC_cali_adc_min >= -30) // 误差在合格范围
  {
    String text = lv_label_get_text(label_share[1]);
    String str = F("向上推");
    if (strcmp(str.c_str(), text.c_str()) == 0)
    {
      eep_keyADCUp = keyADC_old;
      // 更换文字和动画方向
      lv_label_set_text(label_share[1], String("向下推").c_str());
      lv_anim_t *b = lv_anim_get(label_share[1], label_y_bounce_anim_cb);
      if (b != NULL)
      {
        lv_anim_delete(b, label_y_bounce_anim_cb);
        lv_obj_align(label_share[1], LV_ALIGN_TOP_MID, 0, 18);
        lv_obj_update_layout(label_share[1]);
        uint8_t y = lv_obj_get_y(label_share[1]);
        lv_anim_init(b);                                      // 动画初始化
        lv_anim_set_var(b, label_share[1]);                   // 设置需要动画的对象
        lv_anim_set_values(b, y + 8, y);                      // 设置动画的开始值和结束值
        lv_anim_set_duration(b, 200);                         // 设置动画的持续时间
        lv_anim_set_exec_cb(b, label_y_bounce_anim_cb);       // 设置需要变化的值
        lv_anim_set_path_cb(b, lv_anim_path_ease_out);        // 设置变化特效
        lv_anim_set_repeat_count(b, LV_ANIM_REPEAT_INFINITE); // 动画重复
        lv_anim_set_repeat_delay(b, 1200);                    // 在重复动画之前设置延迟。
        lv_anim_start(b);
      }
    }
    else
    {
      eep_keyADCDown = keyADC_old;
      my_msgbox_send(F("校准"), F("完成"), 0, F("退出\n重来\n"), keyADC_cali_msgbox_end);
    }
    buzzer_setNote();
    buzzerSen(150);
  }
  else // 误差大，提示重新开始
  {
    buzzer_negative();
    my_msgbox_send(F("校准"), F("误差过大"), 0, F("返回\n"), msgbox_exit_cb);
  }
  Serial.printf("eep_keyADCUp:%d\n",eep_keyADCUp);
  Serial.printf("eep_keyADCDown:%d\n",eep_keyADCDown);
  keyADC_cali_adc_max = -5000;
  keyADC_cali_adc_min = 5000;
}
void keyADC_cali_timer_cb(lv_timer_t *time)
{
  if (eep_disPage != page_keyADCCali) return;
  if (buzzerRun == 1) return;
  if (bitRead(mbox.state, MBOX_STATE_REMAIN) == 1) return;

  lv_obj_update_layout(label_share[3]);
  int16_t w = lv_obj_get_width(label_share[3]);     // 进度条的长度

  //********** ADC按键处理 动画
  uint16_t adc = analogRead(KEY_ADC_PIN);
  lv_label_set_text_fmt(label_share[2], "%d", adc); // ADC标签文本
  if (adc < 4000 && adc > 100)
  {
    // 检查与上一次的差值
    if (keyADC_old == -1)
    {
      keyADC_old = adc;
    }
    else 
    {
      int16_t diff = adc - keyADC_old;
      if      (diff > keyADC_cali_adc_max) keyADC_cali_adc_max = diff;
      else if (diff < keyADC_cali_adc_min) keyADC_cali_adc_min = diff;
      keyADC_old = adc;
      //Serial.printf("keyADC_cali_adc_max:%d\n",keyADC_cali_adc_max);
      //Serial.printf("keyADC_cali_adc_min:%d\n",keyADC_cali_adc_min);
      //Serial.println();
    }

    // 更改ADC标签颜色
    if (w > 45)
      lv_obj_set_style_text_color(label_share[2], MY_COLOR_WHITE, 0);

    // 播放声音
    if     (w >= 10 && w < 15) {buzzer_setNote(1,8);  buzzerSen(20);}
    else if(w >= 15 && w < 20) {buzzer_setNote(2,8);  buzzerSen(20);}
    else if(w >= 20 && w < 25) {buzzer_setNote(3,8);  buzzerSen(20);}
    else if(w >= 25 && w < 30) {buzzer_setNote(4,8);  buzzerSen(20);}
    else if(w >= 30 && w < 35) {buzzer_setNote(5,8);  buzzerSen(20);}
    else if(w >= 35 && w < 40) {buzzer_setNote(6,8);  buzzerSen(20);}
    else if(w >= 40 && w < 45) {buzzer_setNote(7,8);  buzzerSen(20);}
    else if(w >= 45 && w < 50) {buzzer_setNote(8,8);  buzzerSen(20);}
    else if(w >= 50 && w < 55) {buzzer_setNote(9,8);  buzzerSen(20);}
    else if(w >= 45 && w < 50) {buzzer_setNote(10,8); buzzerSen(20);}
      
    // 检查进度条减少的动画是否运行中
    lv_anim_t *a = lv_anim_get(label_share[3], width_change_anim_cb1);
    if (a == NULL && w < 60) // 进度条减少的动画不运行才执行增加动画
    {
      a = lv_anim_get(label_share[3], width_change_anim_cb0);
      if (a == NULL)
      {
        lv_anim_t a;
        lv_anim_init(&a);                                 // 动画初始化
        lv_anim_set_var(&a, label_share[3]);              // 设置需要动画的对象
        lv_anim_set_values(&a, w, 60);                    // 设置动画的开始值和结束值
        lv_anim_set_duration(&a, 2000);                   // 设置动画的持续时间
        lv_anim_set_exec_cb(&a, width_change_anim_cb0);   // 设置需要变化的值
        lv_anim_set_path_cb(&a, lv_anim_path_linear);     // 设置变化特效
        lv_anim_set_completed_cb(&a, keyADC_cali_up_end); // 设置动画完成时的函数调用
        lv_anim_start(&a);                                // 动画开始
      }
    }
  }
  else
  {
    // 更改ADC标签颜色
    lv_obj_set_style_text_color(label_share[2], MY_COLOR_YELLOW, 0);
    //检查进度条增加的动画是否运行中 ，运行中就删除
    lv_anim_t *a = lv_anim_get(label_share[3], width_change_anim_cb0);
    if (a != NULL || (a == NULL && w > 5))
    {
      keyADC_old = -1;
      lv_anim_delete(label_share[3], width_change_anim_cb0);
      // 检查进度条减少的动画是否运行中，运行中就等待运行结束
      a = lv_anim_get(label_share[3], width_change_anim_cb1);
      if (a == NULL) 
      {
        lv_anim_t a;
        lv_anim_init(&a);                              // 动画初始化
        lv_anim_set_var(&a, label_share[3]);           // 设置需要动画的对象
        lv_anim_set_values(&a, w, 5);                  // 设置动画的开始值和结束值
        lv_anim_set_duration(&a, 500);                 // 设置动画的持续时间
        lv_anim_set_exec_cb(&a, width_change_anim_cb1); // 设置需要变化的值
        lv_anim_set_path_cb(&a, lv_anim_path_bounce);   // 设置变化特效
        lv_anim_start(&a);
      }
    }
  }
}
void display_keyADC_cali_init()
{
  LV_FONT_DECLARE(ArialRoundedMTBold_14px);

  eepSavePage(page_keyADCCali, 0);

  uint8_t index = pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_group_add_obj(group_my, page.p[index]);
  // lv_obj_add_event_cb(page.p[index], display_keyADC_cali_event, LV_EVENT_KEY, NULL);

  lv_obj_t *label = lv_label_create(page.p[index]);        // 创建标签
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);            // 设置对齐方式
  lv_label_set_text(label, String(F("按键校准")).c_str());  // 标签文本
  label = lv_label_create(page.p[index]);                  // 创建标签
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 28);            // 设置对齐方式
  lv_label_set_text(label, String(F("侧面复位")).c_str());  // 标签文本
  label = lv_label_create(page.p[index]);                  // 创建标签
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 46);            // 设置对齐方式
  lv_label_set_text(label, String(F("退出")).c_str());     // 标签文本
  // lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP); // 长字符模式

  //********** ADC数值和进度条背景 **********
  label_share[0] = lv_obj_create(page.p[index]);
  lv_obj_set_size(label_share[0], 72, 72);                                     // 设置大小
  lv_obj_align(label_share[0], LV_ALIGN_BOTTOM_MID, 0, 0);                     // 设置对齐方式
  lv_obj_set_style_bg_color(label_share[0], MY_COLOR_BLACK, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(label_share[0], &style_shadow, LV_STATE_DEFAULT);           // 设置阴影样式
  lv_obj_add_style(label_share[0], &style_squareShape, LV_STATE_DEFAULT);      // 设置方型样式
  lv_obj_set_scrollbar_mode(label_share[0], LV_SCROLLBAR_MODE_OFF);            // 关闭滑动条
  // 提示文字
  label = lv_label_create(label_share[0]);              // 创建标签
  lv_label_set_text(label, String(F("将拨轮")).c_str());            // 标签文本
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);                    // 对齐方式
  lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  label_share[1] = lv_label_create(label_share[0]);               // 创建标签
  lv_label_set_text(label_share[1], String(F("向上推")).c_str()); // 标签文本
  lv_obj_align(label_share[1], LV_ALIGN_TOP_MID, 0, 22);          // 对齐方式
  lv_obj_set_style_text_color(label_share[1], MY_COLOR_WHITE, LV_STATE_DEFAULT);
  label_share[2] = lv_label_create(label_share[0]);             // 创建标签
  lv_label_set_text(label_share[2], String(F("4095")).c_str()); // 标签文本
  lv_obj_align(label_share[2], LV_ALIGN_TOP_MID, 0, 42);        // 对齐方式
  lv_obj_set_style_text_color(label_share[2], MY_COLOR_YELLOW, 0);
  lv_obj_set_style_text_font(label_share[2], &ArialRoundedMTBold_14px, 0);
  // 进度条外框
  lv_obj_t *wk = lv_obj_create(label_share[0]);
  lv_obj_add_style(wk, &style_shadow, LV_STATE_DEFAULT);      // 设置阴影样式
  lv_obj_add_style(wk, &style_squareShape, LV_STATE_DEFAULT); // 设置方型样式
  lv_obj_set_scrollbar_mode(wk, LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_set_size(wk, 62, 9);                                 // 设置大小
  lv_obj_align(wk, LV_ALIGN_BOTTOM_MID, 0, -4);                // 设置对齐方式
  // lv_obj_set_style_bg_color(wk, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_set_style_bg_opa(wk, LV_OPA_0, LV_STATE_DEFAULT);              // 背景不透明度
  lv_obj_set_style_outline_color(wk, MY_COLOR_CYAN, LV_STATE_DEFAULT); // 外框颜色
  lv_obj_set_style_outline_width(wk, 1, LV_STATE_DEFAULT);              // 外框宽度
  // 进度条 动态条
  label_share[3] = lv_obj_create(label_share[0]);
  lv_obj_set_style_bg_color(label_share[3], MY_COLOR_CYAN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_add_style(label_share[3], &style_shadow, LV_STATE_DEFAULT);          // 设置阴影样式
  lv_obj_add_style(label_share[3], &style_squareShape, LV_STATE_DEFAULT);     // 设置方型样式
  lv_obj_set_scrollbar_mode(label_share[3], LV_SCROLLBAR_MODE_OFF);           // 关闭滑动条
  lv_obj_set_size(label_share[3], 5, 7);                                      // 设置大小
  lv_obj_align_to(label_share[3], wk, LV_ALIGN_LEFT_MID, 1, 0);               // 设置对齐方式
  lv_obj_set_style_bg_color(label_share[3], MY_COLOR_GREEN, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_set_style_outline_opa(label_share[3], LV_OPA_0, LV_STATE_DEFAULT);    // 外框不透明度

  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(keyADC_cali_timer_cb, 100, NULL); // 定时更新

  //********** 播放弹跳动画
  lv_obj_update_layout(label_share[1]);
  uint8_t y = lv_obj_get_y(label_share[1]);
  lv_anim_t a;
  lv_anim_init(&a);                                      // 动画初始化
  lv_anim_set_var(&a, label_share[1]);                   // 设置需要动画的对象
  lv_anim_set_values(&a, y - 8, y);                      // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, 200);                         // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, label_y_bounce_anim_cb);       // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);        // 设置变化特效
  lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); // 动画重复
  lv_anim_set_repeat_delay(&a, 1200);                    // 在重复动画之前设置延迟。
  lv_anim_start(&a);
}

//****** 备忘录
// 通用 弹窗的退出返回，返回则返回至主设置页面
void backPage_memoSet(lv_event_t *e) 
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出
  {
   my_msgbox_exit(5); // 退出弹窗
    display_memoSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter();     // 打开全局抖动
    focusPosOld_return(); // 回到刚才的焦点
  }
  else if (data[0] == 1) // 返回
  {
   my_msgbox_exit(0); // 退出弹窗
  }
}
void display_memo_event_msgbox(lv_event_t *e)  // 当屏幕被聚焦时，弹出退出弹窗
{
  uint8_t key = lv_indev_get_key(lv_indev_active());
  //Serial.printf("key:%d", key);
  if (key == LV_KEY_RIGHT || key == LV_KEY_LEFT)
  {
    my_msgbox_send(F("备忘录"), F("是否退出"), 0, F("退出\n返回\n"), backPage_memoSet);
  }
}
void display_memo_init()
{
  lv_color_t color[8] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW, MY_COLOR_MAGENTA,
                         MY_COLOR_BLUE, MY_COLOR_RED, MY_COLOR_WHITE, MY_COLOR_BLACK};

  eepSavePage(page_memo, 1);
  pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_bg_color(page.p[page.index], color[eep_memoBg], 0);        // 设置背景颜色
  lv_group_add_obj(group_my, page.p[page.index]);
  lv_obj_add_event_cb(page.p[page.index], display_memo_event_msgbox, LV_EVENT_KEY, NULL);
  //****************** 一句话标签
  const char *inAWord = eep_inAWord.c_str();
  lv_obj_t *sentence = lv_label_create(page.p[page.index]); // 句子
  lv_obj_add_style(sentence, &style_squareShape, 0); // 添加正方形样式
  const lv_font_t *font = lv_obj_get_style_text_font(sentence, 0);
  // 对长字符分行时，缩短其间隔
  uint8_t line = 1;
  String result = autoLineFeed(inAWord, 72, font, &line); // 自动根据指定像素值添加换行符
  //Serial.printf("line:%d\n", line);
  lv_obj_align(sentence, LV_ALIGN_CENTER, 0, 1);
  lv_label_set_text(sentence, result.c_str());
  lv_obj_set_style_text_color(sentence, color[eep_memoFC], 0); // 字体颜色
  if (line >= 10)
    lv_obj_align(sentence, LV_ALIGN_TOP_MID, 0, -2);
  if (line >= 9)// 三行以上时缩短行间距
    lv_obj_set_style_text_line_space(sentence, -4, 0); // 设置行间距

  // 播放进入音乐
  uint16_t *melody = (uint16_t *)malloc(10 * sizeof(uint16_t));
  uint16_t i = 0;
  melody[i++] = 3200; melody[i++] = 60; melody[i++] = 35;
  melody[i++] = 3600; melody[i++] = 60; melody[i++] = 40; 
  melody[i++] = 2800; melody[i++] = 80; melody[i++] = 50;
  melody[i++] = 0; 
  buzzer_music_rtos_init(melody);
}

//****** 备忘录设置
void display_memoSet_event1(lv_event_t *e) // 切换标签编辑模式的事件
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  // Serial.printf("code:%d\n",code);

  if (code == LV_EVENT_PRESSED) // 切换编辑状态
  {
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;
    if (page.keyMode == KEY_MODE_PN) // 进入编辑模式，修改成白底黑字
    {
      page.keyMode = KEY_MODE_RL;
      lv_obj_set_style_bg_color(obj, MY_COLOR_BLACK, LV_STATE_DEFAULT); // 设置背景颜色
      lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
    else // 退出编辑模式，恢复原来的样式
    {
      eepSaveState = 1;
      page.keyMode = KEY_MODE_PN;
      lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                             MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
      lv_obj_set_style_bg_color(obj, color[i % 6], LV_STATE_DEFAULT); // 设置背景颜色
      if ((i % 6) < 3)
        lv_obj_set_style_text_color(child, MY_COLOR_BLACK, LV_STATE_DEFAULT);
      else
        lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
  }
  else if (code == LV_EVENT_KEY) // 数值加减
  {
    uint8_t key = lv_indev_get_key(lv_indev_active());
    if (key == LV_KEY_ENTER) return;
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;  
    // 数值加减
    if (key == LV_KEY_LEFT) // 减
    {
      if (*sm0.num_u8[i] == sm0.min[i])
        *sm0.num_u8[i] = sm0.max[i];
      else
        *sm0.num_u8[i] -= sm0.step[i];
    }
    else if (key == LV_KEY_RIGHT) // 加
    {
      if (*sm0.num_u8[i] == sm0.max[i])
        *sm0.num_u8[i] = sm0.min[i];
      else
        *sm0.num_u8[i] += sm0.step[i];
    }

    String color0[8] = {F("青色"), F("绿色"), F("黄色"), F("洋红"),
                        F("蓝色"), F("红色"), F("白色"), F("黑色")};
    String text = String(lv_label_get_text(child));
    int pos = text.indexOf("色");
    text = text.substring(0, pos + 3);
    text += String(color0[*sm0.num_u8[i]]);
    // Serial.printf("text:%s", text);
    lv_label_set_text(child, text.c_str()); // 标签文本
  }

  LV_UNUSED(obj);
  LV_UNUSED(child);
}
void display_memoSet_event2(lv_event_t *e) // 时钟显示使能切换
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  eep_memoClockEn = !eep_memoClockEn;
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  String obj_name1 = F("时钟显示");
  if (eep_memoClockEn)
    obj_name1 += F("已启用");
  else
    obj_name1 += F("已停用");
  lv_label_set_text(child, obj_name1.c_str());  
  eepSaveState = 1;
}
void display_memoSet_event3(lv_event_t *e) // 休眠显示使能切换
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  eep_memoSleepEn = !eep_memoSleepEn;
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  String obj_name1 = F("休眠显示");
  if (eep_memoSleepEn) obj_name1 += F("已启用");
  else                 obj_name1 += F("已停用");
  lv_label_set_text(child, obj_name1.c_str());  
  eepSaveState = 1;
}
void display_memoSet_event4(lv_event_t *e) // 跳转备忘录界面
{
  if (eep_inAWord.length() > 1)
  {
    focusPosOld_save(); // 保存上一个界面的焦点
    display_memo_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
  }
  else my_msgbox_send(F("备忘录"), F("未设置"), 0, F("退出\n返回\n"), backPage_mainSet);
}
void display_memoSet_init()
{
  eepSavePage(page_memoSet, 1);

  uint8_t j = 0;
  sm0.num_u8[j++] = &eep_memoBg;   // 背景色
  sm0.num_u8[j++] = &eep_memoFC; // 字体色
  j = 0;
  sm0.step[j++] = 1; // 加减的步进值
  sm0.step[j++] = 1;
  j = 0;
  sm0.min[j++] = 0; // 最小值
  sm0.min[j++] = 0;
  j = 0;
  sm0.max[j++] = 7; // 最大值
  sm0.max[j++] = 7;

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 3, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  //参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值 控制Y轴排布
  //参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER    
  //参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。 控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // lv_obj_set_flex_grow(page.p[page.index], 3); //设置对象生长的宽度或高度（在主轴上），以填充自由空间
  lv_obj_set_style_pad_row(page.p[page.index], 5, LV_STATE_DEFAULT); // 设置行间距为5像素

  String color0[8] = {F("青色"), F("绿色"), F("黄色"), F("洋红"),
                     F("蓝色"), F("红色"), F("白色"), F("黑色")};

  uint8_t optNum = 2; // 可调数值的数量
  String obj_name[optNum];
  uint8_t count = 0;
  obj_name[0] = F("背景颜色");
  obj_name[0] += color0[eep_memoBg];
  obj_name[1] = F("字体颜色");
  obj_name[1] += color0[eep_memoFC];

  lv_obj_t *but[optNum];
  lv_obj_t *label[optNum];

  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};

  uint16_t timeArray[optNum];
  for (uint8_t i = 0; i < optNum; i++)
    timeArray[i] = *sm0.num_u8[i];

  for (uint8_t i = 0; i < optNum; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[page.index]);
    lv_obj_set_size(but[i], 72, 40);                                            // 设置大小
    //lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 46);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
    
    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    lv_obj_set_width(label[i], 72);
    lv_label_set_long_mode(label[i], LV_LABEL_LONG_WRAP); // 长字符模式
    lv_obj_align(label[i], LV_ALIGN_LEFT_MID, 4, 0);      // 对齐方式
    lv_label_set_text(label[i], obj_name[i].c_str());     // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);
    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);

    // 按钮触发功能
    lv_obj_add_event_cb(but[i], display_memoSet_event1, LV_EVENT_PRESSED, &num[i]); // 切换编辑状态
    lv_obj_add_event_cb(but[i], display_memoSet_event1, LV_EVENT_KEY, &num[i]);     // 编辑状态下的数值加减
  }

  
  lv_obj_t *but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 40);                                               // 设置大小
  //lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 2 * 46);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_BLUE, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  lv_obj_t *label1 = lv_label_create(but1);     // 创建标签
  lv_obj_align(label1, LV_ALIGN_LEFT_MID, 4, 0); // 居中对齐
  lv_obj_set_style_text_align(label1, LV_ALIGN_CENTER, 0);// 对齐方式
  lv_obj_set_width(label1, 72);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); // 长字符模式
  String obj_name1 = F("时钟显示");
  if (eep_memoClockEn) obj_name1 += F("已启用");
  else                 obj_name1 += F("已停用");
  lv_label_set_text(label1, obj_name1.c_str());                              // 标签文本
  lv_obj_add_event_cb(but1, display_memoSet_event2, LV_EVENT_PRESSED, NULL); // 使能切换
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_group_add_obj(group_my, but1);

  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 40);                                            // 设置大小
  //lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 3 * 46);                          // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_YELLOW, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  label1 = lv_label_create(but1);                                           // 创建标签
  lv_obj_align(label1, LV_ALIGN_LEFT_MID, 4, 0);                            // 居中对齐
  lv_obj_set_style_text_align(label1, LV_ALIGN_CENTER, 0);                  // 对齐方式
  lv_obj_set_style_text_color(label1, MY_COLOR_BLACK, 0);
  lv_obj_set_width(label1, 72);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_WRAP); // 长字符模式
  obj_name1 = F("休眠显示");
  if (eep_memoSleepEn) obj_name1 += F("已启用");
  else                 obj_name1 += F("已停用");
  lv_label_set_text(label1, obj_name1.c_str());                              // 标签文本
  lv_obj_add_event_cb(but1, display_memoSet_event3, LV_EVENT_PRESSED, NULL); // 使能切换
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_group_add_obj(group_my, but1);

  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 25);                                               // 设置大小
  //lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 4 * 46);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_RED, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  label1 = lv_label_create(but1);                                             // 创建标签
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);                                // 对齐方式
  lv_label_set_text(label1, "查看");                                          // 标签文本
  lv_obj_add_event_cb(but1, display_memoSet_event4, LV_EVENT_PRESSED, NULL);  // 进入回调
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);  // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);

  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 25);                                               // 设置大小
  //lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 5 * 46);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_MAGENTA, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  label1 = lv_label_create(but1);                                             // 创建标签
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);                                 // 对齐方式
  lv_label_set_text(label1, "退出"); // 标签文本
  lv_obj_add_event_cb(but1, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);   // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);
}

//****** 前置光设置
void readAmbientLight_timer_cb(lv_timer_t *time)
{
  if (eep_disPage != page_frontLightSet)
    return;
  lv_label_set_text_fmt(label_share[0], "%.2fLux", shareNum_f[0]); // 光强度
}
void display_frontLightSet_event1(lv_event_t *e) // 切换标签编辑模式的事件
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  lv_event_code_t code = lv_event_get_code(e);
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];
  // Serial.printf("code:%d\n",code);

  if (code == LV_EVENT_PRESSED) // 切换编辑状态
  {
    bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    if(run == 1) return;
    if (page.keyMode == KEY_MODE_PN) // 进入编辑模式，修改成白底黑字
    {
      page.keyMode = KEY_MODE_RL;
      lv_obj_set_style_bg_color(obj, MY_COLOR_BLACK, LV_STATE_DEFAULT); // 设置背景颜色
      lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
    else // 退出编辑模式，恢复原来的样式
    {
      eepSaveState = 1;
      page.keyMode = KEY_MODE_PN;
      lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                             MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
      lv_obj_set_style_bg_color(obj, color[i % 6], LV_STATE_DEFAULT); // 设置背景颜色
      if ((i % 6) < 3)
        lv_obj_set_style_text_color(child, MY_COLOR_BLACK, LV_STATE_DEFAULT);
      else
        lv_obj_set_style_text_color(child, MY_COLOR_WHITE, LV_STATE_DEFAULT);
    }
  }
  else if (code == LV_EVENT_KEY) // 数值加减
  {
    uint8_t key = lv_indev_get_key(lv_indev_active());
    if (key == LV_KEY_ENTER) return;
    // bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    // if(run == 1) return;  
    addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
    // 数值加减
    if (key == LV_KEY_LEFT) // 减
    {
      if (*sm0.num_u8[i] == sm0.min[i])
        *sm0.num_u8[i] = sm0.max[i];
      else
        *sm0.num_u8[i] -= sm0.step[i];
    }
    else if (key == LV_KEY_RIGHT) // 加
    {
      if (*sm0.num_u8[i] == sm0.max[i])
        *sm0.num_u8[i] = sm0.min[i];
      else
        *sm0.num_u8[i] += sm0.step[i];
    }

    if (eep_ledEn) ledcWrite(LED_CHANNEL, map(eep_ledPwm,0,255,0,1023));
    else           ledcWrite(LED_CHANNEL, 0);

    String text = String(lv_label_get_text(child));
    int pos = text.indexOf(":");
    text = text.substring(0, pos + 1);
    text += String(*sm0.num_u8[i]);
    // Serial.printf("text:%s", text);
    lv_label_set_text(child, text.c_str()); // 标签文本
  }

  LV_UNUSED(obj);
  LV_UNUSED(child);
}
void display_frontLightSet_event2(lv_event_t *e) // 自动打开使能
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  eep_ledAuto = !eep_ledAuto;
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  String obj_name1=F("自动:");
  if (eep_ledAuto) obj_name1 += F("开");
  else             obj_name1 += F("关");
  lv_label_set_text(child, obj_name1.c_str());  
  eepSaveState = 1;
}
void display_frontLightSet_event3(lv_event_t *e) // LED使能切换
{
  //检查动画是否播放中，播放中就退出
  lv_obj_t *obj = lv_event_get_target_obj(e);
  bool run = addAnimation_event(obj, button_width_shrink_anim_init); // 添加动画不重叠
  if(run == 1) return;

  eep_ledEn = !eep_ledEn;
  lv_obj_t *child = lv_obj_get_child(obj, 0);
  String obj_name1;
  if (eep_ledEn) obj_name1 = F("已启用");
  else           obj_name1 = F("已停用");
  if (eep_ledEn) ledcWrite(LED_CHANNEL, map(eep_ledPwm,0,255,0,1023));
  else           ledcWrite(LED_CHANNEL, 0);
  lv_label_set_text(child, obj_name1.c_str());  
  eepSaveState = 1;
}
void display_frontLightSet_init()
{
  eepSavePage(page_frontLightSet, 0);

  uint8_t j = 0;
  sm0.num_u8[j++] = &eep_ledPwm; // 占空比
  sm0.num_u8[j++] = &eep_ledFre; // 频率
  j = 0;
  sm0.step[j++] = 5; // 加减的步进值
  sm0.step[j++] = 10;
  j = 0;
  sm0.min[j++] = 5; // 最小值
  sm0.min[j++] = 30;
  j = 0;
  sm0.max[j++] = 255; // 最大值
  sm0.max[j++] = 250;

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 3, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  //参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值 控制Y轴排布
  //参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER    
  //参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。 控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  //lv_obj_set_flex_grow(page.p[page.index], 3); //设置对象生长的宽度或高度（在主轴上），以填充自由空间
    lv_obj_set_style_pad_row(page.p[page.index], 5, LV_STATE_DEFAULT); // 设置行间距为5像素

  uint8_t optNum = 2; // 可调数值的数量
  uint8_t count = 0;
  String obj_name[optNum];
  obj_name[0] = F("亮度:");
  obj_name[0] += String(eep_ledPwm);
  obj_name[1] = F("频率:");
  obj_name[1] += String(eep_ledFre);

  lv_obj_t *but[optNum];
  lv_obj_t *label[optNum];

  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};

  // 可调选项赋值
  uint16_t timeArray[optNum];
  for (uint8_t i = 0; i < optNum; i++)
    timeArray[i] = *sm0.num_u8[i];

  for (uint8_t i = 0; i < optNum; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[page.index]);
    lv_obj_set_size(but[i], 72, 25);                                            // 设置大小
    //lv_obj_align(but[i], LV_ALIGN_TOP_MID, 0, i * 46);                          // 设置对齐方式
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
    
    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    lv_obj_set_width(label[i], 72);
    lv_label_set_long_mode(label[i], LV_LABEL_LONG_WRAP); // 长字符模式
    lv_obj_align(label[i], LV_ALIGN_LEFT_MID, 4, 0);      // 对齐方式
    lv_label_set_text(label[i], obj_name[i].c_str());     // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);
    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);

    // 按钮触发功能
    lv_obj_add_event_cb(but[i], display_frontLightSet_event1, LV_EVENT_PRESSED, &num[i]); // 切换编辑状态
    lv_obj_add_event_cb(but[i], display_frontLightSet_event1, LV_EVENT_KEY, &num[i]);     // 编辑状态下的数值加减
  }

  lv_obj_t *but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 25); // 设置大小
  lv_obj_set_style_bg_color(but1, MY_COLOR_YELLOW, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  lv_obj_t *label1 = lv_label_create(but1);                                 // 创建标签
  lv_obj_align(label1, LV_ALIGN_LEFT_MID, 10, 0);                            // 居中对齐
  lv_obj_set_style_text_align(label1, LV_ALIGN_CENTER, 0);// 对齐方式
  lv_obj_set_width(label1, 72);
  lv_obj_set_style_text_color(label1, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  String obj_name1 = F("自动:");
  if (eep_ledAuto) obj_name1 += F("开");
  else           obj_name1 += F("关");
  lv_label_set_text(label1, obj_name1.c_str());                              // 标签文本
  lv_obj_add_event_cb(but1, display_frontLightSet_event2, LV_EVENT_PRESSED, NULL); // 使能切换
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);       // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);

  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 25); // 设置大小
  lv_obj_set_style_bg_color(but1, MY_COLOR_MAGENTA, LV_STATE_DEFAULT);      // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  label1 = lv_label_create(but1);                                           // 创建标签
  lv_obj_align(label1, LV_ALIGN_LEFT_MID, 12, 0);                           // 居中对齐
  lv_obj_set_style_text_align(label1, LV_ALIGN_CENTER, 0);// 对齐方式
  lv_obj_set_width(label1, 72);
  lv_obj_set_style_text_color(label1, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  obj_name1.clear();
  if (eep_ledEn) obj_name1 = F("已启用");
  else           obj_name1 = F("已停用");
  lv_label_set_text(label1, obj_name1.c_str());                              // 标签文本
  lv_obj_add_event_cb(but1, display_frontLightSet_event3, LV_EVENT_PRESSED, NULL); // 使能切换
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);       // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);

  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 25); // 设置大小
  // lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 5 * 46);                    // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_BLUE, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  label_share[0] = lv_label_create(but1);                                           // 创建标签
  lv_obj_align(label_share[0], LV_ALIGN_CENTER, 0, 0);                              // 对齐方式
  lv_label_set_text_fmt(label_share[0], "%.2fLux", shareNum_f[0]);                  // 光强度
  lv_obj_set_style_text_color(label_share[0], MY_COLOR_WHITE, LV_STATE_DEFAULT);
  // lv_obj_add_event_cb(but1, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);
  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(readAmbientLight_timer_cb, 2000, NULL); // 定时更新

  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 25);                                               // 设置大小
  //lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 5 * 46);                             // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_RED, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but1, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but1, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but1, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but1, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but1, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  label1 = lv_label_create(but1);                                             // 创建标签
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, 0);                                 // 对齐方式
  lv_label_set_text(label1, "退出"); // 标签文本
  lv_obj_set_style_text_color(label1, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  lv_obj_add_event_cb(but1, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but1, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);   // 添加聚焦动画
  lv_obj_add_event_cb(but1, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but1);
  
}

//****** 休眠设置设置
void display_sleepSet_switchStatusChange_event_cb(lv_event_t *e) // 开关状态更改
{
  //Serial.println("开关状态更改");
  buzzerSen(30);
  lv_obj_t *obj = lv_event_get_target_obj(e);           // 获取触发的对象
  bool *data = (bool *)lv_event_get_user_data(e);       // 获取输入的值
  bool state = lv_obj_has_state(obj, LV_STATE_CHECKED); // 切换状态
  *data = state;                                        // 状态保存
  eepSaveState = 1;                                     // 标记保存eeprom
}
void numericalChange_event_cb(lv_event_t *e) // 数值更改事件回调
{
  lv_event_code_t code = lv_event_get_code(e);
  uint8_t key = lv_indev_get_key(lv_indev_active());
  if (key == LV_KEY_ENTER) return;

  lv_obj_t *obj = lv_event_get_target_obj(e);
  // 检查动画是否播放完毕
  lv_anim_t *a = lv_anim_get(obj, NULL); // button_width_shrink_anim_cb
  if (a == NULL) button_width_shrink_anim_init(obj);
    
  lv_obj_t *child = lv_obj_get_child(obj, 1);
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];

  // 时钟界面休眠时间、其他界面休眠时间、空气质量界面休眠时间
  if (key == LV_KEY_LEFT) // 减
  {
    if (*sm0.num_u8[i] == sm0.min[i])
      *sm0.num_u8[i] = sm0.max[i];
    else
      *sm0.num_u8[i] -= sm0.step[i];
  }
  else if (key == LV_KEY_RIGHT) // 加
  {
    if (*sm0.num_u8[i] == sm0.max[i])
      *sm0.num_u8[i] = sm0.min[i];
    else
      *sm0.num_u8[i] += sm0.step[i];
  }

/*
  if (*sm0.num_u8[i] > sm0.max[i]) // 限制最大值
    *sm0.num_u8[i] = sm0.min[i];
  else if (*sm0.num_u8[i] < sm0.min[i]) // 限制最小值
    *sm0.num_u8[i] = sm0.max[i];
*/

  // 整合标签内容
  // 时钟界面休眠时间、其他界面休眠时间、空气质量界面休眠时间
  String text = String(*sm0.num_u8[i]);
  text += sm0.unit[i];

  lv_label_set_text(child, text.c_str()); // 标签文本
}
void button_remove_anim_completed_cb(lv_anim_t *a) // 退出编辑状态的动画完成事件 
{
  lv_obj_remove_event_cb((lv_obj_t *)a->var, numericalChange_event_cb); // 移除加减事件
  // structClear((unsigned char *)&sm0, sizeof(sm0)); // 清空结构体
}
void display_sleepSet_edit_event(lv_event_t *e) //背景下拉进入编辑状态
{
  static uint32_t mainSetEditAnimTime = 0;
  if (millis() - mainSetEditAnimTime < 400) return;
  mainSetEditAnimTime = millis();
  
  //检查动画是否播放中，播放中就退出
  /*lv_anim_t *c = lv_anim_get(obj, NULL);
  Serial.printf("c1:%p\n", c);
  if (c != NULL) return;*/

  lv_obj_t *obj = lv_event_get_target_obj(e); // 即按钮对象
  lv_obj_t *child = lv_obj_get_child(obj, 0);  // 即文本描述标签
  lv_obj_t *child1 = lv_obj_get_child(obj, 1); // 即文本变量标签
  lv_event_code_t code = lv_event_get_code(e);
  uint8_t key = lv_indev_get_key(lv_indev_active());
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  uint8_t i = data[0];

  //****** 按钮按下和按钮加减
  Serial.printf("编辑模式:%d\n", i);

  buzzerSen(30);

  // 创建动画时间线
  lv_anim_timeline_t *anim_timeline = lv_anim_timeline_create();
  uint16_t h = lv_obj_get_height(obj);
  lv_anim_t a;
  lv_anim_init(&a);
  lv_anim_set_var(&a, obj);
  lv_anim_set_exec_cb(&a, button_height_expand_anim_cb);
  lv_anim_set_duration(&a, 200);
  lv_anim_set_path_cb(&a, lv_anim_path_bounce); // 设置变化特效
  
  if (page.keyMode == KEY_MODE_PN) // 进入编辑状态
  {
    page.keyMode = KEY_MODE_RL;

    // 添加数值加减回调
    lv_obj_add_event_cb(obj, numericalChange_event_cb, LV_EVENT_KEY, data);

    lv_obj_set_style_bg_color(obj, MY_COLOR_MAGENTA, 0);   // 设置背景颜色
    lv_obj_set_style_text_color(child, MY_COLOR_WHITE, 0); // 设置文本颜色
    lv_obj_align(child, LV_ALIGN_TOP_MID, 0, -6);          // 对齐方式

    // 整合标签内容
    // 时钟界面休眠时间、其他界面休眠时间、空气质量界面休眠时间
    String text = String(*sm0.num_u8[i]);
    text += sm0.unit[i];

    lv_obj_t *label = lv_label_create(obj);          // 创建标签
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 25); // 对齐方式
    lv_label_set_text(label, text.c_str());          // 标签文本

    lv_anim_set_values(&a, h, h + 24); // 设置动画的开始值和结束值
    lv_anim_t b;
    lv_anim_init(&b);                                     // 动画初始化
    lv_anim_set_var(&b, label);                           // 设置需要动画的对象
    lv_anim_set_values(&b, 25, 6);                        // 设置动画的开始值和结束值
    lv_anim_set_duration(&b, 240);                        // 设置动画的持续时间
    lv_anim_set_exec_cb(&b, button_editNumEject_anim_cb); // 设置需要变化的值
    lv_anim_set_path_cb(&b, lv_anim_path_bounce);         // 设置变化特效
    //lv_anim_set_completed_cb(&b, markAnimIdle);           // 设置动画完成时的函数调用
    lv_anim_timeline_add(anim_timeline, 50, &b);          // 添加动画时间线
  }
  else // 退出编辑状态
  {
    page.keyMode = KEY_MODE_PN;
    
    lv_obj_set_style_bg_color(obj, MY_COLOR_YELLOW, 0);      // 设置背景颜色
    lv_obj_set_style_text_color(child, MY_COLOR_BLACK, 0); // 设置文本颜色
    lv_obj_align(child, LV_ALIGN_CENTER, 0, 0);            // 对齐方式

    lv_obj_delete_async(child1);// 删除新建的标签

    lv_anim_set_values(&a, h, h - 24);                    // 设置动画的开始值和结束值
    lv_anim_set_completed_cb(&a, button_remove_anim_completed_cb); // 设置动画完成时的函数调用

    eepSaveState = 1; // 退出时标记保存eeprom
  }

  lv_anim_timeline_add(anim_timeline, 0, &a); // 添加动画时间线
  lv_anim_timeline_start(anim_timeline);      // 开始动画时间线

  LV_UNUSED(obj);
  LV_UNUSED(child);
  LV_UNUSED(child1);
}
void display_sleepSet_init()
{
  eepSavePage(page_sleepSet, 0);

  //****** 可调数值初始化
  uint8_t j = 0;
  sm0.num_u8[j++] = &eep_clockSleep;
  sm0.num_u8[j++] = &eep_otherSleep;
  sm0.num_u8[j++] = &eep_airSleep;
  j = 0;
  sm0.unit[j++] = F("秒");
  sm0.unit[j++] = F("秒");
  sm0.unit[j++] = F("分钟");
  j = 0;
  sm0.step[j++] = 5; // 加减的步进值
  sm0.step[j++] = 5; // 加减的步进值
  sm0.step[j++] = 5; // 加减的步进值
  j = 0;
  sm0.min[j++] = 5;  // 最小值
  sm0.min[j++] = 5;  // 最小值
  sm0.min[j++] = 10; // 最小值
  j = 0;
  sm0.max[j++] = 255; // 最小值
  sm0.max[j++] = 255; // 最小值
  sm0.max[j++] = 255; // 最小值

  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF); //关闭滑动条
  //lv_obj_set_scroll_snap_y(page.p[index], LV_SCROLL_SNAP_CENTER);
  lv_obj_set_style_pad_top(page.p[index],5, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 5, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[index], LV_FLEX_FLOW_COLUMN);
  //参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值    控制Y轴排布
  //参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER    
  //参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。             控制X轴排布
  lv_obj_set_flex_align(page.p[index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  //lv_obj_set_flex_grow(page2, 5);
  
  // 设置垂直滚动结束时捕捉子对象的位置
  lv_obj_set_scroll_snap_y(page.p[index], LV_SCROLL_SNAP_CENTER);  // 不要对齐，留在原地

  String obj_text[9];

  uint8_t count = 0;
  obj_text[count++] = F("时钟界面休眠时间");
  obj_text[count++] = F("其他界面休眠时间");
  obj_text[count++] = F("空气质量休眠时间");

  lv_obj_t *but[count];
  lv_obj_t *label[count];
  for (uint8_t i = 0; i < count; i++)
  {
    // 将项目添加到列
    but[i] = lv_button_create(page.p[index]);
    uint16_t text_width = lv_text_get_width(obj_text[i].c_str(), obj_text[i].length(), lv_obj_get_style_text_font(but[i], 0), 0);
    uint16_t text_width_zl =  text_width / 65;
    lv_obj_set_size(but[i], 68, 22 + (text_width_zl * 20));
    //lv_obj_align(but[i], LV_ALIGN_CENTER, 0, 0); // 对齐方式
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_ANY); // 移除阴影
     // 可编辑按钮是黄色 
    lv_obj_set_style_bg_color(but[i], MY_COLOR_YELLOW, 0);

    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色

    lv_obj_set_style_border_width(but[i], 1, 0);                // 设置边框宽度
    lv_obj_set_style_border_color(but[i], MY_COLOR_MAGENTA, 0); // 设置边框颜色

    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    lv_obj_set_width(label[i], 66);
    lv_obj_align(label[i], LV_ALIGN_CENTER, 0, 0);        // 对齐方式
    lv_label_set_long_mode(label[i], LV_LABEL_LONG_WRAP); // 设置文本长字符模式
    lv_obj_set_style_text_align(label[i], LV_TEXT_ALIGN_CENTER, 0);
    // lv_label_set_text_fmt(label[i], obj_text[i].c_str(), timeArray[i]); // 标签文本
    lv_label_set_text(label[i], obj_text[i].c_str()); // 标签文本
    lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);

    lv_group_add_obj(group_my, but[i]); // 将对象邦定到组
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 按钮聚焦动画
  }

  count = 0;
  obj_text[count++] = F("抬手唤醒");
  obj_text[count++] = F("拨轮唤醒");
  obj_text[count++] = F("时钟界面息屏");
  obj_text[count++] = F("其他界面息屏");
  obj_text[count++] = F("普通休眠壁纸");
  obj_text[count++] = F("低电休眠壁纸");
  lv_obj_t *sw[count]; 
  lv_obj_t *box[count];
  for (uint8_t i = 0; i < count; i++)
  {
    // 使用新样式创建标签
    box[i] = lv_obj_create(page.p[index]);
    lv_obj_set_size(box[i] , 72, 25);
    lv_obj_align(box[i], LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(box[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);    // 设置背景颜色
    lv_obj_add_style(box[i], &style_shadow, LV_STATE_DEFAULT);              // 设置阴影样式
    lv_obj_set_style_pad_all(box[i], 0, 0);                                 // 设置边界
    lv_obj_set_style_border_color(box[i], MY_COLOR_BLUE, LV_STATE_DEFAULT); // 边框颜色
    lv_obj_set_style_border_width(box[i], 2, LV_STATE_DEFAULT);             // 边框宽度
    lv_obj_set_style_radius(box[i], 4, LV_STATE_DEFAULT);                   // 设置圆角
    lv_obj_set_scrollbar_mode(box[i], LV_SCROLLBAR_MODE_OFF);               // 关闭滑动条

    // 使用新样式创建标签
    lv_obj_t *label = lv_label_create(box[i]);
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_style_anim_duration(label, 3000, 0);
    lv_obj_set_width(label, 43);
    lv_label_set_text(label, obj_text[i].c_str());
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 1, 0);

    // 创建开关
    sw[i] = lv_switch_create(box[i]);
    lv_obj_set_size(sw[i], 20, 11);
    lv_obj_align(sw[i], LV_ALIGN_RIGHT_MID, -3, 0);
    lv_obj_set_style_bg_color(sw[i], MY_COLOR_RED, LV_PART_MAIN);                           // 开关 关闭的背景颜色
    lv_obj_set_style_bg_color(sw[i], MY_COLOR_GREEN, LV_PART_INDICATOR | LV_STATE_CHECKED); // 开关 打开的背景颜色
    lv_obj_set_style_bg_color(sw[i], MY_COLOR_WHITE, LV_PART_KNOB);                         // 手柄颜色

    // 设置聚焦样式
    lv_obj_set_style_outline_width(sw[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(sw[i], 1, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(sw[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(sw[i], 0, LV_PART_MAIN);                    // 失焦时的宽度
    lv_obj_set_style_outline_color(sw[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色

    lv_group_add_obj(group_my, sw[i]); // 将对象邦定到组
    lv_obj_add_event_cb(sw[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 聚焦动画
  }
  
  // 根据eep里的值设置初始开关状态
  if (eep_WU_TaiShou)          lv_obj_add_state(sw[0], LV_STATE_CHECKED);
  if (eep_WU_AnDong)           lv_obj_add_state(sw[1], LV_STATE_CHECKED);
  if (eep_clockSleepOffScreen) lv_obj_add_state(sw[2], LV_STATE_CHECKED);
  if (eep_otherSleepOffScreen) lv_obj_add_state(sw[3], LV_STATE_CHECKED);
  if (eep_sleepPicEn)          lv_obj_add_state(sw[4], LV_STATE_CHECKED);
  if (eep_batSleepPicEn)       lv_obj_add_state(sw[5], LV_STATE_CHECKED);

  lv_obj_t *backBut = lv_button_create(page.p[page.index]);
  lv_obj_set_size(backBut, 72, 25); // 设置大小
  // lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 5 * 46);                             // 设置对齐方式
  lv_obj_set_style_bg_color(backBut, MY_COLOR_RED, LV_STATE_DEFAULT);          // 设置背景颜色
  lv_obj_add_style(backBut, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(backBut, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(backBut, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(backBut, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(backBut, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(backBut, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(backBut, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(backBut, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  //lv_obj_set_style_pad_top(backBut, 2, 0); // 设置边距
  //lv_obj_set_style_pad_bottom(backBut, 2, 0); // 设置边距
  //lv_obj_set_style_pad_left(backBut, 20, 0); // 设置边距
  //lv_obj_set_style_pad_right(backBut, 20, 0); // 设置边距
  lv_obj_t * backLabel = lv_label_create(backBut); // 创建标签
  lv_obj_align(backLabel, LV_ALIGN_CENTER, 0, 0); // 对齐方式
  lv_label_set_text(backLabel, "退出");           // 标签文本
  lv_obj_set_style_text_color(backLabel, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  lv_obj_add_event_cb(backBut, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(backBut, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(backBut, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_group_add_obj(group_my, backBut);

  // 将对象邦定到组
  //lv_group_add_obj(group_my, page.p[index]);

  // 切换数值编辑模式
  lv_obj_add_event_cb(but[0], display_sleepSet_edit_event, LV_EVENT_PRESSED, &num[0]); // 时间界面休眠时间
  lv_obj_add_event_cb(but[1], display_sleepSet_edit_event, LV_EVENT_PRESSED, &num[1]); // 其他界面休眠时间
  lv_obj_add_event_cb(but[2], display_sleepSet_edit_event, LV_EVENT_PRESSED, &num[2]); // 空气界面休眠时间

  // 开关状态切换
  lv_obj_add_event_cb(sw[0], display_sleepSet_switchStatusChange_event_cb, LV_EVENT_VALUE_CHANGED, &eep_WU_TaiShou);          // 开关改变触发时的回调函数
  lv_obj_add_event_cb(sw[1], display_sleepSet_switchStatusChange_event_cb, LV_EVENT_VALUE_CHANGED, &eep_WU_AnDong);           // 开关改变触发时的回调函数
  lv_obj_add_event_cb(sw[2], display_sleepSet_switchStatusChange_event_cb, LV_EVENT_VALUE_CHANGED, &eep_clockSleepOffScreen); // 开关改变触发时的回调函数
  lv_obj_add_event_cb(sw[3], display_sleepSet_switchStatusChange_event_cb, LV_EVENT_VALUE_CHANGED, &eep_otherSleepOffScreen); // 开关改变触发时的回调函数
  lv_obj_add_event_cb(sw[4], display_sleepSet_switchStatusChange_event_cb, LV_EVENT_VALUE_CHANGED, &eep_sleepPicEn);          // 开关改变触发时的回调函数
  lv_obj_add_event_cb(sw[5], display_sleepSet_switchStatusChange_event_cb, LV_EVENT_VALUE_CHANGED, &eep_batSleepPicEn);       // 开关改变触发时的回调函数

  lv_group_focus_obj(but[0]); // 将焦点设为第一个子对象处
}

//****** 更新检查界面
void display_checkUpdate_event0(lv_event_t *e)
{
  my_msgbox_send(F("固件更新"), F("4MB不支持"), 1500);
}
void display_checkUpdate_init(String ver, String content)
{
  eepSavePage(page_checkUpdate, 0);
  LV_FONT_DECLARE(MISans_Normal_12px);

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 3, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  //参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值 控制Y轴排布
  //参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER    
  //参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。 控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  //lv_obj_set_flex_grow(page.p[page.index], 3); //设置对象生长的宽度或高度（在主轴上），以填充自由空间
  lv_obj_set_style_pad_row(page.p[page.index], 5, LV_STATE_DEFAULT); // 设置行间距为5像素

  String verCur;
  verCur += version;
  verCur += "->" + ver;
  lv_obj_t *but_ver = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but_ver, 72, 20); // 设置大小
  lv_obj_set_style_bg_color(but_ver, MY_COLOR_RED, LV_STATE_DEFAULT);           // 设置背景颜色
  lv_obj_add_style(but_ver, &style_shadow, LV_STATE_DEFAULT);                   // 设置阴影样式
  lv_obj_add_style(but_ver, &style_squareShape, LV_STATE_DEFAULT);              // 设置方型样式
  lv_obj_set_style_outline_width(but_ver, 2, LV_STATE_FOCUS_KEY);               // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_ver, 0, LV_STATE_FOCUS_KEY);                 // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_ver, LV_OPA_100, LV_STATE_FOCUS_KEY);        // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_ver, 0, LV_STATE_DEFAULT);                 // 失焦时的宽度
  lv_obj_set_style_outline_color(but_ver, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);  // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_ver, LV_SCROLLBAR_MODE_OFF);                    // 关闭滑动条
  lv_obj_t *label_ver = lv_label_create(but_ver);                               // 创建标签
  lv_obj_align(label_ver, LV_ALIGN_CENTER, 0, 0);                               // 对齐方式
  lv_label_set_text(label_ver, verCur.c_str());                                 // 标签文本
  lv_obj_set_style_text_font(label_ver, &MISans_Normal_12px, 0);                // LV_FONT_DECLARE(MISans_Normal_12px);

  lv_obj_add_event_cb(but_ver, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(but_ver, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);

  lv_group_add_obj(group_my, but_ver);

  // 检查内容有多少行
  //Serial.printf("content.length():%d\n",content.length());
  uint8_t line = 1;
  for (uint16_t i = 0; i < content.length(); i++)
    if (content[i] == '\n')
      line++;
  
  // 分割内容
  uint8_t pos = 0;
  String obj_name[line];
  for (uint16_t i = 0; i < content.length(); i++)
  {
    if (content[i] == '\n') pos++;
    else obj_name[pos] += content[i];
  }
  //for (uint8_t i = 0; i < line; i++)
    //Serial.printf("obj_name[%d]:%s\n", i, obj_name[i].c_str());
 

  lv_obj_t *but[line];
  lv_obj_t *label[line];
  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
  for (uint8_t i = 0; i < line; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[page.index]);
    lv_obj_set_size(but[i], 72, 25);                                            // 设置大小
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条

    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    uint16_t text_width = lv_text_get_width(obj_name[i].c_str(), obj_name[i].length(), lv_obj_get_style_text_font(but[i], 0), 0);
    //Serial.printf("text_width:%d\n",text_width);
    lv_label_set_long_mode(label[i], LV_LABEL_LONG_SCROLL_CIRCULAR); // 长字符模式
    lv_obj_set_style_anim_duration(label[i], text_width * 35, 0);
    lv_obj_set_width(label[i], 72);
    lv_obj_align(label[i], LV_ALIGN_CENTER, 0, 0);    // 对齐方式
    lv_label_set_text(label[i], obj_name[i].c_str()); // 标签文本
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);

    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
  }

  lv_obj_t *but_update = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but_update, 72, 25);                                                   // 设置大小
  lv_obj_set_style_bg_color(but_update, MY_COLOR_RED, LV_STATE_DEFAULT);                 // 设置背景颜色
  lv_obj_add_style(but_update, &style_shadow, LV_STATE_DEFAULT);                         // 设置阴影样式
  lv_obj_add_style(but_update, &style_squareShape, LV_STATE_DEFAULT);                    // 设置方型样式
  lv_obj_set_style_outline_width(but_update, 2, LV_STATE_FOCUS_KEY);                     // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_update, 0, LV_STATE_FOCUS_KEY);                       // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_update, LV_OPA_100, LV_STATE_FOCUS_KEY);              // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_update, 0, LV_STATE_DEFAULT);                       // 失焦时的宽度
  lv_obj_set_style_outline_color(but_update, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);        // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_update, LV_SCROLLBAR_MODE_OFF);                          // 关闭滑动条
  lv_obj_t *label_update = lv_label_create(but_update);                                  // 创建标签
  lv_obj_align(label_update, LV_ALIGN_CENTER, 0, 0);                                     // 对齐方式
  lv_label_set_text(label_update, String(F("更新")).c_str());                            // 标签文本
  lv_obj_add_event_cb(but_update, display_checkUpdate_event0, LV_EVENT_PRESSED, NULL);   // 进入回调
  lv_obj_add_event_cb(but_update, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);       // 添加聚焦动画
  lv_obj_add_event_cb(but_update, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but_update);

  lv_obj_t *but_exit = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but_exit, 72, 25);                                               // 设置大小
  lv_obj_set_style_bg_color(but_exit, MY_COLOR_MAGENTA, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but_exit, &style_shadow, LV_STATE_DEFAULT);                     // 设置阴影样式
  lv_obj_add_style(but_exit, &style_squareShape, LV_STATE_DEFAULT);                // 设置方型样式
  lv_obj_set_style_outline_width(but_exit, 2, LV_STATE_FOCUS_KEY);                 // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_exit, 0, LV_STATE_FOCUS_KEY);                   // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_exit, LV_OPA_100, LV_STATE_FOCUS_KEY);          // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_exit, 0, LV_STATE_DEFAULT);                   // 失焦时的宽度
  lv_obj_set_style_outline_color(but_exit, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY);    // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_exit, LV_SCROLLBAR_MODE_OFF);                      // 关闭滑动条
  lv_obj_t *label_exit = lv_label_create(but_exit);                                // 创建标签
  lv_obj_align(label_exit, LV_ALIGN_CENTER, 0, 0);                                 // 对齐方式
  lv_label_set_text(label_exit, String(F("退出")).c_str());                        // 标签文本
  lv_obj_add_event_cb(but_exit, backPage_mainSet_event, LV_EVENT_PRESSED, NULL);   // 退出回调
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);   // 添加聚焦动画
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but_exit);

  //lv_group_focus_obj(but[0]);
}

//****** 串口空气质量界面
void uartAir_msgbox_cb(lv_event_t *e) 
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出
  {
    mqtt_send = 0; // 发送关闭
    bitWrite(backgroundTask, BGT_AIR_READ, 0); // 关闭空气质量读取任务
    bitWrite(backgroundTask, BGT_MQTT, 0);     // 关闭MQTT任务
    offLVGLTimer();                            // 关闭LVGL定时器
    my_msgbox_exit(10);                        // 退出弹窗
    exitToMainSet();                           // 退出至设置菜单
  }
  else if (data[0] == 1) // 返回
  {
   my_msgbox_exit(0); // 退出弹窗
  }
  else if (data[0] == 2) // 发送
  {
    mqtt_send = 1;
    my_msgbox_exit(0); // 退出弹窗
  }
}
void display_uartAir_event_msgbox(lv_event_t *e)  // 当屏幕被聚焦时，弹出退出弹窗
{
  my_msgbox_send(F("空气质量"), F("是否退出"), 0, F("退出\n返回\n发送\n"), uartAir_msgbox_cb);
}
void update_uartAir_timer_cb(lv_timer_t *time) // 定时更新加速度数据
{
  if (eep_disPage != page_uartAir)
  {
    bitWrite(backgroundTask, BGT_AIR_READ, 0); // 标记关闭
    return;
  }

  lv_label_set_text(label_share[0], String(UART_TEMP).c_str());
  lv_label_set_text(label_share[1], String(UART_HUMI).c_str());
  lv_label_set_text(label_share[2], String(UART_TVOC.data, 2).c_str());
  lv_label_set_text(label_share[3], String(UART_HCHO.data, 2).c_str());
  lv_label_set_text(label_share[4], String(UART_CO2.data, 0).c_str());
}
void display_uartAir_init()
{
  LV_FONT_DECLARE(airQualityIcon_24px);

  // 创建定时器并保存句柄
  lvTimer_share[0] = lv_timer_create(update_uartAir_timer_cb, 1000, NULL); // 定时更新

  eepSavePage(page_uartAir, 0);

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式

  // 将对象邦定到组
  lv_group_add_obj(group_my, page.p[page.index]);
  // 聚焦触发 弹出退出返回框
  lv_obj_add_event_cb(page.p[page.index], display_uartAir_event_msgbox, LV_EVENT_KEY, NULL);

  lv_obj_t *but1;
  lv_obj_t *label1;

  String str = F("空气质量");
  but1 = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but1, 72, 20);                                            // 设置大小
  lv_obj_align(but1, LV_ALIGN_TOP_MID, 0, 0);                               // 设置对齐方式
  lv_obj_set_style_bg_color(but1, MY_COLOR_CYAN, LV_STATE_DEFAULT);         // 设置背景颜色
  lv_obj_add_style(but1, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but1, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_scrollbar_mode(but1, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  label1 = lv_label_create(but1);                                           // 创建标签
  lv_obj_set_style_text_color(label1, MY_COLOR_BLACK, LV_STATE_DEFAULT);    // 字体颜色
  lv_obj_align(label1, LV_ALIGN_CENTER, 0, 1);                              // 对齐方式
  lv_label_set_text(label1, str.c_str());                                   // 标签文本

  //********** 温湿度图标和数据
  lv_obj_t *tempHumi_bg = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(tempHumi_bg, 72, 45);                          // 设置大小
  lv_obj_align(tempHumi_bg, LV_ALIGN_TOP_MID, 0, 20);            // 设置对齐方式
  lv_obj_set_style_bg_color(tempHumi_bg, MY_COLOR_WHITE, 0);     // 设置背景颜色
  lv_obj_add_style(tempHumi_bg, &style_shadow, 0);               // 设置阴影样式
  lv_obj_add_style(tempHumi_bg, &style_squareShape, 0);          // 设置方型样式
  lv_obj_set_scrollbar_mode(tempHumi_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_set_style_border_color(tempHumi_bg, MY_COLOR_CYAN, 0);  // 设置边框颜色
  lv_obj_set_style_border_width(tempHumi_bg, 1, 0);              // 设置边框宽度

  lv_obj_t *tempIcon = lv_label_create(tempHumi_bg);             // 创建标签
  lv_obj_set_style_text_color(tempIcon, MY_COLOR_BLACK, 0);      // 字体颜色
  lv_obj_align(tempIcon, LV_ALIGN_TOP_LEFT, 4, 0);               // 对齐方式
  lv_label_set_text(tempIcon, LV_SYMBOL_TEMP);                   // 标签文本
  lv_obj_set_style_text_font(tempIcon, &airQualityIcon_24px, 0);

  lv_obj_t *humiIcon = lv_label_create(tempHumi_bg);        // 创建标签
  lv_obj_set_style_text_color(humiIcon, MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_align(humiIcon, LV_ALIGN_TOP_RIGHT, -4, 0);         // 对齐方式
  lv_label_set_text(humiIcon, LV_SYMBOL_HUMI);              // 标签文本
  lv_obj_set_style_text_font(humiIcon, &airQualityIcon_24px, 0);

  label_share[0] = lv_label_create(tempHumi_bg);                  // 创建标签 temp
  lv_obj_set_style_text_color(label_share[0], MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_align(label_share[0], LV_ALIGN_CENTER, -18, 13);         // 对齐方式
  lv_label_set_text(label_share[0], String(F("0")).c_str());     // 标签文本

  label_share[1] = lv_label_create(tempHumi_bg);                  // 创建标签 humi
  lv_obj_set_style_text_color(label_share[1], MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_align(label_share[1], LV_ALIGN_CENTER, 18, 13);          // 对齐方式
  lv_label_set_text(label_share[1], String(F("0")).c_str());     // 标签文本

  //********** 温湿度图标和数据
  lv_obj_t *VOC_bg = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(VOC_bg, 72, 45);                          // 设置大小
  lv_obj_align(VOC_bg, LV_ALIGN_TOP_MID, 0, 65);            // 设置对齐方式
  lv_obj_set_style_bg_color(VOC_bg, MY_COLOR_BLACK, 0);     // 设置背景颜色
  lv_obj_add_style(VOC_bg, &style_shadow, 0);               // 设置阴影样式
  lv_obj_add_style(VOC_bg, &style_squareShape, 0);          // 设置方型样式
  lv_obj_set_scrollbar_mode(VOC_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_set_style_border_color(VOC_bg, MY_COLOR_CYAN, 0);  // 设置边框颜色
  lv_obj_set_style_border_width(VOC_bg, 1, 0);              // 设置边框宽度

  lv_obj_t *TVOCIcon = lv_label_create(VOC_bg);             // 创建标签
  lv_obj_set_style_text_color(TVOCIcon, MY_COLOR_WHITE, 0); // 字体颜色
  lv_obj_align(TVOCIcon, LV_ALIGN_TOP_LEFT, 4, 1);          // 对齐方式
  lv_label_set_text(TVOCIcon, LV_SYMBOL_TVOC);              // 标签文本
  lv_obj_set_style_text_font(TVOCIcon, &airQualityIcon_24px, 0);

  lv_obj_t *HCHOIcon = lv_label_create(VOC_bg);             // 创建标签
  lv_obj_set_style_text_color(HCHOIcon, MY_COLOR_WHITE, 0); // 字体颜色
  lv_obj_align(HCHOIcon, LV_ALIGN_TOP_RIGHT, -4, 1);        // 对齐方式
  lv_label_set_text(HCHOIcon, LV_SYMBOL_HCHO);              // 标签文本
  lv_obj_set_style_text_font(HCHOIcon, &airQualityIcon_24px, 0);

  label_share[2] = lv_label_create(VOC_bg);                       // 创建标签 TVOC
  lv_obj_set_style_text_color(label_share[2], MY_COLOR_WHITE, 0); // 字体颜色
  lv_obj_align(label_share[2], LV_ALIGN_CENTER, -18, 14);         // 对齐方式
  lv_label_set_text(label_share[2], String(F("0.00")).c_str());   // 标签文本

  label_share[3] = lv_label_create(VOC_bg);                       // 创建标签 HCHO
  lv_obj_set_style_text_color(label_share[3], MY_COLOR_WHITE, 0); // 字体颜色
  lv_obj_align(label_share[3], LV_ALIGN_CENTER, 18, 14);          // 对齐方式
  lv_label_set_text(label_share[3], String(F("0.00")).c_str());   // 标签文本

  //********** 温湿度图标和数据
  lv_obj_t *co2_bg = lv_obj_create(page.p[page.index]);
  lv_obj_set_size(co2_bg, 72, 34);                          // 设置大小
  lv_obj_align(co2_bg, LV_ALIGN_TOP_MID, 0, 110);           // 设置对齐方式
  lv_obj_set_style_bg_color(co2_bg, MY_COLOR_WHITE, 0);     // 设置背景颜色
  lv_obj_add_style(co2_bg, &style_shadow, 0);               // 设置阴影样式
  lv_obj_add_style(co2_bg, &style_squareShape, 0);          // 设置方型样式
  lv_obj_set_scrollbar_mode(co2_bg, LV_SCROLLBAR_MODE_OFF); // 关闭滑动条
  lv_obj_set_style_border_color(co2_bg, MY_COLOR_CYAN, 0);  // 设置边框颜色
  lv_obj_set_style_border_width(co2_bg, 1, 0);              // 设置边框宽度

  lv_obj_t *co2Icon = lv_label_create(co2_bg);             // 创建标签
  lv_obj_set_style_text_color(co2Icon, MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_align(co2Icon, LV_ALIGN_LEFT_MID, 5, 0);          // 对齐方式
  lv_label_set_text(co2Icon, LV_SYMBOL_CO2);              // 标签文本
  lv_obj_set_style_text_font(co2Icon, &airQualityIcon_24px, 0);

  label_share[4] = lv_label_create(co2_bg);                       // 创建标签 co2
  lv_obj_set_style_text_color(label_share[4], MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_align(label_share[4], LV_ALIGN_RIGHT_MID, -5, 3);        // 对齐方式
  lv_label_set_text(label_share[4], String(F("000")).c_str());    // 标签文本
}

//****** WIFI选择主页
void openWifiSelectMenu_event(lv_event_t *e) // 打开WiFi选择菜单
{
  focusPosOld_save(); // 保存焦点
  display_wifiSelectMenu_init();
}
void display_wifiSelect_init(String content)
{
  eepSavePage(page_wifiSelect, 0);

  pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[page.index], 4, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[page.index], 3, LV_STATE_DEFAULT);

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  //参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值 控制Y轴排布
  //参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER    
  //参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。 控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  //lv_obj_set_flex_grow(page.p[page.index], 3); //设置对象生长的宽度或高度（在主轴上），以填充自由空间
  lv_obj_set_style_pad_row(page.p[page.index], 5, LV_STATE_DEFAULT); // 设置行间距为5像素

  // 检查内容有多少行
  uint8_t line = 1;
  for (uint8_t i = 0; i < content.length(); i++)
    if (content[i] == '\n')
      if (i != content.length() - 1)
        line++;

  // 提取内容
  uint8_t pos = 0;
  bool nameState = 1; // 换行
  String obj_name[line];
  for (uint8_t i = 0; i < content.length(); i++)
  {
    if (content[i] == '\n')
    {
      pos++;
      nameState = 1;
    }
    else if (content[i] != '\r')
    {
      // 剔除“隔”字
      if (content[i] == 0xe9 && content[i + 1] == 0x9a && content[i + 2] == 0x94)
      {
        nameState = 0;
        i += 2;
      }
      if (nameState)
        obj_name[pos] += content[i];
    }
  }

  /*for (uint8_t i = 0; i < line; i++)
  {
    Serial.printf("obj_name[%d]:%s\n", i, obj_name[i].c_str());
  }*/

  lv_obj_t *but[line];
  lv_obj_t *label[line];
  lv_color_t color[6] = {MY_COLOR_CYAN, MY_COLOR_GREEN, MY_COLOR_YELLOW,
                         MY_COLOR_MAGENTA, MY_COLOR_BLUE, MY_COLOR_RED};
  for (uint8_t i = 0; i < line; i++)
  {
    // 按钮对象
    but[i] = lv_button_create(page.p[page.index]);
    lv_obj_set_size(but[i], 72, 22);                                            // 设置大小
    lv_obj_set_style_bg_color(but[i], color[i % 6], LV_STATE_DEFAULT);          // 设置背景颜色
    lv_obj_add_style(but[i], &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
    lv_obj_add_style(but[i], &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
    lv_obj_set_style_outline_width(but[i], 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
    lv_obj_set_style_outline_pad(but[i], 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
    lv_obj_set_style_outline_opa(but[i], LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
    lv_obj_set_style_outline_width(but[i], 0, LV_STATE_DEFAULT);                // 失焦时的宽度
    lv_obj_set_style_outline_color(but[i], MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
    lv_obj_set_scrollbar_mode(but[i], LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条

    // 标签对象
    label[i] = lv_label_create(but[i]); // 创建标签
    lv_obj_align(label[i], LV_ALIGN_CENTER, 0, 0);    // 对齐方式
    lv_label_set_text(label[i], obj_name[i].c_str()); // 标签文本
    uint16_t text_width = lv_text_get_width(obj_name[i].c_str(), obj_name[i].length(), lv_obj_get_style_text_font(but[i], 0), 0);
    if (text_width > 72)
    {
      lv_obj_set_width(label[i], 72);
      lv_obj_set_style_anim_duration(label[i], text_width * 35, 0);
      lv_label_set_long_mode(label[i], LV_LABEL_LONG_SCROLL_CIRCULAR); // 长字符模式
    }
    if ((i % 6) < 3)
      lv_obj_set_style_text_color(label[i], MY_COLOR_BLACK, LV_STATE_DEFAULT);
    else
      lv_obj_set_style_text_color(label[i], MY_COLOR_WHITE, LV_STATE_DEFAULT);

    // 将对象邦定到组
    lv_group_add_obj(group_my, but[i]);
    // 添加按钮聚焦动画
    lv_obj_add_event_cb(but[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    // 打开菜单回调
    lv_obj_add_event_cb(but[i], openWifiSelectMenu_event, LV_EVENT_PRESSED, NULL); 
  }

  lv_obj_t *but_exit = lv_button_create(page.p[page.index]);
  lv_obj_set_size(but_exit, 72, 25);                                            // 设置大小
  lv_obj_set_style_bg_color(but_exit, color[line % 6], LV_STATE_DEFAULT);       // 设置背景颜色
  lv_obj_add_style(but_exit, &style_shadow, LV_STATE_DEFAULT);                  // 设置阴影样式
  lv_obj_add_style(but_exit, &style_squareShape, LV_STATE_DEFAULT);             // 设置方型样式
  lv_obj_set_style_outline_width(but_exit, 2, LV_STATE_FOCUS_KEY);              // 聚焦框的宽度
  lv_obj_set_style_outline_pad(but_exit, 0, LV_STATE_FOCUS_KEY);                // 聚焦框的间隙
  lv_obj_set_style_outline_opa(but_exit, LV_OPA_100, LV_STATE_FOCUS_KEY);       // 聚焦框的不透明度
  lv_obj_set_style_outline_width(but_exit, 0, LV_STATE_DEFAULT);                // 失焦时的宽度
  lv_obj_set_style_outline_color(but_exit, MY_COLOR_BLACK, LV_STATE_FOCUS_KEY); // 聚焦框颜色
  lv_obj_set_scrollbar_mode(but_exit, LV_SCROLLBAR_MODE_OFF);                   // 关闭滑动条
  lv_obj_t *l_exit = lv_label_create(but_exit);                                 // 创建标签
  lv_obj_align(l_exit, LV_ALIGN_CENTER, 0, 0);                                  // 对齐方式
  lv_label_set_text(l_exit, String("退出").c_str());                            // 标签文本
  if ((line % 6) < 3)
    lv_obj_set_style_text_color(l_exit, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  else
    lv_obj_set_style_text_color(l_exit, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  lv_obj_add_event_cb(but_exit, backPage_mainSet_event, LV_EVENT_PRESSED, NULL); // 退出回调
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL); // 添加聚焦动画
  lv_obj_add_event_cb(but_exit, buttonFocus_anim_event2, LV_EVENT_FOCUSED, NULL);
  lv_group_add_obj(group_my, but_exit);
}
//****** WIFI选择菜单
void wifiSelectMenu_exit_anim_end(lv_anim_t *a)  // 退出动画结束回调 
{
  lv_obj_delete(box_share[0]);         // 删除对象
  box_share[0] = NULL;                 // 对象地址清空
  lv_indev_set_group(indev, group_my); // 将组邦定到按键

  // 回到刚才的焦点
  focusPosOld_return();
  eepSavePage(page_wifiSelect, 0);
}
void wifiSelectMenu_anim_cb0(lv_anim_t *a) // 进入动画结束回调
{
  //lv_obj_align(lv_obj_xk, LV_ALIGN_DEFAULT, -20, 0);
  //lv_obj_set_align(lv_obj_xk, LV_ALIGN_DEFAULT); // 只有LV_ALIGN_DEFAULT才能正常
  lv_obj_t *box = lv_obj_get_child(box_share[0], 0); // 获取子对象 box
  lv_obj_t *open = lv_obj_get_child(box, 1);         // 获取子对象 open
  lv_group_focus_obj(open);                          // 聚焦到第一个选项
  // lv_obj_add_state(label_head_icon, LV_STATE_FOCUS_KEY);
}
void wifiSelectMenu_exitRefresh(lv_obj_t *butCur) // 退出弹窗加刷新
{
  lv_anim_t a;
  lv_anim_init(&a);                                           // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                          // 设置需要动画的对象
  lv_anim_set_values(&a, 0, 72);                              // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);                 // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb);        // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_overshoot);            // 设置变化特效
  lv_anim_set_completed_cb(&a, wifiSelectMenu_exit_anim_end); // 设置动画完成时的函数调用
  lv_anim_start(&a);

  File file = LittleFS.open(wifiRecord, "r");
  String str;
  for (uint16_t i = 0; i < file.size(); i++)
    str += char(file.read());
  file.close();
  display_wifiSelect_init(str);
  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
  onGlobalJitter(); // 打开全局抖动
  if(butCur != NULL) lv_group_focus_obj(butCur);
}
void wifiSelectMenu_open(lv_event_t *e)    // 使用回调
{
  lv_obj_t *box = lv_obj_get_child(box_share[0], 0);      // 获取子对象
  lv_obj_t *pawBg = lv_obj_get_child(box, 5);             // 获取子对象
  lv_obj_t *label_pawssword = lv_obj_get_child(pawBg, 0); // 获取子对象
  String pawssword = lv_label_get_text(label_pawssword);
  //Serial.printf("pawssword:%s\n", pawssword.c_str());

  // 获取上一个焦点
  int8_t focusPos = -1;
  lv_obj_t *focused_obj = lv_group_get_focused(group_my);    // 获取被聚焦的对象
  if (focused_obj != NULL) focusPos = lv_obj_get_index(focused_obj); // 获取对象的索引
  if (focusPos < 0) my_msgbox_forceSend(F("获取焦点"), F("错误"), 1200);

  //Serial.printf("focusPos:%d\n", focusPos);

  lv_obj_t *but = lv_obj_get_child(page.p[page.index], focusPos); // 获取子对象 按钮
  lv_obj_t *label_name = lv_obj_get_child(but, 0);                // 获取子对象 按钮的标签
  String name = lv_label_get_text(label_name);
  //Serial.printf("name:%s\n", name.c_str());
  
  eep_sta_ssid = name;
  eep_sta_password = pawssword;
  eep.begin("eepUser", false);
  eep.putString("sta_ssid", eep_sta_ssid);
  eep.putString("sta_password", eep_sta_password);
  eep.end();

  my_msgbox_forceSend(F("已切换"), LV_SYMBOL_LAUGH, 800);
}
void wifiSelectMenu_delete(lv_event_t *e)  // 删除回调
{
  // 获取上一个焦点
  int8_t focusPos = -1;
  lv_obj_t *but = lv_group_get_focused(group_my);    // 获取被聚焦的对象
  if (but != NULL) focusPos = lv_obj_get_index(but); // 获取对象的索引
  if (focusPos < 0) my_msgbox_forceSend(F("获取焦点"), F("错误"), 1200);

  bool ok = fileEdit_deleteRow(LittleFS, wifiRecord, focusPos);
  if (!ok)
    my_msgbox_forceSend(F("删除失败"), LV_SYMBOL_FROWN_OPEN, 1200);
  else
  {
    my_msgbox_forceSend(F("已删除"), LV_SYMBOL_LAUGH, 600);
    wifiSelectMenu_exitRefresh(NULL);
    //删除对象
    //lv_obj_delete(but);
  }
}
void wifiSelectMenu_topUp(lv_event_t *e)   // 置顶回调
{
  // 获取上一个焦点
  int8_t butPos = -1;
  lv_obj_t *butCur = lv_group_get_focused(group_my);  // 获取被聚焦的对象
  if (butCur != NULL) butPos = lv_obj_get_index(butCur); // 获取对象的索引
  //Serial.printf("butPos:%d\n",butPos);
  if     (butPos < 0)  my_msgbox_forceSend(F("获取焦点"), F("错误"), 1200);
  else if (butPos == 0)
  {
    my_msgbox_forceSend(F("已是最顶"), LV_SYMBOL_LAUGH, 800);
    return;
  }

  bool ok = fileEdit_moveToTop(LittleFS, wifiRecord, butPos);
  if (!ok)
    my_msgbox_forceSend(F("置顶失败"), LV_SYMBOL_FROWN_OPEN, 1200);
  else
  {
    my_msgbox_forceSend(F("已置顶"), LV_SYMBOL_LAUGH, 600);
    wifiSelectMenu_exitRefresh(butCur);

    //lv_obj_t *parent = lv_obj_get_parent(butCur);  // 交换父对象
    //lv_obj_t *but_0 = lv_obj_get_child(parent, 0); // 获取子对象
    //lv_obj_set_state(butCur, LV_STATE_FOCUS_KEY, 0);
    //lv_obj_set_state(butCur, LV_STATE_PRESSED, false); // 取消按下状态
    //lv_obj_swap(but_0, butCur); // 交换对象
    //lv_obj_add_state(but_0, LV_STATE_DEFAULT);
    // but_0 = lv_obj_get_child(parent, 0);           // 获取子对象
    // lv_group_focus_obj(but_0);                     // 聚焦第一个对象
  }
}
void wifiSelectMenu_exit(lv_event_t *e)    // 返回回调
{
  // 检查是否在退出中 防止重复触发
  lv_anim_t *b = lv_anim_get(box_share[0], display_alarmClock_anim_cb);
  if (b != NULL) return;

  lv_anim_t a;
  lv_anim_init(&a);                                           // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                          // 设置需要动画的对象
  lv_anim_set_values(&a, 0, 72);                              // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);                 // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb);        // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_overshoot);            // 设置变化特效
  lv_anim_set_completed_cb(&a, wifiSelectMenu_exit_anim_end); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
void display_wifiSelectMenu_init()
{
  //LV_FONT_DECLARE(ArialRoundedMTBold_14px);

  eepSavePage(page_wifiSelectMenu, 0); // 保存现在的界面

  // 获取上一个焦点
  int8_t focusPos = -1; 
  lv_obj_t *focused_obj = lv_group_get_focused(group_my);
  if (focused_obj != NULL) focusPos = lv_obj_get_index(focused_obj);
  //Serial.printf("focusPos:%d\n", focusPos);
  String pawssword = extractPasswordFromFile(wifiRecord, focusPos + 1);
  //Serial.printf("pawssword:%s\n", pawssword.c_str());
  //Serial.println();
  // 启用弹窗组
  lv_indev_set_group(indev, group_mbox1);
  page.keyMode == KEY_MODE_PN;

  // 创建容器盒子
  box_share[0] = lv_obj_create(lv_layer_top());      // lv_screen_active() lv_layer_top() lv_layer_sys()
  lv_obj_align(box_share[0], LV_ALIGN_CENTER, 0, 0); // 设置对齐方式
  lv_obj_set_scrollbar_mode(box_share[0], LV_SCROLLBAR_MODE_OFF);
  lv_obj_add_style(box_share[0], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box_share[0], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_bg_opa(box_share[0], LV_OPA_0, 0);

  uint16_t box_h = 90;
  // 创建实际盒子 即 外边框
  lv_obj_t *box = lv_obj_create(box_share[0]);
  lv_obj_set_scrollbar_mode(box, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(box, 72, box_h);
  lv_obj_align(box, LV_ALIGN_CENTER, 0, 0); // 设置对齐方式
  // 删除滚动条样式以获得干净的开始
  // lv_obj_remove_style(box, NULL, LV_PART_SCROLLBAR | LV_STATE_ANY);
  lv_obj_add_style(box, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(box, 6, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(box, 6, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(box, 7, 0);                  // 设置圆角
  lv_obj_set_style_border_width(box, 2, 0);             // 设置边框宽度
  lv_obj_set_style_border_color(box, MY_COLOR_BLACK, 0); // 设置边框颜色
  // lv_obj_set_style_bg_opa(box, LV_OPA_0, 0);

  // 创建内边框
  lv_obj_t *innerBorder = lv_obj_create(box_share[0]);
  lv_obj_set_size(innerBorder, 68, box_h - 4);
  lv_obj_align(innerBorder, LV_ALIGN_CENTER, 0, 0);               // 设置对齐方式
  lv_obj_add_style(innerBorder, &style_shadow, LV_STATE_DEFAULT); // 添加阴影不透明度样式
  lv_obj_set_style_pad_top(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(innerBorder, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(innerBorder, 5, 0);                   // 设置圆角
  lv_obj_set_style_border_width(innerBorder, 1, 0);             // 设置边框宽度
  lv_obj_set_style_border_color(innerBorder, MY_COLOR_CYAN, 0); // 设置边框颜色
  lv_obj_set_style_bg_opa(innerBorder, LV_OPA_0, 0);

  // 创建选框
  lv_obj_xk = lv_obj_create(box);
  lv_obj_set_scrollbar_mode(lv_obj_xk, LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(lv_obj_xk, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(lv_obj_xk, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_bg_opa(lv_obj_xk, LV_OPA_100, LV_STATE_DEFAULT);
  lv_obj_set_style_bg_color(lv_obj_xk, MY_COLOR_CYAN, LV_STATE_DEFAULT);
  lv_obj_align(lv_obj_xk, LV_ALIGN_DEFAULT, 0, -8);
  //lv_obj_set_size(lv_obj_xk, 66, 20);
  lv_obj_set_width(lv_obj_xk, 66);
  lv_obj_set_style_radius(lv_obj_xk, 4, 0); // 设置圆角

  int16_t label_x = -3;
  lv_obj_t *label_open;
  lv_obj_t *label_delete;
  lv_obj_t *label_topUp;
  lv_obj_t *label_exit;
  lv_obj_t *label_pawssword;
  lv_obj_t *opt[4];
  uint8_t optPos = 0;

  // 使用
  label_open = lv_label_create(box);                      // 创建标签
  opt[optPos++] = label_open;                             // 添加进数组
  lv_obj_align(label_open, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
  lv_label_set_text(label_open, String("使用").c_str());  // 标签文本
  // lv_obj_set_style_text_color(label_sw, MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_add_flag(label_open, LV_OBJ_FLAG_CLICKABLE);       // 使对象可被输入设备点击
  lv_obj_add_flag(label_open, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  lv_obj_add_flag(label_open, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见

  // 删除
  label_x += 21;
  label_delete = lv_label_create(box);                    // 创建标签
  opt[optPos++] = label_delete;                           // 添加进数组
  lv_obj_align(label_delete, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
  lv_label_set_text(label_delete, String("删除").c_str());  // 标签文本
  // lv_obj_set_style_text_color(label_sw, MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_add_flag(label_delete, LV_OBJ_FLAG_CLICKABLE);       // 使对象可被输入设备点击
  lv_obj_add_flag(label_delete, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  lv_obj_add_flag(label_delete, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见

  // 置顶
  label_x += 21;
  label_topUp = lv_label_create(box);                     // 创建标签
  opt[optPos++] = label_topUp;                             // 添加进数组
  lv_obj_align(label_topUp, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
  lv_label_set_text(label_topUp, String("置顶").c_str());  // 标签文本
  // lv_obj_set_style_text_color(label_sw, MY_COLOR_BLACK, 0); // 字体颜色
  lv_obj_add_flag(label_topUp, LV_OBJ_FLAG_CLICKABLE);       // 使对象可被输入设备点击
  lv_obj_add_flag(label_topUp, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  lv_obj_add_flag(label_topUp, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见

  // lv_obj_update_layout(box_share[0]);
  //  退出
  label_x += 21;
  label_exit = lv_label_create(box);                      // 创建标签
  opt[optPos++] = label_exit;                             // 添加进数组
  lv_obj_align(label_exit, LV_ALIGN_TOP_MID, 0, label_x); // 对齐方式
  lv_label_set_text(label_exit, String("返回").c_str());  // 标签文本
  lv_obj_add_flag(label_exit, LV_OBJ_FLAG_CLICKABLE);     // 使对象可被输入设备点击
  // lv_obj_add_flag(label_exit, LV_OBJ_FLAG_SCROLLABLE);      // 使对象可滚动
  // lv_obj_add_flag(label_exit, LV_OBJ_FLAG_SCROLL_ON_FOCUS); // 自动滚动对象以使其在聚焦时可见

  // 显示密码
  label_x += 21;
  lv_obj_t *pawBg = lv_obj_create(box);
  lv_obj_set_scrollbar_mode(pawBg, LV_SCROLLBAR_MODE_OFF);
  lv_obj_set_size(pawBg, 66, 21);
  lv_obj_align(pawBg, LV_ALIGN_TOP_MID, 0, label_x); // 设置对齐方式
  lv_obj_set_style_bg_color(pawBg, MY_COLOR_RED, 0);
  lv_obj_add_style(pawBg, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  label_pawssword = lv_label_create(pawBg);                      // 创建标签
  lv_obj_align(label_pawssword, LV_ALIGN_CENTER, 0, 0);          // 对齐方式
  lv_label_set_text(label_pawssword, pawssword.c_str());         // 标签文本
  lv_obj_set_style_text_color(label_pawssword, MY_COLOR_WHITE, LV_STATE_DEFAULT); // 设置文本颜色
  uint16_t text_width = lv_text_get_width(pawssword.c_str(), pawssword.length(), lv_obj_get_style_text_font(label_pawssword, 0), 0);
  if (text_width > 66)
  {
    lv_obj_set_width(label_pawssword, 66);
    lv_obj_set_style_anim_duration(label_pawssword, text_width * 35, 0);
    lv_label_set_long_mode(label_pawssword, LV_LABEL_LONG_SCROLL_CIRCULAR); // 长字符模式
  }
  // 批量设置
  for (uint8_t i = 0; i < optPos; i++)
  {
    set_style_outline(opt[i]);
    // 设置文本长字符模式
    lv_label_set_long_mode(opt[i], LV_LABEL_LONG_SCROLL); 
    // 将对象邦定到组
    lv_group_add_obj(group_mbox1, opt[i]);
    // 添加按钮聚焦动画
    //lv_obj_add_event_cb(opt[i], buttonFocus_anim_event, LV_EVENT_FOCUSED, NULL);
    // 聚焦移动选框动画
    lv_obj_add_event_cb(opt[i], fileExplorer_xk_anim_event, LV_EVENT_FOCUSED, &num[0]);      
  }

  // 重新设置盒子高度
  box_h = box_h + (optPos - 3) * 21;
  lv_obj_set_size(box, 72, box_h);
  lv_obj_set_size(innerBorder, 68, box_h - 4);

  // 使用回调
  lv_obj_add_event_cb(label_open, wifiSelectMenu_open, LV_EVENT_PRESSED, NULL);
  // 删除回调
  lv_obj_add_event_cb(label_delete, wifiSelectMenu_delete, LV_EVENT_PRESSED, NULL);
  // 置顶回调
  lv_obj_add_event_cb(label_topUp, wifiSelectMenu_topUp, LV_EVENT_PRESSED, NULL);
  // 返回回调
  lv_obj_add_event_cb(label_exit, wifiSelectMenu_exit, LV_EVENT_PRESSED, NULL);

  // 添加进入动画
  lv_anim_t a;
  lv_anim_init(&a);                                      // 动画初始化
  lv_anim_set_var(&a, box_share[0]);                     // 设置需要动画的对象
  lv_anim_set_values(&a, 36, 0);                         // 设置动画的开始值和结束值
  lv_anim_set_duration(&a, MSGBOX_ANIM_TIME);            // 设置动画的持续时间
  lv_anim_set_exec_cb(&a, display_alarmClock_anim_cb);   // 设置需要变化的值
  lv_anim_set_path_cb(&a, lv_anim_path_ease_out);        // 设置变化特效
  lv_anim_set_completed_cb(&a, wifiSelectMenu_anim_cb0); // 设置动画完成时的函数调用
  lv_anim_start(&a);
}
//文件编辑 删除指定行 从0开始
bool fileEdit_deleteRow(fs::FS &fs, const char *record, uint8_t row)
{

  // 打开文件进行读取
  File file = fs.open(record, "r");
  if (!file) {
    //Serial.println("无法打开文件进行读取");
    return false;
  }

  // 创建一个临时文件来存储修改后的内容
  File tempFile = fs.open("/temp.txt", "w");
  if (!tempFile) {
    //Serial.println("无法打开临时文件进行写入");
    file.close();
    return false;
  }

  uint8_t currentRow = 0;
  bool deleted = false;

  // 逐行读取文件内容
  while (file.available()) {
    String line = file.readStringUntil('\n'); // 读取到 \n 为止
    // 检查是否包含 \r（Windows 换行符）
    if (line.endsWith("\r")) {
      line.remove(line.length() - 1); // 去掉 \r
    }

    if (currentRow != row) {
      // 如果不是要删除的行，则写入临时文件
      tempFile.println(line); // 使用 println 自动添加换行符
    } else {
      deleted = true; // 标记已删除
    }
    currentRow++;
  }

  // 关闭文件
  file.close();
  tempFile.close();

  // 如果成功删除了指定行，则用临时文件替换原文件
  if (deleted) {
    fs.remove(record); // 删除原文件
    fs.rename("/temp.txt", record); // 重命名临时文件为原文件名
  } else {
    fs.remove("/temp.txt"); // 如果没有删除任何行，则删除临时文件
  }

  return deleted;
}
//文件编辑 置顶指定行 从0开始
bool fileEdit_moveToTop(fs::FS &fs, const char *record, uint8_t row)
{
  // 打开文件进行读取
  File file = fs.open(record, "r");
  if (!file)
  {
    return false;
  }

  // 如果指定行是第一行，则无需操作
  if (row == 0)
  {
    file.close();
    return true;
  }

  // 创建一个临时文件来存储修改后的内容
  File tempFile = fs.open("/temp.txt", "w");
  if (!tempFile)
  {
    file.close();
    return false;
  }

  uint8_t currentRow = 0;
  String targetLine; // 用于存储要置顶的行
  bool moved = false;

  // 逐行读取文件内容
  while (file.available())
  {
    String line = file.readStringUntil('\n'); // 读取到 \n 为止
    // 检查是否包含 \r（Windows 换行符）
    if (line.endsWith("\r"))
    {
      line.remove(line.length() - 1); // 去掉 \r
    }

    if (currentRow == row)
    {
      // 找到要置顶的行，保存到 targetLine
      targetLine = line;
      moved = true;
    }
    else
    {
      // 其他行暂时写入临时文件
      tempFile.println(line);
    }
    currentRow++;
  }

  // 关闭文件
  file.close();
  tempFile.close();

  if (!moved)
  {
    // 如果未找到指定行，删除临时文件并返回失败
    fs.remove("/temp.txt");
    return false;
  }

  // 打开临时文件和最终文件
  tempFile = fs.open("/temp.txt", "r");
  File finalFile = fs.open(record, "w");
  if (!tempFile || !finalFile)
  {
    if (tempFile)
      tempFile.close();
    if (finalFile)
      finalFile.close();
    fs.remove("/temp.txt");
    return false;
  }

  // 将要置顶的行写入最终文件的开头
  finalFile.println(targetLine);

  // 将临时文件的内容追加到最终文件
  while (tempFile.available())
  {
    String line = tempFile.readStringUntil('\n');
    if (line.endsWith("\r"))
    {
      line.remove(line.length() - 1);
    }
    finalFile.println(line);
  }

  // 关闭所有文件
  tempFile.close();
  finalFile.close();

  // 删除临时文件
  fs.remove("/temp.txt");
  return true;
}

//****** 万年历
void analysisYiJi(String strIn)
{
  bool yi_ji_state = 0;   // 0-宜 1-忌
  int16_t kg_pos_old = -1; // 上一个空格的位置
  uint8_t yi2_num = 0;    // 宜2字数量
  uint8_t yi3_num = 0;    // 宜3字数量
  uint8_t ji2_num = 0;    // 忌2字数量
  uint8_t ji3_num = 0;    // 宜3字数量
  for (uint16_t i = 0; i < strIn.length(); i++)
  {
    char c = strIn[i];
    if(c == ' ' || c == '\n')  
    {
      // 宜的范围
      if (yi_ji_state == 0)
      {
        if (i - kg_pos_old == 7) // 相差2个字
        {
          yi2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 10)  // 相差3个字
        {
          yi3_num++;
          kg_pos_old = i;
        }
      }
      // 忌的范围
      else if (yi_ji_state == 1)
      {
        if (i - kg_pos_old == 7) // 相差2个字
        {
          ji2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 10) // 相差3个字
        {
          ji3_num++;
          kg_pos_old = i;
        }
      }
      // 切换至忌的范围
      if(c == '\n') yi_ji_state = 1;
    }
  }

  /*Serial.printf("yi2_num:%d\n", yi2_num);
  Serial.printf("yi3_num:%d\n", yi3_num);
  Serial.printf("ji2_num:%d\n", ji2_num);
  Serial.printf("ji3_num:%d\n", ji3_num);*/

  String yi_2[yi2_num];
  String yi_3[yi3_num];
  String ji_2[ji2_num];
  String ji_3[ji3_num];
  yi_ji_state = 0; // 0-宜 1-忌
  kg_pos_old = -1; // 上一个空格的位置
  yi2_num = 0;     // 宜2字数量
  yi3_num = 0;     // 宜3字数量
  ji2_num = 0;     // 忌2字数量
  ji3_num = 0;     // 宜3字数量
  for (uint16_t i = 0; i < strIn.length(); i++)
  {
    char c = strIn[i];
    if (c == ' ' || c == '\n')
    {
      // 宜的范围
      if (yi_ji_state == 0)
      {
        if (i - kg_pos_old == 7) // 相差2个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            yi_2[yi2_num] += strIn[j];
          }
          Serial.printf("yi_2[%d]:%s\n", yi2_num, yi_2[yi2_num].c_str());
          yi2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 10) // 相差3个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            yi_3[yi3_num] += strIn[j];
          }
          Serial.printf("yi_3[%d]:%s\n", yi3_num, yi_3[yi3_num].c_str());
          yi3_num++;
          kg_pos_old = i;
        }
      }
      // 忌的范围
      else if (yi_ji_state == 1)
      {
        if (i - kg_pos_old == 7) // 相差2个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            ji_2[ji2_num] += strIn[j];
          }
          Serial.printf("ji_2[%d]:%s\n", ji2_num, ji_2[ji2_num].c_str());
          ji2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 10) // 相差3个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            ji_3[ji3_num] += strIn[j];
          }
          Serial.printf("ji_3[%d]:%s\n", ji3_num, ji_3[ji3_num].c_str());
          ji3_num++;
          kg_pos_old = i;
        }
      }
      // 切换至忌的范围
      if (c == '\n') yi_ji_state = 1;
    }
  }

}
void wanNianLi_event0(lv_event_t *e)
{
  // 检查动画是否播放中，播放中就退出
  // lv_obj_t *obj = lv_event_get_target_obj(e);
  // lv_event_code_t code = lv_event_get_code(e);
  // uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  // uint8_t i = data[0];
  uint8_t key = lv_indev_get_key(lv_indev_active());
  //Serial.printf("key:%d\n", key);
  if(key == LV_KEY_ENTER)
  {
    my_msgbox_send(F("万年历"), F("是否退出"), 0, F("退出\n返回\n"), backPage_mainSet);
  }
}
void display_wanNianLi_init(String strIn)
{
  bool yi_ji_state = 0;   // 0-宜 1-忌
  int16_t kg_pos_old = -1; // 上一个空格的位置
  uint8_t yi2_num = 0;     // 宜2字数量
  uint8_t yi3_num = 0;     // 宜3字数量
  uint8_t yi4_num = 0;     // 宜4字数量
  uint8_t ji2_num = 0;     // 忌2字数量
  uint8_t ji3_num = 0;     // 忌3字数量
  uint8_t ji4_num = 0;     // 忌4字数量
  for (uint16_t i = 0; i < strIn.length(); i++)
  {
    char c = strIn[i];
    if(c == ' ' || c == '\n')  
    {
      // 宜的范围
      if (yi_ji_state == 0)
      {
        if      (i - kg_pos_old == 2 * 3 + 1) // 相差2个字
        {
          yi2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 3 * 3 + 1) // 相差3个字
        {
          yi3_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 4 * 3 + 1) // 相差4个字
        {
          yi4_num++;
          kg_pos_old = i;
        }
      }
      // 忌的范围
      else if (yi_ji_state == 1)
      {
        if      (i - kg_pos_old == 2 * 3 + 1) // 相差2个字
        {
          ji2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 3 * 3 + 1) // 相差3个字
        {
          ji3_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 4 * 3 + 1) // 相差4个字
        {
          ji4_num++;
          kg_pos_old = i;
        }
      }
      // 切换至忌的范围
      if(c == '\n') yi_ji_state = 1;
    }
  }
  
  /*Serial.printf("yi2_num:%d\n", yi2_num);
  Serial.printf("yi3_num:%d\n", yi3_num);
  Serial.printf("yi4_num:%d\n", yi4_num);
  Serial.printf("ji2_num:%d\n", ji2_num);
  Serial.printf("ji3_num:%d\n", ji3_num);
  Serial.printf("yi4_num:%d\n", yi4_num);*/

  String yi_2[yi2_num];
  String yi_3[yi3_num];
  String yi_4[yi4_num];
  String ji_2[ji2_num];
  String ji_3[ji3_num];
  String ji_4[ji4_num];
  yi_ji_state = 0; // 0-宜 1-忌
  kg_pos_old = -1; // 上一个空格的位置
  yi2_num = 0;     // 宜2字数量
  yi3_num = 0;     // 宜3字数量
  yi4_num = 0;     // 宜4字数量
  ji2_num = 0;     // 忌2字数量
  ji3_num = 0;     // 忌3字数量
  ji4_num = 0;     // 忌4字数量
  for (uint16_t i = 0; i < strIn.length(); i++)
  {
    char c = strIn[i];
    if (c == ' ' || c == '\n')
    {
      // 宜的范围
      if (yi_ji_state == 0)
      {
        if      (i - kg_pos_old == 2 * 3 + 1) // 相差2个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            yi_2[yi2_num] += strIn[j];
          }
          //Serial.printf("yi_2[%d]:%s\n", yi2_num, yi_2[yi2_num].c_str());
          yi2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 3 * 3 + 1) // 相差3个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            yi_3[yi3_num] += strIn[j];
          }
          //Serial.printf("yi_3[%d]:%s\n", yi3_num, yi_3[yi3_num].c_str());
          yi3_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 4 * 3 + 1) // 相差4个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            yi_4[yi4_num] += strIn[j];
          }
          //Serial.printf("yi_4[%d]:%s\n", yi4_num, yi_4[yi4_num].c_str());
          yi4_num++;
          kg_pos_old = i;
        }
      }
      // 忌的范围
      else if (yi_ji_state == 1)
      {
        if      (i - kg_pos_old == 2 * 3 + 1) // 相差2个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            ji_2[ji2_num] += strIn[j];
          }
          //Serial.printf("ji_2[%d]:%s\n", ji2_num, ji_2[ji2_num].c_str());
          ji2_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 3 * 3 + 1) // 相差3个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            ji_3[ji3_num] += strIn[j];
          }
          //Serial.printf("ji_3[%d]:%s\n", ji3_num, ji_3[ji3_num].c_str());
          ji3_num++;
          kg_pos_old = i;
        }
        else if (i - kg_pos_old == 4 * 3 + 1) // 相差4个字
        {
          for (int16_t j = kg_pos_old + 1; j < i; j++)
          {
            ji_4[ji4_num] += strIn[j];
          }
          //Serial.printf("ji_4[%d]:%s\n", ji4_num, ji_4[ji4_num].c_str());
          ji4_num++;
          kg_pos_old = i;
        }
      }
      // 切换至忌的范围
      if (c == '\n') yi_ji_state = 1;
    }
  }

  eepSavePage(page_wanNianLi, 0);
  pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[page.index] = lv_obj_create(NULL);
  lv_obj_set_scrollbar_mode(page.p[page.index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[page.index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[page.index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式

  lv_obj_set_flex_flow(page.p[page.index], LV_FLEX_FLOW_COLUMN);
  // 参数2：将项目放置在主轴上的位置（在其轨迹中）。lv_flex_align_t的任何值 控制Y轴排布
  // 参数3：在横轴上的轨迹中放置项目的位置。LV_FLEX_ALIGN_START/END/CENTER
  // 参数4：在交叉方向上放置轨道的位置。lv_flex_align_t的任何值。 控制X轴排布
  lv_obj_set_flex_align(page.p[page.index], LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
  // lv_obj_set_flex_grow(page.p[page.index], 3); //设置对象生长的宽度或高度（在主轴上），以填充自由空间
  lv_obj_set_style_pad_row(page.p[page.index], 0, LV_STATE_DEFAULT); // 设置行间距为5像素

  // 将对象邦定到组
  lv_group_add_obj(group_my, page.p[page.index]);
  lv_obj_add_event_cb(page.p[page.index], wanNianLi_event0, LV_EVENT_KEY, NULL);
  
  //****** 宜的内容
  lv_obj_t *lab_yi = lv_label_create(page.p[page.index]); // 创建标签
  lv_obj_set_size(lab_yi, 72, 20);
  lv_label_set_text(lab_yi, String(F("宜")).c_str());                   // 标签文本
  lv_obj_set_style_text_align(lab_yi, LV_TEXT_ALIGN_CENTER, 0);         // 文本对齐方式
  lv_obj_set_style_bg_opa(lab_yi, LV_OPA_100, 0);                       // 设置背景颜色透明度
  lv_obj_set_style_bg_color(lab_yi, MY_COLOR_YELLOW, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_set_style_text_color(lab_yi, MY_COLOR_BLACK, LV_STATE_DEFAULT);

  uint8_t zi_pos = 0;
  uint8_t numMax = float(yi2_num) / 2.0 + 0.5;
  for (uint8_t i = 0; i < numMax; i++)
  {
    String str;
    lv_obj_t *label = lv_label_create(page.p[page.index]); // 创建标签
    lv_obj_set_size(label, 72, 18);
    if (zi_pos + 1 < yi2_num || yi2_num == 2)
    {
      lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
      str = yi_2[zi_pos] + " " + yi_2[zi_pos + 1];
      zi_pos += 2;
    }
    else
    {
      lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);
      str = yi_2[yi2_num - 1];
    }
    //Serial.printf("str:%s\n", str.c_str());
    lv_label_set_text(label, str.c_str()); // 标签文本
    lv_obj_set_style_bg_opa(label, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(label, MY_COLOR_GREEN, LV_STATE_DEFAULT); // 设置背景颜色
    lv_obj_set_style_text_color(label, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  }
  for (uint8_t i = 0; i < yi3_num; i++)
  {
    lv_obj_t *label = lv_label_create(page.p[page.index]); // 创建标签
    lv_obj_set_size(label, 72, 18);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);
    lv_label_set_text(label, yi_3[i].c_str()); // 标签文本
    lv_obj_set_style_bg_opa(label, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(label, MY_COLOR_GREEN, LV_STATE_DEFAULT); // 设置背景颜色
    lv_obj_set_style_text_color(label, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  }
  for (uint8_t i = 0; i < yi4_num; i++)
  {
    lv_obj_t *label = lv_label_create(page.p[page.index]); // 创建标签
    lv_obj_set_size(label, 72, 18);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);
    lv_label_set_text(label, yi_4[i].c_str()); // 标签文本
    lv_obj_set_style_bg_opa(label, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(label, MY_COLOR_GREEN, LV_STATE_DEFAULT); // 设置背景颜色
    lv_obj_set_style_text_color(label, MY_COLOR_BLACK, LV_STATE_DEFAULT);
  }
  //****** 忌的内容
  lv_obj_t *lab_ji = lv_label_create(page.p[page.index]); // 创建标签
  lv_label_set_text(lab_ji, String(F("忌")).c_str());                   // 标签文本
  lv_obj_set_size(lab_ji, 72, 20);
  lv_obj_set_style_text_align(lab_ji, LV_TEXT_ALIGN_CENTER, 0);       // 文本对齐方式
  lv_obj_set_style_bg_opa(lab_ji, LV_OPA_100, 0);                     // 设置背景颜色透明度
  lv_obj_set_style_bg_color(lab_ji, MY_COLOR_BLUE, LV_STATE_DEFAULT); // 设置背景颜色
  lv_obj_set_style_text_color(lab_ji, MY_COLOR_WHITE, LV_STATE_DEFAULT);  
  zi_pos = 0;
  numMax = float(ji2_num) / 2.0 + 0.5;
  for (uint8_t i = 0; i < numMax; i++)
  {
    String str;
    lv_obj_t *label = lv_label_create(page.p[page.index]); // 创建标签
    lv_obj_set_size(label, 72, 18);
    if (zi_pos + 1 < ji2_num || ji2_num == 2)
    {
      lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
      str = ji_2[zi_pos] + " " + ji_2[zi_pos + 1];
      zi_pos += 2;
    }
    else
    {
      lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);
      str = ji_2[ji2_num - 1];
    }
    lv_label_set_text(label, str.c_str()); // 标签文本
    lv_obj_set_style_bg_opa(label, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(label, MY_COLOR_RED, LV_STATE_DEFAULT); // 设置背景颜色
    lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  }
  for (uint8_t i = 0; i < ji3_num; i++)
  {
    lv_obj_t *label = lv_label_create(page.p[page.index]); // 创建标签
    lv_obj_set_size(label, 72, 18);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);
    lv_label_set_text(label, ji_3[i].c_str()); // 标签文本
    lv_obj_set_style_bg_opa(label, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(label, MY_COLOR_RED, LV_STATE_DEFAULT); // 设置背景颜色
    lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  }
  for (uint8_t i = 0; i < ji4_num; i++)
  {
    lv_obj_t *label = lv_label_create(page.p[page.index]); // 创建标签
    lv_obj_set_size(label, 72, 18);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 2, 0);
    lv_label_set_text(label, ji_4[i].c_str()); // 标签文本
    lv_obj_set_style_bg_opa(label, LV_OPA_100, 0);
    lv_obj_set_style_bg_color(label, MY_COLOR_RED, LV_STATE_DEFAULT); // 设置背景颜色
    lv_obj_set_style_text_color(label, MY_COLOR_WHITE, LV_STATE_DEFAULT);
  }
}




/*
// 创建一个LVGL显示对象
lv_obj_t *box_obj;
lv_obj_t *box_obj2;
lv_obj_t *box_obj3;
// Box2D相关定义
b2WorldId worldId;
b2BodyId bodyId;
b2BodyId bodyId2;
b2BodyId bodyId3;
float timeStep = 1.0f / 55.0f;
int32_t subStepCount = 1;
// 更新LVGL对象位置
static void update_box_position()
{
    b2Vec2 position = b2Body_GetPosition(bodyId);
    //b2Rot rot = b2Body_GetRotation(bodyId);
    lv_obj_set_pos(box_obj, (int)position.x, (int)(position.y));
    //Serial.printf("position.x:%d\n",(int)position.x);
    //Serial.printf("position.y:%d\n",(int)position.y);
    b2Rot rot = b2Body_GetRotation(bodyId);
    float angle = atan2f(rot.s, rot.c); // 从sin和cos值获取角度（弧度）
    lv_obj_set_style_transform_rotation(box_obj, (int16_t)(angle * 180.0f / M_PI * 10), 0);


    b2Vec2 position2 = b2Body_GetPosition(bodyId2);
    b2Rot rot2 = b2Body_GetRotation(bodyId2);
    lv_obj_set_pos(box_obj2, (int)position2.x, (int)(position2.y));
    //Serial.printf("rot2.c:%f\n",(float)rot2.c);
    // Serial.printf("rot2.s:%f\n",(float)rot2.s);
    angle = atan2f(rot2.s, rot2.c); // 从sin和cos值获取角度（弧度）
    lv_obj_set_style_transform_rotation(box_obj2, (int16_t)(angle * 180.0f / M_PI * 10), 0);

    b2Vec2 position3 = b2Body_GetPosition(bodyId3);
    lv_obj_set_pos(box_obj3, (int)position3.x, (int)(position3.y));
}
// 定义一个LVGL任务来更新Box2D物理引擎 
void box2d_task(lv_timer_t *timer)
{
    // 更新物理引擎
    //uint32_t time1 = millis();
    b2World_Step(worldId, timeStep, subStepCount);
    //Serial.printf("time1:%d\n", millis() - time1);

    b2Vec2 new_gravity = {(float)acc.y, (float)acc.x + 144.0f}; // 垂直方向保持-10.0f
    b2World_SetGravity(worldId, new_gravity);
    // 更新LVGL显示对象的位置
    update_box_position();
}
void box2d_world_init()
{
  uint8_t index = pageInit(KEY_MODE_PN, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);

  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF);       // 关闭滑动条
  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_style_pad_top(page.p[index], 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_bottom(page.p[index], 0, LV_STATE_DEFAULT);

  //****** 初始化Box2D
  //b2SetLengthUnitsPerMeter();
  b2Vec2 gravity = {0.0f, 154.0f};
  b2WorldDef worldDef = b2DefaultWorldDef();
  worldDef.gravity = gravity;
  worldId = b2CreateWorld(&worldDef);

  //****** 创建地面
  b2BodyDef groundBodyDef = b2DefaultBodyDef();
  groundBodyDef.type = b2_staticBody;
  groundBodyDef.position = (b2Vec2){0.0f, 134.0f}; // 表示在 y 轴上距离原点 10 个单位的地方。
  // b2World_CreateBody 使用 groundBodyDef 定义在物理世界中创建了一个静态的地面物体。
  b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
  // 创建一个宽144,高2 的盒子形状
  b2Polygon groundBox = b2MakeBox(400.0f, 5.0f);
  b2ShapeDef groundShapeDef = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

  //****** 创建左墙面
  b2BodyDef groundBodyDef2 = b2DefaultBodyDef();
  groundBodyDef2.type = b2_staticBody;
  groundBodyDef2.position = (b2Vec2){-9.0f, 0.0f}; 
  b2BodyId groundId2 = b2CreateBody(worldId, &groundBodyDef2);
  b2Polygon groundBox2 = b2MakeBox(1.0f, 143.0f);
  b2ShapeDef groundShapeDef2 = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId2, &groundShapeDef2, &groundBox2);

  //****** 创建右墙面
  b2BodyDef groundBodyDef3 = b2DefaultBodyDef();
  groundBodyDef3.type = b2_staticBody;
  groundBodyDef3.position = (b2Vec2){61.0f, 0.0f}; 
  b2BodyId groundId3 = b2CreateBody(worldId, &groundBodyDef3);
  b2Polygon groundBox3 = b2MakeBox(1.0f, 143.0f);
  b2ShapeDef groundShapeDef3 = b2DefaultShapeDef();
  b2CreatePolygonShape(groundId3, &groundShapeDef3, &groundBox3);

  //****** 创建动态物体 1
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.enableSleep = false;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = (b2Vec2){15.0f, -40.0f};
  bodyId = b2CreateBody(worldId, &bodyDef);
  // 创建形状
  b2Polygon box = b2MakeBox(10.0f, 10.0f);
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 1.0f;
  shapeDef.friction = 0.6f;
  b2CreatePolygonShape(bodyId, &shapeDef, &box);

  //****** 创建动态物体2
  b2BodyDef bodyDef2 = b2DefaultBodyDef();
  bodyDef2.type = b2_dynamicBody;
  bodyDef2.position = (b2Vec2){2.0f, 0.0f};
  bodyId2 = b2CreateBody(worldId, &bodyDef2);
  // 创建形状
  b2Polygon box2 = b2MakeBox(10.0f, 10.0f);
  b2ShapeDef shapeDef2 = b2DefaultShapeDef();
  shapeDef2.density = 1.0f;
  shapeDef2.friction = 0.5f;
  b2CreatePolygonShape(bodyId2, &shapeDef2, &box2);

  //****** 创建动态物体3
  b2BodyDef bodyDef3 = b2DefaultBodyDef();
  bodyDef3.type = b2_dynamicBody;
  bodyDef3.position = (b2Vec2){26.0f, -80.0f};
  bodyId3 = b2CreateBody(worldId, &bodyDef3);
  // 创建形状
  b2Polygon box3 = b2MakeRoundedBox(10.0f, 10.0f, 0.25f);
  b2ShapeDef shapeDef3 = b2DefaultShapeDef();
  shapeDef3.density = 1.0f;
  shapeDef3.friction = 0.2f;
  b2CreatePolygonShape(bodyId3, &shapeDef3, &box3);

  //****** 创建一个LVGL对象显示这个物体
  box_obj = lv_obj_create(page.p[index]);
  lv_obj_add_style(box_obj, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box_obj, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_size(box_obj, 20, 20);
  lv_obj_set_style_bg_color(box_obj, MY_COLOR_RED, 0);
  //lv_obj_set_pos(box_obj, 10, 10);

  box_obj2 = lv_obj_create(page.p[index]);
  lv_obj_add_style(box_obj2, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box_obj2, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_size(box_obj2, 20, 20);
  lv_obj_set_style_bg_color(box_obj2, MY_COLOR_BLUE, 0);
  //lv_obj_set_pos(box_obj2, 10, 10);

  box_obj3 = lv_obj_create(page.p[index]);
  lv_obj_add_style(box_obj3, &style_shadow, LV_STATE_DEFAULT);      // 添加阴影不透明度样式
  lv_obj_add_style(box_obj3, &style_squareShape, LV_STATE_DEFAULT); // 添加方形样式
  lv_obj_set_size(box_obj3, 20, 20);
  lv_obj_set_style_bg_color(box_obj3, MY_COLOR_GREEN, 0);
  lv_obj_set_style_radius(box_obj3, 10, 0);

  lv_obj_update_layout(page.p[index]);

  // **设置旋转中心**：将旋转中心设置为对象的几何中心
  lv_obj_set_style_transform_pivot_x(box_obj, lv_obj_get_width(box_obj) / 2, 0);
  lv_obj_set_style_transform_pivot_y(box_obj, lv_obj_get_height(box_obj) / 2, 0);
  // **设置旋转中心**：将旋转中心设置为对象的几何中心
  lv_obj_set_style_transform_pivot_x(box_obj2, lv_obj_get_width(box_obj2) / 2, 0);
  lv_obj_set_style_transform_pivot_y(box_obj2, lv_obj_get_height(box_obj2) / 2, 0);
  lv_obj_set_style_transform_pivot_x(box_obj3, lv_obj_get_width(box_obj3) / 2, 0);
  lv_obj_set_style_transform_pivot_y(box_obj3, lv_obj_get_height(box_obj3) / 2, 0);


  //****** 设置定时器更新Box2D物理引擎和LVGL对象位置
  lv_timer_create(box2d_task, 15, NULL);
}
*/

/*static lv_subject_t temperature_subject;
void lv_example_observer_1(void)
{
    lv_subject_init_int(&temperature_subject, 28);

    //Create a slider in the center of the display
    lv_obj_t * slider = lv_slider_create(lv_screen_active());
    lv_obj_center(slider);
    lv_slider_bind_value(slider, &temperature_subject);

    //Create a label below the slider
    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 30);
    lv_label_bind_text(label, &temperature_subject, "%d °C");
}*/

/*void display_lottie_init()
{
    LV_IMG_DECLARE(qft);
  lv_obj_t *gif = lv_gif_create(page1);
  lv_gif_set_src(gif, &qft);
  lv_obj_align(gif, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_t *lottie;
  lv_lottie_set_buffer(lottie, w, h, buf);
  lv_lottie_set_src_file(lottie, "path/to/file.json");
}*/

// 使用bin字体 ，字体使用的是动态内存空间
// lv_font_t * MISans_font = lv_binfont_create("A:MISans_1.bin");

// 使用ttf字体,速度慢
/*static lv_style_t style;
lv_style_init(&style);
lv_font_t *font = lv_tiny_ttf_create_file("A:font2.ttf", 16);
lv_style_set_text_font(&style, font);
lv_style_set_text_align(&style, LV_TEXT_ALIGN_CENTER);*/

// 使用.c字体 ，较为理想，使用存储内存运行
//static lv_style_t font_style;
//lv_style_init(&font_style);
//LV_FONT_DECLARE(MISans_1);
//lv_style_set_text_font(&font_style, &MISans_1);
//lv_obj_add_style(label2, &font_style, 0);

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

//移除事件回调操作
/*uint32_t event_cnt = lv_obj_get_event_count(obj);
for (uint32_t i = 0; i < event_cnt; i++)
{
  lv_event_dsc_t *event_dsc = lv_obj_get_event_dsc(obj, 0);
  if (lv_event_dsc_get_cb(event_dsc) == event_jitterSet) // 移除 event_jitterSet
  {
    bool ok = lv_obj_remove_event(obj, 0);
  }
}*/