
void checkUpdate_rtos(void *param);
// 创建检查更新任务
void checkUpdate_rtos_init()
{
  xTaskCreatePinnedToCore(
      checkUpdate_rtos, /* 任务指针，创建任务用的那个函数名 */
      "checkUpdate",    /* 任务名称 */
      16 * 1024,         /* 任务栈大小，根据需要自行设置*/
      NULL,             /* 可选参数，一般不填*/
      2,                /* 优先级 */
      &TH_checkUpdate,  /* 任务句柄，用于后续挂起或恢复运行*/
      0                 /* 核ID */
  );
}
// 检查更新任务
void checkUpdate_rtos(void *param)
{
  String title, text;
  String add = F("https://gitee.com/Lichengjiez/ESP32C3-JDI-LCD-LVGL/raw/main/updateLog.json");
  String message;
  String str;

  JsonDocument doc;
  DeserializationError error;
  const char *version; // "074"
  const char *address; // 更新地址
  uint32_t size;       // 文件大小
  const char *content; // 更新内容

  //****** 检查WIFI是否有配置
  if (eep_sta_ssid.length() < 1)
  {
    title = F("连接WIFI");
    text = "WIFI未配置";
    goto exit0; // 退出
  }

  //****** 连接WIFI
  title = F("连接WIFI");
  text = eep_sta_ssid;
  my_msgbox_send(title, text);
  if (!connectToWifi()) // wifi连接失败
  {
    text = F("失败");
    goto exit0; // 退出
  }

  //****** 获取消息
  title = F("检查更新");
  text = F("获取消息");
  my_msgbox_send(title, text);
  delay(500);
  int code;
  message = callHttps(add, &code);
  if (code <= 0)
  {
    title = F("获取失败");
    text = message;
    goto exit0; // 退出
  }
  // Serial.printf("code:%d\n", code);

  //****** 解析json
  deserializeJson(doc, message);
  message.clear(); // 释放内存
  if (error)
  {
    title = F("Json失败");
    text = error.c_str();
    goto exit0; // 退出
  }
  version = doc["version"]; // "015"
  address = doc["address"]; // 更新地址
  size = doc["size"];       // 文件大小
  content = doc["content"]; // 更新内容

  //****** 显示更新内容
  //Serial.printf("version:%s\n",version);
  //Serial.printf("content:%s\n",content);

  xSemaphoreTake(lvgl_mutex, portMAX_DELAY); // xSemaphoreGive(lvgl_mutex);
  focusPosOld_save(); // 保存上一个界面的焦点
  display_checkUpdate_init(version, content);
  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 10, true);
  onGlobalJitter(); // 打开全局抖动
  xSemaphoreGive(lvgl_mutex);

  // Serial.println("退出弹窗checkUpdate");
  my_msgbox_exit(100); // 退出弹窗

  goto exit1; // 退出

//****** 退出
exit0:
  delay(MSGBOX_ANIM_TIME2);
  my_msgbox_send(title, text, 1500);
exit1:
  WiFi.mode(WIFI_OFF);
  bitWrite(backgroundTask, BGT_CHECK_UPDATE, 0);
  TH_checkUpdate = NULL;
  Serial.println("删除TH_checkUpdate");
  vTaskDelete(NULL); // 删除自己
}