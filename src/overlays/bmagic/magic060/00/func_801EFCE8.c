#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
/* Draws the targeted enemy's resistance bar: one 12x12 textured segment per element. */
NON_MATCHING void func_801EFCE8(s32 x, s32 y) {
    POLY_FT4* prim;
    u16*      uv_left;
    u16*      uv_right;
    s32       selector;
    s32       i;

    selector = g_Battle.target_selector - 3;
    uv_right = (u16*)(D_801F0B8C + 14);
    uv_left  = uv_right - 1;
    i        = 0;
    do {
        prim = GFX_CURSOR(POLY_FT4);
        SetPolyFT4(prim);
        setXYWH(prim, x, y, 12, 12);
        g_ScratchPad.cells.words[1] = 0x30;
        switch (i) {
            case 0:
                if (g_BattleEnemyBattlers[selector].stats.resistances[RES_INDEX_FIRE] < 2) {
                    g_ScratchPad.cells.words[1] = 0x80;
                }
                break;
            case 1:
                if (g_BattleEnemyBattlers[selector].stats.resistances[RES_INDEX_FROST] < 2) {
                    g_ScratchPad.cells.words[1] = 0x80;
                }
                break;
            case 2:
                if (g_BattleEnemyBattlers[selector].stats.resistances[RES_INDEX_ELECTRIC] < 2) {
                    g_ScratchPad.cells.words[1] = 0x80;
                }
                break;
            case 3:
                if (g_BattleEnemyBattlers[selector].stats.resistances[RES_INDEX_WIND] < 2) {
                    g_ScratchPad.cells.words[1] = 0x80;
                }
                break;
            case 4:
                if (g_BattleEnemyBattlers[selector].stats.resistances[RES_INDEX_EARTH] < 2) {
                    g_ScratchPad.cells.words[1] = 0x80;
                }
                break;
            case 5:
                if (g_BattleEnemyBattlers[selector].stats.resistances[RES_INDEX_HOLY] < 4) {
                    g_ScratchPad.cells.words[1] = 0x80;
                }
                break;
        }
        setRGB0(prim, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1]);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x3C0, 0x100);
        prim->clut  = GetClut(0, 0x1E0);
        setUV4(prim, *uv_left, *uv_right, *uv_left + 12, *uv_right, *uv_left, *uv_right + 12, *uv_left + 12, *uv_right + 12);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
        x += 20;
        uv_left += 2;
        uv_right += 2;
        i++;
    } while (i < 6);
}
#else
INCLUDE_ASM(func_801EFCE8);
#endif
