#include "area158_13.h"

#include "overlays/area/shared/Area_FloorQuad.h"

/* func_801F30D4 */
MATCH void Area_Update(void) {
    AREA_DRAW_FLOOR_QUAD((SELF(Actor)->direction * 0x21 << 16) | 0x150010F);
}
