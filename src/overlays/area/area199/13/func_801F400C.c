#include "area199_13.h"

#ifdef NON_MATCHING
/* Draws the two-panel light pillar: two full-texture quads per band, sliding down as the step grows. */
NON_MATCHING void func_801F400C(void) {
    RECT*     window;
    POLY_FT4* prim;
    s32       shade[2];
    s32       size[2];
    s32       i;

    if (TASK(Actor)->header.step == 0) {
        return;
    }
    shade[0] = (0x80 - abs(0x80 - TASK(Actor)->header.step)) >> 1;
    if (abs(0x80 - TASK(Actor)->header.step) < 0x41) {
        shade[1] = ((rcos((TASK(Actor)->header.step - 0x40) << 5) >> 7) + 0x60) >> 1;
    } else {
        shade[1] = 0x80 - abs(0x80 - TASK(Actor)->header.step);
    }
    size[0] = TASK(Actor)->header.step & 0x3F;
    size[1] = (TASK(Actor)->header.step * 2) & 0x3F;

    for (i = 0; i < 2; i++) {
        window          = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor = (u8*)(window + 1);
        window->x       = 0;
        window->y       = 0;
        window->w       = 0x40;
        window->h       = 0x40;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 448, 256), window);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(DR_MODE));

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        prim->x0    = -size[i];
        prim->y0    = size[i] - 0x20;
        prim->x1    = 0x100 - size[i];
        prim->y1    = size[i] - 0x20;
        prim->x2    = -size[i];
        prim->y2    = size[i] + 0xE0;
        prim->x3    = 0x100 - size[i];
        prim->y3    = size[i] + 0xE0;
        prim->u0    = 0;
        prim->v0    = 0;
        prim->u1    = 0xFF;
        prim->v1    = 0;
        prim->u2    = 0;
        prim->v2    = 0xFF;
        prim->u3    = 0xFF;
        prim->v3    = 0xFF;
        prim->r0    = shade[i];
        prim->g0    = shade[i];
        prim->b0    = shade[i];
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_QUARTER, 704, 256);
        prim->clut  = getClut(0, 483);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_FT4));

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        prim->x0    = 0x100 - size[i];
        prim->y0    = size[i] - 0x20;
        prim->x1    = 0x200 - size[i];
        prim->y1    = size[i] - 0x20;
        prim->x2    = 0x100 - size[i];
        prim->y2    = size[i] + 0xE0;
        prim->x3    = 0x200 - size[i];
        prim->y3    = size[i] + 0xE0;
        prim->u0    = 0;
        prim->v0    = 0;
        prim->u1    = 0xFF;
        prim->v1    = 0;
        prim->u2    = 0;
        prim->v2    = 0xFF;
        prim->u3    = 0xFF;
        prim->v3    = 0xFF;
        prim->r0    = shade[i];
        prim->g0    = shade[i];
        prim->b0    = shade[i];
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_QUARTER, 704, 256);
        prim->clut  = getClut(0, 483);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_FT4));

        window          = (RECT*)g_GfxPrimCursor;
        g_GfxPrimCursor = (u8*)(window + 1);
        window->x       = 0;
        window->y       = 0;
        window->w       = 0x100;
        window->h       = 0x100;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 448, 256), window);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(DR_MODE));
    }
    TASK(Actor)->header.step += 4;
}
#else
INCLUDE_ASM(func_801F400C);
#endif
