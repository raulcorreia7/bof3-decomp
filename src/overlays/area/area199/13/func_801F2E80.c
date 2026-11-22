#include "area199_13.h"

#ifdef NON_MATCHING
/* Draws the area backdrop: the two opening panels, then the cell sprites of the payload table,
 * scrolled by y_offset. */
NON_MATCHING void func_801F2E80(s32 y_offset) {
    RECT*              window;
    POLY_FT4*          prim;
    Area199CellSprite* sprite;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }
    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0;
    window->y       = 0;
    window->w       = 0x10;
    window->h       = 0x10;
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_BACKDROP, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 576, 256));

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
    window->w       = 0x100;
    window->h       = 0x100;
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_BACKDROP, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 576, 256));

    for (sprite = D_801F44D4; sprite < &D_801F44D4[8]; sprite++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 1);
        setXY4(prim, sprite->x, sprite->y + y_offset, sprite->x + sprite->w, sprite->y + y_offset, sprite->x, sprite->y + sprite->h + y_offset, sprite->x + sprite->w,
               sprite->y + sprite->h + y_offset);
        setUV4(prim, sprite->u, sprite->v, sprite->u + sprite->u_size, sprite->v, sprite->u, sprite->v + sprite->v_size, sprite->u + sprite->u_size, sprite->v + sprite->v_size);
        prim->tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, (sprite->page << 7) + 0x140, 256);
        prim->clut  = getClut(0, sprite->page + 0x1E5);
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));
    }
}
#else
INCLUDE_ASM(func_801F2E80);
#endif
