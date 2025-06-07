/*!
 * @file DFRobot_LIS.cpp
 * @brief Define the basic structure of class DFRobot_LIS 
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2021-1-27
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS.h>
DFRobot_LIS::DFRobot_LIS(){}

bool DFRobot_LIS::begin(void){

  uint8_t identifier = 0; 
  bool ret = false;
  _reset = 1;
  readReg(REG_CARD_ID,&identifier,1);
  DBG(identifier);
  if(identifier == 0x32){
    ret = true;
  } else if(identifier == 0 || identifier == 0xff){
    DBG("Communication failure");
    ret = false;
  } else {  
    DBG("the ic is not H3LIS");
    ret = false;
  }
  return ret;
}

uint8_t DFRobot_LIS::getID(){
  uint8_t identifier; 
  readReg(REG_CARD_ID,&identifier,1);
  return identifier;
}

void DFRobot_LIS::setAcquireRate(ePowerMode_t rate)
{
  uint8_t reg = 0;
  readReg(REG_CTRL_REG1,&reg,1);
  reg = reg & (~(0x7 << 5));
  reg = reg & (~(0x3 << 3));
  reg = reg | rate;

  DBG(reg);
  writeReg(REG_CTRL_REG1,&reg,1);
}
void DFRobot_LIS::setInt1Th(uint8_t threshold)
{
    uint8_t reg = (threshold * 128)/_range;
    DBG(reg);
    writeReg(REG_INT1_THS,&reg,1);
}
void DFRobot_LIS::setInt2Th(uint8_t threshold)
{
    uint8_t reg = (threshold * 128)/_range;
    DBG(reg);
    writeReg(REG_INT2_THS,&reg,1);
}
void DFRobot_LIS::enableInterruptEvent(eInterruptSource_t source,eInterruptEvent_t event)
{
  uint8_t reg = 0;
  if(source == eINT1)
    readReg(REG_INT1_CFG,&reg,1);
  else
    readReg(REG_INT2_CFG,&reg,1);
  if(_reset == 1){
     reg = 0;
     _reset = 0;
  }
  reg = reg | event;
  DBG(reg);
  if(source == eINT1)
    writeReg(REG_INT1_CFG,&reg,1);
  else
    writeReg(REG_INT2_CFG,&reg,1);
 
 
}
bool DFRobot_LIS::getInt1Event(eInterruptEvent_t event)
{
  uint8_t reg = 0;
  readReg(REG_INT1_SRC,&reg,1);
  DBG(reg);
  if(reg & (1 << event))  return true;
  return false;
}
bool DFRobot_LIS::getInt2Event(eInterruptEvent_t event)
{
  uint8_t reg = 0;
  readReg(REG_INT2_SRC,&reg,1);
  DBG(reg);
  if(reg & (1 << event)) return true;
  return false;
}


bool DFRobot_LIS::enableSleep(bool enable)
{
  uint8_t reg = 0;
  uint8_t readRe = 0;

  if(enable == true)
    reg = 3;
  else
    reg = 0;
  writeReg(REG_CTRL_REG5,&reg,1);
  
  readReg(REG_CTRL_REG5,&readRe,1);
  
  if(reg == readRe)
    return true;
  else 
    return false;
}
void DFRobot_LIS::setHFilterMode(eHighPassFilter_t mode){

  uint8_t reg = 0;
  readReg(REG_CTRL_REG2,&reg,1);
  if(mode == eShutDown){
    reg = reg & (~0x10);
    return;
  } else{
    reg = reg | 0x10;
  }
  reg = reg & (~3);
  reg = reg | (uint8_t)mode;
  DBG(reg);
  writeReg(REG_CTRL_REG2,&reg,1);
}
bool DFRobot_LIS::getSleepState()
{
  return _state;
}
void DFRobot_LIS::setSleepFlag(bool flag){

   _state = flag;
}

DFRobot_H3LIS200DL_I2C::DFRobot_H3LIS200DL_I2C(TwoWire * pWire,uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;
}

bool DFRobot_H3LIS200DL_I2C::begin(void)
{
  _pWire->begin();
  return DFRobot_LIS::begin();
}
bool DFRobot_H3LIS200DL_I2C::getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz)
{
  uint8_t reg = 0;
  uint8_t sensorData[3];
  readReg(REG_STATUS_REG,&reg,1);
  if((reg & 0x01) == 1){
    for(uint8_t i = 0 ;i<6;i++){
      readReg(REG_OUT_Z_H+i,&sensorData[i],1);
    }
    accx = ((int8_t)sensorData[1]*_range)/128;
    accy = ((int8_t)sensorData[3]*_range)/128;
    accz = ((int8_t)sensorData[5]*_range)/128;
    return true;
  }
return false;
}
int32_t DFRobot_H3LIS200DL_I2C::readAccX(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_X_L,&sensorData[0],1);
  readReg(REG_OUT_X_L+1,&sensorData[1],1);
  a = ((int8_t)sensorData[1] *_range)/128;

  return a;
}
int32_t DFRobot_H3LIS200DL_I2C::readAccY(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;
  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Y_L,&sensorData[0],1);
  readReg(REG_OUT_Y_L+1,&sensorData[1],1);
  a = ((int8_t)sensorData[1] *_range)/128;
  return a;
}
int32_t DFRobot_H3LIS200DL_I2C::readAccZ(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;
  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Z_L,&sensorData[0],1);
  readReg(REG_OUT_Z_L+1,&sensorData[1],1);
  a = ((int8_t)sensorData[1] *_range)/128;
  return a;
}
bool DFRobot_H3LIS200DL_I2C::setRange(eRange_t range){
  uint8_t reg = 0;
  readReg(REG_CTRL_REG4,&reg,1);

  if(range == eH3lis200dl_100g){
     reg = reg & (~0x10);
     _range = 100;
   } else if(range == eH3lis200dl_200g){
     reg = reg | 0x10;
     _range = 200;
   } else {
     reg = reg & (~0x10);
   }
  DBG(reg);
  writeReg(REG_CTRL_REG4,&reg,1);
  return true;
}
uint8_t DFRobot_H3LIS200DL_I2C::writeReg(uint8_t reg, const void * pBuf, size_t size)
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
  return 0;
}

uint8_t DFRobot_H3LIS200DL_I2C::readReg(uint8_t reg, void* pBuf, size_t size)
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
	//Serial.println(_pBuf[i],HEX);
	  DBG(_pBuf[i]);
  }
  return size;
}

DFRobot_H3LIS200DL_SPI::DFRobot_H3LIS200DL_SPI(uint8_t cs,SPIClass *pSpi)
{
  _pSpi = pSpi;
  _cs = cs;
}

bool DFRobot_H3LIS200DL_SPI::begin(void){

  _pSpi->begin();
  pinMode(_cs,OUTPUT);
  digitalWrite(_cs,1);
  return DFRobot_LIS::begin();
}
bool DFRobot_H3LIS200DL_SPI::getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz)
{
  uint8_t reg = 0;
  uint8_t sensorData[3];
  readReg(REG_STATUS_REG,&reg,1);
  if((reg & 0x01) == 1){
    for(uint8_t i = 0 ;i<6 ;i++){
      readReg(REG_OUT_Z_H+i,&sensorData[i],1);
    }
    accx = ((int8_t)sensorData[1]*_range)/128;
    accy = ((int8_t)sensorData[3]*_range)/128;
    accz = ((int8_t)sensorData[5]*_range)/128;
    return true;
  }
return false;
}
int32_t DFRobot_H3LIS200DL_SPI::readAccX(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_X_L,&sensorData[0],1);
  readReg(REG_OUT_X_L+1,&sensorData[1],1);
  a = ((int8_t)sensorData[1] *_range)/128;

  return a;
}
int32_t DFRobot_H3LIS200DL_SPI::readAccY(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Y_L,&sensorData[0],1);
  readReg(REG_OUT_Y_L+1,&sensorData[1],1);
  a = ((int8_t)sensorData[1] *_range)/128;
  return a;
}
int32_t DFRobot_H3LIS200DL_SPI::readAccZ(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Z_L,&sensorData[0],1);
  readReg(REG_OUT_Z_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1] *_range)/128;
  return a;
}
bool DFRobot_H3LIS200DL_SPI::setRange(eRange_t range){
  uint8_t reg = 0;
  readReg(REG_CTRL_REG4,&reg,1);

  if(range == eH3lis200dl_100g){
     reg = reg & (~0x10);
     _range = 100;
   } else if(range == eH3lis200dl_200g){
     reg = reg | 0x10;
     _range = 200;
   } else {
     reg = reg & (~0x10);
   }
  DBG(reg);
  writeReg(REG_CTRL_REG4,&reg,1);
  return true;
}
uint8_t DFRobot_H3LIS200DL_SPI::readReg(uint8_t reg,void * pBuf ,size_t size){
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  size_t count = 0;
  reg = reg | SPI_READ_BIT;
#if (defined NRF5)
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
#else
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
#endif
  digitalWrite(_cs,0);
  _pSpi->transfer(reg);
  while(size--) {
    *_pBuf = SPI.transfer(0x00);
    _pBuf++;
    count++;
  }
  _pSpi->endTransaction();
  digitalWrite(_cs,1);
  return count;

}

uint8_t  DFRobot_H3LIS200DL_SPI::writeReg(uint8_t reg,const void *pBuf,size_t size){
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_cs,0);
  _pSpi->transfer(reg);
  while(size--) {
    _pSpi->transfer(*_pBuf);
    _pBuf ++;
  }

  SPI.endTransaction();
  digitalWrite(_cs,1);
  return 1;
}
DFRobot_LIS331HH_I2C::DFRobot_LIS331HH_I2C(TwoWire * pWire,uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;
}

bool DFRobot_LIS331HH_I2C::begin(void)
{
  _pWire->begin();
  return DFRobot_LIS::begin();
}
bool DFRobot_LIS331HH_I2C::getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz)
{
  uint8_t reg = 0;
  uint8_t sensorData[3];
  int32_t a,b,c;
  readReg(REG_STATUS_REG,&reg,1);
  if((reg & 0x01) == 1){
    for(uint8_t i = 0 ;i<6 ;i++){
      readReg(REG_OUT_Z_H+i,&sensorData[i],1);
    }
    a = ((int8_t)sensorData[1])*256+(int8_t)sensorData[0];
    accx = (a * 1000 * (uint32_t)_range)/(32768);
    b = ((int8_t)sensorData[3])*256+(int8_t)sensorData[2];
    accy = (b * 1000 * (uint32_t)_range)/(32768);
    c = ((int8_t)sensorData[5])*256+(int8_t)sensorData[4];
    accz = (c * 1000 * (uint32_t)_range)/(32768);
    return true;
  }
return false;
}
bool DFRobot_LIS331HH_I2C::setRange(eRange_t range){
  uint8_t reg = 0;
  readReg(REG_CTRL_REG4,&reg,1);

  switch(range){
   case eLis331hh_6g :{
     _range = range;
     reg = reg&(~(3<<4));
     break;
   }
   case eLis331hh_12g :{
    _range = range;
     reg = reg&(~(3<<4));
     reg = reg | (0x01<<4);
     break;
   }
   case eLis331hh_24g : {
     _range = range;
     reg = reg&(~(3<<4));
     reg = reg | (0x03<<4);
     break;
   }
  default:
    break;
  }
  DBG(reg);
  writeReg(REG_CTRL_REG4,&reg,1);
  return true;
}
int32_t DFRobot_LIS331HH_I2C::readAccX(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_X_L,&sensorData[0],1);
  readReg(REG_OUT_X_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1])*256+sensorData[0];
  #if defined(__AVR__) 
    a = -(a * 1000 * (uint32_t)_range)/(32768);
  #else 
    a = (a * 1000 * (uint32_t)_range)/(32768);
  #endif

  return a;
}
int32_t DFRobot_LIS331HH_I2C::readAccY(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Y_L,&sensorData[0],1);
  readReg(REG_OUT_Y_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1])*256+sensorData[0];
  #if defined(__AVR__) 
    a = -(a * 1000 * (uint32_t)_range)/(32768);
  #else 
    a = (a * 1000 * (uint32_t)_range)/(32768);
  #endif

     return a;
}
int32_t DFRobot_LIS331HH_I2C::readAccZ(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;
  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Z_L,&sensorData[0],1);
  readReg(REG_OUT_Z_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1])*256+sensorData[0];
  #if defined(__AVR__) 
    a = -(a * 1000 * (uint32_t)_range)/(32768);
  #else 
    a = (a * 1000 * (uint32_t)_range)/(32768);
  #endif
     return a;
}
uint8_t DFRobot_LIS331HH_I2C::writeReg(uint8_t reg, const void * pBuf, size_t size)
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
  return 1;
}

uint8_t DFRobot_LIS331HH_I2C::readReg(uint8_t reg, void* pBuf, size_t size)
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

DFRobot_LIS331HH_SPI::DFRobot_LIS331HH_SPI(uint8_t cs,SPIClass *pSpi)
{
  _pSpi = pSpi;
  _cs = cs;
}

bool DFRobot_LIS331HH_SPI::begin(void){

  _pSpi->begin();
  pinMode(_cs,OUTPUT);
  digitalWrite(_cs,1);
  return DFRobot_LIS::begin();
}
bool DFRobot_LIS331HH_SPI::getAcceFromXYZ(int32_t &accx,int32_t &accy,int32_t &accz)
{
  uint8_t reg = 0;
  uint8_t sensorData[3];
  int32_t a,b,c;
  readReg(REG_STATUS_REG,&reg,1);
  if((reg & 0x01) == 1){


    for(uint8_t i = 0 ;i<6 ;i++){
      readReg(REG_OUT_Z_H+i,&sensorData[i],1);
    }
    a = ((int8_t)sensorData[1])*256+(int8_t)sensorData[0];
    accx = (a * 1000 * (uint8_t)_range)/(32768);
    b = ((int8_t)sensorData[3])*256+(int8_t)sensorData[2];
    accy = (b * 1000 * (uint8_t)_range)/(32768);
    c = ((int8_t)sensorData[5])*256+(int8_t)sensorData[4];
    accz = (c * 1000 * (uint8_t)_range)/(32768);
    return true;
  }
return false;
}
bool DFRobot_LIS331HH_SPI::setRange(eRange_t range){
  uint8_t reg = 0;
  readReg(REG_CTRL_REG4,&reg,1);

  switch(range){
   case eLis331hh_6g :{
     _range = range;
     reg = reg&(~(3<<4));
     break;
   }
   case eLis331hh_12g :{
    _range = range;
     reg = reg&(~(3<<4));
     reg = reg | (0x01<<4);
     break;
   }
   case eLis331hh_24g : {
     _range = range;
     reg = reg&(~(3<<4));
     reg = reg | (0x03<<4);
     break;
   }
   default:
    break;
  }
  DBG(reg);
  writeReg(REG_CTRL_REG4,&reg,1);
  return true;
}
int32_t DFRobot_LIS331HH_SPI::readAccX(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_X_L,&sensorData[0],1);
  readReg(REG_OUT_X_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1])*256+sensorData[0];
  #if defined(__AVR__) 
    a = -(a * 1000 * (uint32_t)_range)/(32768);
  #else 
    a = (a * 1000 * (uint32_t)_range)/(32768);
  #endif
  return a;
}
int32_t DFRobot_LIS331HH_SPI::readAccY(){
  uint8_t reg = 0;
  uint8_t sensorData[2];
  int32_t a = 0;

  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Y_L,&sensorData[0],1);
  readReg(REG_OUT_Y_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1])*256+sensorData[0];
  #if defined(__AVR__) 
    a = -(a * 1000 * (uint32_t)_range)/(32768);
  #else 
    a = (a * 1000 * (uint32_t)_range)/(32768);
  #endif
   return a;
}
int32_t DFRobot_LIS331HH_SPI::readAccZ(){
  uint8_t reg = 0;

  uint8_t sensorData[2];
  int32_t a = 0;
  readReg(REG_STATUS_REG,&reg,1);
  readReg(REG_OUT_Z_L,&sensorData[0],1);
  readReg(REG_OUT_Z_L+1,&sensorData[1],1);

  a = ((int8_t)sensorData[1])*256+sensorData[0];
  #if defined(__AVR__) 
    a = -(a * 1000 * (uint32_t)_range)/(32768);
  #else 
    a = (a * 1000 * (uint32_t)_range)/(32768);
  #endif
     return a;
}
uint8_t DFRobot_LIS331HH_SPI::readReg(uint8_t reg,void * pBuf ,size_t size){
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;
  size_t count = 0;
  reg = reg | SPI_READ_BIT;
  DBG(reg);
#if (defined NRF5)
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
#else
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
#endif
  digitalWrite(_cs,0);
  _pSpi->transfer(reg);
  while(size--) {
    *_pBuf = SPI.transfer(0x00);
    _pBuf++;
    count++;
  }
  _pSpi->endTransaction();
  digitalWrite(_cs,1);
  return count;
}

uint8_t  DFRobot_LIS331HH_SPI::writeReg(uint8_t reg,const void *pBuf,size_t size){
  if(pBuf == NULL){
	  DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t * _pBuf = (uint8_t *)pBuf;

  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_cs,0);
  _pSpi->transfer(reg);
  while(size--) {
    _pSpi->transfer(*_pBuf);
    _pBuf ++;
  }

  SPI.endTransaction();
  digitalWrite(_cs,1);
  return 1;
}