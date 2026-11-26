#include "area105_13.h"

#ifdef NON_MATCHING
/* Draws the three cell-row quads: the texture window, a semi-transparent quad a row, and the
 * final 0x100-wide window. */
NON_MATCHING void func_801F2D9C(s32 phase) {
    POLY_FT4* prim;
    RECT*     tw;
    SVECTOR*  quad;
    long      depth;
    long      flag;
    s32       i;
    s32       x;
    s32       y;

    tw = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += sizeof(RECT);
    tw->x = 0x60;
    tw->y = 0x10;
    tw->h = 0x10;
    tw->w = 0x10;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256), tw);
    GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MODE));

    quad = g_ScratchPadVectors;
    for (i = 0; i < 3; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_QUARTER, 704, 256);
        prim->clut  = 0x78C6;
        quad[0].vx = quad[2].vx = x = (phase * 4 + ((g_Area105CellRows[i].x - 0x80) << 7)) - 0x40;
        quad[1].vx = quad[3].vx = (phase * 4 + ((g_Area105CellRows[i].x + g_Area105CellRows[i].width - 0x81) << 7)) + 0x40;
        quad[0].vy = quad[1].vy = y = (phase * 4 + ((g_Area105CellRows[i].y - 0x80) << 7)) - 0x40;
        quad[0].vz = quad[1].vz = quad[2].vz = quad[3].vz = phase * 6 - 0x380;
        quad[2].vy = quad[3].vy = (phase * 4 + ((g_Area105CellRows[i].y + g_Area105CellRows[i].height - 0x81) << 7)) + 0x40;
        if (i == 2) {
            quad[0].vx = x + (phase << 3);
            quad[0].vy = y + (phase << 3);
        }
        prim->u0 = 0;
        prim->v0 = 0;
        prim->u1 = (g_Area105CellRows[i].width << 4) - 1;
        prim->v1 = 0;
        prim->u2 = 0;
        prim->v2 = (g_Area105CellRows[i].height << 4) - 1;
        prim->u3 = (g_Area105CellRows[i].width << 4) - 1;
        prim->v3 = (g_Area105CellRows[i].height << 4) - 1;
        setRGB0(prim, 0x80, 0x80, 0x80);
        RotTransPers4(quad, &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_FT4));
    }

    tw = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += sizeof(RECT);
    tw->x = 0;
    tw->y = 0;
    tw->h = 0x100;
    tw->w = 0x100;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256), tw);
    GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MODE));
}
#else
INCLUDE_ASM(func_801F2D9C);
#endif
