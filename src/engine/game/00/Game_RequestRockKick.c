#include "game_00.h"

/* func_801B5F68 */
MATCH bool Game_RequestRockKick(s32 walk_speed) {
    s32 type;
    s8  result;

    type = g_Game.current->chr.character_id;
    if (type != CHAR_ID_TEEPO && type != CHAR_ID_PECO)
        return false;
    if (!(g_Task->direction & 0x1))
        return false;
    if ((walk_speed & BYTE_MASK) != FIELD_SPEED_RUN)
        return false;
    result = Game_FindRockAhead(walk_speed, type);
    if (result == -1)
        return false;
    g_Game.current->u.field.mode.unsigned_value = GAME_PANEL_MODE_PERSONAL_ACTION;
    g_Task->param.unk_0B                        = result;
    g_Task->header.mode                         = FIELD_TASK_MODE_PERSONAL_ACTION;
    g_Task->header.step                         = 1;
    g_Task->unk_03                              = 0;
    return true;
}
