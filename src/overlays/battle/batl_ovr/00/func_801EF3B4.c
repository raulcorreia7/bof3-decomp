#include "batl_ovr_00.h"

MATCH void func_801EF3B4(s32 shade) {
    SPRT* sprt;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(1, 0, 0x340, 0x100), 0);
    GFX_AddPrim(2, sizeof(DR_MODE));

    sprt       = (SPRT*)g_GfxPrimCursor;
    sprt->clut = GetClut(0, 0x1FA);
    setXY0(sprt, 0x4C, 0x30);
    sprt->w = 0xA8;
    setRGB0(sprt, shade, shade, shade);
    sprt->u0 = 0;
    sprt->v0 = 0;
    sprt->h  = 0x18;
    SetSprt(sprt);
    GFX_AddPrim(2, sizeof(SPRT));
}
