#include "batl_ovr_00.h"

MATCH void func_801EF3B4(s32 shade) {
    SPRT* sprt;

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 0x340, 0x100));

    sprt       = (SPRT*)g_GfxPrimCursor;
    sprt->clut = GetClut(0, 0x1FA);
    setXY0(sprt, 0x4C, 0x30);
    sprt->w = 0xA8;
    setRGB0(sprt, shade, shade, shade);
    setUV0(sprt, 0, 0);
    sprt->h = 0x18;
    SetSprt(sprt);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
}
