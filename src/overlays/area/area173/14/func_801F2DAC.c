#include "area173_14.h"

MATCH void func_801F2DAC(void) {
    AreaMapBundle* map;
    u8*            base;
    u32            grid_offset;
    /* FAKE: retail keeps the half-grid span in a2; plain C uses v0. */
    FAKE_REG(u32, tile_offset, "a2");
    u32  entry_base;
    u32* entry;
    s32  id;
    s32  i;
    u32  row_offset;
    u32  value;

    SYS_SetFlag(g_SceneEventFlags, 0x80);
    SELF(Actor)->timer = 0;
    func_801F3324(0xC0, 0);
    for (i = 0; i < 2; i++) {
        map         = (AreaMapBundle*)MAP_BUNDLE_BASE;
        base        = (u8*)map;
        grid_offset = MEM(u16, MAP_BUNDLE_BASE + 2) * 4;
        tile_offset = ((map->width * MEM(u8, MAP_BUNDLE_BASE + 1) + 1) / 2) * 4;
        entry_base  = grid_offset + (tile_offset + (u32)base);
        row_offset  = grid_offset + 0x61 * map->width * 2;
        row_offset += i * 2;
        entry  = (u32*)(entry_base + MEM(u16, row_offset + 0x22 + (u32)base) * 4);
        value  = *entry;
        *entry = (value & ~0xFFu) | (i + 0xE6);
        id     = Area_CellGetId(i + 0x11, 0x61);
        if (id != 0) {
            Area_ApplyTileToQuad(*entry, &g_AreaCellPrims[id][0], 2);
        }
    }
    SELF(Actor)->header.step++;
}
