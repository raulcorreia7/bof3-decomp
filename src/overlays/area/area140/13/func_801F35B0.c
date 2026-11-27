#include "area140_13.h"

MATCH void func_801F35B0(void) {
    s32 column;
    s32 row;
    s32 id;
    s32 i;
    s32 offset;
    s32 row_adjustment;
    s32 prim;
    s32 row_id;
    s32 y;
    u8* entry;

    i = 0;
    do {
        column = COORD_INT(SELF(Actor)->pos.x) + SELF(Actor)->direction;
        if (SELF(Actor)->direction == 0) {
            column += i;
        }
        row_adjustment = 1;
        y              = COORD_INT(SELF(Actor)->pos.y);
        offset         = i * SELF(Actor)->direction;
        row            = y + (SELF(Actor)->direction != 0 ? offset : offset + row_adjustment);
        entry          = (u8*)&AREA_MAP_TILES[AREA_MAP_GRID_ROW(row)[column]];
        id             = Area_CellGetId(column, row);
        if (SELF(Actor)->direction != 0) {
            prim = g_AreaCellPrims[id][1].pad1;
            if (prim == 0) {
                prim                        = Area_CellAllocPrimSlot();
                g_AreaCellPrims[id][1].pad1 = prim;
                row_id                      = prim & HALF_MASK;
                Area_ApplyTileToQuad(*(u32*)(entry + 4), &g_AreaCellPrims[row_id][0], 2);
            }
        } else {
            prim = g_AreaCellPrims[id][1].pad2;
            if (prim == 0) {
                prim                        = Area_CellAllocPrimSlot();
                g_AreaCellPrims[id][1].pad2 = prim;
                row_id                      = prim & HALF_MASK;
                Area_ApplyTileToQuad(*(u32*)(entry + 4), &g_AreaCellPrims[row_id][0], 2);
            }
        }
        i++;
    } while (i < 2);
    g_AreaCameraRefreshCount = 2;
    SELF(Actor)->header.step++;
    func_801F3950(SELF(Actor)->direction, COORD_INT(SELF(Actor)->pos.z));
}
