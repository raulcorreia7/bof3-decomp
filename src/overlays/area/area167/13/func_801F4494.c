#include "area167_13.h"

MATCH void func_801F4494(void) {
    u8*  flag;
    u8*  mode;
    u16* countdown;

    switch (g_SceneEventState.step) {
        case 0:
            Scene_SetupParty(0);
            g_SceneEventState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[3] == 0x18) {
                mode                   = &g_SceneEventState.mode;
                *mode                  = 0;
                g_SceneEventState.step = 0;
                /* FAKE: retail reaches g_SceneEventFlags as the mode byte plus 0x63D. */
                SYS_SetFlag(mode + 0x63D, 0x46);
                Game_RequestAreaChange(AREA_ID_CAER_XHAN_LIFT_RIDE, TO_COORD(8), TO_COORD(12), AREA_ENTRY_MAP_LOADING | FACING_UP);
            }
            break;
        case 5:
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
            g_SceneEventState.step = 6;
            D_801448EE             = 0xA;
            break;
        case 6:
            if (--LOHU(D_801448EE) == 0) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
        case 10:
            if (g_ScriptVars[3] == 0x64) {
                Scene_SetupParty(5);
                g_SceneEventState.step = 0xB;
            }
            break;
        case 11:
            if (g_ScriptVars[3] == 0x74) {
                if (g_GameCellType == 2) {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(19), TO_COORD(154), AREA_ENTRY_MAP_LOADING | FACING_LEFT);
                } else {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(10), TO_COORD(30), AREA_ENTRY_MAP_LOADING | FACING_DOWN_LEFT);
                }
                SYS_ToggleFlag(g_SceneEventFlags, 0x4B);
                SYS_SetFlag(g_SceneEventFlags, 0x4C);
                g_SceneEventState.step = 0xC;
            }
            break;
        case 12:
            if (g_ScriptVars[3] == 0) {
                if (g_GameCellType == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
                }
                g_ScriptVars[2]        = 0;
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
        case 20:
            if (g_ScriptVars[3] == 0x44) {
                Scene_SetupParty(2);
                g_SceneEventState.step = 0x18;
            }
            break;
        case 21:
            Scene_SetupParty(8);
            g_SceneEventState.step = 0x18;
            break;
        case 24:
            flag = &g_ScriptVars[3];
            if (*flag == 0x54) {
                if (g_ScriptVars[2] == 0) {
                    *flag = 0;
                    Game_ClearScriptActive();
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(26) + COORD_HALF, TO_COORD(86), FACING_DOWN);
                    SYS_ClearFlag(g_SceneEventFlags, 0x48);
                    SYS_ClearFlag(g_SceneEventFlags, 0x49);
                } else if (g_ScriptVars[2] == 1) {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(32), TO_COORD(15), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
                    SYS_SetFlag(g_SceneEventFlags, 0x48);
                    SYS_ClearFlag(g_SceneEventFlags, 0x49);
                } else if (g_ScriptVars[2] == 2) {
                    Game_RequestAreaChange(AREA_ID_MYRIA_STATION_WORKERS, TO_COORD(41), TO_COORD(139), AREA_ENTRY_MAP_LOADING | FACING_DOWN_RIGHT);
                    SYS_ClearFlag(g_SceneEventFlags, 0x48);
                    SYS_SetFlag(g_SceneEventFlags, 0x49);
                }
                if (g_GameCellType == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 5));
                }
                SYS_SetFlag(g_SceneEventFlags, 0x4A);
                g_SceneEventState.step = 0xC;
            }
            break;
        case 30:
            g_SceneEventState.step = 0x1F;
            break;
        case 31:
            if (!WINDOW_EFFECT_BUSY()) {
                g_AreaSceneMode        = 0x20;
                D_801448EE             = 0x1E;
                g_SceneEventState.step = 0x20;
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
                g_SceneEventState.mode = 0;
                g_SceneEventState.step = 0;
            }
            break;
    }
}
