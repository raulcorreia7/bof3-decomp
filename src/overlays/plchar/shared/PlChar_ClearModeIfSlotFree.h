/* Clears the panel mode byte in the game state record once the actor slot at the work byte +0x0B is free, then runs Script_AnimStepLoop. */
MATCH void PlChar_ClearModeIfSlotFree(void) {
    if (g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags == 0) {
        g_Game.current->u.field.mode.value = 0;
    }
    Script_AnimStepLoop();
}
