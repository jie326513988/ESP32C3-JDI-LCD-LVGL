# -*- coding:utf-8 -*-
'''!
   @file orientation.py
   @brief  When detecting the orientation of the module, the sensor can detect the following six events:
   @n Positive z-axis is facing up
   @n Positive z-axis is facing down
   @n Positive y-axis is facing up
   @n Positive y-axis is facing down
   @n Positive x-axis is facing up
   @n Positive x-axis is facing down
   @n When using SPI, chip select pin can be modified by changing the value of RASPBERRY_PIN_CS
   @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
   @license     The MIT License (MIT)
   @author [fengli](li.feng@dfrobot.com)
   @version  V1.0
   @date  2021-01-16
   @url https://github.com/DFRobot/DFRobot_LIS
'''

import sys
sys.path.append("../..") # set system path to top

from DFRobot_LIS2DW12 import *
import time

#If you want to use SPI to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via SPI port
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected, use BCM coding method, the number is 27, corresponding to pin GPIO2
#acce = DFRobot_IIS2DLPC_SPI(RASPBERRY_PIN_CS)

#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port
#The I2C address can be switched through the DIP switch (gravity version) or SDO pin (Breakout version) on the board
I2C_BUS         = 0x01             #default use I2C1
#ADDRESS_0       = 0x18             #sensor address 0
ADDRESS_1       = 0x19             #sensor address 1
acce = DFRobot_IIS2DLPC_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())
#Software reset to restore the value of all registers
acce.soft_reset()
'''
  Set the sensor measurement range:
              RANGE_2G     #±2g
              RANGE_4G     #±4g
              RANGE_8G     #±8g
              RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)
'''
   Set power mode:
       HIGH_PERFORMANCE_14BIT           #High-Performance Mode
       CONT_LOWPWR4_14BIT               #Continuous measurement,Low-Power Mode 4(14-bit resolution)
       CONT_LOWPWR3_14BIT               #Continuous measurement,Low-Power Mode 3(14-bit resolution)
       CONT_LOWPWR2_14BIT               #Continuous measurement,Low-Power Mode 2(14-bit resolution)
       CONT_LOWPWR1_12BIT               #Continuous measurement,Low-Power Mode 1(12-bit resolution)
       SING_LELOWPWR4_14BIT             #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution)
       SING_LELOWPWR3_14BIT             #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution
       SING_LELOWPWR2_14BIT             #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution)
       SING_LELOWPWR1_12BIT             #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution)
       HIGHP_ERFORMANCELOW_NOISE_14BIT  #High-Performance Mode,Low-noise enabled
       CONT_LOWPWRLOWNOISE4_14BIT       #Continuous measurement,Low-Power Mode 4(14-bit resolution,Low-noise enabled)
       CONT_LOWPWRLOWNOISE3_14BIT       #Continuous measurement,Low-Power Mode 3(14-bit resolution,Low-noise enabled)
       CONT_LOWPWRLOWNOISE2_14BIT       #Continuous measurement,Low-Power Mode 2(14-bit resolution,Low-noise enabled)
       CONT_LOWPWRLOWNOISE1_12BIT       #Continuous measurement,Low-Power Mode 1(14-bit resolution,Low-noise enabled)
       SINGLE_LOWPWRLOWNOISE4_14BIT     #Single data conversion on demand mode,Low-Power Mode 4(14-bit resolution),Low-noise enabled
       SINGLE_LOWPWRLOWNOISE3_14BIT     #Single data conversion on demand mode,Low-Power Mode 3(14-bit resolution),Low-noise enabled
       SINGLE_LOWPWRLOWNOISE2_14BIT     #Single data conversion on demand mode,Low-Power Mode 2(14-bit resolution),Low-noise enabled
       SINGLE_LOWPWRLOWNOISE1_12BIT     #Single data conversion on demand mode,Low-Power Mode 1(12-bit resolution),Low-noise enabled
'''
acce.set_power_mode(acce.CONT_LOWPWRLOWNOISE1_12BIT)
'''
    Set the sensor data collection rate:
        RATE_OFF            #Measurement off
        RATE_1HZ6           #1.6hz, use only under low-power mode
        RATE_12HZ5          #12.5hz
        RATE_25HZ           
        RATE_50HZ           
        RATE_100HZ          
        RATE_200HZ          
        RATE_400HZ          #Use only under High-Performance mode
        RATE_800HZ          #Use only under High-Performance mode
        RATE_1600HZ         #Use only under High-Performance mode
        SETSWTRIG           #The software triggers a single measurement
'''
acce.set_data_rate(acce.RATE_200HZ)
'''
  Set Thresholds for 4D/6D，when the threshold of rotation exceeds the specified angle, a direction change event will occur.
  degree:         DEGREES_80   (80°)
                  DEGREES_70   (70°)
                  DEGREES_60   (60°)
                  DEGREES_50   (50°)
'''
acce.set_6d_threshold(acce.DEGREES_60)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double click)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-Click)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.IA6D)
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    #time.sleep(0.01)
    if acce.ori_change_detected() == True:
      '''
        X_DOWN = 0  #X is now down>
        X_UP  = 1   #X is now up
        Y_DOWN = 2  #Y is now down
        Y_UP = 3    #Y is now up
        Z_DOWN = 4  #Z is now down
        Z_UP = 5    #Z is now up
      '''
      orient = acce.get_oriention()
      if orient == acce.X_DOWN:
        print("X is down now")
      elif orient == acce.X_UP:
        print("X is up now")
      elif orient == acce.Y_DOWN:
        print("Y is down now")
      elif orient == acce.Y_UP:
        print("Y is up now")
      elif orient == acce.Z_DOWN:
        print("Z is down now")
      elif orient == acce.Z_UP:
        print("Z is up now")
