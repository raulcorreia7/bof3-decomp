#include "engine/slus/slus.h"

/* scans the 0x10-stride slot table at D_80145DA0 and hands the index
 * of every entry whose key word equals match_key to func_8014E484.
 */
MATCH void GFX_FreePaletteSlotOwner(s32 match_key) {
    s32 index;
    s32 offset;
    s32 key;

    key    = match_key;
    index  = 0;
    offset = 0;
    do {
        if (*(u32*)(((u8*)&D_80145DA0) + offset) == key) {
            GFX_FreePaletteSlot(index & BYTE_MASK);
        }
        index += 1;
        offset += 0x10;
    } while (index < 8);
}
