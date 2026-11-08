/* The dark ring: a flat ring of 64 subtractive Gouraud quads around the effect matrix, between the radii in
 * scratchpad params 0 (inner) and 1 (outer). The outer edge subtracts nothing; the inner edge subtracts
 * params[shade_slot] from each channel, so the ring darkens toward its centre. Each member sets the draw mode
 * and the three params, then runs this with its ordering-table layer. A statement macro, not a static
 * inline: the static inline form builds 64 bytes longer with a different frame. One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* BMagic_DrawDarkRing: magic053 func_801EFA30, magic110 func_801EFC98, magic220 func_801EFC40, magic222
 * func_801EFACC and magic226 func_801EFA64. */
#define BMAGIC_DARK_RING_SEGMENTS 64 /* 64 steps of 64 make the full 4096 circle */

/* The quad corners, outer pair first. */
extern SVECTOR D_1F800014[];

#define BMAGIC_DRAW_DARK_RING_QUADS(layer, shade_slot)                                                              \
    do {                                                                                                            \
        POLY_G4* prim;                                                                                              \
        long     depth;                                                                                             \
        long     flag;                                                                                              \
        s32      i;                                                                                                 \
                                                                                                                    \
        D_1F800014[1].vx = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);                                    \
        D_1F800014[1].vy = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);                                    \
        D_1F800014[3].vx = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);                                    \
        D_1F800014[3].vy = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);                                    \
        D_1F800014[3].vz = 0;                                                                                       \
        D_1F800014[2].vz = 0;                                                                                       \
        D_1F800014[1].vz = 0;                                                                                       \
        D_1F800014[0].vz = 0;                                                                                       \
        for (i = 1; i <= BMAGIC_DARK_RING_SEGMENTS; i++) {                                                          \
            prim = (POLY_G4*)g_GfxPrimCursor;                                                                       \
            SetPolyG4(prim);                                                                                        \
            SetSemiTrans(prim, 1);                                                                                  \
            D_1F800014[0].vx = D_1F800014[1].vx;                                                                    \
            D_1F800014[0].vy = D_1F800014[1].vy;                                                                    \
            D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[1]);                           \
            D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[1]);                           \
            D_1F800014[2].vx = D_1F800014[3].vx;                                                                    \
            D_1F800014[2].vy = D_1F800014[3].vy;                                                                    \
            D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[0]);                           \
            D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[0]);                           \
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0,         \
                          (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);                     \
            setRGB0(prim, 1, 1, 1);                                                                                 \
            setRGB1(prim, 1, 1, 1);                                                                                 \
            setRGB2(prim, D_1F800000.view.effect.params[(shade_slot)], D_1F800000.view.effect.params[(shade_slot)], \
                    D_1F800000.view.effect.params[(shade_slot)]);                                                   \
            setRGB3(prim, D_1F800000.view.effect.params[(shade_slot)], D_1F800000.view.effect.params[(shade_slot)], \
                    D_1F800000.view.effect.params[(shade_slot)]);                                                   \
            GFX_AddPrim((layer), 0x24);                                                                             \
        }                                                                                                           \
    } while (0)
