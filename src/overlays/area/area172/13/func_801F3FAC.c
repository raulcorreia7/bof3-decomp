#include "area172_13.h"

MATCH void func_801F3FAC(void) {
    MATRIX matrix;
    s32    spin;
    s32    angle;
    s32    i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x380, 0x100), 0);
    GFX_AddPrim(1, 0xC);
    Area_SetCameraMatrix(&matrix);
    spin  = 0x800E48C0;
    i     = 0;
    angle = 0x800E48E4;
    do {
        func_801F3BFC(spin);
        spin += 0x2C;
        FIELD(u16, angle, 0) += 0x10;
        i += 1;
        angle += 0x2C;
    } while ((u32)(i & 0xFF) < 0x20U);
}
