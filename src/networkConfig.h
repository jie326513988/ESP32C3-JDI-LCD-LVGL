// 创建配网任务
void networkConfig_rtos_init()
{
  //i2c_begin();
  xTaskCreatePinnedToCore(
      networkConfig_rtos, /* 任务指针，创建任务用的那个函数名 */
      "networkConfig",    /* 任务名称 */
      8 * 1024,           /* 任务栈大小，根据需要自行设置*/
      NULL,               /* 可选参数，一般不填*/
      1,                  /* 优先级 */
      &TH_networkConfig,  /* 任务句柄，用于后续挂起或恢复运行*/
      0                   /* 核ID */
  );
}

//int8_t pw_state = 0;
// 启动ap模式状态  0-无 1-WiFi未配置 2-有配置 3-有配置但连接失败 4-连接成功
void networkConfig_rtos(void *param)
{
  String title, text;
  // wifi未配置
  if (eep_sta_ssid == NULL) pw_state = 1; 
  //WiFi已配置尝试连接
  else
  {
    pw_state = 2; 
    title = F("连接WIFI");
    text = eep_sta_ssid;
    my_msgbox_send(title.c_str(), text.c_str());
    if (!connectToWifi()) // 连接wifi失败
    {
      pw_state = 3;
      initAp(); // 启动热点
      text = F("连接失败启动热点模式");
      my_msgbox_send(title.c_str(), text.c_str(), 2500);
      delay(3000);
    }
    else // 连接wifi成功
    {
      pw_state = 4;
      initApSTANoBegin(); // 启动STA和热点
      text = F("连接成功双模启动");
      my_msgbox_send(title.c_str(), text.c_str(), 1700);
      delay(2000);
    }
  }

  onGlobalJitter(); // 打开全局抖动

  xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
  display_networkConfig_init();
  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_ON, GRADUAL_ANIM_TIME, 0, true);
  xSemaphoreGive(lvgl_mutex);

  vTaskDelay(2);
  
  initWebServer(); // 初始化WEB服务器、webServerOTA服务

  for (;;)
  {
    //删除自己
    if (!bitRead(backgroundTask, BGT_CONFIG_NETWORK))
    {
      Serial.println("删除TH_networkConfig");
      TH_networkConfig = NULL;
      vTaskDelete(NULL);
    }
    server.handleClient(); // 处理http请求
    vTaskDelay(1);
  }
}


// 配网界面事件回调
void networkConfig_end_cb(lv_event_t *e) //配网退出回调
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0) // 退出配网
  {
    WiFi.mode(WIFI_OFF);       // 关闭wifi
    server.close();            // 关闭服务器
    my_msgbox_exit(5); // 退出弹窗
    bitWrite(backgroundTask, BGT_CONFIG_NETWORK, 0); // 标记关闭配网
    vTaskDelay(5);

    display_mainSet_init();
    lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_OUT, GRADUAL_ANIM_TIME, 0, true);
    onGlobalJitter(); // 打开全局抖动
    
    //pageStartupEnters();

    // 回到上一个焦点
    focusPosOld_return();
  }
  else if (data[0] == 1)  // 返回配网
  {
    my_msgbox_exit(0); // 退出弹窗
  }
}
void display_networkConfig_event(lv_event_t *e)
{
  //lv_event_code_t code = lv_event_get_code(e);
  //lv_obj_t *obj = lv_event_get_target_obj(e);
  uint8_t key = lv_indev_get_key(lv_indev_active());
  //Serial.print("networkConfig key:");Serial.println(key);
  //Serial.print("networkConfig code:");Serial.println(code);
  if (key == LV_KEY_RIGHT || key == LV_KEY_LEFT)
    my_msgbox_send(F("配网模式"), F("是否退出"), 0, F("退出\n返回\n"), networkConfig_end_cb);
}
// 配网界面初始化
void display_networkConfig_init()
{
  eepSavePage(page_networkConfig, 0);

  focusPosOld_save(); //保存上一个界面的焦点

  LV_FONT_DECLARE(MiSans_Bold_14px);

  uint8_t index = pageInit(KEY_MODE_RL, FIRST_EVENT_OFF);
  page.p[index] = lv_obj_create(NULL);
  lv_obj_set_size(page.p[index], TFT_HOR_RES, TFT_VER_RES);
  lv_obj_align(page.p[index], LV_ALIGN_CENTER, 0, 0);

  lv_obj_add_style(page.p[index], &style_shadow, LV_STATE_DEFAULT);      // 设置阴影样式
  lv_obj_add_style(page.p[index], &style_squareShape, LV_STATE_DEFAULT); // 设置方型样式
  lv_obj_set_scrollbar_mode(page.p[index], LV_SCROLLBAR_MODE_OFF); // 关闭滑动条

  lv_group_add_obj(group_my, page.p[index]); // 将对象邦定到组
  lv_obj_add_event_cb(page.p[index], display_networkConfig_event, LV_EVENT_KEY, NULL);

  String obj_name[7];
  uint8_t count = 0;
  String prompt = F("请连接热点,浏览器输入192.168.3.3");
  if (eep_language == 0)
  {
    obj_name[count++] = F("配网模式");
    obj_name[count++] = F("热点名称");
    obj_name[count++] = ap_ssid;
    obj_name[count++] = F("热点密码");
    obj_name[count++] = ap_password;
    if (pw_state == 1) // 1-WiFi未配置
    {
      obj_name[count++] = F("未配置WIFI");
    }
    else if (pw_state == 3 || pw_state == 4) //3-有配置但连接失败 4-连接成功
    {
      obj_name[count] = F("连接");
      obj_name[count] += eep_sta_ssid;
      if (pw_state == 3) obj_name[count] += F("失败");
      else if (pw_state == 4)
      {
        obj_name[count] += F("成功");
        prompt = F("热点192.168.3.3或同一网络");
        prompt += WiFi.localIP().toString();
      }
      count++;
    }
    obj_name[count] = prompt;
  }

  lv_obj_t *obj[4];
  lv_obj_t *label[7];
  uint8_t objPos = 0;
  uint8_t labelPos = 0;

  //配网模式背景
  obj[objPos] = lv_obj_create(page.p[index]); // 创建基本对象
  lv_obj_set_size(obj[objPos], 72, 24);
  lv_obj_align(obj[objPos], LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_set_style_bg_color(obj[objPos], MY_COLOR_GREEN, LV_STATE_DEFAULT);   // 背景颜色
  lv_obj_set_style_text_color(obj[objPos], MY_COLOR_BLACK, LV_STATE_DEFAULT); // 字体颜色
  lv_obj_add_style(obj[objPos], &style_shadow, LV_STATE_DEFAULT);           // 设置阴影样式
  lv_obj_add_style(obj[objPos], &style_squareShape, LV_STATE_DEFAULT);      // 设置方型样式
  lv_obj_set_scrollbar_mode(obj[objPos], LV_SCROLLBAR_MODE_OFF);              // 关闭滑动条
  // 配网模式标签
  label[labelPos] = lv_label_create(obj[objPos]);                             // 创建标签
  lv_obj_align(label[labelPos], LV_ALIGN_CENTER, 0, 2);                       // 居中对齐
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str());             // 标签

  // 热点名称背景
  objPos++;
  obj[objPos] = lv_obj_create(page.p[index]); // 创建基本对象
  lv_obj_set_size(obj[objPos], 72, 36);
  lv_obj_align_to(obj[objPos], obj[objPos - 1], LV_ALIGN_OUT_BOTTOM_MID, 0, 2);
  lv_obj_set_style_bg_color(obj[objPos], MY_COLOR_CYAN, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_add_style(obj[objPos], &style_shadow, LV_STATE_DEFAULT);           // 设置阴影样式
  lv_obj_add_style(obj[objPos], &style_squareShape, LV_STATE_DEFAULT);      // 设置方型样式
  lv_obj_set_scrollbar_mode(obj[objPos], LV_SCROLLBAR_MODE_OFF);           // 关闭滑动条
  // 热点名称标签
  labelPos++;
  label[labelPos] = lv_label_create(obj[objPos]);                 // 创建标签
  lv_obj_align(label[labelPos], LV_ALIGN_TOP_MID, 0, 0);          // 居中对齐
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str()); // 标签
  // 热点名称名称标签
  labelPos++;
  label[labelPos] = lv_label_create(obj[objPos]); // 创建标签
  lv_obj_set_style_text_font(label[labelPos], &MiSans_Bold_14px, LV_STATE_DEFAULT);
  lv_obj_align(label[labelPos], LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str()); // 标签内容

  // 热点密码背景
  objPos++;
  obj[objPos] = lv_obj_create(page.p[index]); // 创建基本对象
  lv_obj_set_size(obj[objPos], 72, 36);
  lv_obj_align_to(obj[objPos], obj[objPos - 1], LV_ALIGN_OUT_BOTTOM_MID, 0, 2);
  lv_obj_set_style_bg_color(obj[objPos], MY_COLOR_CYAN, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_add_style(obj[objPos], &style_shadow, LV_STATE_DEFAULT);           // 设置阴影样式
  lv_obj_add_style(obj[objPos], &style_squareShape, LV_STATE_DEFAULT);      // 设置方型样式
  lv_obj_set_scrollbar_mode(obj[objPos], LV_SCROLLBAR_MODE_OFF);           // 关闭滑动条
  // 热点密码标签
  labelPos++;
  label[labelPos] = lv_label_create(obj[objPos]);                 // 创建标签
  lv_obj_align(label[labelPos], LV_ALIGN_TOP_MID, 0, 0);
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str()); // 标签
  // 热点密码密码标签
  labelPos++;
  label[labelPos] = lv_label_create(obj[objPos]); // 创建标签
  lv_obj_align(label[labelPos], LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_set_style_text_font(label[labelPos], &MiSans_Bold_14px, LV_STATE_DEFAULT);
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str()); // 标签内容

  // 连接失败/成功、网址提示提示背景
  objPos++;
  obj[objPos] = lv_obj_create(page.p[index]);                                 // 创建基本对象
  lv_obj_set_style_text_color(obj[objPos], MY_COLOR_WHITE, LV_STATE_DEFAULT); // 字体颜色
  lv_obj_set_size(obj[objPos], 72, 42);
  lv_obj_align_to(obj[objPos], obj[objPos - 1], LV_ALIGN_OUT_BOTTOM_MID, 0, 2);
  lv_obj_set_style_bg_color(obj[objPos], MY_COLOR_BLACK, LV_STATE_DEFAULT); // 背景颜色
  lv_obj_add_style(obj[objPos], &style_shadow, LV_STATE_DEFAULT);           // 设置阴影样式
  lv_obj_add_style(obj[objPos], &style_squareShape, LV_STATE_DEFAULT);      // 设置方型样式
  lv_obj_set_scrollbar_mode(obj[objPos], LV_SCROLLBAR_MODE_OFF);            // 关闭滑动条
  // 连接失败/成功提示
  labelPos++;
  label[labelPos] = lv_label_create(obj[objPos]); // 创建标签
  lv_obj_update_layout(obj[objPos]);
  lv_obj_set_width(label[labelPos], lv_obj_get_width(obj[objPos])); // 设置标签大小与父对象相同
  lv_obj_align(label[labelPos], LV_ALIGN_TOP_MID, 0, 2);
  lv_label_set_long_mode(label[labelPos], LV_LABEL_LONG_SCROLL); // 设置长字符模式
  lv_obj_set_style_anim_duration(label[labelPos], 3000, 0);
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str()); // 标签内容
  // 连接网址提示
  labelPos++;
  label[labelPos] = lv_label_create(obj[objPos]); // 创建标签
  lv_obj_update_layout(obj[objPos]);
  lv_obj_set_width(label[labelPos], lv_obj_get_width(obj[objPos])); // 设置标签大小与父对象相同
  lv_obj_align(label[labelPos], LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_label_set_long_mode(label[labelPos], LV_LABEL_LONG_SCROLL_CIRCULAR); // 设置长字符模式
  lv_label_set_text(label[labelPos], obj_name[labelPos].c_str());         // 标签内容
}