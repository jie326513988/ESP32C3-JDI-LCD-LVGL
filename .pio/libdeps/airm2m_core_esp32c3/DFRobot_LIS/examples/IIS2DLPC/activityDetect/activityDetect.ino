/**！
 * @file activityDetect.ino
 * @brief Motion detection, can detect whether the module is moving.
 * @n It’s necessary to go into low power mode before using this function. Then call setActMode() to make the chip enter sleep mode.
 * @n In this state, the measurement rate is 12.5hz.
 * @n When the acceleration change in a certain direction is detected to exceed the threshold, the measurement rate will be increased to the normal rate we set before.
 * @n The threshold can be set by the setWakeUpThreshold() function.
 * @n But if the module stops moving, also, the acceleration change in the three directions is less than the threshold, the chip will turn into sleep
 * @n mode after a period of time. This duration time can be set by the setWakeUpDur() function.
 * @n When using SPI, chip select pin can be modified by changing the value of macro IIS2DLPC_CS
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @url https://github.com/DFRobot/DFRobot_LIS
 */


#include <DFRobot_LIS2DW12.h>

//When using I2C communication, use the following program to construct an object by DFRobot_IIS2DLPC_I2C.
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//FRobot_IIS2DLPC_I2C acce(&Wire,0x18);
DFRobot_IIS2DLPC_I2C acce;

//When using SPI communication, use the following program to construct an object by DFRobot_IIS2DLPC_SPI.
#if defined(ESP32) || defined(ESP8266)
#define IIS2DLPC_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define IIS2DLPC_CS 3
#elif (defined NRF5)
#define IIS2DLPC_CS 2  //The pin on the development board with the corresponding silkscreen printed as P2
#endif
/*!
 * @brief Constructor 
 * @param cs Chip selection pinChip selection pin
 * @param spi SPI controller
 */
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS,&SPI);
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);

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
    |                       An example of a linear relationship between an argument and time                                 |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
   */
  acce.setWakeUpDur(/*dur = */2);
  
  //Set wakeup threshold, when the acceleration change exceeds this value, the eWakeUp event will be triggered,unit:mg
  //The value is within the range
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
    eDetectAct         /<If set this mode, the rate of the chip will drop to 12.5hz and turn normal after the eWakeUp event is generated.>/
    eDetectStatMotion  /<This mode can only detect if the chip is in sleep mode without changing the measurement frequency and power mode,
                         continuously measuring data at normal frequency.>/
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
               eRate_1hz6          /<1.6hz, use only in low-power mode>/
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
