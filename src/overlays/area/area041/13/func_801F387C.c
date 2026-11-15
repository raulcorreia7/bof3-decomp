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
    pos.vx = g_Task->pos.x.fixed;
    pos.vy = g_Task->pos.y.fixed;
    pos.vz = COORD_INT(g_Task->pos.z);

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
        D_1F800014[0].vx = D_1F800014[1].vx = D_1F800014[2].vx = D_1F800014[3].vx = 0;
        D_1F800014[0].vy = D_1F800014[2].vy = (i + 1) << 7;
        D_1F800014[1].vy = D_1F800014[3].vy = i << 7;
        D_1F800014[0].vz = D_1F800014[1].vz = -0x180;
        D_1F800014[2].vz = D_1F800014[3].vz = 0;
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        func_80155560(D_801F42D4[i], prim, 1);
        Area_AddCellPrim((g_Task->pos.x.fixed + AREA_CELL_ORIGIN) << 9, (g_Task->pos.y.fixed + (i << 7) + (AREA_CELL_ORIGIN + AREA_CELL_HALF)) << 9, 2, sizeof(POLY_FT4));
    }
    PopMatrix();
}
