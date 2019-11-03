Run the pythonfile if you are using a different version than 1.200, the version.xml file needs to be in the same folder (you can find it in the ECUMaster software folder). This will update the emuStruct.h and emuFormat.h files which contain the dataformat. To save memory it makes sense to filter the  buffered values, see the Filter.txt file in the Preprocessor folder and rerun the python script. See the generated emuStruct.h file for the available channels.

Example:

```
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
 ```
 
Tested using a MAX3232CPE with an ESP32. Only for personal (non-commerical) use!
