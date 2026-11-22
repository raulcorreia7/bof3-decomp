#include "engine/slus/slus.h"

/* clears the 0x10-stride flag byte selected by slot when its bit 0 is set.
 */
MATCH void GFX_PaletteFreeSlot(s32 slot) {
    if (g_PaletteAnimations[slot & BYTE_MASK].flags & 0x1u) {
        g_PaletteAnimations[slot & BYTE_MASK].flags = 0u;
    }
}
