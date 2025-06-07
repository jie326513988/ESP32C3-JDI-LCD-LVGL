/**！
 * @file getAcceleration.ino
 * @brief Get the acceleration in the three directions of xyz, the range can be ±100g or ±200g
 * @n When using SPI, chip select pin can be modified by changing the value of macro H3LIS200DL_CS
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS.h>

//When using I2C communication, use the following program to construct an object by DFRobot_H3LIS200DL_I2C
/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
//DFRobot_H3LIS200DL_I2C acce(&Wire,0x18);
DFRobot_H3LIS200DL_I2C acce;

//When using SPI communication, use the following program to construct an object by DFRobot_H3LIS200DL_SPI
#if defined(ESP32) || defined(ESP8266)
#define H3LIS200DL_CS  D3
#elif defined(__AVR__) || defined(ARDUINO_SAM_ZERO)
#define H3LIS200DL_CS 3
#elif (defined NRF5)
#define H3LIS200DL_CS 2  //The pin on the development board with the corresponding silkscreen printed as P2 
#endif
/*!
 * @brief Constructor 
 * @param cs  Chip selection pinChip selection pin
 * @param spi  SPI controller
 */
//DFRobot_H3LIS200DL_SPI acce(/*cs = */H3LIS200DL_CS);

void setup(void){

  Serial.begin(9600);
  //Chip initialization
  while(!acce.begin()){
     Serial.println("Initialization failed, please check the connection and I2C address settings");
     delay(1000);
  }
  //Get chip id
  Serial.print("chip id : ");
  Serial.println(acce.getID(),HEX);
  
  /**
    set range:Range(g)
              eH3lis200dl_100g,/< ±100g>/
              eH3lis200dl_200g,/< ±200g>/
  */
  acce.setRange(/*Range = */DFRobot_LIS::eH3lis200dl_100g);

  /**
    Set data measurement rate：
      ePowerDown_0HZ = 0,
      eLowPower_halfHZ,
      eLowPower_1HZ,
      eLowPower_2HZ,
      eLowPower_5HZ,
      eLowPower_10HZ,
      eNormal_50HZ,
      eNormal_100HZ,
      eNormal_400HZ,
      eNormal_1000HZ,
  */
  acce.setAcquireRate(/*Rate = */DFRobot_LIS::eNormal_50HZ);
  Serial.print("Acceleration:\n");
  delay(1000);
}

void loop(void){

  //Get the acceleration in the three directions of xyz
  long ax,ay,az;
  //The measurement range can be ±100g or ±200g set by the setRange() function
  ax = acce.readAccX();//Get the acceleration in the x direction
  ay = acce.readAccY();//Get the acceleration in the y direction
  az = acce.readAccZ();//Get the acceleration in the z direction
  //acce.getAcceFromXYZ(/*accx = */ax,/*accy = */ay,/*accz = */az);//The second method to obtain acceleration in three directions
  //Print acceleration
  Serial.print("x: ");
  Serial.print(ax);
  Serial.print(" g\t  y: ");
  Serial.print(ay);
  Serial.print(" g\t  z: ");
  Serial.print(az);
  Serial.println(" g");
  delay(300);

}
