#include "battle_03.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 28.57%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D9E9C(s16 arg0, s16 arg1, u16 arg2, u16 arg3, s8 arg4) {
    s16       tmp0;
    s16       tmp1;
    s16       tmp2;
    s16       tmp3;
    s16       tmp4;
    s16       val0;
    s16       val1;
    s32       val2;
    s8        val3;
    s8        val4;
    u16       val5;
    u16       val6;
    POLY_FT4* val7;
    u8        val8;

    val7 = (POLY_FT4*)g_GfxPrimCursor;
    val8 = (u8)arg4;
    val1 = arg0;
    val0 = arg1;
    val5 = arg2;
    val6 = arg3;
    SetPolyFT4(val7);
    val7->tpage = GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    val2        = 0xB0;
    if (val8 == 0) {
        val2 = 0xE0;
    }
    val7->clut = GetClut(val2, 480);
    val3       = 0x80;
    tmp2       = val1 + (val5 & BYTE_MASK);
    tmp4       = val0 + 7;
    val7->r0   = 0x80;
    val7->g0   = 0x80;
    val7->b0   = 0x80;
    val7->x0   = val1;
    val7->y0   = val0;
    val7->x1   = tmp2;
    val7->y1   = val0;
    val7->x2   = val1;
    val7->y2   = tmp4;
    val7->x3   = tmp2;
    val7->y3   = tmp4;
    if (val8 == 0) {
        val3 = 0x90;
        val4 = 0x97;
    } else {
        val4 = 0x87;
    }
    val7->v0 = 216;
    val7->v1 = 216;
    val7->u0 = val3;
    val7->u1 = val4;
    val7->u2 = val3;
    val7->v2 = 223;
    val7->u3 = val4;
    val7->v3 = 223;
    GFX_AddPrim(1U, 0x28U);
    val7 = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(val7);
    val7->tpage = GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    val7->clut  = GetClut(176, 480);
    val7->r0    = 0x80;
    val7->g0    = 0x80;
    val7->b0    = 0x80;
    tmp0        = val1 + (val5 & BYTE_MASK);
    tmp3        = (val6 & BYTE_MASK) + tmp0;
    val7->x0    = tmp0;
    val7->x2    = tmp0;
    tmp1        = val0 + 7;
    val7->y2    = tmp1;
    val7->y3    = tmp1;
    val7->x1    = tmp3;
    val7->x3    = tmp3;
    val7->v0    = 216;
    val7->v1    = 216;
    val7->y0    = val0;
    val7->y1    = val0;
    val7->u0    = 152;
    val7->u1    = 159;
    val7->u2    = 152;
    val7->v2    = 223;
    val7->u3    = 159;
    val7->v3    = 223;
    GFX_AddPrim(1U, 0x28U);
}
#else
INCLUDE_ASM(func_801D9E9C);
#endif
