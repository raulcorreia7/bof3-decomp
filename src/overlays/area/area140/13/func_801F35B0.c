#include "area140_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F35B0(void) {
    AreaMapBundle* map;
    s32            column;
    s32            row;
    s32            id;
    s32            i;
    s32            offset;
    s32            prim;
    s32            row_id;
    u8*            entry;

    i = 0;
    do {
        column = COORD_INT(g_Task->pos.x) + g_Task->direction_08;
        if (g_Task->direction_08 == 0) {
            column += i;
        }
        offset = i * g_Task->direction_08;
        row    = COORD_INT(g_Task->pos.y) + (g_Task->direction_08 != 0 ? offset : offset + 1);
        map    = (AreaMapBundle*)MAP_BUNDLE_BASE;
        entry  = (u8*)(map->grid_off4_02 * 4 + (((map->width * map->height + 1) / 2) * 4 + (u32)map) + *(u16*)(column * 2 + (row * map->width * 2 + map->grid_off4_02 * 4) + (u32)map) * 4);
        id     = Area_GetCellId(column, row);
        if (g_Task->direction_08 != 0) {
            prim = g_AreaCellPrims[id][1].pad1;
            if (prim == 0) {
                prim                        = Area_AllocCellPrimRow();
                g_AreaCellPrims[id][1].pad1 = prim;
                row_id                      = prim & HALF_MASK;
                func_80155560(*(u32*)(entry + 4), &g_AreaCellPrims[row_id][0], 2);
            }
        } else {
            prim = g_AreaCellPrims[id][1].pad2;
            if (prim == 0) {
                prim                        = Area_AllocCellPrimRow();
                g_AreaCellPrims[id][1].pad2 = prim;
                row_id                      = prim & HALF_MASK;
                func_80155560(*(u32*)(entry + 4), &g_AreaCellPrims[row_id][0], 2);
            }
        }
        i++;
    } while (i < 2);
    g_AreaCameraRefreshCount = 2;
    g_Task->header.step++;
    func_801F3950(g_Task->direction_08, COORD_INT(g_Task->pos.z));
}
#else
INCLUDE_ASM(func_801F35B0);
#endif
