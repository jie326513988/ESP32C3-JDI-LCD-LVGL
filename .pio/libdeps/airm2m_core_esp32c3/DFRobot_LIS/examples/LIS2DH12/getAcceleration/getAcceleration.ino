/**！
 * @file getAcceleration.ino
 * @brief Get the acceleration in the three directions of xyz, the range can be ±2g、±4g、±8g、±16g
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [tangjie](jie.tang@dfrobot.com)
 * @version  V1.0
 * @date  2021-01-16
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS2DH12.h>

/*!
 * @brief Constructor 
 * @param pWire I2c controller
 * @param addr  I2C address(0x18/0x19)
 */
DFRobot_LIS2DH12 acce(&Wire,0x18);

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
              eLIS2DH12_2g,/< ±2g>/
              eLIS2DH12_4g,/< ±4g>/
              eLIS2DH12_8g,/< ±8g>/
              eLIS2DH12_16g,/< ±16g>/
  */
  acce.setRange(/*Range = */DFRobot_LIS2DH12::eLIS2DH12_16g);

  /**
    Set data measurement rate：
      ePowerDown_0Hz 
      eLowPower_1Hz 
      eLowPower_10Hz 
      eLowPower_25Hz 
      eLowPower_50Hz 
      eLowPower_100Hz
      eLowPower_200Hz
      eLowPower_400Hz
  */
  acce.setAcquireRate(/*Rate = */DFRobot_LIS2DH12::eLowPower_10Hz);
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
  //Print acceleration
  Serial.print("x: ");
  Serial.print(ax);
  Serial.print(" mg\t  y: ");
  Serial.print(ay);
  Serial.print(" mg\t  z: ");
  Serial.print(az);
  Serial.println(" mg");
  delay(300);

}
