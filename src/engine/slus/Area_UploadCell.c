#include "engine/slus/slus.h"

/* resolves the bundle cell at (column, row) and uploads its word list plus the pad2 and pad1 linked rows
 * to the g_AreaCellPrims row context for display buffer slot; presence bits of the uploaded words fold into the
 * returned mask and an empty pad1 link is released.
 */
MATCH s32 Area_UploadCell(s32 column, s32 row, POLY_FT4* context, s32 slot) {
    AreaMapBundle* map;
    u8*            entry;
    s32            value;
    s32            result;
    s32            cell;
    s32            size;
    u16            id;

    map  = (AreaMapBundle*)MAP_BUNDLE_BASE;
    cell = *(u16*)(column * 2 + (row * map->width_00 * 2 + map->grid_off4_02 * 4) + (u32)map);
    if (cell == 0) {
        return 0;
    }
    entry  = (u8*)(map->grid_off4_02 * 4 + (((map->width_00 * map->height_01 + 1) / 2) * 4 + (u32)map) + cell * 4);
    value  = *(u32*)entry;
    result = ((value & 0x40000000) >> 15) | (value & 0x4000);
    func_80155560(value, &context[slot], 1);
    entry += 4;
    id = context[1].pad2;
    if (id != 0) {
        value = *(u32*)entry;
        func_80155560(value, &g_AreaCellPrims[id][slot], 1);
        result |= (*(s32*)entry & 0x40000000) >> 18;
        entry += 4;
    }
    size = context[1].pad1;
    if (size != 0) {
        value = *(u32*)entry;
        if (value != 0) {
            func_80155560(value, &g_AreaCellPrims[size][slot], 1);
            result |= (*(s32*)entry & 0x40000000) >> 17;
        } else {
            Area_FreeCellPrimRow(size);
            context[1].pad1 = 0;
        }
    }
    return result;
}
