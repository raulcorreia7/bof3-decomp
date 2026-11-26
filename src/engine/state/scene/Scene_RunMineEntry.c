#include "engine/game/00/game_00.h"
#include "area/map.h"

/* func_801A7E54 */
/* Sets up the party, then requests the Dauna Mine area the event selection picks. */
MATCH void Scene_RunMineEntry(void) {
    u8* flag;

    switch (g_SceneEventState.step) {
        case 0:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_SetScriptActive();
                g_SceneEventState.step = 1;
            }
            break;
        case 1:
            Scene_SetupParty(s_ScenarioStateStepArgs[g_SceneEventState.selection]);
            g_SceneEventState.step = 2;
            break;
        case 2:
            if (g_ScriptVars[3] == 0x20) {
                D_801448EE             = 0x10;
                g_SceneEventState.step = 3;
            }
            break;
        case 3:
            if (--(*(u16*)&D_801448EE) == 0) {
                switch (g_SceneEventState.selection) {
                    case 0:
                    case 4:
                        Game_RequestAreaChange(AREA_ID_DAUNA_MINE_ZOMBIE_DRAGON, TO_COORD(17), TO_COORD(89), AREA_ENTRY_MAP_LOADING | FACING_DOWN);
                        break;
                    case 1:
                    case 2:
                        Game_RequestAreaChange(AREA_ID_DAUNA_MINE_BAIS, TO_COORD(52), TO_COORD(67), AREA_ENTRY_MAP_LOADING | FACING_UP);
                        break;
                    case 3:
                    case 5:
                        Game_RequestAreaChange(AREA_ID_DAUNA_MINE_INTRO, TO_COORD(62), TO_COORD(5), AREA_ENTRY_MAP_LOADING | FACING_UP);
                        break;
                }
                g_SceneEventState.step = 4;
            }
            break;
        case 4:
            flag = &g_ScriptVars[3];
            if (*flag == 0x31) {
                *flag = 0;
                Game_ClearScriptActive();
                SYS_ClearFlag(g_SceneEventFlags, 30);
                SYS_ClearFlag(g_SceneEventFlags, 31);
                g_SceneEventState.mode      = SCENE_EVENT_NONE;
                g_SceneEventState.step      = 0;
                g_SceneEventState.selection = 0;
            }
            break;
    }
}
