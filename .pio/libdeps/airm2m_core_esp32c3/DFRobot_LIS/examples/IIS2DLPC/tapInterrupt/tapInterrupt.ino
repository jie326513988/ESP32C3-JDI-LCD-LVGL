/**！
 * @file tapInterrupt.ino
 * @brief Tap interrupt detection, tapping the module and the desktop near the module can both trigger the interrupt level on pin int1.
 * @n When using SPI communication, use the following program to construct an object by DFRobot_IIS2DLPC_SPI
 * @n In this example, the int2/int1 pin on the module needs to be connected to the interrupt pin on the motherboard. Default UNO(2),
 * @n          Mega2560(2), Leonardo(3), microbit(P0),FireBeetle-ESP8266(D6),FireBeetle-ESP32((D6),FireBeetle-M0(6)        
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
//FRobot_IIS2DLPC_I2C acce(&Wire,0x18);
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

volatile uint8_t intFlag = 0;
void interEvent(){
  intFlag = 1;
}

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
  #if defined(ESP32) || defined(ESP8266)
  //By default, the D6 pin is used as the interrupt pin. Other non-conflicting pins can also be selected as the external interrupt pins
  attachInterrupt(digitalPinToInterrupt(D6)/*Query the interrupt number of the D6 pin*/,interEvent,CHANGE);
  #elif defined(ARDUINO_SAM_ZERO)
  //By default, the pin 5 is used as the interrupt pin. Other non-conflicting pins can also be selected as the external interrupt pins
  attachInterrupt(digitalPinToInterrupt(5)/*Query the interrupt number of the pin 5*/,interEvent,CHANGE);
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
  attachInterrupt(/*Interrupt No*/0,interEvent,CHANGE);//Enable the external interrupt 0, connect INT1/2 to the digital pin of the main controller: 
     //UNO(2), Mega2560(2), Leonardo(3), microbit(P0).
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
  acce.setDataRate(DFRobot_LIS2DW12::eRate_800hz);
  
  //Enable tap detection in the X direction
  acce.enableTapDetectionOnZ(true);
  //Enable tap detection in Y direction
  acce.enableTapDetectionOnY(true);
  //Enable tap detection in the Z direction
  acce.enableTapDetectionOnX(true);
  //The threshold setting in the X direction 
  //Threshold(mg), can only be used in the range of ±2g
  acce.setTapThresholdOnX(/*Threshold = */0.5);
  //The threshold setting in the Y direction   //Threshold(mg), can only be used in the range of ±2g
  acce.setTapThresholdOnY(/*Threshold = */0.5);
  //The threshold setting in the Z direction   //Threshold(mg), can only be used in the range of ±2g)
  acce.setTapThresholdOnZ(/*Threshold = */0.5);
  
  /*
   Set the interval time between two taps when detecting double tap 
    dur duration(0 ~ 15)
    time = dur * (1/ODR)(unit:s)
    |                            An example of a linear relationship between an argument and time                            |
    |------------------------------------------------------------------------------------------------------------------------|
    |                |                     |                          |                          |                           |
    |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
    |------------------------------------------------------------------------------------------------------------------------|
    |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
    |------------------------------------------------------------------------------------------------------------------------|
  */
  acce.setTapDur(/*dur=*/3);
  
  /**！
    Set tap detection mode:
      eOnlySingle(single tap)
      eBothSingleDouble(Single tap and double tap)
  */
  acce.setTapMode(DFRobot_LIS2DW12::eBothSingleDouble);
  
  /**！
    Set the interrupt source of the int1 pin:
      eDoubleTap(Double tap)
      eFreeFall(Free fall)
      eWakeUp(wake)
      eSingleTap(single-tap)
      e6D(Orientation change check)
  */
  acce.setInt1Event(DFRobot_LIS2DW12::eDoubleTap);
  delay(1000);
}

void loop(void){
  if(intFlag == 1){
   //Tap detected
     DFRobot_LIS2DW12:: eTap_t tapEvent = acce.tapDetect();
    //Tap direction source detection
     DFRobot_LIS2DW12::eTapDir_t dir = acce.getTapDirection();
     if(tapEvent  == DFRobot_LIS2DW12::eSTap){
         Serial.print("Single tap Detected :");
     }
     if(tapEvent  == DFRobot_LIS2DW12::eDTap){  
         Serial.print("Double Tap Detected :");
     }
     if(dir == DFRobot_LIS2DW12::eDirXUp){
       Serial.println("tap is detected in the positive direction of X");
     }else if(dir == DFRobot_LIS2DW12::eDirXDown){
       Serial.println("tap is detected in the negative direction of X");
     }else if(dir == DFRobot_LIS2DW12::eDirYUp){
       Serial.println("tap is detected in the positive direction of Y");
     }else if(dir == DFRobot_LIS2DW12::eDirYDown){
       Serial.println("tap is detected in the negative direction of Y");
     }else if(dir == DFRobot_LIS2DW12::eDirZUp){
       Serial.println("tap is detected in the positive direction of Z");
     }else if(dir == DFRobot_LIS2DW12::eDirZDown){
       Serial.println("tap is detected in the negative direction of Z");
     }
     delay(500);
     intFlag = 0;
   
  }
}
