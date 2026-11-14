/* Launches the facing probe from a free actor slot once the script reaches CHAR_LAUNCH_SCRIPT_PC. */
MATCH void Char_ClaimLinkSlot(void) {
    Actor_StepAnimLoop();
    if (g_Task->script_pc == CHAR_LAUNCH_SCRIPT_PC) {
        g_Task->param.actor_slot = Actor_FindFreeSlot();
        if (g_Task->param.actor_slot != GAME_NONE) {
            g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
            g_SpawnedActors[g_Task->param.actor_slot].type         = ACTOR_TYPE_FACING_PROBE;
        }
        /* FAKE: retail reads SND_PlayCue as void(s32). */
        ((void (*)(s32))SND_PlayCue)(g_Task->unk_2C + 0x100);
        g_Task->option_flags = 0;
        g_Task->header.step++;
    }
}
