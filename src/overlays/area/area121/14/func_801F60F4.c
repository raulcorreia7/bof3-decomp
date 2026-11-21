#include "area121_14.h"

/* Raises the effect height by 16 and draws its textured ground quad; ends the effect past 640. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F60F4(void* actor) {
    SVECTOR   vertex;
    SVECTOR   rotation;
    MATRIX    matrix;
    long      trans_flag;
    long      depth;
    long      flag;
    POLY_FT4* prim;

    g_Task->pos.z.part.integer += 0x10;
    if (g_Task->pos.z.part.integer >= 641) {
        g_Task->header.mode = 3;
    }
    if (g_AreaDrawFlags & 0x1B) {
        PushMatrix();
        setVector(&rotation, 0, 0, 0);
        vertex.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
        vertex.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
        vertex.vz = -g_Task->pos.z.part.integer / 2;
        RotTransMatrix(&vertex, matrix, &trans_flag);
        RotMatrix(&rotation, &matrix);
        MulMatrix2(&g_CameraMatrix, &matrix);
        SetRotMatrix(&matrix);
        SetTransMatrix(&matrix);
        prim                      = (POLY_FT4*)g_GfxPrimCursor;
        depth                     = (g_Task->pos.z.part.integer >> 7) * 10 + 16;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vz = g_ScratchPadVectors[1].vx = 0;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[2].vx = 0;
        g_ScratchPadVectors[3].vz = g_ScratchPadVectors[3].vy = 0;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vx = -(u16)depth;
        g_ScratchPadVectors[3].vx = g_ScratchPadVectors[2].vy = (u16)depth;
        SetPolyFT4(prim);
        SetSemiTrans(prim, 1);
        prim->tpage = getTPage(0, 1, 704, 256);
        prim->u0    = 224;
        prim->u1    = 254;
        prim->u2    = prim->u0;
        prim->v0    = 48;
        prim->v1    = 48;
        prim->clut  = 0x78CA;
        prim->v3 = prim->v2 = prim->v0 + 30;
        prim->u3            = prim->u1;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 128, 128, 128);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
        PopMatrix();
    }
}
#else
INCLUDE_ASM(func_801F60F4);
#endif
