#include "area142_13.h"

#ifdef NON_MATCHING
/* The area's spiral backdrop: sixteen wedge-and-band steps turn with the actor timer, behind the scene. */
NON_MATCHING void func_801F2CB0(s32 timer) {
    POLY_G3* prim;
    s32      mode;
    s32      i;
    s32      phase;
    s32      angle;
    s32      shade;
    s32      color;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, mode);

    phase = timer << 4;
    for (i = 0; i < 16; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetPolyG4((POLY_G4*)(prim + 1));
        SetPolyG4((POLY_G4*)(prim + 1) + 1);

        angle    = i << 8;
        prim->x0 = 160;
        prim->y0 = 120;
        /* Each rim point is shared: the wedge's corner is the band's, the band's is the outer's. */
        prim->x1 = ((POLY_G4*)(prim + 1))->x0 = 160 + (rcos(angle) >> 4) / 3;
        prim->y1 = ((POLY_G4*)(prim + 1))->y0 = 120 + (rsin(angle) >> 5) / 3;
        prim->x2 = ((POLY_G4*)(prim + 1))->x1 = 160 + (rcos((i + 1) << 8) >> 4) / 3;
        prim->y2 = ((POLY_G4*)(prim + 1))->y1 = 120 + (rsin((i + 1) << 8) >> 5) / 3;
        ((POLY_G4*)(prim + 1))->x2 = ((POLY_G4*)(prim + 1) + 1)->x0 = 160 + (rcos((i + 1) << 8) >> 3) / 3;
        ((POLY_G4*)(prim + 1))->y2 = ((POLY_G4*)(prim + 1) + 1)->y0 = 120 + (rsin((i + 1) << 8) >> 4) / 3;
        ((POLY_G4*)(prim + 1))->x3 = ((POLY_G4*)(prim + 1) + 1)->x1 = 160 + (rcos((i + 2) << 8) >> 3) / 3;
        ((POLY_G4*)(prim + 1))->y3 = ((POLY_G4*)(prim + 1) + 1)->y1 = 120 + (rsin((i + 2) << 8) >> 4) / 3;
        ((POLY_G4*)(prim + 1) + 1)->x2                              = 160 + (rcos((i + 2) << 8) >> 2) / 3;
        ((POLY_G4*)(prim + 1) + 1)->y2                              = 120 + (rsin((i + 2) << 8) >> 3) / 3;
        ((POLY_G4*)(prim + 1) + 1)->x3                              = 160 + (rcos((i + 3) << 8) >> 2) / 3;
        ((POLY_G4*)(prim + 1) + 1)->y3                              = 120 + (rsin((i + 3) << 8) >> 3) / 3;

        /* A blue wave turns with the timer, a red one half a turn against it; the rim colours go blue first. */
        shade = 0x80 - timer;
        if (shade < 0) {
            shade = -shade;
        }
        shade                          = (u32)shade >> 1;
        prim->b0                       = shade;
        prim->g0                       = shade;
        prim->r0                       = shade;
        ((POLY_G4*)(prim + 1) + 1)->b3 = shade;
        ((POLY_G4*)(prim + 1) + 1)->g3 = shade;
        ((POLY_G4*)(prim + 1) + 1)->r3 = shade;
        ((POLY_G4*)(prim + 1) + 1)->b2 = shade;
        ((POLY_G4*)(prim + 1) + 1)->g2 = shade;
        ((POLY_G4*)(prim + 1) + 1)->r2 = shade;
        color                          = (u32)((rcos(angle + phase) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        ((POLY_G4*)(prim + 1) + 1)->b0 = color;
        ((POLY_G4*)(prim + 1))->b2     = color;
        ((POLY_G4*)(prim + 1))->b0     = color;
        prim->b1                       = color;
        color                          = (u32)((rcos(((i + 1) << 8) + phase) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        ((POLY_G4*)(prim + 1) + 1)->b1 = color;
        ((POLY_G4*)(prim + 1))->b3     = color;
        ((POLY_G4*)(prim + 1))->b1     = color;
        prim->b2                       = color;
        color                          = (u32)((rcos(angle - phase + ANGLE_180) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        ((POLY_G4*)(prim + 1) + 1)->r0 = color;
        ((POLY_G4*)(prim + 1))->r2     = color;
        ((POLY_G4*)(prim + 1))->r0     = color;
        prim->r1                       = color;
        color                          = (u32)((rcos(((i + 1) << 8) - phase + ANGLE_180) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        ((POLY_G4*)(prim + 1) + 1)->r1 = color;
        ((POLY_G4*)(prim + 1))->r3     = color;
        ((POLY_G4*)(prim + 1))->r1     = color;
        prim->r2                       = color;
        prim->g2                       = 0;
        prim->g1                       = 0;
        ((POLY_G4*)(prim + 1))->g1     = 0;
        ((POLY_G4*)(prim + 1))->g0     = 0;
        ((POLY_G4*)(prim + 1))->g3     = 0;
        ((POLY_G4*)(prim + 1))->g2     = 0;
        ((POLY_G4*)(prim + 1) + 1)->g1 = 0;
        ((POLY_G4*)(prim + 1) + 1)->g0 = 0;

        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G3));
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
    }

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_BACKDROP, mode);
}
#else
INCLUDE_ASM(func_801F2CB0);
#endif
