#include "engine/slus/slus.h"

/* writes one 4-byte cell record into the bundle's cell area: the u16 grid slot under (row, column) holds
 * the record id, and the record is copied from cell+4 (cell+8 while D_8014933C is zero) to the scaled slot after the
 * 4bpp cell image.
 */
MATCH void Area_CellWriteRecord(u8* cell) {
    u32  scratch[2];
    u32* src;
    u32* dst;

    src = (u32*)(cell + 4);
    dst = &AREA_MAP_TILES[*(AREA_MAP_GRID + cell[1] + cell[0] * AREA_MAP_BUNDLE->width)];
    if (D_8014933C == 0) {
        src = (u32*)(cell + 8);
    }
    *dst = *src;
}
