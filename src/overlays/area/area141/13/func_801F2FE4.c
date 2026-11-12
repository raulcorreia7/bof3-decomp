#include "area141_13.h"

MATCH void func_801F2FE4(void) {
    AreaMapBundle* map;
    u8*            base;
    u32            entry_base;
    u32*           entry;
    s32            row;
    s32            col;
    s32            id;
    u32            fade;
    u32            value;

    g_Task->timer += 1;
    fade = g_Task->timer < 17 ? g_Task->timer : 0x10;
    for (row = D_801F47D4[COORD_INT(g_Task->pos.x)].y0; row <= D_801F47D4[COORD_INT(g_Task->pos.x)].y1; row++) {
        map  = (AreaMapBundle*)MAP_BUNDLE_BASE;
        base = (u8*)map;
        for (col = D_801F47D4[COORD_INT(g_Task->pos.x)].x0; col <= D_801F47D4[COORD_INT(g_Task->pos.x)].x1; col++) {
            entry_base = MEM(u16, MAP_BUNDLE_BASE + 2) * 4 + (((map->width * MEM(u8, MAP_BUNDLE_BASE + 1) + 1) / 2) * 4 + (u32)base);
            entry      = (u32*)(entry_base + MEM(u16, col * 2 + (row * map->width * 2 + MEM(u16, MAP_BUNDLE_BASE + 2) * 4) + (u32)base) * 4);
            value      = *entry;
            *entry     = (value & CELL_UPLOAD_MASK) | (fade << 19);
            id         = Area_GetCellId(col, row);
            if (id != 0) {
                func_80155560(*entry, &g_AreaCellPrims[id][g_FrameBufferIndex], 1);
            }
        }
    }
    if (g_Task->timer >= 18) {
        Actor_Clear();
    }
}
