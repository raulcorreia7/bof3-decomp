#include "engine/slus/slus.h"

/* stores value in the height-byte table of the map bundle at the scaled (s16) index.
 */
MATCH void Area_StoreHeight(s32 x, s32 y, u8 value) {
    u8* base;

    base = (u8*)MAP_BUNDLE_BASE;
    base[g_AreaMapBundle.height_off4_2A * 4 + (s16)x + (s16)y * ((AreaMapBundle*)base)->width_00] = value;
}
