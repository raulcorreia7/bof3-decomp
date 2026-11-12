#include "area167_13.h"

MATCH void func_801F4494(void) {
    u8*  flag;
    u8*  mode;
    u16* countdown;

    switch (g_SceneEventStep) {
        case 0:
            func_801BE1B0(0);
            g_SceneEventStep = 1;
            break;
        case 1:
            if (D_80146867 == 0x18) {
                mode             = &g_SceneEventMode;
                *mode            = 0;
                g_SceneEventStep = 0;
                /* FAKE: retail reaches g_SceneEventFlags as the mode byte plus 0x63D. */
                SYS_SetFlag(mode + 0x63D, 0x46);
                Game_RequestAreaChange(AREA_ID_CAER_XHAN_LIFT_RIDE, TO_COORD(8), TO_COORD(12), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 5:
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
            g_SceneEventStep = 6;
            D_801448EE       = 0xA;
            break;
        case 6:
            if (--LOHU(D_801448EE) == 0) {
                Game_ClearScriptActive();
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 10:
            if (D_80146867 == 0x64) {
                func_801BE1B0(5);
                g_SceneEventStep = 0xB;
            }
            break;
        case 11:
            if (D_80146867 == 0x74) {
                if (D_80143F03 == 2) {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(19), TO_COORD(154), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                } else {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(10), TO_COORD(30), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                }
                SYS_ToggleFlag(g_SceneEventFlags, 0x4B);
                SYS_SetFlag(g_SceneEventFlags, 0x4C);
                g_SceneEventStep = 0xC;
            }
            break;
        case 12:
            if (D_80146867 == 0) {
                if (D_80143F03 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
                }
                D_80146866       = 0;
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
        case 20:
            if (D_80146867 == 0x44) {
                func_801BE1B0(2);
                g_SceneEventStep = 0x18;
            }
            break;
        case 21:
            func_801BE1B0(8);
            g_SceneEventStep = 0x18;
            break;
        case 24:
            flag = &D_80146867;
            if (*flag == 0x54) {
                if (D_80146866 == 0) {
                    *flag = 0;
                    Game_ClearScriptActive();
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(26) + COORD_HALF, TO_COORD(86), FACING_DOWN);
                    SYS_ClearFlag(g_SceneEventFlags, 0x48);
                    SYS_ClearFlag(g_SceneEventFlags, 0x49);
                } else if (D_80146866 == 1) {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(32), TO_COORD(15), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                    SYS_SetFlag(g_SceneEventFlags, 0x48);
                    SYS_ClearFlag(g_SceneEventFlags, 0x49);
                } else if (D_80146866 == 2) {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(41), TO_COORD(139), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
                    SYS_ClearFlag(g_SceneEventFlags, 0x48);
                    SYS_SetFlag(g_SceneEventFlags, 0x49);
                }
                if (D_80143F03 == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
                }
                SYS_SetFlag(g_SceneEventFlags, 0x4A);
                g_SceneEventStep = 0xC;
            }
            break;
        case 30:
            g_SceneEventStep = 0x1F;
            break;
        case 31:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaSceneMode  = 0x20;
                D_801448EE       = 0x1E;
                g_SceneEventStep = 0x20;
            }
            break;
        case 32:
            countdown = &LOHU(D_801448EE);
            if (--*countdown == 0) {
                Game_ClearScriptActive();
                /* FAKE: retail reaches g_SceneEventFlags as the countdown halfword plus 0x31D. */
                SYS_SetFlag(countdown + 0x31D, 0x90);
                Game_RequestAreaChange(AREA_ID_MYRIA_STATION_MAIN_HALL, TO_COORD(21), TO_COORD(4), FACING_LEFT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
            break;
    }
}
