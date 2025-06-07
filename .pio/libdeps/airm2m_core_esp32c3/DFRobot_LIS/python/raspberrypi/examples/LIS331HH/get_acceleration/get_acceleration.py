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

#If you want to use SPI to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via SPI port.
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected, use BCM coding method, the number is 27, corresponding to pin GPIO2
#acce = DFRobot_LIS331HH_SPI(RASPBERRY_PIN_CS)


#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port.
I2C_BUS         = 0x01            #default use I2C1
#ADDRESS_0       = 0x18            #Sensor address0
ADDRESS_1       = 0x19            #Sensor address1
acce = DFRobot_LIS331HH_I2C(I2C_BUS ,ADDRESS_1)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())

'''
set range:Range(g)
          LIS331HH_6G  = 6   #±6G
          LIS331HH_12G = 12  #±12G
          LIS331HH_24G = 24  #±24G
'''
acce.set_range(acce.LIS331HH_6G)

'''
Set data measurement rate
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
    #The measurement range can be ±6g, ±12g or ±24g, set by set_range() function
    x,y,z = acce.read_acce_xyz()
    print("Acceleration [X = %.2d mg,Y = %.2d mg,Z = %.2d mg]"%(x,y,z))
    time.sleep(1)
