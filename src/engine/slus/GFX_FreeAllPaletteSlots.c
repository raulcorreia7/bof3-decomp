#include "engine/slus/slus.h"

/* hands every slot index 0..7 of the D_80145DA0 table to
 * func_8014E484 (refresh-all).
 */
MATCH void GFX_FreeAllPaletteSlots(void) {
    s32 index;

    for (index = 0; index < 8; index++) {
        GFX_FreePaletteSlot(index & BYTE_MASK);
    }
}
