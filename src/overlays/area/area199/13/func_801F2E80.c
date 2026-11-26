#include "area199_13.h"

/* Draws the area backdrop: the two opening panels, then the cell sprites of the payload table,
 * scrolled by y_offset. */
MATCH void func_801F2E80(s32 y_offset) {
    RECT*     window;
    POLY_FT4* prim;
    s32       i;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }
    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0x10;
    window->y       = 0;
    window->h       = 0x10;
    window->w       = 0x10;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 576, 256), window);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 1);
    setXY4(prim, 0, 0, 0x100, 0, 0, 0x100, 0x100, 0x100);
    setUV4(prim, 0, 0, 0xFF, 0, 0, 0xFF, 0xFF, 0xFF);
    prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 576, 256);
    prim->clut  = getClut(0, 487);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 1);
    setXY4(prim, 0x100, 0, 0x140, 0, 0x100, 0x100, 0x140, 0x100);
    setUV4(prim, 0, 0, 0x40, 0, 0, 0xFF, 0x40, 0xFF);
    prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 576, 256);
    prim->clut  = getClut(0, 487);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0;
    window->y       = 0;
    window->h       = 0x100;
    window->w       = 0x100;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 576, 256), window);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));

    for (i = 0; i < 8; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 1);
        setXY4(prim, D_801F44D4[i].x, D_801F44D4[i].y + y_offset, D_801F44D4[i].x + D_801F44D4[i].w, D_801F44D4[i].y + y_offset, D_801F44D4[i].x, D_801F44D4[i].y + y_offset + D_801F44D4[i].h,
               D_801F44D4[i].x + D_801F44D4[i].w, D_801F44D4[i].y + y_offset + D_801F44D4[i].h);
        setUV4(prim, D_801F44D4[i].u, D_801F44D4[i].v, D_801F44D4[i].u + D_801F44D4[i].u_size, D_801F44D4[i].v, D_801F44D4[i].u, D_801F44D4[i].v + D_801F44D4[i].v_size,
               D_801F44D4[i].u + D_801F44D4[i].u_size, D_801F44D4[i].v + D_801F44D4[i].v_size);
        prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, (D_801F44D4[i].page << 7) + 0x140, 256);
        prim->clut  = getClut(0, D_801F44D4[i].page + 0x1E5);
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));
    }
}
