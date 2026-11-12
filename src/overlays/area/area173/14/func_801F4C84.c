#include "area173_14.h"

MATCH void func_801F4C84(void) {
    switch (g_SceneEventStep) {
        case 0:
            func_801BE1B0(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (D_80146867 == 0x18) {
                if (D_80143F03 == 2) {
                    Game_RequestAreaChange(AREA_ID_LOOP_ELEVATOR, TO_COORD(4) + COORD_HALF, TO_COORD(10), AREA_ENTRY_MAP_LOADING);
                } else {
                    Game_RequestAreaChange(AREA_ID_LOOP_ELEVATOR, TO_COORD(4) + COORD_HALF, TO_COORD(100), AREA_ENTRY_MAP_LOADING);
                }
                SYS_SetFlag(g_SceneEventFlags, 0x58);
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 10:
            if (D_80146867 == 0x20) {
                g_AreaSceneMode  = 1;
                D_801448EE       = 0x1E;
                g_SceneEventStep = 0xB;
            }
            break;
        case 11:
            if (--LOHU(D_801448EE) == 0) {
                D_80146867       = 0x24;
                g_SceneEventStep = 0xC;
            }
            break;
        case 12:
            if (D_80146867 == 0) {
                SYS_ClearFlag(g_SceneEventFlags, 0x58);
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
    }
}
