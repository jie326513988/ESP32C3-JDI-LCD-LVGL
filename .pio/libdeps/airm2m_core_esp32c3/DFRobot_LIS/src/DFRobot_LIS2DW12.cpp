/*!
 * @file DFRobot_LIS2DW12.cpp
 * @brief The realization of the class DFRobot_LIS2DW12
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [fengli](li.feng@dfrobot.com)
 * @version  V1.0
 * @date  2020-12-23
 * @url https://github.com/DFRobot/DFRobot_LIS
 */

#include <DFRobot_LIS2DW12.h>
DFRobot_LIS2DW12::DFRobot_LIS2DW12()
{
}

bool DFRobot_LIS2DW12::begin(void)
{
  uint8_t identifier = 0;
  readReg(REG_CARD_ID, &identifier, 1);
  DBG(identifier);
  if (identifier == 0x44)
  {
    return true;
  }
  else
  {
    return false;
  }
}

uint8_t DFRobot_LIS2DW12::getID()
{
  uint8_t identifier;
  readReg(REG_CARD_ID, &identifier, 1);
  return identifier;
}
void DFRobot_LIS2DW12::softReset()
{
  uint8_t value;
  readReg(REG_CTRL_REG2, &value, 1);
  value = value | (1 << 6);
  DBG(value);
  writeReg(REG_CTRL_REG2, &value, 1);
}
void DFRobot_LIS2DW12::continRefresh(bool enable)
{

  uint8_t value;
  readReg(REG_CTRL_REG2, &value, 1);
  if (enable == true)
  {
    value = value | (1 << 3);
  }
  else
  {
    value = value & (~(1 << 3));
  }
  DBG(value);
  writeReg(REG_CTRL_REG2, &value, 1);
}

void DFRobot_LIS2DW12::setFilterPath(ePath_t path)
{
  uint8_t value;
  readReg(REG_CTRL_REG6, &value, 1);
  uint8_t enable = (path & 0x10U) ? 1 : 0;
  value = value & (~(3 << 2));
  value = value | enable << 3;
  DBG(value);
  writeReg(REG_CTRL_REG6, &value, 1);

  readReg(REG_CTRL_REG7, &value, 1);

  enable = (path & 0x01U) ? 1 : 0;
  value = value & (~(1 << 4));
  value = value | enable << 4;
  DBG(value);
  writeReg(REG_CTRL_REG7, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setFilterBandwidth(eBWFilter_t bw)
{

  uint8_t value;
  readReg(REG_CTRL_REG6, &value, 1);
  value = value & (~(3 << 6));
  value = value | (bw << 6);
  DBG(value);
  writeReg(REG_CTRL_REG6, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setPowerMode(ePowerMode_t mode)
{

  uint8_t value;
  readReg(REG_CTRL_REG1, &value, 1);
  value = value & (~0x0f);
  value = value | (mode & 0xF);
  writeReg(REG_CTRL_REG1, &value, 1);
  DBG(value);

  readReg(REG_CTRL_REG6, &value, 1);
  uint8_t enable = mode >> 4;
  value = value & (~(1 << 2));
  value = value | enable << 2;
  DBG(value);
  writeReg(REG_CTRL_REG6, &value, 1);
  return;
}
void DFRobot_LIS2DW12::setDataRate(eRate_t rate)
{

  uint8_t value;
  readReg(REG_CTRL_REG1, &value, 1);
  value = value & (~(0xf << 4));
  value = value | rate << 4;
  DBG(value);
  writeReg(REG_CTRL_REG1, &value, 1);

  readReg(REG_CTRL_REG3, &value, 1);
  uint8_t enable = (rate & 0x30) >> 4;
  value = value & (~3);
  value = value | enable;
  DBG(value);
  writeReg(REG_CTRL_REG3, &value, 1);
  return;
}
void DFRobot_LIS2DW12::demandData()
{
  uint8_t value;
  readReg(REG_CTRL_REG3, &value, 1);
  value = value | 1;
  DBG(value);
  writeReg(REG_CTRL_REG3, &value, 1);
}
void DFRobot_LIS2DW12::setRange(eRange_t range)
{
  uint8_t value = 0;
  readReg(REG_CTRL_REG6, &value, 1);
  _range1 = range;
  value = value & (~(3 << 4));
  switch (range)
  {
  case e2_g:
  {
    _range = 0.061f;
    value = value | 0;
    break;
  }
  case e4_g:
  {
    _range = 0.122f;
    value = value | (1 << 4);
    break;
  }
  case e8_g:
  {
    _range = 0.244f;
    value = value | (2 << 4);
    break;
  }
  case e16_g:
  {
    _range = 0.488f;
    value = value | (3 << 4);
    break;
  }
  }
  DBG(value);
  writeReg(REG_CTRL_REG6, &value, 1);
}

void DFRobot_LIS2DW12::setFreeFallDur(uint8_t dur)
{
  uint8_t value1 = 0;
  uint8_t value2 = 0;
  readReg(REG_WAKE_UP_DUR, &value1, 1);
  readReg(REG_FREE_FALL, &value2, 1);
  value1 = value1 & (~0x80);
  value2 = value2 & (~0xf8);
  value2 = value2 | (dur << 3);
  DBG(value1);
  writeReg(REG_WAKE_UP_DUR, &value1, 1);
  DBG(value2);
  writeReg(REG_FREE_FALL, &value2, 1);
  setFfThreshold(3);
}

void DFRobot_LIS2DW12::setFfThreshold(uint8_t th)
{

  uint8_t value;
  readReg(REG_FREE_FALL, &value, 1);
  value = value & (~7);
  value = value | (th & 0x7);
  DBG(value);
  writeReg(REG_FREE_FALL, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setInt1Event(eInt1Event_t event)
{

  uint8_t value1 = 0;
  uint8_t value2 = 0;
  uint8_t value3 = 0;

  readReg(REG_CTRL_REG4, &value1, 1);
  readReg(REG_CTRL_REG5, &value2, 1);
  readReg(REG_CTRL_REG7, &value3, 1);

  value3 = value3 & (~0x20);
  if (((value2 & 0x80) | (value2 & 0x40) | (value1 & 0x08) | (value1 & 0x10) | (value1 & 0x20) | (value1 & 0x40) | (value1 & 0x80)) != 0)
  {
    value3 = value3 | 0x20;
  }
  value3 = value3 | 0x20;

  value1 = value1 | event;
  DBG(value1);
  DBG(value3);
  writeReg(REG_CTRL_REG4, &value1, 1);
  writeReg(REG_CTRL_REG7, &value3, 1);

  if (event == eFreeFall)
  {
    // lockInterrupt(true);
  }
}
void DFRobot_LIS2DW12::setWakeUpDur(uint8_t dur)
{

  uint8_t value;

  readReg(REG_WAKE_UP_DUR, &value, 1);
  value = value & (~0x60);
  value = value | ((dur << 5) & 0x60);

  DBG(value);
  writeReg(REG_WAKE_UP_DUR, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setActSleepDur(uint8_t dur)
{
  uint8_t value;
  readReg(REG_WAKE_UP_DUR, &value, 1);
  dur = dur & 0X0F;
  value = value & (~0X0F);
  value = value | dur;

  DBG(value);
  writeReg(REG_WAKE_UP_DUR, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setActMode(eActDetect_t mode)
{
  uint8_t value1;
  uint8_t value2;

  readReg(REG_WAKE_UP_THS, &value1, 1);
  readReg(REG_WAKE_UP_DUR, &value2, 1);
  value1 = value1 & (~(1 << 6));
  value2 = value2 & (~(1 << 4));
  value1 = value1 | (mode & 0x01) << 6;
  value2 = value2 | ((mode & 0x02) >> 1) << 4;
  DBG(value1);
  DBG(value2);
  writeReg(REG_WAKE_UP_THS, &value1, 1);
  writeReg(REG_WAKE_UP_DUR, &value2, 1);
  return;
}

void DFRobot_LIS2DW12::setWakeUpThreshold(float th)
{
  uint8_t value;
  uint8_t th1 = (th / (_range1)) * 64;

  DBG(th1);
  readReg(REG_WAKE_UP_THS, &value, 1);
  value = value & (~0x3f);
  value = value | (th1 & 0x3f);
  DBG(value);
  writeReg(REG_WAKE_UP_THS, &value, 1);
  return;
}

void DFRobot_LIS2DW12::lockInterrupt(bool enable)
{

  uint8_t value;
  readReg(REG_CTRL_REG3, &value, 1);
  value = value & (~0x10);
  value = value | (enable << 4);
  writeReg(REG_CTRL_REG3, &value, 1);
  return;
}
void DFRobot_LIS2DW12::enableTapDetectionOnZ(bool enable)
{
  uint8_t value;
  readReg(REG_TAP_THS_Z, &value, 1);
  value = value & (~(1 << 5));
  value = value | (enable << 5);
  DBG(value);
  writeReg(REG_TAP_THS_Z, &value, 1);
  return;
}

void DFRobot_LIS2DW12::enableTapDetectionOnY(bool enable)
{
  uint8_t value;
  readReg(REG_TAP_THS_Z, &value, 1);
  value = value & (~(1 << 6));
  value = value | (enable << 6);
  DBG(value);
  writeReg(REG_TAP_THS_Z, &value, 1);
  return;
}
void DFRobot_LIS2DW12::enableTapDetectionOnX(bool enable)
{

  uint8_t value;
  readReg(REG_TAP_THS_Z, &value, 1);
  value = value & (~(1 << 7));
  value = value | (enable << 7);
  DBG(value);
  writeReg(REG_TAP_THS_Z, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setTapThresholdOnX(float th)
{
  uint8_t value;
  uint8_t th1 = (th / _range1) * 32;

  readReg(REG_TAP_THS_X, &value, 1);
  value = value & (~0x1f);
  value = value | (th1 & 0x1f);
  DBG(value);
  writeReg(REG_TAP_THS_X, &value, 1);
  return;
}
void DFRobot_LIS2DW12::setTapThresholdOnY(float th)
{
  uint8_t value;
  uint8_t th1 = (th / _range1) * 32;
  readReg(REG_TAP_THS_Y, &value, 1);
  value = value & (~0x1f);
  value = value | (th1 & 0x1f);
  DBG(value);
  writeReg(REG_TAP_THS_Y, &value, 1);
  return;
}
void DFRobot_LIS2DW12::setTapThresholdOnZ(float th)
{
  uint8_t value;
  uint8_t th1 = (th / _range1) * 32;
  readReg(REG_TAP_THS_Z, &value, 1);
  value = value & (~0x1f);
  value = value | (th1 & 0x1f);
  DBG(value);
  writeReg(REG_TAP_THS_Z, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setTapDur(uint8_t dur)
{
  uint8_t value;
  readReg(REG_INT_DUR, &value, 1);
  value = value & (~0xf0);
  value = value | (dur << 4);
  DBG(value);
  writeReg(REG_INT_DUR, &value, 1);

  setTapQuiet(2);
  setTapShock(2);
  return;
}
void DFRobot_LIS2DW12::setTapQuiet(uint8_t quiet)
{
  uint8_t value;
  readReg(REG_INT_DUR, &value, 1);
  value = value & (~0xC);
  quiet = quiet & 0x3;
  value = value | (quiet << 2);
  DBG(value);
  writeReg(REG_INT_DUR, &value, 1);
  return;
}
void DFRobot_LIS2DW12::setTapShock(uint8_t shock)
{
  uint8_t value;
  readReg(REG_INT_DUR, &value, 1);
  value = value & (~0x3);
  shock = shock & 0x3;
  value = value | (shock);
  DBG(value);
  writeReg(REG_INT_DUR, &value, 1);
  return;
}

void DFRobot_LIS2DW12::setTapMode(eTapMode_t mode)
{

  uint8_t value;

  readReg(REG_WAKE_UP_THS, &value, 1);
  value = value & (~0x80);
  value = value | (mode << 7);
  DBG(value);
  writeReg(REG_WAKE_UP_THS, &value, 1);
  return;
}
void DFRobot_LIS2DW12::set6DThreshold(e6DTh_t degree)
{

  uint8_t value;
  readReg(REG_TAP_THS_X, &value, 1);
  value = value & (~0x60);
  value = value | degree << 5;
  DBG(value);
  writeReg(REG_TAP_THS_X, &value, 1);
  set6dFeedData(1);
  return;
}

void DFRobot_LIS2DW12::setInt2Event(eInt2Event_t event)
{
  uint8_t value1 = 0;
  uint8_t value2 = 0;
  uint8_t value3 = 0;
  readReg(REG_CTRL_REG4, &value1, 1); // 0X23
  readReg(REG_CTRL_REG5, &value2, 1); // 0X24
  readReg(REG_CTRL_REG7, &value3, 1); // 0X3F

  value3 = value3 & (~0x20);
  if (((value2 & 0x80) | (value2 & 0x40) | (value1 & 0x08) | (value1 & 0x10) | (value1 & 0x20) | (value1 & 0x40) | (value1 & 0x80)) != 0)
  {
    value3 = value3 | 0x20;
  }
  value3 = value3 | 0x20;

  value2 = value2 | event;
  DBG(value1);
  DBG(value3);
  Serial.println(value1, BIN);
  Serial.println(value2, BIN);
  Serial.println(value3, BIN);
  writeReg(REG_CTRL_REG5, &value2, 1); // 0X24
  writeReg(REG_CTRL_REG7, &value3, 1); // 0X3F
  //lockInterrupt(0);
}
/*LPF2 on 6D function selection. */
void DFRobot_LIS2DW12::set6dFeedData(uint8_t data)
{
  uint8_t value;
  readReg(REG_CTRL_REG7, &value, 1);
  value = value & (~1);
  value = value | data;
  DBG(value);
  writeReg(REG_CTRL_REG7, &value, 1);
  return;
}

int16_t DFRobot_LIS2DW12::readAccX()
{
  uint8_t sensorData[2];
  readReg(REG_OUT_X_L, sensorData, 2);
  int16_t a = ((int16_t)sensorData[1]) * 256 + (int16_t)sensorData[0];
  return a * _range;
}
int16_t DFRobot_LIS2DW12::readAccY()
{

  uint8_t sensorData[2];
  readReg(REG_OUT_Y_L, sensorData, 2);
  int16_t a = ((int16_t)sensorData[1]) * 256 + (int16_t)sensorData[0];
  return a * _range;
}

int16_t DFRobot_LIS2DW12::readAccZ()
{
  uint8_t sensorData[2];
  readReg(REG_OUT_Z_L, sensorData, 2);
  int16_t a = ((int16_t)sensorData[1]) * 256 + (int16_t)sensorData[0];
  DBG(_range);
  return a * _range;
}
bool DFRobot_LIS2DW12::actDetected()
{
  uint8_t value;
  readReg(REG_WAKE_UP_SRC, &value, 1);
  if ((value & 0x08) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool DFRobot_LIS2DW12::freeFallDetected()
{
  uint8_t value;
  readReg(REG_WAKE_UP_SRC, &value, 1);
  if ((value & 0x20) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool DFRobot_LIS2DW12::oriChangeDetected()
{
  uint8_t value;
  readReg(REG_SIXD_SRC, &value, 1);
  if ((value & 0x40) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

DFRobot_LIS2DW12::eOrient_t DFRobot_LIS2DW12::getOrientation()
{
  uint8_t value;
  readReg(REG_SIXD_SRC, &value, 1);
  if ((value & 0x01) > 0)
  {
    return eXDown;
  }
  else if ((value & 0x2) > 0)
  {
    return eXUp;
  }
  else if ((value & 0x4) > 0)
  {
    return eYDown;
  }
  else if ((value & 0x8) > 0)
  {
    return eYUp;
  }
  else if ((value & 0x10) > 0)
  {
    return eZDown;
  }
  else if ((value & 0x20) > 0)
  {
    return eZUp;
  }
}
DFRobot_LIS2DW12::eTap_t DFRobot_LIS2DW12::tapDetect()
{
  uint8_t value;
  readReg(REG_TAP_SRC, &value, 1);
  if ((value & 0x20) > 0)
  {
    return eSTap;
  }
  else if ((value & 0x10) > 0)
  {
    return eDTap;
  }
  else
  {
    return eNoTap;
  }
}
DFRobot_LIS2DW12::eTapDir_t DFRobot_LIS2DW12::getTapDirection()
{
  uint8_t value;
  readReg(REG_TAP_SRC, &value, 1);
  uint8_t positive = value & 0x08;

  if (((value & 0x04) != 0) && (positive > 0))
  {
    return eDirXUp;
  }
  else if (((value & 0x4) != 0) && (positive == 0))
  {
    return eDirXDown;
  }
  else if (((value & 0x2) != 0) && (positive > 0))
  {
    return eDirYUp;
  }
  else if (((value & 0x2) != 0) && (positive == 0))
  {
    return eDirYDown;
  }
  else if (((value & 0x1) != 0) && (positive > 0))
  {
    return eDirZUp;
  }
  else if (((value & 0x1) != 0) && (positive == 0))
  {
    return eDirZDown;
  }
  return eDirNone;
}
DFRobot_LIS2DW12::eWakeUpDir_t DFRobot_LIS2DW12::getWakeUpDir()
{
  uint8_t value;
  readReg(REG_WAKE_UP_SRC, &value, 1);
  if ((value & 0x1) > 0)
  {
    return eDirZ;
  }
  else if ((value & 0x2) > 0)
  {
    return eDirY;
  }
  else if ((value & 0x4) > 0)
  {
    return eDirX;
  }
  else
  {
    return eDirError;
  }
}

DFRobot_IIS2DLPC_I2C::DFRobot_IIS2DLPC_I2C(TwoWire *pWire, uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;
}

bool DFRobot_IIS2DLPC_I2C::begin(void)
{
  _pWire->begin();

  uint8_t regData = 0x01;
  // writeReg(IIS2DLPC_REG_CTRL_REG2,&regData,1);
  return DFRobot_LIS2DW12::begin();
}

uint8_t DFRobot_IIS2DLPC_I2C::writeReg(uint8_t reg, const void *pBuf, size_t size)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  for (uint16_t i = 0; i < size; i++)
  {
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
}

uint8_t DFRobot_IIS2DLPC_I2C::readReg(uint8_t reg, uint8_t *pBuf, size_t size)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if (_pWire->endTransmission() != 0)
  {
    return 0;
  }
  // Serial.println("a----------------");
  _pWire->requestFrom(_deviceAddr, (uint8_t)size);
  for (uint16_t i = 0; i < size; i++)
  {
    _pBuf[i] = _pWire->read();
  }
  return size;
}
DFRobot_IIS2DLPC_SPI::DFRobot_IIS2DLPC_SPI(uint8_t cs, SPIClass *pSpi)
{
  _pSpi = pSpi;
  _cs = cs;
}

bool DFRobot_IIS2DLPC_SPI::begin(void)
{

  _pSpi->begin();
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, 1);
  return DFRobot_LIS2DW12::begin();
}
uint8_t DFRobot_IIS2DLPC_SPI::readReg(uint8_t reg, uint8_t *pBuf, size_t size)
{

  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  size_t count = 0;

#if (defined NRF5)
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
#else
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
#endif
  digitalWrite(_cs, 0);
  _pSpi->transfer(reg | SPI_READ_BIT);
  while (size--)
  {
    *_pBuf = SPI.transfer(0x00);
    _pBuf++;
    count++;
  }
  _pSpi->endTransaction();
  digitalWrite(_cs, 1);
  return count;
}

uint8_t DFRobot_IIS2DLPC_SPI::writeReg(uint8_t reg, const void *pBuf, size_t size)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_cs, 0);
  _pSpi->transfer(reg);

  while (size--)
  {
    _pSpi->transfer(*_pBuf);
    _pBuf++;
  }
  SPI.endTransaction();
  digitalWrite(_cs, 1);
}
DFRobot_LIS2DW12_I2C::DFRobot_LIS2DW12_I2C(TwoWire *pWire, uint8_t addr)
{
  _deviceAddr = addr;
  _pWire = pWire;
}

bool DFRobot_LIS2DW12_I2C::begin(void)
{
  //_pWire->begin();

  // writeReg(IIS2DLPC_REG_CTRL_REG2,&regData,1);
  return DFRobot_LIS2DW12::begin();
}

uint8_t DFRobot_LIS2DW12_I2C::writeReg(uint8_t reg, const void *pBuf, size_t size)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);

  for (uint16_t i = 0; i < size; i++)
  {
    _pWire->write(_pBuf[i]);
  }
  _pWire->endTransmission();
  return 1;
}

uint8_t DFRobot_LIS2DW12_I2C::readReg(uint8_t reg, uint8_t *pBuf, size_t size)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pWire->beginTransmission(_deviceAddr);
  _pWire->write(&reg, 1);
  if (_pWire->endTransmission() != 0)
  {
    return 0;
  }
  // Serial.println("a----------------");
  _pWire->requestFrom(_deviceAddr, (uint8_t)size);
  for (uint16_t i = 0; i < size; i++)
  {

    _pBuf[i] = _pWire->read();
    // Serial.println(_pBuf[i],HEX);
  }
  return size;
}
DFRobot_LIS2DW12_SPI::DFRobot_LIS2DW12_SPI(uint8_t cs, SPIClass *pSpi)
{
  _pSpi = pSpi;
  _cs = cs;
}

bool DFRobot_LIS2DW12_SPI::begin(void)
{

  _pSpi->begin();
  uint8_t regData = 0x2;
  pinMode(_cs, OUTPUT);
  digitalWrite(_cs, 1);
  // writeReg(REG_CTRL_REG2,&regData,1);
  return DFRobot_LIS2DW12::begin();
}
uint8_t DFRobot_LIS2DW12_SPI::readReg(uint8_t reg, uint8_t *pBuf, size_t size)
{

  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  uint8_t *_pBuf = (uint8_t *)pBuf;
  size_t count = 0;

#if (defined NRF5)
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));
#else
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
#endif
  digitalWrite(_cs, 0);
  _pSpi->transfer(reg | SPI_READ_BIT);
  while (size--)
  {
    *_pBuf = SPI.transfer(0x00);
    // Serial.println(*_pBuf);
    _pBuf++;
    count++;
  }
  _pSpi->endTransaction();
  digitalWrite(_cs, 1);
  return count;
}

uint8_t DFRobot_LIS2DW12_SPI::writeReg(uint8_t reg, const void *pBuf, size_t size)
{
  if (pBuf == NULL)
  {
    DBG("pBuf ERROR!! : null pointer");
  }
  delay(1);
  uint8_t *_pBuf = (uint8_t *)pBuf;
  _pSpi->beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(_cs, 0);
  _pSpi->transfer(reg);

  while (size--)
  {
    _pSpi->transfer(*_pBuf);
    _pBuf++;
  }
  SPI.endTransaction();
  digitalWrite(_cs, 1);
}
