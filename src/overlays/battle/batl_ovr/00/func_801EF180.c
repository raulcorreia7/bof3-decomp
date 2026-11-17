#include "batl_ovr_00.h"

MATCH void func_801EF180(s32 shade) {
    SPRT* sprt;
    /* FAKE: keeps the first two sprites' y coordinate in retail register s2. */
    FAKE_REG(s16, y, "s2");
    /* FAKE: keeps the last two sprites' x coordinate in retail register s1. */
    FAKE_REG(s16, x, "s1");

    y = 60;
    x = 272;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 832, 256), 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));

    sprt       = (SPRT*)g_GfxPrimCursor;
    sprt->clut = GetClut(0, 0x1FA);
    sprt->x0   = 16;
    sprt->v0   = 96;
    sprt->w    = 256;
    setRGB0(sprt, shade, shade, shade);
    sprt->y0 = y;
    sprt->u0 = 0;
    sprt->h  = 160;
    SetSprt(sprt);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));

    sprt       = (SPRT*)g_GfxPrimCursor;
    sprt->clut = GetClut(0, 0x1FA);
    sprt->y0   = y;
    sprt->u0   = 192;
    setRGB0(sprt, shade, shade, shade);
    sprt->x0 = x;
    sprt->v0 = 0;
    sprt->w  = 32;
    sprt->h  = 96;
    SetSprt(sprt);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));

    sprt       = (SPRT*)g_GfxPrimCursor;
    sprt->clut = GetClut(0, 0x1FA);
    sprt->y0   = 156;
    sprt->u0   = 224;
    setRGB0(sprt, shade, shade, shade);
    sprt->x0 = x;
    sprt->v0 = 0;
    sprt->w  = 32;
    sprt->h  = 64;
    SetSprt(sprt);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
}
