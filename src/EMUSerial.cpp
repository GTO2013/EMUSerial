#include "EMUSerial.h"

EMUSerial::EMUSerial(Stream& stream) {
	serial = &stream;
}

void EMUSerial::checkEmuSerial() {
	while (serial->available()) {
		//Move stream of bytes from bottom of frame upwards
		//Once magic numbers aligns --> everything received
		memmove(&currentFrame, ((uint8_t*)&currentFrame) + 1, sizeof(currentFrame) - 1);
		currentFrame.checksum = serial->read(); //checksum --> last byte

		if (currentFrame.magic == EMUSERIAL_MAGIC) {
			//Calc own checksum
			uint8_t checksum = currentFrame.channel + currentFrame.magic + currentFrame.valueH + currentFrame.valueL;

			//Compare to what we received
			if (currentFrame.checksum == checksum) decodeEmuFrame(currentFrame);
		}
	}
}

bool EMUSerial::decodeEmuFrame(const struct emu_frame &frame) {
	int index = -1;

	//Find array index for channel and mapping
	for (int i = 0; i < sizeof(channels) / sizeof(channels[0]); i++) {
		if (channels[i] == frame.channel) {
			index = i;
			break;
		}
	}

	//Firmware on emu != Firmware in format file?
	if (index == -1) return false;

	//Map channel to struct "index"
	const void* p = channelMapping[index];

	int16_t div = divider[index];
	uint8_t stor = typeIncoming[index];

	//Integer values
	if (div == 1) {
		if (stor == EMU_TYPE_UBYTE) *((uint8_t*)p) = frame.valueL;
		else if (stor == EMU_TYPE_SBYTE) *((int8_t*)p) = (int8_t)frame.valueL;
		else if (stor == EMU_TYPE_WORD) *((uint16_t*)p) = ((uint16_t)(frame.valueH) << 8) | frame.valueL;
		else if (stor == EMU_TYPE_SWORD) *((int16_t*)p) = ((int16_t)(frame.valueH) << 8) | frame.valueL;
	}

	//Floats
	else {
		if (stor == EMU_TYPE_UBYTE) *((float*)p) = (float)(frame.valueL) / div;
		else if (stor == EMU_TYPE_SBYTE) *((float*)p) = (float)((int8_t)frame.valueL) / div;
		else if (stor == EMU_TYPE_WORD) *((float*)p) = (float)(((uint16_t)(frame.valueH) << 8) | frame.valueL) / div;
		else if (stor == EMU_TYPE_SWORD) *((float*)p) = (float)(((int16_t)(frame.valueH) << 8) | frame.valueL) / div;
	}

	return true;
}



