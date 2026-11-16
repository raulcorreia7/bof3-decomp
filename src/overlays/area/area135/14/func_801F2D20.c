#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2D20(void) {
    u8*       work;
    Actor*    work_cell;
    Actor*    adopted;
    u8*       prim;
    POLY_FT4* poly;
    s32       origin[3];
    SVECTOR   projection;
    long      depth;
    long      flag;
    u16       x;
    u16       x2;
    u16       y;

    work      = (u8*)g_Task;
    prim      = g_GfxPrimCursor;
    work_cell = (Actor*)work;
    adopted   = &D_80147A58[work_cell->unk_18];

    work_cell->pos.x       = adopted->pos.x.fixed;
    work_cell->pos.y       = adopted->pos.y.fixed;
    work_cell->pos.z.fixed = adopted->pos.z.fixed;
    g_GfxPrimCursor        = prim + 8;
    TASK_SET(adopted);
    ((RECT*)prim)->x = 0;
    ((RECT*)prim)->y = 240;
    setWH(((RECT*)prim), 16, 16);
    SetTexWindow((DR_TWIN*)(prim + 8), (RECT*)prim);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0x11, 0x0C);

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);

    func_801AC1DC(origin, work_cell->unk_1C);

    setVector(&projection, ((origin[0] + g_Task->pos.x.fixed) >> 9) - 0x4000, ((origin[1] + g_Task->pos.y.fixed) >> 9) - 0x4000, -(origin[2] + COORD_INT(g_Task->pos.z)) / 2);

    work_cell->unk_60 = RotTransPers(&projection, (long*)&poly->x0, &depth, &flag);

    y        = poly->y0;
    x        = poly->x0;
    poly->y1 = 0;
    poly->y0 = 0;
    g_Task   = work;
    x2       = poly->x0;
    poly->x1 = x + 8;
    poly->x3 = x + 8;
    poly->x0 = x2 - 8;
    poly->x2 = x2 - 8;
    poly->y3 = y;
    poly->y2 = y;
    setClut(poly, 176, STAGE_PALETTE_Y + 3);
    poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);

    setUV4(poly, 0, (g_FrameCount >> 2) & 0x15, 16, (g_FrameCount >> 2) & 0x15, 0, ((g_FrameCount >> 2) & 0x15) + poly->y2, 16, ((g_FrameCount >> 2) & 0x15) + poly->y2);

    setRGB0(poly, 128, 128, 128);

    SetShadeTex(poly, 1);

    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0x11, sizeof(POLY_FT4));

    prim             = g_GfxPrimCursor;
    g_GfxPrimCursor  = prim + 8;
    ((RECT*)prim)->x = 0;
    ((RECT*)prim)->y = 0;
    setWH(((RECT*)prim), 256, 256);
    SetTexWindow((DR_TWIN*)(prim + 8), (RECT*)prim);

    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0x11, 0x0C);
}
#else
INCLUDE_ASM(func_801F2D20);
#endif
