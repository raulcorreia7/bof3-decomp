#include "battle_15.h"

/* claims `count` packets of `size` bytes for the map cell at the packed (pos_x, pos_y) position: in
 * each pass the largest remaining value pins the packet at base + its index * size.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed) {
    u8*    cursor;
    u8*    next;
    P_TAG* packet;
    u8*    address;
    u32    offset;
    u32    limit;
    u32    addend;
    u32    adjust;
    u32    slot;
    u32    claim;
    u32    entry;
    u32    best;
    u32    cell;
    u32    total;
    s32    tile_x;
    s32    tile_y;
    /* FAKE: retail frames 0x10 bytes; the callee base frame is 8, and no statement uses the other 8. */
    FAKE_STACK_PADS(u8, 8);

    tile_x = (pos_x >> 16) - g_AreaTileOriginX;
    tile_y = (pos_y >> 16) - g_AreaTileOriginY;
    if (pos_x & HALF_MASK) {
        tile_y += 1;
    }
    /* FAKE: keeps tile_x in its own pseudo so the sum lands in a fresh register, as Area_AddCellPrim. */
    tile_x++;
    tile_x--;
    cell = tile_x;
    cell += tile_y;
    addend = seed & BYTE_MASK;
    if (pos_y & HALF_MASK) {
        adjust = addend + 1;
        total  = cell + adjust;
    } else {
        total = cell + addend;
    }
    slot = size & BYTE_MASK;
    if ((u32)total >= 0x38) {
        g_GfxPrimCursor -= count * size;
    } else {
        cursor = g_GfxPrimCursor;
        limit  = g_GfxBufferIndex * 0x9000 + PRIM_ARENA_BASE;
        next   = cursor + slot;
        if (next < limit) {
            offset = (g_GfxBufferIndex + 4) * 8 + total * 0x30;
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
                        packet       = *(P_TAG**)(D_80142CC4 + offset);
                        address      = base + best * slot;
                        setaddr(packet, address);
                        *(u8**)(D_80142CC4 + offset) = (u8*)address;
                    }
                    claim++;
                } while (claim < (count & BYTE_MASK));
            }
        } else {
            g_GfxPrimCursor -= count * slot;
        }
    }
}
#else
INCLUDE_ASM(func_800AF0F8);
#endif
