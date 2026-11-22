#include "area086_13.h"
#include "area/spad.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2DE8(void) {
    AreaMapBundle* map;
    s32            x;
    s32            y;
    u8             code;
    s16            height;
    s32            depth;

    code = COORD_INT(g_Task->pos.z) != -0x200 ? 0x21 : 0;
    for (x = D_801F364C[COORD_INT(g_Task->pos.x)].x0; x < D_801F364C[COORD_INT(g_Task->pos.x)].x_end; x++) {
        for (y = D_801F364C[COORD_INT(g_Task->pos.x)].y0; y < D_801F364C[COORD_INT(g_Task->pos.x)].y_end; y++) {
            (g_AreaCellCodes + y * ((AreaMapBundle*)MAP_BUNDLE_BASE)->width)[x] = code;
        }
    }
    for (x = D_801F364C[COORD_INT(g_Task->pos.x)].x0; x < D_801F364C[COORD_INT(g_Task->pos.x)].x_end; x++) {
        map = (AreaMapBundle*)MAP_BUNDLE_BASE;
        for (y = D_801F364C[COORD_INT(g_Task->pos.x)].y0; y < D_801F364C[COORD_INT(g_Task->pos.x)].y_end; y++) {
            height = Area_HeightSample(x << 16, y << 16);
            depth  = (-(COORD_INT(g_Task->pos.z) * 2) - height) / 32;
            *(u8*)(g_AreaMapBundle.height_offset * 4 + x + y * map->width + (u32)map) = depth;
        }
    }
}
#else
INCLUDE_ASM(func_801F2DE8);
#endif
