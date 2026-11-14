/* The textured ring band of magic055 (func_801EF240) and magic091 (func_801EF240): 32 GT4 quads around the
 * effect cell, each under its own draw mode, the outer edge rising and falling with the phase (byte 0x0B) and
 * the inner edge shaded by it. ABR is the blend rate of the quads and of their draw mode. The caller declares prim, depth, flag, i, tpage, x, y and
 * phase. Every change must verify both member images. */
#define BMAGIC_DRAW_RING_BAND(ABR)                                                                                                                                                    \
    D_1F800000.view.effect.params[0] = g_Task->unk_09 * 4;                                                                                                                            \
    D_1F800000.view.effect.params[2] = g_Task->unk_09 * 3;                                                                                                                            \
    D_1F800000.view.effect.params[3] = (g_Task->timer + 16) * 4;                                                                                                                      \
    D_1F800000.view.effect.params[4] = (g_Task->param.unk_0B & 0xF) << 8;                                                                                                             \
    D_1F800014[1].vx                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);                                                                                          \
    D_1F800014[1].vy                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);                                                                                          \
    D_1F800014[1].vz                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]) - D_1F800000.view.effect.params[3];                        \
    D_1F800014[3].vx                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[2]);                                                                                          \
    D_1F800014[3].vy                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[2]);                                                                                          \
    D_1F800014[3].vz                 = 0;                                                                                                                                             \
    for (i = 1; i <= 32; i++) {                                                                                                                                                       \
        phase                            = g_Task->param.unk_0B;                                                                                                                      \
        D_1F800000.view.effect.params[4] = ((i + phase) & 0xF) << 8;                                                                                                                  \
        D_1F800014[0].vx                 = D_1F800014[1].vx;                                                                                                                          \
        D_1F800014[0].vy                 = D_1F800014[1].vy;                                                                                                                          \
        D_1F800014[0].vz                 = D_1F800014[1].vz;                                                                                                                          \
        D_1F800014[1].vx                 = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[0]);                                                                                 \
        D_1F800014[1].vy                 = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[0]);                                                                                 \
        D_1F800014[1].vz                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]) - D_1F800000.view.effect.params[3];                    \
        D_1F800014[2].vx                 = D_1F800014[3].vx;                                                                                                                          \
        D_1F800014[2].vy                 = D_1F800014[3].vy;                                                                                                                          \
        D_1F800014[2].vz                 = 0;                                                                                                                                         \
        D_1F800014[3].vx                 = FIXED_MUL(rcos(i << 7), D_1F800000.view.effect.params[2]);                                                                                 \
        D_1F800014[3].vy                 = FIXED_MUL(rsin(i << 7), D_1F800000.view.effect.params[2]);                                                                                 \
        D_1F800014[3].vz                 = 0;                                                                                                                                         \
        x                                = (D_1F800014[1].vx << 9) + g_Task->pos.x.fixed;                                                                                             \
        y                                = (D_1F800014[1].vx << 9) + g_Task->pos.y.fixed;                                                                                             \
        tpage                            = getTPage(0, (ABR), 320, 256);                                                                                                              \
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                       \
        Area_AddCellPrim(x, y, 2, sizeof(DR_MODE));                                                                                                                                   \
        prim = (POLY_GT4*)g_GfxPrimCursor;                                                                                                                                            \
        SetPolyGT4(prim);                                                                                                                                                             \
        SetSemiTrans(prim, 1);                                                                                                                                                        \
        setTPage(prim, 0, (ABR), 832, 256);                                                                                                                                           \
        setClut(prim, 0, 506);                                                                                                                                                        \
        setUV4(prim, i * 4, g_Task->param.unk_0B * 4 + 32, i * 4 + 4, g_Task->param.unk_0B * 4 + 32, i * 4, g_Task->param.unk_0B * 4 + 48, i * 4 + 4, g_Task->param.unk_0B * 4 + 48); \
        D_1F800000.view.effect.params[5] = 104 - g_Task->param.unk_0B * 3;                                                                                                            \
        setRGB0(prim, 1, 1, 1);                                                                                                                                                       \
        setRGB1(prim, 1, 1, 1);                                                                                                                                                       \
        setRGB2(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5]);                                                          \
        setRGB3(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5]);                                                          \
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);         \
        Area_AddCellPrim(x, y, 2, sizeof(POLY_GT4));                                                                                                                                  \
    }
