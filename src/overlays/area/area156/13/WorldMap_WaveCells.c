#include "area156_13.h"

/* func_801F2C04 */
MATCH void WorldMap_WaveCells(void) {
    u8* map_width;
    u8* map_height;
    s32 offset_x;
    s32 offset_y;
    s32 cell_x;
    s32 cell_y;
    s32 delta_0;
    s32 delta_1;
    s32 angle_0;
    s32 angle_1;

    offset_x            = 0;
    map_height          = MEM_PTR(u8, MAP_BUNDLE_BASE + 1);
    map_width           = MEM_PTR(u8, MAP_BUNDLE_BASE);
    g_AreaCameraOffsetZ = 0x5DC;
    angle_1             = 0x180;
    angle_0             = 0;
    cell_x              = g_AreaCamera.scroll_x.part.integer - 20;
    cell_y              = g_AreaCamera.scroll_y.part.integer - 20;
    for (offset_x = 0; offset_x < 35; offset_x++) {
        delta_0 = (rsin(((g_FrameCount << 7) + angle_0) & 0xFFF) >> 10) - (rsin((((g_FrameCount - 1) << 7) + angle_0) & 0xFFF) >> 10);
        delta_1 = (rsin(((g_FrameCount << 7) + angle_1) & 0xFFF) >> 10) - (rsin((((g_FrameCount - 1) << 7) + angle_1) & 0xFFF) >> 10);
        for (offset_y = 0; offset_y < 35; offset_y++) {
            if (cell_y + offset_y < 0 || cell_y + offset_y >= *map_height || cell_x + offset_x < 0 || cell_x + offset_x >= *map_width) {
                continue;
            }
            /* The cell's four corner heights. */
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_0;
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + 2)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_0;
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + 1)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_1;
            MEM_PTR(u8, MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE + 3)[((cell_y + offset_y) * *map_width << 2) + ((cell_x + offset_x) << 2)] += delta_1;
        }
        angle_1 += 0x180;
        angle_0 += 0x180;
    }

    g_AreaFocus.z.part.integer = Area_HeightSample(g_PartyActors[0].pos.x.fixed, g_AreaFocus.y.fixed);
    g_PartyActors[0].vz        = 0;
    g_AreaCameraRefreshCount   = 2;
}
