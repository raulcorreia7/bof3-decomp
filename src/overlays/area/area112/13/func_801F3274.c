#include "area112_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3274(void) {
    POLY_FT4* prim;
    Coord     x;
    Coord     y;
    long      depth;
    long      flag;
    s32       part;
    s32       corner;

    for (part = D_801F4250[TASK(Actor)->pos.x.part.integer][0]; part < D_801F4250[TASK(Actor)->pos.x.part.integer][1]; part++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        x.part.integer = ((((&D_801F4294[part])->cell.packed >> 24) - 0x80) << 7) + 0x40;
        y.part.integer = (((((&D_801F4294[part])->cell.packed >> 16) & 0xFF) - 0x80) << 7) + 0x40;
        for (corner = 0; corner < 4; corner++) {
            g_ScratchPadVectors[corner].vx = x.part.integer - (D_801F4258[(&D_801F4294[part])->cell.bytes[1]][corner][0] * 128);
            g_ScratchPadVectors[corner].vy = y.part.integer - (D_801F4258[(&D_801F4294[part])->cell.bytes[1]][corner][1] * 128);
            g_ScratchPadVectors[corner].vz = TASK(Actor)->pos.z.part.integer + (D_801F4258[(&D_801F4294[part])->cell.bytes[1]][corner][2] * 128);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F4294[part].tile, prim, 1);
        x.fixed = ((&D_801F4294[part])->cell.packed >> 8) & 0xFF0000;
        y.fixed = (&D_801F4294[part])->cell.packed & 0xFF0000;
        if (D_801F4240[(&D_801F4294[part])->cell.packed & 0xFF][TASK(Actor)->header.step == 2] < 0) {
            GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_FT4));
        } else {
            Area_CellAddPrim(x.fixed, y.fixed, D_801F4240[(&D_801F4294[part])->cell.packed & 0xFF][TASK(Actor)->header.step == 2], sizeof(POLY_FT4));
        }
    }
}
#else
INCLUDE_ASM(func_801F3274);
#endif
