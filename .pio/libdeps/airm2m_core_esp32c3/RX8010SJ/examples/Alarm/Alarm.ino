#include <RX8010SJ.h>

#define RX8010_I2C_ADDR 0x32

const char * dayOfWeekStrings[] = {
  	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

RX8010SJ::Adapter adapter = RX8010SJ::Adapter(RX8010_I2C_ADDR);
RX8010SJ::DateTime defaultDateTime = RX8010SJ::DateTime();
RX8010SJ::DateTime alarmTime = RX8010SJ::DateTime();

void readDateTime() {
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
}

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

	adapter.resetModule();

	if (reset) {
		Serial.println("The adapter has been reset!");
		adapter.writeDateTime(defaultDateTime);
	}

	Serial.println("Initialised");

	alarmTime.minute = 27;
	alarmTime.hour = 15;
	alarmTime.dayOfWeek = 0b00011111;

	adapter.setAlarm(alarmTime, RX8010_ALARM_MOD_WEEK);
	adapter.enableAlarm();
}

void loop() {
	delay(10000);

	if (adapter.checkAlarm()) {
		readDateTime();
		Serial.println("Alarm triggered at 15:27 on a weekday");
	}
}