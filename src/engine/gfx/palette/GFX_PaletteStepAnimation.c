#include "engine/game/00/game_00.h"

MATCH void GFX_PaletteStepAnimation(u8 palette_slot) {
    GraphicsPaletteAnimation* slot;
    PaletteAnimationStep*     entry;
    u8                        id;

    slot = &g_PaletteAnimations[palette_slot];
    id   = slot->owner[0x4B];
    if (id != slot->unk_02) {
        slot->current_entry = ((PaletteAnimationStep**)slot->source_table)[id];
        slot->unk_01        = slot->current_entry->frames;
        slot->unk_02        = slot->owner[0x4B];
    }
    if (slot->unk_01 == 0) {
        PaletteAnimationStep* next;

        entry               = slot->current_entry;
        next                = entry + 1;
        slot->current_entry = next;
        if (entry[1].dst_column == GAME_NONE) {
            slot->current_entry = next - entry[1].src_column;
        }
        slot->unk_01 = slot->current_entry->frames;
    }
    GFX_PaletteCopyAnimationColors(slot);
    slot->unk_01--;
}
