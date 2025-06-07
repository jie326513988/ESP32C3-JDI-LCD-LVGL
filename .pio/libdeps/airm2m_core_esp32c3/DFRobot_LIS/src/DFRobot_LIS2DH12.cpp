/*!
 * @file DFRobot_LIS2DH12.cpp
 * @brief Define the basic structure of class DFRobot_LIS2DH12 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [tangjie](jie.tang@dfrobot.com)
 * @version  V1.0
 * @date  2021-12-29
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include "DFRobot_LIS2DH12.h"


DFRobot_LIS2DH12::DFRobot_LIS2DH12(TwoWire *pWire,uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;
}

bool DFRobot_LIS2DH12::begin(void)
{
  _pWire->begin();
  uint8_t identifier = 0;
  bool ret = false;
  _reset = 1;
  readReg(REG_CARD_ID,&identifier,1);
  DBG(identifier);
  if(identifier == 0x33){
    ret = true;
  }else if(identifier == 0 || identifier == 0xff){
    DBG("Communication failure");
    ret = false;
  }else{
    DBG("the ic is not LIS2DH12");
    ret = false;
  }
  return ret;
}

int32_t DFRobot_LIS2DH12::readAccX()
{
  int8_t sensorData[2];
  int32_t a;
  readReg(REG_OUT_X_L|0x80,sensorData,2);
  #if defined(__AVR__) 
    a = -(sensorData[1]  * (uint8_t)_mgScaleVel);
  #else 
    a = (sensorData[1]  * (uint8_t)_mgScaleVel);
  #endif
  return a;
}

int32_t DFRobot_LIS2DH12::readAccY()
{
  int8_t sensorData[2];
  int32_t a;
  readReg(REG_OUT_Y_L|0x80, sensorData, 2);
  #if defined(__AVR__) 
    a = -((int16_t)sensorData[1]  * (uint8_t)_mgScaleVel);
  #else 
    a = (sensorData[1]  * (uint8_t)_mgScaleVel);
  #endif
  return a;
}

int32_t DFRobot_LIS2DH12::readAccZ()
{
  int8_t sensorData[2];
  int32_t a;
  readReg(REG_OUT_Z_L|0x80, sensorData, 2);
  DBG(sensorData[0]);
  DBG(sensorData[1]);
  #if defined(__AVR__) 
    a = -(sensorData[1]  * (uint8_t)_mgScaleVel);
  #else 
    a = (sensorData[1]* (uint8_t)_mgScaleVel);
  #endif
  return a;
}

void DFRobot_LIS2DH12::setRange(eRange_t range)
{
  switch(range){
    case eLIS2DH12_2g:
      _mgScaleVel = 16;
      break;
    case eLIS2DH12_4g:
      _mgScaleVel = 32;
      break;
    case eLIS2DH12_8g:
      _mgScaleVel = 64;
      break;
    default:
      _mgScaleVel = 192;
      break;
  }
  DBG(range);
  writeReg(REG_CTRL_REG4,&range,1);
}

void DFRobot_LIS2DH12::setAcquireRate(ePowerMode_t rate)
{
  uint8_t reg = 0x0f;
  reg = reg | rate;
  DBG(reg);
  writeReg(REG_CTRL_REG1,&reg,1);
}

uint8_t DFRobot_LIS2DH12::getID()
{
  uint8_t identifier; 
  readReg(REG_CARD_ID,&identifier,1);
  return identifier;
}

void DFRobot_LIS2DH12::writeReg(uint8_t reg, const void * pBuf, size_t size)
{
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);

  for(uint16_t i = 0; i < size; i++){
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_LIS2DH12::readReg(uint8_t reg, void* pBuf, size_t size)
{
  if(pBuf == NULL){
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if( _pWire->endTransmission() != 0){
      return 0;
  }
  _pWire->requestFrom(_deviceAddr, (uint8_t) size);
  for(uint16_t i = 0; i < size; i++){
	  
    _pBuf[i] = _pWire->read();
  }
  return size;
}

void DFRobot_LIS2DH12::setInt1Th(uint8_t threshold)
{
    uint8_t reg = (threshold * 1024)/_mgScaleVel;
    uint8_t reg1 = 0x08;
    uint8_t reg2 = 0x00;
    uint8_t data = 0x40;

    writeReg(REG_CTRL_REG2,&reg2,1);
    writeReg(REG_CTRL_REG3,&data,1);
    writeReg(REG_CTRL_REG5,&reg1,1);
    writeReg(REG_CTRL_REG6,&reg2,1);
    writeReg(REG_INT1_THS,&reg,1);
    readReg(REG_CTRL_REG5,&reg2,1);
    DBG(reg2);
    readReg(REG_CTRL_REG3,&reg2,1);
    DBG(reg2);
}

void DFRobot_LIS2DH12::setInt2Th(uint8_t threshold)
{
    uint8_t reg = (threshold * 1024)/_mgScaleVel;
    uint8_t reg1 = 0x02;
    uint8_t reg2 = 0x00;
    uint8_t data = 0x40;

    writeReg(REG_CTRL_REG2,&reg2,1);
    writeReg(REG_CTRL_REG3,&reg2,1);
    writeReg(REG_CTRL_REG5,&reg1,1);
    writeReg(REG_CTRL_REG6,&data,1);
    writeReg(REG_INT2_THS,&reg,1);
    readReg(REG_CTRL_REG5,&reg2,1);
    DBG(reg2);
    readReg(REG_CTRL_REG6,&reg2,1);
    DBG(reg2);
}

void DFRobot_LIS2DH12::enableInterruptEvent(eInterruptSource_t source,eInterruptEvent_t event)
{
   uint8_t data = 0;
  data = 0x80 | event;
  DBG(data);
  if(source == eINT1)
    writeReg(REG_INT1_CFG,&data,1);
  else
    writeReg(REG_INT2_CFG,&data,1);

  readReg(REG_INT1_CFG,&data,1);
  DBG(data);
}

bool DFRobot_LIS2DH12::getInt1Event(eInterruptEvent_t event)
{
  uint8_t data = 0;
  bool ret = false;
  readReg(REG_INT1_SRC,&data,1);
  DBG(data,HEX);
  if(data & 0x40){
    switch(event){
      case eXLowerThanTh:
        if(!(data & 0x01))
          ret = true;
        break;
      case eXHigherThanTh:
        if((data & 0x02) == 0x02)
          ret = true;
        break;
      case eYLowerThanTh:
        if(!(data & 0x04))
          ret = true;
        break;
      case eYHigherThanTh:
        if((data & 0x08) == 0x08)
          ret = true;
        break;
      case eZLowerThanTh:
        if(!(data & 0x10))
          ret = true;
        break;
      case eZHigherThanTh:
        if((data & 0x20) == 0x20)
          ret = true;
        break;
      default:
        ret = false;
    }
  }else{
    ret = false;
  }
  return ret;
}

bool DFRobot_LIS2DH12::getInt2Event(eInterruptEvent_t event)
{
  uint8_t data = 0;
  bool ret = false;
  readReg(REG_INT2_SRC,&data,1);
  DBG(data,HEX);
  if(data & 0x40){
    switch(event){
      case eXLowerThanTh:
        if(!(data & 0x01))
          ret = true;
        break;
      case eXHigherThanTh:
        if((data & 0x02) == 0x02)
          ret = true;
        break;
      case eYLowerThanTh:
        if(!(data & 0x04))
          ret = true;
        break;
      case eYHigherThanTh:
        if((data & 0x08) == 0x08)
          ret = true;
        break;
      case eZLowerThanTh:
        if(!(data & 0x10))
          ret = true;
        break;
      case eZHigherThanTh:
        if((data & 0x20) == 0x20)
          ret = true;
        break;
      default:
        ret = false;
    }
  }else{
    ret = false;
  }
  return ret;
}