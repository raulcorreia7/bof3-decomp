#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801EFCE8(s32 x, s32 y) {
    POLY_FT4*     prim;
    u16*          uv_left;
    u16*          uv_right;
    u16*          uv_end;
    u16*          uv_start;
    volatile s32* color;
    u8*           state;
    s32           selector;

    selector = g_Battle.target_selector - 3;
    state    = g_BattleEnemyBattlers[selector].stats.resistances;
    uv_start = (u16*)(D_801F0B8C + 14);
    uv_right = uv_start;
    uv_left  = uv_right - 1;
    uv_end   = (u16*)((u8*)g_BMagicEffectModes + 2);
    color    = (volatile s32*)&g_ScratchPad.cells.words[1];

    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        prim->y2 = y + 12;
        prim->y3 = y + 12;
        setXY2(prim, x, y, x + 12, y);
        prim->x2 = x;
        prim->x3 = x + 12;

        *color = 0x30;
        if ((u32)uv_right < (u32)uv_end) {
            switch (uv_right - uv_start) {
                case 0:
                    if (state[0] < 2)
                        *color = 0x80;
                    break;
                case 2:
                    if (state[1] < 2)
                        *color = 0x80;
                    break;
                case 4:
                    if (state[2] < 2)
                        *color = 0x80;
                    break;
                case 6:
                    if (state[3] < 2)
                        *color = 0x80;
                    break;
                case 8:
                    if (state[4] < 2)
                        *color = 0x80;
                    break;
                case 10:
                    if (state[5] < 4)
                        *color = 0x80;
                    break;
            }
        }

        setRGB0(prim, *color, *color, *color);
        prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x3C0, 0x100);
        prim->clut  = GetClut(0, 0x1E0);
        setUV4(prim, *uv_left, *uv_right, *uv_left + 12, *uv_right, *uv_left, *uv_right + 12, *uv_left + 12, *uv_right + 12);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
        x += 20;
        uv_left += 2;
        uv_right += 2;
    } while ((s32)uv_right < (s32)uv_end);
}
#else
INCLUDE_ASM(func_801EFCE8);
#endif
