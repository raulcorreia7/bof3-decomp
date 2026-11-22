#include "engine/slus/slus.h"

/* empties the two cell packet lists the buffer index selects in every grid
 * row, then advances to the next row; the buffer's own pair is SYS_PrepareFrame's.
 */
MATCH void Area_CellResetPacketLists(void) {
    u8* base;
    u32 level;
    s32 row;
    s32 row_offset;
    s32 column;
    u32 column_offset;
    u32 address;
    u32 slot;

    row        = 0;
    level      = g_GfxBufferIndex & BYTE_MASK;
    base       = (u8*)&D_80142CC0;
    row_offset = 0;
    do {
        column        = 0;
        column_offset = level;
        do {
            address = column_offset << 3;
            column++;
            slot                       = address + row_offset;
            address                    = address + base;
            *(u32*)(D_80142CC4 + slot) = row_offset + address;
            *(u32*)(D_80142CC0 + slot) = 0;
            column_offset += 2;
        } while (column < 2);
        row++;
        row_offset += 0x30;
    } while (row < 56);
}
