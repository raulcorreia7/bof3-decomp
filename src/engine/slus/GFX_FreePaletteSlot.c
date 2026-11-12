#include "engine/slus/slus.h"

/* clears the 0x10-stride flag byte selected by slot when its bit 0 is set.
 */
MATCH void GFX_FreePaletteSlot(s32 slot) {
    if (D_80145D94[slot & BYTE_MASK].flags & 0x1u) {
        D_80145D94[slot & BYTE_MASK].flags = 0u;
    }
}
