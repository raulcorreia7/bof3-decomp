#include "batl_ovr_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EEF10(void) {
    u16* fade;
    u16* mirror;
    u8*  step;
    u16  value;
    u16  i;
    u16  index16;
    u32  gray;
    u16  color;

    func_801EF318();
    func_801EF180(128);
    func_801EF3B4(128);

    fade = &D_801463B0;
    if (*fade < 244) {
        *fade += 4;
    }
    func_801EF47C(*fade);

    if (g_PadStates[0].held != 0) {
        /* Retail addresses the palette as a constant (lui/ori), not a symbol low half. */
        for (i = 0; i < AREA_PALETTE_COLORS; i++) {
            index16                           = i;
            color                             = MEM_PTR(u16, 0x8003AC00)[index16];
            gray                              = (PSX_COLOR_R(color) + PSX_COLOR_G(color) + PSX_COLOR_B(color)) / 3U;
            value                             = (color & PSX_COLOR_STP_BIT) | (gray << 10) | (gray << 5) | gray;
            MEM_PTR(u16, 0x8003AC00)[index16] = value;
        }
        i      = 0;
        mirror = GAME_PALETTE_MIRROR_U16;
        for (; i < AREA_PALETTE_COLORS; i++) {
            color     = mirror[i];
            gray      = (PSX_COLOR_R(color) + PSX_COLOR_G(color) + PSX_COLOR_B(color)) / 3U;
            value     = (color & PSX_COLOR_STP_BIT) | (gray << 10) | (gray << 5) | gray;
            mirror[i] = value;
        }
        g_GfxPalettePending = 1;
        UI_ModeSet(UI_MODE_LONG_FADE_OUT);
        step = &g_BattleUIStep;
        (*step)++;
    }
}
#else
INCLUDE_ASM(func_801EEF10);
#endif
