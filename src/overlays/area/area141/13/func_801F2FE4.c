#include "area141_13.h"

MATCH void func_801F2FE4(void) {
    u32* entry;
    s32  row;
    s32  col;
    s32  id;
    u32  fade;
    u32  value;

    SELF(Actor)->timer += 1;
    fade = SELF(Actor)->timer <= CELL_FADE_MAX ? SELF(Actor)->timer : CELL_FADE_MAX;
    for (row = D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].y0; row <= D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].y1; row++) {
        for (col = D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].x0; col <= D_801F47D4[COORD_INT(SELF(Actor)->pos.x)].x1; col++) {
            entry  = &AREA_MAP_TILES[AREA_MAP_GRID_ROW(row)[col]];
            value  = *entry;
            *entry = (value & CELL_UPLOAD_MASK) | (fade << CELL_FADE_SHIFT);
            id     = Area_CellGetId(col, row);
            if (id != 0) {
                Area_ApplyTileToQuad(*entry, &g_AreaCellPrims[id][g_GfxBufferIndex], 1);
            }
        }
    }
    if (SELF(Actor)->timer >= CELL_FADE_MAX + 2) {
        Actor_Clear();
    }
}
