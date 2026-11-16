#include "area173_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2DAC(void) {
    AreaMapBundle* map;
    u8*            base;
    u32            entry_base;
    u32*           entry;
    s32            id;
    s32            i;
    u32            row_offset;
    u32            value;

    SYS_SetFlag(g_SceneEventFlags, 0x80);
    g_Task->timer = 0;
    func_801F3324(0xC0, 0);
    for (i = 0; i < 2; i++) {
        map        = (AreaMapBundle*)MAP_BUNDLE_BASE;
        base       = (u8*)map;
        entry_base = MEM(u16, MAP_BUNDLE_BASE + 2) * 4 + (((map->width * MEM(u8, MAP_BUNDLE_BASE + 1) + 1) / 2) * 4 + (u32)base);
        row_offset = MEM(u16, MAP_BUNDLE_BASE + 2) * 4 + 0x61 * map->width * 2;
        entry      = (u32*)(entry_base + MEM(u16, row_offset + (i + 0x11) * 2 + (u32)base) * 4);
        value      = *entry;
        *entry     = (value & ~0xFFu) | (i + 0xE6);
        id         = Area_GetCellId(i + 0x11, 0x61);
        if (id != 0) {
            Area_ApplyTileToQuad(*entry, &g_AreaCellPrims[id][0], 2);
        }
    }
    g_Task->header.step++;
}
#else
INCLUDE_ASM(func_801F2DAC);
#endif
