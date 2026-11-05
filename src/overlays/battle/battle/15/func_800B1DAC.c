#include "battle_15.h"

MATCH void func_800B1DAC(s16 x, s16 y, u8 sprite_arg) {
    SPRT* sprt;

    GFX_AddDrawMode(GetTPage(0, 1, 832, 256) & HALF_MASK);
    sprt       = (SPRT*)g_GfxPrimCursor;
    sprt->clut = GetClut(s_BattleAbilityIcon[sprite_arg] * 16, 506);
    PSX_SET_NEUTRAL_RGB(sprt);
    setXY0(sprt, x, y);
    sprt->u0 = (s_BattleAbilityIcon[sprite_arg] % 6) * 40;
    sprt->v0 = (s_BattleAbilityIcon[sprite_arg] / 6) * 24;
    setWH(sprt, 40, 24);
    SetSprt(sprt);
    GFX_AddPrim(1U, 0x14U);
}
