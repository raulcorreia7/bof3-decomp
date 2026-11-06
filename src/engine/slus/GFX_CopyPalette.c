#include "engine/slus/slus.h"

/* copies 0x100 halfwords from the 0x80033800 bank into the 0x80037800 bank
 * for the 0x200-stride slot selected by slot, then marks the copy complete.
 */
MATCH void GFX_CopyPalette(s32 slot) {
    u32        count;
    u16*       dst;
    const u16* src;
    u16*       base_dst;
    const u16* base_src;
    u32        offset;

    count    = 0u;
    base_dst = MEM_PTR(u16, AREA_PALETTE_WORK);
    base_src = MEM_PTR(const u16, 0x80033800u);
    offset   = (slot & BYTE_MASK) * 0x100u;
    dst      = base_dst + offset;
    src      = base_src + offset;
    do {
        *dst++ = *src++;
        count++;
    } while (count < 256u);
    g_GfxPalettePending = 1u;
}
