# EmuSerial
This library allows you to read the ECUMaster serial stream with an Arduino. It contains a Python script to keep it up-to-date with recent versions.

**Important: You will need an RS232 to TTL converter which converts the 15V RS232 signals from the EMU into 5V TTL levels. If you connect the serial line from the EMU directly, you can destroy the Arduino.**

**Tested using a MAX3232CPE converter with an ESP32.**

For CAN communication you can use the EMUcan library: https://github.com/designer2k2/EMUcan

## Setup
This library can easily be installed via the Arduino Boardmanager.

Run the Python script in the **/extras** folder if you are using a different version than 1.200. The script takes the **version.xml** file from the ECUMaster software and create the **emuStruct.h** and **emuFormat.h** files. You need to copy the **version.xml** file into the same folder before you run the script. The Python script (hopefully) makes this library maintenance free.

To save memory it makes sense to filter the buffered values, see the **Filter.txt** file in the **/extras** folder before you run the script.


## Example
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
	
	Serial.println(emu.emu_data.RPM);  //uint16_t
	Serial.println(emu.emu_data.Batt);  //float  
}
 ```
 
## Channels
See the generated emuStruct.h file for the available channels. The following channels that are available for 1.200 without any filtering:

 ```
 struct emu_data_t {
	uint16_t RPM;  //RPM
	uint16_t MAP;  //kPa
	uint8_t TPS;  //%
	int8_t IAT;  //C
	float Batt;  //V
	float IgnAngle;  //deg
	float pulseWidth;  //ms
	float scondarypulseWidth;  //ms
	uint16_t Egt1;  //C
	uint16_t Egt2;  //C
	float knockLevel;  //V
	float dwellTime;  //ms
	float wboAFR;  //AFR
	int8_t gear;  //
	uint8_t Baro;  //kPa
	float analogIn1;  //V
	float analogIn2;  //V
	float analogIn3;  //V
	float analogIn4;  //V
	float injDC;  //%
	int8_t emuTemp;  //C
	float oilPressure;  //Bar
	uint8_t oilTemperature;  //C
	float fuelPressure;  //Bar
	int16_t CLT;  //C
	float flexFuelEthanolContent;  //%
	int8_t ffTemp;  //C
	float wboLambda;  //λ
	float vssSpeed;  //km/h
	uint16_t deltaFPR;  //kPa
	uint8_t fuelLevel;  //%
	uint8_t tablesSet;  //
	float lambdaTarget;  //λ
	float afrTarget;  //AFR
	uint16_t cel;  //
}; 
```