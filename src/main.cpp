#include <Arduino.h>
#include <WiFi.h>
#include <SPI.h>
#include <FS.h>
#include <LittleFS.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <HTTPUpdateServer.h>
#include "driver/temp_sensor.h"
//#include "driver/spi_master.h"
//#include "USB.h"
//#include <box2d/box2d.h>

const char *version PROGMEM = "V015"; // 程序版本
uint8_t version_int = 15;

#define AIR_TYPE 0        // 空气传感器类型 0-无 1-SPG41 2-ENS160 3-串口sys02
#define FUEL_GAUGE_TYPE 1 // 电量计类型 0-无 1-MAX17048

WebServer server(80);
HTTPUpdateServer httpUpdater;
File fsUploadFile; // 建立文件对象用于闪存文件上传
static bool fsOK;
String unsupportedFiles;
static const char TEXT_PLAIN[] PROGMEM = "text/plain";
static const char FS_INIT_ERROR[] PROGMEM = "FS INIT ERROR";
static const char FILE_NOT_FOUND[] PROGMEM = "FileNotFound";

const char *wifiRecord PROGMEM = "/system/wifi.txt";           // wifi记录 LittleFS卡用
const char *wifiScanRecord PROGMEM = "/system/wifiScan.txt";   // wifi扫描记录 LittleFS卡用
const char *alarmClockRecord PROGMEM = "/system/ACR.txt";      // 闹钟记录 LittleFS卡用
const char *wanNianLiRecord PROGMEM = "/system/wanNianLi.txt"; // 万年历 LittleFS卡用

const char *currentFsName = "LittleFS";
bool curFS = 0;                // 0-LittleFS 1-SDFS
fs::FS fileSystem2 = LittleFS; // 配网模式-高级文件管理器使用的FS LittleFS或SD
uint16_t overTime;             // 超时时间
uint8_t batTempComp;           // 电池温度补偿时间
int8_t pw_state = 0;           // 启动ap模式状态  0-无 1-WiFi未配置 2-有配置 3-有配置但连接失败 4-连接成功
bool peiwangInitStete = 0;     // 配网初始化 0-未初始化 1-已初始化
bool dmaTransfer = 0;          // DMA传输完成
uint32_t sleepTime = 0;        // 0=永久休眠 单位ms
uint8_t wu_state = 0;          // 唤醒原因
float bat_vcc = 4.2;           // 电压
float bat_soc = 100.0;         // 电量
float cpuTemp = 0.0;           // cpu温度

// 闹钟目标时间 单位秒
//-100000暂停 -100001文件打开失败 -100002时间芯片错误 -100003都为关闭 -100004响铃中 -100005时钟唤醒有闹钟
int32_t AC_timeTarget = -100003;
uint32_t AC_timeCount = 0;       // 闹钟计数器 单位秒
enum
{
  AC_STOP = -100000,      // 暂停
  AC_FILE_FAIL = -100001, // 文件打开失败
  AC_CHIP_FAIL = -100002, // 时间芯片错误
  AC_ALL_OFF = -100003,   // 都为关闭
  AC_RINGING = -100004,   // 响铃中
  AC_WAKE_UP = -100005,   // 唤醒时有闹钟
};
// RTC数据
RTC_DATA_ATTR uint32_t RTC_PW_rsert = 0;      // 重启进入配网 1-需要 0-不需要
RTC_DATA_ATTR uint32_t RTC_disPage_old = 255; // 上次显示的界面
RTC_DATA_ATTR uint32_t RTC_focus_old = 0;     // 上次聚焦的对象id
RTC_DATA_ATTR uint32_t RTC_timedWakeUp = 0;   // 定时唤醒
RTC_DATA_ATTR uint32_t RTC_ac_wp = 0;         // 有闹钟，需要每天0点唤醒检查
RTC_DATA_ATTR uint32_t RTC_clock_count = 0;   // 时钟刷新次数 单位分钟
// 默认分压系数
#define FYXS 0.54649
#define BAT_LOW1 3.3  // 开机低压提示
#define BAT_LOW2 3.35 // 运行中休眠电压

#include "eep_my.h"

// 后台任务状态，按位存储,可以存储16个任务
uint16_t backgroundTask = 0;
enum
{
  BGT_CONFIG_NETWORK = 0, // 配网
  BGT_CLOCK_AUTU_CALI,    // 时钟自动校准
  BGT_ACC_READ,           // 加速度读取
  BGT_CLOCK_READ,         // 时钟读取
  BGT_AIR_READ,           // 空气质量读取
  BGT_BUZZER,             // 蜂鸣器检测
  BGT_LOCATE_INFO_READ,   // 定位信息模块检测
  BGT_AMBIENT_LIGHT,      // 环境光读取
  BGT_CHECK_UPDATE,       // 检查更新
  BGT_MQTT,               // MQTT
  BGT_GET_WanNianLi,      // 获取万年历
};

#define CLOCK_I2C_ADDR 0x32
#define ACC_I2C_ADDR 0x18
#define BATSOC_I2C_ADDR 0x36
#define AMBIENT_LIGHT_I2C_ADDR 0x44
uint8_t ic_state = 0;       //芯片状态
enum
{
  IC_CLOCK = 0,    // 时钟 RX8010
  IC_ACC,          // 加速度计 LIS2DW12
  IC_BATSOC,       // 电量计 MAX17048
  IC_AMBIENT_LIGHT // 环境光 OPT3001
};

// 任务句柄
TaskHandle_t TH_accRead = NULL;
TaskHandle_t TH_clockRead = NULL;
TaskHandle_t TH_backstageManagement = NULL;
TaskHandle_t TH_clockAutoCali = NULL;
TaskHandle_t TH_batRead = NULL;
TaskHandle_t TH_networkConfig = NULL;
TaskHandle_t TH_eepSave = NULL;
TaskHandle_t TH_airRead = NULL;
TaskHandle_t TH_buzzer = NULL;
TaskHandle_t TH_locateInfo = NULL;
TaskHandle_t TH_ambientLigh = NULL;
TaskHandle_t HT_midi; // midi播放
TaskHandle_t TH_checkUpdate = NULL;
TaskHandle_t TH_mqtt = NULL;
TaskHandle_t TH_getWanNianLi = NULL;

// 定义互斥量的句柄
SemaphoreHandle_t i2c_mutex = NULL;
SemaphoreHandle_t lvgl_mutex = NULL;

bool lv_multiTask = 0;
//这设置了Arduino堆栈大小-注释此行使用默认的8K堆栈大小
SET_LOOP_TASK_STACK_SIZE(16 * 1024);

//****** STA设置
//char sta_ssid[32] = {0};
//char sta_password[64] = {0};
IPAddress dns1(114, 114, 114, 114);
IPAddress dns2(114, 114, 115, 115);
//****** AP设置
const char *ap_ssid PROGMEM = "Pendant";
const char *ap_password PROGMEM = "12345678"; // 无密码则为开放式网络 9个3
IPAddress local_IP(192, 168, 3, 3);
IPAddress gateway(192, 168, 3, 3);
IPAddress subnet(255, 255, 255, 0);

//****** 屏幕驱动
//esp32c3开发板
/*#define SPI_SCLK 2
#define SPI_MISO -1
#define SPI_MOSI 6
#define SPI_CS 10*/
//esp32c3自己画板
#define SPI_SCLK 8
#define SPI_MISO -1
#define SPI_MOSI 10
#define SPI_CS 7
#define EXTCOMIN_PIN 20    // LCD 的公共电极（COM）极性的反转
#define EXTCOMIN_CHANNEL 0 // LCD 的公共电极（COM）极性的反转
// #define PIN_SCS 7  // SPI芯片选择信号引脚
// #define PIN_DISP 6 // 显示器ON/OFF开关信号引脚
// I2C
#define USER_SCL 4
#define USER_SDA 5
// 按键
#define KEY_ADC_PIN 2
// 电池ADC
#if FUEL_GAUGE_TYPE == 0
#define BAT_PIN 0
#endif
// 读取加速度计中断的引脚
#define ACCINT_PIN 1
// 空气质量传感器电源控制
#define AIR_POWER_PIN 21
// 蜂鸣器
#define BUZZER_PIN 3
#define BUZZER_CHANNEL 1

// 前置光LED
#define LED_CHANNEL 2 // 通道
#if FUEL_GAUGE_TYPE == 0
  #define LED_PIN -1 // 引脚
#else   
  #define LED_PIN 0 // 引脚
#endif

//串口
#define UART1_RX 19
#define UART1_TX 18

 // 排查系统卷信息
#define NOSVI(i) i[0] != 'S' && i[7] != 'V' && i[14] != 'I'

#include <JDI_MIP_Display.h>
JDI_MIP_Display jdi_display;
#include <lvgl.h>
#if LV_USE_TFT_ESPI
#include <TFT_eSPI.h>
#endif

/*设置为您的屏幕分辨率*/
#define TFT_HOR_RES 72  // 水平
#define TFT_VER_RES 144 // 垂直

//*** DMA发送缓冲区
// 1个字节存储两个像素的颜色所以只需要屏幕的一半
// 头指令2个+2 ，末尾结束指令2个+2
// 因为DMA有BUG，需要发送多4个字节才能正常
// 行命令2字节 + 一行36字节像素 * 144/4行 + 结束命令2字节 + DMA结束命令4字节
#define DMA_BUF_NUM (2 + 36) * (TFT_VER_RES / 4) + 2 + 4
uint8_t DMA_BUF[DMA_BUF_NUM];

/*LVGL绘制到这个缓冲区，1/10的屏幕大小通常工作得很好。大小以字节为单位*/
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 8 * (LV_COLOR_DEPTH / 8))
uint16_t draw_buf[DRAW_BUF_SIZE]; // LVGL刷新缓存

lv_display_t *disp;
lv_indev_t *indev;

#if LV_USE_LOG != 0
void my_print(lv_log_level_t level, const char *buf)
{
  LV_UNUSED(level);
  Serial.println(buf);
  Serial.flush();
}
#endif

#include "functionAll.h"
#include "my_lvgl_parameter.h"
#include "my_max17048.h"
#include "CallHttps.h"
#include "batAndTempRead.h"
#include "imageProcessing.h"
#include "my_clock.h"
#include "my_acc.h"
#include "STA_AT_OTA.h"
#include "my_sgp41.h"
#include "midiToBuzzer.h"
#include "buzzer.h"
#include "key.h"
#include "other.h"
#include "my_navigationSystem.h"
#include "my_airQuality.h"
#include "my_mqtt.h"
#include "my_LVGLDemo.h"
#include "PowerManagement.h"
#include "WEBServer1.h"
#include "networkConfig.h"
#include "alarmClock.h"
#include "my_box2d.h"
#include "my_ambientLight.h"
#include "checkUpdate.h"
#include "getWanNianLi.h"
//#include "my_audio.h"

// LVGL渲染函数，使用pushPixelsDMA绘制，速度快，暂未实现旋转
void my_disp_flush_RGB565(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{  
  //if(area->y2 < 0) return;
  //if(area->y1 > TFT_VER_RES - 1) return;

  /*Serial.print("area->x1:");Serial.println(area->x1);
  Serial.print("area->x2:");Serial.println(area->x2);
  Serial.print("area->y1:");Serial.println(area->y1);
  Serial.print("area->y2:");Serial.println(area->y2);
  Serial.println();*/
  //delay(1000);

  //*** 当前颜色
  uint16_t color_cur;          // 当前像素的颜色
  uint8_t r_cur, g_cur, b_cur; // 旧的颜色 量化的颜色
  int8_t r_err, g_err, b_err;  // 颜色误差
  //*** 像素抖动参数
  uint32_t pixel_offset_d;
  uint8_t *pixel_d;
  uint16_t color_d;
  uint8_t r_d;
  uint8_t g_d;
  uint8_t b_d;
  uint16_t bufPos = 1; // DMA缓冲区的位置

  int16_t lineNum = area->y2 - area->y1;

  if (lineNum < 0) return;
  
  lineNum += 1;
  //行命令2字节 + 一行36字节像素 * 行数 + 结束命令2字节 + DMA结束命令4字节
  int16_t DMA_buf_bum = (2 + 36) * lineNum + 2 ; // 发送的数量

  for (lv_coord_t y = area->y1; y <= area->y2; y++) // area->y1 area->y2 12 60
  {
    
    DMA_BUF[bufPos] = y + 1;// 发送要刷新哪一行
    for (lv_coord_t x = area->x1; x <= area->x2; x++) //area->x1 area->x2
    {
      uint8_t jdi_color = 0;
      // 获取当前地址的颜色，从rgb565拆成rgb分量
      color_cur = color_p[1] << 8 | color_p[0];
      r_cur = (color_cur >> 11) & 0x1F;
      g_cur = (color_cur >> 5) & 0x3F;
      b_cur = color_cur & 0x1F;
      if (!eep_doudong) // 抖动关闭
      {
        //量化颜色，转成2位
        if(r_cur > 15) jdi_color = jdi_color | B1000;  // 31
        if(g_cur > 31) jdi_color = jdi_color | B0100;  // 63
        if(b_cur > 15) jdi_color = jdi_color | B0010;  // 31
      }
      else 
      {
        // 量化颜色 将16位颜色转换为8位
        if (r_cur > 31 / 2) {r_err = r_cur - 31; r_cur = 31;}
        else                {r_err = r_cur - 0;  r_cur = 0;}
        if (g_cur > 63 / 2) {g_err = g_cur - 63; g_cur = 63;}
        else                {g_err = g_cur - 0;  g_cur = 0;}
        if (b_cur > 31 / 2) {b_err = b_cur - 31; b_cur = 31;}
        else                {b_err = b_cur - 0;  b_cur = 0;}
        //修改当前的颜色
        modify_pixel_color(color_p, 0, create_rgb565(r_cur, g_cur, b_cur));
        // 进行误差扩散
        if (x < area->x2)
        {
          //pixel_offset_d = getPixelIdx(1, 0);
          pixel_offset_d = 2;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 7) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 7) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 7) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        if (x > 0 && y < area->y2)
        {
          /*Serial.print("x:");Serial.println(x);
          Serial.print("y:");Serial.println(y);
          Serial.print("area->y1:");Serial.println(area->y1);
          Serial.print("area->y2:");Serial.println(area->y2);
          Serial.println();*/
          //pixel_offset_d = getPixelIdx(-1, 1);
          pixel_offset_d = 142;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 5) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 5) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 5) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        if (y < area->y2)
        {
          //pixel_offset_d = getPixelIdx(0, 1);
          pixel_offset_d = 144;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 3) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 3) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 3) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        if (x < area->x2 && y < area->y2)
        {
          //pixel_offset_d = getPixelIdx(1, 1);
          pixel_offset_d = 146;
          pixel_d = color_p + pixel_offset_d;
          color_d = pixel_d[1] << 8 | pixel_d[0];
          r_d = (color_d >> 11) & 0x1F;
          g_d = (color_d >> 5) & 0x3F;
          b_d = color_d & 0x1F;
          r_d = colorThresholdLimit(r_d, (r_err * 1) / 16, 31);
          g_d = colorThresholdLimit(g_d, (g_err * 1) / 16, 63);
          b_d = colorThresholdLimit(b_d, (b_err * 1) / 16, 31);
          color_d = create_rgb565(r_d, g_d, b_d);
          modify_pixel_color(color_p, pixel_offset_d, color_d);
        }
        //再次量化颜色，转成2位
        if(r_cur == 31) bitWrite(jdi_color, 3, 1);
        if(g_cur == 63) bitWrite(jdi_color, 2, 1);
        if(b_cur == 31) bitWrite(jdi_color, 1, 1);
      }
      //****** 一个字节存储两个像素的颜色
      int pixelIdx1 = (x >> 1); // 除以2
      if (!(x & 1)) // 偶数            
      {
        DMA_BUF[pixelIdx1 + bufPos + 1] &= 0x0F;
        DMA_BUF[pixelIdx1 + bufPos + 1] |= (jdi_color & 0x0F) << 4;
      }
      else // 奇数
      {
        DMA_BUF[pixelIdx1 + bufPos + 1] &= 0xF0;
        DMA_BUF[pixelIdx1 + bufPos + 1] |= jdi_color & 0x0F;
      }
      color_p += 2; // 16位颜色占用两个字节，移动到下一个地址
    }
    
    bufPos += (72 / 2) + 1; //下一行
    //第2行 38
    //DMA_BUF[bufPos] = 0; // 行命令前面的空数据
    bufPos++;
  }

  //while (dmaTransfer == 0) vTaskDelay(1);
  //dmaTransfer = 0;

  jdi_display.pushPixelsDMA(DMA_BUF, DMA_buf_bum);
  lv_display_flush_ready(disp);
}

void my_disp_flush_RGB332(lv_display_t *disp, const lv_area_t *area, uint8_t *color_p)
{
  if(area->y2 < 0) return;
  if(area->y1 > TFT_VER_RES - 1) return;
  /*Serial.print("area->x1:");Serial.println(area->x1);
  Serial.print("area->x2:");Serial.println(area->x2);
  Serial.print("area->y1:");Serial.println(area->y1);
  Serial.print("area->y2:");Serial.println(area->y2);*/
  //*** 当前颜色
  uint16_t color_cur;          // 当前像素的颜色
  uint8_t r_cur, g_cur, b_cur; // 旧的颜色 量化的颜色
  int8_t r_err, g_err, b_err;  // 颜色误差
  //*** 像素抖动参数
  uint16_t pixel_offset_d;
  uint8_t *pixel_d;
  uint8_t r_d;
  uint8_t g_d;
  uint8_t b_d;

  memset(&DMA_BUF, 0, sizeof(DMA_BUF));

  DMA_BUF[0] = CMD_UPDATE; // 发送要刷新模式 4位模式
  for (lv_coord_t y = area->y1; y <= area->y2; y++)
  {
    DMA_BUF[1] = y + 1; // 发送要刷新哪一行
    Serial.print("y:");Serial.println(y);
    for (lv_coord_t x = area->x1; x <= area->x2; x++)
    {
      //uint16_t pos = y * TFT_HOR_RES + x;
      //Serial.print(color_p[0], HEX);Serial.print(" ");
      uint8_t jdi_color = 0;
      r_cur = (color_p[0] >> 5) & 0x07;
      g_cur = (color_p[0] >> 2) & 0x07;
      b_cur = color_p[0] & 0x03;
      if(eep_doudong)
      {
        // 颜色阈值处理，只有高低
        if (r_cur > 7 / 2) {r_err = r_cur - 7; r_cur = 7;}
        else               {r_err = r_cur - 0; r_cur = 0;}
        if (g_cur > 7 / 2) {g_err = g_cur - 7; g_cur = 7;}
        else               {g_err = g_cur - 0; g_cur = 0;}
        if (b_cur > 3 / 2) {b_err = b_cur - 3; b_cur = 3;}
        else               {b_err = b_cur - 0; b_cur = 0;}
        //修改当前的颜色
        color_p[0] = create_rgb332(r_cur, g_cur, b_cur);
        // 进行误差扩散
        if (x < area->x2)
        {
          pixel_offset_d = 1;
          pixel_d = color_p + pixel_offset_d;// 下一个地址
          r_d = (pixel_d[0] >> 5) & 0x07;
          g_d = (pixel_d[0] >> 2) & 0x07;
          b_d = pixel_d[0] & 0x03;
          r_d = colorThresholdLimit(r_d, (r_err * 7) / 16, 7);
          g_d = colorThresholdLimit(g_d, (g_err * 7) / 16, 7);
          b_d = colorThresholdLimit(b_d, (b_err * 7) / 16, 3);
          pixel_d[0] = create_rgb332(r_d, g_d, b_d);
        }
        if (x > 0 && y < area->y2)
        {
          pixel_offset_d = 71;
          pixel_d = color_p + pixel_offset_d;// 下一个地址
          r_d = (pixel_d[0] >> 5) & 0x07;
          g_d = (pixel_d[0] >> 2) & 0x07;
          b_d = pixel_d[0] & 0x03;
          r_d = colorThresholdLimit(r_d, (r_err * 5) / 16, 7);
          g_d = colorThresholdLimit(g_d, (g_err * 5) / 16, 7);
          b_d = colorThresholdLimit(b_d, (b_err * 5) / 16, 3);
          pixel_d[0] = create_rgb332(r_d, g_d, b_d);
        }
        if (y < area->y2)
        {
          pixel_offset_d = 72;
          pixel_d = color_p + pixel_offset_d;// 下一个地址
          r_d = (pixel_d[0] >> 5) & 0x07;
          g_d = (pixel_d[0] >> 2) & 0x07;
          b_d = pixel_d[0] & 0x03;
          r_d = colorThresholdLimit(r_d, (r_err * 3) / 16, 7);
          g_d = colorThresholdLimit(g_d, (g_err * 3) / 16, 7);
          b_d = colorThresholdLimit(b_d, (b_err * 3) / 16, 3);
          pixel_d[0] = create_rgb332(r_d, g_d, b_d);
        }
        if (x > 0 && y < area->y2)
        {
          pixel_offset_d = 73;
          pixel_d = color_p + pixel_offset_d;// 下一个地址
          r_d = (pixel_d[0] >> 5) & 0x07;
          g_d = (pixel_d[0] >> 2) & 0x07;
          b_d = pixel_d[0] & 0x03;
          r_d = colorThresholdLimit(r_d, (r_err * 1) / 16, 7);
          g_d = colorThresholdLimit(g_d, (g_err * 1) / 16, 7);
          b_d = colorThresholdLimit(b_d, (b_err * 1) / 16, 3);
          pixel_d[0] = create_rgb332(r_d, g_d, b_d);
        }
        //量化颜色，转成2位
        if(r_cur == 7) bitWrite(jdi_color, 3, 1);
        if(g_cur == 7) bitWrite(jdi_color, 2, 1);
        if(b_cur == 3) bitWrite(jdi_color, 1, 1);
      }
      else 
      {
        //量化颜色，转成2位
        if(r_cur > 7 / 2) bitWrite(jdi_color, 3, 1);
        if(g_cur > 7 / 2) bitWrite(jdi_color, 2, 1);
        if(b_cur > 3 / 2) bitWrite(jdi_color, 1, 1);
      }

      //****** 一个字节存储两个像素的颜色
      uint8_t pixelIdx1 = x >> 1; 
      if (!(x & 1)) //偶数
      {
        DMA_BUF[pixelIdx1 + 2] &= 0x0F;
        DMA_BUF[pixelIdx1 + 2] |= (jdi_color & 0x0F) << 4;
      }
      else  //奇数
      {
        DMA_BUF[pixelIdx1 + 2] &= 0xF0;
        DMA_BUF[pixelIdx1 + 2] |= jdi_color & 0x0F;
      }
      color_p++;
      Serial.print(color_p[0], HEX);Serial.print(" ");
    }
    Serial.println();Serial.println();
    //推送一行
    jdi_display.pushPixelsDMA(DMA_BUF, DMA_BUF_NUM);
  }
  Serial.println();
  delay(1000);
  lv_disp_flush_ready(disp);
}

// 读取按键
void my_keypad_read(lv_indev_t *indev, lv_indev_data_t *data)
{
  static uint32_t last_key = 0;
  int8_t act_key = getKey(); // 获取哪个按键被按下
  if (act_key != 0)
  {
    data->state = LV_INDEV_STATE_PRESSED; // 输入驱动状态已按下
  
    if      (act_key == 1) act_key = LV_KEY_ENTER;  // 按下
    else if (act_key == 2 && (page.keyMode == KEY_MODE_PN || mbox.keyMode == KEY_MODE_PN))
      act_key = LV_KEY_PREV; // 上一个焦点
    else if (act_key == 3 && (page.keyMode == KEY_MODE_PN || mbox.keyMode == KEY_MODE_PN))
      act_key = LV_KEY_NEXT; // 下一个焦点
    else if (act_key == 2 && page.keyMode == KEY_MODE_RL)
      act_key = LV_KEY_LEFT; // 左
    else if (act_key == 3 && page.keyMode == KEY_MODE_RL)
      act_key = LV_KEY_RIGHT; // 右

    last_key = act_key; //  更新最后一个键
  }
  else
  {
    //last_key = 0; // 更新最后一个键
    data->state = LV_INDEV_STATE_RELEASED; // 输入驱动状态已释放
  }
  data->key = last_key;
  key_code = last_key;
}
//i2c初始化
void i2c_begin()
{
  Wire.begin(USER_SDA, USER_SCL, 400000);
}

void setup()
{
  //Serial.begin(115200);
  //delay(1000);
  bool printState = 1; // 是否需要串口打印
  wu_state = print_wakeup_reason(); //获取唤醒原因
  // 通过GPIO唤醒，取消定时唤醒标志
  if (wu_state == ESP_SLEEP_WAKEUP_GPIO) 
  {
    printState = 0;
    RTC_timedWakeUp = 0;
  }
  // 崩溃唤醒 或 手动重启 或 内存溢出 或 
  else if (wu_state == ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG || wu_state == 0)
  {
    RTC_timedWakeUp = 0;
    delay(500);
  }

  if (printState) Serial.begin(115200);

  //i2c_mutex = xSemaphoreCreateMutex();
  lvgl_mutex = xSemaphoreCreateMutex();

  gpio_hold(0);
  eeprom_init();
  i2c_begin();

  // 文件系统初始化
  fsOK = LittleFS.begin(1, "/LFS");
  if (!fsOK)
  {
    String str = F("LittleFS 启动失败");
    Serial.println(str);
  }

  // 电池电压和cpu温度读取
  cupTempInit(); // 初始化cpu温度配置
  temp_sensor_read_celsius(&cpuTemp);
#if FUEL_GAUGE_TYPE == 0
  pinMode(BAT_PIN, INPUT);
#else
  max17048_init();
#endif
  bat_vcc = getBatVolNew(); // 初始化bat_vcc
  get_bat_vcc_rtos_init();  // 定时读取电量&温度

  //File file = LittleFS.open("/MISans_1.bin");
  //Serial.print("/MISans_1.bin:");Serial.println(file);

  jdi_init();  // 屏幕硬件初始化
  lvgl_init(); // 屏幕软件初始化

  backstageManagement_rtos_init(); // 启动任务管理器

  pageStartupEnters(); // 开机时进入哪个界面

#if AIR_TYPE == 1
  // 空气传感器电源关闭
  pinMode(AIR_POWER_PIN, OUTPUT);
  digitalWrite(AIR_POWER_PIN, 0);
#endif

  // 文件管理器初始化
  memset(fm.pageRecord, 1, sizeof(fm.pageRecord));

  // 是否打开蜂鸣器
  if (eep_buzzerEn)
    bitWrite(backgroundTask, BGT_BUZZER, 1);
  else
    bitWrite(backgroundTask, BGT_BUZZER, 0);

  // LED初始化
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 0);
  ledcSetup(LED_CHANNEL, eep_ledFre, 10); // 通道，频率，分辨率
  ledcAttachPin(LED_PIN, LED_CHANNEL);    // 映射引脚，通道
  if (eep_ledEn) ledcWrite(LED_CHANNEL, map(eep_ledPwm,0,255,0,1023));
  else           ledcWrite(LED_CHANNEL, 0);


  //String strIn = "祭祀 祈福 求嗣 沐浴 问名 交易 纳财 入殓 教牛马 移柩 安葬 修坟 立碑 谢土 造畜稠\n入宅 置产 嫁娶 动土 栽种 开市 开光 动土 破土 ";
  //analysisYiJi(strIn);

  //Serial.end();

  //i2s_music_rtos_init();

  // 加速计模式
  //acc.state = acc_continRefresh();
  //acc.state = acc_wakeUp();
  //acc.state = acc_6d();

  //ENS160.setPWRMode(ENS160_SLEEP_MODE);
  //read_ens160_rtos_init();
}

uint32_t time1 = 0;
bool io1_state = 0;
int lastOrientation = 0; // 没有事件发生

// DMA传输完成的中断
void loop()
{
  xSemaphoreTake(lvgl_mutex,portMAX_DELAY);
  lv_task_handler();        // 让 GUI 去做它该做的事
  dormantTimeoutDecision(); // 休眠超时决策低电量检测
  my_msgbox_loop();         // 弹窗检测
  xSemaphoreGive(lvgl_mutex);
  vTaskDelay(1);

  /*if (millis() - time1 > 1000)
  {
    time1 = millis();
    sgp41_readIndex();
  }*/

  // 检测到唤醒事件
 /* if (acce.actDetected())
  {
    Serial.print("ACCINT_PIN_STATE_0:");Serial.println(digitalRead(ACCINT_PIN));
    Serial.print("唤醒事件发生在");
    // 唤醒运动方向检测
    DFRobot_LIS2DW12::eWakeUpDir_t dir = acce.getWakeUpDir();
    if (dir == DFRobot_LIS2DW12::eDirX)
    {
      Serial.println("x方向");
    }
    if (dir == DFRobot_LIS2DW12::eDirY)
    {
      Serial.println("y方向");
    }
    if (dir == DFRobot_LIS2DW12::eDirZ)
    {
      Serial.println("z方向");
    }
    delay(100);
  }*/

  // 检查在六个方向检测到的变化
  /*if (acce.oriChangeDetected())
  {
    DFRobot_LIS2DW12::eOrient_t orientation = acce.getOrientation();
    if (lastOrientation != orientation)
    {
      Serial.print("ACCINT_PIN_STATE:");
      Serial.println(digitalRead(ACCINT_PIN));
      if (orientation == DFRobot_LIS2DW12::eXDown)
        Serial.println("X现在下降了");
      else if (orientation == DFRobot_LIS2DW12::eXUp)
        Serial.println("X现在上升了");
      if (orientation == DFRobot_LIS2DW12::eYDown)
        Serial.println("Y现在下降了");
      else if (orientation == DFRobot_LIS2DW12::eYUp)
        Serial.println("Y现在上升了");
      if (orientation == DFRobot_LIS2DW12::eZDown)
        Serial.println("Z现在下降了");
      else if (orientation == DFRobot_LIS2DW12::eZUp)
        Serial.println("Z现在上升了");
      lastOrientation = orientation;
    }
  }*/

  //if (millis() - time1 > 1000)
  //{
    //time1 = millis();
    //Serial.print("ACCINT_PIN_STATE:");
    //Serial.println(digitalRead(ACCINT_PIN));
    //UBaseType_t stackRemaining;
    //stackRemaining = uxTaskGetStackHighWaterMark(NULL);
    //Serial.printf("Arduino堆栈设置为%d字节", getArduinoLoopTaskStackSize());Serial.println();
    //Serial.print("loop内存最小值:"); Serial.println(stackRemaining);
    /*Serial.print("自由内存:"); Serial.println(xPortGetFreeHeapSize());
    Serial.print("自由内存最小值:"); Serial.println(xPortGetMinimumEverFreeHeapSize());
    //Serial.println();
 
    UBaseType_t stackRemaining;
    stackRemaining = uxTaskGetStackHighWaterMark(TH_batRead);
    Serial.print("TH_batRead内存最小值:"); Serial.println(stackRemaining);
    Serial.println();*/
  //}

}

// DMA传输完成的中断
void IRAM_ATTR myDMACallback()
{
  dmaTransfer = 1;
  //lv_display_flush_ready(disp);
}

// 屏幕硬件初始化
void jdi_init()
{
  // SPI.setFrequency(8000000);
  // SPI.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SPI_CS); // sck,miso,mosi,cs
  jdi_display.begin(SPI_SCLK, SPI_MISO, SPI_MOSI, SPI_CS, 8000000, 1, 0); // max12.36Mhz

  // 注册DMA完成回调函数
  //jdi_display.registerDMACallback(myDMACallback);
  // jdi_display.begin();

  //jdi_display.displayOn();
  //delay(1);
  // 定期反转LCD COM信号
  
  jdi_display.displayOn();
  //delay(1);
  //jdi_display.clearScreen();
  //delay(1);
  pinMode(EXTCOMIN_PIN, OUTPUT);
  float vcc = getBatVolNew();
  
  ledcSetup(EXTCOMIN_CHANNEL, LCD_COM_FRE, 10); // 通道，频率，分辨率
  ledcAttachPin(EXTCOMIN_PIN, EXTCOMIN_CHANNEL); // 映射引脚，通道
  ledcWrite(EXTCOMIN_CHANNEL, LCD_COM_TIME);     // 占空比 0-1023

  jdi_display.noUpdate();  // 停止更新
  //delay(1);
  memset(&DMA_BUF, 0, sizeof(DMA_BUF));
  DMA_BUF[0] = CMD_UPDATE; // 发送要刷新模式 4位模式
  
  // if (RTC_timedWakeUp == 1)
  //{
  // jdi_display.noUpdate(); // 停止更新
  // delay(5);
  //}

  // jdi_display.setRotation(3); // 无效
  // jdi_display.frontlightOn(); // 前灯打开 可选，具体取决于显示器型号
}

// lvgl整行刷新回调
void globalCallback(lv_event_t *area)
{
  // 获取发送事件时传递的参数
  lv_area_t *e = (lv_area_t *)lv_event_get_param(area);
  e->x1 = 0;
  e->x2 = TFT_HOR_RES - 1;
}
// lvgl软件初始化
void lvgl_init()
{
  String LVGL_Arduino = "Hello Arduino! ";
  LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
  Serial.println(LVGL_Arduino);
  lv_init();

  /*设置一个时间戳源，以便 LVGL 知道经过了多少时间. */
  lv_tick_set_cb(millis);

  /* 用于调试的寄存器打印功能 */
#if LV_USE_LOG != 0
  lv_log_register_print_cb(my_print);
#endif

  //****** 创建一个显示
  disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
  lv_display_set_flush_cb(disp, my_disp_flush_RGB565);
  lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);
  lv_display_set_antialiasing(disp, false); // 抗锯齿关闭
  // 设置显示器旋转方向，可以是LV_DISP_ROT_NONE, LV_DISP_ROT_90, LV_DISP_ROT_180, LV_DISP_ROT_270
  lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_0);
  
  //lv_display_set_color_format(disp,LV_COLOR_FORMAT_L8);

  //****** 初始化（伪）输入设备驱动程序
  indev = lv_indev_create();                      // 使用当前的屏幕能全局
  lv_indev_set_type(indev, LV_INDEV_TYPE_KEYPAD); // 类型设置为键盘、按键 LV_INDEV_TYPE_ENCODER LV_INDEV_TYPE_KEYPAD
  lv_indev_set_read_cb(indev, my_keypad_read);    // 设置回调函数

  //****** 创建组
  group_my = lv_group_create();          // 创建组
  group_mbox0 = lv_group_create();       // 创建组
  group_mbox1 = lv_group_create();       // 创建组
  //group_mbox2 = lv_group_create();       // 创建组
  lv_indev_set_group(indev, group_my);   // 将组邦定到按键
  //lv_indev_set_group(indev, group_mbox); // 将组邦定到按键
  //lv_indev_set_group(indev, lv_group_get_default()); // 将组邦定到按键
  //lv_group_set_default(group_my);      // 设置为默认组
  //****** 初始化样式
  lv_style_init(&style_shadow);
  lv_style_init(&style_msgbox);
  lv_style_init(&style_squareShape);
  //阴影设为透明宽度0，即为不需要阴影
  lv_style_set_shadow_opa(&style_shadow, 0);   // 设置样式阴影不透明度
  lv_style_set_shadow_width(&style_shadow, 0); // 设置样式阴影宽度
  //基本对象设置为方形
  lv_style_set_pad_all(&style_squareShape, 0);      // 设置边界
  lv_style_set_border_width(&style_squareShape, 0); // 边框宽度
  lv_style_set_radius(&style_squareShape, 0);       // 设置圆角
  //****** 添加显示屏的全局回调,用来强制小部件整行刷新，而不是局部刷新
  lv_display_add_event_cb(disp, globalCallback, LV_EVENT_INVALIDATE_AREA, NULL);

  //Serial.println("Setup done");
}

//后台任务管理器
void backstageManagement_rtos_init() // 创建任务管理器
{
  xTaskCreatePinnedToCore(
      backstageManagement_rtos, /* 任务指针，创建任务用的那个函数名 */
      "backstageManagement",    /* 任务名称 */
      2 * 1024,                 /* 任务栈大小，根据需要自行设置*/
      NULL,                     /* 可选参数，一般不填*/
      10,                       /* 优先级 */
      &TH_backstageManagement,  /* 任务句柄，用于后续挂起或恢复运行*/
      0                         /* 核ID */
  );
}
void backstageManagement_rtos(void *param)
{
  for (;;)
  {
    vTaskDelay(5);
    backstageManagement();
  }
}
void backstageManagement()
{
  //buzzerMonitor(); // 闹钟监测

  if (backgroundTask == 0) return;

  //****** 配网任务 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_CONFIG_NETWORK)) 
  {
    if (TH_networkConfig == NULL)
    {
      networkConfig_rtos_init();
      Serial.println("创建TH_networkConfig");
    }
  }

  //****** 加速度读取任务管理 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_ACC_READ))
  {
    if (TH_accRead == NULL)
    {
      accRead_rtos_init();
      Serial.println("创建TH_accRead");
    }
  }

  //****** 时钟读取任务管理 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_CLOCK_READ)) 
  {
    if (TH_clockRead == NULL)
    {
      clockRead_rtos_init();
      Serial.println("创建TH_clockRead");
    }
  }

  //****** 时钟联网校准任务 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_CLOCK_AUTU_CALI)) 
  {
    if (TH_clockAutoCali == NULL)
    {
      clockAutoCali_rtos_init();
      Serial.println("创建TH_clockAutoCali");
    }
  }

  //****** 空气质量读取任务 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_AIR_READ)) 
  {
    if (TH_airRead == NULL)
    {
      //airRead_rtos_init();
      read_airQuality_rtos_init();
      Serial.println("创建TH_airRead");
    }
  }

    //****** 蜂鸣器 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_BUZZER)) 
  {
    if (TH_buzzer == NULL)
    {
      buzzer_rtos_init();
      Serial.println("创建TH_buzzer");
    }
  }

    //****** 定位信息 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_LOCATE_INFO_READ)) 
  {
    if (TH_locateInfo == NULL)
    {
      locateInfo_rtos_init();
      Serial.println("创建TH_locateInfo");
    }
  }

  //****** 环境光读取 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_AMBIENT_LIGHT))
  {
    if (TH_ambientLigh == NULL)
    {
      ambientLight_rtos_init();
      Serial.println("创建TH_ambientLight");
    }
  }

  //****** 检查更新 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_CHECK_UPDATE))
  {
    if (TH_checkUpdate == NULL)
    {
      checkUpdate_rtos_init();
      Serial.println("创建TH_checkUpdate");
    }
  }

  //****** MQTT 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_MQTT))
  {
    if (TH_mqtt == NULL)
    {
      mqtt_rtos_init();
      Serial.println("创建TH_mqtt");
    }
  }

  //****** 万年历 删除任务在自己里面删除
  if (bitRead(backgroundTask, BGT_GET_WanNianLi))
  {
    if (TH_getWanNianLi == NULL)
    {
      getWanNianLi_rtos_init();
      Serial.println("创建TH_getWanNianLi");
    }
  }
}

/*
  eRunning = 0,     // 任务正在查询自身状态，因此必须正在运行。
  eReady = 1,       // 正在查询的任务处于读取或待处理就绪列表中。
  eBlocked = 2,     // 正在查询的任务处于阻塞状态。
  eSuspended = 3,   // 正在查询的任务处于暂停状态，或处于阻塞状态且超时时间无限。
  eDeleted = 4,     // 正在查询的任务已被删除，但其 TCB 尚未释放。
  eInvalid = 5      // 用作“无效状态”值。
*/