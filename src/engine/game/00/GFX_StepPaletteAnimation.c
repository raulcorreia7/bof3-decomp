#include "game_00.h"

MATCH void GFX_StepPaletteAnimation(u8 slot_index) {
    GraphicsPaletteAnimation* slot;
    u8*                       entry;
    u8                        id;

    slot = &D_80145D94[slot_index];
    id   = slot->owner[0x4B];
    if (id != slot->unk_02) {
        slot->current_entry = ((u8**)slot->source_table)[id];
        slot->unk_01        = slot->current_entry[3];
        slot->unk_02        = slot->owner[0x4B];
    }
    if (slot->unk_01 == 0) {
        u8* next;

        entry               = slot->current_entry;
        next                = entry + 4;
        slot->current_entry = next;
        if (entry[4] == GAME_NONE) {
            slot->current_entry = next - entry[5] * 4;
        }
        slot->unk_01 = slot->current_entry[3];
    }
    GFX_CopyPaletteAnimationColors(slot);
    slot->unk_01--;
}
