# -*- coding: utf-8 -*
'''! 
  @file DFRobot_LIS.py
  @brief Define the basic structure of class DFRobot_LIS 
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2021-1-30
  @url https://github.com/DFRobot/DFRobot_LIS
'''
import time
import smbus
import spidev 
import numpy as np
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
H3LIS200DL                = 0x32  
LIS331HH                  = 0x32  
               
class DFRobot_LIS(object):
  REG_CARD_ID    = 0x0F       #Chip id
  REG_CTRL_REG1  = 0x20       #Control register 1
  REG_CTRL_REG4  = 0x23       #Control register 4
  REG_CTRL_REG2  = 0x21       #Control register 2
  REG_CTRL_REG3  = 0x22       #Control register 3
  REG_CTRL_REG5  = 0x24       #Control register 5
  REG_CTRL_REG6  = 0x25       #Control register 6
  REG_STATUS_REG = 0x27       #Status register
  REG_OUT_X_L    = 0x28       #The low order of the X-axis acceleration register
  REG_OUT_X_H    = 0x29       #The high point of the X-axis acceleration register
  REG_OUT_Y_L    = 0x2A       #The low order of the Y-axis acceleration register
  REG_OUT_Y_H    = 0x2B       #The high point of the Y-axis acceleration register
  REG_OUT_Z_L    = 0x2C       #The low order of the Z-axis acceleration register
  REG_OUT_Z_H    = 0x2D       #The high point of the Z-axis acceleration register
  REG_INT1_THS   = 0x32       #Interrupt source 1 threshold
  REG_INT2_THS   = 0x36       #Interrupt source 2 threshold
  REG_INT1_CFG   = 0x30       #Interrupt source 1 configuration register
  REG_INT2_CFG   = 0x34       #Interrupt source 2 configuration register
  REG_INT1_SRC   = 0x31       #Interrupt source 1 status register
  REG_INT2_SRC   = 0x35       #Interrupt source 2 status register
  SPI_READ_BIT   = 0X80       # bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) from the device is read.
  ENABLE_FILTER  = 0X10       #Enable filter
  __reset = 0
  
  '''!
    Power mode selection, determine the frequency of data collection
    Represents the number of data collected per second
  '''
  POWERDOWN_0HZ = 0
  LOWPOWER_HALFHZ = 0X40 
  LOWPOWER_1HZ = 0X60
  LOWPOWER_2HZ = 0X80
  LOWPOWER_5HZ = 0XA0
  LOWPOWER_10HZ = 0XC0
  NORMAL_50HZ = 0X20
  NORMAL_100HZ = 0X28
  NORMAL_400HZ = 0X30
  NORMAL_1000HZ = 0X38
  
  '''!
    Sensor range selection
  '''
  H3LIS200DL_100G = 100 #±100G
  H3LIS200DL_200G = 200 #±200G

  LIS331HH_6G      = 6   #±6G
  LIS331HH_12G     = 12  #±12G
  LIS331HH_24G     = 24  #±24G

  '''!
  # @n                          High-pass filter cut-off frequency configuration
  # @n|--------------------------------------------------------------------------------------------------------|
  # @n|                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
  # @n|   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
  # @n|--------------------------------------------------------------------------------------------------------|
  # @n|  eCutoffMode1  |     1           |         2            |            8         |             20        |
  # @n|--------------------------------------------------------------------------------------------------------|
  # @n|  eCutoffMode2  |    0.5          |         1            |            4         |             10        |
  # @n|--------------------------------------------------------------------------------------------------------|
  # @n|  eCutoffMode3  |    0.25         |         0.5          |            2         |             5         |
  # @n|--------------------------------------------------------------------------------------------------------|
  # @n|  eCutoffMode4  |    0.125        |         0.25         |            1         |             2.5       |
  # @n|--------------------------------------------------------------------------------------------------------|
  '''
  CUTOFF_MODE1 = 0
  CUTOFF_MODE2 = 1
  CUTOFF_MODE3 = 2
  CUTOFF_MODE4 = 3
  SHUTDOWN     = 4
  
  '''!
    Interrupt event
  '''
  X_LOWERTHAN_TH   = 0X1  #The acceleration in the x direction is less than the threshold
  X_HIGHERTHAN_TH  = 0X2  #The acceleration in the x direction is greater than the threshold
  Y_LOWERTHAN_TH   = 0X4  #The acceleration in the y direction is less than the threshold
  Y_HIGHERTHAN_TH  = 0X8  #The acceleration in the y direction is greater than the threshold
  Z_LOWERTHAN_TH   = 0X10  #The acceleration in the z direction is less than the threshold
  Z_HIGHERTHAN_TH  = 0X20  #The acceleration in the z direction is greater than the threshold
  EVENT_ERROR      = 0  # No event

  #Interrupt pin selection
  INT_1 = 0 #int1
  INT_2 = 1 #int2
  
  def __init__(self):
    __reset = 1

  
  def begin(self):
    '''!
      @brief Initialize the function
      @return return True(Succeed)/False(Failed)
    '''
    identifier = self.read_reg(self.REG_CARD_ID)
    if identifier == H3LIS200DL or identifier == LIS331HH:
      return True
    else:
      return False
      
  
  def get_id(self):
    '''!
      @brief Get chip id
      @return the 8 bit serial number
    '''
    identifier = self.read_reg(self.REG_CARD_ID)
    return identifier

  
  def set_acquire_rate(self, rate): 
    '''!
      @brief Set data measurement rate
      @param rate rate(HZ)
      @n     POWERDOWN_0HZ = 0
      @n     LOWPOWER_HALFHZ = 0X40 
      @n     LOWPOWER_1HZ = 0X60
      @n     LOWPOWER_2HZ = 0X80
      @n     LOWPOWER_5HZ = 0XA0
      @n     LOWPOWER_10HZ = 0XC0
      @n     NORMAL_50HZ = 0X20
      @n     NORMAL_100HZ = 0X28
      @n     NORMAL_400HZ = 0X30
      @n     NORMAL_1000HZ = 0X38
    '''   
    value = self.read_reg(self.REG_CTRL_REG1)
    value = value & (~(0x7 << 5))
    value = value & (~(0x3 << 3))
    value = value | rate
    self.write_reg(self.REG_CTRL_REG1,value)

  
  def set_int1_th(self,threshold):
    '''!
      @brief Set the threshold of interrupt source 1 interrupt
      @param threshold Threshold(g)
    '''
    value = (threshold * 128)/_range
    self.write_reg(self.REG_INT1_THS,value)

  
  def set_int2_th(self,threshold):
    '''!
      @brief Set interrupt source 2 interrupt generation threshold
      @param threshold Threshold(g)
    '''
    value = (threshold * 128)/_range
    self.write_reg(self.REG_INT2_THS,value)
  
  
  def enable_int_event(self,source,event):
    '''!
      @brief Enable interrupt
      @param source Interrupt pin selection
      @n       INT_1 = 0,/<int pad 1 >/
      @n       INT_2,/<int pad 2>/
      @param event Interrupt event selection
      @n       X_LOWERTHAN_TH     = 0X1  #The acceleration in the x direction is less than the threshold
      @n       X_HIGHERTHAN_TH  = 0X2  #The acceleration in the x direction is greater than the threshold
      @n       Y_LOWERTHAN_TH     = 0X4  #The acceleration in the y direction is less than the threshold
      @n       Y_HIGHERTHAN_TH  = 0X8  #The acceleration in the y direction is greater than the threshold
      @n       Z_LOWERTHAN_TH     = 0X10  #The acceleration in the z direction is less than the threshold
      @n       Z_HIGHERTHAN_TH  = 0X20  #The acceleration in the z direction is greater than the threshold
      @n       EVENT_ERROR      = 0  # No event
    '''
    value = 0    
    if source == self.INT_1:
      value = self.read_reg(self.REG_INT1_CFG)
    else:
      value = self.read_reg(self.REG_INT2_CFG)
    if self.__reset == 1:
       value = 0
       self.__reset = 0
    value = value | event
    #print(value)
    if source == self.INT_1:
      self.write_reg(self.REG_INT1_CFG,value)
    else:
      self.write_reg(self.REG_INT2_CFG,value)

  
  def get_int1_event(self,event):
    '''!
      @brief Check whether the interrupt event'event' is generated in interrupt 1
      @param event:Interrupt event
      @n       X_LOWERTHAN_TH     = 0X1  #The acceleration in the x direction is less than the threshold
      @n       X_HIGHERTHAN_TH  = 0X2  #The acceleration in the x direction is greater than the threshold
      @n       Y_LOWERTHAN_TH     = 0X4  #The acceleration in the y direction is less than the threshold
      @n       Y_HIGHERTHAN_TH  = 0X8  #The acceleration in the y direction is greater than the threshold
      @n       Z_LOWERTHAN_TH     = 0X10  #The acceleration in the z direction is less than the threshold
      @n       Z_HIGHERTHAN_TH  = 0X20  #The acceleration in the z direction is greater than the threshold
      @n       EVENT_ERROR      = 0  # No event
      @return true This event generated/false This event not generated
    '''
    value = self.read_reg(self.REG_INT1_SRC)
    if (value & event) >= 1:
         return True
    else:
         return False
         
  
  def get_int2_event(self,event):
    '''!
      @brief Check whether the interrupt event'event' is generated in interrupt 2
      @param event:Interrupt event
      @n       X_LOWERTHAN_TH     = 0X1  #The acceleration in the x direction is less than the threshold
      @n       X_HIGHERTHAN_TH  = 0X2  #The acceleration in the x direction is greater than the threshold
      @n       Y_LOWERTHAN_TH     = 0X4  #The acceleration in the y direction is less than the threshold
      @n       Y_HIGHERTHAN_TH  = 0X8  #The acceleration in the y direction is greater than the threshold
      @n       Z_LOWERTHAN_TH     = 0X10  #The acceleration in the z direction is less than the threshold
      @n       Z_HIGHERTHAN_TH  = 0X20  #The acceleration in the z direction is greater than the threshold
      @n       EVENT_ERROR      = 0  # No event
      @return true This event generated/false This event not generated
    '''
    value = self.read_reg(self.REG_INT2_SRC)
    if (value & event) >= 1:
         return True
    else:
         return False
  
  def enable_sleep(self, enable):
    '''!
      @brief Enable sleep wake function
      @param enable:True(enable)/False(disable)
    '''
    value = 0
    if enable == True:
      value = 3
    self.write_reg(self.REG_CTRL_REG5,value)
    return 0

  
  def set_filter_mode(self,mode):
    '''!
      @brief Set data filtering mode
      @param mode:Four modes
      @n          CUTOFF_MODE1 = 0
      @n          CUTOFF_MODE2 = 1
      @n          CUTOFF_MODE3 = 2
      @n          CUTOFF_MODE4 = 3
      @n                        High-pass filter cut-off frequency configuration
      @n|--------------------------------------------------------------------------------------------------------|
      @n|                |    ft [Hz]      |        ft [Hz]       |       ft [Hz]        |        ft [Hz]        |
      @n|   mode         |Data rate = 50 Hz|   Data rate = 100 Hz |  Data rate = 400 Hz  |   Data rate = 1000 Hz |
      @n|--------------------------------------------------------------------------------------------------------|
      @n|  CUTOFF_MODE1  |     1           |         2            |            8         |             20        |
      @n|--------------------------------------------------------------------------------------------------------|
      @n|  CUTOFF_MODE2  |    0.5          |         1            |            4         |             10        |
      @n|--------------------------------------------------------------------------------------------------------|
      @n|  CUTOFF_MODE3  |    0.25         |         0.5          |            2         |             5         |
      @n|--------------------------------------------------------------------------------------------------------|
      @n|  CUTOFF_MODE4  |    0.125        |         0.25         |            1         |             2.5       |
      @n|--------------------------------------------------------------------------------------------------------|
    '''
    value = self.read_reg(self.REG_CTRL_REG2)
    if mode == self.SHUTDOWN:
      value = value & (~ENABLE_FILTER)
    else:
      value = value | ENABLE_FILTER
    value = value & (~3)
    value = value | mode
    self.write_reg(self.REG_CTRL_REG2,value)
  

class DFRobot_H3LIS200DL_I2C(DFRobot_LIS): 
  def __init__(self ,bus ,addr):
    self.__addr = addr
    super(DFRobot_H3LIS200DL_I2C, self).__init__()
    self.i2cbus = smbus.SMBus(bus)
    
  
  def set_range(self,range_r):
    '''!
      @brief Set the measurement range
      @param range:Range(g)
      @n           H3LIS200DL_100G = 100   #±100g
      @n           H3LIS200DL_200G = 200   #±200g
    '''
    global _range 
    value = self.read_reg(self.REG_CTRL_REG4)
    _range = range_r
    if range_r == self.H3LIS200DL_100G:
     value = value & (~0x10)
    else:
     value = value | 0x10

  
  def read_acce_xyz(self):
    '''!
      @brief Get the acceleration in the three directions of xyz
      @return Three-axis acceleration(g), the measurement range is ±100g or ±200g, set by the set_range() function
    '''
    global _range 
    value = self.read_reg(self.REG_STATUS_REG)
    data = [0,0,0,0,0,0,0]
    x = 0
    y = 0
    z = 0
    if(value & 0x01) == 1:
      base = self.REG_OUT_X_L
      for i in range(0,6):
        data[i] = self.read_reg(base+i)
      for i in range(0,6):
        data[i] = np.int8(data[i])
      x = (data[1]*_range)/128
      y = (data[3]*_range)/128
      z = (data[5]*_range)/128
    return x,y,z

  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param data written data
    '''
    self.i2cbus.write_i2c_block_data(self.__addr ,reg,[data])
        
  
  def read_reg(self, reg):
    '''!
      @brief read the data from the register
      @param reg register address
      @rerun read data
    '''
    self.i2cbus.write_byte(self.__addr,reg)
    time.sleep(0.01)
    rslt = self.i2cbus.read_byte(self.__addr)
    return rslt

class DFRobot_H3LIS200DL_SPI(DFRobot_LIS): 
  def __init__(self ,cs, bus = 0, dev = 0,speed = 100000):
    super(DFRobot_H3LIS200DL_SPI, self).__init__()
    self.__cs = cs
    GPIO.setup(self.__cs, GPIO.OUT)
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi = spidev.SpiDev()
    self.__spi.open(bus, dev)
    self.__spi.no_cs = True
    self.__spi.max_speed_hz = speed
    
  
  def set_range(self,range_r):
    '''!
      @brief Set the measurement range
      @param range:Range(g)
      @n           H3LIS200DL_100G = 100   #±100g
      @n           H3LIS200DL_200G = 200   #±200g
    '''
    global _range 
    value = self.read_reg(self.REG_CTRL_REG4)
    _range = range_r
    if range_r == self.H3LIS200DL_100G:
     value = value & (~0x10)
    else:
     value = value | 0x10

  
  def read_acce_xyz(self):
    '''!
      @brief Get the acceleration in the three directions of xyz
      @return Three-axis acceleration(g), the measurement range is ±100g or ±200g, set by the set_range() function
    '''
    global _range 
    value = self.read_reg(self.REG_STATUS_REG)
    data = [0,0,0,0,0,0,0]
    x = 0
    y = 0
    z = 0
    if(value & 0x01) == 1:
      base = self.REG_OUT_X_L
      for i in range(0,6):
        data[i] = self.read_reg(base+i)
      for i in range(0,6):
        data[i] = np.int8(data[i])
      x = (data[1]*_range)/128
      y = (data[3]*_range)/128
      z = (data[5]*_range)/128

    return x,y,z

  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param data written data
    '''
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi.writebytes([reg,data])
    GPIO.output(self.__cs, GPIO.HIGH)
    #self._spi.transfer(data)
  
  def read_reg(self, reg):
    '''!
      @brief read the data from the register
      @param reg register address
      @return read data
    '''
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi.writebytes([reg|self.SPI_READ_BIT])
    time.sleep(0.01)
    data = self.__spi.readbytes(1)
    GPIO.output(self.__cs, GPIO.HIGH)
    return  data[0]
     
class DFRobot_LIS331HH_I2C(DFRobot_LIS): 
  def __init__(self ,bus ,addr):
    self.__addr = addr
    super(DFRobot_LIS331HH_I2C, self).__init__()
    self.i2cbus = smbus.SMBus(bus)
    
  
  def set_range(self,range_r):
    '''!
      @brief Set the measurement range
      @param range:Range(g)
      @n           LIS331HH_6G  = 6  #±6G
      @n           LIS331HH_12G = 12 #±12G
      @n           LIS331HH_24G = 24 #±24G
    '''
    global _range   
    value = self.read_reg(self.REG_CTRL_REG4)
    _range = range_r
    value = value&(~(3<<4))
    if range_r == self.LIS331HH_6G:
     value = value | (0x0<<4)
    elif range_r == self.LIS331HH_12G:
     value = value | (0x01<<4)
    elif range_r == self.LIS331HH_24G:
     value = value | (0x03<<4)
    self.write_reg(self.REG_CTRL_REG4,value)

  
  def read_acce_xyz(self):
    '''!
      @brief Get the acceleration in the three directions of xyz
      @return Three-axis acceleration(mg), the measurement range is ±6g, ±12g or ±24g, set by the set_range() function
    '''
    global _range   
    value = self.read_reg(self.REG_STATUS_REG)
    data = [0,0,0,0,0,0,0]
    x = 0
    y = 0
    z = 0
    if(value & 0x01) == 1:
      base = self.REG_OUT_X_L
      for i in range(0,6):
        data[i] = self.read_reg(base+i)
      for i in range(0,6):
        data[i] = np.int8(data[i])

      x = data[1]*256+data[0]
      x = (x*1000*_range)/(256*128)
      y = data[3]*256+data[2]
      y = (y*1000*_range)/(256*128)
      z = data[5]*256+data[4]
      z = (z*1000*_range)/(256*128)
    return x,y,z
    
  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param data written data
    '''
    self.i2cbus.write_i2c_block_data(self.__addr ,reg,[data])
  
  def read_reg(self, reg):
    '''!
      @brief read the data from the register
      @param reg register address
      @return read data
    '''
    self.i2cbus.write_byte(self.__addr,reg)
    time.sleep(0.01)
    rslt = self.i2cbus.read_byte(self.__addr)
    #print(rslt)
    return rslt

class DFRobot_LIS331HH_SPI(DFRobot_LIS): 
  def __init__(self ,cs, bus = 0, dev = 0,speed = 1000000):
    super(DFRobot_LIS331HH_SPI, self).__init__()
    self.__cs = cs
    GPIO.setup(self.__cs, GPIO.OUT)
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi = spidev.SpiDev()
    self.__spi.open(bus, dev)
    self.__spi.no_cs = True
    self.__spi.max_speed_hz = speed
    
  
  def set_range(self,range_r):
    '''!
      @brief Set the measurement range
      @param range:Range(g)
      @n           LIS331HH_6G  = 6  #±6G
      @n           LIS331HH_12G = 12 #±12G
      @n           LIS331HH_24G = 24 #±24G
    '''
    global _range   
    value = self.read_reg(self.REG_CTRL_REG4)
    _range = range_r
    value = value&(~(3<<4))
    if range_r == self.LIS331HH_6G:
     value = value | (0x0<<4)
    elif range_r == self.LIS331HH_12G:
     value = value | (0x01<<4)
    elif range_r == self.LIS331HH_24G:
     value = value | (0x03<<4)
    self.write_reg(self.REG_CTRL_REG4,value)

  
  def read_acce_xyz(self):
    '''!
      @brief Get the acceleration in the three directions of xyz
      @return Three-axis acceleration(mg), the measurement range is ±6g, ±12g or ±24g, set by the set_range() function
    '''
    global _range   
    value = self.read_reg(self.REG_STATUS_REG)
    data = [0,0,0,0,0,0,0]
    x = 0
    y = 0
    z = 0
    #print(_range)
    if(value & 0x01) == 1:
      base = self.REG_OUT_X_L
      for i in range(0,6):
        data[i] = self.read_reg(base+i)
      for i in range(0,6):
        data[i] = np.int8(data[i])

      x = data[1]*256+data[0]
      x = (x*1000*_range)/(256*128)
      y = data[3]*256+data[2]
      y = (y*1000*_range)/(256*128)
      z = data[5]*256+data[4]
      z = (z*1000*_range)/(256*128)
    return x,y,z

  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param data written data
    '''
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi.writebytes([reg,data])
    GPIO.output(self.__cs, GPIO.HIGH)
    #self._spi.transfer(data)
  
  def read_reg(self, reg):
    '''!
      @brief read the data from the register
      @param reg register address
      @return read data
    '''
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi.writebytes([reg|self.SPI_READ_BIT])
    time.sleep(0.01)
    data = self.__spi.readbytes(1)
    GPIO.output(self.__cs, GPIO.HIGH)
    #print(data)
    return  data[0]

