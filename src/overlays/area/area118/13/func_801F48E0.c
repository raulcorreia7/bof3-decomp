#include "area118_13.h"

/* Draws the actor's cell outline as a projected line, with its vertex heights
 * lifted off the sampled ground and the actor's stage height. */
/* func_801F48E0 */
MATCH void func_801F48E0(void) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    s32      shade;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x225;
    } else {
        tpage = 0x95;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));
    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    SetSemiTrans(prim, 1);
    shade    = (g_FrameCount & 1) << 7;
    prim->b0 = shade;
    prim->g0 = shade;
    prim->r0 = shade;
    g_ScratchPadVectors[0].vz =
        -Area_SampleHeight((g_ScratchPadVectors[0].vx + 0x4000) << 9, (g_ScratchPadVectors[0].vy + 0x4000) << 9) / 2 - LOHU(((Actor*)g_Task)->pos.z.part.integer) - 60 + (g_FrameCount % 48) * 2;
    g_ScratchPadVectors[1].vz =
        -Area_SampleHeight((g_ScratchPadVectors[1].vx + 0x4000) << 9, (g_ScratchPadVectors[1].vy + 0x4000) << 9) / 2 - LOHU(((Actor*)g_Task)->pos.z.part.integer) - 60 + (g_FrameCount % 48) * 2;
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)D_1F800034, &depth, &flag);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(LINE_F2));

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x225;
    } else {
        tpage = 0x95;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));
}
