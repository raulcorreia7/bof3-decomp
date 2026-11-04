#include "game_00.h"

MATCH void GFX_UpdatePaletteAnimations(void) {
    u8 slot_index;

    for (slot_index = 0u; slot_index < 8u; slot_index++) {
        if ((D_80145D94[slot_index].flags & 1u) != 0u) {
            GFX_StepPaletteAnimation(slot_index);
        }
    }
}
