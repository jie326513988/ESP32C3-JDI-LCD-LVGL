# -*- coding:utf-8 -*-
'''!
   @file wake_up.py
   @brief When the acceleration change in x, y or z direction is detected to exceed the threshold we set before, the chip will generate a wake-up event.
   @n By accessing the chip register, we can know which direction of movement wakes up the chip.
   @n In this example, it is necessary to set the wake-up duration by setWakeUpThreshold(). 
   @n When woken up, the chip will last for a while before it enters sleep state.
   @n And to set the threshold by setWakeUpDur(). When the acceleration change exceeds this value, the eWakeUp event will be triggered.
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
#acce = DFRobot_LIS2DW12_SPI(RASPBERRY_PIN_CS)

#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port
#The I2C address can be switched through the DIP switch (gravity version) or SDO pin (Breakout version) on the board
I2C_BUS         = 0x01             #default use I2C1
#ADDRESS_0       = 0x18             #sensor address0
ADDRESS_1       = 0x19             #sensor address1
acce = DFRobot_LIS2DW12_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())
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
        SETSWTRIG           #The software triggers a single measurement.
'''
acce.set_data_rate(acce.RATE_200HZ)

'''
  Filter settings:
      LPF      Low pass filter
      HPF      High pass filter
'''
acce.set_filter_path(acce.LPF)
'''
  Set the wake-up duration:
     dur duration(0 ~ 3)
     time = dur * (1/rate)(unit:s)
     |                          An example of a linear relationship between an argument and time                              |
     |------------------------------------------------------------------------------------------------------------------------|
     |                |                     |                          |                          |                           |
     |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
     |------------------------------------------------------------------------------------------------------------------------|
     |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
     |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_wakeup_dur(dur = 1)

'''
  Set the wake-up Threshold:
  unit(g), the value is within the range
'''
acce.set_wakeup_threshold(0.1)

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
Set the interrupt source of the int2 pin:
                  SLEEP_CHANGE # Enable routing of SLEEP_STATE on INT2 pad
                  SLEEP_STATE  #Sleep change status routed to INT2 pad
'''
#acce.set_int2_event(acce.SLEEP_CHANGE):
time.sleep(0.1)

while True:
    #Motion detected
    act = acce.act_detected()
    if act == True:
      print("wake-up event happened in ")
      #Wake-up motion direction detection
      direction = acce.get_wake_up_dir() 
      if direction == acce.DIR_Z:
         print("z direction")
      elif direction == acce.DIR_Y:
         print("y direction")
      elif direction == acce.DIR_X:
         print("x  direction")
      time.sleep(0.3)
