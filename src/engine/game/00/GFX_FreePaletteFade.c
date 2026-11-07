#include "game_00.h"

MATCH void GFX_FreePaletteFade(u8 index) {
    Actor* target;
    u8     saved;

    if ((D_80145BD4[index].flags & PALETTE_FADE_ACTIVE) == 0u) {
        return;
    }
    if ((D_80145BD4[index].flags & 0x80u) != 0u) {
        D_80145BD4[index].target->active_flags &= 0xFBu;
    }
    target                  = D_80145BD4[index].target;
    saved                   = D_80145BD4[index].saved_byte;
    D_80145BD4[index].flags = 0u;
    target->unk_27          = saved;
    GFX_MarkPaletteCells(D_80145BD4[index].table_index, index, 0u);
}
