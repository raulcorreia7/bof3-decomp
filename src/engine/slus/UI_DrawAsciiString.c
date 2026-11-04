#include "engine/slus/slus.h"

/* draws the ASCII string at (x, y + 1) as 8x12 sprite cells:
 * advances x by 8 per character, starts a new row 12 pixels down on a
 * newline, and skips spaces and the terminator.
 */
MATCH void UI_DrawAsciiString(s16 left, s16 top, s32 flags, u8* text) {
    /* FAKE: the two pins reproduce retail's callee-saved assignment; the logic
     * alone lets the allocator pick different saved registers. */
    MATCH_FAKE_PIN(SPRT*, sprite, "s1"); /* FAKE: sprite cursor */
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
        MATCH_FAKE_PIN(s32, attr, "s0");
        attr = flags;
        func_8014FC00(0);
        color = (u16)((attr & 0x3F) | 0x7800);
    }
    x0     = x;
    shade  = 0x80;
    sprite = (SPRT*)g_GfxPrimCursor;
    do {
        if (*str == '\n') {
            x = x0;
            y += 0xC;
        } else if (*str != ' ' && *str != '\0') {
            sprite->w    = 8;
            sprite->clut = color;
            setRGB0(sprite, shade, shade, shade);
            sprite->h  = 12;
            sprite->u0 = (u8)(((*str - '0') % 31) * 8);
            value      = ((*str - '0') / 31) * 0xC + 0x48;
            sprite->x0 = x;
            sprite->y0 = y;
            sprite->v0 = (u8)value;
            SetSprt(sprite);
            PSX_SET_SEMI_TRANSPARENT(sprite);
            GFX_AddPrim(1, 0x14);
            sprite = (SPRT*)g_GfxPrimCursor;
        }
        str++;
        x += 8;
    } while (*str != '\0');
}
