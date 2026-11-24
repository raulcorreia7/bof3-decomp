#include "area142_13.h"

/* The area's spiral backdrop: sixteen wedge-and-band steps turn with the actor timer, behind the scene. */
MATCH void func_801F2CB0(s32 timer) {
    typedef struct {
        POLY_G3 wedge;
        POLY_G4 inner_band;
        POLY_G4 outer_band;
    } SpiralSlice;

    register SpiralSlice* slice;
    s32                   mode;
    s32                   i;
    s32                   angle;
    s32                   next_angle;
    /* FAKE: The retail register allocation requires the outer angle in s1. */
    FAKE_REG(s32, outer_angle, "s1");
    register s32 rim_y;
    s32          shade;
    s32          color;

    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, mode);

    i = 0;
    do {
        slice = (SpiralSlice*)g_GfxPrimCursor;
        SetPolyG3(&slice->wedge);
        SetPolyG4(&slice->inner_band);
        SetPolyG4(&slice->outer_band);

        /* Each rim point is shared: the wedge's corner is the band's, the band's is the outer's. */
        setXY0(&slice->wedge, 160, 120);
        slice->wedge.x1 = slice->inner_band.x0 = 160 + (rcos(i << 8) >> 4) / 3;
        slice->wedge.y1 = slice->inner_band.y0 = 120 + (rsin(i << 8) >> 5) / 3;
        next_angle                             = (i + 1) << 8;
        slice->wedge.x2 = slice->inner_band.x1 = 160 + (rcos(next_angle) >> 4) / 3;
        slice->wedge.y2 = slice->inner_band.y1 = 120 + (rsin(next_angle) >> 5) / 3;
        slice->inner_band.x2 = slice->outer_band.x0 = 160 + (rcos(next_angle) >> 3) / 3;
        slice->inner_band.y2 = slice->outer_band.y0 = 120 + (rsin(next_angle) >> 4) / 3;
        angle                                       = i << 8;
        outer_angle                                 = i + 2;
        outer_angle <<= 8;
        slice->inner_band.x3 = slice->outer_band.x1 = 160 + (rcos(outer_angle) >> 3) / 3;
        slice->inner_band.y3 = slice->outer_band.y1 = 120 + (rsin(outer_angle) >> 4) / 3;
        slice->outer_band.x2                        = 160 + (rcos(outer_angle) >> 2) / 3;
        slice->outer_band.y2                        = 120 + (rsin(outer_angle) >> 3) / 3;
        outer_angle                                 = i + 3;
        outer_angle <<= 8;
        i++;
        slice->outer_band.x3 = 160 + (rcos(outer_angle) >> 2) / 3;
        rim_y                = rsin(outer_angle);

        /* A blue wave turns with the timer, a red one half a turn against it; the rim colours go blue first. */
        shade           = (u32)abs(GFX_COLOR_NEUTRAL - timer) >> 1;
        slice->wedge.r0 = slice->wedge.g0 = slice->wedge.b0 = shade;
        slice->outer_band.r3 = slice->outer_band.g3 = slice->outer_band.b3 = shade;
        slice->outer_band.r2 = slice->outer_band.g2 = slice->outer_band.b2 = shade;
        slice->outer_band.y3                                               = 120 + (rim_y >> 3) / 3;
        color                                                              = (u32)((rcos(angle + (timer << 4)) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        slice->outer_band.b0                                               = color;
        slice->inner_band.b2                                               = color;
        slice->inner_band.b0                                               = color;
        slice->wedge.b1                                                    = color;
        color                                                              = (u32)((rcos(next_angle + (timer << 4)) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        slice->outer_band.b1                                               = color;
        slice->inner_band.b3                                               = color;
        slice->inner_band.b1                                               = color;
        slice->wedge.b2                                                    = color;
        angle -= timer << 4;
        color                = (u32)((rcos(angle + ANGLE_180) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        slice->outer_band.r0 = color;
        slice->inner_band.r2 = color;
        slice->inner_band.r0 = color;
        slice->wedge.r1      = color;
        next_angle -= timer << 4;
        color                = (u32)((rcos(next_angle + ANGLE_180) >> 6) + GFX_COLOR_NEUTRAL) >> 1;
        slice->outer_band.r1 = color;
        slice->inner_band.r3 = color;
        slice->inner_band.r1 = color;
        slice->wedge.r2      = color;
        slice->wedge.g2      = 0;
        slice->wedge.g1      = 0;
        slice->inner_band.g1 = 0;
        slice->inner_band.g0 = 0;
        slice->inner_band.g3 = 0;
        slice->inner_band.g2 = 0;
        slice->outer_band.g1 = 0;
        slice->outer_band.g0 = 0;

        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G3));
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
        GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
    } while (i < 16);

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_BACKDROP, mode);
}
