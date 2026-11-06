#include "area030_04.h"

/* Draws the AREA030 panel sprite selected by icon_index at the position it
 * is given, sourcing its CLUT, size and texture coordinates from the panel
 * table, and appends it to the ordering-table layer layer names. */
MATCH u8* func_801E0DCC(s32 icon_index, s32 layer, s16 sprite_x, s16 sprite_y) {
    SPRT* sprite;

    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    setRGB0(sprite, 128, 128, 128);
    setXY0(sprite, sprite_x, sprite_y);
    sprite->clut = getClut(D_801E2424[icon_index & BYTE_MASK].unk_00, D_801E2424[icon_index & BYTE_MASK].unk_04);
    setWH(sprite, D_801E2424[icon_index & BYTE_MASK].width, D_801E2424[icon_index & BYTE_MASK].height);
    setUV0(sprite, D_801E2424[icon_index & BYTE_MASK].u, D_801E2424[icon_index & BYTE_MASK].v);
    GFX_AddPrim((u8)layer, 0x14);
    return (u8*)sprite;
}
