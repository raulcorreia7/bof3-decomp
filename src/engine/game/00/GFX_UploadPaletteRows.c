#include "game_00.h"

MATCH void GFX_UploadPaletteRows(void) {
    u8* work;
    u32 table_index;
    /* FAKE: retail keeps the dividend in v1. */
    MATCH_REG(u32, value, "v1");
    /* FAKE: retail keeps the divisor in v0. */
    MATCH_REG(u32, divisor, "v0");
    /* FAKE: retail keeps the quotient in a3. */
    MATCH_REG(u32, quotient, "a3");
    u32           remainder;
    u32           flags;
    u32           stride;
    u32           start;
    u32           cell_base;
    u8*           loop_work;
    u32           product;
    volatile u16* colors;
    u32           color_index;

    work        = (u8*)g_SpadWork;
    table_index = work[0x28];
    value       = work[0x27];
    divisor     = s_PaletteFadeRowDivisors[table_index];
    quotient    = value / divisor;
    remainder   = value % divisor;
    flags       = work[0x24];
    stride      = s_PaletteFadeStrides[table_index];
    product     = stride * remainder;
    if ((flags & 4u) != 0u) {
        start = quotient + 0x10u;
    } else {
        start = quotient;
    }
    color_index = 1u;
    if (color_index < ((u32)s_PaletteFadeColorCounts[table_index] << 4)) {
        colors    = g_GraphicsPaletteDst + (start & BYTE_MASK) * 256u;
        cell_base = product & BYTE_MASK;
        loop_work = work;
        do {
            colors[cell_base + color_index] |= 0x8000u;
            color_index++;
        } while (color_index < ((u32)s_PaletteFadeColorCounts[loop_work[0x28]] << 4));
    }
    g_GfxPalettePending = 1u;
}
