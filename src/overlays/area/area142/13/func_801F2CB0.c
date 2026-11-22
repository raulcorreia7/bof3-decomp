#include "area142_13.h"

#ifdef NON_MATCHING
/* The area's spiral backdrop: sixteen wedge-and-band steps turn with the actor timer, behind the scene. */
NON_MATCHING void func_801F2CB0(s32 timer) {
    POLY_G3* wedge;
    POLY_G4* band;
    POLY_G4* outer;
    s32      mode;
    s32      i;
    s32      phase;
    s32      angle;
    s32      next;
    s32      rim_angle;
    s32      x;
    s32      y;
    s32      shade;
    u32      color;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, mode);

    phase = timer << 4;
    for (i = 0; i < 16; i++) {
        wedge = (POLY_G3*)g_GfxPrimCursor;
        band  = (POLY_G4*)((u8*)wedge + sizeof(POLY_G3));
        outer = (POLY_G4*)((u8*)band + sizeof(POLY_G4));
        SetPolyG3(wedge);
        SetPolyG4(band);
        SetPolyG4(outer);

        /* The wedge spans the screen centre and the inner rim; the two bands taper out from it. */
        angle     = i << 8;
        wedge->x0 = 160;
        wedge->y0 = 120;
        x         = 160 + (rcos(angle) >> 4) / 3;
        band->x0  = x;
        wedge->x1 = x;
        y         = 120 + (rsin(angle) >> 5) / 3;
        band->y0  = y;
        wedge->y1 = y;

        next      = (i + 1) << 8;
        x         = 160 + (rcos(next) >> 4) / 3;
        band->x1  = x;
        wedge->x2 = x;
        y         = 120 + (rsin(next) >> 5) / 3;
        band->y1  = y;
        wedge->y2 = y;

        x         = 160 + (rcos(next) >> 3) / 3;
        outer->x0 = x;
        band->x2  = x;
        y         = 120 + (rsin(next) >> 4) / 3;
        outer->y0 = y;
        band->y2  = y;

        rim_angle = (i + 2) << 8;
        x         = 160 + (rcos(rim_angle) >> 3) / 3;
        outer->x1 = x;
        band->x3  = x;
        y         = 120 + (rsin(rim_angle) >> 4) / 3;
        outer->y1 = y;
        band->y3  = y;

        x         = 160 + (rcos(rim_angle) >> 2) / 3;
        outer->x2 = x;
        y         = 120 + (rsin(rim_angle) >> 3) / 3;
        outer->y2 = y;

        rim_angle = (i + 3) << 8;
        x         = 160 + (rcos(rim_angle) >> 2) / 3;
        outer->x3 = x;
        y         = 120 + (rsin(rim_angle) >> 3) / 3;
        outer->y3 = y;

        /* The rim shade follows the timer; a blue wave runs with it and a red one half a turn against it. */
        shade     = abs(0x80 - timer) >> 1;
        wedge->b0 = shade;
        wedge->g0 = shade;
        wedge->r0 = shade;
        outer->b3 = shade;
        outer->g3 = shade;
        outer->r3 = shade;
        outer->b2 = shade;
        outer->g2 = shade;
        outer->r2 = shade;

        color = (rcos(angle + phase) >> 6) + 0x80;
        color >>= 1;
        outer->b0 = color;
        band->b2  = color;
        band->b0  = color;
        wedge->b1 = color;

        color = (rcos(next + phase) >> 6) + 0x80;
        color >>= 1;
        outer->b1 = color;
        band->b3  = color;
        band->b1  = color;
        wedge->b2 = color;

        color = (rcos(angle - phase + ANGLE_180) >> 6) + 0x80;
        color >>= 1;
        outer->r0 = color;
        band->r2  = color;
        band->r0  = color;
        wedge->r1 = color;

        color = (rcos(next - phase + ANGLE_180) >> 6) + 0x80;
        color >>= 1;
        outer->r1 = color;
        band->r3  = color;
        band->r1  = color;
        wedge->r2 = color;

        wedge->g2 = 0;
        wedge->g1 = 0;
        band->g1  = 0;
        band->g0  = 0;
        band->g3  = 0;
        band->g2  = 0;
        outer->g1 = 0;
        outer->g0 = 0;

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
