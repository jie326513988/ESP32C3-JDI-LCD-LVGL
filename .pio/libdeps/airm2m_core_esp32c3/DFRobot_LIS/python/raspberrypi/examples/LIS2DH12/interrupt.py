# -*- coding:utf-8 -*-
'''!
  @file interrupt.py
  @brief Interrupt detection
  @n In this example, the enable eZHigherThanTh interrupt event means when the acceleration in the Z direction exceeds the threshold we set 
  @n before, the interrupt level can be detected on the interrupt pin int1/int2 we set, and the level change on the interrupt pin 
  @n can be used to determine whether the interrupt occurs. The following are the six settable interrupt events: eXHigherThanTh, eXLowerThanTh, 
  @n eYHigherThanTh, eYLowerThanTh, eZHigherThanTh,eZLowerThanTh. For a detailed explanation of each interrupt event, please look up the 
  @n comments of function enableInterruptEvent()
  @n When using SPI, chip select pin can be modified by changing the value of macro RASPBERRY_PIN_CS
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [tangjie](jie.tang@dfrobot.com)
  @version  V1.0
  @date  2022-01-05
  @url https://github.com/DFRobot/DFRobot_LIS
'''

import sys
sys.path.append("../..") # set system path to top

from DFRobot_LIS2DH12 import *
import time

INT1 = 26                            #Interrupt pin(BCM code), use BCM coding method, the code number is 26, corresponding to pin GPIO25
int_pad_Flag = False                 #intPad flag
def int_pad_callback(status):
  global int_pad_Flag
  int_pad_Flag = True


#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port
#The I2C address can be switched through the DIP switch (gravity version) or SDO pin (Breakout version) on the board
I2C_BUS         = 0x01            #default use I2C1
ADDRESS_0       = 0x18            #sensor address0
acce = DFRobot_LIS2DH12(I2C_BUS ,ADDRESS_0)

# set int_Pad to input
GPIO.setup(INT1, GPIO.IN)
#set int_Pad interrupt callback
GPIO.add_event_detect(INT1,GPIO.RISING,int_pad_callback)

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

'''
Set the threshold of interrupt source 1 interrupt
threshold Threshold(g), the range is the set measurement range. 
'''
acce.set_int1_th(2)

'''
Enable interrupt
Interrupt pin selection
         INT_1 = 0,/<int pad 1 >/
         INT_2,/<int pad 2>/
Interrupt event selection
             X_LOWERTHAN_TH     = 0x1<The acceleration in the x direction is less than the threshold>
             X_HIGHERTHAN_TH  = 0x2<The acceleration in the x direction is greater than the threshold>
             Y_LOWERTHAN_TH     = 0x4<The acceleration in the y direction is less than the threshold>
             Y_HIGHERTHAN_TH  = 0x8<The acceleration in the y direction is greater than the threshold>
             Z_LOWERTHAN_TH     = 0x10<The acceleration in the z direction is less than the threshold
             Z_HIGHERTHAN_TH  = 0x20<The acceleration in the z direction is greater than the threshold>
             EVENT_ERROR      = 0 <No event>
'''
acce.enable_int_event(acce.INT_1,acce.Z_HIGHERTHAN_TH)
time.sleep(1)

while True:
    
    if(int_pad_Flag == True):
      #Check whether the interrupt event'source' is generated in interrupt 1
      if acce.get_int1_event(acce.Z_HIGHERTHAN_TH) == True:
        print("The acceleration in the z direction is greater than the threshold")
      int_pad_Flag = False
    #Get the acceleration in the three directions of xyz
    
    x = acce.read_acc_x()
    y = acce.read_acc_y()
    z = acce.read_acc_z()
    print("Acceleration [X = %.2d mg,Y = %.2d mg,Z = %.2d mg]"%(x,y,z))
    
    time.sleep(0.1)
