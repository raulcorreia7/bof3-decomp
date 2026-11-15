/* Draws a sixteen-part semi-transparent fan of RADIUS around the effect screen point, the centre corner in SHADE grey,
 * between a draw mode on each side. A statement macro: the member declares POLY_G3* poly, s32 tpage and s32 i. */
/* func_801EF7FC (magic040), func_801EF920 (magic042) */
#define EFFECT_DRAW_GLOW_FAN(RADIUS, SHADE)                                                                                                                                            \
    tpage = getTPage(0, 1, 320, 256);                                                                                                                                                  \
    GFX_AddDitheredDrawMode(3, tpage);                                                                                                                                                 \
    i                                = 0;                                                                                                                                              \
    D_1F800000.view.effect.params[2] = (RADIUS);                                                                                                                                       \
    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;                                                                                                                            \
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;                                                                                                                            \
    do {                                                                                                                                                                               \
        poly = (POLY_G3*)g_GfxPrimCursor;                                                                                                                                              \
        SetPolyG3(poly);                                                                                                                                                               \
        SetSemiTrans(poly, 1);                                                                                                                                                         \
        setXY3(poly, D_1F800000.view.effect.params[0], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[0] + ((rsin(i << 9) * D_1F800000.view.effect.params[2]) >> 12), \
               D_1F800000.view.effect.params[1] + ((rcos(i << 9) * D_1F800000.view.effect.params[2]) >> 12),                                                                           \
               D_1F800000.view.effect.params[0] + ((rsin((i + 1) << 9) * D_1F800000.view.effect.params[2]) >> 12),                                                                     \
               D_1F800000.view.effect.params[1] + ((rcos((i + 1) << 9) * D_1F800000.view.effect.params[2]) >> 12));                                                                    \
        setRGB0(poly, (SHADE), (SHADE), (SHADE));                                                                                                                                      \
        setRGB1(poly, 1, 1, 1);                                                                                                                                                        \
        setRGB2(poly, 1, 1, 1);                                                                                                                                                        \
        GFX_AddPrim(3, sizeof(POLY_G3));                                                                                                                                               \
        i++;                                                                                                                                                                           \
    } while (i < 16);                                                                                                                                                                  \
    tpage = getTPage(0, 0, 320, 256);                                                                                                                                                  \
    GFX_AddDitheredDrawMode(3, tpage)
