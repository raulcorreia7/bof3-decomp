#include "area030_04.h"

/* Builds the AREA030 menu icon textured quad: sets the FT4 header,
 * picks the tpage from the GPU graph type, lays the icon into both halves of
 * the quad and queues the primitive.
 */

MATCH void func_801D2C34(s16 arg0, s16 arg1, s8 arg2, u8 arg3) {
    POLY_FT4* primitive;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);

    if (GetGraphType() != 1) {
        if (GetGraphType() == 2) {
            primitive->tpage = 0x229;
        } else {
            primitive->tpage = 0x99;
        }
    } else {
        primitive->tpage = 0x229;
    }
    primitive->clut = 0x7A40;
    setXY0(primitive, (arg0 - 8), arg1);
    primitive->x1 = (arg0 + 8);
    setRGB0(primitive, 128, 128, 128);
    primitive->y1 = arg1;
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    primitive->y2 = primitive->y0 + 8;
    primitive->y3 = primitive->y2;

    if ((arg2 & BYTE_MASK) == 0) {
        primitive->u0 = 40;
        primitive->u1 = 56;
    } else {
        primitive->u0 = 56;
        primitive->u1 = 40;
    }

    primitive->v0 = 88;
    primitive->v1 = 88;
    primitive->u2 = primitive->u0;
    primitive->u3 = primitive->u1;
    primitive->v2 = primitive->v0 + 8;
    primitive->v3 = primitive->v2;

    GFX_AddPrim(arg3 & BYTE_MASK, 0x28);
}
