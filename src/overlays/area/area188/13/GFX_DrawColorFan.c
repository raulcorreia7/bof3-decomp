#include "area188_13.h"

#include "overlays/area/shared/Area_DrawRadialLight.h"

/* Draws a fan of colored triangles. */
/* func_801F38E0 */
MATCH void GFX_DrawColorFan(void* position, s32 radius, s32 colors) {
    Area_DrawRadialLight(position, radius, colors, 5);
}
