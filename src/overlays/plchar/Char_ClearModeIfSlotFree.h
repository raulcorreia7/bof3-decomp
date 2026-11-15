/* Clears the panel mode byte in the game state record once the actor slot at the work byte +0x0B is free, then runs Actor_StepAnimLoop. */
MATCH void Char_ClearModeIfSlotFree(void) {
    if (g_SpawnedActors[g_Task->param.actor_slot].header.flags == 0) {
        g_Game.current->u.field.mode_12B.s8_value = 0;
    }
    Actor_StepAnimLoop();
}
