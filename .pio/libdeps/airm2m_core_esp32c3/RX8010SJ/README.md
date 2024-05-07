# RX8010SJ

- [RX8010SJ](#rx8010sj)
- [Introduction](#introduction)
	- [How to use it?](#how-to-use-it)
	- [API](#api)
		- [Adapter - Methods](#adapter---methods)
			- [General](#general)
			- [Date time](#date-time)
			- [Fixed cycle timer (FCT)](#fixed-cycle-timer-fct)
			- [Alarm](#alarm)
			- [Time update interrupt (TUI)](#time-update-interrupt-tui)
			- [Frequency output (FOUT)](#frequency-output-fout)
		- [DateTime - Attributes](#datetime---attributes)
	- [Examples](#examples)
	- [Missing elements.](#missing-elements)

# Introduction

This is a library to handle Seiko's RX8010SJ RTC module with an arduino. Original datasheet can be found [here](files/RX8010SJ.pdf). To set up your module, you only need to power up and use the i2c protocol to communicate with it. You have to provide the slave address to the constructor to start the communication. As many other i2c devices, this one also needs pull up resistors on the communication ports. (I'm using 5K, but 10K or 1K should be also good) The library is using the built-in "Wire" library to send and receive messages.

## How to use it?

The current version only has methods for setting and retrieving date-time, implementing all the other features is still in progress. With the following code, you can get the current time at every second:

```c
#include <RX8010SJ.h>

#define RX8010_I2C_ADDR 0x32

const char * dayOfWeekStrings[] = {
  	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

RX8010SJ::Adapter adapter = RX8010SJ::Adapter(RX8010_I2C_ADDR);
RX8010SJ::DateTime defaultDateTime = RX8010SJ::DateTime();

void setup() {
	defaultDateTime.second = 5;
	defaultDateTime.minute = 25;
	defaultDateTime.hour = 15;
	defaultDateTime.dayOfWeek = 5;
	defaultDateTime.dayOfMonth = 18;
	defaultDateTime.month = 7;
	defaultDateTime.year = 20;

	Serial.begin(9600);
	bool reset = adapter.initAdapter();

	if (reset) {
		Serial.println("The adapter has been reset!");
		adapter.writeDateTime(defaultDateTime);
	}

	Serial.println("Initialised");
}

void loop() {
	RX8010SJ::DateTime dateTime = adapter.readDateTime();

	Serial.println("-------------------------------");
	Serial.print("20");
	Serial.print(dateTime.year);
	Serial.print("-");
	Serial.print(dateTime.month);
	Serial.print("-");
	Serial.print(dateTime.dayOfMonth);
	Serial.print(" (");
	Serial.print(dayOfWeekStrings[dateTime.dayOfWeek]);
	Serial.print(") ");
	Serial.print(dateTime.hour);
	Serial.print(":");
	Serial.print(dateTime.minute);
	Serial.print(":");
	Serial.println(dateTime.second);
	Serial.println("-------------------------------");

	delay(1000);
}
```

## API

There are two main objects that can be used in this library: The Adapter class and the DateTime struct. The adapter instance will take care of the communications and the DateTime struct is storing the time data.

### Adapter - Methods


#### General

- __void Constructor(byte i2cSlaveAddr)__: When you create an instance, you have to pass the slave address as a parameter, so the initialisation can open an i2c connection.
- __bool initAdapter(void)__: You have to call this method before you can start using the library, because it will setup the i2c communication library. It will also call the initModule method, so you don't have to do it separately and it returns with the initModule's return value.
- __bool initModule(void)__: This method will initialise the RX8010SJ if needed. Firstly it checks the VLF flag and if the oscillator had issue, then it will wait arbitrary amount of time until the module restart itself and then it call the resetModule method to clear any invalid state. In this case any predefined time values or setting flags will be reset to default. This method will return with a bool depending on the state of the VLF flag. If the module needed to execute a software reset, then it returns true. (recommended to check the outcome and if needed, setup the module with the desired values afterwards)

#### Date time

- __DateTime readDateTime(void)__: This method will read the module and returns with the current state of the clock. DateTime is a struct which is holding date and time related values. For more details about it's attributes, check the DateTime documentation bellow.
- __void writeDateTime(DateTime dateTime)__: You can set or update the time with calling this method. The input parameter is a custom DateTime struct instance. For more details about it's attributes, check the DateTime documentation bellow.

#### Fixed cycle timer (FCT)

- __void setFCTCounter(uint16_t multiplier, byte frequency)__: You can set the fixed cycle's length with this function. The multiplier is a maximum 2 byte long number and the frequency can be the following 5 values decoded in a binary form: 4096(0b000), 64(0b001), 1(0b010), 1/60(0b011), 1/3600(0b100).The header file contains shortcut constants for the frequency values:
  - ```RX8010_FCT_FREQ_4096```: 4096Hz
  - ```RX8010_FCT_FREQ_64```: 64Hz
  - ```RX8010_FCT_FREQ_1```: 1Hz
  - ```RX8010_FCT_FREQ_1_60```: 1/60Hz
  - ```RX8010_FCT_FREQ_1_3600```: 1/3600 Hz
Example values: multiplier 3 and the frequency is RX8010_FCT_FREQ_1 (0b010). With these value the fixed cycle will be 3 seconds long. The minimum cycle length is 244.14 μs and the longest cycle is 65535 hours.
- __uint16_t getFCTCounter()__: You can retrieve the current counter value with this method.
- __void setFCTOutput(byte pin)__: Both IRQ pins can be used to output the FCT signal and you can change the output pin with this method. Value 1 is IRQ1, value 0 is IRQ2 and any value greater than 1 will turn off the output. There are shortcut constants for the pin selection:
  - ```RX8010_FCT_OUT_IRQ1``` (0b01)
  - ```RX8010_FCT_OUT_IRQ2``` (0b00)
  - ```RX8010_FCT_OUT_OFF``` (0b10)
- __void enableFCT()__: Enable and start the fixed cycle counter with the previously assigned parameters. You should set up the counter before call this method!
- __void disableFCT()__: This function will stop the fixed ccycle counter. Important! It won't reset anything, so you can resume thos counter any time with the enableFCT() function.
- __bool checkFCT()__: Check if the fixed cycle counter has been triggered or not. If you check the module and a trigger occured, this function will reset the flag in the register, so the next end of cycle can be detected

#### Alarm

- __void setAlarm(DateTime time, byte mode)__: This method will set the alarm timer's registers. The first parameter's type is a custom struct with generic time related attributes (only the minutes, hours and dayOfWeek or dayOfMonth attributes are used in this method) and the second parameter determines the switch between the dayOfWeek or dayOfMonth type of alarm. If any of the previously mentioned attribute's value equals with ```RX8010_ALARM_IGNORE``` constant's value (0b11111111) then that attribute will be ignored. For example if you gave the ```RX8010_ALARM_IGNORE``` value to the hour attribute and the minute is 42 then during the triggered day (or on every day if you also give the same value to the dayOfWeek or dayOfMonth attribute) the clock module will turn on the alarm hourly at 42 minutes. The mode parameter determines the way how you handle the days in the alarm. If the value is 0 then the given dayOfMonth will be the trigger for the alarm and it will only acticate on the given day. If the value is 1 then dayOfWeek value is used and you can give one or more days per week to trigger the alarm. For example if you want to set your alarm to signal on every weekday at 8:42 then you have to set the following values: time.minute = 42, time.hours = 8, time.dayOfWeek = 0b00011111 (which is 31 decimaly) and finaly assigning mode to 1. The module is unable to mix the two day types, so it's not part of the API. The following shortcut constants are available for this method:
  - ```RX8010_ALARM_IGNORE```: (0b11111111) The given attribute's value will be ignored in the alarm
  - ```RX8010_ALARM_MOD_MONTH```: (0b0) Proceed with the dayOfMonth value and dayOfWeek is ignored
  - ```RX8010_ALARM_MOD_WEEK```: (0b1) Proceed with the dayOfWeek value and dayOfMonth is ignored
- __void enableAlarm()__: This method will enable the alarm's trigger. When the set time combination is reached the IRQ1 output will be triggered.
- __void disableAlarm()__: This will disable the alarm's trigger and no longer updates the IRQ1 output on the given alarm time.
- __bool checkAlarm()__: This method will check the alarm's register flag and if the alarm is occured since the last check it will reset the flag and returns with a true value.

#### Time update interrupt (TUI)

- __void setTUIMode(bool minute)__: This method will change the time update interrupt's mode. If the given value is zero then it will update once per every second, if it's 1 then once per every minute. These values also has shortcuts:
  - ```RX8010_TUI_MOD_SEC```: Update once per every second
  - ```RX8010_TUI_MOD_MIN```: Update once per every minute
- __void enableTUI()__: This method will enable this interrupt and after the time update event it will trigger the IRQ1 output.
- __void disableTUI()__: Calling this method will stop the update event and the IRQ1 output is free to use for other triggers.
- __bool checkTUI()__: This method will check the interrupt's register flag and if the update event is occured since the last check it will reset the flag and returns with a true value.

#### Frequency output (FOUT)

- __void enableFOUT(byte frequency, byte pin)__: This is a relatively straightforward function, it will generate an output trigger after certain amount of time using the clock's frequency generator. The available frequencies on the IRQ1 pin are the following: 1Hz, 1024Hz and 32768Hz and on the IRQ2 pin: 1Hz and 1024Hz. (the last resolution is not available for this pin) The frequency values are the following: frequency off = 0, 1Hz = 1, 1024Hz = 2 and 32768Hz = 3. The output pins are the following: IRQ1 = 1 and IRQ2 = 0. The following shortcut constants are available for this method:
  - ```RX8010_FOUT_FREQ_OFF``` (0b00)
  - ```RX8010_FOUT_FREQ_1``` (0b01)
  - ```RX8010_FOUT_FREQ_1024``` (0b10)
  - ```RX8010_FOUT_FREQ_32768``` (0b11)
  - ```RX8010_FOUT_IRQ1``` (0b01)
  - ```RX8010_FOUT_IRQ2``` (0b00)
- __void disableFOUT()__: This function will disable the output signal.

### DateTime - Attributes

- __byte second__: A number type attribute which is storing the second part of the time. Valid values are: 0-59
- __byte minute__: A number type attribute which is storing the minute part of the time. Valid values are: 0-59
- __byte hour__: A number type attribute which is storing the hour part of the time. Valid values are: 0-23
- __byte dayOfWeek__: A number type attribute which is storing the day of the week. You have to update this value, when you are changing the date, because the module handles those two informations independently. Valid values are: 0-6
- __byte dayOfMonth__: A number type attribute which is storing the day of the selected month. Depending on the year value it is capable of calculating and using leap days. Valid values are: 0-31
- __byte month__: A number type attribute which is storing the month part of the date. This attribute is starts from 1. Valid values are: 1-12
- __byte year__: A number type attribute which is storing the year part of the date. This value is only 2 digit long and every four year count as a leap year. Valid values are: 0-99


## Examples

You can find examples for each and every major function under the [examples](/examples) folder. The attached datasheet also has some low level examples and more detailed descriptions of these functions. I tried to simplify the usage and hide the more complex logic, so everyone can easily use these modules. If you have any questions or you are curious about one of the behaviours, then just send me a message or open a ticket and I try to respond as soon as possible.

## Missing elements.

This module also capable of storing some informations in it's registers like a static ram. (you can even use the alarm register bytes to store some values if you won't use that function) It's not implemented, because the amount of storage that we can gain from those registers is just smaller than the amount of bytes that we would loose implementing those features. However if you still think that it's good idea to store your informations there, then you can directly connect with the wire library to the module and read/write to those parts of the clock. You can find the extra memory addresses between 0x20 and 0x2F which immediately usable after the init function is executed.