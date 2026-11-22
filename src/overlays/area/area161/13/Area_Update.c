#include "area161_13.h"

#include "overlays/area/shared/Area_FloorQuad.h"

/* func_801F30D4 */
MATCH void Area_Update(void) {
    AREA_DRAW_FLOOR_QUAD((TASK(Actor)->direction << 21) | 0x150010F | (TASK(Actor)->direction == 0 ? 0x10000 : 0));
}
