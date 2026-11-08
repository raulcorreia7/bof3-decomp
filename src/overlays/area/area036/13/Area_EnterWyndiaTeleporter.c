#include "area036_13.h"
#include "area/map.h"

MATCH s32 Area_EnterWyndiaTeleporter(void) {
    Game_RequestAreaChange(AREA_ID_WYNDIA_BASEMENT_TELEPORTER, TO_COORD(70), TO_COORD(52),
                           AREA_ENTRY_MAP_LOADING | FACING_UP);
}
