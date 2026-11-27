#include "area199_13.h"

/* Draws the two-panel light pillar: two full-texture quads per band, sliding down as the step grows. */
MATCH void func_801F400C(void) {
    RECT*     window;
    POLY_FT4* prim;
    s32       shade[2];
    s32       size[2];
    s32       i;

    if (SELF(Actor)->header.step == 0) {
        return;
    }
    shade[0] = (0x80 - abs(0x80 - SELF(Actor)->header.step)) >> 1;
    if (abs(0x80 - SELF(Actor)->header.step) > 0x40) {
        shade[1] = 0x80 - abs(0x80 - SELF(Actor)->header.step);
    } else {
        shade[1] = ((rcos((SELF(Actor)->header.step - 0x40) << 5) >> 7) + 0x60) >> 1;
    }
    size[0] = SELF(Actor)->header.step & 0x3F;
    size[1] = (SELF(Actor)->header.step * 2) & 0x3F;

    for (i = 0; i < 2; i++) {
        window          = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor = (u8*)(window + 1);
        window->x       = 0;
        window->y       = 0;
        window->h       = 0x40;
        window->w       = 0x40;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 448, 256), window);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(DR_MODE));

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        setXY4(prim, -size[i], size[i] - 0x20, -size[i] + 0x100, size[i] - 0x20, -size[i], size[i] + 0xE0, -size[i] + 0x100, size[i] + 0xE0);
        setUV4(prim, 0, 0, 0xFF, 0, 0, 0xFF, 0xFF, 0xFF);
        setRGB0(prim, shade[i], shade[i], shade[i]);
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_QUARTER, 704, 256);
        prim->clut  = getClut(0, 483);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_FT4));

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        setXY4(prim, 0x100 - size[i], size[i] - 0x20, 0x200 - size[i], size[i] - 0x20, 0x100 - size[i], size[i] + 0xE0, 0x200 - size[i], size[i] + 0xE0);
        setUV4(prim, 0, 0, 0xFF, 0, 0, 0xFF, 0xFF, 0xFF);
        setRGB0(prim, shade[i], shade[i], shade[i]);
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_QUARTER, 704, 256);
        prim->clut  = getClut(0, 483);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_FT4));

        window          = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor = (u8*)(window + 1);
        window->x       = 0;
        window->y       = 0;
        window->h       = 0x100;
        window->w       = 0x100;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 448, 256), window);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(DR_MODE));
    }
    SELF(Actor)->header.step += 4;
}
