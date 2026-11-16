#include "scena02_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8070(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = 1;
            Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_AREA, TO_COORD(44), TO_COORD(67), AREA_ENTRY_MAP_LOADING);
            break;
        case 1:
            if (g_ScriptVars[0] == 8) {
                g_GameFlags |= 0x6;
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                SYS_SetFlag(g_SceneFlags, 4);
            }
            break;
        case 5:
            Scene_SetupParty(1);
            g_SceneState.step_05 = 6;
            break;
        case 6:
            if (g_ScriptVars[0] == 0x22) {
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                SYS_SetFlag(g_SceneFlags, 5);
                SYS_SetFlag(g_SceneFlags, 6);
                g_GameFlags ^= 0x80;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_COURTYARD, TO_COORD(49), TO_COORD(75), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
                g_GameArea.request_kind = 1;
            }
            break;
        case 7:
            Scene_SetupParty(2);
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] == 0x22) {
                Game_ClearScriptActive();
                D_80146865            = 0;
                D_80146866            = 0;
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
                SYS_SetFlag(g_SceneFlags, 5);
                SYS_SetFlag(g_SceneFlags, 6);
                g_GameFlags ^= 0x80;
                Game_RequestAreaChange(AREA_ID_MCNEIL_MANOR_COURTYARD, TO_COORD(49), TO_COORD(75), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
                g_GameArea.request_kind = 1;
            }
            break;
    }
}
