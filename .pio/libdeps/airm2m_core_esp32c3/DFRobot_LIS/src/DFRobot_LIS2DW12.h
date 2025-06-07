/*!
 * @file DFRobot_LIS2DW12.h
 * @brief Define the basic structure of class DFRobot_LIS2DW12
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#ifndef DFROBOT_LIS2DW12_H
#define DFROBOT_LIS2DW12_H
#include "Arduino.h"

#include <Wire.h>
#include <SPI.h>
// #define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...)                 \
  {                              \
    Serial.print("[");           \
    Serial.print(__FUNCTION__);  \
    Serial.print("(): ");        \
    Serial.print(__LINE__);      \
    Serial.print(" ] ");         \
    Serial.println(__VA_ARGS__); \
  }
#else
#define DBG(...)
#endif

#define LIS2DW12_I2C_ADDR (0x19) ///< LIS2DW12 IIC address
#define IIS2DLPC_I2C_ADDR (0x19) ///< IIS2DLPC IIC address

#define ERR_OK 0          ///< ok
#define ERR_DATA_BUS -1   ///< error in data bus
#define ERR_IC_VERSION -2 ///< chip version mismatch

class DFRobot_LIS2DW12
{
public:
#define REG_CARD_ID 0x0F     ///< 芯片id
#define REG_CTRL_REG1 0x20   ///< 控制寄存器1
#define REG_CTRL_REG4 0x23   ///< 控制寄存器2
#define REG_CTRL_REG2 0x21   ///< 控制寄存器3
#define REG_CTRL_REG3 0x22   ///< 控制寄存器4
#define REG_CTRL_REG5 0x24   ///< 控制寄存器5
#define REG_CTRL_REG6 0x25   ///< 控制寄存器6
#define REG_CTRL_REG7 0x3F   ///< 控制寄存器7
#define REG_STATUS_REG 0x27  ///< 状态寄存器
#define REG_OUT_X_L 0x28     ///< X轴加速度寄存器低位
#define REG_OUT_X_H 0x29     ///< X轴加速度寄存器高位
#define REG_OUT_Y_L 0x2A     ///< Y轴加速度寄存器低位
#define REG_OUT_Y_H 0x2B     ///< Y轴加速度寄存器高位
#define REG_OUT_Z_L 0x2C     ///< Z轴加速度寄存器低位
#define REG_OUT_Z_H 0x2D     ///< Z轴加速度寄存器高位
#define REG_WAKE_UP_DUR 0x35 ///< 唤醒和睡眠时长配置寄存器
#define REG_FREE_FALL 0x36   ///< 自由落体事件寄存器
#define REG_STATUS_DUP 0x37  ///< 中断事件状态寄存器
#define REG_WAKE_UP_SRC 0x38 ///< 唤醒源寄存器
#define REG_TAP_SRC 0x39     ///< Tap 源寄存器
#define REG_SIXD_SRC 0x3A    ///< 6D 源寄存器
#define REG_ALL_INT_SRC 0x3B ///< 读取此寄存器，路由到 INT 引脚的所有相关中断功能标志将同时复位

#define REG_TAP_THS_X 0x30   ///< 4D 配置启用和 TAP 阈值配置。
#define REG_TAP_THS_Y 0x31   ///< Y 方向 @ FS = ±2 g 的敲击识别阈值
#define REG_TAP_THS_Z 0x32   ///< Z 方向 @ FS = ±2 g 的敲击识别阈值
#define REG_INT_DUR 0x33     ///< 中断持续时间寄存器
#define REG_WAKE_UP_THS 0x34 ///< 唤醒阈值寄存器
#define SPI_READ_BIT 0X80    ///< 位 0：RW 位。为 0 时，数据 DI(7:0) 写入设备。为 1 时，从设备读取数据 DO(7:0)。*/
public:
  /**
   * @fn ePowerMode_t
   * @brief 功率模式，传感器测量加速度有两种模式
   * @n 1.连续测量。在此模式下，传感器将连续测量并将数据存储在数据寄存器中。
   * @n 2.单次数据转换按需模式。在此模式下，传感器仅在收到外部请求时才会进行测量。
   */
  typedef enum
  {
    eHighPerformance_14bit = 0x04,         /**<高性能模式，14 位分辨率>*/
    eContLowPwr4_14bit = 0x03,             /**<连续测量，低功耗模式 4（14 位分辨率）>*/
    eContLowPwr3_14bit = 0x02,             /**<连续测量，低功耗模式 3（14 位分辨率）>*/
    eContLowPwr2_14bit = 0x01,             /**<连续测量，低功耗模式 2（14 位分辨率）>*/
    eContLowPwr1_12bit = 0x00,             /**<连续测量，低功耗模式 1（12 位分辨率）>*/
    eSingleLowPwr4_14bit = 0x0b,           /**<按需单次数据转换模式，低功耗模式 4（14 位分辨率）>*/
    eSingleLowPwr3_14bit = 0x0a,           /**<按需单数据转换模式，低功耗模式 3（14 位分辨率）>*/
    eSingleLowPwr2_14bit = 0x09,           /**<按需单数据转换模式，低功耗模式 2（14 位分辨率）>*/
    eSingleLowPwr1_12bit = 0x08,           /**<按需单数据转换模式，低功耗模式 1（12 位分辨率）>*/
    eHighPerformanceLowNoise_14bit = 0x14, /**<高性能模式，低噪声启用，14 位分辨率>*/
    eContLowPwrLowNoise4_14bit = 0x13,     /**<连续测量,低功耗模式 4(14 位分辨率,低噪声使能)>*/
    eContLowPwrLowNoise3_14bit = 0x12,     /**<连续测量,低功耗模式 3(14 位分辨率,低噪声使能)>*/
    eContLowPwrLowNoise2_14bit = 0x11,     /**<连续测量,低功耗模式 2(14 位分辨率,低噪声使能)>*/
    eContLowPwrLowNoise1_12bit = 0x10,     /**<连续测量,低功耗模式 1(12 位分辨率,低噪声使能)>*/
    eSingleLowPwrLowNoise4_14bit = 0x1b,   /**<单次数据转换按需模式,低功耗模式4(14 位分辨率),低噪声使能>*/
    eSingleLowPwrLowNoise3_14bit = 0x1a,   /**<按需单次数据转换模式,低功耗模式 3(14 位分辨率),低噪声使能>*/
    eSingleLowPwrLowNoise2_14bit = 0x19,   /**<按需单次数据转换模式,低功耗模式 2(14 位分辨率),低噪声使能>*/
    eSingleLowPwrLowNoise1_12bit = 0x18,   /**<按需单次数据转换模式,低功耗模式 1(12 位分辨率),低噪声使能>*/
  } ePowerMode_t;

  /**
   * @fn eRange_t
   * @brief 传感器范围
   */
  typedef enum
  {
    e2_g = 2,   /**<±2g>*/
    e4_g = 4,   /**<±4g>*/
    e8_g = 8,   /**<±8g>*/
    e16_g = 16, /**<±16g>*/
  } eRange_t;

  /**
   * @fn ePath_t
   * @brief 过滤模式
   */
  typedef enum
  {
    eLPF = 0x00, /**< 选定低通滤波器路径>*/
    eHPF = 0x10, /**< 选定高通滤波器路径>*/
  } ePath_t;

  /**
   * @fn eBWFilter_t
   * @brief 带宽选择
   */
  typedef enum
  {
    eRateDiv_2 = 0,  /**<Rate/2 (最高 Rate = 800 Hz，Rate = 1600 Hz 时为 400 Hz)>*/
    eRateDiv_4 = 1,  /**<Rate/4 (高功率/低功率)>*/
    eRateDiv_10 = 2, /**<Rate/10 (HP/LP)>*/
    eRateDiv_20 = 3, /**<Rate/20 (HP/LP)>*/
  } eBWFilter_t;

  /**
   * @fn  eRate_t
   * @brief 数据收集率
   */
  typedef enum
  {
    eRate_0hz = 0x00,   /**<测量关闭>*/
    eRate_1hz6 = 0x01,  /**<1.6hz，仅在低功耗模式下使用>*/
    eRate_12hz5 = 0x02, /**<12.5hz>*/
    eRate_25hz = 0x03,
    eRate_50hz = 0x04,
    eRate_100hz = 0x05,
    eRate_200hz = 0x06,
    eRate_400hz = 0x07, /**<仅在高性能模式下使用>*/
    eRate_800hz = 0x08, /**<仅在高性能模式下使用>*/
    eRate_1k6hz = 0x09, /**<仅在高性能模式下使用mode>*/
    eSetSwTrig = 0x12,  /**<软件触发单次测量>*/
  } eRate_t;

  /**
   * @fn eActDetect_t
   * @brief 运动检测模式
   */
  typedef enum
  {
    eNoDetection = 0,      /**<无检测>*/
    eDetectAct = 1,        /**<检测到运动，芯片在低功耗模式下自动进入 12.5 Hz 速率>*/
    eDetectStatMotion = 3, /**<检测到运动，芯片检测到低于固定阈值的加速度，但不会改变速率或操作模式>*/
  } eActDetect_t;

  /**
   * @fn eInt1Event_t
   * @brief 中断源1触发事件设置
   */
  typedef enum
  {
    eDoubleTap = 0x08, /**<双击事件>*/
    eFreeFall = 0x10,  /**<自由落体事件>*/
    eWakeUp = 0x20,    /**<唤醒事件>*/
    eSingleTap = 0x40, /**<单击事件>*/
    e6D = 0x80,        /**<改变向上/向下/向左/向右/向前/向后状态的事件>*/
  } eInt1Event_t;

  /**
   * @fn eInt2Event_t
   * @brief 中断源 2 触发事件设置
   */
  typedef enum
  {
    eSleepChange = 0x40, /**<睡眠改变状态进程到 INT2 pad>*/
    eSleepState = 0x80,  /**<启用 INT2 pad 上的 SLEEP_STATE 进程>*/
    eSleepDRDY = 0x01,   /**<数据准备就绪状态已被路由到INT2 pad>*/
    eSleepBOOT = 0x20,   /**<引导状态已路由到INT2 pad>*/
  } eInt2Event_t;

  /**
   * @fn eTapMode_t
   * @brief 点击检测模式
   */
  typedef enum
  {
    eOnlySingle = 0,       /**<仅检测点击事件。>*/
    eBothSingleDouble = 1, /**<同时检测单击和双击事件。>*/
  } eTapMode_t;

  /**
   * @fn e6DTh_t
   * @brief 位置检测角度转换阈值
   */
  typedef enum
  {
    eDegrees80, /**<80 度。>*/
    eDegrees70, /**<70 度。>*/
    eDegrees60, /**<60 度。>*/
    eDegrees50, /**<50 度。>*/
  } e6DTh_t;

  /**
   * @fn  eTap_t
   * @brief tap or double tap
   */
  typedef enum
  {
    eSTap = 0, /**<single tap>*/
    eDTap,     /**<double tap>*/
    eNoTap,
  } eTap_t;

  /**
   * @fn eTapDir_t
   * @brief which direction is tap event detected
   */
  typedef enum
  {
    eDirXUp = 0,   /**<Tap is detected in the positive direction of X>*/
    eDirXDown = 1, /**<Tap is detected in the negative direction of X>*/
    eDirYUp = 2,   /**<Tap is detected in the positive direction of Y>*/
    eDirYDown = 3, /**<Tap is detected in the negative direction of Y>*/
    eDirZUp = 4,   /**<Tap is detected in the positive direction of Z>*/
    eDirZDown = 5, /**<Tap is detected in the negative direction of Z>*/
    eDirNone = 6,
  } eTapDir_t;

  /**
   * @fn eWakeUpDir_t
   * @brief which direction is wake up event detected
   */
  typedef enum
  {
    eDirX = 0,     /**<Chip woken up by motion in X direction>*/
    eDirY = 1,     /**<Chip woken up by motion in Y direction>*/
    eDirZ = 2,     /**<Chip woken up by motion in Z direction>*/
    eDirError = 4, /**<Direction detection error>*/
  } eWakeUpDir_t;

  /**
   * @fn eOrient_t
   * @brief orientation
   */
  typedef enum
  {
    eXDown = 0, /**<X is now down>*/
    eXUp = 1,   /**<X is now up>*/
    eYDown = 2, /**<Y is now down>*/
    eYUp = 3,   /**<Y is now up>*/
    eZDown = 4, /**<Z is now down>*/
    eZUp = 5,   /**<Z is now up>*/
  } eOrient_t;

public:
  DFRobot_LIS2DW12();

  /**
   * @fn begin
   * @brief 初始化函数
   * @return true(Initialization succeed)/fasle(Iniatialization failed)
   */
  bool begin(void);

  /**
   * @fn getID
   * @brief 获取芯片 ID
   * @return 8 bit serial number
   */
  uint8_t getID();

  /**
   * @fn softReset
   * @brief 软件复位，恢复所有寄存器值为默认值
   */
  void softReset();

  /**
   * @fn continRefresh
   * @brief 使能芯片连续采集
   * @param enable true(连续更新)/false(输出寄存器直到 MSB 和 LSB 读取后才更新)
   */
  void continRefresh(bool enable);

  /**
   * @fn setFilterPath
   * @brief 设置滤波处理模式
   * @param path 滤波路径
   * @n eLPF = 0x00,/<选择低通滤波路径>/
   * @n eHPF = 0x10,/<选择高通滤波路径>/
   */
  void setFilterPath(ePath_t path);

  /**
   * @fn setFilterBandwidth
   * @brief 设置数据的带宽
   * @param bw 带宽
   * @n eRateDiv_2 ,/<Rate/2 (最高 Rate = 800 Hz，Rate = 1600 Hz 时为 400 Hz)>/
   * @n eRateDiv_4 ,/<Rate/4 (高功率/低功率)>*
   * @n eRateDiv_10 ,/<Rate/10 (HP/LP)>/
   * @n eRateDiv_20 ,/<Rate/20 (HP/LP)>/
   */
  void setFilterBandwidth(eBWFilter_t bw);

  /**
   * @fn setPowerMode
   * @brief 设置功耗模式，传感器测量加速度有两种模式
   * @n 1.连续测量 在此模式下，传感器将连续测量并将数据存储在数据寄存器中
   * @n 2.单次数据转换按需模式 在此模式下，除非收到外部请求，否则传感器将进行测量
   * @param mode 可供选择的功耗模式
   * @n eHighPerformance_14bit /<高性能模式，14 位分辨率>/
   * @n eContLowPwr4_14bit /<连续测量，低功耗模式 4（14 位分辨率）>/
   * @n eContLowPwr3_14bit /<连续测量，低功耗模式 3（14 位分辨率）>/
   * @n eContLowPwr2_14bit /<连续测量，低功耗模式 2（14 位分辨率）/
   * @n eContLowPwr1_12bit /<连续测量,低功耗模式 1(12 位分辨率)>/
   * @n eSingleLowPwr4_14bit /<按需单次数据转换模式,低功耗模式 4(14 位分辨率)>/
   * @n eSingleLowPwr3_14bit /<按需单次数据转换模式,低功耗模式 3(14 位分辨率)>/
   * @n eSingleLowPwr2_14bit /<按需单次数据转换模式,低功耗模式 2(14 位分辨率)>/
   * @n eSingleLowPwr1_12bit /<按需单次数据转换模式,低功耗模式 1(12 位分辨率)>/
   * @n eHighPerformanceLowNoise_14bit /<高性能模式,低噪声启用，14 位分辨率>/
   * @n eContLowPwrLowNoise4_14bit /<连续测量，低功耗模式 4（14 位分辨率，启用低噪声）>/
   * @n eContLowPwrLowNoise3_14bit /<连续测量，低功耗模式 3（14 位分辨率，启用低噪声）>/
   * @n eContLowPwrLowNoise2_14bit /<连续测量，低功耗模式 2（14 位分辨率，启用低噪声）>/
   * @n eContLowPwrLowNoise1_12bit /<连续测量，低功耗模式 1（12 位分辨率，启用低噪声）>/
   * @n eSingleLowPwrLowNoise4_14bit /<按需单次数据转换模式，低功耗模式 4（14 位分辨率），低噪声使能>/
   * @n eSingleLowPwrLowNoise3_14bit /<按需单次数据转换模式，低功耗模式 3（14 位分辨率），低噪声使能>/
   * @n eSingleLowPwrLowNoise2_14bit /<按需单次数据转换模式，低功耗模式 2（14 位分辨率），低噪声使能>/
   * @n eSingleLowPwrLowNoise1_12bit /<按需单次数据转换模式，低功耗模式 1（12 位分辨率），低噪声使能>/
   */
  void setPowerMode(ePowerMode_t mode);

  /**
   * @fn setDataRate
   * @brief 芯片数据采集速率设置
   * @param rate 加速度计频率，0-1600hz选择
   * @n eRate_0hz /<测量关闭>/
   * @n eRate_1hz6 /<1.6hz，仅在低功耗模式下使用>/
   * @n eRate_12hz5 /<12.5hz>/
   * @n eRate_25hz
   * @n eRate_50hz
   * @n eRate_100hz
   * @n eRate_200hz
   * @n eRate_400hz /<仅在高性能模式下使用>/
   * @n eRate_800hz /<仅在高性能模式下使用>/
   * @n eRate_1k6hz /<仅在高性能模式下使用>/
   * @n eSetSwTrig /<软件触发单次测量>/
   */
  void setDataRate(eRate_t rate);

  /**
   * @fn setFreeFallDur
   * @brief 设置自由落体时间，或者自由落体采样次数，只有采样次数足够时，才会发生自由落体事件
   * @param dur 自由落体采样次数，范围：0~31
   * @n time = dur * (1/rate)(unit:s)
   * @n |                           An example of a linear relationship between an argument and time                             |
   * @n |------------------------------------------------------------------------------------------------------------------------|
   * @n |                |                     |                          |                          |                           |
   * @n |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   * @n |------------------------------------------------------------------------------------------------------------------------|
   * @n |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   * @n |------------------------------------------------------------------------------------------------------------------------|
   */
  void setFreeFallDur(uint8_t dur);

  /**
   *@fn setInt1Event
   *@brief 选择在中断1引脚上生成的中断事件
   *@param 事件中断事件
   *@n eDoubleTap=0x08，/<双击事件>/
   *@n eFreeFall=0x10，/<自由落体事件>/
   *@n eWakeUp=0x20，/<唤醒事件>/
   *@n eSingleTap=0x40，/<单次点击事件>/
   *@n e6D=0x80，/<改变面朝上/面朝下/面朝左/面朝右/面朝前/面朝后状态的事件>/
   */
  void setInt1Event(eInt1Event_t event);

  /**
   * @fn setInt2Event
   * @fn setInt2Event
   * @brief 选择中断 2 引脚上生成的中断事件
   * @param event 中断事件
   * @n eSleepChange = 0x40,/<睡眠改变状态进程到 INT2 引脚>/
   * @n eSleepState = 0x80,/<启用 INT2 引脚上 SLEEP_STATE 的进程>/
   */
  void setInt2Event(eInt2Event_t event);

  /**
   * @fn setWakeUpDur
   * @brief 设置唤醒时长，当在setActMode()函数中使用eDetectAct检测模式时，芯片被唤醒后会等待一段时间以正常速率采集
   * @n 个数据。然后芯片会继续休眠，以12.5hz的频率采集数据。
   * @param dur duration，范围：0~3
   * @n time = dur * (1/rate)(unit:s)
   * @n  |                        An example of a linear relationship between an argument and time                                |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |                |                     |                          |                          |                           |
   * @n  |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   */
  void setWakeUpDur(uint8_t dur);

  /**
   * @fn setWakeUpThreshold
   * @brief 设置唤醒阈值，当某个方向的加速度大于此值时，会触发唤醒事件
   * @param th 阈值，单位：mg，该值在测量范围内
   */
  void setWakeUpThreshold(float th);

  /**
  * @fn setActMode
  * @brief 设置运动检测的模式，第一种模式不会检测模块是否运动；
           第二种模式设置后会以较低的频率测量数据以节省功耗，
           检测到运动后恢复正常；第三种只能检测模块是否处于休眠状态。
   * @param mode 运动检测模式
   * @n          eNoDetection /<未检测>/
   * @n          eDetectAct /<检测运动，芯片自动进入12.5Hz低功耗模式>/
   * @n          eDetectStatMotion /<检测运动，芯片检测到低于固定阈值的加速度，但不会改变速率或操作模式>/
   */
  void setActMode(eActDetect_t mode);

  /**
   * @fn setRange
   * @brief 设置范围
   * @param range Measurement range
   * @n           e2_g     = 2, /<±2g>/
   * @n           e4_g     = 4, /<±4g>/
   * @n           e8_g     = 8, /<±8g>/
   * @n           e16_g    = 16, /< ±16g>/
   */
  void setRange(eRange_t range);

  /**
   * @fn enableTapDetectionOnZ
   * @brief 启用检测 Z 方向的点击事件
   * @param enable ture(Enable tap detection)\false(Disable tap detection)
   */
  void enableTapDetectionOnZ(bool enable);

  /**
   * @fn enableTapDetectionOnY
   * @brief 启用检测 Y 方向的点击事件
   * @param enable ture(Enable tap detection)\false(Disable tap detection)
   */
  void enableTapDetectionOnY(bool enable);

  /**
   * @fn enableTapDetectionOnX
   * @brief 启用检测 X 方向的点击事件
   * @param enable ture(Enable tap detection)\false(Disable tap detection)
   */
  void enableTapDetectionOnX(bool enable);

  /**
   * @fn setTapThresholdOnX
   * @brief 设置X方向的点击阈值
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnX(float th);

  /**
   * @fn setTapThresholdOnY
   * @brief 设置Y方向的点击阈值
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnY(float th);

  /**
   * @fn setTapThresholdOnZ
   * @brief 设置Z方向的敲击阈值
   * @param th Threshold(mg),Can only be used in the range of 0~2g
   */
  void setTapThresholdOnZ(float th);

  /**
   * @fn setTapDur
   * @brief 双击识别的最大时间间隔。当启用双击
   * @n 识别时，此寄存器表示两次
   * @n 次连续检测到的点击之间的最大时间，以确定双击事件。
   * @param dur duration，范围：0~15
   * @n time = dur * (1/rate)(unit:s)
   * @n  |                      An example of a linear relationship between an argument and time                                  |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |                |                     |                          |                          |                           |
   * @n  |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   * @n  |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   * @n  |------------------------------------------------------------------------------------------------------------------------|
   */
  void setTapDur(uint8_t dur);

  /**
   * @fn setTapMode
   * @brief 设置点击检测模式，检测单击或单击和双击。
   * @param mode Tap detection mode
   * @n           eOnlySingle   /<Detect only single tap>/
   * @n           eBothSingleDouble /<Detect both single tap and double tap>/
   */
  void setTapMode(eTapMode_t mode);

  /**
   * @fn set6DThreshold
   * @brief 为4D/6D设置阈值，当旋转的阈值超过指定的角度时，就会发生方向改变事件。
   * @param degree   eDegrees80   /<80°>/
   * @n              eDegrees70   /<70°>/
   * @n              eDegrees60   /<60°>/
   * @n              eDegrees50   /<50°>/
   */
  void set6DThreshold(e6DTh_t degree);

  /**
   * @fn readAccX
   * @brief Read the acceleration in the x direction
   * @return  Acceleration data from x(mg), the measurement range is ±2g, ±4g, ±8g or ±16g, set by the setRange() function
   */
  int16_t readAccX();

  /**
   * @fn readAccY
   * @brief Read the acceleration in the y direction
   * @return  Acceleration data from y(mg), the measurement range is ±2g, ±4g, ±8g or ±16g, set by the setRange() function
   */
  int16_t readAccY();

  /**
   * @fn readAccZ
   * @brief Read the acceleration in the z direction
   * @return  Acceleration data from z(mg), the measurement range is ±2g, ±4g, ±8g or ±16g, set by the setRange() function
   */
  int16_t readAccZ();

  /**
   *@fn 已检测到动作
   *@brief 检测是否生成运动
   *@return true（运动生成）/false（无运动）
   */
  bool actDetected();

  /**
   * @fn freeFallDetected
   * @brief 检测是否发生自由落体
   * @return true(检测到自由落体)/false(未检测到自由落体)
   */
  bool freeFallDetected();

  /**
   * @fn oriChangeDetected
   * @brief 检测芯片在朝上/朝下/朝左/朝右/朝前/朝后（即6D）时方向是否发生变化
   * @return true（检测到位置变化）/false（未检测到事件）
   */
  bool oriChangeDetected();

  /**
   * @fn getOrientation
   * @brief 只有在 6D（朝上/朝下/朝左/朝右/朝前/朝后）状态下，
   * 该函数才能获取传感器相对于正 z 轴的方向。
   * @return    eXDown  /<X is now down>/
   * @n         eXUp    /<X is now up>/
   * @n         eYDown  /<Y is now down>/
   * @n         eYUp    /<Y is now up>/
   * @n         eZDown  /<Z is now down>/
   * @n         eZUp    /<Z is now up>/
   */
  eOrient_t getOrientation();

  /**
   * @fn tapDetect
   * @brief 点击检测，可以检测双击还是单击
   * @return   eSTap       /<Single Tap>/
   * @n        eDTap       /<double Tap>/
   * @n        eNoTap,     /<No tap>
   */
  eTap_t tapDetect();

  /**
   * @fn getTapDirection
   * @brief 点击方向源检测
   * @return eDirXUp /<在 X 的正方向检测到点击>/
   * @n eDirXDown /<在 X 的负方向检测到点击>/
   * @n eDirYUp /<在 Y 的正方向检测到点击>/
   * @n eDirYDown /<在 Y 的负方向检测到点击>/
   * @n eDirZUp /<在 Z 的正方向检测到点击>/
   * @n eDirZDown /<在 Z 的负方向检测到点击>/
   */
  eTapDir_t getTapDirection();

  /**
   * @fn getWakeUpDir
   * @brief 唤醒运动方向检测
   * @return eDirX /<X 方向运动唤醒芯片>/
   * @n eDirY /<Y 方向运动唤醒芯片>/
   * @n eDirZ /<Z 方向运动唤醒芯片>/
   * @n eDirError,/<方向检测错误>/
   */
  eWakeUpDir_t getWakeUpDir();

  /**
   * @fn demandData
   * @brief 单一数据按需转换模式
   */
  void demandData();

protected:
  /**
   * @fn readReg
   * @brief 从传感器芯片寄存器读取数据
   * @param reg chip register
   * @param pBuf  buf for store data to read
   * @param size  number of data to read
   * @return Number of successfully read data
   */
  virtual uint8_t readReg(uint8_t reg, uint8_t *pBuf, size_t size) = 0;

  /**
   * @fn writeReg
   * @brief 将数据写入传感器寄存器
   * @param reg register
   * @param pBuf  buf for store data to write
   * @param size  The number of the data in pBuf
   * @return Number of successfully sent data
   */
  virtual uint8_t writeReg(uint8_t reg, const void *pBuf, size_t size) = 0;
  float _range = e2_g;
  int32_t _range1 = 0;

private:
  /**
   * @fn setTapQuiet
   * @brief 设置点击检测后的安静时间：该寄存器代表
   * @n the time after the first detected tap in which there must not be any overthreshold event.
   * @param quiet quiet time
   */
  void setTapQuiet(uint8_t quiet);

  /**
   * @fn setTapShock
   * @brief 设置超过阈值信号检测的最大时间，以将其识别为点击事件。
   * @param shock  shock time
   */
  void setTapShock(uint8_t shock);

  /**
   * @fn set6dFeedData
   * @brief 设置6d过滤数据源
   * @param data 0: rate/2 低通滤波数据发送到 6D 中断函数（默认）
   * @n          1: LPF2 输出数据发送到 6D 中断函数）
   */
  void set6dFeedData(uint8_t data);

  /**
   * @fn setFfThreshold
   * @brief 设置自由落体阈值
   * @param th threshold
   */
  void setFfThreshold(uint8_t th);

  /**
   * @fn setActSleepDur
   * @brief 设置进入睡眠模式的持续时间。
   * @param dur  duration
   */
  void setActSleepDur(uint8_t dur);

  /**
   * @fn lockInterrupt
   * @brief lock Interrupt 在锁存（“1”逻辑）和脉冲（“0”逻辑）模式之间切换
   * @n function 源信号和中断路由到引脚（唤醒、单击/双击）。
   * @param enable true lock Interrupt/false 脉冲中断
   */
  void lockInterrupt(bool enable);
};

class DFRobot_IIS2DLPC_I2C : public DFRobot_LIS2DW12
{
public:
  /**
   * @fn DFRobot_IIS2DLPC_I2C
   * @brief Constructor
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_IIS2DLPC_I2C(TwoWire *pWire = &Wire, uint8_t addr = IIS2DLPC_I2C_ADDR);

  /**
   * @fn begin
   * @brief init function
   * @return true(Initialization succeeded)/fasle(Initialization failed)
   */
  bool begin(void);

protected:
  /**
   * @fn readReg
   * @brief read data from sensor chip register
   * @param reg chip register
   * @param pBuf  buf for store data to read
   * @param size  number of data to read
   * @return Number of successfully read data
   */
  uint8_t readReg(uint8_t reg, uint8_t *pBuf, size_t size);

  /**
   * @fn writeReg
   * @brief Write data to sensor register
   * @param reg register
   * @param pBuf  buf for store data to write
   * @param size  The number of the data in pBuf
   * @return Number of successfully sent data
   */
  uint8_t writeReg(uint8_t reg, const void *pBuf, size_t size);

private:
  uint8_t _deviceAddr;
  TwoWire *_pWire;
};

class DFRobot_IIS2DLPC_SPI : public DFRobot_LIS2DW12
{

public:
  /**
   * @fn DFRobot_IIS2DLPC_SPI
   * @brief Constructor
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_IIS2DLPC_SPI(uint8_t cs = 3, SPIClass *spi = &SPI);

  /**
   * @fn begin
   * @brief init function
   * @return true(Initialization succeeded)/fasle(Initialization failed)
   */
  bool begin(void);

protected:
  /**
   * @fn readReg
   * @brief read data from sensor chip register
   * @param reg chip register
   * @param pBuf  buf for store data to read
   * @param size  number of data to read
   * @return Number of successfully read data
   */
  uint8_t readReg(uint8_t reg, uint8_t *pBuf, size_t size);

  /**
   * @fn writeReg
   * @brief Write data to sensor register
   * @param reg register
   * @param pBuf  buf for store data to write
   * @param size  The number of the data in pBuf
   * @return Number of successfully sent data
   */
  uint8_t writeReg(uint8_t reg, const void *pBuf, size_t size);

private:
  SPIClass *_pSpi;
  uint8_t _cs = 0;
};

class DFRobot_LIS2DW12_I2C : public DFRobot_LIS2DW12
{
public:
  /**
   * @fn DFRobot_LIS2DW12_I2C
   * @brief Constructor
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_LIS2DW12_I2C(TwoWire *pWire = &Wire, uint8_t addr = LIS2DW12_I2C_ADDR);

  /**
   * @fn begin
   * @brief init function
   * @return true(Initialization succeeded)/fasle(Initialization succeeded)
   */
  bool begin(void);

protected:
  /**
   * @fn begin
   * @brief read data from sensor chip register
   * @param reg chip register
   * @param pBuf  buf for store data to read
   * @param size  number of data to read
   * @return Number of successfully read data
   */
  uint8_t readReg(uint8_t reg, uint8_t *pBuf, size_t size);

  /**
   * @fn writeReg
   * @brief Write data to sensor register
   * @param reg register
   * @param pBuf  buf for store data to write
   * @param size  The number of the data in pBuf
   * @return Number of successfully sent data
   */
  uint8_t writeReg(uint8_t reg, const void *pBuf, size_t size);

private:
  uint8_t _deviceAddr;
  TwoWire *_pWire;
};

class DFRobot_LIS2DW12_SPI : public DFRobot_LIS2DW12
{

public:
  /**
   * @fn DFRobot_LIS2DW12_SPI
   * @brief Constructor
   * @param cs : Chip selection pinChip selection pin
   * @param spi :SPI controller
   */
  DFRobot_LIS2DW12_SPI(uint8_t cs = 3, SPIClass *spi = &SPI);

  /**
   * @fn begin
   * @brief init function
   * @return true(Initialization succeeded)/fasle(Initialization succeeded)
   */
  bool begin(void);

protected:
  /**
   * @fn readReg
   * @brief read data from sensor chip register
   * @param reg chip register
   * @param pBuf  buf for store data to read
   * @param size  number of data to read
   * @return Number of successfully read data
   */
  uint8_t readReg(uint8_t reg, uint8_t *pBuf, size_t size);

  /**
   * @fn writeReg
   * @brief Write data to sensor register
   * @param reg register
   * @param pBuf  buf for store data to write
   * @param size  The number of the data in pBuf
   * @return Number of successfully sent data
   */
  uint8_t writeReg(uint8_t reg, const void *pBuf, size_t size);

private:
  SPIClass *_pSpi;
  uint8_t _cs = 0;
};
#endif
