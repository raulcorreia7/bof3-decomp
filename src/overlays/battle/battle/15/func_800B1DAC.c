#include "battle_15.h"

MATCH void func_800B1DAC(s16 x, s16 y, u8 sprite_arg) {
    SPRT* sprt;

    GFX_AddDrawMode(GetTPage(0, 1, 832, 256) & HALF_MASK);
    sprt = (SPRT*)g_GfxPrimCursor;
    setClut(sprt, s_BattleAbilityIcon[sprite_arg] * 16, STAGE_PALETTE_Y + 26);
    setRGB0(sprt, 128, 128, 128);
    setXY0(sprt, x, y);
    setUV0(sprt, (s_BattleAbilityIcon[sprite_arg] % 6) * 40, (s_BattleAbilityIcon[sprite_arg] / 6) * 24);
    setWH(sprt, 40, 24);
    SetSprt(sprt);
    GFX_AddPrim(1U, sizeof(SPRT));
}
