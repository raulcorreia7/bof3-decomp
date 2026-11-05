#include "area030_04.h"

/* Draws the AREA030 panel sprite selected by icon_index at the position it
 * is given, sourcing its CLUT, size and texture coordinates from the panel
 * table, and appends it to the ordering-table layer layer names. */
MATCH u8* func_801E0DCC(s32 icon_index, s32 layer, s16 sprite_x, s16 sprite_y) {
    SPRT* sprite;

    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    PSX_SET_NEUTRAL_RGB(sprite);
    sprite->x0 = sprite_x;
    sprite->y0 = sprite_y;
    sprite->clut =
        ((D_801E2424[icon_index & BYTE_MASK].unk_04 << 6) | ((D_801E2424[icon_index & BYTE_MASK].unk_00 >> 4) & 0x3F));
    sprite->w  = D_801E2424[icon_index & BYTE_MASK].width;
    sprite->h  = D_801E2424[icon_index & BYTE_MASK].height;
    sprite->u0 = D_801E2424[icon_index & BYTE_MASK].u;
    sprite->v0 = D_801E2424[icon_index & BYTE_MASK].v;
    GFX_AddPrim((u8)layer, 0x14);
    return (u8*)sprite;
}
