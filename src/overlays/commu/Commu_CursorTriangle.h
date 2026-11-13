/* The blinking cursor triangle of the commu overlays: it picks this frame's flat colour and queues a
 * POLY_F3 with its three points around the cell at x, y. The member declares `POLY_F3* poly` and
 * `u8 colour`.
 * Members: commu01/07 func_801D3984, commu02/08 func_801D88A4. */
#define COMMU_DRAW_CURSOR_TRIANGLE(X, Y, FLAG)          \
    if ((u8)(FLAG) == 0) {                              \
        if ((g_FrameCount & 8) != 0) {                  \
            colour = ((g_FrameCount & 6) << 5) | 0x3F;  \
        } else {                                        \
            colour = ((~g_FrameCount & 6) << 5) | 0x3F; \
        }                                               \
    } else {                                            \
        colour = 0xFF;                                  \
    }                                                   \
    poly = g_GfxPrimCursor;                             \
    SetPolyF3(poly);                                    \
    poly->x0 = (X);                                     \
    poly->y0 = (Y);                                     \
    poly->x1 = (X) - 4;                                 \
    poly->y1 = (Y) - 4;                                 \
    poly->x2 = (X) + 4;                                 \
    poly->y2 = (Y) - 4;                                 \
    poly->r0 = 0;                                       \
    poly->g0 = colour;                                  \
    poly->b0 = 0;                                       \
    GFX_AddPrim(1, sizeof(POLY_F3))
