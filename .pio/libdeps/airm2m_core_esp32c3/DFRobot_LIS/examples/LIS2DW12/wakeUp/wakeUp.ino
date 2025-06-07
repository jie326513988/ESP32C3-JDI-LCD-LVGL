/**！
 * @file wakeUp.ino
 * @brief 当检测到x,y或者z方向的加速度变化超过我们之前设置的阈值时，芯片就会产生唤醒事件。
 * @n 通过访问芯片的寄存器，我们可以知道哪个方向的运动会唤醒芯片。
 * @n 本例中需要通过setWakeUpDur()来设置唤醒时长。
 * @n 当被唤醒后，芯片会持续一段时间，然后进入休眠状态。
 * @n 并通过setWakeUpThreshold()来设置阈值，当加速度变化超过这个值时，就会触发eWakeUp事件。
 * @n 使用SPI时，可以通过改变LIS2DW12_CS的值来修改片选引脚
 * @copyright Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version V1.0
 * @date 2021-01-16
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS2DW12.h>

// 使用I2C通信时，使用如下程序通过DFRobot_LIS2DW12_I2C构造一个对象
/*!
 * @brief Constructor
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
// DFRobot_LIS2DW12_I2C acce(&Wire,0x18);
DFRobot_LIS2DW12_I2C acce;

// 使用SPI通信时，使用以下程序通过DFRobot_LIS2DW12_SPI构造一个对象
#if defined(ESP32) || defined(ESP8266)
#define LIS2DW12_CS D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS2DW12_CS 3
#elif (defined NRF5)
#define LIS2DW12_CS 2 // The pin on the development board with the corresponding silkscreen printed as P2
#endif
/*!
 * @brief Constructor
 * @param cs  Chip selection pinChip selection pin
 * @param spi SPI controller
 */
// DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS,&SPI);
// DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);

void setup(void)
{
  Serial.begin(9600);
  while (!acce.begin())
  {
    Serial.println("Communication failed, check the connection and I2C address setting when using I2C communication.");
    delay(1000);
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(), HEX);
  // Chip soft reset
  acce.softReset();

  /**！
    设置传感器测量范围：
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);

  /**！
  设置电源模式：
  eHighPerformance_14bit /<高性能模式,14位分辨率>/
  eContLowPwr4_14bit /<连续测量,低功耗模式4(14位分辨率)>/
  eContLowPwr3_14bit /<连续测量,低功耗模式3(14位分辨率)>/
  eContLowPwr2_14bit /<连续测量,低功耗模式2(14位分辨率)/
  eContLowPwr1_12bit /<连续测量,低功耗模式1(12位分辨率)>/
  eSingleLowPwr4_14bit /<单次数据按需转换模式,低功耗模式4(14位分辨率)>/
  eSingleLowPwr3_14bit /<单次数据按需转换模式，低功耗模式 3（14 位分辨率）>/
  eSingleLowPwr2_14bit /<按需单次数据转换模式，低功耗模式 2（14 位分辨率）>/
  eSingleLowPwr1_12bit /<按需单次数据转换模式，低功耗模式 1（12 位分辨率）>/
  eHighPerformanceLowNoise_14bit /<高性能模式，启用低噪声，14 位分辨率>/
  eContLowPwrLowNoise4_14bit /<连续测量，低功耗模式 4（14 位分辨率，启用低噪声）>/
  eContLowPwrLowNoise3_14bit /<连续测量，低功耗模式 3（14 位分辨率，启用低噪声）>/
  eContLowPwrLowNoise2_14bit /<连续测量,低功耗模式 2(14 位分辨率,低噪声使能)>/
  eContLowPwrLowNoise1_12bit /<连续测量,低功耗模式 1(12 位分辨率,低噪声使能)>/
  eSingleLowPwrLowNoise4_14bit /<按需单次数据转换模式,低功耗模式 4(14 位分辨率),低噪声使能>/
  eSingleLowPwrLowNoise3_14bit /<按需单次数据转换模式,低功耗模式 3(14 位分辨率),低噪声使能>/
  eSingleLowPwrLowNoise2_14bit /<按需单次数据转换模式,低功耗模式 2(14 位分辨率),低噪声已启用>/
  eSingleLowPwrLowNoise1_12bit /<单数据转换按需模式，低功耗模式 1（12 位分辨率），低噪声已启用>/
  */
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise1_12bit);

  /**！
    设置传感器数据采集率：
               eRate_0hz           /<Measurement off>/
               eRate_1hz6          /<1.6hz, use only under low-power mode>/
               eRate_12hz5         /<12.5hz>/
               eRate_25hz
               eRate_50hz
               eRate_100hz
               eRate_200hz
               eRate_400hz       /<Use only under High-Performance mode>/
               eRate_800hz       /<Use only under High-Performance mode>/
               eRate_1k6hz       /<Use only under High-Performance mode>/
               eSetSwTrig        /<The software triggers a single measurement>/
  */
  acce.setDataRate(DFRobot_LIS2DW12::eRate_200hz);

  /**！
    筛选器设置：
           eLPF(Low pass filter)
           eHPF(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);

  /**
    唤醒时长 – 芯片被唤醒后，会持续一段时间，然后进入休眠状态。
    dur (0 ~ 3)
    time = dur * (1/Rate)（单位：秒）
    |                      参数和时间之间的线性关系示例                                  |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  数据速率     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   时间         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
   */
  acce.setWakeUpDur(/*dur =*/2);

  // 设置唤醒阈值，当加速度变化超过此值时，会触发eWakeUp事件，单位：mg
  // 该值在范围内
  acce.setWakeUpThreshold(/*threshold = */ 0.5);

  /**！
  设置 int1 引脚的中断事件：
  eDoubleTap（双击）
  eFreeFall（自由落体）
  eWakeUp（唤醒）
  eSingleTap（单击）
  e6D（方向变化检查）
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);

  /**！
    设置 int2 引脚的中断事件：
    eSleepChange = 0x40,/<睡眠改变状态路由到 INT2 pad>/
    eSleepState = 0x80,/<在 INT2 pad 上启用 SLEEP_STATE 路由>/
  */
  // acce.setInt2Event(DFRobot_LIS2DW12::eSleepChange);
  delay(100);
}

void loop(void)
{

  // 检测到唤醒事件
  if (acce.actDetected())
  {
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
  }
}
