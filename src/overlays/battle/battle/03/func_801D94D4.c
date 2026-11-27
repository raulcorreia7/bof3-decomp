#include "battle_03.h"

MATCH void func_801D94D4(s32 x, u32 y, s32 clut_index, s32 text_value) {
    u8    index;
    u8    temp;
    u8    digit;
    SPRT* packet;
    u16   clut;

    index = 0;
    if ((u16)text_value == 0xFFFFu) {
        TEXT_FormatLiteral(g_UITextFormatBuffer, D_801D0C70);
    } else {
        TEXT_Format(g_UITextFormatBuffer, D_801D0C74, (u16)text_value);
    }
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));

    do {
        temp = g_UITextFormatBuffer[index];
        if (temp != ' ') {
            g_UITextFormatBuffer[index] = temp - '0';
            packet                      = (SPRT*)g_GfxPrimCursor;
            clut                        = GetClut((clut_index & BYTE_MASK) << 4, STAGE_PALETTE_Y);
            packet->clut                = clut;
            setRGB0(packet, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
            setXY0(packet, x, y);
            digit      = g_UITextFormatBuffer[index];
            packet->v0 = 216;
            setWH(packet, 6, 5);
            packet->u0 = digit * 6u - 80u;
            SetSprt(packet);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
        }

        x += 5;
    } while (g_UITextFormatBuffer[++index] != 0);
}
