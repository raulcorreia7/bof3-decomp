#include "area143_13.h"
#include "area/map.h"

MATCH void func_801F3C10(void) {
    Game_RequestAreaChange(AREA_ID_RELAY_POINT_A_PORTAL, TO_COORD(12) + COORD_HALF, TO_COORD(88),
                           AREA_ENTRY_MAP_LOADING | FACING_UP);
}
