# -*- coding:utf-8 -*-
'''!
   @file free_fall.py
   @brief  Sensor module free fall detection, set the free fall time with the setFrDur() function to adjust the sensitivity of the detection
   @n The shorter the free fall time we set, the easier for the module to detect the free fall event
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
#Choose whether to continuously let the chip collect data
acce.contin_refresh(True)

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
acce.set_power_mode(acce.CONT_LOWPWR4_14BIT);
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
acce.set_data_rate(acce.RATE_100HZ);
'''
   Set the measurement range
               RANGE_2G     #±2g
               RANGE_4G     #±4g
               RANGE_8G     #±8g
               RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)
'''
  Set the free fall time (Or the number of free-fall samples. In a measurement, it will not be determined as a free-fall event unless the free-fall samples are sufficient.) 
     dur duration(0 ~ 31)
     time = dur * (1/rate)(unit:s)
     |                        An example of a linear relationship between an argument and time                                |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_free_fall_Dur(dur = 0x06)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double click)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-Click)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.FREEFALL)
time.sleep(0.1)

while True:
    #Free fall event detected
    free_fall = acce.free_fall_detected()
    if free_fall == True:
      print("free fall detected")
      time.sleep(0.3)
