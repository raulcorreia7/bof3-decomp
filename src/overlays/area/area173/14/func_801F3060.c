#include "area173_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3060(s32 index, s32 flag) {
    AreaMapBundle* map;
    u8*            base;
    u8             first_codes[2][3];
    u8             codes[6];
    u32            size;
    u32            image_offset;
    u32            grid_offset;
    u32            entry_base;
    u32            row_offset;
    u32*           entry;
    s32            row;
    s32            id;
    s32            i;

    map        = (AreaMapBundle*)MAP_BUNDLE_BASE;
    size       = map->width * D_80104001;
    row        = index + 0x47;
    row_offset = row * map->width * 2;
    memcpy(first_codes, D_801F2C04, sizeof(first_codes));
    memcpy(codes, D_801F2C04 + 8, sizeof(codes));
    image_offset = ((size + 1) / 2) * 4;
    grid_offset  = D_80104002 * 4;
    entry_base   = grid_offset + (image_offset + (u32)map);
    row_offset   = grid_offset + row_offset;
    entry        = (u32*)(entry_base + *(u16*)(row_offset + 0x1A + (u32)map) * 4);
    entry[1] &= ~0xFFu;
    entry[1] |= first_codes[flag][index % 3];
    id = Area_GetCellId(13, row);
    if (id != 0) {
        Area_ApplyTileToQuad(entry[1], &g_AreaCellPrims[g_AreaCellPrims[id][1].pad1 & AREA_CELL_PRIM_MASK][0], 2);
    }

    for (i = 0; i < 8; i++) {
        base         = (u8*)MAP_BUNDLE_BASE;
        size         = ((AreaMapBundle*)base)->width * D_80104001;
        grid_offset  = D_80104002 * 4;
        image_offset = ((size + 1) / 2) * 4;
        entry_base   = grid_offset + (image_offset + (u32)base);
        row_offset   = grid_offset + row * ((AreaMapBundle*)base)->width * 2 + i * 2;
        entry        = (u32*)(entry_base + *(u16*)(row_offset + 0x1C + (u32)base) * 4);
        entry[0] &= ~0xFFu;
        entry[0] |= codes[flag * 3 + index % 3] | (i + 3);
        id = Area_GetCellId(i + 14, row);
        if (id != 0) {
            Area_ApplyTileToQuad(entry[0], &g_AreaCellPrims[id][0], 2);
        }
    }
}
#else
INCLUDE_ASM(func_801F3060);
#endif
