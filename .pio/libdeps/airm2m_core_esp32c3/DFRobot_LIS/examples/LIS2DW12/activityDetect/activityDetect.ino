/**！
* @file activityDetect.ino
* @brief 运动检测，可以检测模块是否在运动
* @n 使用该函数前需要先进入低功耗模式，然后调用setActMode()使芯片进入休眠模式。
* @n 在此状态下，测量速率为12.5hz。
* @n 当检测到某个方向的加速度变化超过阈值时，测量速率将增加
* @n 到我们之前设置的正常速率。阈值可以通过setWakeUpThreshold()函数设置。
* @n 但如果模块停止运动，并且三个方向的加速度变化都小于阈值，芯片会在一段时间后转入休眠
* @n 模式。这个持续时间可以通过setWakeUpDur()函数设置。
* @n 使用SPI时，可以通过改变LIS2DW12_CS的值来修改片选引脚。
* @copyright 版权所有 (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
* @license MIT 许可证 (MIT)
* @author [fengli](li.feng@dfrobot.com)
* @version V1.0
* @date 2021-01-16
* @url https://github.com/DFRobot/DFRobot_LIS
*/

#include <DFRobot_LIS2DW12.h>

//When using I2C communication, use the following program to construct an object by DFRobot_LIS2DW12_I2C
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_LIS2DW12_I2C acce(&Wire,0x18);
DFRobot_LIS2DW12_I2C acce;

//When using SPI communication, use the following program to construct an object by DFRobot_LIS2DW12_SPI
#if defined(ESP32) || defined(ESP8266)
#define LIS2DW12_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define LIS2DW12_CS 3
#elif (defined NRF5)
#define LIS2DW12_CS 2  //The pin on the development board with the corresponding silkscreen printed as P2
#endif
/*!
 * @brief Constructor 
 * @param cs  Chip selection pinChip selection pin
 * @param spi SPI controller
 */
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS);
//DFRobot_LIS2DW12_SPI acce(/*cs = */LIS2DW12_CS,&SPI);

void setup(void){
  Serial.begin(9600);
  while(!acce.begin()){
     Serial.println("Communication failed, check the connection and I2C address setting when using I2C communication.");
     delay(1000);
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Software reset
  acce.softReset();
  
  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /<±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  
  /**！
    Filter settings:
           eLPF(Low pass filter)
           eHPF(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**！
    Set bandwidth：
        eRateDiv_2  ,/<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>/
        eRateDiv_4  ,/<Rate/4 (High Power/Low power)>*
        eRateDiv_10 ,/<Rate/10 (HP/LP)>/
        eRateDiv_20 ,/< Rate/20 (HP/LP)>/
  */
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);
  
  /**
     Wake-up duration: when using the detection mode of eDetectAct in the setActMode() function, it will collect data
   at a normal rate after the chip is awakened. Then after a period of time, the chip will continue to hibernate, collecting data at a frequency of 12.5hz.
    dur (0 ~ 3)
    time = dur * (1/Rate)(unit:s)
    |                    An example of a linear relationship between an argument and time                                    |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
   */
  acce.setWakeUpDur(/*dur = */2);
  
//设置唤醒阈值，当加速度变化超过该值时，会触发eWakeUp事件，单位：mg
//该值在范围内。
  acce.setWakeUpThreshold(/*threshold = */0.2);
  
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
    Set the mode of motion detection:
    eNoDetection       /<No detection>/
    eDetectAct         /<If set this mode, the rate of the chip will drop to 12.5hz and turn into normal measurement frequency 
                        after the eWakeUp event is generated.>/
    eDetectStatMotion  /<In this mode, it can only detect if the chip is in sleep mode without changing the measurement frequency
                         and power mode, continuously measuring the data at normal frequency.>/
  */
  acce.setActMode(DFRobot_LIS2DW12::eDetectAct);
  
  /**！
    Set the interrupt source of the int1 pin:
    eDoubleTap(Double click)
    eFreeFall(Free fall)
    eWakeUp(wake up)
    eSingleTap(single-Click)
    e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);
  
  /**！
    Set the sensor data collection rate:
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
  delay(100);
}

void loop(void){
    //Motion detected
    if(acce.actDetected()){
        Serial.println("Activity Detected!");
        Serial.print("x: ");
        Serial.print(acce.readAccX());
        Serial.print(" mg \t y: ");
        Serial.print(acce.readAccY());
        Serial.print(" mg \t z: ");
        Serial.print(acce.readAccZ());
        Serial.println(" mg");
        delay(100);
    }
}
