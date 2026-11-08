#include "area087_13.h"

MATCH void func_801F4798(void) {
    POLY_FT4* prim;
    POLY_FT4* cell;
    SVECTOR*  quad;
    SVECTOR*  q1;
    SVECTOR*  q2;
    SVECTOR*  q3;
    long      depth;
    long      flag;
    s32       width;
    s32       size;
    s32       row;
    s32       col;
    s32       x_high;
    s32       y_high;

    if (g_Task->header.step == 0) {
        COORD_INT(g_Task->pos.y) += g_FrameCount & 0xF;
        g_Task->header.step++;
    }
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }

    width = g_Task->param.unk_0B - 2;
    g_Task->pos.y.fixed += 0x800 + (width << 10);
    if (D_80104001 + 8 < COORD_INT(g_Task->pos.y)) {
        COORD_INT(g_Task->pos.y) = -8;
    }

    if (abs(g_AreaTargetCellX - COORD_INT(g_Task->pos.x)) >= 0x1A &&
        abs(g_AreaTargetCellY - COORD_INT(g_Task->pos.y)) >= 0x1A) {
        return;
    }

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    quad     = D_1F800014;
    q1       = quad + 1;
    q2       = quad + 2;
    q3       = quad + 3;
    size     = ((2 - width) << 8) + abs(0xF - (g_FrameCount & 0x1F));
    x_high   = (g_Task->pos.x.fixed >> 9) - 0x3FC0;
    y_high   = (g_Task->pos.y.fixed >> 9) - 0x3FC0;
    quad->vz = -0x300;
    q1->vz   = -0x300;
    q2->vz   = -0x300;
    q3->vz   = -0x300;
    quad->vx = x_high - size;
    quad->vy = y_high - size;
    q1->vx   = x_high + size;
    q1->vy   = y_high - size;
    q2->vx   = x_high - size;
    q2->vy   = y_high + size;
    q3->vx   = x_high + size;
    q3->vy   = y_high + size;
    RotTransPers4(quad, q1, q2, q3, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    func_80155560(width | 0xBB509100, prim, 1);
    GFX_AddPrim(4, sizeof(POLY_FT4));

    for (row = 0; row < (2 - width) * 4 + 1; row++) {
        for (col = 0; col < (2 - width) * 4; col++) {
            cell = Area_FindCellQuad(COORD_INT(g_Task->pos.x) - (2 - width) + col,
                                     COORD_INT(g_Task->pos.y) - (2 - width) + row);
            if (cell == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            SetSemiTrans(prim, 1);
            *(u32*)&prim->x0 = *(u32*)&cell->x0;
            *(u32*)&prim->x1 = *(u32*)&cell->x1;
            *(u32*)&prim->x2 = *(u32*)&cell->x2;
            *(u32*)&prim->x3 = *(u32*)&cell->x3;
            prim->clut       = 0x78CB;
            prim->tpage      = getTPage(0, 2, 704, 256);
            setRGB0(prim, 0x28, 0x28, 0x28);
            prim->u0 = D_801F580C[width] + col * D_801F5814[width];
            prim->v0 =
                D_801F5810[width] + row * D_801F5814[width] - D_801F5814[width] * COORD_FRAC(g_Task->pos.y) / 0x10000;
            prim->u1 = D_801F5814[width] + (D_801F580C[width] + D_801F5814[width] * col);
            prim->v1 =
                D_801F5810[width] + row * D_801F5814[width] - D_801F5814[width] * COORD_FRAC(g_Task->pos.y) / 0x10000;
            prim->u2 = D_801F580C[width] + col * D_801F5814[width];
            prim->v2 = D_801F5814[width] + (u8)(D_801F5810[width] + row * D_801F5814[width] -
                                                D_801F5814[width] * COORD_FRAC(g_Task->pos.y) / 0x10000);
            prim->u3 = D_801F5814[width] + (D_801F580C[width] + D_801F5814[width] * col);
            prim->v3 = D_801F5814[width] + (u8)(D_801F5810[width] + row * D_801F5814[width] -
                                                D_801F5814[width] * COORD_FRAC(g_Task->pos.y) / 0x10000);
            Area_AddCellPrim((COORD_INT(g_Task->pos.x) - (2 - width) + col) << 16,
                             (COORD_INT(g_Task->pos.y) - (2 - width) + row) << 16, 1, 0x28);
        }
    }
}
