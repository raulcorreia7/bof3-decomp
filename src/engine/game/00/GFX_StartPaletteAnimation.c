#include "game_00.h"

MATCH u8 GFX_StartPaletteAnimation(u8* owner, u8* source_table) {
    u8 slot_index;

    for (slot_index = 0u; slot_index < 8u; slot_index++) {
        if ((D_80145D94[slot_index].flags & 1u) == 0u) {
            D_80145D94[slot_index].flags        = 1u;
            D_80145D94[slot_index].owner        = owner;
            D_80145D94[slot_index].source_table = source_table;
            D_80145D94[slot_index].unk_02       = 0xFFu;
            D_80145D94[slot_index].unk_03       = owner[0x27];
            return slot_index;
        }
    }
    return 0xFFu;
}
