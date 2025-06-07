/**！
 * @file getAcceleration.ino
 * @brief Get the acceleration in x, y, z directions, the measurement range can be ±2g, ±4g, ±8g or ±16g, set by the setRange() function
 * @n In this example, the continuous measurement mode is selected by default -- the acceleration data will be measured continuously according to the measuring rate.
 * @n You can also use single data conversion on demand mode 1. You need to select a suitable conversion mode in the setPowerMode() function
 * @n                                                        2. Then fill in the setDataRate() function with the eSetSwTrig parameter
 * @n                                                        3. Request a measurement by the demandData() function
 * @n When using SPI, chip select pin can be modified by changing the value of macro IIS2DLPC_CS
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
 * @param cs Chip selection pinChip selection pin
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
  //Set whether to collect data continuously
  acce.continRefresh(true);
  
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
  acce.setDataRate(DFRobot_LIS2DW12::eRate_50hz);
  
  /**！
    Set the sensor measurement range:
                   e2_g   /<±2g>/
                   e4_g   /<±4g>/
                   e8_g   /<±8g>/
                   e16_g  /< ±16g>/
  */
  acce.setRange(DFRobot_LIS2DW12::e2_g);
  
  
  /**！
    Filter settings:
           eLPF (Low pass filter)
           eHPF (High pass filter)
  */
  acce.setFilterPath(DFRobot_LIS2DW12::eLPF);
  
  /**！
    Set bandwidth：
        eRateDiv_2  /<Rate/2 (up to Rate = 800 Hz, 400 Hz when Rate = 1600 Hz)>/
        eRateDiv_4  /<Rate/4 (High Power/Low power)>*
        eRateDiv_10 /<Rate/10 (HP/LP)>/
        eRateDiv_20 /< Rate/20 (HP/LP)>/
  */
  acce.setFilterBandwidth(DFRobot_LIS2DW12::eRateDiv_4);
  
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
  acce.setPowerMode(DFRobot_LIS2DW12::eContLowPwrLowNoise2_14bit);
  Serial.print("Acceleration:\n");
  delay(100);
}

void loop(void){
    //Request a measurement under single data conversion on demand mode
    //acce.demandData();
    //The mearsurement range can be ±2g, ±4g, ±8g or ±16g, set by the setRange() function.
    Serial.print("x: ");
    //Read the acceleration in the x direction
    Serial.print(acce.readAccX());
    Serial.print(" mg \t  y:");
    //Read the acceleration in the y direction
    Serial.print(acce.readAccY());
    Serial.print(" mg \t  z:");
    //Read the acceleration in the z direction
    Serial.print(acce.readAccZ());
    Serial.println(" mg");
    delay(300);
}
