/* Clears the panel mode byte in the game state record during scenario 15; otherwise picks the nearer of directions 3 and 5 by distance from the work direction byte, starts that direction's script through func_801B2D00 as the turn target at byte 0x03, loads the timer at byte 0x09 with 2 and advances the handler index. */
/* func_801CFCE8 (plp267), func_801CF23C (plp257), func_801CEC60 (plp457), func_801CFAEC (plp567) */
MATCH void PlChar_StartNearestFacingTurn(void) {
    s32 to_back;
    s32 to_away;

    if (g_ScenarioState.scenario_id == 15) {
        g_Game.current->u.field.mode.value = 0;
    } else {
        to_back = SELF(Actor)->direction - FACING_RIGHT;
        to_back = ABS(to_back);
        to_away = SELF(Actor)->direction - FACING_DOWN;
        to_away = ABS(to_away);
        if (to_away < to_back) {
            SELF(Actor)->param.turn_delta = func_801B2D00(FACING_DOWN);
            SELF(Actor)->unk_03           = FACING_DOWN;
        } else {
            SELF(Actor)->param.turn_delta = func_801B2D00(FACING_RIGHT);
            SELF(Actor)->unk_03           = FACING_RIGHT;
        }
        SELF(Actor)->timer = 2;
        SELF(Actor)->header.step++;
    }
}
