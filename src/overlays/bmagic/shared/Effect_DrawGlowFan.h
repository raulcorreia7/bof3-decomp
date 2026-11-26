/* Draws a sixteen-part semi-transparent fan of RADIUS around the effect screen point, the centre corner in SHADE grey,
 * between a draw mode on each side. A statement macro: the member declares POLY_G3* poly, s32 tpage and s32 i. */
/* func_801EF7FC (magic040), func_801EF920 (magic042) */
#define EFFECT_DRAW_GLOW_FAN(RADIUS, SHADE)                                                                                                                                                      \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);                                                                                                                                 \
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage);                                                                                                                                  \
    i                            = 0;                                                                                                                                                            \
    g_ScratchPad.cells.halves[2] = (RADIUS);                                                                                                                                                     \
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->screen_x.value;                                                                                                                            \
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->screen_y.value;                                                                                                                            \
    do {                                                                                                                                                                                         \
        poly = (POLY_G3*)g_GfxPrimCursor;                                                                                                                                                        \
        SetPolyG3(poly);                                                                                                                                                                         \
        SetSemiTrans(poly, 1);                                                                                                                                                                   \
        setXY3(poly, g_ScratchPad.cells.halves[0], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[0] + ((rsin(i << 9) * g_ScratchPad.cells.halves[2]) >> 12),                           \
               g_ScratchPad.cells.halves[1] + ((rcos(i << 9) * g_ScratchPad.cells.halves[2]) >> 12), g_ScratchPad.cells.halves[0] + ((rsin((i + 1) << 9) * g_ScratchPad.cells.halves[2]) >> 12), \
               g_ScratchPad.cells.halves[1] + ((rcos((i + 1) << 9) * g_ScratchPad.cells.halves[2]) >> 12));                                                                                      \
        setRGB0(poly, (SHADE), (SHADE), (SHADE));                                                                                                                                                \
        setRGB1(poly, 1, 1, 1);                                                                                                                                                                  \
        setRGB2(poly, 1, 1, 1);                                                                                                                                                                  \
        GFX_AddPrim(BMAGIC_LAYER_OVER_BATTLERS, sizeof(POLY_G3));                                                                                                                                \
        i++;                                                                                                                                                                                     \
    } while (i < 16);                                                                                                                                                                            \
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);                                                                                                                                \
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, tpage)
