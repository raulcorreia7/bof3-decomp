/* Clears the panel mode byte in the game state record during scenario 15. */
/* func_801CFCE8 (plp267), func_801CF23C (plp257), func_801CEC60 (plp457), func_801CFAEC (plp567) */
MATCH void Char_StartNearestFacingTurn(void) {
    s32 to_back;
    s32 to_away;

    if (g_SceneState.scenario_id == 15) {
        g_Game.current->u.field.mode_12B.s8_value = 0;
    } else {
        to_back = g_Task->direction_08 - FACING_RIGHT;
        to_back = ABS(to_back);
        to_away = g_Task->direction_08 - FACING_DOWN;
        to_away = ABS(to_away);
        if (to_away < to_back) {
            g_Task->param.turn_step = func_801B2D00(FACING_DOWN);
            g_Task->unk_03          = FACING_DOWN;
        } else {
            g_Task->param.turn_step = func_801B2D00(FACING_RIGHT);
            g_Task->unk_03          = FACING_RIGHT;
        }
        g_Task->timer = 2;
        g_Task->header.step++;
    }
}
