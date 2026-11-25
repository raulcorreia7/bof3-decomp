#include "area173_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3060(s32 index, s32 flag) {
    u8   first_codes[2][3];
    u8   codes[2][3];
    u32* entry;
    s32  width;
    s32  row;
    s32  id;
    s32  i;

    width = ((AreaMapBundle*)MAP_BUNDLE_BASE)->width;
    row   = index + 0x47;
    memcpy(first_codes, D_801F2C04, sizeof(first_codes));
    memcpy(codes, D_801F2C04 + 8, sizeof(codes));
    entry = (u32*)((u8*)MAP_BUNDLE_BASE + ((width * D_80104001 + 1) >> 1) * 4 + D_80104002 * 4 + *(u16*)((u8*)MAP_BUNDLE_BASE + D_80104002 * 4 + row * width * 2 + 0x1A) * 4);
    entry[1] &= ~0xFFu;
    entry[1] |= first_codes[flag][index % 3];
    id = Area_CellGetId(13, row);
    if (id != 0) {
        Area_ApplyTileToQuad(entry[1], &g_AreaCellPrims[g_AreaCellPrims[id][1].pad1 & AREA_CELL_PRIM_MASK][0], 2);
    }

    for (i = 0; i < 8; i++) {
        width = ((AreaMapBundle*)MAP_BUNDLE_BASE)->width;
        entry = (u32*)((u8*)MAP_BUNDLE_BASE + ((width * D_80104001 + 1) >> 1) * 4 + D_80104002 * 4 + *(u16*)((u8*)MAP_BUNDLE_BASE + D_80104002 * 4 + row * width * 2 + i * 2 + 0x1C) * 4);
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
