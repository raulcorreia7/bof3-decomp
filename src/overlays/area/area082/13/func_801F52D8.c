#include "area082_13.h"

MATCH void func_801F52D8(void) {
    POLY_F4* poly = (POLY_F4*)g_GfxPrimCursor;

    SetPolyF4(poly);
    poly->x0 = 0;
    poly->y0 = 0;
    poly->x1 = 320;
    poly->y1 = 0;
    poly->x2 = 0;
    poly->y2 = 240;
    poly->x3 = 320;
    poly->y3 = 240;
    poly->r0 = 0xFF;
    poly->g0 = 0xFF;
    poly->b0 = 0xFF;
    GFX_AddPrim(4, 24);
    SND_PlayCue(0x202);
    D_8014933A = 1;
    func_801F5388(0x80);
    D_80145EED[2] = 0;
    D_80145EED[1] = 0;
    D_80145EED[0] = 0;
    func_80196070();
}
