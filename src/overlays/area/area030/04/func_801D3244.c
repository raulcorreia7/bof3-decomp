#include "area030_04.h"

/* Sets the graphic-0 draw mode on the work layer, places the panel
 * sprite at (x, y), gives it the requested width and shifts its u coordinate,
 * then, unless the shared state word masks the layer off (bit 8), sets graphic
 * 6 and appends the matching semi-transparent tile primitive to the layer. */
MATCH void func_801D3244(s16 panel_x, s16 panel_y, u8 panel_width, s8 u_offset, u8 ot_layer, s8 is_enabled) {
    TILE* prim;
    SPRT* sprite;
    u8    width;
    s16   x;
    s16   y;
    s8    u_shift;
    u8    enabled;
    u8    layer;
    s32   w;

    layer   = ot_layer;
    x       = panel_x;
    y       = panel_y;
    enabled = is_enabled;
    u_shift = u_offset;
    width   = panel_width;

    func_801E0C80(0, layer);
    sprite     = (SPRT*)func_801E0DCC(0x1C, layer, x, y);
    w          = width & BYTE_MASK;
    sprite->w  = w;
    sprite->u0 = sprite->u0 + u_shift;

    if (enabled != 0 && (g_FrameCount & 8) == 0) {
        func_801E0C80(6, 2);
        prim = (TILE*)g_GfxPrimCursor;
        SetTile(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        prim->h  = 8;
        prim->x0 = x;
        prim->y0 = y;
        prim->w  = w;
        setRGB0(prim, 255, 0, 0);
        GFX_AddPrim(layer, 0x10);
    }
}
