#include "engine/slus/slus.h"

/* claims a packet slot for the map cell at the packed (x, y) position: an in-range slot under the
 * buffer's packet limit takes a 0x30-byte record whose tag address becomes the cursor.
 */
MATCH void Area_AddCellPrim(s32 x, s32 y, s32 depth, s32 size) {
    u8* cursor;
    u8* next;
    u8* packet;
    u32 offset;
    u32 limit;
    s32 index;
    s32 value;
    s32 cell;
    s32 seed;
    s32 count;
    s32 addend;

    index = (x >> 16) - g_AreaTileOriginX;
    value = (y >> 16) - g_AreaTileOriginY;
    if (x & HALF_MASK) {
        value += 1;
    }
    /* FAKE: keeps index in its own pseudo so the sum lands in a fresh register; pure C best 93.33. */
    index++;
    index--;
    cell = index;
    cell += value;
    seed = (s8)depth;
    if (y & HALF_MASK) {
        addend = seed + 1;
        count  = cell + addend;
    } else {
        count = cell + seed;
    }
    if ((u32)count < 56) {
        cursor = g_GfxPrimCursor;
        limit  = g_FrameBufferIndex * 0x9000 + PRIM_ARENA_BASE;
        next   = cursor + (size & BYTE_MASK);
        if ((u32)next < limit) {
            offset = (g_FrameBufferIndex + 4) * 8 + count * 0x30;
            packet = *(u8**)(D_80142CC4 + offset);
            setaddr(packet, cursor);
            g_GfxPrimCursor              = next;
            *(u32*)(D_80142CC4 + offset) = (u32)cursor;
        }
    }
}
