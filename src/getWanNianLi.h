
void getWanNianLi_rtos(void *param);
String json_wanNianLi(String input, String &date)
{
  JsonDocument filter;
  filter.set(true);

  JsonDocument doc;

  DeserializationError error = deserializeJson(doc, input, DeserializationOption::Filter(filter));

  if (error)
  {
    //Serial.print(F("deserializeJson() failed: "));
    //Serial.println(error.f_str());
    return F("error:Json");
  }

  String out;

  int error1 = doc[F("errno")];          // 0
  const char *errmsg = doc[F("errmsg")]; // nullptr
  if (error1 > 0)
  {
    out = F("error:");
    out += errmsg;
    return out;
  }

  JsonObject data = doc[F("data")];
  int data_year = data[F("year")];   // 2025
  int data_month = data[F("month")]; // 1
  int data_day = data[F("day")];     // 30
  date = String(data_year) + " ";
  date += String(data_month) + " ";
  date += String(data_day) + " ";

  JsonObject data_almanac = data[F("almanac")];
  const char *data_almanac_yi = data_almanac[F("yi")]; // "纳采 订盟 祭祀 祈福 求嗣 斋醮 沐浴 进人口 会亲友 入学 治病 安碓磑 掘井 开池 纳畜 ...
  const char *data_almanac_ji = data_almanac[F("ji")]; // "嫁娶 合帐 入宅 行丧 安葬"
  out = data_almanac_yi;
  out += "\n";
  out += data_almanac_ji;
  out += " ";
  return out;
}

// 创建获取万年历任务
void getWanNianLi_rtos_init()
{
    xTaskCreatePinnedToCore(
        getWanNianLi_rtos, /* 任务指针，创建任务用的那个函数名 */
        "getWanNianLi",    /* 任务名称 */
        8 * 1024,         /* 任务栈大小，根据需要自行设置*/
        NULL,             /* 可选参数，一般不填*/
        1,                /* 优先级 */
        &TH_getWanNianLi, /* 任务句柄，用于后续挂起或恢复运行*/
        0                 /* 核ID */
    );
}
// 获取万年历任务
void getWanNianLi_rtos(void *param)
{
  String date;
  String conten;
  String out;
  String title, text;
  String rec;
  uint8_t nyr_state = 0; // 年月日状态 0-年 1-月 2-日
  bool retry = 0;
GET:
  File file = LittleFS.open(wanNianLiRecord, "r");
  if (!file)
  {
    int code;
    String message;
    File file1;
    title = F("连接WIFI");
    text = eep_sta_ssid;
    my_msgbox_send(title.c_str(), text.c_str());
    if (!connectToWifi())
    {
      // wifi连接失败
      text = F("失败");
      goto exit0; // 退出
    }
    // 更新时钟芯片
    if (ntpConnect()) ntpToClockChip();

    title = F("万年历");
    text = F("获取消息");
    my_msgbox_send(title, text);

    message = callHttps(F("https://api.timelessq.com/time"), &code);
    if (code < 0)
    {
      title = F("获取失败");
      text = message;
      goto exit0; // 退出
    }
    file1 = LittleFS.open(wanNianLiRecord, "w+");
    bool ok = file1.print(message);
    if (ok == 0)
    {
      title = F("LittleFS");
      text = F("写入失败");
      goto exit0; // 退出
    }
    file1.close();
  }

  file = LittleFS.open(wanNianLiRecord, "r");
  while (file.available())
    conten += char(file.read());
  file.close();

  out = json_wanNianLi(conten, date);
  //Serial.printf("out:%s\n", out.c_str());
  //Serial.printf("date:%s\n", date.c_str());

  // 检查日期是否是今日
  clock_read();
  //Serial.printf("curTime.year:%d\n", curTime.year);
  //Serial.printf("curTime.month:%d\n", curTime.month);
  //Serial.printf("curTime.dayOfMonth:%d\n", curTime.dayOfMonth);
  for (uint8_t i = 0; i < date.length(); i++)
  {
    char c = date[i];
    if (c != ' ')
    {
      rec += date[i];
    }
    else if (c == ' ')
    {
      uint16_t num = atoi(rec.c_str());
      //Serial.printf("num:%d\n", num);
      if (nyr_state == 0 && num < curTime.year + 2000)
        goto remove;
      else if (nyr_state == 1 && num < curTime.month)
        goto remove;
      else if (nyr_state == 2 && num < curTime.dayOfMonth)
        goto remove;
      rec.clear();
      nyr_state++;
    }
  }

  xSemaphoreTake(lvgl_mutex, portMAX_DELAY); //xSemaphoreGive(lvgl_mutex);
  focusPosOld_save(); // 保存上一个界面的焦点
  display_wanNianLi_init(out);
  lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
  onGlobalJitter(1000); // 打开全局抖动
  xSemaphoreGive(lvgl_mutex);
  my_msgbox_exit(100); // 退出弹窗
  goto exit1;
  //title = F("万年历");
  //text = F("获取成功");

exit0:
  delay(MSGBOX_ANIM_TIME2);
  my_msgbox_send(title, text, 1500);
exit1:
  WiFi.mode(WIFI_OFF);
  bitWrite(backgroundTask, BGT_GET_WanNianLi, 0); // 关闭任务
  TH_getWanNianLi = NULL;
  Serial.println("删除TH_getWanNianLi");
  vTaskDelete(NULL); // 删除自己

remove:
  LittleFS.remove(wanNianLiRecord);
  date.clear();
  conten.clear();
  out.clear();
  rec.clear();
  nyr_state = 0;
  if (retry == 1)
  {
    title = F("万年历");
    text = F("重试失败");
  }
  else retry = 1;
  goto GET;
}