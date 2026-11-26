#include "area041_13.h"

MATCH void func_801F387C(s32 angle) {
    SVECTOR   pos;
    SVECTOR   rot;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    s32       i;

    rot.vy = -angle;
    rot.vz = 0;
    rot.vx = 0;
    setVector(&pos, SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, COORD_INT(SELF(Actor)->pos.z));

    PushMatrix();
    RotTransMatrix(&pos, matrix, &flag);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = 0;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = (i + 1) << 7;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = i << 7;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = -0x180;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = 0;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F42D4[i], prim, 1);
        Area_CellAddPrim((SELF(Actor)->pos.x.fixed + AREA_CELL_ORIGIN) << 9, (SELF(Actor)->pos.y.fixed + (i << 7) + (AREA_CELL_ORIGIN + AREA_CELL_HALF)) << 9, 2, sizeof(POLY_FT4));
    }
    PopMatrix();
}
