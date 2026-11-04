#include "engine/slus/slus.h"

/* clears the 0x10-stride flag byte selected by slot when its bit 0 is set.
 */
MATCH void GFX_FreePaletteSlot(s32 slot) {
    u32 offset;

    offset = (slot & BYTE_MASK) * 0x10;
    if (*(u8*)((char*)D_80145D94 + offset) & 1u) {
        *(u8*)((char*)D_80145D94 + offset) = 0u;
    }
}
