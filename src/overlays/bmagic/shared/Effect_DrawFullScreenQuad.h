/* Draws a full-screen semi-transparent quad, its grey following the effect tick, with a draw mode on each side, in
 * ordering-table slot LAYER. A statement macro: the member declares POLY_F4* prim, s32 shade and s32 tpage. */
/* func_801F030C (magic131), func_801EF970 (magic111) */
#define EFFECT_DRAW_FULL_SCREEN_QUAD(LAYER)                 \
    if (GetGraphType() == 1) {                              \
        tpage = 0xA5;                                       \
    } else if (GetGraphType() == 2) {                       \
        tpage = 0xA5;                                       \
    } else {                                                \
        tpage = 0x35;                                       \
    }                                                       \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0); \
    GFX_AddPrim(LAYER, sizeof(DR_MODE));                    \
    prim = (POLY_F4*)g_GfxPrimCursor;                       \
    SetPolyF4(prim);                                        \
    SetSemiTrans(prim, 1);                                  \
    setXY4(prim, 0, 0, 0x13F, 0, 0, 0xEF, 0x13F, 0xEF);     \
    shade = g_Task->unk_09 * 15;                            \
    setRGB0(prim, shade, shade, shade);                     \
    GFX_AddPrim(LAYER, sizeof(POLY_F4));                    \
    if (GetGraphType() == 1) {                              \
        tpage = 0x25;                                       \
    } else if (GetGraphType() == 2) {                       \
        tpage = 0x25;                                       \
    } else {                                                \
        tpage = 0x15;                                       \
    }                                                       \
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0); \
    GFX_AddPrim(LAYER, sizeof(DR_MODE))
