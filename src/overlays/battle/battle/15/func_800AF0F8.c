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
    u32    stride;
    u32    claim;
    u32    entry;
    u32    best;
    u32    cell;
    u32    total;
    u32    buffer;
    s32    tile_x;
    s32    tile_y;

    tile_x = (pos_x >> 16) - g_AreaTileOriginX;
    tile_y = (pos_y >> 16) - g_AreaTileOriginY;
    if (pos_x & HALF_MASK) {
        tile_y += 1;
    }
    /* FAKE: keeps tile_x in its own pseudo so the sum lands in a fresh register, as Area_CellAddPrim. */
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
    if ((u32)total >= 0x38) {
        g_GfxPrimCursor -= size * count;
    } else {
        stride = size & BYTE_MASK;
        cursor = g_GfxPrimCursor;
        buffer = g_GfxBufferIndex;
        limit  = buffer * 0x9000 + PRIM_ARENA_BASE;
        next   = cursor + stride;
        if (next < limit) {
            for (claim = 0; claim < (count & BYTE_MASK); claim++) {
                best = 0;
                for (entry = 0; entry < (count & BYTE_MASK); entry++) {
                    if (values[best] < values[entry]) {
                        best = entry;
                    }
                }
                if (values[best] != 0) {
                    values[best] = 0;
                    address      = base + best * (size & BYTE_MASK);
                    offset       = (buffer + 4) * 8 + total * 0x30;
                    packet       = *(P_TAG**)(D_80142CC4 + offset);
                    setaddr(packet, address);
                    *(u8**)(D_80142CC4 + offset) = (u8*)address;
                }
            }
        } else {
            g_GfxPrimCursor -= count * stride;
        }
    }
}
#else
INCLUDE_ASM(func_800AF0F8);
#endif
