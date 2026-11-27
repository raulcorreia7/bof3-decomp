#include "engine/game/00/game_00.h"

MATCH void GFX_PaletteUploadRows(void) {
    Actor* work;
    u32    table_index;
    /* FAKE: retail keeps the dividend in v1. */
    FAKE_REG(u32, value, "v1");
    /* FAKE: retail keeps the divisor in v0. */
    FAKE_REG(u32, divisor, "v0");
    /* FAKE: retail keeps the quotient in a3. */
    FAKE_REG(u32, quotient, "a3");
    u32           remainder;
    u32           flags;
    u32           stride;
    u32           start;
    u32           cell_base;
    Actor*        loop_work;
    u32           product;
    volatile u16* colors;
    u32           color_index;

    work        = SELF(Actor);
    table_index = work->palette_8bit;
    value       = work->clut_select;
    divisor     = s_PaletteFadeRowDivisors[table_index];
    quotient    = value / divisor;
    remainder   = value % divisor;
    flags       = work->active_flags;
    stride      = s_PaletteFadeStrides[table_index];
    product     = stride * remainder;
    if ((flags & 0x4u) != 0u) {
        start = quotient + 0x10u;
    } else {
        start = quotient;
    }
    color_index = 1u;
    if (color_index < (s_PaletteFadeColorCounts[table_index] << 4)) {
        colors    = g_GraphicsPaletteDst + (start & BYTE_MASK) * 256u;
        cell_base = product & BYTE_MASK;
        loop_work = work;
        do {
            colors[cell_base + color_index] |= PSX_COLOR_STP_BIT;
            color_index++;
        } while (color_index < (s_PaletteFadeColorCounts[loop_work->palette_8bit] << 4));
    }
    g_GfxPalettePending = 1u;
}
