/* Draws a black, semi-transparent Gouraud quad over the whole 320x320 screen with dithering on. */
/* func_801F2C3C, func_801F2D18, func_801F2E10 (area188), func_801F71C0 (scena01) */
#define AREA_DRAW_DIM_QUAD(abr)                                          \
    POLY_G4* prim;                                                       \
    GFX_AddDitheredDrawMode(6U, GetTPage(2, abr, 320, 320) & HALF_MASK); \
    prim = (POLY_G4*)g_GfxPrimCursor;                                    \
    SetPolyG4(prim);                                                     \
    setRGB0(prim, prim->r1 = 0, prim->g1 = 0, prim->b1 = 0);             \
    setRGB2(prim, prim->r3 = 0, prim->g3 = 0, prim->b3 = 0);             \
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, 320, SCREEN_WIDTH, 320);      \
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);                          \
    GFX_AddPrim(2U, sizeof(POLY_G4))
