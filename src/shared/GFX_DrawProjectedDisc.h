/* Draws the glow of one area work row as a 16-segment Gouraud fan around the projected row position: the radius is
 * the row's position projected at SCALE, plus the frame parity, and the fan fades from the row's shade at the
 * centre to black at the rim. The image passes the row's world position, its shade, its projected scale and its
 * ordering-table layer. */
/* func_801F81D4 (scena07), func_801F8964 (scena08), func_801F4BC0 (area098) */
#define GFX_DRAW_PROJECTED_DISC(POS, SHADE, SCALE, LAYER)            \
    POLY_G3* packet;                                                 \
    u16      size[2];                                                \
    u16      radius[2];                                              \
    DVECTOR  screen;                                                 \
    s16      scale;                                                  \
    u16      angle;                                                  \
    u8       shade;                                                  \
                                                                     \
    size[0] = (SCALE);                                               \
    Game_ProjectWorldPoint((POS), size, radius);                     \
    Area_ProjectPoint((POS), &screen);                               \
    scale = (s16)(radius[0] + (g_FrameCount & 1));                   \
    angle = 0;                                                       \
    do {                                                             \
        packet     = GFX_BeginPolyG3(1);                             \
        packet->x0 = screen.vx;                                      \
        packet->y0 = screen.vy;                                      \
        packet->x1 = screen.vx + ((scale * rcos((u16)angle)) >> 12); \
        packet->y1 = screen.vy + ((scale * rsin((u16)angle)) >> 12); \
        angle += 256;                                                \
        packet->x2 = screen.vx + ((scale * rcos((u16)angle)) >> 12); \
        packet->y2 = screen.vy + ((scale * rsin((u16)angle)) >> 12); \
        shade      = (SHADE);                                        \
        packet->r2 = packet->g2 = packet->b2 = 0;                    \
        packet->r1 = packet->g1 = packet->b1 = 0;                    \
        packet->r0 = packet->g0 = packet->b0 = shade;                \
        GFX_AddPrim((LAYER), sizeof(POLY_G3));                       \
    } while ((u16)angle < ONE);
