#include "area104_14.h"

/* The sine wave that ripples through the map's cell heights around the target cell. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F2C14(void) {
    u8* map_width;
    s32 cell_x;
    s32 cell_y;
    s32 offset_x;
    s32 offset_y;
    s32 delta_0;
    s32 delta_1;
    s32 angle_0;
    s32 angle_1;

    if (g_AreaSceneMode == 0) {
        return;
    }

    map_width = MEM_PTR(u8, MAP_BUNDLE_BASE);
    angle_1   = 0x180;
    angle_0   = 0;
    cell_x    = g_AreaTargetCellX - 20;
    cell_y    = g_AreaTargetCellY - 20;
    for (offset_y = 0; offset_y < 35; offset_y++) {
        delta_0 = (rsin(((g_FrameCount << 7) + angle_0) & 0xFFF) >> 10) - (rsin((((g_FrameCount - 1) << 7) + angle_0) & 0xFFF) >> 10);
        delta_1 = (rsin(((g_FrameCount << 7) + angle_1) & 0xFFF) >> 10) - (rsin((((g_FrameCount - 1) << 7) + angle_1) & 0xFFF) >> 10);
        for (offset_x = 0; offset_x < 35; offset_x++) {
            if (cell_y + offset_y < 0 || cell_y + offset_y >= g_AreaMapBundle.height || cell_x + offset_x < 0 || cell_x + offset_x >= *map_width) {
                continue;
            }
            /* The cell's four corner heights. */
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_0;
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + 1)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_0;
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + 2)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_1;
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + 3)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_1;
        }
        angle_1 += 0x180;
        angle_0 += 0x180;
    }

    COORD_INT(g_Game.members[0].pos.z) = Area_HeightSample(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed);
    g_AreaCameraRefreshCount           = 2;
}
#else
INCLUDE_ASM(func_801F2C14);
#endif
