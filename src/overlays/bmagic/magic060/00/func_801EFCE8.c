#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801EFCE8(s32 x, s32 y) {
    POLY_FT4* prim;
    u16*      u;
    u16*      v;
    s32       index;
    s32       i;

    index = g_Battle.target_selector - 3;
    v     = D_801F0B9A;
    u     = v - 1;
    i     = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        setXY4(prim, x, y, x + 12, y, x, y + 12, x + 12, y + 12);
        D_1F800004 = 0x30;
        switch (i) {
            case 0:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_FIRE] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 1:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_FROST] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 2:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_ELECTRIC] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 3:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_WIND] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 4:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_EARTH] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 5:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_HOLY] < 4) {
                    D_1F800004 = 0x80;
                }
                break;
        }
        setRGB0(prim, D_1F800004, D_1F800004, D_1F800004);
        prim->tpage = GetTPage(0, 1, 960, 256);
        prim->clut  = GetClut(0, 480);
        prim->u0    = *u;
        prim->v0    = *v;
        prim->u1    = (u8)*u + 12;
        prim->v1    = *v;
        prim->u2    = *u;
        prim->v2    = (u8)*v + 12;
        prim->u3    = (u8)*u + 12;
        prim->v3    = (u8)*v + 12;
        i++;
        x += 20;
        u += 2;
        v += 2;
        GFX_AddPrim(2, sizeof(POLY_FT4));
    } while (v < D_801F0B9A + 12);
}
#else
INCLUDE_ASM(func_801EFCE8);
#endif
