/**！
 * @file wakeUp.ino
 * @brief When the acceleration change in x, y or z direction is detected to exceed the threshold we set before, the chip will generate a wake-up event.
 * @n By accessing the chip register, we can know which direction of movement wakes up the chip.
 * @n In this example, it is necessary to set the wake-up duration by setWakeUpDur().
 * @n When woken up, the chip will last for a while before it enters the sleep state.
 * @n And to set the threshold by setWakeUpThreshold(). When the acceleration change exceeds this value, the eWakeUp event will be triggered.
 * @n When using SPI, chip select pin can be modified by changing the value of macro IIS2DLPC_CS.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @url https://github.com/DFRobot/DFRobot_LIS
 */


#include <DFRobot_LIS2DW12.h>

//When using I2C communication, use the following program to construct an object by DFRobot_IIS2DLPC_I2C
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//FRobot_IIS2DLPC_I2C acce(&Wire,0x19);
DFRobot_IIS2DLPC_I2C acce;

//When using SPI communication, use the following program to construct an object by DFRobot_IIS2DLPC_SPI
#if defined(ESP32) || defined(ESP8266)
#define IIS2DLPC_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define IIS2DLPC_CS 3
#elif (defined NRF5)
#define IIS2DLPC_CS 2  //The pin on the development board with the corresponding silkscreen printed as P2
#endif
/*!
 * @brief Constructor 
 * @param cs  Chip selection pinChip selection pin
 * @param spi SPI controller
 */
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS,&SPI);
//DFRobot_IIS2DLPC_SPI acce(/*cs = */IIS2DLPC_CS);

void setup(void){

  Serial.begin(9600);
  while(!acce.begin()){
     Serial.println("Communication failed, check the connection and I2C address settings when using I2C communication.");
     delay(1000);
  }
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  //Chip soft reset
  acce.softReset();
  
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
    Filter settings:
           eLPF(Low pass filter)
           eHPF(High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**
    The wake-up duration – when woken up, the chip will last for a while before it enters the sleep state.
    dur (0 ~ 3)
    time = dur * (1/Rate)(unit:s)
    |                         An example of a linear relationship between an argument and time                               |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
   */
  acce.setWakeUpDur(/*dur =*/2);
  
  //Set wakeup threshold, when the acceleration change exceeds this value, the eWakeUp event will be triggered, unit:mg
  //The value is within the range.
  acce.setWakeUpThreshold(/*threshold = */0.5);
  
  /**！
    Set the interrupt event of the int1 pin:
    eDoubleTap(Double click)
    eFreeFall(Free fall)
    eWakeUp(wake)
    eSingleTap(single-Click)
    e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eWakeUp);
  
  /**！
    Set the interrupt event of the int2 pin:
       eSleepChange = 0x40,/<Sleep change status routed to INT2 pad>/
       eSleepState  = 0x80,/<Enable routing of SLEEP_STATE on INT2 pad>/
  */
  //acce.setInt2Event(DFRobot_LIS2DW12::eSleepChange);
  delay(100);
}

void loop(void){

   //Wake-up event detected
   if(acce.actDetected()){
     Serial.print("wake-up event happened in ");
     //Wake-up motion direction detection.
     DFRobot_LIS2DW12::eWakeUpDir_t dir  = acce.getWakeUpDir();
     if(dir == DFRobot_LIS2DW12::eDirX){
       Serial.println("x direction");
     }
     if(dir == DFRobot_LIS2DW12::eDirY){
       Serial.println("y direction");
     }
     if(dir == DFRobot_LIS2DW12::eDirZ){
       Serial.println("z direction");
     }
     delay(100);
   }
}
