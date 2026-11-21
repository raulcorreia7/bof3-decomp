/* The dark ring: a flat ring of 64 subtractive Gouraud quads around the effect matrix, between the radii in scratchpad params 0 (inner) and 1 (outer). The outer edge subtracts nothing; the inner edge subtracts params[shade_slot] from each channel, so the ring darkens toward its centre. Each member sets the draw mode and the three params, then runs this with its ordering-table layer. A statement macro, not a static inline: the static inline form builds 64 bytes longer with a different frame. */
/* BMagic_DrawDarkRing: magic053 func_801EFA30 and magic226 func_801EFA64 (BMagic_DrawDarkRing.h), magic110
 * func_801EFC98, magic220 func_801EFC40 and magic222 func_801EFACC. */
#define BMAGIC_DARK_RING_SEGMENTS 64 /* 64 steps of 64 make the full 4096 circle */

/* The quad corners, outer pair first. */

#define BMAGIC_DRAW_DARK_RING_QUADS(layer, shade_slot)                                                                                                                                                \
    do {                                                                                                                                                                                              \
        POLY_G4* prim;                                                                                                                                                                                \
        long     depth;                                                                                                                                                                               \
        long     flag;                                                                                                                                                                                \
        s32      i;                                                                                                                                                                                   \
                                                                                                                                                                                                      \
        g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);                                                                                                                 \
        g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);                                                                                                                 \
        g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);                                                                                                                 \
        g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);                                                                                                                 \
        g_ScratchPadVectors[3].vz = 0;                                                                                                                                                                \
        g_ScratchPadVectors[2].vz = 0;                                                                                                                                                                \
        g_ScratchPadVectors[1].vz = 0;                                                                                                                                                                \
        g_ScratchPadVectors[0].vz = 0;                                                                                                                                                                \
        for (i = 1; i <= BMAGIC_DARK_RING_SEGMENTS; i++) {                                                                                                                                            \
            prim = (POLY_G4*)g_GfxPrimCursor;                                                                                                                                                         \
            SetPolyG4(prim);                                                                                                                                                                          \
            SetSemiTrans(prim, 1);                                                                                                                                                                    \
            g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;                                                                                                                                    \
            g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;                                                                                                                                    \
            g_ScratchPadVectors[1].vx = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[1]);                                                                                                        \
            g_ScratchPadVectors[1].vy = FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[1]);                                                                                                        \
            g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx;                                                                                                                                    \
            g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy;                                                                                                                                    \
            g_ScratchPadVectors[3].vx = FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[0]);                                                                                                        \
            g_ScratchPadVectors[3].vy = FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[0]);                                                                                                        \
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, \
                          &depth, &flag);                                                                                                                                                             \
            setRGB0(prim, 1, 1, 1);                                                                                                                                                                   \
            setRGB1(prim, 1, 1, 1);                                                                                                                                                                   \
            setRGB2(prim, g_ScratchPad.cells.halves[(shade_slot)], g_ScratchPad.cells.halves[(shade_slot)], g_ScratchPad.cells.halves[(shade_slot)]);                                                 \
            setRGB3(prim, g_ScratchPad.cells.halves[(shade_slot)], g_ScratchPad.cells.halves[(shade_slot)], g_ScratchPad.cells.halves[(shade_slot)]);                                                 \
            GFX_AddPrim((layer), sizeof(POLY_G4));                                                                                                                                                    \
        }                                                                                                                                                                                             \
    } while (0)
