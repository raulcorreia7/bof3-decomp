#include "area082_13.h"

/* Scales the 0x100 colours of the palette source window by scale (0x80 is unity)
 * into the working copy, then flags the upload. */
MATCH void func_801F5388(s32 scale) {
    u16*       dst;
    const u16* src;
    u32        color;
    s32        red;
    s32        green;
    s32        blue;
    s32        i;

    i   = 0;
    dst = (u16*)(AREA_PALETTE_WORK + 0x800);
    src = (const u16*)(AREA_PALETTE_ARENA + 0x800);
    do {
        color = *src++;
        red   = ((s32)(color & 0x1F) * scale) >> 7;
        green = ((s32)((color & 0xFFFF) >> 5 & 0x1F) * scale) >> 7;
        blue  = ((s32)((color & 0xFFFF) >> 10 & 0x1F) * scale) >> 7;
        *dst  = (u16)((color & 0x8000) | (blue << 10) | (green << 5) | red);
        dst++;
        i++;
    } while (i < 0x100);
    g_GfxPalettePending = 1;
}
