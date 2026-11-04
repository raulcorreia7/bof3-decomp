#include "engine/slus/slus.h"

/* writes one 4-byte cell record into the bundle's cell area: the u16 grid slot under (row, column) holds
 * the record id, and the record is copied from cell+4 (cell+8 while D_8014933C is zero) to the scaled slot after the
 * 4bpp cell image.
 */
MATCH void Area_WriteCellRecord(u8* cell) {
    u32  map;
    u32  scratch[2];
    u32* src;
    u32* dst;
    s32  grid_off;
    s32  size;
    s32  image_off;
    s32  index;
    u16  record;

    map       = MAP_BUNDLE_BASE;
    src       = (u32*)(cell + 4);
    size      = *(u8*)map * g_AreaMapBundle.height_01;
    grid_off  = g_AreaMapBundle.grid_off4_02 * 4;
    image_off = ((size + 1) >> 1) * 4;
    dst       = (u32*)(grid_off + (map + image_off));
    index     = cell[0] * *(u8*)map * 2 + (grid_off + cell[1] * 2);
    record    = *(u16*)(index + map);
    dst += record;
    if (D_8014933C == 0) {
        src = (u32*)(cell + 8);
    }
    *dst = *src;
}
