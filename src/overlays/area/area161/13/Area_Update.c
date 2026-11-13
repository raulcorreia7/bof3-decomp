#include "area161_13.h"

#include "overlays/area/Area_FloorQuad.h"

/* func_801F30D4 */
MATCH void Area_Update(void) {
    AREA_DRAW_FLOOR_QUAD((g_Task->direction_08 << 21) | 0x150010F | (g_Task->direction_08 == FACING_UP_LEFT ? 0x10000 : 0));
}
