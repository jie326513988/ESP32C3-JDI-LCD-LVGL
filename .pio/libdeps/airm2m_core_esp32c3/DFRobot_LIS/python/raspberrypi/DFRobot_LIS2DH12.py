# -*- coding:utf-8 -*-
'''!
  @file DFRobot_LIS2DH12.py
  @brief Define the basic structure of class DFRobot_LIS2DH12 
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [tangjie](jie.tang@dfrobot.com)
  @version  V1.0
  @date  2022-1-5
  @url https://github.com/DFRobot/DFRobot_LIS
'''
import time
#from python.raspberrypi.examples.H3LIS200DL.interrupt.interrupt import INT1
import smbus
import spidev 
import numpy as np
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

class DFRobot_LIS2DH12():
  REG_CARD_ID      =  0x0F     #Chip id
  REG_CTRL_REG1    =  0x20     #Control register 1
  REG_CTRL_REG4    =  0x23     #Control register 4
  REG_CTRL_REG2    =  0x21     #Control register 2
  REG_CTRL_REG3    =  0x22     #Control register 3
  REG_CTRL_REG5    =  0x24     #Control register 5
  REG_CTRL_REG6    =  0x25     #Control register 6
  REG_STATUS_REG   =  0x27     #Status register
  REG_OUT_X_L      =  0x28     #The low order of the X-axis acceleration register
  REG_OUT_X_H      =  0x29     #The high point of the X-axis acceleration register
  REG_OUT_Y_L      =  0x2A     #The low order of the Y-axis acceleration register
  REG_OUT_Y_H      =  0x2B     #The high point of the Y-axis acceleration register
  REG_OUT_Z_L      =  0x2C     #The low order of the Z-axis acceleration register
  REG_OUT_Z_H      =  0x2D     #The high point of the Z-axis acceleration register
  REG_INT1_THS     =  0x32     #Interrupt source 1 threshold
  REG_INT2_THS     =  0x36     #Interrupt source 2 threshold
  REG_INT1_CFG     =  0x30     #Interrupt source 1 configuration register
  REG_INT2_CFG     =  0x34     #Interrupt source 2 configuration register
  REG_INT1_SRC     =  0x31     #Interrupt source 1 status register
  REG_INT2_SRC     =  0x35     #Interrupt source 2 status register

  '''!
    Power mode
  '''
  POWERDOWN_0HZ  = 0X00
  LOWPOWER_1Hz   = 0x10
  LOWPOWER_10Hz  = 0x20
  LOWPOWER_25Hz  = 0x30
  LOWPOWER_50Hz  = 0x40
  LOWPOWER_100Hz = 0x50
  LOWPOWER_200Hz = 0x60
  LOWPOWER_400Hz = 0x70

  '''!
    Sensor range selection
  '''
  LIS2DH12_2g = 0x00
  LIS2DH12_4g = 0x10
  LIS2DH12_8g = 0x20
  LIS2DH12_16g = 0x30

  '''!
    Interrupt event
  '''
  X_LOWERTHAN_TH   = 0X01  #The acceleration in the x direction is less than the threshold
  X_HIGHERTHAN_TH  = 0X02  #The acceleration in the x direction is greater than the threshold
  Y_LOWERTHAN_TH   = 0X04  #The acceleration in the y direction is less than the threshold
  Y_HIGHERTHAN_TH  = 0X08  #The acceleration in the y direction is greater than the threshold
  Z_LOWERTHAN_TH   = 0X10  #The acceleration in the z direction is less than the threshold
  Z_HIGHERTHAN_TH  = 0X20  #The acceleration in the z direction is greater than the threshold
  EVENT_ERROR      = 0  # No event

  #Interrupt pin selection
  INT_1 = 0 #int1
  INT_2 = 1 #int2

  def __init__(self,bus,addr):
    self._addr = addr
    self._i2cbus = smbus.SMBus(bus)
    self._mg_scanlevel = 0

  def begin(self):
    '''!
      @brief Initialize the function
      @return true(Succeed)/false(Failed)
    '''
    self._id = self._read_reg(self.REG_CARD_ID,1)
    if(self._id == 0x33):
      self._ret = True
    elif(self._id == 0 or self._id == 0xff):
      print("Communication failure")
      self._ret = False
    else:
      print("the ic is not LIS2DH12")
      self._ret = False
    return self._ret

  def set_range(self, range):
    '''!
      @brief Set the measurement range
      @param range Range(g)
                  LIS2DH12_2g, //2g
                  LIS2DH12_4g, //4g
                  LIS2DH12_8g, //8g
                  LIS2DH12_16g, //16g
    '''
    if(range == self.LIS2DH12_2g):
      self._mg_scanlevel = 16
    elif(range == self.LIS2DH12_4g):
      self._mg_scanlevel = 32
    elif(range == self.LIS2DH12_8g):
      self._mg_scanlevel = 64
    else:
      self._mg_scanlevel = 192
    self._write_reg(self.REG_CTRL_REG4,range)

  def get_id(self):
    '''!
      @brief Get chip id
      @return 8 bit serial number
    '''
    self._id = self._read_reg(self.REG_CARD_ID,1)
    return self._id[0]
  
  def set_acquire_rate(self, rate):
    '''!
      @brief Set data measurement rate
      @param rate rate(HZ)
      @n            POWERDOWN_0HZ 
      @n            LOWPOWER_1Hz 
      @n            LOWPOWER_10Hz 
      @n            LOWPOWER_25Hz 
      @n            LOWPOWER_50Hz 
      @n            LOWPOWER_100Hz
      @n            LOWPOWER_200Hz
      @n            LOWPOWER_400Hz
    '''
    self._reg = 0x0f
    self._reg = (rate + self._reg)
    self._write_reg(self.REG_CTRL_REG1, self._reg)
  
  def set_int1_th(self, threshold):
    '''!
      @brief Set the threshold of interrupt source 1 interrupt
      @param threshold The threshold is within the measurement range(unit:g)
    '''
    self._reg = (threshold * 1024)/self._mg_scanlevel
    self._reg1 = 0x08
    self._reg2 = 0x00
    self._data = 0x40
    self._write_reg(self.REG_CTRL_REG2,self._reg2)
    self._write_reg(self.REG_CTRL_REG3,self._data)
    self._write_reg(self.REG_CTRL_REG5,self._reg1)
    self._write_reg(self.REG_CTRL_REG6,self._reg2)
    self._write_reg(self.REG_INT1_THS,self._reg)

  def set_int2_th(self, threshold):
    '''!
      @brief Set the threshold of interrupt source 1 interrupt
      @param threshold The threshold is within the measurement range(unit:g)
    '''
    self._reg = (threshold * 1024)/self._mg_scanlevel
    self._reg1 = 0x08
    self._reg2 = 0x00
    self._data = 0x40
    self._write_reg(self.REG_CTRL_REG2,self._reg2)
    self._write_reg(self.REG_CTRL_REG3,self._reg2)
    self._write_reg(self.REG_CTRL_REG5,self._reg1)
    self._write_reg(self.REG_CTRL_REG6,self._data)
    self._write_reg(self.REG_INT2_THS,self._reg)

  def enable_int_event(self, source, event):
    '''!
      @brief Enable interrupt
      @param source Interrupt pin selection
      @n        INT_1 = 0,/<int1 >/
      @n        INT_2,/<int2>/
      @param event Interrupt event selection
      @n             X_LOWERTHAN_TH ,/<The acceleration in the x direction is less than the threshold>/
      @n             X_HIGHERTHAN_TH ,/<The acceleration in the x direction is greater than the threshold>/
      @n             Y_LOWERTHAN_TH,/<The acceleration in the y direction is less than the threshold>/
      @n             Y_HIGHERTHAN_TH,/<The acceleration in the y direction is greater than the threshold>/
      @n             Z_LOWERTHAN_TH,/<The acceleration in the z direction is less than the threshold>/
      @n             Z_HIGHERTHAN_TH,/<The acceleration in the z direction is greater than the threshold>/
    '''
    self._data = (0x80 + event)
    if(source == self.INT_1):
      self._write_reg(self.REG_INT1_CFG,self._data)
    else:
      self._write_reg(self.REG_INT2_CFG,self._data)

  def get_int1_event(self, event):
    '''!
      @brief Check whether the interrupt event'event' is generated in interrupt 1
      @param event Interrupt event
      @n             X_LOWERTHAN_TH ,/<The acceleration in the x direction is less than the threshold>/
      @n             X_HIGHERTHAN_TH ,/<The acceleration in the x direction is greater than the threshold>/
      @n             Y_LOWERTHAN_TH,/<The acceleration in the y direction is less than the threshold>/
      @n             Y_HIGHERTHAN_TH,/<The acceleration in the y direction is greater than the threshold>/
      @n             Z_LOWERTHAN_TH,/<The acceleration in the z direction is less than the threshold>/
      @n             Z_HIGHERTHAN_TH,/<The acceleration in the z direction is greater than the threshold>/
      @return true Generated/false Not generated
    '''
    self._ret = False
    self._data = self._read_reg(self.REG_INT1_SRC,1)
    if((self._data[0] & 0x40)):
      if(event == self.X_LOWERTHAN_TH):
        if((self._data[0] & 0x01)== 0):
          self._ret = True
      elif(event == self.X_HIGHERTHAN_TH):
        if((self._data[0] & 0x02)== 0x02):
          self._ret = True
      elif(event == self.Y_LOWERTHAN_TH):
        if((self._data[0] & 0x04)== 0):
          self._ret = True
      elif(event == self.Y_HIGHERTHAN_TH):
        if((self._data[0] & 0x08)== 0x08):
          self._ret = True
      elif(event == self.Z_LOWERTHAN_TH):
        if((self._data[0] & 0x10)== 0):
          self._ret = True
      elif(event == self.Z_HIGHERTHAN_TH):
        if((self._data[0] & 0x20)== 0x20):
          self._ret = True
      else:
        self._ret = False
        
    else:
      self._ret= False

    return self._ret

  def get_int2_event(self, event):
    '''!
      @brief Check whether the interrupt event'event' is generated in interrupt 1
      @param event Interrupt event
      @n             X_LOWERTHAN_TH ,/<The acceleration in the x direction is less than the threshold>/
      @n             X_HIGHERTHAN_TH ,/<The acceleration in the x direction is greater than the threshold>/
      @n             Y_LOWERTHAN_TH,/<The acceleration in the y direction is less than the threshold>/
      @n             Y_HIGHERTHAN_TH,/<The acceleration in the y direction is greater than the threshold>/
      @n             Z_LOWERTHAN_TH,/<The acceleration in the z direction is less than the threshold>/
      @n             Z_HIGHERTHAN_TH,/<The acceleration in the z direction is greater than the threshold>/
      @return true Generated/false Not generated
    '''
    self._ret = False
    self._data =self._read_reg(self.REG_INT2_SRC,1)
    if(self._data[0] & 0x40):
      if(event == self.X_LOWERTHAN_TH):
        if((self._data[0] & 0x01)== 0):
          self._ret = True
      elif(event == self.X_HIGHERTHAN_TH):
        if((self._data[0] & 0x02)== 0x02):
          self._ret = True
      elif(event == self.Y_LOWERTHAN_TH):
        if((self._data[0] & 0x04)== 0):
          self._ret = True
      elif(event == self.Y_HIGHERTHAN_TH):
        if((self._data[0] & 0x08)== 0x08):
          self._ret = True
      elif(event == self.Z_LOWERTHAN_TH):
        if((self._data[0] & 0x10)== 0):
          self._ret = True
      elif(event == self.Z_HIGHERTHAN_TH):
        if((self._data[0] & 0x20)== 0x20):
          self._ret = True
      else:
        self._ret = False
        
    else:
      self._ret= False

    return self._ret


  def read_acc_x(self):
    '''!
      @brief Get the acceleration in the x direction
      @return acceleration from x (unit:g), the mearsurement range is 2g or 16g, set by setRange() function.
    '''
    self._sensor_data = self._read_reg((self.REG_OUT_X_L + 0x80),2)
    return -(np.int8(self._sensor_data[1])* self._mg_scanlevel)

  def read_acc_y(self):
    '''!
      @brief Get the acceleration in the y direction
      @return acceleration from y (unit:g), the mearsurement range is 2g or 16g, set by setRange() function.
    '''
    self._sensor_data = self._read_reg((self.REG_OUT_Y_L + 0x80),2)
    return -(np.int8(self._sensor_data[1]) * self._mg_scanlevel)

  def read_acc_z(self):
    '''!
      @brief Get the acceleration in the z direction
      @return acceleration from z (unit:g), the mearsurement range is 2g or 16g, set by setRange() function.
    '''
    self._sensor_data = self._read_reg((self.REG_OUT_Z_L + 0x80),2)
    return -(np.int8(self._sensor_data[1]) * self._mg_scanlevel)

  def _write_reg(self, reg, data):
    '''!
  		@brief writes data to a register
    	@param reg register address
    	@param data written data
  	'''
    self._i2cbus.write_i2c_block_data(self._addr,reg,[data])
        
  def _read_reg(self, reg ,length):
    '''!
      @brief read the data from the register
      @param reg register address
      @param value read data
    '''
    try:
      rslt = self._i2cbus.read_i2c_block_data(self._addr ,reg , length)
    except:
      rslt = -1
    return rslt

