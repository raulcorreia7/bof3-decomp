/* Draws a sixteen-part semi-transparent fan of RADIUS around the effect screen point, the centre corner in SHADE grey,
 * between a draw mode on each side. A statement macro: the member declares POLY_G3* poly, s32 tpage and s32 i. */
/* func_801EF7FC (magic040), func_801EF920 (magic042) */
#define EFFECT_DRAW_GLOW_FAN(RADIUS, SHADE)                                                                                                                                            \
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;                                                                                                                  \
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
        poly->r0 = (SHADE);                                                                                                                                                            \
        poly->g0 = (SHADE);                                                                                                                                                            \
        poly->b0 = (SHADE);                                                                                                                                                            \
        poly->r1 = 1;                                                                                                                                                                  \
        poly->g1 = 1;                                                                                                                                                                  \
        poly->b1 = 1;                                                                                                                                                                  \
        poly->r2 = 1;                                                                                                                                                                  \
        poly->g2 = 1;                                                                                                                                                                  \
        poly->b2 = 1;                                                                                                                                                                  \
        GFX_AddPrim(3, sizeof(POLY_G3));                                                                                                                                               \
        i++;                                                                                                                                                                           \
    } while (i < 16);                                                                                                                                                                  \
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;                                                                                                                  \
    GFX_AddDitheredDrawMode(3, tpage)
