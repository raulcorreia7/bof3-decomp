#include "area086_13.h"

MATCH void func_801F3070(void) {
    POLY_FT4* prim;
    Coord     x;
    Coord     y;
    long      depth;
    long      flag;
    s32       part;
    s32       corner;

    for (part = D_801F367C[SELF(Actor)->pos.x.part.integer][0]; part < D_801F367C[SELF(Actor)->pos.x.part.integer][1]; part++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        x.part.integer = (((D_801F36C0[part].cell.packed >> 24) - 0x80) << 7) + 0x40;
        y.part.integer = ((((D_801F36C0[part].cell.packed >> 16) & 0xFF) - 0x80) << 7) + 0x40;
        for (corner = 0; corner < 4; corner++) {
            g_ScratchPadVectors[corner].vx = x.part.integer - (D_801F3684[D_801F36C0[part].cell.bytes[1]][corner][0] * 128);
            g_ScratchPadVectors[corner].vy = y.part.integer - (D_801F3684[D_801F36C0[part].cell.bytes[1]][corner][1] * 128);
            g_ScratchPadVectors[corner].vz = SELF(Actor)->pos.z.part.integer + (D_801F3684[D_801F36C0[part].cell.bytes[1]][corner][2] * 128);
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F36C0[part].tile, prim, 1);
        x.fixed = (D_801F36C0[part].cell.packed >> 8) & 0xFF0000;
        y.fixed = D_801F36C0[part].cell.packed & 0xFF0000;
        Area_CellAddPrim(x.fixed, y.fixed, D_801F3674[D_801F36C0[part].cell.packed & 0xFF][SELF(Actor)->pos.z.part.integer != -0x200], sizeof(POLY_FT4));
    }
}
