#include "area118_13.h"

MATCH void func_801F2D78(void) {
    if (g_GameStateIndex != 2 && g_GameEntryState != 4 && D_80145FBB != 2 && g_GameStateIndex != 1 &&
        g_GameEntryState != 3 && (g_InputPressed & D_80145AB8) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 7;
        func_80196070();
    }
}
