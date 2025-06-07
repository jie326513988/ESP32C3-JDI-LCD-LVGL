/*!
 * @file DFRobot_LIS2DH12.h
 * @brief Define the basic structure of class DFRobot_LIS2DH12 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [tangjie](jie.tang@dfrobot.com)
 * @version  V1.0
 * @date  2021-1-23
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#ifndef DFROBOT_LIS2DH12_H
#define DFROBOT_LIS2DH12_H

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>

//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define DFRobot_LIS2DH12_ADDR    0x18

class DFRobot_LIS2DH12
{
public:
  #define REG_CARD_ID      0x0F     ///<Chip id
  #define REG_CTRL_REG1    0x20     ///<Control register 1
  #define REG_CTRL_REG4    0x23     ///<Control register 4
  #define REG_CTRL_REG2    0x21     ///<Control register 2
  #define REG_CTRL_REG3    0x22     ///<Control register 3
  #define REG_CTRL_REG5    0x24     ///<Control register 5
  #define REG_CTRL_REG6    0x25     ///<Control register 6
  #define REG_STATUS_REG   0x27     ///<Status register
  #define REG_OUT_X_L      0x28     ///<The low order of the X-axis acceleration register
  #define REG_OUT_X_H      0x29     ///<The high point of the X-axis acceleration register
  #define REG_OUT_Y_L      0x2A     ///<The low order of the Y-axis acceleration register
  #define REG_OUT_Y_H      0x2B     ///<The high point of the Y-axis acceleration register
  #define REG_OUT_Z_L      0x2C     ///<The low order of the Z-axis acceleration register
  #define REG_OUT_Z_H      0x2D     ///<The high point of the Z-axis acceleration register
  #define REG_INT1_THS     0x32     ///<Interrupt source 1 threshold
  #define REG_INT2_THS     0x36     ///<Interrupt source 2 threshold
  #define REG_INT1_CFG     0x30     ///<Interrupt source 1 configuration register
  #define REG_INT2_CFG     0x34     ///<Interrupt source 2 configuration register
  #define REG_INT1_SRC     0x31     ///<Interrupt source 1 status register
  #define REG_INT2_SRC     0x35     ///<Interrupt source 2 status register
  
public:

/**
 * @fn  ePowerMode_t
 * @brief  Power mode selection, determine the frequency of data collection Represents the number of data collected per second
 */
typedef enum{
    ePowerDown_0Hz  = 0,
    eLowPower_1Hz   =  0x10,
    eLowPower_10Hz  = 0x20,
    eLowPower_25Hz  = 0x30,
    eLowPower_50Hz  = 0x40,
    eLowPower_100Hz = 0x50,
    eLowPower_200Hz = 0x60,
    eLowPower_400Hz = 0x70
}ePowerMode_t;

/**
 * @fn  eRange_t
 * @brief  Sensor range selection
 */
typedef enum{
    eLIS2DH12_2g = 0x00,/**<±2g>*/
    eLIS2DH12_4g = 0x10,/**<±4g>*/
    eLIS2DH12_8g = 0x20,/**<±8g>*/
    eLIS2DH12_16g = 0x30/**<±16g>*/
}eRange_t;

/**
 * @fn  eInterruptEvent_t
 * @brief  Interrupt event
 */
typedef enum{
  eXLowerThanTh = 0x01,    /**<The acceleration in the x direction is less than the threshold>*/
  eXHigherThanTh = 0x02,  /**<The acceleration in the x direction is greater than the threshold>*/
  eYLowerThanTh = 0x04,   /**<The acceleration in the y direction is less than the threshold>*/
  eYHigherThanTh = 0x08,  /**<The acceleration in the y direction is greater than the threshold>*/
  eZLowerThanTh = 0x10,   /**<The acceleration in the z direction is less than the threshold>*/
  eZHigherThanTh = 0x20,  /**<The acceleration in the z direction is greater than the threshold>*/
  eEventError = 0,        /**< No event>*/
}eInterruptEvent_t;

/**
 * @fn  eInterruptSource_t
 * @brief  Interrupt pin selection
 */
typedef enum{
  eINT1 = 0, /**<int1 >*/
  eINT2,     /**<int2>*/
}eInterruptSource_t;

public:

  /**
   * @fn DFRobot_LIS2DH12
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_LIS2DH12(TwoWire* pWire = &Wire,uint8_t addr = DFRobot_LIS2DH12_ADDR);

  /**
   * @fn begin
   * @brief Initialize the function
   * @return true(Succeed)/false(Failed)
   */
  bool begin(void);

  /**
   * @fn setRange
   * @brief Set the measurement range
   * @param range Range(g)
   * @n           eLIS2DH12_2g, //2g
   * @n           eLIS2DH12_4g, //4g
   * @n           eLIS2DH12_8g, //8g
   * @n           eLIS2DH12_16g, //16g
   */
  void setRange(eRange_t range);

  /**
   * @fn setAcquireRate
   * @brief Set data measurement rate
   * @param rate rate(HZ)
   * @n          ePowerDown_0Hz 
   * @n          eLowPower_1Hz 
   * @n          eLowPower_10Hz 
   * @n          eLowPower_25Hz 
   * @n          eLowPower_50Hz 
   * @n          eLowPower_100Hz
   * @n          eLowPower_200Hz
   * @n          eLowPower_400Hz
   */
  void setAcquireRate(ePowerMode_t rate);

  /**
   * @fn getID
   * @brief Get chip id
   * @return 8 bit serial number
   */
  uint8_t getID();

  /**
   * @fn readAccX
   * @brief Get the acceleration in the x direction
   * @return acceleration from x (unit:g), the mearsurement range is ±100g or ±200g, set by setRange() function.
   */
  int32_t readAccX();

  /**
   * @fn readAccY
   * @brief Get the acceleration in the y direction
   * @return acceleration from y(unit:g), the mearsurement range is ±100g or ±200g, set by setRange() function.
   */
  int32_t readAccY();

  /**
   * @fn readAccZ
   * @brief Get the acceleration in the z direction
   * @return acceleration from z(unit:g), the mearsurement range is ±100g or ±200g, set by setRange() function.
   */
  int32_t readAccZ();
  
  /**
   * @fn setInt1Th
   * @brief Set the threshold of interrupt source 1 interrupt
   * @param threshold The threshold is within the measurement range(unit:g)
   */
  void setInt1Th(uint8_t threshold);

  /**
   * @fn setInt2Th
   * @brief Set interrupt source 2 interrupt generation threshold
   * @param threshold The threshold is within the measurement range(unit:g）
   */
  void setInt2Th(uint8_t threshold);

  /**
   * @fn enableInterruptEvent
   * @brief Enable interrupt
   * @param source Interrupt pin selection
   * @n           eINT1 = 0,/<int1 >/
   * @n           eINT2,/<int2>/
   * @param event Interrupt event selection
   * @n           eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
   * @n           eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
   * @n           eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
   * @n           eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
   * @n           eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
   * @n           eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   */
  void enableInterruptEvent(eInterruptSource_t source, eInterruptEvent_t event);

  /**
   * @fn getInt1Event
   * @brief Check whether the interrupt event'event' is generated in interrupt 1
   * @param event Interrupt event
   * @n           eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
   * @n           eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
   * @n           eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
   * @n           eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
   * @n           eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
   * @n           eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true Generated/false Not generated
   */
  bool getInt1Event(eInterruptEvent_t event);

  /**
   * @fn getInt2Event
   * @brief Check whether the interrupt event'event' is generated in interrupt 1
   * @param event Interrupt event
   * @n           eXLowerThanTh ,/<The acceleration in the x direction is less than the threshold>/
   * @n           eXHigherThanTh ,/<The acceleration in the x direction is greater than the threshold>/
   * @n           eYLowerThanTh,/<The acceleration in the y direction is less than the threshold>/
   * @n           eYHigherThanTh,/<The acceleration in the y direction is greater than the threshold>/
   * @n           eZLowerThanTh,/<The acceleration in the z direction is less than the threshold>/
   * @n           eZHigherThanTh,/<The acceleration in the z direction is greater than the threshold>/
   * @return true Generated/false Not generated
   */
  bool getInt2Event(eInterruptEvent_t event);

  protected:
  /**
   * @fn readReg
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return The number of successfully read data
   */
  uint8_t readReg(uint8_t reg,void * pBuf ,size_t size);
  
  /**
   * @fn writeReg
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   */
  void  writeReg(uint8_t reg,const void *pBuf,size_t size); 

private:
  uint8_t _deviceAddr;
  TwoWire *_pWire;
  uint8_t _mgScaleVel = 16;
  uint8_t _reset = 0;
};
#endif
