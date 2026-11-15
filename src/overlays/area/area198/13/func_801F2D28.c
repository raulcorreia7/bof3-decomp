#include "area198_13.h"

MATCH void func_801F2D28(s32 scale) {
    s32        block;
    u16*       destination;
    const u16* source;
    u16*       out;
    const u16* in;
    u16*       limit;
    u32        color;
    u32        packed;
    s32        green;
    s32        blue;

    /* The two palette blocks this pass scales: destination then source. */
    block       = 0;
    destination = MEM_PTR(u16, AREA_PALETTE_WORK + 0x800u);
    source      = MEM_PTR(const u16, AREA_PALETTE_ARENA + 0x800u);
    do {
        out   = destination;
        in    = source;
        limit = destination + 0x100;
        do {
            color  = *in;
            packed = ((s32)(color & 0x1F) * scale) / 0x80;
            green  = ((s32)((color & 0xFFFF) >> 5 & 0x1F) * scale) / 0x80;
            blue   = ((s32)((color & 0xFFFF) >> 10 & 0x1F) * scale) / 0x80;
            packed |= (blue << 10) | (green << 5);
            if (packed == 0 && (color & 0xFFFF) != 0) {
                packed = 0x8000;
            }
            *out++ = (u16)packed;
            in++;
        } while ((s32)out < (s32)limit);
        destination += 0x100;
        block++;
        source += 0x100;
    } while (block < 2);
    g_GfxPalettePending = 1;
}
