#include "area118_13.h"

MATCH void func_801F2D78(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && g_Game.members[0].u.field.mode_12B.u8_value != 2 && g_GameStateIndex != GAME_REQUEST_MENU && g_GameEntryState != 3 &&
        (g_InputPressed & g_InputMasks[FIELD_INPUT_MENU]) == 0) {
        Game_SetScriptActive();
        g_SceneState.step_05  = 5;
        g_SceneState.state_04 = 7;
        Actor_Clear();
    }
}
