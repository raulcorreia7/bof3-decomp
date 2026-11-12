/* Draws a black, semi-transparent Gouraud quad over the whole 320x320 screen with dithering on. */
/* AREA_DRAW_DIM_QUAD (area188 0x801F2C3C, area188 0x801F2D18) */
#define AREA_DRAW_DIM_QUAD()                                               \
    POLY_G4* prim;                                                         \
    GFX_AddDitheredDrawMode(6U, GetTPage(2, 2, 0x140, 0x140) & HALF_MASK); \
    prim = (POLY_G4*)g_GfxPrimCursor;                                      \
    SetPolyG4(prim);                                                       \
    setRGB0(prim, prim->r1 = 0, prim->g1 = 0, prim->b1 = 0);               \
    setRGB2(prim, prim->r3 = 0, prim->g3 = 0, prim->b3 = 0);               \
    setXY4(prim, 0, 0, 0x140, 0, 0, 0x140, 0x140, 0x140);                  \
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);                            \
    GFX_AddPrim(2U, sizeof(POLY_G4))
