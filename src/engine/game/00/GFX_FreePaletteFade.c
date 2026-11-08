#include "game_00.h"

MATCH void GFX_FreePaletteFade(u8 index) {
    PaletteOwner* target;
    u8            saved;

    if ((g_PaletteFades[index].flags & PALETTE_FADE_ACTIVE) == 0u) {
        return;
    }
    if ((g_PaletteFades[index].flags & 0x80u) != 0u) {
        g_PaletteFades[index].target->flags &= 0xFBu;
    }
    target                      = g_PaletteFades[index].target;
    saved                       = g_PaletteFades[index].saved_byte;
    g_PaletteFades[index].flags = 0u;
    target->saved_byte          = saved;
    GFX_MarkPaletteCells(g_PaletteFades[index].table_index, index, 0u);
}
