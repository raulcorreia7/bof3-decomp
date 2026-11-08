/* The area floor quad: one textured POLY_FT4 laid flat at the actor's cell, its long side along x or y as
 * direction_08 picks, and its corners lifted to the terrain by Area_SampleHeight. Each member passes the
 * sprite word for func_80155560; area160 and area162 to area165 share Area_UpdateFloorQuad.h. A statement macro, not a
 * static inline: the word is read after RotTransPers4, and an inline argument would load it first. Every
 * change here must verify every member. */
extern SVECTOR D_1F800014[];

#define AREA_DRAW_FLOOR_QUAD(sprite)                                                                    \
    do {                                                                                                \
        POLY_FT4* prim;                                                                                 \
        long      depth;                                                                                \
        long      flag;                                                                                 \
        s32       y;                                                                                    \
        s32       x;                                                                                    \
        s32       y1;                                                                                   \
        s32       x1;                                                                                   \
                                                                                                        \
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(1, 0, 320, 256), NULL);                   \
        GFX_AddPrim(6, 0xC);                                                                            \
        prim = (POLY_FT4*)g_GfxPrimCursor;                                                              \
        SetPolyFT4(prim);                                                                               \
        SetShadeTex(prim, 0);                                                                           \
        if (g_Task->direction_08 != 0) {                                                                \
            D_1F800014[0].vy = D_1F800014[1].vy = D_1F800014[2].vy = D_1F800014[3].vy =                 \
                (((g_Task->pos.y.fixed >> 16) - 0x80) << 7) | 0x40;                                     \
            D_1F800014[0].vx = D_1F800014[2].vx =                                                       \
                (((g_Task->pos.x.fixed >> 16) - 0x7F) << 7) - (g_Task->screen_y - 0x40);                \
            D_1F800014[1].vx = D_1F800014[3].vx =                                                       \
                (((g_Task->pos.x.fixed >> 16) - 0x80) << 7) - (g_Task->screen_y + 0x40);                \
        } else {                                                                                        \
            D_1F800014[0].vx = D_1F800014[1].vx = D_1F800014[2].vx = D_1F800014[3].vx =                 \
                (((g_Task->pos.x.fixed >> 16) - 0x80) << 7) | 0x40;                                     \
            D_1F800014[0].vy = D_1F800014[2].vy =                                                       \
                (((g_Task->pos.y.fixed >> 16) - 0x7F) << 7) + (g_Task->screen_y + 0x40);                \
            D_1F800014[1].vy = D_1F800014[3].vy =                                                       \
                (((g_Task->pos.y.fixed >> 16) - 0x80) << 7) + (s16)(g_Task->screen_y - 0x40);           \
        }                                                                                               \
        x                = (D_1F800014[0].vx + 0x4000) << 9;                                            \
        y                = (D_1F800014[0].vy + 0x4000) << 9;                                            \
        D_1F800014[0].vz = -Area_SampleHeight(x, y) / 2 + 0x40;                                         \
        D_1F800014[2].vz = -Area_SampleHeight(x, y) / 2 + 0x180;                                        \
        x1               = (D_1F800014[1].vx + 0x4000) << 9;                                            \
        y1               = (D_1F800014[1].vy + 0x4000) << 9;                                            \
        D_1F800014[1].vz = -Area_SampleHeight(x1, y1) / 2 + 0x40;                                       \
        D_1F800014[3].vz = -Area_SampleHeight(x1, y1) / 2 + 0x180;                                      \
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, \
                      (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);             \
        func_80155560((sprite), prim, 1);                                                               \
        GFX_AddPrim(6, 0x28);                                                                           \
    } while (0)
