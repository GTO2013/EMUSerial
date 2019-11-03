Run the pythonfile if you are using a different version than 1.200 with the version.xml file (located in the ECUMaster software folder). This will update the emuStruct.h and emuFormat.h files which contain the dataformat. To save memory it makes sense to filter the values (which are buffered), see the Filter.txt file in the Preprocessor folder for this. For the available channels, see the generated emuStruct.h file.

Example:

```
#include <EMUSerial.h>
EMUSerial emu(Serial1);

void setup()
{
	Serial.begin(9600); //Debugging
	Serial1.begin(19200, SERIAL_8N1, 19, 21); //EMU Serial setup
}

void loop()
{
	emu.checkEmuSerial();
  Serial.println(emu.emu_data.RPM); //uint16_t
  Serial.println(emu.emu_data.Batt); //float  
}
 ```
 
Tested using a MAX3232CPE with an ESP32.
