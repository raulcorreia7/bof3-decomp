/* Starts the turn to the nearer of facings 3 and 5: stores that facing and its
 * Actor_GetTurnStep sign, sets the timer byte to 2 and advances the task
 * state; on scenario 15 it only clears the panel mode byte. One definition
 * shared by the plchar character programs; each program includes it where the
 * function sits, and a change must keep every member matching.
 */
MATCH void Char_StartFacingTurn(void) {
    s32 to_back;
    s32 to_away;

    if (g_SceneState.scenario_id == 15) {
        g_GameState->mode_12B.s8_value = 0;
    } else {
        to_back = g_SpadWork->direction_08 - 3;
        to_back = ABS(to_back);
        to_away = g_SpadWork->direction_08 - 5;
        to_away = ABS(to_away);
        if (to_away < to_back) {
            g_SpadWork->unk_0B = Actor_GetTurnStep(5);
            g_SpadWork->unk_03 = 5;
        } else {
            g_SpadWork->unk_0B = Actor_GetTurnStep(3);
            g_SpadWork->unk_03 = 3;
        }
        g_SpadWork->unk_09 = 2;
        g_SpadWork->state_02++;
    }
}
