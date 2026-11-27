/* Fades the cell marker out: draws the draw mode and cell primitive of the frame, fills the scratch corners of the actor cell through SET_CORNERS, queues the semi-transparent quad in the timer's shade and the outline DRAW_OUTLINE; at timer 0 the step returns to 1. FLAGS is the image's per-actor flag table. */
#define AREA_FADING_CELL_STEP(FLAGS, SET_CORNERS, DRAW_OUTLINE)                                                                                                                            \
    POLY_F4* primitive;                                                                                                                                                                    \
    s32      shade;                                                                                                                                                                        \
    long     depth;                                                                                                                                                                        \
    long     flag;                                                                                                                                                                         \
                                                                                                                                                                                           \
    SELF(Actor)->timer--;                                                                                                                                                                  \
    if (SELF(Actor)->timer == 0) {                                                                                                                                                         \
        SELF(Actor)->header.step = 1;                                                                                                                                                      \
    }                                                                                                                                                                                      \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256), NULL);                                                                               \
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(DR_MODE));                                                                                              \
    SET_CORNERS(SELF(Actor)->param.unk_0B + SYS_TestFlag(D_80144ED0, FLAGS[SELF(Actor)->param.unk_0B]) * 4 + 1, AREA_CELL_HALF);                                                           \
    primitive = (POLY_F4*)g_GfxPrimCursor;                                                                                                                                                 \
    SetPolyF4(primitive);                                                                                                                                                                  \
    SetSemiTrans(primitive, 1);                                                                                                                                                            \
    shade         = SELF(Actor)->timer * 30;                                                                                                                                               \
    primitive->b0 = shade;                                                                                                                                                                 \
    primitive->g0 = shade;                                                                                                                                                                 \
    primitive->r0 = shade;                                                                                                                                                                 \
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&primitive->x0, (long*)&primitive->x1, (long*)&primitive->x2, \
                  (long*)&primitive->x3, &depth, &flag);                                                                                                                                   \
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_F4));                                                                                              \
    DRAW_OUTLINE();
