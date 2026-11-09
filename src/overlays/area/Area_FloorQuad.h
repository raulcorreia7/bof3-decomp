/* The area floor quad: one textured POLY_FT4 laid flat at the actor's cell, its long side along x or y as direction_08 picks. */
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
        GFX_AddPrim(6, sizeof(DR_MODE));                                                                \
        prim = (POLY_FT4*)g_GfxPrimCursor;                                                              \
        SetPolyFT4(prim);                                                                               \
        SetShadeTex(prim, 0);                                                                           \
        if (g_Task->direction_08 != 0) {                                                                \
            D_1F800014[0].vy = D_1F800014[1].vy = D_1F800014[2].vy = D_1F800014[3].vy =                 \
                ((FIX_INT(g_Task->pos.y.fixed) - 0x80) << 7) | 0x40;                                    \
            D_1F800014[0].vx = D_1F800014[2].vx =                                                       \
                ((FIX_INT(g_Task->pos.x.fixed) - 0x7F) << 7) - (g_Task->screen_y - 0x40);               \
            D_1F800014[1].vx = D_1F800014[3].vx =                                                       \
                ((FIX_INT(g_Task->pos.x.fixed) - 0x80) << 7) - (g_Task->screen_y + 0x40);               \
        } else {                                                                                        \
            D_1F800014[0].vx = D_1F800014[1].vx = D_1F800014[2].vx = D_1F800014[3].vx =                 \
                ((FIX_INT(g_Task->pos.x.fixed) - 0x80) << 7) | 0x40;                                    \
            D_1F800014[0].vy = D_1F800014[2].vy =                                                       \
                ((FIX_INT(g_Task->pos.y.fixed) - 0x7F) << 7) + (g_Task->screen_y + 0x40);               \
            D_1F800014[1].vy = D_1F800014[3].vy =                                                       \
                ((FIX_INT(g_Task->pos.y.fixed) - 0x80) << 7) + (s16)(g_Task->screen_y - 0x40);          \
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
        GFX_AddPrim(6, sizeof(POLY_FT4));                                                               \
    } while (0)
