#include <RX8010SJ.h>

#define RX8010_I2C_ADDR 0x32

const char * dayOfWeekStrings[] = {
  	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

RX8010SJ::Adapter adapter = RX8010SJ::Adapter(RX8010_I2C_ADDR);
RX8010SJ::DateTime defaultDateTime = RX8010SJ::DateTime();

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

	if (reset) {
		Serial.println("The adapter has been reset!");
		adapter.writeDateTime(defaultDateTime);
	}

	adapter.disableFCT();
	adapter.setFCTOutput(RX8010_FCT_OUT_IRQ2);
	adapter.setFCTCounter(1, RX8010_FCT_FREQ_1_60); // 1 minutes
	adapter.enableFCT();

	Serial.println("Initialised");
}

void loop() {
	delay(500);

	bool interrupted = adapter.checkFCT();

	if (interrupted) {
		Serial.println("1 minute passed");
		readDateTime();
	}
}