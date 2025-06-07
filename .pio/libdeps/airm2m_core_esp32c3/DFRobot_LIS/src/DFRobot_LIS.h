/*!
 * @file DFRobot_LIS.h
 * @brief Define the basic structure of class DFRobot_LIS 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-1-23
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#ifndef DFROBOT_LIS_H
#define DFROBOT_LIS_H

#include "Arduino.h"
#include <Wire.h>
#include <SPI.h>
//#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...) {Serial.print("["); Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
#define DBG(...)
#endif

#define H3LIS200DL_I2C_ADDR  (0x19)    ///<sensor H3LIS200DL IIC address
#define LIS331HH_I2C_ADDR    (0x19)    ///<sensor LIS331HH IIC address
#define H3LIS200DL            0x01       
#define LIS331HH              0x02       
#define ERR_DATA_BUS          -1         ///<error in data bus
#define ERR_IC_VERSION        -2         ///<chip version mismatch


class DFRobot_LIS
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
  
  #define SPI_READ_BIT     0X80   ///<bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) from the device is read.
  
public:

/**
 * @fn  ePowerMode_t
 * @brief  Power mode selection, determine the frequency of data collection Represents the number of data collected per second
 */
typedef enum{
   ePowerDown_0HZ = 0,/*Measurement off*/
   eLowPower_halfHZ = 0x40,/*0.5 hz*/
   eLowPower_1HZ  = 0x60,
   eLowPower_2HZ  = 0x80,
   eLowPower_5HZ  = 0xA0,
   eLowPower_10HZ = 0xC0,
   eNormal_50HZ   = 0x20,
   eNormal_100HZ  = 0x28,
   eNormal_400HZ  = 0x30,
   eNormal_1000HZ = 0x38,
}ePowerMode_t;

/**
 * @fn  eRange_t
 * @brief Sensor range selection
 */
typedef enum{
  eH3lis200dl_100g = 100,/**< ±100g>*/
  eH3lis200dl_200g = 200,/**< ±200g>*/

  eLis331hh_6g = 6,/**<±6g>*/
  eLis331hh_12g = 12,/**<±12g>*/
  eLis331hh_24g = 24/**<±24g>*/
  
}eRange_t;

/**
 * @fn eHighPassFilter_t
 * @brief                        High-pass filter cut-off frequency configuration
 * @n |--------------------------------------------------------------------------------------------------------|
 * @n |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
 * @n |   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
 * @n |--------------------------------------------------------------------------------------------------------|
 * @n |  eCutOffMode1  |     1           |         2            |            8         |             20        |
 * @n |--------------------------------------------------------------------------------------------------------|
 * @n |  eCutOffMode2  |    0.5          |         1            |            4         |             10        |
 * @n |--------------------------------------------------------------------------------------------------------|
 * @n |  eCutOffMode3  |    0.25         |         0.5          |            2         |             5         |
 * @n |--------------------------------------------------------------------------------------------------------|
 * @n |  eCutOffMode4  |    0.125        |         0.25         |            1         |             2.5       |
 * @n |--------------------------------------------------------------------------------------------------------|
 */
typedef enum{
  eCutOffMode1 = 0,
  eCutOffMode2,
  eCutOffMode3,
  eCutOffMode4,
  eShutDown,
}eHighPassFilter_t;

/**
 * @fn eInterruptEvent_t
 * @brief Interrupt event
 */
typedef enum{
  eXLowerThanTh = 0x1,    /**<The acceleration in the x direction is less than the threshold>*/
  eXHigherThanTh = 0x2,   /**<The acceleration in the x direction is greater than the threshold>*/
  eYLowerThanTh = 0x4,    /**<The acceleration in the y direction is less than the threshold>*/
  eYHigherThanTh = 0x8,   /**<The acceleration in the y direction is greater than the threshold>*/
  eZLowerThanTh = 0x10,   /**<The acceleration in the z direction is less than the threshold>*/
  eZHigherThanTh = 0x20,  /**<The acceleration in the z direction is greater than the threshold>*/
  eEventError = 0,        /**< No event>*/
}eInterruptEvent_t;

/**
 * @fn  eInterruptSource_t
 * @brief Interrupt pin selection
 */
typedef enum{
  eINT1 = 0, /**<int1 >*/
  eINT2,     /**<int2>*/
}eInterruptSource_t;

public:
  DFRobot_LIS();
  /**
   * @fn begin
   * @brief Initialize the function
   * @return true(Succeed)/false(Failed)
   */
  bool begin(void);
 
  /**
   * @fn getID
   * @brief Get chip id
   * @return 8 bit serial number
   */
  uint8_t getID();
  
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
   * @fn setAcquireRate
   * @brief Set data measurement rate
   * @param rate rate(HZ)
   * @n          ePowerDown_0HZ   //Measurement off
   * @n          eLowPower_halfHZ //0.5 hz
   * @n          eLowPower_1HZ
   * @n          eLowPower_2HZ
   * @n          eLowPower_5HZ
   * @n          eLowPower_10HZ
   * @n          eNormal_50HZ
   * @n          eNormal_100HZ
   * @n          eNormal_400HZ
   * @n          eNormal_1000HZ
   */
  void setAcquireRate(ePowerMode_t rate);
  
  /**
   * @fn setHFilterMode
   * @brief Set data filtering mode
   * @param mode Four modes
   * @n          eCutOffMode1 = 0,
   * @n          eCutOffMode2,
   * @n          eCutOffMode3,
   * @n          eCutOffMode4,
   * @n          eShutDown,  no filtering
   * @n  eg：Select eCutOffMode1 in 50HZ, and the filtered frequency is 1HZ
   * @n |---------------------------High-pass filter cut-off frequency configuration-----------------------------|
   * @n |--------------------------------------------------------------------------------------------------------|
   * @n |                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
   * @n |   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
   * @n |--------------------------------------------------------------------------------------------------------|
   * @n |  eCutOffMode1  |     1           |         2            |            8         |             20        |
   * @n |--------------------------------------------------------------------------------------------------------|
   * @n |  eCutOffMode2  |    0.5          |         1            |            4         |             10        |
   * @n |--------------------------------------------------------------------------------------------------------|
   * @n |  eCutOffMode3  |    0.25         |         0.5          |            2         |             5         |
   * @n |--------------------------------------------------------------------------------------------------------|
   * @n |  eCutOffMode4  |    0.125        |         0.25         |            1         |             2.5       |
   * @n |--------------------------------------------------------------------------------------------------------|
   */
  void setHFilterMode(eHighPassFilter_t mode);

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
   * @fn enableSleep
   * @brief Enable sleep wake function
   * @param enable true(enable)\false(disable)
   * @return false Indicate enable failed/true Indicate enable succeed
   */
  bool enableSleep(bool enable);
  
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
   * @brief Check whether the interrupt event'event' is generated in interrupt 2
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

  /**
   * @fn getSleepState
   * @brief Get whether the sensor is in sleep mode
   * @return true(In sleep mode)/false(In normal mode)
   */
  bool getSleepState();
  
  /**
   * @fn setSleepFlag
   * @brief Set the sleep state flag
   * @param flag true(Flag the current mode as sleep mode)/false(Flag the current mode as normal mode)
   */
  void setSleepFlag(bool flag);
protected:

  uint8_t _reset = 0;
  uint8_t _range = 100;
  bool _state = true;
  
  /**
   * @fn readReg
   * @brief read data from sensor chip register
   * @param reg chip register 
   * @param pBuf  buf for store data to read 
   * @param size  number of data to read
   * @return The number of successfully read data
   */
  virtual uint8_t readReg(uint8_t reg,void * pBuf ,size_t size) = 0;
  
  /**
   * @fn writeReg
   * @brief Write data to sensor register 
   * @param reg register
   * @param pBuf  buf for store data to write 
   * @param size  The number of the data in pBuf
   * @return The number of successfully sent data
   */
  virtual uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size)= 0; 

};

class DFRobot_H3LIS200DL_I2C : public DFRobot_LIS{
public:
  /**
   * @fn DFRobot_H3LIS200DL_I2C
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x18/0x19)
   */
  DFRobot_H3LIS200DL_I2C(TwoWire * pWire = &Wire,uint8_t addr = H3LIS200DL_I2C_ADDR);
  /**
   * @fn begin
   * @brief init function
   * @return true(Succeed)/false(Failed)
   */
  bool begin(void);
  
  /**
   * @fn setRange
   * @brief Set the measurement range
   * @param range Range(g)
   * @n           eH3lis200dl_100g, //±100g
   * @n           eH3lis200dl_200g, //±200g
   * @return true(Set successfully)/false(Set failed)
   */
  bool setRange(eRange_t range);

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
   * @fn getAcceFromXYZ
   * @brief Get the acceleration in the three directions of xyz
   * @param accx Store the variable of acceleration in x direction
   * @param accy Store the variable of acceleration in y direction
   * @param accz Store the variable of acceleration in z direction
   * @return true(Get data successfully)/false(Data not ready)
   */
  bool getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz);
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
   * @return The number of successfully sent data
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
  uint8_t _deviceAddr;
  TwoWire *_pWire;
};

class DFRobot_H3LIS200DL_SPI : public DFRobot_LIS{
public:
  /**
   * @fn DFRobot_H3LIS200DL_SPI
   * @brief Constructor 
   * @param cs : Chip selection pin 
   * @param spi :SPI controller
   */
  DFRobot_H3LIS200DL_SPI(uint8_t cs,SPIClass *spi=&SPI);
  
  /**
   * @fn begin
   * @brief init function
   * @return true(Succeed)/false(Failed)
   */
  bool begin(void);
  
  /**
   * @fn setRange
   * @brief Set the measurement range
   * @param range Range(g)
   * @n           eH3lis200dl_100g, //±100g
   * @n           eH3lis200dl_200g, //±200g
   * @return true(Set successfully)/false(Set failed)
   */
  bool setRange(eRange_t range);
  
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
   * @fn getAcceFromXYZ
   * @brief Get the acceleration in the three directions of xyz
   * @param accx Store the variable of acceleration in x direction
   * @param accy Store the variable of acceleration in y direction
   * @param accz Store the variable of acceleration in z direction
   * @return true(Get data successfully)/false(Data not ready)
   */
  bool getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz);
  
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
   * @return The number of successfully sent data
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
  SPIClass *_pSpi;
  uint8_t _cs;
};

class DFRobot_LIS331HH_I2C : public DFRobot_LIS{
  
public:
  /**
   * @fn DFRobot_LIS331HH_I2C
   * @brief Constructor 
   * @param pWire I2c controller
   * @param addr  I2C address(0x19/0x18)
   */
  DFRobot_LIS331HH_I2C(TwoWire * pWire = &Wire,uint8_t addr = LIS331HH_I2C_ADDR);
  /**
   * @fn begin
   * @brief init function
   * @return true(Succeed)/false(Failed)
   */
  bool begin(void);
  
  /**
   * @fn setRange
   * @brief Set the measurement range
   * @param range Range(g)
   * @n           eLis331hh_6g = 6,//±6g
   * @n           eLis331hh_12g = 12 //±12g
   * @n           eLis331hh_24g = 24 //±24g  
   * @return true(Set successfully)/false(Set failed)
   */
  bool setRange(eRange_t range);

  /**
   * @fn readAccX
   * @brief Get the acceleration in the x direction
   * @return acceleration from x (unit:mg), the mearsurement range is ±6g, ±12g or ±24g, set by setRange() function.
   */
  int32_t readAccX();
  
  /**
   * @fn readAccY
   * @brief Get the acceleration in the y direction
   * @return acceleration from y(unit:mg), the mearsurement range is ±6g, ±12g or ±24g, set by setRange() function.
   */
  int32_t readAccY();
  
  /**
   * @fn readAccZ
   * @brief Get the acceleration in the z direction
   * @return acceleration from z(unit:mg), the mearsurement range is ±6g, ±12g or ±24g, set by setRange() function.
   */
  int32_t readAccZ();
  
  /**
   * @fn getAcceFromXYZ
   * @brief Get the acceleration in the three directions of xyz
   * @param accx Store the variable of acceleration in x direction
   * @param accy Store the variable of acceleration in y direction
   * @param accz Store the variable of acceleration in z direction
   * @return true(Get data successfully)/false(Data not ready)
   */
  bool getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz);
  
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
   * @return The number of successfully sent data
   */
  uint8_t  writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    uint8_t _deviceAddr;
    TwoWire *_pWire;
};

class DFRobot_LIS331HH_SPI : public DFRobot_LIS{
  
public:

  /**
   * @fn DFRobot_LIS331HH_SPI
   * @brief Constructor 
   * @param cs : Chip selection pin
   * @param spi :SPI controller
   */
  DFRobot_LIS331HH_SPI(uint8_t cs,SPIClass *spi=&SPI);
  
  /**
   * @fn begin
   * @brief init function
   * @return true(Succeed)/false(Failed)
   */
  bool begin(void);
  
  /**
   * @fn setRange
   * @brief Set the measurement range
   * @param range Range(g)
   * @n           eLis331hh_6g = 6,//±6g
   * @n           eLis331hh_12g = 12 //±12g
   * @n           eLis331hh_24g = 24 //±24g  
   * @return true(Set successfully)/false(Set failed)
   */
  bool setRange(eRange_t range);
  
  /**
   * @fn readAccX
   * @brief Get the acceleration in the x direction
   * @return acceleration from x (unit:mg), the mearsurement range is ±6g, ±12g or ±24g, set by setRange() function.
   */
  int32_t readAccX();
  
  /**
   * @fn readAccY
   * @brief Get the acceleration in the y direction
   * @return acceleration from y(unit:mg), the mearsurement range is ±6g, ±12g or ±24g, set by setRange() function.
   */
  int32_t readAccY();
  
  /**
   * @fn readAccZ
   * @brief Get the acceleration in the z direction
   * @return acceleration from z(unit:mg), the mearsurement range is ±6g, ±12g or ±24g, set by setRange() function.
   */
  int32_t readAccZ();
  
  /**
   * @fn getAcceFromXYZ
   * @brief Get the acceleration in the three directions of xyz
   * @param accx Store the variable of acceleration in x direction
   * @param accy Store the variable of acceleration in y direction
   * @param accz Store the variable of acceleration in z direction
   * @return true(Successfully get data)/false(Data not ready)
   */
  bool getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz);
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
   * @return The number of successfully sent data
   */
  uint8_t writeReg(uint8_t reg,const void *pBuf,size_t size); 
private:
    SPIClass *_pSpi;
    uint8_t _cs;
};
#endif
