#include "game_00.h"

/* Draws the formatted work-record byte as 8x8 digit sprites starting at (x, y). */
MATCH void func_8019F5B8(s16 x, s16 y, u8 unused, u8 palette) {
    SPRT* sprt;
    s32   index;
    s32   next;
    u8    ch;

    index = 0;
    TEXT_Format(g_UiFormatBuffer, D_80195860, g_Task->unk_06);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), NULL);
    GFX_AddPrim(g_Task->unk_29, sizeof(DR_MODE));
    do {
        ch = g_UiFormatBuffer[index & BYTE_MASK];
        if (ch != ' ') {
            g_UiFormatBuffer[index & BYTE_MASK] = ch - '0';
            sprt                                = (SPRT*)g_GfxPrimCursor;
            setClut(sprt, palette * 16, STAGE_PALETTE_Y);
            setRGB0(sprt, 128, 128, 128);
            setXY0(sprt, x, y);
            setUV0(sprt, g_UiFormatBuffer[index & BYTE_MASK] * 8 - 80, 208);
            setWH(sprt, 8, 8);
            SetSprt(sprt);
            GFX_AddPrim(g_Task->unk_29, sizeof(SPRT));
        }
        x += 8;
        next  = index + 1;
        index = next;
    } while (g_UiFormatBuffer[next & BYTE_MASK] != 0);
}
