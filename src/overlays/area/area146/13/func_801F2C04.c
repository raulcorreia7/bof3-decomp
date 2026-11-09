#include "area146_13.h"
#include "area/map.h"

MATCH s32 func_801F2C04(void) {
    Game_RequestAreaChange(AREA_ID_RELAY_POINT_A_PORTAL, TO_COORD(12) + COORD_HALF, TO_COORD(88), AREA_ENTRY_MAP_LOADING | FACING_UP);
}
