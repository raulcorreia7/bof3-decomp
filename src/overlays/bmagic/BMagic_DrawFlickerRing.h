#ifndef BMAGIC_DRAW_FLICKER_RING_H
#define BMAGIC_DRAW_FLICKER_RING_H

/* Draws eight semi-transparent triangles in a ring round the effect's screen point, the radius flickering by up to
 * seven past four per counter tick; the centre colour is the counter times the three steps, the rim colour 1. A
 * statement macro: the member declares POLY_G3* prim, s32 i and s32 tpage. */
/* func_801F083C (magic097), func_801F00C4 (magic098) */
#define BMAGIC_DRAW_FLICKER_RING(RED_STEP, GREEN_STEP, BLUE_STEP)                                                                                                                      \
    D_1F800000.view.effect.params[0] = (rand() & 7) + g_Task->timer * 4;                                                                                                               \
    if (GetGraphType() == 1 || GetGraphType() == 2) {                                                                                                                                  \
        tpage = 0xA5;                                                                                                                                                                  \
    } else {                                                                                                                                                                           \
        tpage = 0x35;                                                                                                                                                                  \
    }                                                                                                                                                                                  \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                            \
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));                                                                                                    \
    for (i = 0; i < 8; i++) {                                                                                                                                                          \
        prim = (POLY_G3*)g_GfxPrimCursor;                                                                                                                                              \
        SetPolyG3(prim);                                                                                                                                                               \
        SetSemiTrans(prim, 1);                                                                                                                                                         \
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), D_1F800000.view.effect.params[0]),                                        \
               g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), D_1F800000.view.effect.params[0]), g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 9), D_1F800000.view.effect.params[0]), \
               g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 9), D_1F800000.view.effect.params[0]));                                                                                 \
        setRGB0(prim, g_Task->timer * (RED_STEP), g_Task->timer * (GREEN_STEP), g_Task->timer * (BLUE_STEP));                                                                          \
        setRGB1(prim, 1, 1, 1);                                                                                                                                                        \
        setRGB2(prim, 1, 1, 1);                                                                                                                                                        \
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));                                                                                                \
    }

#endif
