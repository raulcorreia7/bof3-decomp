#include "game_00.h"

/* func_801B5F68 */
MATCH bool Game_RequestRockKick(s32 walk_speed) {
    s32 kind;
    s8  result;

    kind = g_Game.current->chr.character_id;
    if (kind != CHAR_ID_TEEPO && kind != CHAR_ID_PECO)
        return false;
    if (!(g_Task->direction_08 & 0x1))
        return false;
    if ((walk_speed & BYTE_MASK) != FIELD_SPEED_RUN)
        return false;
    result = Game_FindRockAhead(walk_speed, kind);
    if (result == -1)
        return false;
    g_Game.current->u.field.mode_12B.u8_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    g_Task->param.unk_0B                      = result;
    g_Task->header.mode                       = FIELD_TASK_MODE_PERSONAL_ACTION;
    g_Task->header.step                       = 1;
    g_Task->unk_03                            = 0;
    return true;
}
