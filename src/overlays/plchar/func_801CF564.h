/* Counts down the step byte; while it is nonzero it decrements the byte and calls the step handler, at zero it clears the mode byte and game flag 0x1000, then runs the follow-up call. */
MATCH void func_801CF564(void) {
    if (g_Task->timer == 0) {
        g_Game.current->u.field.mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_Task->timer--;
        Actor_UpdateMovement();
    }
    Actor_StepAnimLoop();
}
