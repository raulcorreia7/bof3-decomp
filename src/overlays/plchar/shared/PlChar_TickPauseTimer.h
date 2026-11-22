/* Counts the pause timer down and ends the pause at zero. */
MATCH void PlChar_TickPauseTimer(void) {
    if (TASK(Actor)->timer == 0) {
        g_Game.current->u.field.mode.value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        TASK(Actor)->timer--;
        Actor_MovementUpdate();
    }
    Script_AnimStepLoop();
}
