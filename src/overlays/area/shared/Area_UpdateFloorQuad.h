/* Area_Update of area160 and area162 to area165 (func_801F30D4): the floor quad with sprite word
 * 0x150010F, turned by direction << 21. */
#include "overlays/area/shared/Area_FloorQuad.h"

MATCH void Area_Update(void) {
    AREA_DRAW_FLOOR_QUAD((SELF(Actor)->direction << 21) | 0x150010F);
}
