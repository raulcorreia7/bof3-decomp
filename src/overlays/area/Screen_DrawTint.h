/* Draws a semi-transparent tile over the whole screen in the colour of the task's tint. One definition shared by
 * the area overlays and scena13 (which has a second copy under another name); each member passes its function name,
 * ordering table layer and draw-mode texture page. Every change here must verify every member. */
#define SCREEN_TINT_BODY(name, layer, tpage)                         \
    MATCH void name(void) {                                          \
        TILE* tile;                                                  \
        u8    blue;                                                  \
                                                                     \
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (tpage), NULL); \
        GFX_AddPrim((layer), 0xCU);                                  \
        tile = (TILE*)g_GfxPrimCursor;                               \
        SetTile(tile);                                               \
        tile->r0 = g_Task->tint.bytes.unk_5D;                        \
        tile->g0 = g_Task->tint.bytes.unk_5E;                        \
        blue     = g_Task->tint.bytes.unk_5F;                        \
        tile->w  = 0x140;                                            \
        tile->x0 = 0;                                                \
        tile->y0 = 0;                                                \
        tile->h  = 0xF0;                                             \
        tile->b0 = blue;                                             \
        SetSemiTrans(tile, 1);                                       \
        SetShadeTex(tile, 0);                                        \
        GFX_AddPrim((layer), 0x10U);                                 \
    }
