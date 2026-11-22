#include "area141_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3D28(void) {
    switch (g_SceneEventState.step) {
        case 0:
            /* Wait for an open message to close, then unwind the event. */
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                Scene_SetupParty(5);
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
        case 10:
            UI_MessageStartArea(3);
            g_GameStateIndex       = GAME_REQUEST_MESSAGE;
            D_801448EE             = 0;
            g_SceneEventState.step = 11;
            g_Game.flags |= 0x7;
            break;
        case 11:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_SceneEventState.step = 12;
            }
            break;
        case 12:
            /* Hold the beat for 450 frames; any button skips to the cancel step. */
            D_801448EE++;
            if (D_801448EE >= 450) {
                g_SceneEventState.step = 13;
            } else if (g_PadStates[0].pressed != 0) {
                g_SceneEventState.step = 20;
            }
            break;
        case 13:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            UI_MessageStartArea(4);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            Area_ScrollStartRoute(2);
            g_SceneEventState.step = 14;
            break;
        case 14:
            /* The script releases the row-2 cell band and starts a 60-frame beat. */
            if (g_ScriptVars[0] == 1) {
                SYS_SetFlag(g_SceneEventFlags, 0x7A);
                Area_CellSetRun(D_801F4D9E, 0);
                Area_CellSetRun(D_801F4D9E + 5, 0);
                D_801448EE             = 60;
                g_SceneEventState.step = 15;
            }
            break;
        case 15:
            /* The beat ends: recentre the camera scroll on the leader. */
            D_801448EE--;
            if (D_801448EE == 0) {
                g_SceneEventState.step = 16;
                g_AreaScrollTargetX    = g_Game.members[0].pos.x.fixed;
                g_AreaScrollTargetY    = g_Game.members[0].pos.y.fixed;
            }
            break;
        case 16:
            /* Wait for the scroll to stop, then latch the window mode and end. */
            if (g_AreaCameraMoving != 0) {
                break;
            }
            g_SceneEventState.step = 20;
            g_UiWindowChannel |= FRONTEND_FLAG_MODE_LATCH;
            break;
        case 20:
            /* Cancel: hand the field back and drop the three low flag bits. */
            Game_ClearScriptActive();
            g_SceneEventState.mode = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            g_Game.flags &= ~0x7;
            break;
        case 30:
            /* Retire the row-4 cell band, or cancel if a flag already retired it. */
            if (SYS_TestFlag(g_SceneEventFlags, 0x7B) != 0) {
                g_SceneEventState.step = 20;
                break;
            }
            SYS_SetFlag(g_SceneEventFlags, 0x7B);
            Area_CellSetRun(D_801F4DA8, 0);
            Area_CellSetRun(D_801F4DA8 + 5, 0);
            D_801448EE             = 60;
            g_SceneEventState.step = 31;
            break;
        case 31:
        case 41:
            D_801448EE--;
            if (D_801448EE == 0) {
                g_SceneEventState.step = 20;
            }
            break;
        case 40:
            /* Retire the row-6 cell band, or cancel if a flag already retired it. */
            if (SYS_TestFlag(g_SceneEventFlags, 0x7C) != 0) {
                g_SceneEventState.step = 20;
                break;
            }
            SYS_SetFlag(g_SceneEventFlags, 0x7C);
            Area_CellSetRun(D_801F4DB2, 0);
            Area_CellSetRun(D_801F4DB2 + 5, 0);
            D_801448EE             = 60;
            g_SceneEventState.step = 41;
            break;
        case 50:
            /* The script asks for the area scene mode; hold 60 frames first. */
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_AreaSceneMode        = 1;
            D_801448EE             = 60;
            g_SceneEventState.step = 51;
            break;
        case 51:
            D_801448EE--;
            if (D_801448EE != 0) {
                break;
            }
            g_SceneEventState.mode = SCENE_EVENT_NONE;
            g_SceneEventState.step = 0;
            g_ScriptVars[0]++;
            break;
    }
}
#else
INCLUDE_ASM(func_801F3D28);
#endif
