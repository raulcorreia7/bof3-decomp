#include "area141_13.h"

MATCH void func_801F2D2C(void) {
    u32* entry;
    s32  row;
    s32  col;
    s32  id;
    u32  value;

    SELF(Actor)->timer = 0;
    for (row = D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].y0; row <= D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].y1; row++) {
        for (col = D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].x0; col <= D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].x1; col++) {
            entry  = &AREA_MAP_TILES[AREA_MAP_GRID_ROW(row)[col]];
            value  = *entry;
            *entry = value & CELL_UPLOAD_MASK;
            id     = Area_CellGetId(col, row);
            if (id != 0) {
                Area_ApplyTileToQuad(*entry, &g_AreaCellPrims[id][0], 2);
            }
        }
    }
    SELF(Actor)->header.step++;
}
