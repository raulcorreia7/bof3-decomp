#include "area091_13.h"

MATCH void func_801F2ED4(u16 radius, u16 color) {
    SVECTOR  pos;
    SVECTOR  rot;
    MATRIX   matrix;
    POLY_G3* prim;
    long     flag;
    long     p;
    long     otz;
    s32      cell_x;
    s32      cell_y;
    s32      angle;
    s32      i;

    PushMatrix();
    setVector(&rot, 0, 0, 0);
    setVector(&pos, -0x3040, -0x3300, 0x80);
    RotTrans(&pos, (VECTOR*)matrix.t, &flag);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    cell_x = TO_COORD(31) + COORD_HALF;
    cell_y = TO_COORD(26);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 896, 256), 0);
    Area_AddCellPrim(cell_x, cell_y, 2, sizeof(DR_MODE));

    i = 0;
    do {
        angle = i << 7;
        /* FAKE: the counter's spare refs keep it in s1; the plain loop leaves the
         * scratch-vector pointer there and the two swap (19 rows). */
        i++;
        i--;
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[0].vz = 0;
        g_ScratchPadVectors[1].vx = (s16)FIXED_MUL(radius, rcos(angle));
        g_ScratchPadVectors[1].vy = (s16)FIXED_MUL(radius, rsin(angle));
        g_ScratchPadVectors[1].vz = 0;
        i++;
        angle                     = i << 7;
        g_ScratchPadVectors[2].vx = (s16)FIXED_MUL(radius, rcos(angle));
        g_ScratchPadVectors[2].vy = (s16)FIXED_MUL(radius, rsin(angle));
        g_ScratchPadVectors[2].vz = 0;
        prim                      = (POLY_G3*)g_GfxPrimCursor;
        setPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &otz);
        setRGB0(prim, color, color, 0);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        Area_AddCellPrim(cell_x, cell_y, 2, sizeof(POLY_G3));
    } while (i < 32);
    PopMatrix();
}
