#include "battle_03.h"

MATCH void func_801D7D10(u8 clut_index, u16 x, u16 y, u16 width, u8 height, u8 shade) {
    BattleIconPalette clut_table;
    POLY_FT4*        primitive;
    s32              u0;

    clut_table = D_801D0C64;
    GFX_AddDrawMode(GetTPage(0, 0, 256, 256));
    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    setRGB0(primitive, shade, shade, shade);
    setXY4(primitive, x, y, x + (u8)width, y, x, y + height, x + (u8)width, y + height);
    u0 = clut_index * 0x18;
    setUV4(primitive, u0, 224, u0 + 24, 224, u0, 248, u0 + 24, 248);
    primitive->tpage = GetTPage(0, 0, 256, 256);
    primitive->clut  = (clut_table.bytes[clut_index] & 0x3F) | STAGE_PALETTE_CLUT;
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
