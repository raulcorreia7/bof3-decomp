#include "engine/game/00/game_00.h"

MATCH u8 GFX_StartPaletteAnimation(u8* owner, u8* source_table) {
    u8 palette_slot;

    for (palette_slot = 0u; palette_slot < 8u; palette_slot++) {
        if ((g_PaletteAnimations[palette_slot].flags & 0x1u) == 0u) {
            g_PaletteAnimations[palette_slot].flags        = 1u;
            g_PaletteAnimations[palette_slot].owner        = owner;
            g_PaletteAnimations[palette_slot].source_table = source_table;
            g_PaletteAnimations[palette_slot].unk_02       = 0xFFu;
            g_PaletteAnimations[palette_slot].unk_03       = owner[0x27];
            return palette_slot;
        }
    }
    return 0xFFu;
}
