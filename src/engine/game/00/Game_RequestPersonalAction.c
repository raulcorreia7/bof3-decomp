#include "game_00.h"

/* func_801B5EBC */
MATCH s32 Game_RequestPersonalAction(void) {
    u8 kind;

    kind = g_GameState->slot_index_79;
    if (kind == 2 || kind == 4)
        return 0;
    if (kind == 9 || kind == 10)
        return 0;
    if (!(g_InputPressed & g_InputMasks[FIELD_INPUT_PERSONAL_ACTION]))
        return 0;
    if (g_GameRequestFlags & GAME_REQUEST_FLAG_WORLD_MAP)
        return 0;
    g_Task->header.mode = FIELD_TASK_MODE_PERSONAL_ACTION;
    ACTOR_CLEAR_STEP();
    g_GameState->mode_12B.u8_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    return 1;
}
