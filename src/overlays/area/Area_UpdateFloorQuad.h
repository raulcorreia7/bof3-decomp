/* Area_Update of area160 and area162 to area165 (func_801F30D4). */
#include "overlays/area/Area_FloorQuad.h"

MATCH void Area_Update(void) {
    AREA_DRAW_FLOOR_QUAD((g_Task->direction_08 << 21) | 0x150010F);
}
