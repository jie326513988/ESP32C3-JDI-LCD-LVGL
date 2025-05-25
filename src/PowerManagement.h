#define uS_TO_S_FACTOR 1000000ULL // 微秒到秒的转换系数
// 系统休眠 millisecond休眠时间毫秒 skip是否跳过闹钟
void sleepWallpaper() //休眠壁纸
{
  // 自定义图片打开成功
  uint16_t time0 = 50;
  if (eep_sleepPicEn && eep_sleepPic.length() > 1)
  {
    File file = LittleFS.open(eep_sleepPic);
    if (file)
    {
      display_picture_init(eep_sleepPic, 0);
      lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
      eep_doudong = 0;
      time0 = 4000;
    }
    file.close();
  }

  // 创建一个单次定时器,3秒后让系统永久休眠
  lv_timer_t *timer = lv_timer_create(sleep_zero_time_cb, time0, NULL); // 4秒后打开
  lv_timer_set_repeat_count(timer, 1);
  lv_timer_set_auto_delete(timer, true);
}

void esp_sleep(unsigned long millisecond, bool skip) 
{
  //vTaskDelete(HT_get_bat_vcc); // 删除任务

  Serial.printf("休眠:%d\n", millisecond);

  RTC_disPage_old = eep_disPage;

  //标记需要定时唤醒
  if (eep_disPage == page_clock)
    RTC_timedWakeUp = 1;

  ledcWrite(EXTCOMIN_CHANNEL, 0); // 占空比
  ledcDetachPin(EXTCOMIN_PIN);    // 卸载引脚

  ledcWrite(BUZZER_CHANNEL, 0); // 占空比
  ledcDetachPin(BUZZER_PIN);    // 卸载引脚

  ledcWrite(LED_CHANNEL, 0); // 占空比
  ledcDetachPin(LED_PIN);    // 卸载引脚

  jdi_display.noUpdate(); // 停止更新

  bool displayXP = 0; // 息屏状态
  // 息屏打开
  if (eep_clockSleepOffScreen && eep_disPage == page_clock)
  {
    jdi_display.displayOff();
    displayXP = 1;
  }
  else if (eep_otherSleepOffScreen && eep_disPage != page_clock && eep_disPage != page_memo)
  {
    jdi_display.displayOff();
    displayXP = 1;
  }

  // 关闭加速度计
  acce.softReset();
  acce.setDataRate(DFRobot_LIS2DW12::eRate_0hz);
  acce.setPowerMode(DFRobot_LIS2DW12::eSingleLowPwrLowNoise1_12bit);

  // 关闭空气质量传感器
  #if AIR_TYPE > 0
    if (bitRead(backgroundTask, BGT_AIR_READ) == 1)
    {
        #if AIR_TYPE == 1
            sgp41.turnHeaterOff();
        #elif AIR_TYPE == 2
            myENS.setOperatingMode(SFE_ENS160_DEEP_SLEEP);
            //ens160.setSleep();
        #endif
    }
  #endif

  // 按动唤醒常驻
  if (eep_WU_AnDong)
  {
    pinMode(KEY_ADC_PIN, INPUT_PULLUP);
    esp_deep_sleep_enable_gpio_wakeup(BIT(KEY_ADC_PIN), ESP_GPIO_WAKEUP_GPIO_LOW);
  }
  // 抬手唤醒
  if (eep_WU_TaiShou)
  {
    bool open = 0;
    // 时钟界面息屏功能 打开
    if(eep_disPage == page_clock && eep_clockSleepOffScreen == 1) open=1;
    // 其他界面打开
    else if(eep_disPage != page_clock)  open=1;
    if (open)
    {
      acc_6d();
      pinMode(ACCINT_PIN, INPUT_PULLDOWN); // 拉低
      delay(5);
      // 检测到高电平唤醒
      esp_deep_sleep_enable_gpio_wakeup(BIT(ACCINT_PIN), ESP_GPIO_WAKEUP_GPIO_HIGH);
    }
  }

  // 闹钟存在，在0点0分1秒时唤醒
  if (millisecond == 0 && eep_disPage != page_clock && AC_timeTarget == AC_STOP)
  {
    clock_read();
    RTC_ac_wp = 86400 - (curTime.hour * 3600 + curTime.minute * 60 + curTime.second);
    RTC_ac_wp += 2; //多休眠2秒
    RTC_ac_wp *= 1000; //转换成毫秒
  }
  else RTC_ac_wp = 0;

  SPI.end();
  Wire.end();
  WiFi.mode(WIFI_OFF);

  //Serial.print("millisecond:");Serial.println(millisecond);
  // 要使得 gpio0 唤醒，下面 2 行代码是关键
  //pinMode(KEY_ADC_PIN, INPUT_PULLUP);

  gpio_hold(1);

  // 有闹钟时，按闹钟时间唤醒
  if (eep_disPage != page_clock)
  {
    int32_t num = AC_timeTarget - AC_timeCount;
    if (num > 0)
    {
      Serial.printf("num:%d\n", num);
      // 闹钟需要的时间大于输入的秒
      if (num > millisecond && millisecond != 0)
      {
        esp_deep_sleep(millisecond * 1000ULL);
      }
      else
      {
        // 提前3秒唤醒
        int16_t num2 = num - 3;
        if(num <= 0) esp_deep_sleep(100);
        else         esp_deep_sleep(num2 * 1000ULL * 1000ULL);
      }
    }
    //暂停时，明天0点再唤醒检查一次
    else if (RTC_ac_wp != 0) esp_deep_sleep(RTC_ac_wp);
  }

  if (millisecond != 0)
  {
    //Serial.printf("111111\n");
    esp_deep_sleep(millisecond * 1000ULL);
  }
  else
  {
    //Serial.printf("2222222\n");
    esp_deep_sleep_start(); // 永久休眠
  }

  /*if (second != 0)
    esp_sleep_enable_timer_wakeup(second * 1000ULL);//启动定时器唤醒
  else
  {
    // 此函数用于停用定义为函数参数的源的唤醒触发器。
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
  }
  esp_deep_sleep_start();*/

  //esp_deep_sleep(second * 1000ULL);
}

//配置睡眠期间是否锁定引脚状态
void gpio_hold(bool en)
{
  if (en)
  {
    esp_sleep_config_gpio_isolate(); // 配置以隔离处于睡眠状态的所有GPIO引脚

    //pinMode(GPIO_NUM_0, INPUT);
    pinMode(GPIO_NUM_1, INPUT);
    pinMode(GPIO_NUM_2, INPUT);
    pinMode(GPIO_NUM_7, INPUT_PULLDOWN);
    pinMode(GPIO_NUM_8, INPUT_PULLDOWN);
    pinMode(GPIO_NUM_10, INPUT_PULLDOWN);
    pinMode(GPIO_NUM_4, INPUT_PULLUP);
    pinMode(GPIO_NUM_5, INPUT_PULLUP);

    pinMode(BUZZER_PIN, OUTPUT); // 关闭蜂鸣器
    digitalWrite(BUZZER_PIN, 0);

    pinMode(LED_PIN, OUTPUT); // 关闭LED
    digitalWrite(LED_PIN, 0);

#if AIR_TYPE == 1
    pinMode(AIR_POWER_PIN, OUTPUT); // 关闭空气质量
    digitalWrite(AIR_POWER_PIN, 0);
#endif

    // 启用gpio保持功能。
    gpio_hold_en(GPIO_NUM_0);
    gpio_hold_en(GPIO_NUM_1);
    gpio_hold_en(GPIO_NUM_2); // KEY ADC
    gpio_hold_en(GPIO_NUM_3);
    gpio_hold_en(GPIO_NUM_4);
    gpio_hold_en(GPIO_NUM_5);
    gpio_hold_en(GPIO_NUM_6);  // 显示器ON/OFF开关信号引脚
    gpio_hold_en(GPIO_NUM_7);  // SPI_CS
    gpio_hold_en(GPIO_NUM_8);  // SPI_SCLK
    gpio_hold_en(GPIO_NUM_10); // SPI_MOSI
    // gpio_hold_en(GPIO_NUM_20); // SPI_MOSI
    gpio_hold_en(GPIO_NUM_21);

    gpio_deep_sleep_hold_en(); // 在深度睡眠期间启用所有数字gpio pads保持功能。
  }
  else
  {
    // 禁用gpio保持功能
    gpio_hold_dis(GPIO_NUM_0);
    gpio_hold_dis(GPIO_NUM_1);
    gpio_hold_dis(GPIO_NUM_2);  // KEY ADC
    gpio_hold_dis(GPIO_NUM_3);
    gpio_hold_dis(GPIO_NUM_4);
    gpio_hold_dis(GPIO_NUM_5);
    gpio_hold_dis(GPIO_NUM_6);  // 显示器ON/OFF开关信号引脚
    gpio_hold_dis(GPIO_NUM_7);  // SPI_CS
    gpio_hold_dis(GPIO_NUM_8);  // SPI_SCLK
    gpio_hold_dis(GPIO_NUM_10); // SPI_MOSI
    //gpio_hold_dis(GPIO_NUM_20);
    gpio_hold_dis(GPIO_NUM_21);
    gpio_deep_sleep_hold_dis(); // 在深度睡眠期间禁用所有数字gpio键盘保持功能。
  }
}

uint8_t print_wakeup_reason() //打印启动的原因
{
  esp_sleep_wakeup_cause_t wakeup_reason;
  String str[] = {
      F("使用RTC_IO由外部信号引起的唤醒"),
      F("使用RTC_CNTL由外部信号引起的唤醒"),
      F("计时器引起的唤醒"),
      F("触摸板引起的唤醒"),
      F("ULP程序导致的唤醒"),
      F("GPIO引起的唤醒"),
  };
  wakeup_reason = esp_sleep_get_wakeup_cause(); // 获取休眠唤醒原因

  if (wakeup_reason >= 2 && wakeup_reason <= 7) //ESP_SLEEP_WAKEUP_EXT0
  {
    uint8_t pos = wakeup_reason - 2;
    Serial.println(str[pos]);
  }
  else
  {
    Serial.print(F("其他原因唤醒:"));
    Serial.println(wakeup_reason);
  }
  return wakeup_reason;
}

/*void esp_sleep_cb(lv_anim_t *a)
{  
  uint32_t *data = (uint32_t *)lv_anim_get_user_data(a);
  uint32_t i = data[0];
  if (i > 100)// 重新计算休眠时间
  {
    clock_read();
    sleepTime = 60000 - (curTime.second * 1000);
    if (sleepTime <= 0) sleepTime = 100;  
    i = sleepTime;
  }
  esp_sleep(i);
}*/
void esp_sleep_cb(lv_timer_t *time)
{  
  uint32_t *data = (uint32_t *)lv_timer_get_user_data(time);
  uint32_t i = data[0];
  if (i > 100)// 重新计算休眠时间
  {
    clock_read();
    sleepTime = 60000 - (curTime.second * 1000);
    if (sleepTime <= 0) sleepTime = 100;  
    i = sleepTime;
  }
  esp_sleep(i);
}

void dormantTimeoutDecision() // 休眠和超时决策
{
  static bool sleepState = 0; // 休眠操作只执行一次的标志位
  if(sleepState == 1) return;

  uint16_t callbackTime = 0; // 设置多少豪秒后执行回调

  // 电量检查 电量低 3.35-2.0
  if ((bat_vcc < BAT_LOW2 && bat_vcc > 2.0) && RTC_timedWakeUp == 0) // BAT_LOW2
  {
    eep_WU_TaiShou = 0; // 临时关闭抬手唤醒
    sleepState = 1;
    
    my_msgbox_forceSend(F("电量低"), F("已休眠"));       // 强制发送
    //my_msgbox(F("电量低"), F("已休眠"));
    callbackTime = 2000;  // 设置多少豪秒后执行回调
  }
  //时钟下休眠，打开定时唤醒
  else if (eep_disPage == page_clock && overTime > eep_clockSleep)
  {
    if (AC_timeTarget == -10004 || AC_timeTarget == -10005) // 闹钟播放中
      overTime = 0; // 超时归零
    else
    {
      sleepState = 1;
      bitWrite(backgroundTask, BGT_CLOCK_READ, 0); // 标记关闭
      lv_obj_delete(label_timeSecond);
      label_timeSecond = NULL;
      // 创建一个单次定时器
      lv_timer_t *timer = lv_timer_create(clockTimedWakeUp_time_cb, 100, &sleepTime);
      lv_timer_set_repeat_count(timer, 1);
      lv_timer_set_auto_delete(timer, true);
      return;
    }
  }
  // 非时钟下，永久休眠
  else if(eep_disPage != page_clock /*&& overTime > eep_otherSleep*/)
  {
    // 配网界面 10分钟后休眠
    if (eep_disPage == page_networkConfig && overTime < 10 * 60)
      return;
    // 空气质量界面自定义休眠时间
    if (eep_disPage == page_uartAir && overTime < eep_airSleep * 60)
      return;
    if (eep_disPage == page_memo && overTime < 1 * 20) //备忘录界面20秒进入休眠
      return;

    bool pop = 1;
    if (overTime > eep_otherSleep) // 其他界面，按设置休眠
    {
      sleepState = 1;
      callbackTime = 900; // 设置多少豪秒后执行回调
      // 开启备忘录时休眠显示备忘录
      if (eep_memoSleepEn && eep_inAWord.length() > 1)
      {
        display_memo_init();
        lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
        onGlobalJitter(); // 打开全局抖动
        pop = 0;// 关闭弹窗
      }
      // 开启休眠壁纸时
      else if (eep_sleepPicEn && eep_sleepPic.length() > 1)
      {
        File file = LittleFS.open(eep_sleepPic);
        if (file)
        {
          display_picture_init(eep_sleepPic, 0);
          lv_screen_load_anim(page.p[page.index], LV_SCR_LOAD_ANIM_FADE_IN, GRADUAL_ANIM_TIME, 0, true);
          eep_doudong = 1;
          callbackTime = 3000; // 设置多少豪秒后执行回调
          pop = 0;// 关闭弹窗
        }
        file.close();
      }

      if (pop == 1) my_msgbox_forceSend(F("省电"), F("已休眠")); // 强制发送
    }
  }
  
  if(sleepState == 0) return;
  sleepTime = 0; // 设置永久休眠
  // 创建一个单次定时器
  lv_timer_t *timer = lv_timer_create(esp_sleep_cb, callbackTime, &sleepTime);
  lv_timer_set_repeat_count(timer, 1);
  lv_timer_set_auto_delete(timer, true);
}