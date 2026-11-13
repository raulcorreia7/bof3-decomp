#include "battle_15.h"

/* claims `count` packets of `size` bytes for the map cell at the packed (pos_x, pos_y) position: an in-range
 * cell under the buffer limit repeatedly picks and clears an entry of values[] and links the packet word to base +
 * entry * size.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, s32 base, u8 count, u8 size, u8 seed) {
    u8*  packet;
    u32* word;
    u32  offset;
    u32  best;
    u32  claim;
    u32  entry;
    u32  slot;
    u32  address;
    s32  cell;
    s32  tile_x;
    s32  tile_y;
    s32  addend;
    /* FAKE: retail frames 0x10 bytes; the callee base frame is 8, and no statement uses the other 8. */
    FAKE_STACK_PADS(u8, 8);

    tile_x = (pos_x >> 16) - g_AreaTileOriginX;
    tile_y = (pos_y >> 16) - g_AreaTileOriginY;
    if (pos_x & HALF_MASK) {
        tile_y += 1;
    }
    cell   = tile_x + tile_y;
    addend = seed & BYTE_MASK;
    if (pos_y & HALF_MASK) {
        cell = cell + (addend + 1);
    } else {
        cell = cell + addend;
    }
    slot = size & BYTE_MASK;
    if ((u32)cell >= 0x38) {
        g_GfxPrimCursor -= count * size;
    } else if ((u32)&g_GfxPrimCursor[slot] < (u32)(MEM_PTR(u8, PRIM_ARENA_BASE) + g_FrameBufferIndex * 0x9000)) {
        offset = (g_FrameBufferIndex + 4) * 8 + (u32)cell * 0x30;
        if ((count & BYTE_MASK) != 0) {
            claim = 0;
            do {
                best = 0;
                for (entry = 0; entry < (count & BYTE_MASK); entry++) {
                    if (values[best] < values[entry]) {
                        best = entry;
                    }
                }
                if (values[best] != 0) {
                    values[best] = 0;
                    packet       = FIELD(u8*, D_80142CC4, offset);
                    word         = (u32*)packet;
                    address      = (u32)base + best * slot;
                    setaddr(word, address);
                    FIELD(u8*, D_80142CC4, offset) = (u8*)address;
                }
                claim += 1;
            } while (claim < (count & BYTE_MASK));
        }
    } else {
        g_GfxPrimCursor -= count * size;
    }
}
#else
INCLUDE_ASM(func_800AF0F8);
#endif
