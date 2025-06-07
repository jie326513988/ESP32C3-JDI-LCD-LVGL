# -*- coding:utf-8 -*-
'''!
  @file tap.py
  @brief Single tap and double tap detection, tapping the module or the desktop nearby both can trigger the tap event
  @n You can select to detect only single tap or to detect both single tap and double tap by the set_tap_mode() function
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
#ADDRESS_0       = 0x18             #sensor address 0
ADDRESS_1       = 0x19             #sensor address 1
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
        SETSWTRIG           #The software triggers a single measurement
'''
acce.set_data_rate(acce.RATE_800HZ)

#Enable tap detection in the X direction
acce.enable_tap_detection_on_z(True)
#Enable tap detection in Y direction
acce.enable_tap_detection_on_y(True)
#Enable tap detection in the Z direction
acce.enable_tap_detection_on_x(True)
#The threshold setting in the X direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_x(0.5)
#The threshold setting in the Y direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_y(0.5)
#The threshold setting in the Z direction is similar to the sensitivity of detection, the larger the value, the less sensitive (0~31)
acce.set_tap_threshold_on_z(0.5)
'''
   The interval time between two taps when detecting double tap
   dur duration(0 ~ 15)
   time = dur * (1/rate)(unit:s)
   |                     An example of a linear relationship between an argument and time                                   |
   |------------------------------------------------------------------------------------------------------------------------|
   |                |                     |                          |                          |                           |
   |  Data rate     |       25 Hz         |         100 Hz           |          400 Hz          |         = 800 Hz          |
   |------------------------------------------------------------------------------------------------------------------------|
   |   time         |dur*(1s/25)= dur*40ms|  dur*(1s/100)= dur*10ms  |  dur*(1s/400)= dur*2.5ms |  dur*(1s/800)= dur*1.25ms |
   |------------------------------------------------------------------------------------------------------------------------|
'''
acce.set_tap_dur(dur = 6)

'''
  Set the tap detection mode:
      ONLY_SINGLE   //Single tap detection
      BOTH_SINGLE_DOUBLE //Both single tap and double tap detection 
'''
acce.set_tap_mode(acce.BOTH_SINGLE_DOUBLE)

'''
  Set the interrupt source of the int1 pin:
          DOUBLE_TAP(Double tap)
          FREEFALL(Free fall)
          WAKEUP(wake)
          SINGLE_TAP(single-tap)
          IA6D(Orientation change check)
'''
acce.set_int1_event(acce.DOUBLE_TAP)
time.sleep(0.1)

while True:
    tap = False
    #Tap detection
    event = acce.tap_detect()
    #Tap source detection
    direction = acce.get_tap_direction()
    if event == acce.S_TAP:
      print ("Tap Detected :")
      tap = True
    elif event == acce.D_TAP:
      print ("Double Tap Detected :")
      tap = True
    if tap == True:
      if direction == acce.DIR_X_UP:
        print("tap is detected in the positive direction of X")
      elif direction == acce.DIR_X_DOWN:
        print("tap is detected in the negative direction of X")
      elif direction == acce.DIR_Y_UP:
        print("tap is detected in the positive direction of Y")
      elif direction == acce.DIR_Y_DOWN:
        print("tap is detected in the negative direction of Y")
      elif direction == acce.DIR_Z_UP:
        print("tap is detected in the positive direction of Z")
      elif direction == acce.DIR_Z_DOWN:
        print("tap is detected in the negative direction of Z")
      tap = False
      time.sleep(0.5)

        
