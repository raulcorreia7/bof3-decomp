#include "engine/game/00/game_00.h"

/* func_801B5EBC */
MATCH bool Game_RequestPersonalAction(void) {
    u8 type;

    type = g_Game.current->chr.character_id;
    if (type == CHAR_ID_GARR || type == CHAR_ID_REI)
        return 0;
    if (type == CHAR_ID_RYU_PAJAMAS || type == CHAR_ID_WHELP)
        return 0;
    if (!(g_PadStates[0].pressed & g_InputMasks[FIELD_INPUT_PERSONAL_ACTION]))
        return 0;
    if (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP)
        return 0;
    SELF(Actor)->header.mode = FIELD_TASK_MODE_PERSONAL_ACTION;
    ACTOR_CLEAR_STEP();
    g_Game.current->u.field.mode.unsigned_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    return 1;
}
