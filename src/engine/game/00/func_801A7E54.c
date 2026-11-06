#include "game_00.h"
#include "area/map.h"

MATCH void func_801A7E54(void) {
    u8* flag;

    switch (g_SceneEventStep) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_SetScriptActive();
                g_SceneEventStep = 1;
            }
            break;
        case 1:
            func_801BE1B0(s_SceneStateStepArgs[g_SceneEventSelection]);
            g_SceneEventStep = 2;
            break;
        case 2:
            if (g_ScriptVars[3] == 0x20) {
                D_801448EE       = 0x10;
                g_SceneEventStep = 3;
            }
            break;
        case 3:
            if (--(*(u16*)&D_801448EE) == 0) {
                switch (g_SceneEventSelection) {
                    case 0:
                    case 4:
                        Game_RequestAreaChange(AREA_ID_DAUNA_MINE_ZOMBIE_DRAGON, 0x110000, 0x590000, 0x85);
                        break;
                    case 1:
                    case 2:
                        Game_RequestAreaChange(0x22, 0x340000, 0x430000, 0x81);
                        break;
                    case 3:
                    case 5:
                        Game_RequestAreaChange(AREA_ID_DAUNA_MINE_INTRO, 0x3E0000, 0x50000, 0x81);
                        break;
                }
                g_SceneEventStep = 4;
            }
            break;
        case 4:
            flag = &g_ScriptVars[3];
            if (*flag == 0x31) {
                *flag = 0;
                Game_ClearScriptActive();
                SYS_ClearFlag(g_SceneEventFlags, 0x1E);
                SYS_ClearFlag(g_SceneEventFlags, 0x1F);
                g_SceneEventMode      = 0;
                g_SceneEventStep      = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}
