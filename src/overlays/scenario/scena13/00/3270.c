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

INCLUDE_ASM(func_801F9F18);

INCLUDE_ASM(func_801FA844);

INCLUDE_ASM(func_801FAFA0);

#include "overlays/scenario/GFX_CopyPaletteCapped.h"

/* func_801FB164 */
MATCH void Scene_RestorePalette(void) {
    s32 i;

    i = 0;
    do {
        g_GraphicsPaletteDst[i] = MEM_PTR(const volatile u16, AREA_PALETTE_ARENA)[i];
        i++;
    } while (i < 16);
    g_GfxPalettePending = (g_GfxPalettePending + 1u);
}
