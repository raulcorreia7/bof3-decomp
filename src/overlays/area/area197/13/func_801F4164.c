#include "area197_13.h"
#include "area/map.h"

MATCH void func_801F4164(void) {
    s8* state;

    state = (s8*)&g_SceneEventStep;
    switch (*state) {
        case 0:
            func_801BE1B0(0);
            *state = 1;
            break;
        case 1:
            if (D_80146867 == 0x24) {
                SYS_SetFlag(state + 0x63C, 85);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_HE_SHELLS, TO_COORD(6), TO_COORD(63), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                *state = 0x1E;
            }
            break;
    }
}
