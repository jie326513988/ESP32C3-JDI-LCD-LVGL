#include <RX8010SJ.h>

#define RX8010_I2C_ADDR 0x32

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

	adapter.enableFOUT(RX8010_FOUT_FREQ_1024, RX8010_FOUT_IRQ2);
}

void loop() {
	delay(10000);

	Serial.println("Turning the frequency output off for 3 seconds");
	adapter.disableFOUT();
	delay(3000);

	Serial.println("Turning back the frequency output for 10 seconds");
	adapter.enableFOUT(RX8010_FOUT_FREQ_1024, RX8010_FOUT_IRQ2);
}