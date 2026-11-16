#include "area143_13.h"

MATCH void func_801F3E60(s32 shift) {
    s32        block;
    s32        i;
    u16*       destination;
    const u16* source;
    u16*       out;
    const u16* in;
    u32        color;
    s32        red;
    s32        green;
    s32        blue;

    block       = 3;
    destination = MEM_PTR(u16, AREA_PALETTE_WORK + 0x600u);
    source      = MEM_PTR(const u16, AREA_PALETTE_ARENA_33E00);

    do {
        i   = 0;
        out = destination;
        in  = source;

        do {
            color  = *in++;
            red    = (s32)(color & 0x1F) >> shift;
            green  = (s32)((color & 0xFFFFu) >> 5 & 0x1F) >> shift;
            blue   = (s32)((color & 0xFFFFu) >> 10 & 0x1F) >> shift;
            *out++ = (u16)((color & PSX_COLOR_STP_BIT) | (blue << 10) | (green << 5) | red);
            i++;
        } while (i < 0x100);

        destination += 0x100;
        block++;
        source += 0x100;
    } while (block < 0xE);

    g_GfxPalettePending = 1;
}
