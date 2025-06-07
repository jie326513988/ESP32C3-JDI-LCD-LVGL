# -*- coding:utf-8 -*-
'''!
   @file activity_detect.py
   @brief Motion detection, can detect whether the module is moving
   @n It’s necessary to go into low power mode before using this function. Then call setActMode() to make the chip enter sleep mode. 
   @n In this state, the measurement rate is 12.5hz.
   @n When the acceleration change in a certain direction is detected to exceed the threshold, the measurement rate will be increased to 
   @n the normal rate we set before. The threshold can be set by the setWakeUpThreshold() function.
   @n But if the module stop moving, also, the change in acceleration in the three directions is less than the threshold, the chip will trun into sleep 
   @n mode after a period of time. This duration time can be set by the setWakeUpDur() function.
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

'''
  Set the sensor measurement range:
              RANGE_2G     #±2g
              RANGE_4G     #±4g
              RANGE_8G     #±8g
              RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)

'''
  Filter settings:
      LPF     #Low pass filter
      HPF     #High pass filter
'''
acce.set_filter_path(acce.LPF)

'''
   Set bandwidth
        RATE_DIV_2  #RATE/2 (up to RATE = 800 Hz, 400 Hz when RATE = 1600 Hz)
        RATE_DIV_4  #RATE/4 (High Power/Low power)
        RATE_DIV_10 #RATE/10 (HP/LP)
        RATE_DIV_20 #RATE/20 (HP/LP)
'''
acce.set_filter_bandwidth(acce.RATE_DIV_4)

'''
      Wake-up duration: when using the detection mode of eDetectAct in the setActMode() function, it will collect data
    at a normal rate after the chip is awakened. Then after a period of time, the chip will continue to hibernate, collecting data at a frequency of 12.5hz.
     dur duration(0 ~ 3)
     time = dur * (1/rate)(unit:s)
     |                            An example of a linear relationship between an argument and time                            |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_wakeup_dur(dur = 6)

#Set wakeup threshold, when the acceleration change exceeds this value, the eWakeUp event will be triggered,unit:mg
#The value is within the range.
acce.set_wakeup_threshold(0.05)

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
    Set the mode of motion detection:
                 NO_DETECTION      #No detection
                 DETECT_ACT        #If set this mode, the rate of the chip will drop to 12.5hz and turn normal  after the eWakeUp event is generated.
                 DETECT_STATMOTION #This mode can only detect if the chip is in sleep mode without changing the measurement frequency and power mode,
                                    continuously measuring data at normal frequency.
'''
acce.set_act_mode(acce.DETECT_ACT)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double click)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-Click)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.WAKEUP)

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
time.sleep(0.1)

while True:
    #Motion detected
    act = acce.act_detected()
    if act == True:
      print("Activity Detected")
    time.sleep(0.3)
