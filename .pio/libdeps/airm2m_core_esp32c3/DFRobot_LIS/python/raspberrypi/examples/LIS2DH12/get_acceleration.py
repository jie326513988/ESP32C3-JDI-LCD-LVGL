# -*- coding:utf-8 -*-
'''!
  @file getAcceleration.py
  @brief Get the acceleration in the three directions of xyz, the range can be
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [tangjie](jie.tang@dfrobot.com)
  @version  V1.0
  @date  2021-01-16
  @url https://github.com/DFRobot/DFRobot_LIS
'''

import sys
sys.path.append("../..") # set system path to top
from DFRobot_LIS2DH12 import *
import time


#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port.
I2C_BUS         = 0x01            #default use I2C1
ADDRESS_0       = 0x18            #Sensor address0
acce = DFRobot_LIS2DH12(I2C_BUS ,ADDRESS_0)

#Chip initialization
acce.begin()
#Get chip id
print('chip id :%x'%acce.get_id())

'''
set range:Range(g)
        LIS2DH12_2g = 0x00
        LIS2DH12_4g = 0x10
        LIS2DH12_8g = 0x20
        LIS2DH12_16g = 0x30
'''
acce.set_range(acce.LIS2DH12_16g)

'''
Set data measurement rate
        POWERDOWN_0HZ  = 0X00
        LOWPOWER_1Hz   = 0x10
        LOWPOWER_10Hz  = 0x20
        LOWPOWER_25Hz  = 0x30
        LOWPOWER_50Hz  = 0x40
        LOWPOWER_100Hz = 0x50
        LOWPOWER_200Hz = 0x60
        LOWPOWER_400Hz = 0x70 
'''
acce.set_acquire_rate(acce.LOWPOWER_10Hz)
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