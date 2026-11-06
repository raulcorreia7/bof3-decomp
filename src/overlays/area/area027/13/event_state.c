#include "area027_13.h"
#include "area/map.h"

MATCH void func_801F394C(void) {
    switch (g_SceneEventStep) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_SetScriptActive();
                SYS_SetFlag(g_SceneEventFlags, 0);
                g_SceneEventStep = 1;
            }
            break;
        case 1:
            func_801BE1B0(2);
            g_SceneEventStep = 2;
            break;
        case 2:
            if (g_ScriptVars[3] == 0x10) {
                D_801448EE       = 16;
                g_SceneEventStep = 3;
            }
            break;
        case 3: {
            u16* timer = &D_801448EE;
            u8*  flag;

            if (TIMER_EXPIRED(*timer)) {
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR, 0x260000u, 0x380000u, 144);
                g_SceneEventStep = 4;
                flag             = &g_ScriptVars[3];
                (*flag)++;
            }
        } break;
        case 4: {
            u8* flag = &g_ScriptVars[3];

            if (*flag == 0x31) {
                *flag = 0;
                Game_ClearScriptActive();
                SYS_ClearFlag(g_SceneEventFlags, 0);
                g_SceneEventMode = 0;
                g_SceneEventStep = 0;
            }
        } break;
    }
}
