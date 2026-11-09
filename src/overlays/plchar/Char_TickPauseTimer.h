/* Counts the pause timer down and ends the pause at zero. */
MATCH void Char_TickPauseTimer(void) {
    if (g_Task->timer == 0) {
        g_Game.current->u.field.mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_Task->timer--;
        func_801B0DFC();
    }
    Actor_StepAnimLoop();
}
