/* Launches the facing probe from a free actor slot once the script reaches CHAR_LAUNCH_SCRIPT_PC. */
MATCH void PlChar_ClaimLinkSlot(void) {
    Script_AnimStepLoop();
    if (TASK(Actor)->script_pc == CHAR_LAUNCH_SCRIPT_PC) {
        TASK(Actor)->param.actor_slot = Actor_FindFreeSpawned();
        if (TASK(Actor)->param.actor_slot != GAME_NONE) {
            g_SpawnedActors[TASK(Actor)->param.actor_slot].header.flags = 1;
            g_SpawnedActors[TASK(Actor)->param.actor_slot].type         = ACTOR_TYPE_FACING_PROBE;
        }
        /* FAKE: retail reads SND_SEPlay as void(s32). */
        ((void (*)(s32))SND_SEPlay)(TASK(Actor)->unk_2C + 0x100);
        TASK(Actor)->option_flags = 0;
        TASK(Actor)->header.step++;
    }
}
