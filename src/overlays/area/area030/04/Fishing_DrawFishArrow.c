#include "area030_04.h"

/* Builds the AREA030 menu icon textured quad: sets the FT4 header,
 * picks the tpage from the GPU graph type, lays the icon into both halves of
 * the quad and queues the primitive.
 */

/* func_801D2C34 */
MATCH void Fishing_DrawFishArrow(s16 x, s16 y, s8 flip, u8 ot_index) {
    POLY_FT4* primitive;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);

    primitive->tpage = getTPage(1, 0, 576, 256);
    primitive->clut  = getClut(0, 489);
    setXY0(primitive, (x - 8), y);
    primitive->x1 = (x + 8);
    setRGB0(primitive, 128, 128, 128);
    primitive->y1 = y;
    primitive->x2 = primitive->x0;
    primitive->x3 = primitive->x1;
    primitive->y2 = primitive->y0 + 8;
    primitive->y3 = primitive->y2;

    if ((flip & BYTE_MASK) == 0) {
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

    GFX_AddPrim(ot_index & BYTE_MASK, sizeof(POLY_FT4));
}
