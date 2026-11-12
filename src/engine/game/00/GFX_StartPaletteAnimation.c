#include "game_00.h"

MATCH u8 GFX_StartPaletteAnimation(u8* owner, u8* source_table) {
    u8 palette_slot;

    for (palette_slot = 0u; palette_slot < 8u; palette_slot++) {
        if ((D_80145D94[palette_slot].flags & 0x1u) == 0u) {
            D_80145D94[palette_slot].flags        = 1u;
            D_80145D94[palette_slot].owner        = owner;
            D_80145D94[palette_slot].source_table = source_table;
            D_80145D94[palette_slot].unk_02       = 0xFFu;
            D_80145D94[palette_slot].unk_03       = owner[0x27];
            return palette_slot;
        }
    }
    return 0xFFu;
}
