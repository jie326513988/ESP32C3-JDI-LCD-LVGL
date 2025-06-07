# -*- coding:utf-8 -*-
'''!
  @file get_acceleration.py
  @brief Get the acceleration in x, y, z directions, its measurement range can be ±6g, ±12g or ±24g 
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

from DFRobot_LIS import *
import time

#If you want to use SPI to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via SPI port
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected, use BCM coding method, the number is 27, corresponding to pin GPIO2
#acce = DFRobot_H3LIS200DL_SPI(RASPBERRY_PIN_CS)

#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port
#The I2C address can be switched through the DIP switch (gravity version) or SDO pin (Breakout version) on the board
I2C_BUS         = 0x01            #default use I2C1
#ADDRESS_0       = 0x18            #Sensor address 0
ADDRESS_1       = 0x19            #Sensor address 1
acce = DFRobot_H3LIS200DL_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())

'''
set range:Range(g)
             H3LIS200DL_100G   # ±100g
             H3LIS200DL_200G   # ±200g
'''
acce.set_range(acce.H3LIS200DL_100G)

'''
Set data measurement rate(hz)
         POWERDOWN_0HZ 
         LOWPOWER_HALFHZ 
         LOWPOWER_1HZ 
         LOWPOWER_2HZ 
         LOWPOWER_5HZ 
         LOWPOWER_10HZ 
         NORMAL_50HZ 
         NORMAL_100HZ 
         NORMAL_400HZ 
         NORMAL_1000HZ 
'''
acce.set_acquire_rate(acce.NORMAL_50HZ)
time.sleep(0.1)

while True:
    #Get the acceleration in the three directions of xyz
    #The measurement range can be ±100g or ±200g, set by the set_range() function
    x,y,z = acce.read_acce_xyz()
    print("Acceleration [X = %.2d g,Y = %.2d g,Z = %.2d g]"%(x,y,z))
    time.sleep(1)
