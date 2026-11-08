/* Draws a flat ring of 64 subtractive Gouraud quads around the effect matrix. The outer edge, at
 * BMAGIC_DARK_RING_OUTER, subtracts nothing; the inner edge, at BMAGIC_DARK_RING_INNER, subtracts
 * BMAGIC_DARK_RING_SHADE * 4 from each channel, so the ring darkens toward its centre. One definition
 * shared by the bmagic effect modules; every change here must verify every member. */
/* BMagic_DrawDarkRing: magic053 func_801EFA30, magic226 func_801EFA64, magic220 func_801EFC40 (shade from
 * unk_5D), magic110 func_801EFC98 (layer 2)
 * and magic222 func_801EFACC (radius from unk_14, shade from unk_09). */
#ifndef BMAGIC_DARK_RING_INNER
#define BMAGIC_DARK_RING_INNER g_Task->param.unk_0B
#endif
#ifndef BMAGIC_DARK_RING_OUTER
#define BMAGIC_DARK_RING_OUTER (g_Task->param.unk_0B * 2)
#endif
#ifndef BMAGIC_DARK_RING_SHADE
#define BMAGIC_DARK_RING_SHADE g_Task->timer
#endif
/* The ordering-table layer of the draw mode and the quads, and the scratch halfword that holds the shade. */
#ifndef BMAGIC_DARK_RING_LAYER
#define BMAGIC_DARK_RING_LAYER 5
#endif
#ifndef BMAGIC_DARK_RING_SHADE_SLOT
#define BMAGIC_DARK_RING_SHADE_SLOT 5
#endif
#define BMAGIC_DARK_RING_SHADE_CELL D_1F800000_HALF[BMAGIC_DARK_RING_SHADE_SLOT]
#define BMAGIC_DARK_RING_SEGMENTS   64 /* 64 steps of 64 make the full 4096 circle */

/* Scratchpad: the inner radius, the outer radius and the inner shade; then the quad corners, outer pair first. */
extern s16     D_1F800000_HALF[];
extern SVECTOR D_1F800014[];

MATCH void BMagic_DrawDarkRing(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    GFX_AddPrim(BMAGIC_DARK_RING_LAYER, 0xC);
    D_1F800000_HALF[0]          = BMAGIC_DARK_RING_INNER;
    D_1F800000_HALF[1]          = BMAGIC_DARK_RING_OUTER;
    BMAGIC_DARK_RING_SHADE_CELL = BMAGIC_DARK_RING_SHADE * 4;
    D_1F800014[1].vx            = FIXED_MUL(rsin(0), D_1F800000_HALF[1]);
    D_1F800014[1].vy            = FIXED_MUL(rcos(0), D_1F800000_HALF[1]);
    D_1F800014[3].vx            = FIXED_MUL(rsin(0), D_1F800000_HALF[0]);
    D_1F800014[3].vy            = FIXED_MUL(rcos(0), D_1F800000_HALF[0]);
    D_1F800014[3].vz            = 0;
    D_1F800014[2].vz            = 0;
    D_1F800014[1].vz            = 0;
    D_1F800014[0].vz            = 0;
    for (i = 1; i <= BMAGIC_DARK_RING_SEGMENTS; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), D_1F800000_HALF[1]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), D_1F800000_HALF[1]);
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), D_1F800000_HALF[0]);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), D_1F800000_HALF[0]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0,
                      (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, BMAGIC_DARK_RING_SHADE_CELL, BMAGIC_DARK_RING_SHADE_CELL, BMAGIC_DARK_RING_SHADE_CELL);
        setRGB3(prim, BMAGIC_DARK_RING_SHADE_CELL, BMAGIC_DARK_RING_SHADE_CELL, BMAGIC_DARK_RING_SHADE_CELL);
        GFX_AddPrim(BMAGIC_DARK_RING_LAYER, 0x24);
    }
}
