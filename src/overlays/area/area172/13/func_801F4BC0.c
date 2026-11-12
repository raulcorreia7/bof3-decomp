#include "area172_13.h"

MATCH void func_801F4BC0(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            func_801BE1B0(1);
            *state = 1;
            break;
        case 1:
            if (D_80146867 == 0x14) {
                SYS_SetFlag(state + 0x63C, 0x4E);
                Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD(10), TO_COORD(5), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
        case 5:
            func_801BE1B0(0);
            *state = 6;
            break;
        case 6:
            if (D_80146867 == 0x14) {
                SYS_SetFlag(state + 0x63C, 0x4E);
                Game_RequestAreaChange(AREA_ID_EDEN_TEEPO_FIGHT, TO_COORD(38), TO_COORD(54), AREA_ENTRY_MAP_LOADING | FACING_UP_RIGHT);
                g_SceneEventMode = 0;
                *state           = 0;
            }
            break;
    }
}
