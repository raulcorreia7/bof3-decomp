#include "battle_03.h"

MATCH void func_801D94D4(s32 x, u32 y, s32 clut_index, s32 text_value) {
    u8    index;
    u8    temp;
    u8    digit;
    SPRT* packet;
    u16   clut;

    index = 0;
    if ((u16)text_value == 0xFFFFu) {
        sprintf(g_UiFormatBuffer, D_801D0C70);
    } else {
        sprintf(g_UiFormatBuffer, D_801D0C74, (u16)text_value);
    }
    GFX_AddDrawMode(GetTPage(0, 0, 960, 0));

    do {
        temp = g_UiFormatBuffer[index];
        if (temp != ' ') {
            g_UiFormatBuffer[index] = temp - '0';
            packet                  = (SPRT*)g_GfxPrimCursor;
            clut                    = GetClut((clut_index & BYTE_MASK) << 4, 480);
            packet->clut            = clut;
            PSX_SET_NEUTRAL_RGB(packet);
            packet->x0 = x;
            packet->y0 = y;
            digit      = g_UiFormatBuffer[index];
            packet->v0 = 216;
            packet->w  = 6;
            packet->h  = 5;
            packet->u0 = digit * 6u - 80u;
            SetSprt(packet);
            GFX_AddPrim(1, 0x14);
        }

        x += 5;
    } while (g_UiFormatBuffer[++index] != 0);
}
