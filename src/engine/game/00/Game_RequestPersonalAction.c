#include "game_00.h"

/* func_801B5EBC */
MATCH bool Game_RequestPersonalAction(void) {
    u8 kind;

    kind = g_Game.current->chr.character_id;
    if (kind == CHAR_ID_GARR || kind == CHAR_ID_REI)
        return 0;
    if (kind == CHAR_ID_RYU_PAJAMAS || kind == CHAR_ID_WHELP)
        return 0;
    if (!(g_InputPressed & g_InputMasks[FIELD_INPUT_PERSONAL_ACTION]))
        return 0;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP)
        return 0;
    g_Task->header.mode = FIELD_TASK_MODE_PERSONAL_ACTION;
    ACTOR_CLEAR_STEP();
    g_Game.current->u.field.mode_12B.u8_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    return 1;
}
