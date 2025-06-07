# -*- coding: utf-8 -*
""" 
  @file DFRobot_LIS2DW12.py
  @brief Define the basic structure of class DFRobot_LIS2DW12 
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [fengli](li.feng@dfrobot.com)
  @version  V1.0
  @date  2021-1-29
  @url https://github.com/DFRobot/DFRobot_LIS
"""
import time
import smbus
import spidev
import numpy as np
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

class DFRobot_LIS2DW12(object):
  REG_CARD_ID      = 0x0F     #The chip id
  REG_CTRL_REG1    = 0x20     #Control register 1
  REG_CTRL_REG4    = 0x23     #Control register 2
  REG_CTRL_REG2    = 0x21     #Control register 3
  REG_CTRL_REG3    = 0x22     #Control register 4
  REG_CTRL_REG5    = 0x24     #Control register 5
  REG_CTRL_REG6    = 0x25     #Control register 6
  REG_CTRL_REG7    = 0x3F     #Control register 7
  REG_STATUS_REG   = 0x27     #Status register
  REG_OUT_X_L      = 0x28     #The low order of the X-axis acceleration register
  REG_OUT_X_H      = 0x29     #The high point of the X-axis acceleration register
  REG_OUT_Y_L      = 0x2A     #The low order of the Y-axis acceleration register
  REG_OUT_Y_H      = 0x2B     #The high point of the Y-axis acceleration register
  REG_OUT_Z_L      = 0x2C     #The low order of the Z-axis acceleration register
  REG_OUT_Z_H      = 0x2D     #The high point of the Z-axis acceleration register
  REG_WAKE_UP_DUR  = 0x35     #Wakeup and sleep duration configuration register (r/w).
  REG_FREE_FALL    = 0x36     #Free fall event register
  REG_STATUS_DUP   = 0x37     #Interrupt event status register
  REG_STATUS_DUP   = 0x37     #Interrupt event status register
  REG_WAKE_UP_SRC  = 0x38     #Wakeup source register
  REG_TAP_SRC      = 0x39     #Tap source register
  REG_SIXD_SRC     = 0x3A     #6D source register
  REG_ALL_INT_SRC  = 0x3B     #Reading this register, all related interrupt function flags routed to the INT pads are reset simultaneously
  REG_TAP_THS_X  =  0x30      #4D configuration enable and TAP threshold configuration .
  REG_TAP_THS_Y  =  0x31      #Threshold for tap recognition @ FS = ±2 g on Y direction
  REG_TAP_THS_Z  =  0x32      #Threshold for tap recognition @ FS = ±2 g on Z direction
  REG_INT_DUR    =  0x33      #Interrupt duration register
  REG_WAKE_UP_THS = 0x34      #Wakeup threshold register
  SPI_READ_BIT   =  0X80      # bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) from the device is read.
  ID = 0X44
  __range =  0.061
  __range_d = 0
  
  '''
    Power mode
  '''
  HIGH_PERFORMANCE_14BIT                   = 0X04#High-Performance Mode
  CONT_LOWPWR4_14BIT                       = 0X03#Continuous measurement,Low-Power Mode 4(14-bit resolution)
  CONT_LOWPWR3_14BIT                       = 0X02#Continuous measurement,Low-Power Mode 3(14-bit resolution)
  CONT_LOWPWR2_14BIT                       = 0X01#Continuous measurement,Low-Power Mode 2(14-bit resolution)
  CONT_LOWPWR1_12BIT                       = 0X00#Continuous measurement,Low-Power Mode 1(12-bit resolution)
  SING_LELOWPWR4_14BIT                     = 0X0B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
  SING_LELOWPWR3_14BIT                     = 0X0A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
  SING_LELOWPWR2_14BIT                     = 0X09#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
  SING_LELOWPWR1_12BIT                     = 0X08#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
  HIGHP_ERFORMANCELOW_NOISE_14BIT          = 0X14#High-Performance Mode,Low-noise enabled
  CONT_LOWPWRLOWNOISE4_14BIT               = 0X13#Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
  CONT_LOWPWRLOWNOISE3_14BIT               = 0X12#Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
  CONT_LOWPWRLOWNOISE2_14BIT               = 0X11#Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
  CONT_LOWPWRLOWNOISE1_12BIT               = 0X10#Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
  SINGLE_LOWPWRLOWNOISE4_14BIT             = 0X1B#Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
  SINGLE_LOWPWRLOWNOISE3_14BIT             = 0X1A#Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
  SINGLE_LOWPWRLOWNOISE2_14BIT             = 0X19#Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
  SINGLE_LOWPWRLOWNOISE1_12BIT             = 0X18#Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled

  '''
    Sensor range
  '''
  RANGE_2G     = 2   #±2g
  RANGE_4G     = 4   #±4g
  RANGE_8G     = 8   #±8g
  RANGE_16G    = 16  #±16g
  
  '''
    Filtering mode
  '''
  LPF         = 0x00 #Low pass filter
  HPF         = 0x10 #High pass filter

  '''
    bandwidth of collected data
  '''
  RATE_DIV_2     = 0  #RATE/2 (up to RATE = 800 Hz, 400 Hz when RATE = 1600 Hz)>*/
  RATE_DIV_4     = 1  #RATE/4 (High Power/Low power)
  RATE_DIV_10    = 2  #RATE/10 (HP/LP)
  RATE_DIV_20    = 3  #RATE/20 (HP/LP)

  '''
    Data collection rate
  '''
  RATE_OFF            = 0X00  #Measurement off
  RATE_1HZ6           = 0X01  #1.6hz, use only under low-power mode
  RATE_12HZ5          = 0X02  #12.5hz
  RATE_25HZ           = 0X03
  RATE_50HZ           = 0X04
  RATE_100HZ          = 0X05
  RATE_200HZ          = 0X06
  RATE_400HZ          = 0X07  #Use only under High-Performance mode
  RATE_800HZ          = 0X08  #Use only under High-Performance mode
  RATE_1600HZ         = 0X09  #Use only under High-Performance mode
  SETSWTRIG           = 0X12  #The software triggers a single measurement
  
  '''
    Motion detection mode
  '''
  NO_DETECTION        = 0 #No detection
  DETECT_ACT          = 1 #Detect movement
  DETECT_STATMOTION   = 3 #Detect Motion


  '''
    Interrupt source 1 trigger event setting
  '''
  DOUBLE_TAP = 0x08     #Double tap event
  FREEFALL   = 0x10     #Freefall event
  WAKEUP     = 0x20     #Wake-up event
  SINGLE_TAP = 0x40     #Single tap event
  IA6D       = 0x80     #An event changed the status of facing up/down/left/right/forward/back

  '''
    Interrupt source 2 trigger event setting
  '''
  SLEEP_STATE  = 0x40 #Sleep change status routed to INT2 pad
  SLEEP_CHANGE = 0x80 #Enable routing of SLEEP_STATE on INT2 pad

  
  '''
    tap or double tap
  '''
  S_TAP  = 0  #single tap
  D_TAP  = 1  #double tap
  NO_TAP      = 2  #no tap
  
  #which direction is tap event detected
  DIR_X_UP   = 0 #Tap event generated in the positive X direction
  DIR_X_DOWN = 1 #Tap event generated in the negative X direction
  DIR_Y_UP   = 2 #Tap event generated in the positive Y direction
  DIR_Y_DOWN = 3 #Tap event generated in the negative Y direction
  DIR_Z_UP   = 4 #Tap event generated in the positive Z direction
  DIR_Z_DOWN = 5 #Tap event generated in the negative Z direction
  
  #which direction is wake up event detected
  DIR_X = 0 #Motion in the X direction woke up the chip
  DIR_Y = 1 #Motion in the Y direction woke up the chip
  DIR_Z = 2 #Motion in the Z direction woke up the chip
  
  ERROR = 0XFF
  
  #tap detection mode
  ONLY_SINGLE          = 0 #Only single tap events detected
  BOTH_SINGLE_DOUBLE   = 1 #Both single-tap and double-tap events detected

  '''
    Position detection
  '''
  DEGREES_80          = 0 #80 degrees.
  DEGREES_70          = 1 #70 degrees.
  DEGREES_60          = 2 #60 degrees.
  DEGREES_50          = 3 #50 degrees.
  
  #orientation
  X_DOWN = 0  #X is now down
  X_UP   = 1  #X is now up
  Y_DOWN = 2  #Y is now down
  Y_UP   = 3  #Y is now up
  Z_DOWN = 4  #Z is now down
  Z_UP   = 5  #Z is now up

  def __init__(self):
    __reset = 1
  
  def begin(self):
    '''!
      @brief Initialize the function
      @return True(Iniatialization succeed)/Fasle(Initialization failed)
    '''
    identifier = self.read_reg(self.REG_CARD_ID)
    if identifier == self.ID:
      return True
    else:
      return False
      
  
  def get_id(self):
    '''!
      @brief Get chip id
      @return 8 bit serial number
    '''
    identifier = self.read_reg(self.REG_CARD_ID)
    return identifier
  
  def soft_reset(self):
    '''!
      @brief Software reset to restore the value of all registers to the default value
    '''
    value = self.read_reg(self.REG_CTRL_REG2)
    value = value | (1<<6)
    #print(value)
    self.write_reg(self.REG_CTRL_REG2,value)
  
  def set_range(self,range_r):
    '''!
      @brief Set the measurement range
      @param range Range
      @n           RANGE_2G     #±2g
      @n           RANGE_4G     #±4g
      @n           RANGE_8G     #±8g
      @n           RANGE_16G    #±16g
    '''
    value = self.read_reg(self.REG_CTRL_REG6)
    self.__range_d = range_r
    value = value & (~(3<<4))
    if range_r == self.RANGE_2G:
      self.__range = 0.061
    elif range_r == self.RANGE_4G:
      self._range = 0.122
      value = value | (1<<4)
    elif range_r == self.RANGE_8G:
      self._range = 0.244
      value = value | (2<<4)
    elif range_r == self.RANGE_16G:
      self._range = 0.488
      value = value | (3<<4)
    self.write_reg(self.REG_CTRL_REG6,value)
  
  def contin_refresh(self,enable):
    '''!
      @brief Choose whether to continuously let the chip collect data
      @param enable  true(continuous update)/false( output registers not updated until MSB and LSB read)
    '''
    value = self.read_reg(self.REG_CTRL_REG2)
    if enable == True:
       value = value | (1<<3)
    else:
       value = value &(~(1<<3))
    self.write_reg(self.REG_CTRL_REG2,value)
  
  
  def set_filter_path(self,path):
    '''!
      @brief Set the filter processing mode
      @param path path of filtering
      @n          LPF          #Low pass filter
      @n          HPF          #High pass filter
    '''
    value = self.read_reg(self.REG_CTRL_REG6)
    enable = path & 0x10
    if(enable > 0):
       enable = 1
    value = value & (~(3<<2))
    value = value | (enable << 3)
    #print(value)
    self.write_reg(self.REG_CTRL_REG6,value)
    value = self.read_reg(self.REG_CTRL_REG7)
    
    value = value &(~(1<<4))
    value = value | enable << 4
    #print(value)
    self.write_reg(self.REG_CTRL_REG7,value)

  
  def set_filter_bandwidth(self,bw):
    '''!
      @brief Set the  bandwidth of the data
      @param bw bandwidth
      @n          RATE_DIV_2   #RATE/2 (up to RATE = 800 Hz, 400 Hz when RATE = 1600 Hz)
      @n          RATE_DIV_4   #RATE/4 (High Power/Low power)
      @n          RATE_DIV_10  #RATE/10 (HP/LP)
      @n          RATE_DIV_20  #RATE/20 (HP/LP)
    '''
    value = self.read_reg(self.REG_CTRL_REG6)
    value = value & (~(3 << 6))
    value = value | (bw << 6)
    #print(value)
    self.write_reg(self.REG_CTRL_REG6,value)
    
                                            
  def set_power_mode(self,mode):
    '''!
      @brief Set power mode
      @param mode 16 power modes to choose from
      @n         HIGH_PERFORMANCE_14BIT          #High-Performance Mode
      @n         CONT_LOWPWR4_14BIT              #Continuous measurement,Low-Power Mode 4(14-bit resolution)
      @n         CONT_LOWPWR3_14BIT              #Continuous measurement,Low-Power Mode 3(14-bit resolution)
      @n         CONT_LOWPWR2_14BIT              #Continuous measurement,Low-Power Mode 2(14-bit resolution)
      @n         CONT_LOWPWR1_12BIT              #Continuous measurement,Low-Power Mode 1(12-bit resolution)
      @n         SING_LELOWPWR4_14BIT            #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
      @n         SING_LELOWPWR3_14BIT            #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
      @n         SING_LELOWPWR2_14BIT            #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
      @n         SING_LELOWPWR1_12BIT            #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
      @n         HIGHP_ERFORMANCELOW_NOISE_14BIT #High-Performance Mode,Low-noise enabled
      @n         CONT_LOWPWRLOWNOISE4_14BIT      #Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
      @n         CONT_LOWPWRLOWNOISE3_14BIT      #Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
      @n         CONT_LOWPWRLOWNOISE2_14BIT      #Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
      @n         CONT_LOWPWRLOWNOISE1_12BIT      #Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
      @n         SINGLE_LOWPWRLOWNOISE4_14BIT    #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
      @n         SINGLE_LOWPWRLOWNOISE3_14BIT    #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
      @n         SINGLE_LOWPWRLOWNOISE2_14BIT    #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
      @n         SINGLE_LOWPWRLOWNOISE1_12BIT    #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
    '''
    value = self.read_reg(self.REG_CTRL_REG1)
    value = value & (~0x0f)
    value = value | (mode & 0xf)
    self.write_reg(self.REG_CTRL_REG1,value)
    #print("set_power_mode")
    #print(value)
    value = self.read_reg(self.REG_CTRL_REG6)
    enable = mode >> 4
    value = value & (~(1 << 2))
    value = value | (enable << 2)
    #print(value)
    self.write_reg(self.REG_CTRL_REG6,value)
    
  
  def set_data_rate(self, rate):
    '''!
      @brief Set data measurement rate
      @param rate rate
      @n             RATE_OFF          #Measurement off
      @n             RATE_1HZ6         #1.6hz, use only under low-power mode
      @n             RATE_12HZ5        #12.5hz
      @n             RATE_25HZ         
      @n             RATE_50HZ         
      @n             RATE_100HZ        
      @n             RATE_200HZ        
      @n             RATE_400HZ        #Use only under High-Performance mode
      @n             RATE_800HZ        #Use only under High-Performance mode
      @n             RATE_1600HZ       #Use only under High-Performance mode
      @n             SETSWTRIG         #The software triggers a single measurement
    '''
    value = self.read_reg(self.REG_CTRL_REG1)
    value = value & (~(0xf << 4))
    value = value | (rate << 4)
    #print("set_data_rate")
    #print(value)
    self.write_reg(self.REG_CTRL_REG1,value)
    value = self.read_reg(self.REG_CTRL_REG3)
    enable = (rate&0x30) >> 4
    
    value = value & (~3)
    value = value | enable
    #print(value)
    self.write_reg(self.REG_CTRL_REG3,value)
    
  
  def set_free_fall_Dur(self,dur):
    '''!
      @brief Set the free fall time, or the numbers of free-fall samples. In a measurement, it will not be determined as a free fall event unless the samples are enough. 
      @param dur duration, range:0~31
      @n time = dur * (1/rate)(unit:s)
      @n|                          An example of a linear relationship between an argument and time                              |
      @n|------------------------------------------------------------------------------------------------------------------------|
      @n|                |                     |                          |                          |                           |
      @n|  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
      @n|------------------------------------------------------------------------------------------------------------------------|
      @n|   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
      @n|------------------------------------------------------------------------------------------------------------------------|
    '''
    value1 = self.read_reg(self.REG_WAKE_UP_DUR)
    value2 = self.read_reg(self.REG_FREE_FALL)
    
    value1 = value1 & (~0x80)
    value2 = value2 & (~0xf8)
    value2 = value2 | (dur << 3)
    #print(value1)
    self.write_reg(self.REG_WAKE_UP_DUR,value1)
    #print(value2)
    self.write_reg(self.REG_FREE_FALL,value2)
    self.__set_ff_threshold(3)
    
  
  def __set_ff_threshold(self,th):
    '''!
      @brief Set Free-fall threshold
      @param th threshold
    '''
    value = self.read_reg(self.REG_FREE_FALL)
    value = value & (~0x07)
    value = value | (th & 0x07)
    #print(value)
    self.write_reg(self.REG_FREE_FALL,value)
  
  
  def set_int1_event(self,event):
    '''!
      @brief Set the interrupt source of the int1 pin
      @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int1 pin
      @n          DOUBLE_TAP    #Double tap event
      @n          FREEFALL      #Freefall event
      @n          WAKEUP        #Wake-up event
      @n          SINGLE_TAP    #Single tap event
      @n          IA6D          #An event changed the status of facing up/down/left/right/forward/back
    '''
    value1 = self.read_reg(self.REG_CTRL_REG4)
    value2 = self.read_reg(self.REG_CTRL_REG5)
    value3 = self.read_reg(self.REG_CTRL_REG7)
    value3 = value3 & (~0x20)
    value3 = value3 | 0x20
    value1 = value1 | event
    self.write_reg(self.REG_CTRL_REG4,value1)
    self.write_reg(self.REG_CTRL_REG7,value3)
    if event == self.FREEFALL:
      self.__lock_interrupt(True)
  
  def set_wakeup_dur(self,dur):
    '''!
      @brief Set wake-up duration, when using the detection mode of eDetectAct in the setActMode() function, it will be a period of time to collect 
      @n data at a normal rate after the chip is awakened. Then the chip will continue to hibernate, collecting data at a frequency of 12.5hz.
      @param dur duration, range: 0~3
      @n time = dur * (1/rate)(unit:s)
      @n|                               An example of a linear relationship between an argument and time                         |
      @n|------------------------------------------------------------------------------------------------------------------------|
      @n|                |                     |                          |                          |                           |
      @n|  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
      @n|------------------------------------------------------------------------------------------------------------------------|
      @n|   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
      @n|------------------------------------------------------------------------------------------------------------------------|
    '''
    value = self.read_reg(self.REG_WAKE_UP_DUR)
    value = value & (~0x60)
    value = value | ((dur << 5) & 0x60)
    #print(value)
    self.write_reg(self.REG_WAKE_UP_DUR,value)

  
  def set_act_mode(self,mode):
    '''!
      @brief Set the mode of motion detection, the first mode will not detect whether the module is moving; the second, once set, will measure
      @n data at a lower frequency to save consumption, and return to normal after detecting motion; the third can only detect whether the
      @n module is in sleep state.
      @param mode Motion detection mode
      @n            NO_DETECTION         #No detection
      @n            DETECT_ACT           #Detect movement,the chip automatically goes to 12.5 Hz rate in the low-power mode
      @n            DETECT_STATMOTION    #Detect Motion, the chip detects acceleration below a fixed threshold but does not change either rate or operating mode
    '''!
    value1 = self.read_reg(self.REG_WAKE_UP_THS)
    value2 = self.read_reg(self.REG_WAKE_UP_DUR)
    value1 = value1 & (~(1<<6))
    value2 = value2 & (~(1<<4))
    value1 = value1 | (mode & 0x01)<<6
    value2 = value2 | ((mode & 0x02)>>1)<<4
    #print(value1)
    #print(value2)
    self.write_reg(self.REG_WAKE_UP_THS,value1)
    self.write_reg(self.REG_WAKE_UP_DUR,value2)

  
  def set_wakeup_threshold(self,th):
    '''!
      @brief Set the wake-up threshold, when the acceleration in a certain direction is greater than this value, a wake-up event will be triggered
      @param th threshold ,unit:mg, the value is within the measurement range
    '''
    th1 = (float(th)/self.__range_d) * 64
    value = self.read_reg(self.REG_WAKE_UP_THS)
    value = value &(~0x3f)
    value = value | (int(th1) & 0x3f)
    #print(value)
    self.write_reg(self.REG_WAKE_UP_THS,value)
    
  
  def __lock_interrupt(self,enable):
    '''!
      @brief lock interrupt Switches between latched ('1'-logic) and pulsed ('0'-logic) mode for 
      @n function source signals and interrupts routed to pins (wakeup, single/double-tap).
      @param enable  true lock interrupt.false pulsed interrupt
    '''
    value = self.read_reg(self.REG_CTRL_REG3)
    value = value & (~0x10)
    value = value | (enable << 4)
    self.write_reg(self.REG_CTRL_REG3,value)
    
  
  def enable_tap_detection_on_z(self, enable):
    '''!
      @brief Set to detect tap events in the Z direction
      @param enable Ture(Enable tap detection\False(Disable tap detection)
    '''
    value = self.read_reg(self.REG_TAP_THS_Z)
    value = value & (~(1<<5))
    value = value | (enable << 5)
    #print("enable_tap_detection_on_z")
    #print(value)
    self.write_reg(self.REG_TAP_THS_Z,value)
  
  
  def enable_tap_detection_on_y(self, enable):
    '''!
      @brief Set to detect tap events in the Y direction
      @param enable Ture(Enable tap detection\False(Disable tap detection)
    '''
    value = self.read_reg(self.REG_TAP_THS_Z)
    value = value & (~(1<<6))
    value = value | (enable << 6)
    #print("enable_tap_detection_on_y")
    #print(value)
    self.write_reg(self.REG_TAP_THS_Z,value)
    
  
  def enable_tap_detection_on_x(self, enable):
    '''!
      @brief Set to detect tap events in the X direction
      @param enable Ture(Enable tap detection)\False(Disable tap detection)
    '''
    value = self.read_reg(self.REG_TAP_THS_Z)
    value = value & (~(1<<7))
    value = value | (enable << 7)
    #print("enable_tap_detection_on_x")
    #print(value)
    self.write_reg(self.REG_TAP_THS_Z,value)

  
  def set_tap_threshold_on_x(self,th):
    '''!
      @brief Set the tap threshold in the X direction
      @param th Threshold(g),Can only be used in the range of ±2g
    '''
    th1 = (float(th)/self.__range_d) * 32
    value = self.read_reg(self.REG_TAP_THS_X)
    value = value & (~0x1f)
    value = value | (int(th1) & 0x1f)
    #print("set_tap_threshold_on_x")
    #print(value)
    self.write_reg(self.REG_TAP_THS_X,value)
   
  def set_tap_threshold_on_y(self,th):
    '''!
      @brief Set the tap threshold in the Y direction
      @param th Threshold(g),Can only be used in the range of ±2g
    '''
    th1 = (float(th)/self.__range_d) * 32
    value = self.read_reg(self.REG_TAP_THS_Y)
    value = value & (~0x1f)
    value = value | (int(th1) & 0x1f)
    #print("set_tap_threshold_on_y")
    #print(value)
    self.write_reg(self.REG_TAP_THS_Y,value)
    
  
  def set_tap_threshold_on_z(self,th):
    '''!
      @brief Set the tap threshold in the Z direction
      @param th Threshold(g),Can only be used in the range of ±2g
    '''
    th1 = (float(th)/self.__range_d) * 32
    value = self.read_reg(self.REG_TAP_THS_Z)
    value = value & (~0x1f)
    value = value | (int(th1) & 0x1f)
    #print("set_tap_threshold_on_z")
    #print(value)
    self.write_reg(self.REG_TAP_THS_Z,value)
    
  
  def set_tap_dur(self,dur):
    '''!
      @brief Duration of maximum time gap for double-tap recognition. When double-tap 
      @n recognition is enabled, this register expresses the maximum time between two 
      @n successive detected taps to determine a double-tap event.
      @param dur  duration,range: 0~15
      @n time = dur * (1/rate)(unit:s)
      @n|                         An example of a linear relationship between an argument and time                               |
      @n|------------------------------------------------------------------------------------------------------------------------|
      @n|                |                     |                          |                          |                           |
      @n|  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
      @n|------------------------------------------------------------------------------------------------------------------------|
      @n|   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
      @n|------------------------------------------------------------------------------------------------------------------------|
  '''
    value = self.read_reg(self.REG_INT_DUR)
    value = value & (~0xf0)
    value = value | (dur << 4)
    #print("set_tap_dur")
    #print(value)
    self.write_reg(self.REG_INT_DUR,value)
    self.__set_tap_quiet(2)
    self.__set_tap_shock(2)
    
  
  def __set_tap_quiet(self,quiet):
    '''!
      @brief set quiet time after a tap detection: this register represents
      @n the time after the first detected tap in which there must not be any overthreshold event.
      @param quiet quiet time
    '''
    value = self.read_reg(self.REG_INT_DUR)
    value = value & (~0x0C)
    quiet = quiet & 0x03
    value = value | (quiet<<2)
    #print("set_tap_quiet")
    #print(value)
    self.write_reg(self.REG_INT_DUR,value)
  
  
  def __set_tap_shock(self,shock):
    '''!
      @brief Set the maximum time of an over-threshold signal detection to be recognized as a tap event.
      @param shock  shock time
    '''
    value = self.read_reg(self.REG_INT_DUR)
    value = value & (~0x03)
    shock = shock & 0x03
    value = value | (shock)
    #print("set_tap_shock")
    #print(value)
    self.write_reg(self.REG_INT_DUR,value)
  
  
  def set_tap_mode(self,mode):
    '''!
      @brief Set the tap detection mode, detect single tap or detect both single tap and double tap
      @param mode  Tap detection mode
      @n               ONLY_SINGLE        #Detect single tap
      @n               BOTH_SINGLE_DOUBLE #Detect both single tap and double tap
    '''
    value = self.read_reg(self.REG_WAKE_UP_THS)
    value = value & (~0x80)
    value = value | (mode << 7)
    #print("set_tap_mode")
    #print(value)
    self.write_reg(self.REG_WAKE_UP_THS,value)

  
  def set_6d_threshold(self,degree):
    '''!
      @brief Set Thresholds for 4D/6D，when the threshold of rotation exceeds the specified angle, a direction change event will occur.
      @param degree   DEGREES_80   #80°
      @n              DEGREES_70   #70°
      @n              DEGREES_60   #60°
      @n              DEGREES_50   #50°
    '''
    value = self.read_reg(self.REG_TAP_THS_X)
    value = value & (~0x60)
    value = value | (degree << 5)
    #print("set_6d_threshold")
    #print(value)
    self.write_reg(self.REG_TAP_THS_X,value)
    self.__set_6d_feed_data(1)
    
  
  def set_int2_event(self,event):
    '''!
      @brief Select the interrupt event generated on the int2 pin
      @param event  Several interrupt events, after setting, when an event is generated, a level transition will be generated on the int2 pin
      @n            SLEEP_CHANGE  #Enable routing of SLEEP_STATE on INT2 pad
      @n            SLEEP_STATE   #0x80 Sleep change status routed to INT2 pad
    '''
    value1 = self.read_reg(self.REG_CTRL_REG4)
    value2 = self.read_reg(self.REG_CTRL_REG5)
    value3 = self.read_reg(self.REG_CTRL_REG7)
    value3 = value3 & (~0x20)
    value3 = value3 | 0x20
    value2 = value2 | event
    #print(value2)
    #print(value3)
    self.write_reg(self.REG_CTRL_REG5,value2)
    self.write_reg(self.REG_CTRL_REG7,value3)

  
  def __set_6d_feed_data(self,data):
    '''!
      @brief Set 6d filtered data source
      @param data 0: RATE/2 low pass filtered data sent to 6D interrupt function (default)
      @n          1: LPF2 output data sent to 6D interrupt function)
    '''
    value = self.read_reg(self.REG_CTRL_REG7)
    value = value & (~1)
    value = value | data
    #print(value)
    self.write_reg(self.REG_CTRL_REG7,value)
  
  def read_acc_x(self):
    '''!
      @brief Read the acceleration in the x direction
      @return Acceleration data from x(mg), the mearsurement range is ±2g,±4g,±8g or ±16g, set by the setRange() function
    '''
    value1 = self.read_reg(self.REG_OUT_X_L)
    value2 = self.read_reg(self.REG_OUT_X_L+1)
    acc_x = np.int8(value2)*256 + np.int8(value1)
    acc_x = acc_x * self.__range
    return acc_x

  
  def read_acc_y(self):
    '''!
      @brief Read the acceleration in the y direction
      @return  Acceleration data from y(mg), the mearsurement range is ±2g,±4g,±8g or ±16g, set by the setRange() function
    '''
    value1 = self.read_reg(self.REG_OUT_Y_L)
    value2 = self.read_reg(self.REG_OUT_Y_L+1)
    acc_y = np.int8(value2)*256 + np.int8(value1)
    acc_y = acc_y * self.__range
    return acc_y

  
  def read_acc_z(self):
    '''!
      @brief Read the acceleration in the z direction
      @return Acceleration data from z(mg), the mearsurement range is ±2g,±4g,±8g or ±16g, set by the setRange() function
    '''
    value1 = self.read_reg(self.REG_OUT_Z_L)
    value2 = self.read_reg(self.REG_OUT_Z_L+1)
    acc_z = np.int8(value2)*256 + np.int8(value1)
    acc_z = acc_z * self.__range
    return acc_z
  
  
  def act_detected(self):
    '''!
      @brief Detect whether a motion is generated
      @return True(Motion generated)/False(No motion generated)
    '''
    value = self.read_reg(self.REG_WAKE_UP_SRC)
    if(value & 0x08) > 0:
      return True
    else:
      return False
      
  
  def free_fall_detected(self):
    '''!
      @brief Freefall detection
      @return True(Freefall detected)/False(No freefall detected)
    '''
    value = self.read_reg(self.REG_WAKE_UP_SRC)
    if(value & 0x20) > 0:
      return True
    return False
    
  
  def ori_change_detected(self):
    '''!
      @brief Detect whether the direction of the chip changes when the chip is facing up/down/left/right/forward/back (ie 6D)
      @return True(a change in position is detected)/False(no event detected)
    '''
    value = self.read_reg(self.REG_SIXD_SRC)
    if(value & 0x40) > 0:
      return True
    else:
      return False
      
  
  def get_oriention(self):
    '''!
      @brief Only in 6D (facing up/down/left/right/forward/backward) state can the function get the orientation of 
      @n     the sensor relative to the positive z-axis.
      @n         X_UP     #X is now up
      @n         Y_DOWN   #Y is now down
      @n         Y_UP     #Y is now up
      @n         Z_DOWN   #Z is now down
      @n         Z_UP     #Z is now up
    '''
    value = self.read_reg(self.REG_SIXD_SRC)
    orient = self.ERROR
    if(value & 0x1) > 0:
      orient =  self.X_DOWN
    elif(value & 0x2) > 0:
      orient =  self.X_UP
    elif(value & 0x4) > 0:
      orient =  self.Y_DOWN
    elif(value & 0x8) > 0:
      orient =  self.Y_UP
    elif(value & 0x10) > 0:
      orient =  self.Z_DOWN
    elif(value & 0x20) > 0:
      orient =  self.Z_UP
    return orient
     
  
  def tap_detect(self):
    '''!
      @brief Tap detection, can detect it is double tap or single tap
      @return   S_TAP       #single tap
      @n        D_TAP       #double tap
      @n        NO_TAP,     #no tap
    '''
    value = self.read_reg(self.REG_TAP_SRC)
    #print(value)
    tap = self.NO_TAP
    if(value & 0x20) > 0:
      tap = self.S_TAP
    elif(value & 0x10) > 0:
      tap = self.D_TAP
    return tap
    #Wakeup event detection status on X-axis

  
  def get_tap_direction(self):
    '''!
      @brief Tap source detection
      @return     DIR_X_UP   #Tap is detected in the positive direction of X
      @n          DIR_X_DOWN #Tap is detected in the negative direction of X
      @n          DIR_Y_UP   #Tap is detected in the positive direction of Y
      @n          DIR_Y_DOWN #Tap is detected in the negative direction of Y
      @n          DIR_Z_UP   #Tap is detected in the positive direction of Z
      @n          DIR_Z_DOWN #Tap is detected in the negative direction of Z
    '''
    value = self.read_reg(self.REG_TAP_SRC)
    #print(value)
    direction = self.ERROR
    positive = value & 0x08
    if(value & 0x4)>0 and positive > 0:
      direction = self.DIR_X_UP
    elif(value & 0x4)>0 and positive == 0:
      direction = self.DIR_X_DOWN
    elif(value & 0x2)>0 and positive > 0:
      direction = self.DIR_Y_UP
    elif(value & 0x2)>0 and positive == 0:
      direction = self.DIR_Y_DOWN
    elif(value & 0x1)>0 and positive > 0:
      direction = self.DIR_Z_UP
    elif(value & 0x1)>0 and positive == 0:
      direction = self.DIR_Z_DOWN
    return direction
  
  def get_wake_up_dir(self):
    '''!
      @brief Wake-up motion direction detection.
      @return    DIR_X  #The chip is woken up by the motion in X direction
      @n           DIR_Y  #The chip is woken up by the motion in Y direction
      @n           DIR_Z  #The chip is woken up by the motion in Z direction
      @n           eDirError,
    '''
    value = self.read_reg(self.REG_WAKE_UP_SRC)
    direction = self.ERROR
    if(value & 0x01) > 0:
      direction = self.DIR_Z
    elif(value & 0x02) > 0:
      direction = self.DIR_Y
    elif(value & 0x04) > 0:
      direction = self.DIR_X
    return direction

  
  def demand_data(self):
    '''!
      @brief In single data conversion on demand mode, request a measurement
    '''
    value = self.read_reg(self.REG_CTRL_REG3)
    value = value | 1
    self.write_reg(self.REG_CTRL_REG3,value)

class DFRobot_IIS2DLPC_I2C(DFRobot_LIS2DW12): 
  def __init__(self ,bus ,addr):
    self.__addr = addr
    super(DFRobot_IIS2DLPC_I2C, self).__init__()
    self.i2cbus = smbus.SMBus(bus)
    
  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param data written data
    '''
        self.i2cbus.write_i2c_block_data(self.__addr ,reg,[data])
        #self.i2cbus.write_byte(self.__addr ,reg)
        #self.i2cbus.write_byte(self.__addr ,data)
  
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
    
class DFRobot_IIS2DLPC_SPI(DFRobot_LIS2DW12): 
  def __init__(self ,cs, bus = 0, dev = 0,speed = 1000000):
    super(DFRobot_IIS2DLPC_SPI, self).__init__()
    self.__cs = cs
    GPIO.setup(self.__cs, GPIO.OUT)
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi = spidev.SpiDev()
    self.__spi.open(bus, dev)
    self.__spi.no_cs = True
    self.__spi.max_speed_hz = speed
    
  
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
     self.__spi.writebytes([reg | self.SPI_READ_BIT])
     time.sleep(0.01)
     data = self.__spi.readbytes(1)
     GPIO.output(self.__cs, GPIO.HIGH)
     return  data[0]
  
class DFRobot_LIS2DW12_I2C(DFRobot_LIS2DW12): 
  def __init__(self ,bus ,addr):
    self.__addr = addr;
    super(DFRobot_LIS2DW12_I2C, self).__init__()
    self.i2cbus = smbus.SMBus(bus)

  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param value written data
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
    return rslt
    
class DFRobot_LIS2DW12_SPI(DFRobot_LIS2DW12): 
  def __init__(self ,cs, bus = 0, dev = 0,speed = 10000000):
    super(DFRobot_LIS2DW12_SPI, self).__init__()
    self.__cs = cs
    GPIO.setup(self.__cs, GPIO.OUT)
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi = spidev.SpiDev()
    self.__spi.open(bus, dev)
    self.__spi.no_cs = True
    self.__spi.max_speed_hz = speed
    
  
  def write_reg(self, reg, data):
    '''!
      @brief writes data to a register
      @param reg register address
      @param data written data
    '''
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi.writebytes([reg,data])
    GPIO.output(self.__cs, GPIO.HIGH)
     
  
  def read_reg(self, reg):
    '''!
      @brief read the data from the register
      @param reg register address
      @return read data
    '''
    GPIO.output(self.__cs, GPIO.LOW)
    self.__spi.writebytes([reg | self.SPI_READ_BIT])
    time.sleep(0.01)
    data = self.__spi.readbytes(1)
    GPIO.output(self.__cs, GPIO.HIGH)
    return  data[0]
