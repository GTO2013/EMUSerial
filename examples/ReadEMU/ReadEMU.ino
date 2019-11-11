#include <EMUSerial.h>
EMUSerial emu(Serial1);

void setup()
{
	Serial.begin(9600); //Debugging
	Serial1.begin(19200, SERIAL_8N1, 19, 21); //EMU Serial setup, 8 Data Bits 1 Stopbit, RX Pin, TX Pin
}

void loop()
{
	emu.checkEmuSerial();

	Serial.println(emu.emu_data.RPM); //uint16_t
	Serial.println(emu.emu_data.Batt); //float  
}