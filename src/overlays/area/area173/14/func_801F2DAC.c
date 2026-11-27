#include "area173_14.h"

MATCH void func_801F2DAC(void) {
    u32* entry;
    s32  id;
    s32  i;
    u32  value;

    SYS_SetFlag(g_SceneEventFlags, 0x80);
    SELF(Actor)->timer = 0;
    func_801F3324(0xC0, 0);
    for (i = 0; i < 2; i++) {
        entry  = &AREA_MAP_TILES[AREA_MAP_GRID_ROW(0x61)[i + 0x11]];
        value  = *entry;
        *entry = (value & ~0xFFu) | (i + 0xE6);
        id     = Area_CellGetId(i + 0x11, 0x61);
        if (id != 0) {
            Area_ApplyTileToQuad(*entry, &g_AreaCellPrims[id][0], 2);
        }
    }
    SELF(Actor)->header.step++;
}
