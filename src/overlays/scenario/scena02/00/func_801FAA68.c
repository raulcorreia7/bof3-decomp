#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FAA68(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVars[0]      = 1;
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] == 2) {
                SYS_SetFlag(g_SceneFlags, 0x1A);
                Scene_SetupParty(2);
                g_SceneState.step_05 = 2;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 4) {
                g_ScriptVars[1] = 0;
                g_ScriptVars[3] = 0;
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
        case 5:
            g_SceneState.step_05 = 6;
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            SND_StopSequence(0, 0);
            g_ScriptVars[2] = 1;
            Game_RequestAreaChange(AREA_ID_FARM, TO_COORD(6), TO_COORD(84), AREA_ENTRY_MAP_LOADING | FACING_RIGHT);
            break;
        case 6:
            if (g_ScriptVars[0] == 0x11) {
                SYS_SetFlag(g_SceneFlags, 0x1C);
                SYS_SetFlag(g_SceneFlags, 0x38);
                SYS_SetFlag(g_SceneFlags, 0x1B);
                g_SceneState.step_05 = 7;
                g_ScriptVars[1]      = 0;
                g_ScriptVars[2]      = 0;
                g_ScriptVars[3]      = 0;
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                Game_ClearScriptActive();
            }
            break;
        case 7:
            if (D_80143F03 == 0) {
                SND_PlayBGM(16, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
                g_ScriptVars[0]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;
    }
}
