/* Starts the turn to the nearer of facings 3 and 5: stores that facing and its Actor_GetTurnStep sign, sets the timer byte to 2 and advances the task state; on scenario 15 it only clears the panel mode byte. */
MATCH void PlChar_StartFacingTurn(void) {
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
            SELF(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_DOWN);
            SELF(Actor)->unk_03           = FACING_DOWN;
        } else {
            SELF(Actor)->param.turn_delta = Actor_GetTurnStep(FACING_RIGHT);
            SELF(Actor)->unk_03           = FACING_RIGHT;
        }
        SELF(Actor)->timer = 2;
        SELF(Actor)->header.step++;
    }
}
