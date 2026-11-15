#include "batl_ovr_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EEF10(void) {
    u16  i;
    u32  gray;
    u16  color;
    u16* mirror;

    func_801EF318();
    func_801EF180(128);
    func_801EF3B4(128);

    if (D_801463B0 < 244) {
        D_801463B0 += 4;
    }
    func_801EF47C(D_801463B0);

    if (g_InputHeld != 0) {
        for (i = 0; i < 256; i++) {
            color                    = g_BattleEffectPalette[i];
            gray                     = ((color & 0x1F) + ((color >> 5) & 0x1F) + ((color >> 10) & 0x1F)) / 3U;
            g_BattleEffectPalette[i] = (color & 0x8000) | (gray << 10) | (gray << 5) | gray;
        }
        mirror = (u16*)GAME_PALETTE_MIRROR;
        for (i = 0; i < 256; i++) {
            color     = mirror[i];
            gray      = ((color & 0x1F) + ((color >> 5) & 0x1F) + ((color >> 10) & 0x1F)) / 3U;
            mirror[i] = (color & 0x8000) | (gray << 10) | (gray << 5) | gray;
        }
        g_GfxPalettePending = 1;
        UI_SetMode(13);
        g_BattleUIStep++;
    }
}
#else
INCLUDE_ASM(func_801EEF10);
#endif
