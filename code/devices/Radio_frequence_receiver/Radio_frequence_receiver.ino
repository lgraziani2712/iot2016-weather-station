#include <VirtualWire.h>

int rfDigPin = 6;
int led13Pin = 13;

void receiverRFSetup()
{
	// Required for DR3100
	vw_set_ptt_inverted(true);
	vw_set_rx_pin(rfDigPin);
	// Bits per sec
	vw_setup(4000);
	// Start the receiver PLL running
	vw_rx_start();
}
void receiverRFLoop()
{
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	// Non-blocking
	if (vw_get_message(buf, &buflen))
	{
		Serial.print("Got: ");
		for (int i = 0; i < buflen; i++)
		{
			int a = buf[i];
			char c = a;
			Serial.print(c);
		}
		Serial.println("");
	}
}

void setup()
{
	Serial.begin(9600);
	pinMode(led13Pin, OUTPUT);
	receiverRFSetup();
}

void loop()
{
	receiverRFLoop();
}
