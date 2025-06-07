# -*- coding:utf-8 -*-
'''!
   @file interrupt.py
   @brief Interrupt detection
   @n In this example, the enable eZHigherThanTh interrupt event means when the acceleration in the Z direction exceeds the threshold
   @n set by the program, the interrupt level can be detected on the interrupt pin int1/int2 we set, and the level change on the interrupt pin
   @n can be used to determine whether the interrupt occurs. The following are the 6 settable interrupt events:   
   @n eXHigherThanTh, eXLowerThanTh, eYHigherThanTh, eYLowerThanTh, eZHigherThanTh,eZLowerThanTh.
   @n For a detailed explanation of each of them, please look up the comments of function enableInterruptEvent()
   @n When using SPI, chip select pin can be modified by changing the value of macro RASPBERRY_PIN_CS
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

INT1 = 26                           #Interrupt pin, use BCM coding method, the code number is 26, corresponding to pin GPIO25
int_pad_Flag = False                 #intPad flag
def int_pad_callback(status):
  global int_pad_Flag
  int_pad_Flag = True

#If you want to use SPI to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via SPI port
#RASPBERRY_PIN_CS =  27              #Chip selection pin when SPI is selected, use BCM coding method, the number is 27, corresponding to pin GPIO2
#acce = DFRobot_H3LIS200DL_SPI(RASPBERRY_PIN_CS)


#If you want to use I2C to drive this module, uncomment the codes below, and connect the module with Raspberry Pi via I2C port
#The I2C address can be switched through the DIP switch (gravity version) or SDO pin (Breakout version) on the board
I2C_BUS         = 0x01            #default use I2C1
#ADDRESS_0       = 0x18            #Sensor address 0
ADDRESS_1       = 0x19            #Sensor address 1
acce = DFRobot_H3LIS200DL_I2C(I2C_BUS ,ADDRESS_1)

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
             H3LIS200DL_100G   # ±100g
             H3LIS200DL_200G   # ±200g
'''
acce.set_range(acce.H3LIS200DL_100G)

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

'''
Set the threshold of interrupt source 1 interrupt
threshold Threshold(g), the range is the set measurement range.
'''
acce.set_int1_th(5);

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
     #Check whether the interrupt event is generated in interrupt 1
     if acce.get_int1_event(acce.Y_HIGHERTHAN_TH) == True:
        print("The acceleration in the y direction is greater than the threshold")
     
     if acce.get_int1_event(acce.Z_HIGHERTHAN_TH) == True:
       print("The acceleration in the z direction is greater than the threshold")
      
     if acce.get_int1_event(acce.X_HIGHERTHAN_TH) == True:
       print("The acceleration in the x direction is greater than the threshold")
     
     int_pad_Flag = False
   #Get the acceleration in the three directions of xyz
   #The measurement range can be ±100g or ±200g, set by the set_range() function
   x,y,z = acce.read_acce_xyz()
   print("Acceleration [X = %.2f g,Y = %.2f g,Z = %.2f g]"%(x,y,z))
   time.sleep(0.1)
