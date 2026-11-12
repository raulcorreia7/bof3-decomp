#include "game_00.h"

MATCH s32 GFX_AllocPaletteFade(void* target, s32 red, s32 green, s32 blue, s32 flag_value) {
    s32 slot;
    s32 result;
    s32 value;
    s32 flagged;
    u8  tmp_a;
    u8  tmp_b;

    value   = flag_value * 2 + 0x41;
    flagged = value | 0x80;

    for (slot = 0; slot < PALETTE_FADE_COUNT; slot++) {
        if ((g_PaletteFades[slot].flags & PALETTE_FADE_ACTIVE) == 0) {
            g_PaletteFades[slot].flags = value;
            if ((PALETTE_OWNER(target)->palette_kind == PALETTE_KIND_CELL) && ((PALETTE_OWNER(target)->flags & 0x4) == 0)) {
                g_PaletteFades[slot].flags = flagged;
            }
            result                            = slot & BYTE_MASK;
            g_PaletteFades[slot].step         = GFX_MarkPaletteCells(PALETTE_OWNER(target)->palette_kind, result, 1);
            tmp_a                             = PALETTE_OWNER(target)->saved_byte;
            g_PaletteFades[slot].saved_byte   = tmp_a;
            tmp_b                             = PALETTE_OWNER(target)->palette_kind;
            g_PaletteFades[slot].target       = target;
            g_PaletteFades[slot].offset.red   = red;
            g_PaletteFades[slot].offset.green = green;
            g_PaletteFades[slot].offset.blue  = blue;
            g_PaletteFades[slot].table_index  = tmp_b;
            return result;
        }
    }
    return 0xFF;
}
