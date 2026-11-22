#include "area118_13.h"

MATCH void func_801F2D78(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && g_Game.members[0].u.field.mode.unsigned_value != 2 && g_GameStateIndex != GAME_REQUEST_MENU && g_GameEntryState != 3 &&
        (g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_MENU]) == 0) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScenarioState.state_04 = 7;
        Actor_Clear();
    }
}
