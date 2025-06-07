# -*- coding:utf-8 -*-
'''!
   @file get_acceleration.py
   @brief Get the acceleration in x, y, and z directions, the mearsurement range is ±2g, ±4g, ±8g or ±16g, set by the setRange() function
   @n In this example, the continuous measurement mode is selected by default -- the acceleration data will be measured continuously according to the measuring rate.
   @n You can also use the single data conversion on demand mode 1. You need to select a suitable conversion mode in the setPowerMode() function                 
   @n                                                            2. Then fill in the setDataRate() function with the eSetSwTrig parameter
   @n                                                            3. Request a measurement by the demandData() function
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
#Chip soft reset
acce.soft_reset()
'''
  Set the sensor measurement range:
              RANGE_2G     #±2g
              RANGE_4G     #±4g
              RANGE_8G     #±8g
              RANGE_16G    #±16g
'''
acce.set_range(acce.RANGE_2G)
#Set whether to collect data continuously
acce.contin_refresh(True)

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
  Filter settings:
      LPF       #Low pass filter
      HPF       #High pass filter
'''
acce.set_filter_path(acce.LPF)

'''
   Set bandwidth
        RATE_DIV_2   #RATE/2 (up to RATE = 800 Hz, 400 Hz when RATE = 1600 Hz)
        RATE_DIV_4   #RATE/4 (High Power/Low power)
        RATE_DIV_10  #RATE/10 (HP/LP)
        RATE_DIV_20  # RATE/20 (HP/LP)
'''
acce.set_filter_bandwidth(acce.RATE_DIV_4)

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
acce.set_power_mode(acce.CONT_LOWPWRLOWNOISE2_14BIT);
time.sleep(0.1)

while True:
    #Request a measurement under single data conversion on demand mode.
    #acce.demand_data()
    #Get the acceleration in the three directions of xyz
    #The mearsurement range is ±2g, ±4g, ±8g or ±16g, set by the setRange() function
    time.sleep(0.3)
    x = acce.read_acc_x()
    y = acce.read_acc_y()
    z = acce.read_acc_z()
    print("Acceleration [X = %.2d mg,Y = %.2d mg,Z = %.2d mg]"%(x,y,z))
