/* Starts the turn to the nearer of facings 3 and 5: stores that facing and its Actor_GetTurnStep sign, sets the timer byte to 2 and advances the task state; on scenario 15 it only clears the panel mode byte. */
MATCH void Char_StartFacingTurn(void) {
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
            g_Task->param.turn_step = Actor_GetTurnStep(FACING_DOWN);
            g_Task->unk_03          = FACING_DOWN;
        } else {
            g_Task->param.turn_step = Actor_GetTurnStep(FACING_RIGHT);
            g_Task->unk_03          = FACING_RIGHT;
        }
        g_Task->timer = 2;
        g_Task->header.step++;
    }
}
