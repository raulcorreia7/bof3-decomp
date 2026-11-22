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
    s32      rim;
    s32      far;
    s32      x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6;
    s32      shade;
    s32      blue_a, blue_b, red_a, red_b;

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
        angle = i << 8;
        next  = (i + 1) << 8;
        rim   = (i + 2) << 8;
        far   = (i + 3) << 8;
        x1    = 160 + (rcos(angle) >> 4) / 3;
        y1    = 120 + (rsin(angle) >> 5) / 3;
        x2    = 160 + (rcos(next) >> 4) / 3;
        y2    = 120 + (rsin(next) >> 5) / 3;
        x3    = 160 + (rcos(next) >> 3) / 3;
        y3    = 120 + (rsin(next) >> 4) / 3;
        x4    = 160 + (rcos(rim) >> 3) / 3;
        y4    = 120 + (rsin(rim) >> 4) / 3;
        x5    = 160 + (rcos(rim) >> 2) / 3;
        y5    = 120 + (rsin(rim) >> 3) / 3;
        x6    = 160 + (rcos(far) >> 2) / 3;
        y6    = 120 + (rsin(far) >> 3) / 3;
        setXY3(wedge, 160, 120, x1, y1, x2, y2);
        setXY4(band, x1, y1, x2, y2, x3, y3, x4, y4);
        setXY4(outer, x3, y3, x4, y4, x5, y5, x6, y6);

        /* The rim shade follows the timer; a blue wave runs with it and a red one half a turn against it. */
        shade  = abs(0x80 - timer) >> 1;
        blue_a = ((rcos(angle + phase) >> 6) + 0x80) >> 1;
        blue_b = ((rcos(next + phase) >> 6) + 0x80) >> 1;
        red_a  = ((rcos(angle - phase + ANGLE_180) >> 6) + 0x80) >> 1;
        red_b  = ((rcos(next - phase + ANGLE_180) >> 6) + 0x80) >> 1;
        setRGB0(wedge, shade, shade, shade);
        setRGB1(wedge, red_a, 0, blue_a);
        setRGB2(wedge, red_b, 0, blue_b);
        setRGB0(band, red_a, 0, blue_a);
        setRGB1(band, red_b, 0, blue_b);
        setRGB2(band, red_a, 0, blue_a);
        setRGB3(band, red_b, 0, blue_b);
        setRGB0(outer, red_a, 0, blue_a);
        setRGB1(outer, red_b, 0, blue_b);
        setRGB2(outer, shade, shade, shade);
        setRGB3(outer, shade, shade, shade);

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
