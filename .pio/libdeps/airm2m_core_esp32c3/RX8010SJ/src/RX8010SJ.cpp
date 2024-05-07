#include "RX8010SJ.h"

namespace RX8010SJ {

    Adapter::Adapter(byte i2cSlaveAddr) 
	{
        i2cAddress = i2cSlaveAddr;
    }

    Adapter::~Adapter() {}

	/**
	 *
	 * PUBLIC FUNCTIONS
	 *
	 */

	/**
	 * GENERAL
	 */

	bool Adapter::initAdapter() 
	{
		//Wire.end();
		//Wire.begin(13,23);
  		//delay(40);
		return initModule();
	}

	bool Adapter::initModule()
	{
		byte flagValue = readFromModule(RX8010_FLAG); //从模块读取
		//Serial.print("flagValue:B");Serial.println(flagValue,BIN);

		byte vlf = getValueFromBinary(flagValue, RX8010_VLF_POS); //从二进制获取值
	    //Serial.print("vlf:");Serial.println(vlf);
	
		// 模块出现电源问题，需要重新初始化时为1
		if (vlf == 1)
		{
			uint8_t i = 0;
			// 振荡器需要一段时间才能稳定
			while (vlf == 1)
			{
				flagValue = setBinary(flagValue, RX8010_VLF_POS, 0);
				writeToModule(RX8010_FLAG, vlf);
				delay(10);
				flagValue = readFromModule(RX8010_FLAG);
				vlf = getValueFromBinary(flagValue, RX8010_VLF_POS);
				i++;
				if(i >= 3) return false;
			}

			resetModule();

			return true;
		}

		return false;
	}

	void Adapter::resetModule()
	 {
		writeToModule(RX8010_RESV17, RX8010_ADDR17_DEF_VAL);
		writeToModule(RX8010_RESV30, RX8010_ADDR30_DEF_VAL);
		writeToModule(RX8010_RESV31, RX8010_ADDR31_DEF_VAL);
		writeToModule(RX8010_IRQ, RX8010_IRQ_DEF_VAL);

		writeFlag(RX8010_EXT, RX8010_TE_POS, 0);
		writeFlag(RX8010_FLAG, RX8010_VLF_POS, 0);

		writeToModule(RX8010_CTRL, RX8010_CTRL_DEF_VAL);
	}

	void Adapter::toggleGlobalStop(bool stopEnabled) {
		writeFlag(RX8010_CTRL, RX8010_STOP_POS, stopEnabled ? 1 : 0);
	}

	/**
	 * DATE TIME
	 */

    DateTime Adapter::readDateTime() 
	{
		byte secondBin = readFromModule(RX8010_SEC);
		byte minuteBin = readFromModule(RX8010_MIN);
		byte hourBin = readFromModule(RX8010_HOUR);
		byte dayOfWeekBin = readFromModule(RX8010_WDAY);
		byte dayOfMonthBin = readFromModule(RX8010_MDAY);
		byte monthBin = readFromModule(RX8010_MONTH);
		byte yearBin = readFromModule(RX8010_YEAR);

		DateTime dateTime;

		dateTime.second = sumValueFromBinary(secondBin, 7);
		dateTime.minute =sumValueFromBinary(minuteBin, 7);
		dateTime.hour = sumValueFromBinary(hourBin, 6);
		dateTime.dayOfWeek = getSingleBit(dayOfWeekBin);
		dateTime.dayOfMonth = sumValueFromBinary(dayOfMonthBin, 6);
		dateTime.month = sumValueFromBinary(monthBin, 5);
		dateTime.year = sumValueFromBinary(yearBin, 8);

		return dateTime;
    }

	void Adapter::writeDateTime(DateTime dateTime) {
		byte second = dateTime.second % 10;
		byte minute = dateTime.minute % 10;
		byte hour = dateTime.hour % 10;
		byte dayOfWeek = setBinary(0, dateTime.dayOfWeek, 1);
		byte dayOfMonth = dateTime.dayOfMonth % 10;
		byte month = dateTime.month % 10;
		byte year = dateTime.year % 10;

		second = setFortyBinary(second, dateTime.second);
		second = setTwentyBinary(second, dateTime.second);
		second = setTenBinary(second, dateTime.second);

		minute = setFortyBinary(minute, dateTime.minute);
		minute = setTwentyBinary(minute, dateTime.minute);
		minute = setTenBinary(minute, dateTime.minute);

		hour = setTwentyBinary(hour, dateTime.hour);
		hour = setTenBinary(hour, dateTime.hour);

		dayOfMonth = setTwentyBinary(dayOfMonth, dateTime.dayOfMonth);
		dayOfMonth = setTenBinary(dayOfMonth, dateTime.dayOfMonth);

		month = setTenBinary(month, dateTime.month);

		year = setEightyBinary(year, dateTime.year);
		year = setFortyBinary(year, dateTime.year);
		year = setTwentyBinary(year, dateTime.year);
		year = setTenBinary(year, dateTime.year);

		writeToModule(RX8010_SEC, second);
		writeToModule(RX8010_MIN, minute);
		writeToModule(RX8010_HOUR, hour);
		writeToModule(RX8010_WDAY, dayOfWeek);
		writeToModule(RX8010_MDAY, dayOfMonth);
		writeToModule(RX8010_MONTH, month);
		writeToModule(RX8010_YEAR, year);
	}

	/**
	 * FCT
	 */

	void Adapter::setFCTCounter(uint16_t multiplier, byte frequency) {
		byte firstHalf = multiplier & 0b11111111;
		byte secondHalf = multiplier >> 8;

		writeToModule(RX8010_TCOUNT0, firstHalf);
		writeToModule(RX8010_TCOUNT1, secondHalf);

		writeFlag(RX8010_EXT, RX8010_TSEL0_POS, getValueFromBinary(frequency, RX8010_TSEL0_POS));
		writeFlag(RX8010_EXT, RX8010_TSEL1_POS, getValueFromBinary(frequency, RX8010_TSEL1_POS));
		writeFlag(RX8010_EXT, RX8010_TSEL2_POS, getValueFromBinary(frequency, RX8010_TSEL2_POS));
	}

	uint16_t Adapter::getFCTCounter() {
		byte firstHalf = readFromModule(RX8010_TCOUNT0);
		byte secondHalf = readFromModule(RX8010_TCOUNT1);

		return firstHalf + (secondHalf << 8);
	}

	void Adapter::setFCTOutput(byte pin) {
		if (pin > 1) {
			writeFlag(RX8010_CTRL, RX8010_TIE_POS, 0);
		} else {
			writeFlag(RX8010_IRQ, RX8010_TMPIN_POS, pin);
			writeFlag(RX8010_CTRL, RX8010_TIE_POS, 1);
		}
	}

	void Adapter::enableFCT() {
		writeFlag(RX8010_CTRL, RX8010_TSTP_POS, 0);
		writeFlag(RX8010_CTRL, RX8010_TIE_POS, 1);
		writeFlag(RX8010_EXT, RX8010_TE_POS, 1);
	}

	void Adapter::disableFCT() {
		writeFlag(RX8010_EXT, RX8010_TE_POS, 0);
		writeFlag(RX8010_CTRL, RX8010_TSTP_POS, 1);
	}

	bool Adapter::checkFCT() {
		byte flag = readFromModule(RX8010_FLAG);
		bool interrupted = getValueFromBinary(flag, RX8010_TF_POS) == 1;

		if (interrupted) {
			writeFlag(RX8010_FLAG, RX8010_TF_POS, 0);
		}

		return interrupted;
	}

	/**
	 * ALARM
	 */

	void Adapter::setAlarm(DateTime time, byte mode) {
		byte minute;
		byte hour;

		if (time.minute == RX8010_ALARM_IGNORE) {
			minute = RX8010_AL_DISABLED;
		} else {
			minute = time.minute % 10;
			minute = setFortyBinary(minute, time.minute);
			minute = setTwentyBinary(minute, time.minute);
			minute = setTenBinary(minute, time.minute);
		}

		if (time.hour == RX8010_ALARM_IGNORE) {
			hour = RX8010_AL_DISABLED;
		} else {
			hour = time.hour % 10;
			hour = setTwentyBinary(hour, time.hour);
			hour = setTenBinary(hour, time.hour);
		}

		writeToModule(RX8010_ALMIN, minute);
		writeToModule(RX8010_ALHOUR, hour);

		if (mode == RX8010_ALARM_MOD_WEEK) {
			writeToModule(RX8010_ALWDAY, time.dayOfWeek == RX8010_ALARM_IGNORE ? RX8010_AL_DISABLED : time.dayOfWeek);
		} else {
			byte day;

			if (time.hour == RX8010_ALARM_IGNORE) {
				day = RX8010_AL_DISABLED;
			} else {
				day = time.dayOfMonth % 10;
				day = setTwentyBinary(hour, time.hour);
				day = setTenBinary(hour, time.hour);
			}

			writeToModule(RX8010_ALWDAY, day);
		}

		writeFlag(RX8010_EXT, RX8010_WADA_POS, mode == RX8010_ALARM_MOD_WEEK ? 0 : 1);
	}

	void Adapter::enableAlarm() {
		writeFlag(RX8010_FLAG, RX8010_AF_POS, 0);
		writeFlag(RX8010_CTRL, RX8010_AIE_POS, 1);
	}

	void Adapter::disableAlarm() {
		writeFlag(RX8010_CTRL, RX8010_AIE_POS, 0);
		writeFlag(RX8010_FLAG, RX8010_AF_POS, 0);
	}

	bool Adapter::checkAlarm() {
		byte flag = readFromModule(RX8010_FLAG);
		bool triggered = getValueFromBinary(flag, RX8010_AF_POS) == 1;

		if (triggered) {
			writeFlag(RX8010_FLAG, RX8010_AF_POS, 0);
		}

		return triggered;
	}

	/**
	 * TIME UPDATE INTERRUPT
	 */

	void Adapter::setTUIMode(byte mode) {
		writeFlag(RX8010_EXT, RX8010_USEL_POS, mode);
	}

	void Adapter::enableTUI() {
		writeFlag(RX8010_CTRL, RX8010_UIE_POS, 1);
	}

	void Adapter::disableTUI() {
		writeFlag(RX8010_CTRL, RX8010_UIE_POS, 0);
	}

	bool Adapter::checkTUI() {
		byte flag = readFromModule(RX8010_FLAG);
		bool interrupted = getValueFromBinary(flag, RX8010_UF_POS) == 1;

		if (interrupted) {
			writeFlag(RX8010_FLAG, RX8010_UF_POS, 0);
		}

		return interrupted;
	}

	/**
	 * FREQUENCY OUTPUT
	 */

	void Adapter::enableFOUT(byte frequency, byte pin) {
		switch (frequency) {
			case 3:
				writeFlag(RX8010_EXT, RX8010_FSEL0_POS, 1);
				writeFlag(RX8010_EXT, RX8010_FSEL1_POS, 1);
				break;
			case 2:
				writeFlag(RX8010_EXT, RX8010_FSEL0_POS, 0);
				writeFlag(RX8010_EXT, RX8010_FSEL1_POS, 1);
				break;
			case 1:
				writeFlag(RX8010_EXT, RX8010_FSEL0_POS, 1);
				writeFlag(RX8010_EXT, RX8010_FSEL1_POS, 0);
				break;
			case 0:
			default:
				disableFOUT();
				return;
		}

		writeFlag(RX8010_IRQ, RX8010_FOPIN0_POS, pin);
		writeFlag(RX8010_IRQ, RX8010_FOPIN1_POS, 0);
	}

	void Adapter::disableFOUT() {
		writeFlag(RX8010_EXT, RX8010_FSEL0_POS, 0);
		writeFlag(RX8010_EXT, RX8010_FSEL1_POS, 0);
	}

	/**
	 *
	 * PRIVATE FUNCTIONS
	 *
	 */

	byte Adapter::readFromModule(byte address)
	{
		Wire.beginTransmission(i2cAddress);
		Wire.write(address);
		Wire.endTransmission();
		int add = i2cAddress;
		Wire.requestFrom(add, 1); // 请求发件人

		//Serial.print("i2cAddress:0X"); Serial.println(i2cAddress,HEX);
        //Serial.print("add:"); Serial.println(add);

		if (Wire.available())
		{
				/*int c = Wire.read();
				Serial.print("c:B");Serial.println(c, BIN);
				return c;*/
				return Wire.read();
		}

		return -1;
	}

	void Adapter::writeToModule(byte address, byte data) {
		Wire.beginTransmission(i2cAddress);
		Wire.write(address);
		Wire.write(data);
		Wire.endTransmission();
	}

	void Adapter::writeFlag(byte address, byte pos, byte value) {
		byte addressValue = readFromModule(address);
		addressValue = setBinary(addressValue, pos, value);
		writeToModule(address, addressValue);
	}

	byte Adapter::getSingleBit(byte binary) {
		for (byte i = 0; i <= 7; i++) {
			if (binary >> i == 1) {
				return i;
			}
		}

		return 0;
	}

	byte Adapter::getValueFromBinary(byte binary, byte pos) {
		return getValueFromBinary(binary, pos, 1);
	}

	byte Adapter::getValueFromBinary(byte binary, byte pos, byte val) 
	{
		//Serial.print("binary:");Serial.println(binary,BIN);
		//Serial.print("pos:");Serial.println(pos,BIN);
		return ((binary >> pos) & 1) == 1 ? val : 0;
	}

	byte Adapter::sumValueFromBinary(byte binary, byte length) {
		byte sum = 0;

		for (byte i = 0; i < length; i++) {
			byte value;

			if (i < 4 ) {
				value = 1 << i;
			} else {
				value = 10 * (1 << (i - 4));
			}

			sum += getValueFromBinary(binary, i, value);
		}

		return sum;
	}

	byte Adapter::setEightyBinary(byte binary, byte val) {
		if (val >= 80) {
			return setBinary(binary, 7, 1);
		}

		return setBinary(binary, 7, 0);
	}

	byte Adapter::setFortyBinary(byte binary, byte val) {
		if (val >= 40 && val < 80) {
			return setBinary(binary, 6, 1);
		}

		return setBinary(binary, 6, 0);
	}

	byte Adapter::setTwentyBinary(byte binary, byte val) {
		if ((val >= 20 && val < 40) ||
			(val >= 60 && val < 80)) {

			return setBinary(binary, 5, 1);
		}

		return setBinary(binary, 5, 0);
	}

	byte Adapter::setTenBinary(byte binary, byte val) {
		if ((val >= 10 && val < 20) ||
			(val >= 30 && val < 40) ||
			(val >= 50 && val < 60) ||
			(val >= 70 && val < 80) ||
			(val >= 90 && val < 100)) {

			return setBinary(binary, 4, 1);
		}

		return setBinary(binary, 4, 0);
	}

	byte Adapter::setBinary(byte binary, byte pos, byte flagVal) {
		if (flagVal == 1) {
			return binary | (1 << pos);
		}

		return binary & (~(1 << pos));
	}

}