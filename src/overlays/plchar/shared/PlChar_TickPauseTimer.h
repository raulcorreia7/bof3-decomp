/* Counts the pause timer down and ends the pause at zero. */
MATCH void PlChar_TickPauseTimer(void) {
    if (SELF(Actor)->timer == 0) {
        g_Game.current->u.field.mode.value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        SELF(Actor)->timer--;
        Actor_MovementUpdate();
    }
    Script_AnimStepLoop();
}
