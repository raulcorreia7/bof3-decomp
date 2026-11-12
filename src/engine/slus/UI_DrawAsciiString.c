#include "engine/slus/slus.h"

/* draws the ASCII string at (x, y + 1) as 8x12 sprite cells:
 * advances x by 8 per character, starts a new row 12 pixels down on a
 * newline, and skips spaces and the terminator.
 */
MATCH void UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text) {
    /* FAKE: the two pins reproduce retail's callee-saved assignment; the logic
     * alone lets the allocator pick different saved registers. */
    FAKE_REG(SPRT*, sprite, "s1"); /* FAKE: sprite cursor */
    u8* str;
    s16 x;
    s16 y;
    u8  shade;
    s16 x0;
    u16 color;
    s32 value;

    str = text;
    x   = left;
    y   = top + 1;
    {
        /* FAKE: the attribute copy shares s0 with the divisor constant. */
        FAKE_REG(s32, attr, "s0");
        attr = flags;
        func_8014FC00(0);
        color = ((attr & 0x3F) | STAGE_PALETTE_CLUT);
    }
    x0     = x;
    shade  = 0x80;
    sprite = (SPRT*)g_GfxPrimCursor;
    do {
        if (*str == '\n') {
            x = x0;
            y += 12;
        } else if (*str != ' ' && *str != '\0') {
            sprite->clut = color;
            setRGB0(sprite, shade, shade, shade);
            setWH(sprite, 8, 12);
            sprite->u0 = (((*str - '0') % 31) * 8);
            value      = ((*str - '0') / 31) * 0xC + 0x48;
            setXY0(sprite, x, y);
            sprite->v0 = value;
            SetSprt(sprite);
            SetSemiTrans(sprite, 1);
            GFX_AddPrim(1, sizeof(SPRT));
            sprite = (SPRT*)g_GfxPrimCursor;
        }
        str++;
        x += 8;
    } while (*str != '\0');
}
