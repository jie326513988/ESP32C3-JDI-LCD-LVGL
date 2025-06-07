/**！
 * @file tapInterrupt.ino
 * @brief tap中断检测，敲击模块和靠近模块的桌面均可触发引脚int1上的中断级别。
 * @n 使用SPI时，可以通过改变宏LIS2DW12_CS的值来修改片选引脚
 * @n 本例中模块上的int2/int1引脚需要和主板上的中断引脚相连。默认 UNO(2),
 * @n Mega2560(2), Leonardo(3), microbit(P0),FireBeetle-ESP8266(D6),FireBeetle-ESP32((D6),FireBeetle-M0(6)
 * @copyright 版权所有 (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license MIT 许可证 (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version V1.0
 * @date 2021-01-16
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS2DW12.h>

// When using I2C communication, use the following program to construct an object by DFRobot_LIS2DW12_I2C
/*!
 * @brief Constructor
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
// DFRobot_LIS2DW12_I2C acce(&Wire,0x18);
DFRobot_LIS2DW12_I2C acce;

// When using SPI communication, use the following program to construct an object by DFRobot_LIS2DW12_SPI
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

volatile uint8_t intFlag = 0;
void interEvent()
{
  intFlag = 1;
}

void setup(void)
{

  Serial.begin(9600);
  while (!acce.begin())
  {
    Serial.println("通信失败，使用I2C通信时请检查连接和I2C地址设置。");
    delay(1000);
  }
  Serial.print("芯片id:");
  Serial.println(acce.getID(), HEX);
  // 芯片软复位
  acce.softReset();
#if defined(ESP32) || defined(ESP8266)
  // 默认情况下，D6引脚用作中断引脚，也可以选择其他不冲突的引脚作为外部中断引脚
  attachInterrupt(digitalPinToInterrupt(D6) /*查询D6引脚的中断号*/, interEvent, CHANGE);
#elif defined(ARDUINO_SAM_ZERO)
  // 默认情况下，5引脚用作中断引脚，也可以选择其他不冲突的引脚作为外部中断引脚
  attachInterrupt(digitalPinToInterrupt(5) /*查询5针的中断号*/, interEvent, CHANGE);
#else
  /*    The Correspondence Table of AVR Series Arduino Interrupt Pins And Terminal Numbers
   * ---------------------------------------------------------------------------------------
   * |                                        |  DigitalPin  | 2  | 3  |                   |
   * |    Uno, Nano, Mini, other 328-based    |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  |                   |
   * |-------------------------------------------------------------------------------------|
   * |                                        |    Pin       | 2  | 3  | 21 | 20 | 19 | 18 |
   * |               Mega2560                 |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  | 2  | 3  | 4  | 5  |
   * |-------------------------------------------------------------------------------------|
   * |                                        |    Pin       | 3  | 2  | 0  | 1  | 7  |    |
   * |    Leonardo, other 32u4-based          |--------------------------------------------|
   * |                                        | Interrupt No | 0  | 1  | 2  | 3  | 4  |    |
   * |--------------------------------------------------------------------------------------
   */
  /*                      The Correspondence Table of micro:bit Interrupt Pins And Terminal Numbers
   * ---------------------------------------------------------------------------------------------------------------------------------------------
   * |             micro:bit                       | DigitalPin |P0-P20 can be used as an external interrupt                                     |
   * |  (When using as an external interrupt,      |---------------------------------------------------------------------------------------------|
   * |no need to set it to input mode with pinMode)|Interrupt No|Interrupt number is a pin digital value, such as P0 interrupt number 0, P1 is 1 |
   * |-------------------------------------------------------------------------------------------------------------------------------------------|
   */
  attachInterrupt(/*Interrupt No*/ 0, interEvent, CHANGE); // Open the external interrupt 0, connect INT1/2 to the digital pin of the main control:
                                                           // UNO(2), Mega2560(2), Leonardo(3), microbit(P0).
#endif

  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);

  /**！
   Set power mode:
       eHighPerformance_14bit         /<High-Performance Mode,14-bit resolution>/
       eContLowPwr4_14bit             /<Continuous measurement,Low-Power Mode 4(14-bit resolution)>/
       eContLowPwr3_14bit             /<Continuous measurement,Low-Power Mode 3(14-bit resolution)>/
       eContLowPwr2_14bit             /<Continuous measurement,Low-Power Mode 2(14-bit resolution)/
       eContLowPwr1_12bit             /<Continuous measurement,Low-Power Mode 1(12-bit resolution)>/
       eSingleLowPwr4_14bit           /<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)>/
       eSingleLowPwr3_14bit           /<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution)>/
       eSingleLowPwr2_14bit           /<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)>/
       eSingleLowPwr1_12bit           /<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)>/
       eHighPerformanceLowNoise_14bit /<High-Performance Mode,Low-noise enabled,14-bit resolution>/
       eContLowPwrLowNoise4_14bit     /<Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise3_14bit     /<Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise2_14bit     /<Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)>/
       eContLowPwrLowNoise1_12bit     /<Continuous measurement,Low-Power Mode 1(12-bit resolution,Low-noise enabled)>/
       eSingleLowPwrLowNoise4_14bit   /<Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise3_14bit   /<Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise2_14bit   /<Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled>/
       eSingleLowPwrLowNoise1_12bit   /<Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled>/
  */
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise1_12bit);

  /**！
    Set the sensor data collection rate:
               eRate_0hz           /<Measurement off>/
               eRate_1hz6          /<1.6hz, Measurement off>/
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
  acce.setDataRate(DFRobot_LIS2DW12::eRate_800hz);

  // 启用Z方向上的敲击检测
  acce.enableTapDetectionOnZ(true);
  // 启用Y方向的敲击检测
  acce.enableTapDetectionOnY(true);
  // 启用X方向上的敲击检测
  acce.enableTapDetectionOnX(true);
  // X方向上的阈值设置,阈值（mg），只能在±2g范围内使用
  acce.setTapThresholdOnX(/*Threshold = */ 0.5);
  // Y方向的阈值设置,阈值（mg），只能在±2g的范围内使用
  acce.setTapThresholdOnY(/*Threshold = */ 0.5);
  // Z方向的阈值设置,阈值（mg），只能在±2g的范围内使用）
  acce.setTapThresholdOnZ(/*Threshold = */ 0.5);

  /*
    设置检测双击时两次点击之间的间隔时间
    持续时间（0~15）
    时间=dur*（1/ODR）（单位：秒）
    |  论证和时间之间线性关系的一个例子                                  |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  数据速率     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   时间         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
  */
  acce.setTapDur(/*dur=*/6);

  /**！
    设置抽头检测模式：
    eOnlySingle（单击）
    eBothSingleDouble（单击和双击）
  */
  acce.setTapMode(DFRobot_LIS2DW12::eBothSingleDouble);

  /**！
    设置int1引脚的中断源：
    e双击（双击）
    eFreeFall（自由落体）
    电子唤醒（唤醒）
    eSingleTap（单点）
    e6D（方向变化检查）
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eDoubleTap);
  delay(1000);
}

void loop(void)
{
  if (intFlag == 1)
  {
    // 检测到点击
    DFRobot_LIS2DW12::eTap_t tapEvent = acce.tapDetect();
    // 敲击方向源检测
    DFRobot_LIS2DW12::eTapDir_t dir = acce.getTapDirection();
    if (tapEvent == DFRobot_LIS2DW12::eSTap)
    {
      Serial.print("检测到单次点击:");
    }
    if (tapEvent == DFRobot_LIS2DW12::eDTap)
    {
      Serial.print("检测到双击:");
    }
    if (dir == DFRobot_LIS2DW12::eDirXUp)
    {
      Serial.println("在X的正方向上检测到敲击");
    }
    else if (dir == DFRobot_LIS2DW12::eDirXDown)
    {
      Serial.println("在X的负方向上检测到敲击");
    }
    else if (dir == DFRobot_LIS2DW12::eDirYUp)
    {
      Serial.println("在Y的正方向上检测到敲击");
    }
    else if (dir == DFRobot_LIS2DW12::eDirYDown)
    {
      Serial.println("在Y的负方向上检测到敲击");
    }
    else if (dir == DFRobot_LIS2DW12::eDirZUp)
    {
      Serial.println("在Z的正方向上检测到敲击");
    }
    else if (dir == DFRobot_LIS2DW12::eDirZDown)
    {
      Serial.println("在Z的负方向上检测到敲击");
    }
    delay(500);
    intFlag = 0;
  }
}
