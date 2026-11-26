/* The blinking cursor triangle of the commu overlays: it picks this frame's flat colour and queues a
 * POLY_F3 with its three points around the cell at x, y. The member declares `POLY_F3* poly` and
 * `u8 colour`.
 * Members: commu01/07 Fairy_DrawCursor, commu02/08 func_801D88A4. */
#define COMMU_DRAW_CURSOR_TRIANGLE(X, Y, FLAG)                  \
    if ((u8)(FLAG) == 0) {                                      \
        if ((g_FrameCount & 8) != 0) {                          \
            colour = ((g_FrameCount & 6) << 5) | 0x3F;          \
        } else {                                                \
            colour = ((~g_FrameCount & 6) << 5) | 0x3F;         \
        }                                                       \
    } else {                                                    \
        colour = 0xFF;                                          \
    }                                                           \
    poly = g_GfxPrimCursor;                                     \
    SetPolyF3(poly);                                            \
    setXY3(poly, (X), (Y), (X) - 4, (Y) - 4, (X) + 4, (Y) - 4); \
    setRGB0(poly, 0, colour, 0);                                \
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F3))
