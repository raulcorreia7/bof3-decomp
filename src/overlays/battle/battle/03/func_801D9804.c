#include "battle_03.h"

MATCH void func_801D9804(s32 x, s32 y, s32 clut_index, s32 glyph_index) {
    SPRT* packet;
    u16   clut;

    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));

    packet       = (SPRT*)g_GfxPrimCursor;
    clut         = GetClut((clut_index & BYTE_MASK) << 4, 480);
    packet->clut = clut;
    PSX_SET_NEUTRAL_RGB(packet);
    packet->u0 = ((glyph_index & BYTE_MASK) * 24 + 104);
    packet->v0 = 208;
    packet->w  = 24;
    packet->x0 = x;
    packet->y0 = y;
    packet->h  = 8;
    SetSprt(packet);
    GFX_AddPrim(1, 0x14);
}
