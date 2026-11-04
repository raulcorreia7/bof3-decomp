#include "game_00.h"

MATCH void GFX_FreePaletteFade(u8 index) {
    u8* target;
    u8  saved;

    if ((D_80145BD4[index].flags & 1u) == 0u) {
        return;
    }
    if ((D_80145BD4[index].flags & 0x80u) != 0u) {
        D_80145BD4[index].target[0x24] &= 0xFBu;
    }
    target                  = D_80145BD4[index].target;
    saved                   = D_80145BD4[index].unk_01;
    D_80145BD4[index].flags = 0u;
    target[0x27]            = saved;
    GFX_MarkPaletteCells(D_80145BD4[index].table_index, index, 0u);
}
