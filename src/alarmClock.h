

void updatealarmClockDifference(bool mod) //更新闹钟时间差
{
  //耗时17ms
  uint32_t time0 = millis();
  AC_timeCount = 0;
  AC_timeTarget = alarmClockTimeDifference(mod);
  Serial.print("AC_timeTarget:");Serial.println(AC_timeTarget);
  // Serial.print("耗时:");Serial.println(millis()-time0);
}

// 闹钟计寻找最小的时间差
// retuen -100000暂停 -100001文件打开失败 -100002时间芯片错误 -100003都为关闭 
// -100004响铃中 -100005时钟天气
// 返回的时间差单位为秒
// mod 0返回最小的正值 1返回绝对值最小的值
int32_t alarmClockTimeDifference(bool mod)
{
  //uint32_t time1 = millis();
  // 打开文件

  RX8010SJ::DateTime dateTime;

  File file = LittleFS.open(alarmClockRecord, "r");
  if (!file) return AC_FILE_FAIL;

  // 读取时钟
  if (clockChipReadCheck() != 1) return AC_CHIP_FAIL;
  dateTime = adapter.readDateTime();
  uint8_t week_dq = dateTime.dayOfWeek; // 星期 123456 0=星期天
  if (week_dq == 0) week_dq = 7;   // 对星期天进行转换 0 = 星期天
  uint8_t hour_dq = dateTime.hour;      // 时
  uint8_t minute_dq = dateTime.minute;  // 分
  uint8_t second_dq = dateTime.second;  // 秒
  //Serial.print("week_dq:");Serial.println(week_dq);
  //Serial.print("hour_dq:");Serial.println(hour_dq);
  //Serial.print("minute_dq:");Serial.println(minute_dq);
  
  //变量定义
  uint32_t timeCountCur = (hour_dq * 60 + minute_dq) * 60 + second_dq; // 转换成时间计数，方便之后的计算
  int32_t timeCountMin = AC_STOP; // 最小的时间计数
  bool offAll = 1;                // 是否都为关闭状态

  //Serial.printf("file.available():%d\n", file.available());

  while (file.available())
  {
    bool swEn = 0;   // 开关使能
    bool weekEn = 0; // 星期使能
    char c = file.read();

    // 读取到换行回车跳过
    if (c == '\n' || c == '\r') continue;

    // 闹钟有打开
    if(c == '1') 
    {
      offAll = 0; // 标记有
      swEn = 1; // 使能有打开
      for (uint8_t i = 0; i < 7; i++)
      {
        uint8_t week = char(file.read()) - 48;
        if (week == week_dq) weekEn = 1; // 星期存在
      }
    }

    // 星期存在，提取时间
    if (weekEn == 1)
    {
      int32_t timeCountTar = AC_STOP; // 目标时间计数
      String hour, minute;
      hour += char(file.read());
      hour += char(file.read());
      minute += char(file.read());
      minute += char(file.read());

      //****** 对比时间计数
      //提取
      timeCountTar = (atoi(hour.c_str()) * 60 + atoi(minute.c_str())) * 60;

      // 刚好等于，立即响应
      if (timeCountCur == timeCountTar)  return 0;
      // 时间未到
      else
      {
        int32_t cz = timeCountTar - timeCountCur;

        if (timeCountMin == AC_STOP)
        {
          if (mod == 0 && cz > 0) timeCountMin = cz;
          else if (mod == 1)      timeCountMin = cz;
        }

        if (mod == 0 && cz > 0 && cz < timeCountMin) // 返回最小的正值
        {
          timeCountMin = cz;
        }
        else if (mod == 1 && abs(cz) < abs(timeCountMin)) //返回绝对值最小的值
        {
          timeCountMin = cz;
        }
        //Serial.print("差值:");Serial.println(cz);
      }

    }

    // 闹钟关闭 或 星期不存在，移动至下一行
    else
    {
      int16_t residue = file.available();
      //Serial.printf("residue:%d\n", residue);
      if (swEn == 0 && residue > 13)       file.seek(13, SeekCur);
      else if (weekEn == 0 && residue > 6) file.seek(6, SeekCur);
      else break;
    }
  }

  //文件读取完毕
  file.close();
  //Serial.print("耗时:"); Serial.println(millis() - time1);
  if (offAll) timeCountMin = AC_ALL_OFF;
  return timeCountMin;
}//end main

// 闹钟监测
void buzzerMonitor_end_cb(lv_event_t *e) //  闹钟监测 弹窗退出
{
  uint8_t *data = (uint8_t *)lv_event_get_user_data(e);
  if (data[0] == 0 || data[0] == 1)
  {
    stopMidi();
    updatealarmClockDifference(); // 更新闹钟时间差
    my_msgbox_exit(0);    // 退出弹窗
  }
}
void buzzerMonitor()
{
  /* enum ACState
  {
    AC_STOP = -100000,      // 暂停
    AC_FILE_FAIL = -100001, // 文件打开失败
    AC_CHIP_FAIL = -100002, // 时间芯片错误
    AC_ALL_OFF = -100003,   // 都为关闭
    AC_RINGING = -100004,   // 响铃中
    AC_WAKE_UP = -100005,   // 时钟唤醒有闹钟
  };*/
  if (AC_timeTarget >= 0 || AC_timeTarget == AC_WAKE_UP)
  {
    // 每512秒更新一次目标时间
    if (bitRead(AC_timeCount, 10) == 1)
    {
      // Serial.println("每512秒更新一次目标时间");
      updatealarmClockDifference(); // 更新闹钟时间差
    }
    // 到达目标时间
    else if (AC_timeCount >= AC_timeTarget || AC_timeTarget == AC_WAKE_UP)
    {
      // Serial.println("闹钟时间到");
      stopMidi();
      clock_read();
      String h = String(curTime.hour);
      String m = String(curTime.minute);
      String time;
      if (curTime.hour <= 9) h = "0" + h;
      if (curTime.minute <= 9)  m = "0" + m;
      time = h + ":" + m;
      //Serial.printf("curTime.hour:%d\n", curTime.hour);
      //Serial.printf("curTime.minute:%d\n", curTime.minute);
      //Serial.printf("curTime.second:%d\n", curTime.second);
      my_msgbox_forceSend(F("闹钟响"), time, 0, F("知道了\n返回\n"), buzzerMonitor_end_cb);
      AC_timeTarget = AC_RINGING; // 标记响铃中
      AC_timeCount = 0;        // 计数归零
      overTime = 0;            // 超时时间归零

      bool ok = 0;
      if (eep_alarmSound.length() > 1)
      {
        File file = LittleFS.open(eep_alarmSound);
        if (file)
        {
          midi_rtos_init((void *)eep_alarmSound.c_str());
          ok = 1;
        }
      }
      if (ok == 0)
      {
        const char *p = "/system/AC.mid";
        midi_rtos_init((void *)p);
      }
    }
    
    AC_timeCount++;
  }
}