#include "engine/slus/slus.h"

/* clears the 0x10-stride flag byte selected by slot when its bit 0 is set.
 */
MATCH void GFX_FreePaletteSlot(s32 slot) {
    if (D_80145D94[slot & 0xFF].flags & 1u) {
        D_80145D94[slot & 0xFF].flags = 0u;
    }
}
