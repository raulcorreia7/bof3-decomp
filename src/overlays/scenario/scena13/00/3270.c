#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F9E70(u16 phase) {
    s16 volume;
    s32 wave;

    wave   = rsin((phase - 0x4C0) >> 1);
    volume = ABS(wave) << 1;
    SpuSetVoiceVolume(0x11, volume, volume);
    SpuSetVoiceVolume(0x12, volume, volume);
    SpuSetVoiceVolume(0x13, volume, volume);
    wave   = rsin((phase - 0xCC0) >> 1);
    volume = ABS(wave) << 1;
    SpuSetVoiceVolume(0x10, volume, volume);
}
