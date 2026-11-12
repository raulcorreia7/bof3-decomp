#include "game_00.h"

/* func_801B6044 */
MATCH s32 Game_RequestGarrPush(void) {
    if (g_Game.current->chr.character_id != CHAR_ID_GARR) {
        return 0;
    }
    if ((g_Task->direction_08 & 0x1) == 0) {
        return 0;
    }
    g_Task->param.unk_0B++;
    if (g_Task->param.unk_0B != GARR_PUSH_HOLD_FRAMES) {
        return 0;
    }
    g_Task->header.mode                       = FIELD_TASK_MODE_PERSONAL_ACTION;
    g_Task->header.step                       = 0;
    g_Game.current->u.field.mode_12B.u8_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    return 1;
}
