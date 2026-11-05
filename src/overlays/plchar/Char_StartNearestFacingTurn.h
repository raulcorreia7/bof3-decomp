/* Clears the panel mode byte in the game state record during scenario 15;
 * otherwise picks the nearer of directions 3 and 5 by distance from the work
 * direction byte, starts that direction's script through func_801B2D00 as the
 * turn target at byte 0x03, loads the timer at byte 0x09 with 2 and advances
 * the handler index. One definition shared by the plchar character programs;
 * each program includes it where the function sits, and a change must keep
 * every member matching.
 */
/* func_801CFCE8 (plp267), func_801CF23C (plp257), func_801CEC60 (plp457), func_801CFAEC (plp567) */
MATCH void Char_StartNearestFacingTurn(void) {
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
            g_SpadWork->unk_0B = func_801B2D00(5);
            g_SpadWork->unk_03 = 5;
        } else {
            g_SpadWork->unk_0B = func_801B2D00(3);
            g_SpadWork->unk_03 = 3;
        }
        g_SpadWork->unk_09 = 2;
        g_SpadWork->state_02++;
    }
}
