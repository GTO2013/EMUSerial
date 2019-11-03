#ifndef EMU_FORMAT_H
#define EMU_FORMAT_H
#define EMU_VERSION1_200

const uint8_t channels[35]={1,2,3,4,5,6,7,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,255};
const int16_t divider[35]={1,1,1,1,37,2,62,62,1,1,51,20,10,1,1,51,51,51,51,2,1,16,1,32,1,2,1,128,4,1,1,1,100,10,1};

#define EMU_TYPE_UBYTE 0
#define EMU_TYPE_SBYTE 1
#define EMU_TYPE_WORD 2
#define EMU_TYPE_SWORD 3
const uint8_t typeIncoming [35]={EMU_TYPE_WORD,EMU_TYPE_WORD,EMU_TYPE_UBYTE,EMU_TYPE_SBYTE,EMU_TYPE_WORD,EMU_TYPE_SBYTE,EMU_TYPE_WORD,EMU_TYPE_WORD,EMU_TYPE_WORD,EMU_TYPE_WORD,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_SBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_SBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_SWORD,EMU_TYPE_UBYTE,EMU_TYPE_SBYTE,EMU_TYPE_UBYTE,EMU_TYPE_WORD,EMU_TYPE_WORD,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_WORD};

const void* channelMapping[35]={&emu_data.RPM,&emu_data.MAP,&emu_data.TPS,&emu_data.IAT,&emu_data.Batt,&emu_data.IgnAngle,&emu_data.pulseWidth,&emu_data.scondarypulseWidth,&emu_data.Egt1,&emu_data.Egt2,&emu_data.knockLevel,&emu_data.dwellTime,&emu_data.wboAFR,&emu_data.gear,&emu_data.Baro,&emu_data.analogIn1,&emu_data.analogIn2,&emu_data.analogIn3,&emu_data.analogIn4,&emu_data.injDC,&emu_data.emuTemp,&emu_data.oilPressure,&emu_data.oilTemperature,&emu_data.fuelPressure,&emu_data.CLT,&emu_data.flexFuelEthanolContent,&emu_data.ffTemp,&emu_data.wboLambda,&emu_data.vssSpeed,&emu_data.deltaFPR,&emu_data.fuelLevel,&emu_data.tablesSet,&emu_data.lambdaTarget,&emu_data.afrTarget,&emu_data.cel};
#endif