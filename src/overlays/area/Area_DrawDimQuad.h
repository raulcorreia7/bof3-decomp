/* Draws a semi-transparent Gouraud quad of one shade of red over the whole 320x320 screen with dithering on; the caller declares `POLY_G4* prim`. */
/* func_801F2C3C, func_801F2D18, func_801F2E10, Area_DrawFadeQuad (area188), func_801F71C0 (scena01) */
#define AREA_DRAW_DIM_QUAD(abr, shade)                                                   \
    GFX_AddDitheredDrawMode(6U, GetTPage(TPAGE_DEPTH_15BIT, abr, 320, 320) & HALF_MASK); \
    prim = (POLY_G4*)g_GfxPrimCursor;                                                    \
    SetPolyG4(prim);                                                                     \
    setRGB0(prim, prim->r1 = (shade), prim->g1 = 0, prim->b1 = 0);                       \
    setRGB2(prim, prim->r3 = (shade), prim->g3 = 0, prim->b3 = 0);                       \
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, 320, SCREEN_WIDTH, 320);                      \
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);                                          \
    GFX_AddPrim(2U, sizeof(POLY_G4))
