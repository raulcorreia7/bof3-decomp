/* Counts the pause timer down and ends the pause at zero. */
MATCH void PlChar_TickPauseTimer(void) {
    if (g_Task->timer == 0) {
        g_Game.current->u.field.mode.value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_Task->timer--;
        Actor_UpdateMovement();
    }
    Actor_StepAnimLoop();
}
