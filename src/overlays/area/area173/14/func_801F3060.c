#include "area173_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3060(s32 index, s32 flag) {
    AreaMapBundle* map;
    u8             first_codes[2][3];
    u8             codes[2][3];
    u32*           entry;
    s32            row;
    s32            id;
    s32            i;

    row = index + 0x47;
    memcpy(first_codes, D_801F2C04, sizeof(first_codes));
    memcpy(codes, D_801F2C04 + 8, sizeof(codes));
    entry = (u32*)(D_80104002 * 4 + (((((AreaMapBundle*)MAP_BUNDLE_BASE)->width * D_80104001 + 1) / 2) * 4 + (u32)((AreaMapBundle*)MAP_BUNDLE_BASE)) +
                   *(u16*)(13 * 2 + (row * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width * 2 + D_80104002 * 4) + (u32)((AreaMapBundle*)MAP_BUNDLE_BASE)) * 4);
    entry[1] &= ~0xFFu;
    entry[1] |= first_codes[flag][index % 3];
    id = Area_CellGetId(13, row);
    if (id != 0) {
        Area_ApplyTileToQuad(entry[1], &g_AreaCellPrims[g_AreaCellPrims[id][1].pad1 & AREA_CELL_PRIM_MASK][0], 2);
    }

    map = (AreaMapBundle*)MAP_BUNDLE_BASE;
    for (i = 0; i < 8; i++) {
        entry = (u32*)(D_80104002 * 4 + (((map->width * D_80104001 + 1) / 2) * 4 + (u32)map) + *(u16*)((i + 14) * 2 + (row * map->width * 2 + D_80104002 * 4) + (u32)map) * 4);
        entry[0] &= ~0xFFu;
        entry[0] |= codes[flag][index % 3] | (i + 3);
        id = Area_CellGetId(i + 14, row);
        if (id != 0) {
            Area_ApplyTileToQuad(entry[0], &g_AreaCellPrims[id][0], 2);
        }
    }
}
#else
INCLUDE_ASM(func_801F3060);
#endif
