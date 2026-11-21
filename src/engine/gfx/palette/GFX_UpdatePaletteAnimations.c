#include "engine/game/00/game_00.h"

MATCH void GFX_UpdatePaletteAnimations(void) {
    u8 palette_slot;

    for (palette_slot = 0u; palette_slot < 8u; palette_slot++) {
        if ((g_PaletteAnimations[palette_slot].flags & 0x1u) != 0u) {
            GFX_StepPaletteAnimation(palette_slot);
        }
    }
}
