#include "engine/game/00/game_00.h"

/* func_801B6044 */
MATCH bool Game_RequestGarrPush(void) {
    if (g_Game.current->chr.character_id != CHAR_ID_GARR) {
        return 0;
    }
    if ((TASK(Actor)->direction & 0x1) == 0) {
        return 0;
    }
    TASK(Actor)->param.unk_0B++;
    if (TASK(Actor)->param.unk_0B != GARR_PUSH_HOLD_FRAMES) {
        return 0;
    }
    TASK(Actor)->header.mode                    = FIELD_TASK_MODE_PERSONAL_ACTION;
    TASK(Actor)->header.step                    = 0;
    g_Game.current->u.field.mode.unsigned_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    return 1;
}
