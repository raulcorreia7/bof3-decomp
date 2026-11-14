#include "area082_13.h"

MATCH void func_801F52D8(void) {
    POLY_F4* poly = (POLY_F4*)g_GfxPrimCursor;

    SetPolyF4(poly);
    setXY4(poly, 0, 0, 320, 0, 0, 240, 320, 240);
    setRGB0(poly, 0xFF, 0xFF, 0xFF);
    GFX_AddPrim(4, 24);
    SND_PlayCue(0x202);
    D_8014933A = 1;
    func_801F5388(0x80);
    D_80145EED[2] = 0;
    D_80145EED[1] = 0;
    D_80145EED[0] = 0;
    func_80196070();
}
