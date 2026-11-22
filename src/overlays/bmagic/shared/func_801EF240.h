/* The textured ring band of magic055 (func_801EF240) and magic091 (func_801EF240): 32 GT4 quads around the
 * effect cell, each under its own draw mode, the outer edge rising and falling with the phase (byte 0x0B) and
 * the inner edge shaded by it. ABR is the blend rate of the quads and of their draw mode. The caller declares prim, depth, flag, i, tpage, x, y and
 * phase. Every change must verify both member images. */
#define BMAGIC_DRAW_RING_BAND(ABR)                                                                                                                                                                \
    g_ScratchPad.cells.halves[0] = g_Task->unk_09 * 4;                                                                                                                                            \
    g_ScratchPad.cells.halves[2] = g_Task->unk_09 * 3;                                                                                                                                            \
    g_ScratchPad.cells.halves[3] = (g_Task->timer + 16) * 4;                                                                                                                                      \
    g_ScratchPad.cells.halves[4] = (g_Task->param.unk_0B & 0xF) << 8;                                                                                                                             \
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);                                                                                                              \
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);                                                                                                              \
    g_ScratchPadVectors[1].vz    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]) - g_ScratchPad.cells.halves[3];                                                    \
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[2]);                                                                                                              \
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[2]);                                                                                                              \
    g_ScratchPadVectors[3].vz    = 0;                                                                                                                                                             \
    for (i = 1; i <= 32; i++) {                                                                                                                                                                   \
        phase                        = g_Task->param.unk_0B;                                                                                                                                      \
        g_ScratchPad.cells.halves[4] = ((i + phase) & 0xF) << 8;                                                                                                                                  \
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;                                                                                                                                 \
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;                                                                                                                                 \
        g_ScratchPadVectors[0].vz    = g_ScratchPadVectors[1].vz;                                                                                                                                 \
        g_ScratchPadVectors[1].vx    = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[0]);                                                                                                     \
        g_ScratchPadVectors[1].vy    = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[0]);                                                                                                     \
        g_ScratchPadVectors[1].vz    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[4]), g_ScratchPad.cells.halves[3]) - g_ScratchPad.cells.halves[3];                                                \
        g_ScratchPadVectors[2].vx    = g_ScratchPadVectors[3].vx;                                                                                                                                 \
        g_ScratchPadVectors[2].vy    = g_ScratchPadVectors[3].vy;                                                                                                                                 \
        g_ScratchPadVectors[2].vz    = 0;                                                                                                                                                         \
        g_ScratchPadVectors[3].vx    = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[2]);                                                                                                     \
        g_ScratchPadVectors[3].vy    = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[2]);                                                                                                     \
        g_ScratchPadVectors[3].vz    = 0;                                                                                                                                                         \
        x                            = (g_ScratchPadVectors[1].vx << 9) + g_Task->pos.x.fixed;                                                                                                    \
        y                            = (g_ScratchPadVectors[1].vx << 9) + g_Task->pos.y.fixed;                                                                                                    \
        tpage                        = getTPage(TPAGE_DEPTH_4BIT, (ABR), 320, 256);                                                                                                               \
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);                                                                                                                                   \
        Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));                                                                                                                                               \
        prim = (POLY_GT4*)g_GfxPrimCursor;                                                                                                                                                        \
        SetPolyGT4(prim);                                                                                                                                                                         \
        SetSemiTrans(prim, 1);                                                                                                                                                                    \
        setTPage(prim, TPAGE_DEPTH_4BIT, (ABR), 832, 256);                                                                                                                                        \
        setClut(prim, 0, 506);                                                                                                                                                                    \
        setUV4(prim, i * 4, g_Task->param.unk_0B * 4 + 32, i * 4 + 4, g_Task->param.unk_0B * 4 + 32, i * 4, g_Task->param.unk_0B * 4 + 48, i * 4 + 4, g_Task->param.unk_0B * 4 + 48);             \
        g_ScratchPad.cells.halves[5] = 104 - g_Task->param.unk_0B * 3;                                                                                                                            \
        setRGB0(prim, 1, 1, 1);                                                                                                                                                                   \
        setRGB1(prim, 1, 1, 1);                                                                                                                                                                   \
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);                                                                                  \
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);                                                                                  \
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, \
                      &depth, &flag);                                                                                                                                                             \
        Area_CellAddPrim(x, y, 2, sizeof(POLY_GT4));                                                                                                                                              \
    }
