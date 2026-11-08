#include "area158_13.h"

#include "overlays/area/Area_FloorQuad.h"

/* func_801F30D4 */
MATCH void Area_Update(void) {
    AREA_DRAW_FLOOR_QUAD((g_Task->direction_08 * 0x21 << 16) | 0x150010F);
}
