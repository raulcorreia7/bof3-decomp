extern SVECTOR D_1F800014[];

/* Fades the cell marker out: draws the draw mode and cell primitive of the frame, fills the scratch corners of the actor cell through SET_CORNERS, queues the semi-transparent quad in the timer's shade and the outline DRAW_OUTLINE; at timer 0 the step returns to 1. FLAGS is the image's per-actor flag table. */
/* AREA_FADING_CELL_STEP (area117 0x801F36CC, area118 0x801F447C) */
#define AREA_FADING_CELL_STEP(FLAGS, SET_CORNERS, DRAW_OUTLINE)                                                                                                                               \
    POLY_F4* primitive;                                                                                                                                                                       \
    s32      shade;                                                                                                                                                                           \
    long     depth;                                                                                                                                                                           \
    long     flag;                                                                                                                                                                            \
                                                                                                                                                                                              \
    g_Task->timer--;                                                                                                                                                                          \
    if (g_Task->timer == 0) {                                                                                                                                                                 \
        g_Task->header.step = 1;                                                                                                                                                              \
    }                                                                                                                                                                                         \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(1, 1, 320, 256), NULL);                                                                                                             \
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(DR_MODE));                                                                                                           \
    SET_CORNERS(g_Task->param.unk_0B + SYS_TestFlag(D_80144ED0, FLAGS[g_Task->param.unk_0B]) * 4 + 1, AREA_CELL_HALF);                                                                        \
    primitive = (POLY_F4*)g_GfxPrimCursor;                                                                                                                                                    \
    SetPolyF4(primitive);                                                                                                                                                                     \
    SetSemiTrans(primitive, 1);                                                                                                                                                               \
    shade         = g_Task->timer * 30;                                                                                                                                                       \
    primitive->b0 = shade;                                                                                                                                                                    \
    primitive->g0 = shade;                                                                                                                                                                    \
    primitive->r0 = shade;                                                                                                                                                                    \
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, (long*)&primitive->x3, &depth, &flag); \
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_F4));                                                                                                           \
    DRAW_OUTLINE();
