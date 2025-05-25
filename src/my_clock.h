#include <RX8010SJ.h>

RX8010SJ::Adapter adapter = RX8010SJ::Adapter(CLOCK_I2C_ADDR);
RX8010SJ::DateTime curTime = RX8010SJ::DateTime();; //当前显示的时间
RX8010SJ::DateTime sdjzTime; //手动校准用的时间

#include <NTPClient.h>
#include <WiFiUdp.h>
// ntp时间设置
#define SECONDS_IN_DAY 86400 // 一天中的秒数
#define START_YEAR 1970      // 开始年份
#define TIME_ZONE +8         // 默认时区
static uint8_t days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char *NTPadd[5] PROGMEM = {
    "ntp1.aliyun.com",
    "time1.cloud.tencent.com",
    "ntp.ntsc.ac.cn",
    "ntp2.aliyun.com",
    "time1.apple.com",
};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTPadd[0], TIME_ZONE * 3600, 60000); // udp，服务器地址，时间偏移量，更新间隔
struct ntpDate //ntp获取日期的结构体
{
  uint16_t year, month, day;
};
void clock_read() // 读取时钟芯片的时间
{
  if (bitRead(ic_state, IC_CLOCK) == 1)
    curTime = adapter.readDateTime();
}
// 读取时钟数据是否正常 0错误 1正常
bool clockChipReadCheck()
{
    if(!i2cChipExist(CLOCK_I2C_ADDR))  return 0;
    curTime = adapter.readDateTime();
    if      (curTime.year < 24      || curTime.year > 99)       return 0;
    else if (curTime.month <= 0     || curTime.month > 12)      return 0;
    else if (curTime.dayOfMonth < 0 || curTime.dayOfMonth > 31) return 0;
    else if (curTime.hour < 0       || curTime.hour >= 24)      return 0;
    else if (curTime.minute < 0     || curTime.minute >= 60)    return 0;
    else if (curTime.second < 0     || curTime.second >= 60)    return 0;
    else return 1;
}
// 检查是否掉电了 0错误 1正常
bool clockChipPowerDown()
{
    if (!i2cChipExist(CLOCK_I2C_ADDR)) return 0;
    
    // 此函数检查VLF-bit是否为 1  当读到的 VLF-bit 为 1 的时候，必须对 RTC 进行初始化。
    if (adapter.initAdapter())  return 0;
    return 1;
}
//ntp连接程序 0-失败 1-成功
bool ntpConnect()
{
  if (eep_ntpAdd.length() > 5) // 自定义地址存在
    timeClient.setPoolServerName(eep_ntpAdd.c_str());

  uint8_t count = 0;
  timeClient.begin();
  while (timeClient.update() == 0)
  {
    delay(1000);
    timeClient.setPoolServerName(NTPadd[count]);
    count++;
    if (count == 5)
    {
      timeClient.end();
      return 0;
    }
  }

  timeClient.end();
  return 1;
}

//将NTP数据写入时钟芯片内
bool ntpToClockChip()
{
  if (!i2cChipExist(CLOCK_I2C_ADDR))  return 0;
  
  ntpDate date;
  getNTPDate(timeClient.getEpochTime(), &date); // 获取日期

  curTime.hour = timeClient.getHours();     // 时
  curTime.minute = timeClient.getMinutes(); // 分
  curTime.second = timeClient.getSeconds(); // 秒
  curTime.dayOfWeek = timeClient.getDay();  // 星期
  curTime.dayOfMonth = date.day;            // 日
  curTime.month = date.month;               // 月
  curTime.year = date.year;                 // 年

  adapter.writeDateTime(curTime); //写入芯片

  return 1;
}
// 获取NTP的日期
void getNTPDate(uint32_t timeStamp, struct ntpDate *jgt) 
{
  unsigned int year = START_YEAR;
  while (1)
  {
    uint32_t seconds;
    if (isLeapYear(year)) seconds = SECONDS_IN_DAY * 366;
    else seconds = SECONDS_IN_DAY * 365;
    if (timeStamp >= seconds)
    {
      timeStamp -= seconds;
      year++;
    }
    else break;
  }

  unsigned int month = 0;
  while (1)
  {
    uint32_t seconds = SECONDS_IN_DAY * days_in_month[month];
    if (isLeapYear(year) && month == 1) seconds = SECONDS_IN_DAY * 29;
    if (timeStamp >= seconds)
    {
      timeStamp -= seconds;
      month++;
    } 
    else break;
  }
  month++;

  unsigned int day = 1;
  while (1)
  {
    if (timeStamp >= SECONDS_IN_DAY)
    {
      timeStamp -= SECONDS_IN_DAY;
      day++;
    }
    else  break;
  }

  jgt->year = year - 2000; // 年
  jgt->month = month;      // 月
  jgt->day = day;          // 日

  // unsigned int hour = timeStamp / 3600;
  // unsigned int minute = (timeStamp - (uint32_t)hour * 3600) / 60;
  // unsigned int second = (timeStamp - (uint32_t)hour * 3600) - minute * 60;

  // eep_year = String(year);   // 年
  // eep_month = String(month); // 月
  // eep_day = String(day);     // 日

  /*Serial.println("当前日期和时间:");

    if (day < 10) Serial.print("0");
    Serial.print(day);
    Serial.print("/");

    if (month < 10) Serial.print("0");
    Serial.print(month);
    Serial.print("/");

    Serial.println(year);

    if (hour < 10) Serial.print("0");
    Serial.print(hour);
    Serial.print(":");

    if (minute < 10) Serial.print("0");
    Serial.print(minute);
    Serial.print(":");

    if (second < 10) Serial.print("0");
    Serial.println(second);

    Serial.println();*/
}
//判断是否闰年
bool isLeapYear(uint16_t year) 
{
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

//获取月有多少天
uint8_t monthHowManyDay(uint16_t year, uint16_t month)
{
  uint8_t dayMax = days_in_month[month - 1];
  if (isLeapYear(year))
    if (month == 2)
      dayMax + 1;
  return dayMax;
}

//星期数字1234567转中文
String weekDigitalToChinese(uint8_t digital) 
{
  if (digital == 1)      return F("一");
  else if (digital == 2) return F("二");
  else if (digital == 3) return F("三");
  else if (digital == 4) return F("四");
  else if (digital == 5) return F("五");
  else if (digital == 6) return F("六");
  else if (digital == 0) return F("日");
  return F("error:digitalToChinese");
}

// 创建时钟自动校准任务
void clockAutoCali_rtos_init()
{
  //i2c_begin();
  xTaskCreatePinnedToCore(
      clockAutoCali_rtos, /* 任务指针，创建任务用的那个函数名 */
      "clockAutoCali",    /* 任务名称 */
      8 * 1024,           /* 任务栈大小，根据需要自行设置*/
      NULL,               /* 可选参数，一般不填*/
      2,                  /* 优先级 */
      &TH_clockAutoCali,  /* 任务句柄，用于后续挂起或恢复运行*/
      0                   /* 核ID */
  );
}
// 时钟自动校准任务
void clockAutoCali_rtos(void *param)
{
  //****** 连接WIFI
  String title, text;

  title = F("连接WIFI");
  text = eep_sta_ssid;
  my_msgbox_send(title, text);

  if (!connectToWifi())
  {
    // wifi连接失败
    text = F("失败");
    goto exit;  // 退出
  }

  //****** 连接NTP服务器
  delay(MSGBOX_ANIM_TIME2);
  title = F("NTP服务");
  text = F("连接中");
  my_msgbox_send(title, text);
  if (!ntpConnect()) // 连接NTP服务器
  {
    text = F("失败");
    goto exit; // 退出
  }
  delay(MSGBOX_ANIM_TIME2);

  //****** 数据写入时钟芯片
  title = F("时钟芯片");
  text = F("写入成功");
  if (!ntpToClockChip()) text = F("写入失败");

exit: // 退出
  delay(MSGBOX_ANIM_TIME2);
  WiFi.mode(WIFI_OFF);
  my_msgbox_send(title, text, 1500);
  bitWrite(backgroundTask, BGT_CLOCK_AUTU_CALI, 0);
  TH_clockAutoCali = NULL;
  vTaskDelete(NULL); // 删除自己
}

// 创建时钟读取任务
void clockRead_rtos_init()
{
  xTaskCreatePinnedToCore(
      clockRead_rtos, // 任务指针，创建任务用的那个函数名
      "clockRead",    // 任务名称
      4 * 1024,       // 任务栈大小，根据需要自行设置
      NULL,           // 可选参数，一般不填
      2,              // 优先级
      &TH_clockRead,  // 任务句柄，用于后续挂起或恢复运行
      0               // 核ID
  );
}
// 时钟读取任务
void clockRead_rtos(void *param)
{
  // 检查时钟芯片是否存在
  bool ok = i2cChipExist(CLOCK_I2C_ADDR);
  // 标记关闭时钟读取任务
  if (ok == 0)
    bitWrite(backgroundTask, BGT_CLOCK_READ, 0); 

  //Serial.print("ok:");Serial.println(ok);

  for (;;)
  {
    // 检查是否需要删除
    if (!bitRead(backgroundTask, BGT_CLOCK_READ))
    {
      Serial.println("删除TH_clockRead");
      TH_clockRead = NULL;
      vTaskDelete(NULL);
    }
    clock_read(); // 读取时钟数据
    //Serial.print("curTime.second:");Serial.println(curTime.second);
    delay(1000);
  }
}