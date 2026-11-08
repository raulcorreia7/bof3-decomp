#include "battle_03.h"

MATCH void func_801D9804(s32 x, s32 y, s32 clut_index, s32 glyph_index) {
    SPRT* packet;
    u16   clut;

    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));

    packet       = (SPRT*)g_GfxPrimCursor;
    clut         = GetClut((clut_index & BYTE_MASK) << 4, STAGE_PALETTE_Y);
    packet->clut = clut;
    setRGB0(packet, 128, 128, 128);
    setUV0(packet, ((glyph_index & BYTE_MASK) * 24 + 104), 208);
    setXY0(packet, x, y);
    setWH(packet, 24, 8);
    SetSprt(packet);
    GFX_AddPrim(1, sizeof(SPRT));
}
