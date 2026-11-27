#include "engine/slus/slus.h"

/* resolves the bundle cell at (column, row) and uploads its word list plus the pad2 and pad1 linked rows
 * to the g_AreaCellPrims row context for display buffer slot; presence bits of the uploaded words fold into the
 * returned mask and an empty pad1 link is released.
 */
MATCH s32 Area_CellUpload(s32 column, s32 row, POLY_FT4* context, s32 slot) {
    u8* entry;
    s32 value;
    s32 result;
    s32 cell;
    s32 size;
    u16 id;

    cell = AREA_MAP_GRID_ROW(row)[column];
    if (cell == 0) {
        return 0;
    }
    entry  = (u8*)&AREA_MAP_TILES[cell];
    value  = *(u32*)entry;
    result = ((value & 0x40000000) >> 15) | (value & 0x4000);
    Area_ApplyTileToQuad(value, &context[slot], 1);
    entry += 4;
    id = context[1].pad2;
    if (id != 0) {
        value = *(u32*)entry;
        Area_ApplyTileToQuad(value, &g_AreaCellPrims[id][slot], 1);
        result |= (*(s32*)entry & 0x40000000) >> 18;
        entry += 4;
    }
    size = context[1].pad1;
    if (size != 0) {
        value = *(u32*)entry;
        if (value != 0) {
            Area_ApplyTileToQuad(value, &g_AreaCellPrims[size][slot], 1);
            result |= (*(s32*)entry & 0x40000000) >> 17;
        } else {
            Area_CellFreePrimSlot(size);
            context[1].pad1 = 0;
        }
    }
    return result;
}
