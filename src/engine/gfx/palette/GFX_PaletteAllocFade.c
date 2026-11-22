#include "engine/game/00/game_00.h"

MATCH s32 GFX_PaletteAllocFade(void* owner, s32 red, s32 green, s32 blue, s32 fade_flags) {
    s32 slot;
    s32 result;
    s32 value;
    s32 flagged;
    u8  tmp_a;
    u8  tmp_b;

    value   = fade_flags * 2 + 0x41;
    flagged = value | 0x80;

    for (slot = 0; slot < PALETTE_FADE_COUNT; slot++) {
        if ((g_PaletteFades[slot].flags & PALETTE_FADE_ACTIVE) == 0) {
            g_PaletteFades[slot].flags = value;
            if ((PALETTE_OWNER(owner)->palette_type == PALETTE_TYPE_CELL) && ((PALETTE_OWNER(owner)->flags & 0x4) == 0)) {
                g_PaletteFades[slot].flags = flagged;
            }
            result                           = slot & BYTE_MASK;
            g_PaletteFades[slot].cell_index  = GFX_PaletteMarkCells(PALETTE_OWNER(owner)->palette_type, result, 1);
            tmp_a                            = PALETTE_OWNER(owner)->saved_byte;
            g_PaletteFades[slot].saved_byte  = tmp_a;
            tmp_b                            = PALETTE_OWNER(owner)->palette_type;
            g_PaletteFades[slot].target      = owner;
            g_PaletteFades[slot].offset.r    = red;
            g_PaletteFades[slot].offset.g    = green;
            g_PaletteFades[slot].offset.b    = blue;
            g_PaletteFades[slot].table_index = tmp_b;
            return result;
        }
    }
    return 0xFF;
}
