#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5418(s32 value, s32 flag) {
    TorchGaugeCells cells;
    POLY_FT4*       primitive;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    cells     = D_801F2C04;
    SetPolyFT4(primitive);
    primitive->tpage = getTPage(0, 0, 960, 0);
    primitive->x0    = 0xE4;
    primitive->x1    = primitive->x0 + (value & BYTE_MASK);
    primitive->y0    = 0x1D;
    primitive->y1    = 0x1D;
    primitive->clut  = (cells.rows[flag & BYTE_MASK].clut >> 4) | 0x7800;
    primitive->x2    = primitive->x0;
    primitive->x3    = primitive->x1;
    primitive->y2    = primitive->y0 + 10;
    primitive->y3    = primitive->y2;
    primitive->v0    = 0xD8;
    primitive->v1    = 0xD8;
    setRGB0(primitive, 128, 128, 128);
    primitive->u0 = cells.rows[flag & BYTE_MASK].u;
    primitive->u1 = primitive->u0 + 4;
    primitive->u2 = primitive->u0;
    primitive->u3 = primitive->u1;
    primitive->v2 = primitive->v0 + 8;
    primitive->v3 = primitive->v2;
    GFX_AddPrim(2, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801F5418);
#endif
