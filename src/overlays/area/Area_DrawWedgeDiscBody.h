/* Draws eight semi-transparent Gouraud wedges around (x, y): a fan of `radius` starting at `angle`,
 * one wedge per 0x100 of the angle, each coloured by the index the work record stores at byte 6.
 * The image queues the wedge with its own primitive call. */
/* func_801F30C0 (area042), func_801F3274 (area048), func_801F3504 (area139) */
#define AREA_DRAW_WEDGE_DISC_BODY(color_r, color_g, color_b, queue)                                           \
    POLY_G3* prim;                                                                                            \
    u8       i;                                                                                               \
                                                                                                              \
    i = 0;                                                                                                    \
    do {                                                                                                      \
        prim     = GFX_BeginPolyG3(1);                                                                        \
        prim->x0 = x;                                                                                         \
        prim->y0 = y;                                                                                         \
        prim->x1 = x + FIXED_MUL(radius, rcos(angle));                                                        \
        prim->y1 = y + FIXED_MUL(radius, rsin(angle));                                                        \
        angle += 0x100;                                                                                       \
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));                                                        \
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));                                                        \
        setRGB0(prim, color_r[g_Task->unk_06 * 3], color_g[g_Task->unk_06 * 3], color_b[g_Task->unk_06 * 3]); \
        setRGB1(prim, 0, 0, 0);                                                                               \
        setRGB2(prim, 0, 0, 0);                                                                               \
        queue;                                                                                                \
        i += 1;                                                                                               \
    } while (i < 8)
