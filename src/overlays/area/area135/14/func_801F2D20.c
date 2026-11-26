#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2D20(void) {
    Actor*    work;
    Actor*    adopted;
    POLY_FT4* poly;
    s32       origin[3];
    SVECTOR   projection;
    long      depth;
    long      flag;
    u16       x;
    u16       x2;
    s32       y;
    s32       shade;

    work    = g_Task;
    adopted = &g_PartyActors[work->unk_18];

    work->pos.x       = adopted->pos.x.fixed;
    work->pos.y       = adopted->pos.y.fixed;
    work->pos.z.fixed = adopted->pos.z.fixed;
    TASK_SET(adopted);
    if (adopted->timer != 0) {
        if (adopted->vz < 0) {
            work->timer--;
        } else {
            work->timer++;
        }
    }
    func_801F3004(0, 240, 16, 16);

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);

    func_801AC1DC(origin, work->unk_1C);

    setVector(&projection, ((origin[0] + TASK(Actor)->pos.x.fixed) >> 9) - 0x4000, ((origin[1] + TASK(Actor)->pos.y.fixed) >> 9) - 0x4000, -(origin[2] + COORD_INT(TASK(Actor)->pos.z)) / 2);

    work->unk_60 = RotTransPers(&projection, (long*)&poly->x3, &depth, &flag);

    x2       = poly->x3;
    poly->y0 = 0;
    x        = poly->x3;
    poly->y1 = 0;
    poly->x1 = x + 8;
    poly->x3 = x + 8;
    y        = poly->y3;
    poly->x0 = x2 - 8;
    poly->x2 = x2 - 8;
    if (y >= 240) {
        poly->y3 = y = 240;
    }
    poly->y2 = y;
    g_Task   = work;
    setClut(poly, 0, STAGE_PALETTE_Y + 3);
    poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);

    setUV4(poly, 0, TASK(Actor)->timer & 0x15, 16, TASK(Actor)->timer & 0x15, 0, (TASK(Actor)->timer & 0x15) + poly->y2, 16, (TASK(Actor)->timer & 0x15) + poly->y2);

    SetShadeTex(poly, 0);

    if (TASK(Actor)->unk_60 >= 0x221) {
        setRGB0(poly, 128, 128, 128);
        SetSemiTrans(poly, 0);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 0, sizeof(POLY_FT4));
    } else if (TASK(Actor)->unk_60 >= 0x1E1) {
        shade = ((TASK(Actor)->unk_60 & 0xFF) - 0x1E0) << 1;
        setRGB0(poly, shade, shade, shade);
        SetSemiTrans(poly, 1);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 0, sizeof(POLY_FT4));
    }
    func_801F3004(0, 0, 256, 256);
}
#else
INCLUDE_ASM(func_801F2D20);
#endif
