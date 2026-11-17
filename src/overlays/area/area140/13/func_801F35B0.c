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
    /* FAKE: keeps the map row coordinate in a1 while the loop product takes v0; the plain ternary is 3 rows off. */
    FAKE_REG(s32, y, "a1");

    i = 0;
    do {
        column = COORD_INT(g_Task->pos.x) + g_Task->direction;
        if (g_Task->direction == 0) {
            column += i;
        }
        y      = COORD_INT(g_Task->pos.y);
        offset = i * g_Task->direction;
        row    = y + (g_Task->direction != 0 ? offset : offset + 1);
        map    = (AreaMapBundle*)MAP_BUNDLE_BASE;
        entry  = (u8*)(map->grid_offset * 4 + (((map->width * map->height + 1) / 2) * 4 + (u32)map) + *(u16*)(column * 2 + (row * map->width * 2 + map->grid_offset * 4) + (u32)map) * 4);
        id     = Area_GetCellId(column, row);
        if (g_Task->direction != 0) {
            prim = g_AreaCellPrims[id][1].pad1;
            if (prim == 0) {
                prim                        = Area_AllocCellPrimRow();
                g_AreaCellPrims[id][1].pad1 = prim;
                row_id                      = prim & HALF_MASK;
                Area_ApplyTileToQuad(*(u32*)(entry + 4), &g_AreaCellPrims[row_id][0], 2);
            }
        } else {
            prim = g_AreaCellPrims[id][1].pad2;
            if (prim == 0) {
                prim                        = Area_AllocCellPrimRow();
                g_AreaCellPrims[id][1].pad2 = prim;
                row_id                      = prim & HALF_MASK;
                Area_ApplyTileToQuad(*(u32*)(entry + 4), &g_AreaCellPrims[row_id][0], 2);
            }
        }
        i++;
    } while (i < 2);
    g_AreaCameraRefreshCount = 2;
    g_Task->header.step++;
    func_801F3950(g_Task->direction, COORD_INT(g_Task->pos.z));
}
#else
INCLUDE_ASM(func_801F35B0);
#endif
