#include "engine/slus/slus.h"

/* draws the outlined, rotating fairy portrait: projects the work
 * coordinates, builds the portrait quad and the rotating triangle fan, and
 * restores the matrix stack.
 */
MATCH void func_80167910(void) {
    SVECTOR   rot;
    SVECTOR   axis;
    MATRIX    mtx;
    SVECTOR   pos;
    DVECTOR   sxy;
    long      p;
    long      flag;
    long      sxy2;
    POLY_FT4* poly;
    u8*       prim;
    s16       sy;
    s16       radius;
    s32       angle;
    s32       i;
    s32       mode;

    TASK_SET(D_8014626C);
    if (D_8014626C[0] & 0x40) {
        return;
    }
    pos.vx           = (s16)((D_801462A0 >> 9) - 0x4000);
    pos.vy           = (s16)((D_801462A4 >> 9) - 0x4000);
    pos.vz           = (s16)(-(D_801462AA + 0x80) / 2);
    g_Task->unk_60   = RotTransPers(&pos, (long*)&sxy, &p, &flag);
    g_Task->screen_x = sxy.vx;
    g_Task->screen_y = sxy.vy;
    poly             = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    sy       = g_Task->screen_x;
    poly->x0 = sy - 6;
    poly->x1 = sy + 7;
    poly->x2 = poly->x0;
    poly->x3 = poly->x1;
    if (g_FrameCount & 0x8) {
        poly->y0 = g_Task->screen_y - 27 + (((u32)g_FrameCount >> 1) & 0x3);
    } else {
        poly->y0 = g_Task->screen_y - 24 - (((u32)g_FrameCount >> 1) & 0x3);
    }
    poly->u0 = 204;
    poly->u1 = 204;
    poly->v1 = 155;
    poly->v0 = poly->v1 + 12;
    poly->v2 = poly->v0;
    setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    poly->y1    = poly->y0;
    poly->y2    = poly->y0 + 24;
    poly->y3    = poly->y2;
    poly->u2    = poly->u0 + 24;
    poly->u3    = poly->u2;
    poly->v3    = poly->v1;
    poly->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = 0x7802;
    if (!(g_Task->param.unk_0B & 0x1)) {
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
    } else {
        GFX_AddPrim(3, sizeof(POLY_FT4));
    }
    PushMatrix();
    axis.vx = 0;
    axis.vy = 0;
    axis.vz = 0;
    rot.vx  = (s16)((g_Task->pos.x.fixed >> 9) - 0x4000);
    rot.vy  = (s16)((g_Task->pos.y.fixed >> 9) - 0x4000);
    rot.vz  = (s16)(-COORD_INT(g_Task->pos.z) / 2);
    RotTransMatrix(&rot, mtx, &flag);
    Camera_SetModelMatrix(&axis, &mtx);
    if (GetGraphType() == 1) {
        mode = 0x12E;
    } else if (GetGraphType() == 2) {
        mode = 0x12E;
    } else {
        mode = 0x5E;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, NULL);
    if (!(g_Task->param.unk_0B & 0x1)) {
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));
    } else {
        GFX_AddPrim(3, sizeof(DR_MODE));
    }
    if (g_FrameCount & 0x8) {
        radius = (s16)(0x38 - ((~((u32)g_FrameCount >> 1) & 0x3) * 2));
    } else {
        radius = (s16)(0x38 - (g_FrameCount & 0x6));
    }
    for (i = 0; i < 32; i++) {
        angle            = i << 7;
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = (s16)FIXED_MUL(radius, rcos(angle));
        D_1F800014[1].vy = (s16)FIXED_MUL(radius, rsin(angle));
        D_1F800014[1].vz = 0;
        D_1F800014[2].vx = (s16)FIXED_MUL(radius, rcos(angle + 128));
        D_1F800014[2].vy = (s16)FIXED_MUL(radius, rsin(angle + 128));
        D_1F800014[2].vz = 0;
        prim             = g_GfxPrimCursor;
        prim[3]          = 6;
        prim[7]          = 0x30;
        SetSemiTrans(prim, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)(prim + 8), (long*)(prim + 0x10), (long*)(prim + 0x18), &p, &sxy2);
        prim[4]    = 0x80;
        prim[5]    = 0x80;
        prim[6]    = 0x80;
        prim[0xC]  = 0;
        prim[0xD]  = 0;
        prim[0xE]  = 0;
        prim[0x14] = 0;
        prim[0x15] = 0;
        prim[0x16] = 0;
        if (!(g_Task->param.unk_0B & 0x1)) {
            Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_G3));
        } else {
            GFX_AddPrim(3, sizeof(POLY_G3));
        }
    }
    PopMatrix();
}
